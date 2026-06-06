#include "user_manager.h"
#include <string.h>

static cp_user_t current_user = {"Jugador 1", 0, 0};

void users_init(void)
{
    // Cargar perfil desde la SD si existe
}

cp_user_t* users_get_current(void)
{
    return &current_user;
}
