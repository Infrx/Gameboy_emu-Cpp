#pragma once

#include <cstdint>
#include <iostream>

class Registers
{
public:

	uint16_t pc{};
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

    void setZeroF(uint16_t res);
    void setSubsF(uint16_t res); // bFlag is false for 8 bit true for 16 bit
    void setHCarryF(uint16_t res);
    void setCarryF(uint64_t res, bool bFlags, bool borrow, bool shiftOut);

    //helpers

    bool isHalfCarry(uint32_t res, bool bFlag);
    bool isCarry(uint64_t res, bool bFlag);
};