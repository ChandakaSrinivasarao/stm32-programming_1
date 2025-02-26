# Path to stlink folder for uploading code to board
STLINK=~/Desktop/linux-workspace/stm32-programming/sources/stlink-1.8.0/build/Release/bin

# Put your source files here (*.c)
SRCS=main.c system_stm32f4xx.c

# Libraries source files
SRCS += stm32f4xx_rcc.c
SRCS += stm32f4xx_gpio.c

# Add syscalls.c
SRCS += syscalls.c

# Add FreeRTOS source files
FREERTOS_DIR=/home/srinu/Desktop/linux-workspace/stm32-programming/sources/FreeRTOS/Source
PORT_DIR=$(FREERTOS_DIR)/portable/GCC/ARM_CM4F
HEAP_DIR=$(FREERTOS_DIR)/portable/MemMang
SRCS += $(FREERTOS_DIR)/croutine.c
SRCS += $(FREERTOS_DIR)/list.c
SRCS += $(FREERTOS_DIR)/queue.c
SRCS += $(FREERTOS_DIR)/tasks.c
SRCS += $(FREERTOS_DIR)/timers.c
SRCS += $(FREERTOS_DIR)/event_groups.c
SRCS += $(FREERTOS_DIR)/FreeRTOS_CLI.c
SRCS += $(PORT_DIR)/port.c
SRCS += $(HEAP_DIR)/heap_4.c  # Choose the appropriate heap implementation

# Binaries will be generated with this name (.elf, .bin, .hex)
PROJ_NAME=build

# Put your STM32F4 library code directory here.
STM_COMMON=/home/srinu/Desktop/linux-workspace/stm32-programming/sources/STM32F4-Discovery_FW_V1.1.0

# Compiler settings. Only edit CFLAGS to include other header files.

CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy
OBJSIZE=arm-none-eabi-size

# Compiler flags
CFLAGS  = -g -O2 -Wall -Tstm32_flash.ld
CFLAGS += -DUSE_STDPERIPH_DRIVER
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m4 -mthumb-interwork
CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16
CFLAGS += -I.

# Include files from STM libraries
CFLAGS += -I$(STM_COMMON)/Libraries/CMSIS/Include
CFLAGS += -I$(STM_COMMON)/Libraries/CMSIS/ST/STM32F4xx/Include
CFLAGS += -I$(STM_COMMON)/Libraries/STM32F4xx_StdPeriph_Driver/inc
CFLAGS += -I$(STM_COMMON)/Utilities/STM32F4-Discovery

# Include FreeRTOS headers
CFLAGS += -I$(FREERTOS_DIR)/include
CFLAGS += -I$(PORT_DIR)

# add startup file to build
SRCS += $(STM_COMMON)/Libraries/CMSIS/ST/STM32F4xx/Source/Templates/TrueSTUDIO/startup_stm32f4xx.s
OBJS = $(SRCS:.c=.o)

vpath %.c $(STM_COMMON)/Libraries/STM32F4xx_StdPeriph_Driver/src \

.PHONY: proj

all: proj

proj: $(PROJ_NAME).elf

$(PROJ_NAME).elf: $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@
	$(OBJCOPY) -O ihex $(PROJ_NAME).elf $(PROJ_NAME).hex
	$(OBJCOPY) -O binary $(PROJ_NAME).elf $(PROJ_NAME).bin
# Print the size of the ELF file
	$(OBJSIZE) $@

clean:
	rm -f *.o $(PROJ_NAME).elf $(PROJ_NAME).hex $(PROJ_NAME).bin

# Flash the STM32F4
burn: proj
	$(STLINK)/st-flash write $(PROJ_NAME).bin 0x8000000
