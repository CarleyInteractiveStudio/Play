#ifndef ACHIEVEMENT_H
#define ACHIEVEMENT_H

#include <stdint.h>

/**
 * @file achievement.h
 * @brief Sistema de trofeos y logros para Carley Play.
 */

typedef struct {
    uint32_t id;
    char name[64];
    bool unlocked;
} cp_achievement_t;

/**
 * @brief Desbloquea un logro para el usuario actual.
 */
void cp_unlock_achievement(uint32_t id);

#endif // ACHIEVEMENT_H
