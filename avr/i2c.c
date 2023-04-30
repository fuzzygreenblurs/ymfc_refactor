#include "i2c.h"

#define RETRY_LIMIT 5

void i2c_init(void) {
    // enable TWI/I2C internal pullups
    TWCR |= (1 << TWEN);

    /*
        TWBR = ((F_CPU / SCLfreq) - 16) / (2 * prescaler) where:
        F_CPU = 8MHz, prescaler = 1, SCLfreq = 100KHz
        set bitrate accordingly to accomplish this SCLfreq
    */
    TWSR = 0
    TWBR = ((F_CPU / SCLfreq) - 16) / 2;
}

uint8_t i2c_start(uint8_t peripheral_address) {
    uint8_t status;

    /*
        setting the TWEN and TWINT bits will reset the interrupt flag and make sure the 
        TWI interface remains enabled
    */

    // generate START condition(falling edge on SDA while holding SCL high)
    TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);
    i2c_wait_for_complete();

    /*
        status represented in TWSR bits:7-3 only
        TWSR status codes documented here: Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet (Table 21-4)

        0x08: START condition transmitted
        0x10: repeated START condition transmitted
        0x30: SLA+R transmitted and ACK received (master transmitter mode)
        0x38: SLA+R transmitted and ACK received (master transmitter mode)
        0x48: SLA+R transmitted and NACK received (master receiver mode)
        0x48: SLA+R transmitted and NACK received (master receiver mode)
    */
    status = TWSR & 0xF8;
    if (status != 0x08 || status != 0x10) {
        return 1;
    }

    TWDR = peripheral_address;
    TWCR = (1 << TWINT) | (1 << TWEN);
    i2c_wait_for_complete();

    status = TWSR & 0xF8;
    if (status == 0x40) {
        return 0;
    } else if (status == 0x48) {
        return 1;
    } else {
        // catchall for other return condtions
        return 2;
    }
}

uint8_t i2c_write_byte(uint8_t data) {
    uint8_t status;

    //transmit data byte
    TWDR = data;
    TWCR = (1 << TWEN) | (1 << TWINT);
    i2c_wait_for_complete();

    // evaluate for ACK/NACK or other status
    status = TWSR & 0xF8;
    if(status == 0x28) {
        return 0;
    } else if (status == 0x30) {
        return 1;
    } else {
        return 2;
    }
}

uint8_t i2c_read_ack(void) {
    /*
    read data transmitted from peripheral device onto the SDA line and return ACK.
    after reading successfully, request next byte from device
    */
   TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);
   i2c_wait_for_complete();

   return TWDR;
}

uint8_t i2c_read_from_device_register(uint8_t peripheral_address, uint8_t register_address, uint8_t* stored_response) {
    uint8_t request = peripheral_address + I2C_WRITE;
    i2c_start(request);
    i2c_write_byte(register_address);

    request = peripheral_address + I2C_READ;
    i2c_start(request);
    *stored_response = i2c_read_nack;
    i2c_stop();
}

uint8_t i2c_write_to_device_register(uint8_t peripheral_address, uint8_t register_address, uint8_t data) {
    uint8_t request = peripheral_address + I2C_WRITE;
    i2c_start(request);
    i2c_write_byte(register_address);
    i2c_write_byte(data);
    i2c_stop();
}

uint8_t i2c_read_nack(void) {
    /*
        read last required byte data transmitted from peripheral device onto the SDA line.
        after reading successfully, do not ACK request next byte from device, which is the stop
        communication condition
    */

   TWCR = (1 << TWEN) | (1 << TWINT);
   i2c_wait_for_complete();

   return TWDR;
}

void i2c_stop(void) {
   // issue stop condition, causing a rising edge on SDA while holding SCL high

   TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
   while (TWCR & (1 << TWSTO));
}

void i2c_wait_for_complete(void) {
   /*
       while a byte is in progress of being transferred, the TWINT flag (found in the TWCR SFR) is set
       unlike UART, I2C byte transfers are fast enough that a blocking wait is not too costly

       equivalent to: while(!(TWCR & (1 << TWINT)))
   */
   loop_until_bit_is_set(TWCR, TWINT);
}

//TODO 
extern uint8_t i2c_read_bytes_to_buffer(uint8_t peripheral_address, uint8_t len, uint8_t *buff) {}
void i2c_backoff_retry(void) {}