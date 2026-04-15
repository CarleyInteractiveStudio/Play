#include "data_manager.h"
#include "fat32.h"
#include "cJSON.h"
#include "kernel.h"
#include <string.h>

static cp_app_t dynamic_apps[MAX_APPS];
static int dynamic_app_count = 0;

void data_manager_load_data(void)
{
    fat_file_t file;
    if (fat32_open("catalog.json", &file) == 0) {
        // Reservar memoria para el contenido del JSON
        char* buffer = (char*)malloc(file.size + 1);
        if (buffer) {
            fat32_read(&file, 0, file.size, (uint8_t*)buffer);
            buffer[file.size] = '\0';

            cJSON* json = cJSON_Parse(buffer);
            if (json) {
                cJSON* games = cJSON_GetObjectItem(json, "games");
                int num_games = cJSON_GetArraySize(games);
                dynamic_app_count = (num_games > MAX_APPS) ? MAX_APPS : num_games;

                for (int i = 0; i < dynamic_app_count; i++) {
                    cJSON* game = cJSON_GetArrayItem(games, i);
                    dynamic_apps[i].name = strdup(cJSON_GetObjectItem(game, "name")->valuestring);
                    dynamic_apps[i].size_mb = cJSON_GetObjectItem(game, "size_mb")->valueint;
                    dynamic_apps[i].installed = true;
                }
                cJSON_Delete(json);
            }
            free(buffer);
        }
    } else {
        // Si no hay SD, usar datos embebidos de respaldo
        dynamic_app_count = MAX_APPS;
        memcpy(dynamic_apps, embedded_apps, sizeof(embedded_apps));
    }
}

const cp_app_t* data_manager_get_apps(int* count)
{
    *count = dynamic_app_count;
    return dynamic_apps;
}
