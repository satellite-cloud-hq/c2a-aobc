use c2a_sils_runtime as c2a_runtime;

extern crate c2a_gen1;

extern crate c2a_gpio_noop;
extern crate c2a_i2c_noop;
extern crate c2a_meisei_adc_noop;
extern crate c2a_pwm_noop;
extern crate c2a_spi_noop;
extern crate c2a_uart_kble;
extern crate c2a_wdt_noop;

fn main() {
    c2a_runtime::c2a_init();
    c2a_runtime::c2a_main();
}
