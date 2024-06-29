#include "cpu.h"

Cpu::Cpu()
	:opcode(0), cb_opcode(0), pc(0x0100), sp(0xFFFE), mCycle(0)
{
}

void Cpu::fetchOpcode()
{
	opcode = mem_read(r.pc);
	r.pc += 1;
	if (opcode == 0xCB) 
	{
		prefixFlag = true;
		cb_opcode = mem_read(r.pc);
		r.pc += 1;
	}
}

void Cpu::decodeOpcode(uint8_t opcode, uint8_t cb_opcode, bool prefixFlag)
{
	if (prefixFlag == true)
		opcode = cb_opcode;

	uint8_t x{ 0 }; uint8_t y{ 0 }; uint8_t z{ 0 }; uint8_t p{ 0 }; uint8_t q{ 0 };
	//
	x = opcode >> 6;
	y = (opcode & 0b00111000) >> 3;
	z = (opcode & 0b00000111);
	p = y >> 1;
	q = y & 0b00000001;
	if (prefixFlag == true)
		executeCBOpcode(x, y, z, p, q);
	if (prefixFlag == false)
		executeOpcode(x, y, z, p, q);
}

void Cpu::executeOpcode(uint8_t x, uint8_t y, uint8_t z, uint8_t p, uint8_t q)
{
	switch (x)
	{
		case 0:
			switch (z)
			{
				case 0:
					if (y == 0)
						//NOP
					if (y == 1)
						//LD (nn), SP
					if (y == 2)
						//STOP
					if (y == 3)
						//JR d
					if (y >= 4 && y <= 7)
						//JR cc[y-4], d
					break;
				case 1:
					switch (q)
					{
						case 0:
							//LD rp[p], nn	
							break;
						case 1:
							//ADD HL, rp[p]
							break;
					}
					break;
				case 2:
					switch (q)
					{
						case 0:
							switch (p)
							{
								case 0:
									//LD (BC), A
									break;
								case 1:
									//LD (DE), A
									break;
								case 2:
									//LD (HL+), A
									break;
								case 3:
									//LD (HL-), A
									break;
							}
							break;
						case 1:
							switch (p)
							{
								case 0:
									//LD A, (BC)	
									break;
								case 1:
									//LD A, (HL+)
									break;
								case 2:
									//LD A, (DE)
									break;
								case 3:
									//LD A, (HL-)
									break;
							}
							break;
					}
					break;
				case 3:
					switch (q)
					{
						case 0:
							//INC rp[p]	
							break;
						case 1:
							//DEC rp[p]
							break;
					}
					break;
				case 4:
					// NC r[y]
					break;
				case 5:
					//DEC r[y]
					break;
				case 6:
					//LD r[y], n
					break;
				case 7:
					switch (y)
					{
						case 0:
							//RLCA
							break;
						case 1:
							//RRCA
							break;
						case 2:
							//RLA
							break;
						case 3:
							//RRA
							break;
						case 4:
							//DAA
							break;
						case 5:
							//CPL
							break;
						case 6:
							//SCF
							break;
						case 7:
							//CCF
							break;
					}
					break;
			}
			break;
		case 1:
			if (z == 6 && y == 6)
			{
			}//HALT
			else {}
				//LD r[y], r[z]
			break;
		case 2:
			// alu[y] r[z]
			break;
		case 3:
			switch (z)
			{
				case 0:
					if (0 >= 0 && y <= 3)
						//RET cc[y]
					if (y == 4)
						//LD (0xFF00 + n), A
					if (y == 5)
						//ADD SP, d
					if (y == 6)
						//LD A, (0xFF00 + n)
					if (y == 7)
						//LD HL, SP+ d
					break;
				case 1:
					switch (q)
					{
						case 0:
							//POP rp2[p]
							break;
						case 1:
							switch (p)
							{
							case 0:
								//RET
								break;
							case 1:
								//RETI
								break;
							case 2:
								//JP HL
								break;
							case 3:
								//LD SP, HL
								break;
							}
							break;
					}
					break;
				case 2:
					if (0 >= 0 && y <= 3)
						//JP cc[y], nn
					if (y == 4)
						//LD (0xFF00+C), A
					if (y == 5)
						//LD (nn), A
					if (y == 6)
						//LD A, (0xFF00+C)
					if (y == 7)
						//LD A, (nn)
					break;
				case 3:
					if (y == 0)
						//JP nn
					if (y == 1)
						//(CB prefix)
					if (y == 6)
						//DI
					if (y == 7)
						//EI
					break;
				case 4:
					if (0 >= 0 && y <= 3)
						//CALL cc[y], nn
					break;
				case 5:
					switch (q)
					{
					case 0:
						//PUSH rp2[p]
						break;
					case 1:
						if (p == 0)
							// CALL nn
						break;
					}
					break;
				case 6:
					//alu[y] n
					break;
				case 7:
					//RST y * 8
					break;
			}
			break;

	}
	}
		

