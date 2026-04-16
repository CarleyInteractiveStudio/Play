# Carley Play OS v8.0 - "Platform Consolidation"

Esta versión convierte a Carley Play en una plataforma robusta y segura para el desarrollo masivo.

## Novedades de la Plataforma:
1.  **Protección de Memoria (MMU):** El kernel ahora aísla la memoria del juego de la del sistema. Un error en el juego ya no colgará la consola.
2.  **Librerías Compartidas (.cpl):** Sistema de enlazado dinámico para ahorrar espacio en la tarjeta SD.
3.  **Compilador de Shaders:** Herramienta `cp-shc.py` para facilitar el desarrollo de gráficos 3D en Creative Engine.

## SDK Actualizado:
- `mmu_init()`: Activa la protección de hardware.
- `tools/cp-shc.py`: Compila tus efectos visuales.

---
**Desarrollado para CP - Carley Play**
