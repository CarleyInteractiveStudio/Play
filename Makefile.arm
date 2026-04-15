# Makefile para Carley Play (Play OS)
# Arquitectura: ARM (GB2 / Bare Metal)

# Compilador Cruzado
CC = arm-none-eabi-gcc
CXX = arm-none-eabi-g++
OBJCOPY = arm-none-eabi-objcopy

# Parámetros de Optimización para ARM
ARCH_FLAGS = -mcpu=arm926ej-s -marm
OPTIMIZATION = -O3 -ffunction-sections -fdata-sections
CFLAGS = $(ARCH_FLAGS) $(OPTIMIZATION) -I. -I./src -I./lvgl -Wall
CXXFLAGS = $(CFLAGS) -std=c++11 -fno-exceptions -fno-rtti

# Enlazado (Bare Metal - Ajustar según el mapa de memoria del kernel)
LDFLAGS = -Wl,--gc-sections -nostartfiles -T link.ld

# Archivos de Fuente
LVGL_DIR = lvgl
include $(LVGL_DIR)/lvgl.mk

SRC_FILES = $(CSRCS) $(CPPSRCS)
SRC_FILES += src/main.cpp src/ui.cpp src/data_manager.cpp src/splash.cpp \
             src/store.cpp src/settings.cpp src/app_manager.cpp src/cJSON.c \
             src/input_handler.cpp src/kernel.c

OBJ_FILES = $(SRC_FILES:.cpp=.o)
OBJ_FILES := $(OBJ_FILES:.c=.o)

# Nombre del archivo final
TARGET = play_os.elf
BINARY = play_os.bin

all: $(TARGET) $(BINARY)

$(TARGET): $(OBJ_FILES)
	@echo "Enlazando para ARM..."
	$(CXX) $(OBJ_FILES) $(LDFLAGS) -o $@

$(BINARY): $(TARGET)
	@echo "Generando binario listo para el hardware..."
	$(OBJCOPY) -O binary $< $@

%.o: %.c
	@echo "Compilando C: $<"
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp
	@echo "Compilando C++: $<"
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_FILES) $(TARGET) $(BINARY)
