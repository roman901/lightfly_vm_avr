#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>

#include "errors.h"
#include "lf_executor.h"
#include "lf_loader.h"
#include "opcodes.h"

#define HEADER_LENGHT 3


int main()
{
    // Init AVR-related things
    errors_init();

    //Set PD4 and PD5 to output
    DDRD |= _BV(DDD5);
    DDRD |= _BV(DDD4);

    // Program definition
    unsigned char raw_program[] PROGMEM = {0x55, 0x57, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFA, 0xFF};
    size_t length = 10;

    if (!lf_loader_check_header(raw_program)) {
        errors_blink_parse();
    }

    if (!lf_loader_check_version(raw_program)) {
        errors_blink_parse();
    }

    lf_context *context = malloc(sizeof(lf_context));
    if (context == 0) {
        errors_blink_ram();
    }
    unsigned char *program = malloc(length - HEADER_LENGHT);
    if (program == 0) {
        errors_blink_ram();
    }
    if (!memcpy(program, raw_program + HEADER_LENGHT, length - HEADER_LENGHT)) { // Copy program code without header
        errors_blink_ram();
    }

    // If all checks successful - turn on "state" led
    PORTD |= _BV(PORTD7);


    lf_runner_opcodes_init();
    lf_executor_init(context, length - HEADER_LENGHT, program);

    // Stage 6: start executing program
    int status = LF_STATE_SUCCESS;
    while (status == LF_STATE_SUCCESS) {
        status = lf_executor_do_step(context);
        _delay_ms(500);
        PORTD |= _BV(PORTD5);
        _delay_ms(500);
        PORTD &= ~_BV(PORTD5);
    }

    if (status == LF_STATE_EXCEPTION) {
        errors_blink_exception();
    } else if (status == LF_STATE_HALT) {
        PORTD |= _BV(PORTD5);
    }

    while(1);
}