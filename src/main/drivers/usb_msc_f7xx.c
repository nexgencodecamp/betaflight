/*
 * This file is part of Cleanflight.
 *
 * Cleanflight is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Cleanflight is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Cleanflight.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Author: Chris Hockuba (https://github.com/conkerkh)
 *
 */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "platform.h"

#if defined(USE_USB_MSC)

#include "build/build_config.h"

#include "common/utils.h"

#include "blackbox/blackbox.h"
#include "drivers/io.h"
#include "drivers/light_led.h"
#include "drivers/nvic.h"
#include "drivers/time.h"
#include "drivers/usb_msc.h"

#include "pg/usb.h"

#include "vcp_hal/usbd_cdc_interface.h"
#include "usb_io.h"
#include "usbd_msc.h"
#include "msc/usbd_storage.h"

USBD_HandleTypeDef USBD_Device;

#define DEBOUNCE_TIME_MS 20

static IO_t mscButton;

void mscInit(void)
{
    if (usbDevConfig()->mscButtonPin) {
        mscButton = IOGetByTag(usbDevConfig()->mscButtonPin);
        IOInit(mscButton, OWNER_USB_MSC_PIN, 0);
        if (usbDevConfig()->mscButtonUsePullup) {
            IOConfigGPIO(mscButton, IOCFG_IPU);
        } else {
            IOConfigGPIO(mscButton, IOCFG_IPD);
        }
    }
}

uint8_t mscStart(void)
{
    ledInit(statusLedConfig());

    //Start USB
    usbGenerateDisconnectPulse();

    IOInit(IOGetByTag(IO_TAG(PA11)), OWNER_USB, 0);
    IOInit(IOGetByTag(IO_TAG(PA12)), OWNER_USB, 0);

    USBD_Init(&USBD_Device, &VCP_Desc, 0);

    /** Regsiter class */
    USBD_RegisterClass(&USBD_Device, USBD_MSC_CLASS);

    /** Register interface callbacks */
    switch (blackboxConfig()->device) {
#ifdef USE_SDCARD
    case BLACKBOX_DEVICE_SDCARD:
        USBD_MSC_RegisterStorage(&USBD_Device, &USBD_MSC_MICRO_SDIO_fops);
        break;
#endif

#ifdef USE_FLASHFS
    case BLACKBOX_DEVICE_FLASH:
        USBD_MSC_RegisterStorage(&USBD_Device, &USBD_MSC_EMFAT_fops);
        break;
#endif

    default:
        return 1;
    }

    USBD_Start(&USBD_Device);

    // NVIC configuration for SYSTick
    NVIC_DisableIRQ(SysTick_IRQn);
    NVIC_SetPriority(SysTick_IRQn, NVIC_BUILD_PRIORITY(0, 0));
    NVIC_EnableIRQ(SysTick_IRQn);

    return 0;
}

bool mscCheckBoot(void)
{
    if (*((__IO uint32_t *)BKPSRAM_BASE + 16) == MSC_MAGIC) {
        return true;
    }
    return false;
}

bool mscCheckButton(void)
{
    bool result = false;
    if (mscButton) {
        uint8_t state = IORead(mscButton);
        if (usbDevConfig()->mscButtonUsePullup) {
            result = state == 0;
        } else {
            result = state == 1;
        }
    }

    return result;
}

void mscWaitForButton(void)
{
    // In order to exit MSC mode simply disconnect the board, or push the button again.
    while (mscCheckButton());
    delay(DEBOUNCE_TIME_MS);
    while (true) {
        asm("NOP");
        if (mscCheckButton()) {
            *((uint32_t *)0x2001FFF0) = 0xFFFFFFFF;
            delay(1);
            NVIC_SystemReset();
        }
    }
}
#endif
