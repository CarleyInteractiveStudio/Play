#ifndef CARLEY_SYNC_H
#define CARLEY_SYNC_H

#include <stdint.h>

/**
 * @file carley_sync.h
 * @brief Protocolo de sincronización inalámbrica entre PC y Carley Play.
 */

#define SYNC_CMD_HELLO      0x01
#define SYNC_CMD_SEND_GAME  0x02
#define SYNC_CMD_SHARE_NET  0x03
#define SYNC_CMD_PROGRESS   0x04

typedef struct {
    uint8_t command;
    uint32_t length;
    uint8_t data[1024];
} sync_packet_t;

/**
 * @brief Inicializa el enlace de sincronización.
 */
void sync_init(void);

/**
 * @brief Procesa la entrada de datos del PC.
 */
void sync_process(void);

#endif // CARLEY_SYNC_H
