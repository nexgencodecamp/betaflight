/*
 * This file is part of Cleanflight and Betaflight.
 *
 * Cleanflight and Betaflight are free software. You can redistribute
 * this software and/or modify this software under the terms of the
 * GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * Cleanflight and Betaflight are distributed in the hope that they
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software.
 *
 * If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#define TARGET_BOARD_IDENTIFIER "POH7"
#define USBD_PRODUCT_STRING     "PORTENTA_H7"

#define LED0_PIN                PK7
#define LED1_PIN                PK5
#define LED2_PIN                PK6

// Force two buttons to look at the single button so config reset on button works
#define USE_BUTTONS
#define	BUTTON_A_PIN            PA4
#define BUTTON_A_PIN_INVERTED // Active high
#define	BUTTON_B_PIN            PA4
#define BUTTON_B_PIN_INVERTED // Active high

#define USE_BEEPER
#define BEEPER_PIN              PH15
#define BEEPER_INVERTED

#define USE_UART

#define USE_UART1
#define UART1_RX_PIN            PA10
#define UART1_TX_PIN            PA9

#define USE_VCP
#define USE_USB_ID

#define SERIAL_PORT_COUNT       10      // VCP, USART1/2/3/6, UART4/5/7/8 & LPUART1

#define USE_SPI
#define USE_SPI_DEVICE_2
#define SPI2_SCK_PIN            PI1
#define SPI2_MISO_PIN           PC2
#define SPI2_MOSI_PIN           PC3
#define SPI2_NSS_PIN            PI0

#define USE_I2C
#define USE_I2C_DEVICE_3
#define I2C3_SCL                PH7
#define I2C3_SDA                PH8
#define I2C_DEVICE              (I2CDEV_1)

#define USE_BARO
#define USE_BARO_DPS310

// MPU6500 interrupt
#define USE_EXTI
#define USE_GYRO_EXTI
#define GYRO_1_EXTI_PIN         PK1
#define USE_MPU_DATA_READY_SIGNAL
#define ENSURE_MPU_DATA_READY_IS_LOW

#define USE_GYRO
#define USE_GYRO_SPI_MPU6500

#define GYRO_1_CS_PIN           PI0
#define GYRO_1_SPI_INSTANCE     SPI2

#define USE_ACC
#define USE_ACC_SPI_MPU6500

#define GYRO_1_ALIGN            CW0_DEG

#define GYRO_CONFIG_USE_GYRO_DEFAULT GYRO_CONFIG_USE_GYRO_1 
#define USE_GYRO_REGISTER_DUMP  // Adds gyroregisters command to cli to dump configured register values

#define USE_TIMER
#define USE_MOTOR

#define USE_ADC
#define USE_ADC_INTERNAL

#define ADC1_INSTANCE           ADC1
#define VBAT_ADC_PIN            NONE
#define DEFAULT_VOLTAGE_METER_SOURCE VOLTAGE_METER_ADC

#define DEFAULT_RX_FEATURE      FEATURE_RX_SERIAL
#define DEFAULT_FEATURES        FEATURE_TELEMETRY 
#define SERIALRX_PROVIDER       SERIALRX_SBUS
#define SERIALRX_UART           SERIAL_PORT_USART1

#define USE_DMA

// Thanks to DMAMUX, H7 does not have limitations on DMA stream assignments to devices (except for collisions among them).
//#define UART1_TX_DMA_OPT        0
//#define UART2_TX_DMA_OPT        1
//#define UART3_TX_DMA_OPT        2
//#define UART4_TX_DMA_OPT        3
//#define UART5_TX_DMA_OPT        4
//#define UART6_TX_DMA_OPT        5
//#define UART7_TX_DMA_OPT        6
//#define UART8_TX_DMA_OPT        7
#define ADC1_DMA_OPT 8

#define TARGET_IO_PORTA 0xffff
#define TARGET_IO_PORTB 0xffff
#define TARGET_IO_PORTC 0xffff
#define TARGET_IO_PORTD 0xffff
#define TARGET_IO_PORTE 0xffff
#define TARGET_IO_PORTF 0xffff
#define TARGET_IO_PORTG 0xffff
#define TARGET_IO_PORTH 0xffff
#define TARGET_IO_PORTI 0xffff
#define TARGET_IO_PORTJ 0xffff
#define TARGET_IO_PORTK 0xffff

#define USABLE_TIMER_CHANNEL_COUNT 4

#define USED_TIMERS  ( TIM_N(1) | TIM_N(2) | TIM_N(3) | TIM_N(5) | TIM_N(8) | TIM_N(12) )