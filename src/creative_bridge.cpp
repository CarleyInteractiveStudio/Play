#include "creative_bridge.h"

void creative_run(creative_engine_t * engine)
{
    if(engine->on_start) engine->on_start();

    while(1) {
        float dt = 0.016f; // 60 FPS
        if(engine->on_update) engine->on_update(dt);
        if(engine->on_render) engine->on_render();

        // Llamar a los servicios de Carley Play OS
        // sync_process();
    }
}