// 0xCB Prefixed

void Cpu::executeCBOpcode(uint8_t x, uint8_t y, uint8_t z, uint8_t p, uint8_t q)
{
	switch (x)
	{
		case 1:
			//rot[y] r[z]
			break;
		case 2:
			//BIT y, r[z]
			break;
		case 3:
			//RES y, r[z]
			break;
		case 4:
			//SET y, r[z]
			break;
	}
}


uint8_t Cpu::mem_read(const uint16_t adr) const
{
	return memory[adr & 0xFFFF];
}

void Cpu::mem_write(const uint16_t adr, uint8_t value)
{
	memory[adr & 0xFFFF] = value;
}


void Cpu::setZeroF(uint32_t res)
{
	r.f &= ~0x80;
	if (res == 0)
		this->r.f |= 0x80;
}

void Cpu::setSubsF(bool subs)
{
	r.f &= ~0x40;
	if (subs)
		this->r.f |= 0x40;
}

void Cpu::setHCarryF8(uint8_t x, uint8_t y)
{
	r.f &= ~0x20;
	if (isHalfCarry8(x, y))
		this->r.f |= 0x20;
}

void Cpu::setHCarryF16(uint16_t x, uint16_t y)
{
	r.f &= ~0x20;
	if (isHalfCarry16(x, y))
		this->r.f |= 0x20;
}

void Cpu::setCarryF8(uint16_t res)
{
	r.f &= ~0x10;
	if (is8bCarry(res))
		this->r.f |= 0x10; 
}

void Cpu::setCarryF16(uint16_t res)
{
	r.f &= ~0x10;
	if (is16bCarry(res))
		this->r.f |= 0x10;
}

void Cpu::setCarryFBorrow()
{
}

void Cpu::setCarryFShift()
{
}


bool Cpu::is8bCarry(uint16_t res)
{
	return (res > 0xFF);
}

bool Cpu::is16bCarry(uint32_t res)
{
	return (res > 0xFFFF);;
}

bool Cpu::isHalfCarry8(uint8_t x, uint8_t y)
{
	return ((x < 0xF) && (y < 0xF) && ((x + y) > 0xF) );
}

bool Cpu::isHalfCarry16(uint16_t x, uint16_t y)
{
	return ((x < 0xFFF) && (y < 0xFFF) && ((x + y) > 0xFFF));;
}

void Cpu::ADC_A_r8(uint8_t& r8)
{
	mCycle += 1;

	uint8_t fCarry = static_cast<uint8_t>((r.f & 0x10) == 0x10);
	uint16_t res = r.a + r8 + fCarry;
	setZeroF(res);
	setSubsF(false); 
	setHCarryF8(r.a, (r8 + fCarry));
	setCarryF8(res);
	r.a = res & 0xFF;
}

void Cpu::ADC_A_HL()
{
	mCycle += 2;

	uint8_t data = mem_read(r.hl);
	uint8_t fCarry = static_cast<uint8_t>((r.f & 0x10) == 0x10);
	uint32_t res = r.a + data + fCarry;
	setZeroF(res);
	setSubsF(false);
	setHCarryF8(r.a, (data + fCarry));
	setCarryF8(res);
	r.a = res & 0xFF;
}

void Cpu::ADC_A_n8(uint8_t n8)
{
	mCycle += 2;

	uint8_t fCarry = static_cast<uint8_t>((r.f & 0x10) == 0x10);
	uint16_t res = r.a + n8 + fCarry; 
	setSubsF(false);
	setHCarryF8(r.a, (n8 + fCarry));
	setCarryF8(res);
	r.a = res & 0xFF;
}