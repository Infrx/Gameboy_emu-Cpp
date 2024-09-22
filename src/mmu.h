//
// Created by mertcan on 9/16/24.
//

#ifndef MMU_H
#define MMU_H
#include <array>
#include <cstdint>
#include <functional>
#include "cpu.h"

constexpr int ROM_BANK_SIZE = 0x4000;
constexpr int VRAM_SIZE = 0x2000;
constexpr int ERAM_SIZE = 0x2000;
constexpr int WRAM_SIZE = 0x2000;
constexpr int OAM_SIZE = 0x9F;
constexpr int HRAM_SIZE = 0x7F;
constexpr int MEMORY = 0xFFFF;



class MMU
{
public:
    std::array<uint8_t, VRAM_SIZE> vram{};
    std::array<uint8_t, ERAM_SIZE> eram{};
    std::array<uint8_t, WRAM_SIZE> wram{};
    std::array<uint8_t, OAM_SIZE> oam{};
    std::array<uint8_t, HRAM_SIZE> hram{};
    std::array<uint8_t, MEMORY> memory{};
public:
    explicit MMU(const std::function<void()>& incrementMCycle);
    [[nodiscard]] uint8_t read(const uint16_t& adr) const;
    void write(const uint16_t& adr, const uint8_t& value);
private:
    std::function<void()> incrementMCycle;
};



#endif //MMU_H
