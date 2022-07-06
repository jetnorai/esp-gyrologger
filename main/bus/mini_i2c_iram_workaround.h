#include "hal/i2c_hal.h"
#include "soc/i2c_periph.h"
#include "soc/dport_reg.h"

static inline void mini_i2c_write_txfifo(i2c_hal_context_t* hal, uint8_t* ptr, uint8_t len) {
    // TODO: handle i2c 0/1
    uint32_t fifo_addr = 0x6001301c;
    for (int i = 0; i < len; i++) {
        WRITE_PERI_REG(fifo_addr, ptr[i]);
    }
}

static inline void mini_i2c_enable_hw() {
    DPORT_SET_PERI_REG_MASK(DPORT_PERIP_CLK_EN_REG, DPORT_I2C_EXT0_CLK_EN);
    DPORT_CLEAR_PERI_REG_MASK(DPORT_PERIP_RST_EN_REG, DPORT_I2C_EXT0_RST);
}

static inline void mini_i2c_disable_hw() {
    DPORT_CLEAR_PERI_REG_MASK(DPORT_PERIP_CLK_EN_REG, DPORT_I2C_EXT0_CLK_EN);
    DPORT_SET_PERI_REG_MASK(DPORT_PERIP_RST_EN_REG, DPORT_I2C_EXT0_RST);
}

void periph_module_enable(periph_module_t periph);
void periph_module_disable(periph_module_t periph);