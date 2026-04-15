# Carley Play (Play OS) - Release Bare Metal v1.8 "Dynamic & Accelerated"

Esta versión convierte la consola en una plataforma dinámica con aceleración de hardware.

## Nuevas Funcionalidades:
1.  **GIC (Interrupciones):** Soporte real para interrupciones del procesador.
2.  **Catálogo Dinámico:** Lee `catalog.json` desde la SD usando FAT32 y cJSON.
3.  **Aceleración RGA:** Driver para el motor gráfico 2D del RK3128.
4.  **Explorador de Archivos:** Nueva app para navegar por la tarjeta SD.

## Cambios Técnicos:
- Implementado gestor de memoria inteligente (`malloc`/`free`).
- Sistema de archivos real (Lector FAT32).
- Soporte para cadenas de texto dinámicas (Traducciones).

---
**Desarrollado para CP - Carley Play**
