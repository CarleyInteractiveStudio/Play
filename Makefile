# Makefile para el Prototipo de Play OS

# 1. Compiladores y Banderas (Flags)
# ------------------------------------
CC = gcc
CXX = g++
# CFLAGS son para el compilador de C.
# CXXFLAGS son para el compilador de C++.
# -Wall y -Wextra activan casi todas las advertencias, es una buena práctica.
# -g incluye información de depuración.
CFLAGS = -Wall -Wextra -g
CXXFLAGS = -Wall -Wextra -g -std=c++11

# 2. Archivos y Directorios
# ------------------------------------
# Nombre del programa final que se creará.
TARGET = play_os_prototype

# Directorio de nuestro código fuente.
SRC_DIR = src

# Directorio de la biblioteca LVGL.
LVGL_DIR = lvgl

# Archivos fuente de C++ (los nuestros).
CXX_SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Archivos fuente de C (los nuestros + cJSON).
C_SRCS = $(wildcard $(SRC_DIR)/*.c)

# 3. Configuración de la Biblioteca LVGL
# ------------------------------------
# Añadimos los módulos de LVGL que estamos usando.
# Usamos 'wildcard' para tomar todos los archivos .c de cada carpeta.
LVGL_SRCS += $(wildcard $(LVGL_DIR)/src/core/*.c)
LVGL_SRCS += $(wildcard $(LVGL_DIR)/src/hal/*.c)
LVGL_SRCS += $(wildcard $(LVGL_DIR)/src/misc/*.c)
LVGL_SRCS += $(wildcard $(LVGL_DIR)/src/draw/*.c)
LVGL_SRCS += $(wildcard $(LVGL_DIR)/src/font/*.c)
LVGL_SRCS += $(wildcard $(LVGL_DIR)/src/widgets/*.c)
LVGL_SRCS += $(wildcard $(LVGL_DIR)/src/extra/widgets/list/*.c)

# Añadimos los drivers de SDL para LVGL.
LVGL_SRCS += $(wildcard $(LVGL_DIR)/src/drivers/display/sdl/*.c)
LVGL_SRCS += $(wildcard $(LVGL_DIR)/src/drivers/indev/sdl/*.c)

# Juntamos todas las fuentes de C.
C_SRCS += $(LVGL_SRCS)

# 4. Configuración de Inclusión y Enlazado (Includes & Linking)
# ------------------------------------
# Directorios de cabecera (-I) que el compilador debe buscar.
INCLUDES = -I. -I$(LVGL_DIR)

# Banderas del enlazador (linker). `sdl2-config` nos da las banderas
# necesarias para enlazar nuestro programa con la biblioteca SDL2.
LDFLAGS = `sdl2-config --libs` -lstdc++

# 5. Reglas de Compilación
# ------------------------------------
# Convertimos las listas de archivos .c y .cpp en listas de archivos .o (objeto).
OBJS = $(C_SRCS:.c=.o) $(CXX_SRCS:.cpp=.o)

# La regla principal. Se ejecuta por defecto al llamar a `make`.
# Depende del ejecutable final.
all: $(TARGET)

# Regla para crear el ejecutable final.
# Depende de todos los archivos objeto.
# Une todos los .o para crear el programa.
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Regla genérica para compilar archivos .c en archivos .o.
# $< es el archivo fuente (ej. main.c)
# $@ es el archivo de salida (ej. main.o)
$(LVGL_DIR)/%.o: $(LVGL_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) `sdl2-config --cflags` -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) `sdl2-config --cflags` -c $< -o $@

# Regla genérica para compilar archivos .cpp en .o.
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) `sdl2-config --cflags` -c $< -o $@

# 6. Limpieza
# ------------------------------------
# La regla 'clean' borra todos los archivos generados.
# Es útil para forzar una recompilación completa.
clean:
	rm -f $(TARGET) $(OBJS)

# .PHONY le dice a make que 'all' y 'clean' no son nombres de archivos.
.PHONY: all clean