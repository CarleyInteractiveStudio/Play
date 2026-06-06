#include "config_manager.h"
#include "fat32.h"
#include <string.h>

static cp_config_t current_config = {70, 0, 100}; // Valores por defecto

void config_load(void)
{
    fat_file_t file;
    if(fat32_open("system.cfg", &file) == 0) {
        fat32_read(&file, 0, sizeof(cp_config_t), (uint8_t*)&current_config);
    }
}

void config_save(void)
{
    fat_file_t file;
    if(fat32_open("system.cfg", &file) != 0) {
        fat32_create("system.cfg");
    }
    fat32_write(&file, 0, sizeof(cp_config_t), (uint8_t*)&current_config);
}

cp_config_t* config_get(void)
{
    return &current_config;
}
