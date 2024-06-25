#include "register.h"

void Registers::setZeroF(uint16_t res)
{
	f &= ~0x80;
	if (res == 0)
		this->f |= 0x80;
}

void Registers::setSubsF(uint16_t res)
{
	f &= ~0x40;
}

void Registers::setHCarryF(uint16_t res)
{
	f &= ~0x20;
}

void Registers::setCarryF(uint64_t res, bool bFlag, bool borrow, bool shiftOut)
{
	f &= ~0x10;
	if (isHalfCarry(res, bFlag) || isCarry(res, bFlag) || borrow || shiftOut)
		f |= 0x10; // Set the Carry flag bit if any condition is true
}

bool Registers::isHalfCarry(uint32_t res, bool bFlag)
{
	return (bFlag && res > 0xFFFF);
}

bool Registers::isCarry(uint64_t res, bool bFlag)
{
	return (!bFlag && res > 0xFF);;
}
