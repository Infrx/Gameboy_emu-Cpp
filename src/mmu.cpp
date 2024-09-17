//
// Created by mertcan on 9/16/24.
//

#include "mmu.h"

MMU::MMU(const std::function<void()>& incrementMCycle)
    : incrementMCycle(incrementMCycle)
{
}

uint8_t MMU::read(const uint16_t& adr) const
{
    incrementMCycle();
    return 0;
}

void MMU::write(const uint16_t& adr, const uint8_t& value)
{
}
