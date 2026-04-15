# Carley Play OS - Native Game Engine Edition (v2.0)

Este paquete convierte el hardware en una plataforma de desarrollo de juegos nativos.

## Novedades de la Versión 2.0:
1.  **Nuevo Dashboard:** Interfaz con diseño propio (no PlayStation). Iconos dinámicos, descripciones y leyendas de controles.
2.  **Audio HDMI:** Driver I2S real para salida de sonido digital por televisión.
3.  **Ejecución Nativa:** El sistema puede cargar binarios directos desde la SD a la RAM y ejecutarlos.
4.  **SDK para Desarrolladores:** Se incluye `cp_sdk.h` para que crees tus propios juegos 2D/3D optimizados.

## Cómo crear juegos para Carley Play:
1.  Incluye `cp_sdk.h` en tu proyecto de C.
2.  Usa la dirección `0x01000000` para dibujar en el Framebuffer.
3.  Compila tu juego como un binario plano (`.bin`) y ponlo en tu tarjeta SD.

---
**Desarrollado para CP - Carley Play**
