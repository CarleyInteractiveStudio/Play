# Carley Play (Play OS) - Release Bare Metal v1.5 "Core Engine"

Esta versión completa el núcleo funcional de la consola **Carley Play** para el hardware **RK3128**.

## Drivers Críticos Implementados:
1.  **SDMMC Completo:** Lectura real de sectores desde la Micro SD.
2.  **USB Host HID:** Soporte para detectar mandos inalámbricos por USB.
3.  **Lanzador de Juegos (Loader):** Sistema que carga un binario de la SD a la RAM y lo ejecuta.
4.  **Depuración UART:** Puerto serie activo a 115200 baudios para ver los registros del sistema.

## Integración:
Este código permite que la consola sea autónoma. Al compilar y arrancar, el sistema inicializa todo el hardware y queda listo para cargar juegos desde la tarjeta SD.

---
**Desarrollado para CP - Carley Play**
