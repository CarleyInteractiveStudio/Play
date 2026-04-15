# Carley Play (Play OS) - Release Bare Metal v1.2 "Dynamic Kernel"

Esta versión convierte el núcleo en un sistema dinámico y real:

## Nuevas Funcionalidades Reales:
1.  **Filesystem (FAT32):** Lector de archivos real para tarjetas SD. Puede buscar particiones y abrir archivos.
2.  **Memoria Dinámica:** Gestor de memoria con `malloc` y `free` para manejar los 256MB de la consola.
3.  **Reloj Real (RTC):** Acceso al reloj de hardware del RK3128.
4.  **Optimización de Velocidad:** Configuración de relojes (CRU) para máximo rendimiento.

## Cómo usar:
El código fuente está en la carpeta `src`. Al compilar con `make`, obtendrás el binario para tu Game Stick.

---
**Desarrollado para CP - Carley Play**
