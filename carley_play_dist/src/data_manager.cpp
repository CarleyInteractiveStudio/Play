#include "data_manager.h"

static int app_count = MAX_APPS;

void data_manager_load_data(void)
{
    // En Bare Metal con datos embebidos, no hay nada que cargar de disco.
}

const cp_app_t* data_manager_get_apps(int* count)
{
    *count = app_count;
    return embedded_apps;
}

int data_manager_get_used_storage(void)
{
    int total = 0;
    for(int i = 0; i < app_count; i++) {
        if(embedded_apps[i].installed) {
            total += embedded_apps[i].size_mb;
        }
    }
    return total;
}
