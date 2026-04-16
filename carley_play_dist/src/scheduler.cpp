#include "scheduler.h"
#include <string.h>

static thread_t threads[MAX_THREADS];
static int current_thread = 0;

int thread_create(void (*fn)(void), uint32_t stack_size)
{
    for(int i = 0; i < MAX_THREADS; i++) {
        if(!threads[i].active) {
            memset(&threads[i], 0, sizeof(thread_t));
            threads[i].pc = (uint32_t)fn;
            threads[i].active = 1;
            return i;
        }
    }
    return -1;
}

void schedule(void)
{
    // 1. Guardar contexto del hilo actual

    // 2. Buscar siguiente hilo activo
    int next = (current_thread + 1) % MAX_THREADS;
    while(!threads[next].active && next != current_thread) {
        next = (next + 1) % MAX_THREADS;
    }

    current_thread = next;

    // 3. Restaurar contexto del siguiente hilo
}
