

#ifndef I2C
#define I2C

#if (__GNUC__ * 100 + __GNUC_MINOR__) < 304
#error "This library requires AVR-GCC 3.4 or later, update to newer AVR-GCC compiler !"
#endif

#include <avr/io.h>

#define I2C_READ    1
#define I2C_WRITE   0

extern void i2c_init(void);
extern uint8_t i2c_start(uint8_t addr);
extern uint8_t i2c_write_byte(uint8_t data);
extern uint8_t i2c_read_ack(void);
extern uint8_t i2c_read_nack(void);
extern void i2c_stop(void);
void i2c_wait_for_complete(void);

//TODO
extern uint8_t i2c_read_bytes_to_buffer(uint8_t peripheral_address, uint8_t len, uint8_t *buff) 
void i2c_backoff_retry(void);

#endif