#include "register.h"

void Registers::setZeroF(uint32_t res)
{
	f &= ~0x80;
	if (res == 0)
		this->f |= 0x80;
}

void Registers::setSubsF(bool subs)
{
	f &= ~0x40;
	if (subs)
		this->f |= 0x40;
}

void Registers::setHCarryF(uint32_t res)
{
	f &= ~0x20;
	if (isHalfCarry(res))
		this->f |= 0x20;
}

void Registers::setCarryF(uint32_t res, bool bFlag, bool borrow, bool shiftOut)
{
	f &= ~0x10;
	if (is8bCarry(res, bFlag) || is16bCarry(res, bFlag) || borrow || shiftOut)
		this->f |= 0x10; // Set the Carry flag bit if any condition is true
}

bool Registers::is8bCarry(uint32_t res, bool bFlag)
{
	return (!bFlag && res > 0xFF);
}

bool Registers::is16bCarry(uint32_t res, bool bFlag)
{
	return (bFlag && res > 0xFFFF);;
}

bool Registers::isHalfCarry(uint32_t res)
{
		return ((res & 0x0FFF) > 0x0FFF);
}
