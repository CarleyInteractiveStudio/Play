#include "gpu_mali.h"
#include "rk3128_regs.h"

// Dirección reservada para texturas y buffers de video
#define VRAM_START 0x08000000 // A partir de los 128MB
static uint32_t vram_ptr = VRAM_START;

void gpu_init(void)
{
    // 1. Habilitar reloj de la GPU Mali
    RK_REG(CRU_CLKGATE_CON(1)) &= ~(1 << 0);

    // 2. Power ON de la GPU (Implementación de registros de energía)
}

void* vram_alloc(uint32_t size)
{
    void* ptr = (void*)vram_ptr;
    vram_ptr += (size + 4095) & ~4095; // Alineación de página de 4KB
    return ptr;
}

void cp_gpu_load_shader(const char * vcode, const char * fcode)
{
    // Compilar código de sombreadores para el Mali-400
}

void cp_gpu_draw_mesh(cp_vertex_t * vertices, uint32_t count, cp_texture_t * tex)
{
    // Enviar comandos al procesador de geometría y fragmentos de la GPU
}
