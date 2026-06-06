#include "achievement.h"
#include "fat32.h"

void cp_unlock_achievement(uint32_t id)
{
    // 1. Guardar estado del logro en la SD
    // fat32_write(...)

    // 2. Notificación en pantalla (OSD)
    // osd_show_notification("¡Logro Desbloqueado!");
}
