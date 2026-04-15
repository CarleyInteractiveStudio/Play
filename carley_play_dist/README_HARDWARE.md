# Carley Play (Play OS) - Release para Hardware Real

Este directorio contiene el código fuente de **Play OS** configurado y optimizado para la consola **Carley Play** (basada en el hardware Game Stick 4k Lite B-1 / GB2).

## Cambios Realizados para el Hardware:
1.  **Eliminación de SDL2:** El sistema ahora está configurado para ejecutarse en modo "Bare Metal" (sin sistema operativo pesado).
2.  **Resolución Optimizada:** Configurado a 1280x720 (720p) para llenar la pantalla de la TV con máxima fluidez.
3.  **Gestión de Mandos:** Se ha incluido un módulo `input_handler` para conectar los mandos inalámbricos.
4.  **Marca Carley Play:** La interfaz ha sido personalizada con los nombres "Carley Play" y "CP".

## Instrucciones para el Desarrollador del Kernel:

### 1. Conexión con el Video
En `src/main.cpp`, debes implementar las funciones:
*   `kernel_init_video()`: Inicializa el hardware de video.
*   `kernel_flush_area(...)`: Copia el buffer de píxeles a la memoria de video real (`/dev/fb0` o dirección física).

### 2. Conexión con los Mandos
En `src/input_handler.cpp`, debes implementar:
*   `kernel_get_gamepad_state(...)`: Esta función debe rellenar la estructura con el estado actual de los botones (presionado o no) leídos desde el USB/Bluetooth.

**Nota sobre Navegación:** El sistema usa `lv_group_t` para la navegación con mando. He configurado la lista principal para que responda automáticamente al mando. Si añades nuevos botones, recuerda añadirlos al grupo usando `lv_group_add_obj(cp_input_get_group(), nuevo_boton);`.

### 3. Compilación
He incluido un Makefile configurado para `arm-none-eabi-gcc`. Para compilar, simplemente abre una terminal en esta carpeta y escribe:
```bash
make
```
Esto generará un archivo `play_os.bin` que puedes cargar en tu hardware.

---
**Desarrollado para CP - Carley Play**
