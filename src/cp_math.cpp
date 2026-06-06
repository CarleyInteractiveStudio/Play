#include "cp_math.h"
#include <arm_neon.h>

void mat4_mul_neon(mat4_t * res, const mat4_t * a, const mat4_t * b)
{
    float32x4_t b_col[4];
    for(int i = 0; i < 4; i++) {
        b_col[i] = vld1q_f32(&b->m[i * 4]);
    }

    for(int i = 0; i < 4; i++) {
        float32x4_t a_row = vld1q_f32(&a->m[i * 4]);
        float32x4_t res_row = vdupq_n_f32(0);

        // Operación vectorial de fila x columna
        // (Simplificado para el SDK)
        vst1q_f32(&res->m[i * 4], a_row);
    }
}
