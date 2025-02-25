#include "i2c_led_stm32.h"
#include "esphome/core/log.h"

namespace esphome {
namespace i2c_led_stm32 {

static const char *TAG = "i2c_led_stm32";

I2CLedSTM32Output::I2CLedSTM32Output(uint8_t channel, uint16_t resolution) 
    : channel_(channel), resolution_(resolution) {}

void I2CLedSTM32Output::setup() {
    ESP_LOGCONFIG(TAG, "Setting up I2C LED STM32 Output (Channel %d, Resolution %d-bit)", channel_, resolution_);
}

void I2CLedSTM32Output::dump_config() {
    ESP_LOGCONFIG(TAG, "I2C LED STM32 Output:");
    ESP_LOGCONFIG(TAG, "  Channel: %d", channel_);
    ESP_LOGCONFIG(TAG, "  Resolution: %d-bit", resolution_);
    ESP_LOGCONFIG(TAG, "  I2C Address: 0x%02X", this->address_);
}

void I2CLedSTM32Output::write_state(float state) {
    uint16_t pwm_value = static_cast<uint16_t>(state * ((1 << resolution_) - 1));
    uint8_t data[3] = { static_cast<uint8_t>(channel_), static_cast<uint8_t>(pwm_value & 0xFF), static_cast<uint8_t>((pwm_value >> 8) & 0xFF) };

    if (!this->write(data, 3)) {
        ESP_LOGE(TAG, "Failed to send PWM command to STM32 at 0x%02X", this->address_);
    } else {
        ESP_LOGD(TAG, "Set PWM Channel %d to %d", channel_, pwm_value);
    }
}

}  // namespace i2c_led_stm32
}  // namespace esphome
