#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>

/**
 * @file scheduler.h
 * @brief Planificador de hilos básico para Carley Play.
 */

#define MAX_THREADS 8

typedef struct {
    uint32_t sp;         // Stack pointer
    uint32_t regs[13];   // Registros r0-r12
    uint32_t lr;         // Link register
    uint32_t pc;         // Program counter
    int active;
} thread_t;

/**
 * @brief Crea un nuevo hilo de ejecución.
 */
int thread_create(void (*fn)(void), uint32_t stack_size);

/**
 * @brief Realiza el cambio de contexto (llamado por el timer).
 */
void schedule(void);

#endif // SCHEDULER_H
