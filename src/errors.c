#include <avr/io.h>
#include <util/delay.h>

#include "errors.h"

void errors_init() {
    DDRD |= _BV(DDD7); // Set PD7 pin as output
}

void errors_blink_ram() {
    int blink_state = 0;
    while(1) {
        if (blink_state) {
            PORTD |= _BV(PORTD7);
        } else {
            PORTD &= ~_BV(PORTD7);
        }
        blink_state=!blink_state;
        _delay_ms(50);
    }
}

void errors_blink_parse() {
    int blink_state = 0;
    while(1) {
        if (blink_state) {
            PORTD |= _BV(PORTD7);
        } else {
            PORTD &= ~_BV(PORTD7);
        }
        blink_state=!blink_state;
        _delay_ms(500);
    }
}

void errors_blink_exception() {
    int blink_state = 0;
    while(1) {
        if (blink_state) {
            PORTD |= _BV(PORTD7);
        } else {
            PORTD &= ~_BV(PORTD7);
        }
        blink_state=!blink_state;
        _delay_ms(1000);
    }
}