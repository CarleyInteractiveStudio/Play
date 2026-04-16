# Carley Play OS v7.0 - "Industrial Grade"

Esta versión marca la transición de la consola a un ecosistema de desarrollo profesional.

## Cambios de Arquitectura (Nivel Industrial):
1.  **Migración Cortex-A7:** Todo el sistema ahora corre nativamente en la arquitectura A7 con soporte NEON y VFP.
2.  **DDR Real (0x60000000):** Se han ajustado las direcciones de memoria a la ubicación real de la RAM en el chip RK3128.
3.  **Creative Bridge:** Capa de soporte directo para tu motor propio 'Creative Engine'.
4.  **USB HID Completo:** El sistema ahora puede entender cualquier mando inalámbrico mediante el análisis de descriptores HID.
5.  **Instalación OTA (Inalámbrica):** Capacidad de recibir y grabar juegos en la SD mediante el programa de PC.

## Notas para Desarrolladores:
- Usa el `toolchain.cmake` actualizado para tus proyectos de motor.
- Implementa `creative_run()` en tu motor para integrarlo al instante.

---
**Desarrollado para CP - Carley Play**
