#ifndef RK3128_REGS_H
#define RK3128_REGS_H

#include <stdint.h>

/**
 * @file rk3128_regs.h
 * @brief Definiciones de registros para el SoC Rockchip RK3128 (GB2).
 */

#define RK_REG(addr) (*(volatile uint32_t *)(addr))

// --- CRU (Clock & Reset Unit) ---
#define CRU_BASE          0x20000000
#define CRU_MODE_CON      (CRU_BASE + 0x0040)
#define CRU_CLKSEL_CON(i) (CRU_BASE + 0x0044 + ((i) * 4))
#define CRU_CLKGATE_CON(i) (CRU_BASE + 0x00d0 + ((i) * 4))
#define CRU_SOFTRST_CON(i) (CRU_BASE + 0x0110 + ((i) * 4))

// --- GRF (General Register Files) ---
#define GRF_BASE          0x20008000
#define GRF_GPIO0A_IOMUX  (GRF_BASE + 0x0000)
#define GRF_GPIO1A_IOMUX  (GRF_BASE + 0x000c)
#define GRF_SOC_CON0      (GRF_BASE + 0x0140)

// --- VOP (Video Output Processor) ---
#define VOP_BASE          0x10128000
#define VOP_REG(offset)   RK_REG(VOP_BASE + offset)
#define VOP_SYS_CTRL      0x0000
#define VOP_SYS_CTRL1     0x0004
#define VOP_DSP_CTRL0     0x0010
#define VOP_DSP_CTRL1     0x0014
#define VOP_WIN0_CTRL0    0x0030
#define VOP_WIN0_COLOR_KEY 0x003c
#define VOP_WIN0_YRGB_MST 0x005c
#define VOP_WIN0_ACT_INFO 0x0060
#define VOP_WIN0_DSP_INFO 0x0064
#define VOP_WIN0_DSP_ST   0x0068
#define VOP_DSP_HTOTAL_HSW 0x00a8
#define VOP_DSP_HACT_ST_END 0x00ac
#define VOP_DSP_VTOTAL_VSW 0x00b0
#define VOP_DSP_VACT_ST_END 0x00b4
#define VOP_REG_DONE_EN   0x01f0

// --- SDMMC ---
#define SDMMC_BASE        0x10214000
#define SDMMC_CTRL        (SDMMC_BASE + 0x0000)
#define SDMMC_PWREN       (SDMMC_BASE + 0x0004)
#define SDMMC_CLKDIV      (SDMMC_BASE + 0x0008)
#define SDMMC_CMD         (SDMMC_BASE + 0x002c)
#define SDMMC_CMDARG      (SDMMC_BASE + 0x0030)
#define SDMMC_RESP0       (SDMMC_BASE + 0x0034)
#define SDMMC_MINTSTS     (SDMMC_BASE + 0x0040)

// --- RTC (Real Time Clock) ---
#define RTC_BASE          0x2003c000
#define RTC_SET_TIME      (RTC_BASE + 0x0000)
#define RTC_READ_TIME     (RTC_BASE + 0x0004)
#define RTC_CTRL          (RTC_BASE + 0x0010)

// --- Mali-400 GPU ---
#define MALI_BASE         0x10090000
#define MALI_GPU_ID       (MALI_BASE + 0x0000)
#define MALI_L2_CACHE_BASE (MALI_BASE + 0x0010)

#endif // RK3128_REGS_H
