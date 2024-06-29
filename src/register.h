#pragma once

#include <cstdint>
#include <iostream>

const uint16_t START_ADRESS = 0x0100;

struct Registers
{
public:

	uint16_t pc{ START_ADRESS };
	uint16_t sp{};
    union {
        struct {
            uint8_t f;   // Flags register
            uint8_t a;   // Accumulator register
        };
        uint16_t af;     // Combined AF register (f + a)
    };

    union {
        struct {
            uint8_t c;   // Counter register
            uint8_t b;   // B register
        };
        uint16_t bc;     // Combined BC register (c + b)
    };

    union {
        struct {
            uint8_t e;   // E register
            uint8_t d;   // D register
        };
        uint16_t de;     // Combined DE register (e + d)
    };

    union {
        struct {
            uint8_t l;   // L register
            uint8_t h;   // H register
        };
        uint16_t hl;     // Combined HL register (l + h)
    };
};