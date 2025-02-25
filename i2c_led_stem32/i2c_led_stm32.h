#pragma once

#include "esphome.h"
#include "esphome/components/output/float_output.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace i2c_led_stm32 {

class I2CLedSTM32Output : public output::FloatOutput, public Component, public i2c::I2CDevice {
 public:
  I2CLedSTM32Output(uint8_t channel, uint16_t resolution);
  void setup() override;
  void dump_config() override;
  void write_state(float state) override;

 protected:
  uint8_t channel_;
  uint16_t resolution_;
};

}  // namespace i2c_led_stm32
}  // namespace esphome
