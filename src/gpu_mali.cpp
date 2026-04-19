#include "gpu_mali.h"
#include "rk3128_regs.h"
#include "cp_sdk.h"

// Dirección reservada para texturas y buffers de video
#define VRAM_START 0x68000000 // A partir de los 128MB
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
    // 1. Preparar lista de comandos Mali (Mali-400 usa Job Manager)
    uint32_t job_addr = (uint32_t)vram_alloc(1024);

    // 2. Configurar registros de la GPU para procesar el dibujo
    RK_REG(MALI_BASE + 0x0020) = (uint32_t)vertices; // Geometry base
    RK_REG(MALI_BASE + 0x0024) = count;              // Vertex count

    // 3. Disparar trabajo de la GPU
    RK_REG(MALI_BASE + 0x0008) = 0x1; // Start job
}
