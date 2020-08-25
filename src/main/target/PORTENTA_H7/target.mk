H747xI_TARGETS += $(TARGET)

HSE_VALUE   = 27000000

FEATURES    += VCP ONBOARDFLASH

TARGET_SRC += \
            drivers/accgyro/accgyro_spi_mpu6500.c \
            drivers/accgyro/accgyro_mpu6500.c \
            drivers/barometer/barometer_dps310.c