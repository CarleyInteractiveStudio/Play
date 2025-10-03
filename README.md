# Play OS - Prototipo de Interfaz para PC

## 1. ¿Qué es este proyecto?

Este repositorio contiene el código fuente para un **prototipo funcional de la interfaz de "Play OS"**.

**Importante:** Esto **NO** es un sistema operativo completo para el Game Stick Lite 4k. Es una aplicación de escritorio para **Linux (PC)** que demuestra cómo se vería y funcionaría la interfaz de usuario. El objetivo de este prototipo es proporcionar una base de código sólida, segura y funcional que pueda servir como punto de partida para un futuro desarrollo en el hardware real.

### Funcionalidades Implementadas:
*   Una interfaz de usuario con un estilo inspirado en PlayStation.
*   Una lista de juegos y una tienda que se cargan dinámicamente desde `catalog.json`.
*   Un **Gestor de Aplicaciones** completamente funcional que:
    *   Calcula y muestra el uso de almacenamiento real basado en los datos del catálogo.
    *   Permite la **desinstalación persistente** de aplicaciones, actualizando el archivo `catalog.json` en el disco.
*   Una pantalla de "Ajustes" con widgets de ejemplo.
*   Navegación completa entre todas las pantallas.

### Funcionalidades NO Implementadas (Demostrativas):
*   **Lanzamiento de juegos:** Al hacer clic en un juego, no ocurrirá nada.
*   **Descarga de la tienda:** La tienda muestra el contenido del catálogo, pero no descarga archivos.

---

## 2. Requisitos para la Compilación

Para compilar y ejecutar este prototipo en tu ordenador, necesitarás un entorno Linux (como Ubuntu 22.04 o similar) con las siguientes herramientas instaladas:

*   `build-essential` (contiene `make`, `gcc`, `g++`)
*   `libsdl2-dev` (la biblioteca gráfica que usa el prototipo)

Puedes instalar todo con el siguiente comando en la terminal:
```bash
sudo apt-get update && sudo apt-get install -y build-essential libsdl2-dev
```

---

## 3. Compilación y Ejecución

Gracias al `Makefile` que he incluido, el proceso es muy sencillo.

### 3.1. Descargar las dependencias de LVGL
Este prototipo depende de la biblioteca gráfica LVGL. Clona su repositorio en el mismo directorio donde tienes la carpeta `src` de este proyecto:

```bash
git clone https://github.com/lvgl/lvgl.git
```

### 3.2. Configurar LVGL
1.  Copia la plantilla de configuración de LVGL:
    ```bash
    cp lvgl/lv_conf_template.h lvgl/lv_conf.h
    ```
2.  Abre `lvgl/lv_conf.h` con un editor de texto.
3.  **Activa el archivo:** Cambia la primera línea de `#if 0` a `#if 1`.
4.  **Activa SDL:** Busca la línea `#define LV_USE_SDL 0` y cámbiala a `#define LV_USE_SDL 1`.

### 3.3. Compilar el Prototipo
Abre una terminal en el directorio raíz del proyecto (donde se encuentra el `Makefile`) y simplemente ejecuta:
```bash
make
```
Esto compilará todo el código y creará un archivo ejecutable llamado `play_os_prototype`.

### 3.4. Ejecutar el Prototipo
Para ejecutar la interfaz de Play OS en tu PC, corre el siguiente comando:
```bash
./play_os_prototype
```
Deberías ver una ventana con la interfaz de Play OS, donde podrás navegar por la lista de juegos y entrar a la tienda.

---

## 4. Pasos Futuros (Para Desarrolladores)

Este prototipo puede ser la base para un firmware real. Un desarrollador experimentado que desee portar esto al Game Stick necesitaría:
1.  Establecer un entorno de compilación cruzada para el procesador ARM del dispositivo.
2.  Adaptar el backend de LVGL para que en lugar de SDL2, utilice el `framebuffer` (`/dev/fb0`) y el `evdev` (`/dev/input/eventX`) del Game Stick.
3.  Implementar la lógica para lanzar los emuladores reales del sistema.
4.  Implementar la funcionalidad de descarga y extracción de archivos para la tienda.

Espero que este prototipo te sea de gran utilidad. ¡Ha sido un placer trabajar en este fascinante proyecto contigo!