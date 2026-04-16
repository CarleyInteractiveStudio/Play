# Guía de Integración de Motores (Unity / Unreal / Creative Engine)

Carley Play OS soporta motores de juego modernos gracias a su capa de compatibilidad POSIX y GLES.

## Requisitos de Exportación:
- **Arquitectura:** ARMv7-A (Cortex-A7).
- **Formato:** Binario plano (.bin) o ELF ejecutable.
- **Gráficos:** OpenGL ES 2.0 (vía `gles_wrapper.h`).

## Pasos para Compilar:
1.  Exporta tu proyecto desde Unity/Unreal como código C++.
2.  Usa el archivo `toolchain.cmake` incluido en este paquete:
    ```bash
    cmake -DCMAKE_TOOLCHAIN_FILE=toolchain.cmake .
    make
    ```
3.  Copia el archivo resultante a la carpeta `/roms/` de tu tarjeta SD.

## Consideraciones de Hardware:
- Tienes **192MB de RAM** libres para tu juego.
- Usa texturas en formato comprimido para ahorrar VRAM.
- El audio debe ser PCM 44.1kHz para mayor calidad.

---
**Desarrollado para CP - Carley Play**
