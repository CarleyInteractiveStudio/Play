# Carley Play (Play OS) - Release Bare Metal v1.0

Este paquete contiene el sistema operativo **Play OS** totalmente preparado para el hardware **Carley Play** (Game Stick 4k Lite B-1).

## Cambios Realizados para Bare Metal:
1.  **Sin Dependencias de SO:** Se han eliminado `std::vector`, `std::string` y lectura de archivos. El código es C/C++ puro compatible con Bare Metal.
2.  **Datos Embebidos:** El catálogo de juegos está incluido directamente en el binario (`src/catalog_data.h`).
3.  **Gestor de Memoria:** Se ha incluido un `malloc` básico en `src/kernel.c` que utiliza un heap estático de 16MB.
4.  **Resolución HD:** Configurado a 1280x720 para salida HDMI.
5.  **Mando:** Soporte de navegación por grupos habilitado.

## Cómo empezar:
1.  **Drivers de Video:** Abre `src/kernel.c` e implementa la función `kernel_flush_area`. Debes copiar el `px_map` a la dirección de memoria de tu Framebuffer.
2.  **Drivers de Mando:** En `src/kernel.c`, implementa `kernel_get_gamepad_state` para leer los botones de tu driver USB.
3.  **Compilar:** Ejecuta `make`. El resultado será un archivo `play_os.bin`.

---
**Desarrollado para CP - Carley Play**
