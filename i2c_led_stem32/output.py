import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import output, i2c
from esphome.const import CONF_ID, CONF_CHANNEL, CONF_RESOLUTION

CODEOWNERS = ["@yourgithub"]
DEPENDENCIES = ["i2c"]

i2c_led_stm32_ns = cg.esphome_ns.namespace("i2c_led_stm32")
I2CLedSTM32Output = i2c_led_stm32_ns.class_("I2CLedSTM32Output", cg.Component, output.FloatOutput)

CONF_I2C_LED_STM32_ID = "i2c_led_stm32_id"
CONF_I2C_ADDRESS = "i2c_address"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(I2CLedSTM32Output),
        cv.Required(CONF_CHANNEL): cv.int_range(min=0, max=15),
        cv.Optional(CONF_RESOLUTION, default=16): cv.int_range(min=8, max=16),
        cv.Optional(CONF_I2C_ADDRESS, default=0x40): cv.i2c_address,
    }
).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID], config[CONF_CHANNEL], config[CONF_RESOLUTION])
    await cg.register_component(var, config)
    await output.register_output(var, config)
    cg.add(var.set_i2c_address(config[CONF_I2C_ADDRESS]))
