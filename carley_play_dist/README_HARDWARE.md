# Carley Play OS v4.5 - "Hyper Optimized"

Esta versión se centra en el rendimiento puro y la reducción de tamaño.

## Mejoras de Optimización:
1.  **Compresión LZ4:** Los juegos .pg ahora pueden estar comprimidos. El sistema los descomprime al vuelo en la RAM, ahorrando hasta un 50% de espacio en la SD.
2.  **Aceleración NEON:** El SDK usa las instrucciones matemáticas vectoriales del Cortex-A7 para mezclas de color ultra-rápidas.
3.  **Transferencia DMA:** El video ya no consume CPU. El hardware DMA se encarga de mover los píxeles a la pantalla.
4.  **libcp-mini:** Nuevo runtime que reduce el peso de los ejecutables al mínimo.

## Cambios en el SDK:
- `cp_alpha_blend_neon(...)`: Mezcla de imágenes por hardware.
- `pg-pack --compress`: Opción para crear juegos comprimidos.

---
**Desarrollado para CP - Carley Play**
