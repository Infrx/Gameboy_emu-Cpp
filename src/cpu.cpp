#include "cpu.h"

Cpu::Cpu()
	:opcode(0), cb_opcode(0), pc(0x0100), sp(0xFFFE), mCycle(0)
{
}

void Cpu::fetchOpcode()
{
	opcode = mem_read(pc);
	pc += 1;
	if (opcode == 0xCB) 
	{
		prefixFlag = true;
		cb_opcode = mem_read(pc);
		pc += 1;
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

void Cpu::setHCarryF8(uint16_t x, uint16_t y)
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

void Cpu::setHCarryF8(bool flag)
{
	r.f &= ~0x20;
	if (flag)
		this->r.f |= 0x20;
}

void Cpu::setHCarryF16(bool flag)
{
	r.f &= ~0x20;
	if (flag)
		this->r.f |= 0x20;
}

void Cpu::setCarryF8(uint16_t res)
{
	r.f &= ~0x10;
	if (is8bCarry(res))
		this->r.f |= 0x10; 
}

void Cpu::setCarryF8(uint32_t res)
{
	r.f &= ~0x10;
	if (is8bCarry(res))
		this->r.f |= 0x10;
}

void Cpu::setCarryF8(bool flag)
{
	r.f &= ~0x10;
	if (flag)
		this->r.f |= 0x10;
}

void Cpu::setCarryF16(uint16_t res)
{
	r.f &= ~0x10;
	if (is16bCarry(res))
		this->r.f |= 0x10;
}

void Cpu::setCarryFBorrow(uint16_t x, uint16_t y)
{
	r.f &= ~0x10;
	if (isBorrow8(x,y))
		this->r.f |= 0x10;
}

void Cpu::setHCarryFBorrow(uint16_t x, uint16_t y)
{
	r.f &= ~0x10;
	if (isBorrow4(x, y))
		this->r.f |= 0x10;
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

bool Cpu::isHalfCarry8(uint16_t x, uint16_t y)
{
	return ((x < 0xF) && (y < 0xF) && ((x + y) > 0xF) );
}

bool Cpu::isHalfCarry16(uint16_t x, uint16_t y)
{
	return ((x < 0xFFF) && (y < 0xFFF) && ((x + y) > 0xFFF));;
}

bool Cpu::isBorrow8(uint16_t x, uint16_t y)
{
	return (x < y);  // y is r8 or r8 + carry
}

bool Cpu::isBorrow4(uint16_t x, uint16_t y)
{
	return ((x > 0xF && ((x - y) < 0xF)));
}

void Cpu::ADC_A_r8(uint8_t& r8)
{
	mCycle += 1;

	uint8_t fCarry = static_cast<uint8_t>((r.f & 0x10) == 0x10);
	uint32_t res = r.a + r8 + fCarry;
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
	uint32_t res = r.a + n8 + fCarry; 
	setSubsF(false);
	setHCarryF8(r.a, (n8 + fCarry));
	setCarryF8(res);
	r.a = res & 0xFF;
}

void Cpu::ADD_A_r8(uint8_t& r8)
{
	mCycle += 1;

	uint16_t res = r.a + r8;
	setZeroF(res);
	setSubsF(false);
	setHCarryF8(r.a, r8);
	setCarryF8(res);
	r.a = res & 0xFF;
}

void Cpu::ADD_A_HL()
{
	mCycle += 2;

	uint8_t data = mem_read(r.hl);
	uint16_t res = r.a + data;
	setZeroF(res);
	setSubsF(false);
	setHCarryF8(r.a, data );
	setCarryF8(res);
	r.a = res & 0xFF;
}

void Cpu::ADD_A_n8(uint8_t n8)
{
	mCycle += 2;

	uint16_t res = r.a + n8;
	setZeroF(res);
	setSubsF(false);
	setHCarryF8(r.a, n8);
	setCarryF8(res);
	r.a = res & 0xFF;
}

void Cpu::AND_A_r8(uint8_t& r8)
{
	mCycle += 1;

	uint16_t res = r.a & r8;
	setZeroF(res);
	setSubsF(false);
	setHCarryF8(true);
	setCarryF8(res);
	r.a = res;
}

void Cpu::AND_A_HL()
{
	mCycle += 2;

	uint8_t data = mem_read(r.hl);
	uint16_t res = r.a & data;
	setZeroF(res);
	setSubsF(false);
	setHCarryF8(true);
	setCarryF8(res);
	r.a = res;
}

void Cpu::AND_A_n8(uint8_t n8)
{
	mCycle += 2;

	uint16_t res = r.a & n8;
	setZeroF(res);
	setSubsF(false);
	setHCarryF8(true);
	setCarryF8(res);
	r.a = res;
}

void Cpu::CP_A_r8(uint8_t& r8)
{
	mCycle += 1;

	uint16_t res = r.a - r8;
	setZeroF(res);
	setSubsF(true);
	setHCarryFBorrow(r.a, r8);
	setCarryFBorrow(r.a, r8);
	// dont store the result
}

void Cpu::CP_A_HL()
{
	mCycle += 2;

	uint8_t data = mem_read(r.hl);
	uint16_t res = r.a - data;
	setZeroF(res);
	setSubsF(true);
	setHCarryFBorrow(r.a, data);
	setCarryFBorrow(r.a, data);
}

void Cpu::CP_A_n8(uint8_t n8)
{
	mCycle += 2;

	uint16_t res = r.a - n8;
	setZeroF(res);
	setSubsF(true);
	setHCarryFBorrow(r.a, n8);
	setCarryFBorrow(r.a, n8);
}

void Cpu::DEC_r8(uint8_t& r8)
{
	mCycle += 1;

	uint16_t res = r8 - 1;
	setZeroF(res);
	setSubsF(true);
	setHCarryFBorrow(r8, 1);
	r8 = res;
}

void Cpu::DEC_HL()
{
	mCycle += 3;
	
	uint8_t data = mem_read(r.hl);
	uint16_t res = data - 1;
	setZeroF(res);
	setSubsF(true);
	setHCarryFBorrow(data, 1);
	mem_write(r.hl, res);
}

void Cpu::INC_r8(uint8_t& r8)
{
	mCycle += 1;

	uint16_t res = r8 + 1;
	setZeroF(res);
	setSubsF(false);
	setHCarryF8(r8, 1);
	r8 = res & 0xFF;
}

void Cpu::INC_HL()
{
	mCycle += 3;

	uint8_t data = mem_read(r.hl);
	uint16_t res = data + 1;
	setZeroF(res);
	setSubsF(false);
	setHCarryF8(data, 1);
	mem_write(r.hl, res);
}

void Cpu::OR_A_r8(uint8_t& r8)
{
	mCycle += 1;

	uint16_t res = r.a | r8;
	setZeroF(res);
	setSubsF(false);
	setHCarryF8(false);
	setCarryF8(false);
	r.a = res;
}

void Cpu::OR_A_HL()
{
	mCycle += 2;
	uint8_t data = mem_read(r.hl);
	uint16_t res = r.a | data;
	setZeroF(res);
	setSubsF(false);
	setHCarryF8(false);
	setCarryF8(false);
	r.a = res;
}

void Cpu::OR_A_n8(uint8_t n8)
{
	mCycle += 2;

	uint16_t res = r.a | n8;
	setZeroF(res);
	setSubsF(false);
	setHCarryF8(false);
	setCarryF8(false);
	r.a = res;
}

void Cpu::SBC_A_r8(uint8_t& r8)
{
	mCycle += 1;

	uint8_t fCarry = static_cast<uint8_t>((r.f & 0x10) == 0x10);
	uint32_t res = r.a - (r8 + fCarry);
	setSubsF(true);
	setHCarryFBorrow(r.a, (r8 + fCarry));
	setCarryFBorrow(r.a, (r8 + fCarry));
	r.a = res & 0xFF;
}

void Cpu::SBC_A_HL()
{
	mCycle += 2;
	uint8_t data = mem_read(r.hl);
	uint8_t fCarry = static_cast<uint8_t>((r.f & 0x10) == 0x10);
	uint32_t res = r.a - (data + fCarry);
	setSubsF(true);
	setHCarryFBorrow(r.a, (data + fCarry));
	setCarryFBorrow(r.a, (data + fCarry));
	r.a = res & 0xFF;
}

void Cpu::SBC_A_n8(uint8_t n8)
{
	mCycle += 2;

	uint8_t fCarry = static_cast<uint8_t>((r.f & 0x10) == 0x10);
	uint32_t res = r.a - (n8 + fCarry);
	setSubsF(true);
	setHCarryFBorrow(r.a, (n8 + fCarry));
	setCarryFBorrow(r.a, (n8 + fCarry));
	r.a = res & 0xFF;
}

void Cpu::SUB_A_r8(uint8_t& r8)
{
	mCycle += 1;

	uint32_t res = r.a - r8;
	setSubsF(true);
	setHCarryFBorrow(r.a, r8);
	setCarryFBorrow(r.a, r8);
	r.a = res & 0xFF;
}

void Cpu::SUB_A_HL()
{
	mCycle += 1;
	uint8_t data = mem_read(r.hl);
	uint32_t res = r.a - data;
	setSubsF(true);
	setHCarryFBorrow(r.a, data);
	setCarryFBorrow(r.a, data);
	r.a = res & 0xFF;
}

void Cpu::SUB_A_n8(uint8_t n8)
{
	mCycle += 2;

	uint32_t res = r.a - n8;
	setSubsF(true);
	setHCarryFBorrow(r.a, n8);
	setCarryFBorrow(r.a, n8);
	r.a = res & 0xFF;
}

void Cpu::XOR_A_r8(uint8_t& r8)
{
	mCycle += 1;

	uint16_t res = r.a ^ r8;
	setZeroF(res);
	setSubsF(false);
	setHCarryF8(false);
	setCarryF8(false);
	r.a = res;
}

void Cpu::XOR_A_HL()
{
	mCycle += 2;
	
	uint8_t data = mem_read(r.hl);
	uint16_t res = r.a ^ data;
	setZeroF(res);
	setSubsF(false);
	setHCarryF8(false);
	setCarryF8(false);
	r.a = res;
}

void Cpu::XOR_A_n8(uint8_t n8)
{
	mCycle += 2;

	uint16_t res = r.a ^ n8;
	setZeroF(res);
	setSubsF(false);
	setHCarryF8(false);
	setCarryF8(false);
	r.a = res;
}

void Cpu::ADD_HL_r16(uint16_t r16)
{
	mCycle += 2;

	uint32_t res = r.hl + r16;
	setSubsF(false);
	setHCarryF16(r.hl + r16);
	setCarryF16(r.hl + r16);
	r.hl = res & 0xFFFF;
}

void Cpu::DEC_r16(uint16_t r16)
{
	mCycle += 2;

	r16 -= 1;
}

void Cpu::INC_r16(uint16_t r16)
{
	mCycle += 2;

	r16 += 1;
}

void Cpu::BIT_u3_r8(uint8_t& r8, uint8_t u3)
{
	mCycle += 2;

	uint16_t res = (r8 & (1 << u3)) != 0;
	setZeroF(res);
	setSubsF(false);
	setHCarryF8(false);
}

void Cpu::BIT_u3_HL(uint8_t u3)
{
	mCycle += 3;

	uint8_t data = mem_read(r.hl);
	uint16_t res = (data & (1 << u3)) != 0;
	setZeroF(res);
	setSubsF(false);
	setHCarryF8(false);
}

void Cpu::RES_u3_r8(uint8_t& r8, uint8_t u3)
{
	mCycle += 2;

	r8 &= (0xFF ^ (1 << u3));
}

void Cpu::RES_u3_HL(uint8_t u3)
{
	mCycle += 4;

	uint8_t data = mem_read(r.hl);
	data &= (0xFF ^ (1 << u3));
	mem_write(r.hl, data);
}

void Cpu::SET_u3_r8(uint8_t& r8, uint8_t u3)
{
	mCycle += 2;

	r8 |= (1 << u3);
}

void Cpu::SET_u3_HL(uint8_t u3)
{
	mCycle += 4;
	
	uint8_t data = mem_read(r.hl) | (1 << u3);
	mem_write(r.hl, data);
}

void Cpu::SWAP_r8(uint8_t& r8)
{
	mCycle += 2;

	uint8_t temp1 = (r8 & 0x0F) << 4;
	uint8_t temp2 = (r8 & 0xF0) >> 4;
	uint8_t res = temp1 | temp2;
	setZeroF(res);
	setSubsF(false);
	setHCarryF8(false);
	setCarryF8(false);
	r8 = res;
}

void Cpu::SWAP_HL()
{
	mCycle += 4;

	uint8_t data = mem_read(r.hl);
	uint8_t temp1 = (data & 0x0F) << 4;
	uint8_t temp2 = (data & 0xF0) >> 4;
	uint8_t res = temp1 | temp2;
	setZeroF(res);
	setSubsF(false);
	setHCarryF8(false);
	setCarryF8(false);
	mem_write(r.hl, res);
}

void Cpu::RL_r8(uint8_t& r8)
{
	mCycle += 2;

	uint8_t b7 = r8 & 0x80;
	bool flag = static_cast<bool>(b7);
	uint8_t res = (r8 << 1);
	setZeroF(res);
	setSubsF(false);
	setHCarryF8(false);
	setCarryF8(flag);
	r8 = res;
}

void Cpu::RL_HL()
{
	mCycle += 4;

	uint8_t data = mem_read(r.hl);
	uint8_t b7 = data & 0x80;
	bool flag = static_cast<bool>(b7);
	uint8_t res = (data << 1);
	setZeroF(res);
	setSubsF(false);
	setHCarryF8(false);
	setCarryF8(flag);
	mem_write(r.hl, res);
}

void Cpu::RLA()
{
	mCycle += 2;

	uint8_t b7 = r.a & 0x80;
	bool flag = static_cast<bool>(b7);
	uint8_t res = (r.a << 1);
	r.f |= 0x80; // setZeroF(res); use overload
	setSubsF(false);
	setHCarryF8(false);
	setCarryF8(flag);
	r.a = res;
}

void Cpu::RLC_r8(uint8_t& r8)
{
	mCycle += 2;

	uint8_t b7 = r8 & 0x80;
	bool flag = static_cast<bool>(b7);
	uint8_t res = (r8 << 1);
	if (flag)
		res |= 0x01;
	setZeroF(res);
	setSubsF(false);
	setHCarryF8(false);
	setCarryF8(flag);
	r8 = res;
}

void Cpu::RLC_HL()
{
	mCycle += 4;

	uint8_t data = mem_read(r.hl);
	uint8_t b7 = data & 0x80;
	bool flag = static_cast<bool>(b7);
	uint8_t res = (data << 1);
	if (flag)
		res |= 0x01;
	setZeroF(res);
	setSubsF(false);
	setHCarryF8(false);
	setCarryF8(flag);
	mem_write(r.hl, res);
}

void Cpu::RLCA()
{
	mCycle += 2;

	uint8_t b7 = r.a & 0x80;
	bool flag = static_cast<bool>(b7);
	uint8_t res = (r.a << 1);
	if (flag)
		res |= 0x01;
	r.f |= 0x80; // setZeroF(res); use overload
	setSubsF(false);
	setHCarryF8(false);
	setCarryF8(flag);
	r.a = res;
}

void Cpu::RR_r8(uint8_t& r8)
{
	mCycle += 2;

	uint8_t b0 = r8 & 0x01;
	bool flag = static_cast<bool>(b0);
	uint8_t res = (r8 >> 1);
	setZeroF(res);
	setSubsF(false);
	setHCarryF8(false);
	setCarryF8(flag);
	r8 = res;
}

void Cpu::RR_HL()
{
	mCycle += 4;

	uint8_t data = mem_read(r.hl);
	uint8_t b0 = data & 0x01;
	bool flag = static_cast<bool>(b0);
	uint8_t res = (data >> 1);
	setZeroF(res);
	setSubsF(false);
	setHCarryF8(false);
	setCarryF8(flag);
	mem_write(r.hl, res);
}

void Cpu::RRA()
{
	mCycle += 2;

	uint8_t b0 = r.a & 0x01;
	bool flag = static_cast<bool>(b0);
	uint8_t res = (r.a >> 1);
	r.f |= 0x80; // setZeroF(res); use overload
	setSubsF(false);
	setHCarryF8(false);
	setCarryF8(flag);
	r.a = res;
}

void Cpu::RRC_r8(uint8_t& r8)
{
	mCycle += 2;

	uint8_t b0 = r8 & 0x01;
	bool flag = static_cast<bool>(b0);
	uint8_t res = (r8 >> 1);
	if (flag)
		res |= 0x80;
	setZeroF(res);
	setSubsF(false);
	setHCarryF8(false);
	setCarryF8(flag);
	r8 = res;
}

void Cpu::RRC_HL()
{
	mCycle += 4;

	uint8_t data = mem_read(r.hl);
	uint8_t b0 = data & 0x01;
	bool flag = static_cast<bool>(b0);
	uint8_t res = (data >> 1);
	if (flag)
		res |= 0x80;
	setZeroF(res);
	setSubsF(false);
	setHCarryF8(false);
	setCarryF8(flag);
	mem_write(r.hl, res);
}

void Cpu::RRCA()
{
	mCycle += 2;

	uint8_t b0 = r.a & 0x01;
	bool flag = static_cast<bool>(b0);
	uint8_t res = (r.a >> 1);
	if (flag)
		res |= 0x80;
	r.f |= 0x80; // setZeroF(res); use overload
	setSubsF(false);
	setHCarryF8(false);
	setCarryF8(flag);
	r.a = res;
}

void Cpu::SLA_r8(uint8_t& r8)
{
	mCycle += 2;

	uint8_t b7 = r8 & 0x80;
	bool flag = static_cast<bool>(b7);
	uint8_t res = r8 << 1;
	setZeroF(res);
	setSubsF(false);
	setHCarryF8(false);
	setCarryF8(flag);
	r8 = res;
}

void Cpu::SLA_HL()
{
	mCycle += 4;

	uint8_t data = mem_read(r.hl);
	uint8_t b7 = data & 0x80;
	bool flag = static_cast<bool>(b7);
	uint8_t res = data << 1;
	setZeroF(res);
	setSubsF(false);
	setHCarryF8(false);
	setCarryF8(flag);
	mem_write(r.hl, res);
}

void Cpu::SRA_r8(uint8_t& r8)
{
	mCycle += 2;

	uint8_t b0 = r8 & 0x01;
	uint8_t b0 = r8 & 0x80;
	bool flagb0 = static_cast<bool>(b0);
	bool flagb7 = static_cast<bool>(b0);
	uint8_t res = r8 >> 1;
	if (flagb7)
		res |= 0x80;
	setZeroF(res);
	setSubsF(false);
	setHCarryF8(false);
	setCarryF8(flagb0);
	r8 = res;
}

void Cpu::SRA_HL()
{
	mCycle += 4;

	uint8_t data = mem_read(r.hl);
	uint8_t b0 = data & 0x01;
	uint8_t b0 = data & 0x80;
	bool flagb0 = static_cast<bool>(b0);
	bool flagb7 = static_cast<bool>(b0);
	uint8_t res = data >> 1;
	if (flagb7)
		res |= 0x80;
	setZeroF(res);
	setSubsF(false);
	setHCarryF8(false);
	setCarryF8(flagb0);
	mem_write(r.hl, res);
}

void Cpu::SRL_r8(uint8_t& r8)
{
	mCycle += 2;

	uint8_t b0 = r8 & 0x01;
	bool flag = static_cast<bool>(b0);
	uint8_t res = r8 >> 1;
	setZeroF(res);
	setSubsF(false);
	setHCarryF8(false);
	setCarryF8(flag);
	r8 = res;
}

void Cpu::SRL_HL()
{
	mCycle += 4;

	uint8_t data = mem_read(r.hl);
	uint8_t b0 = data & 0x01;
	bool flag = static_cast<bool>(b0);
	uint8_t res = data >> 1;
	setZeroF(res);
	setSubsF(false);
	setHCarryF8(false);
	setCarryF8(flag);
	mem_write(r.hl, res);
}

void Cpu::LD_r8_r8(uint8_t& r8, uint8_t& r8_)
{
	mCycle += 1;

	r8 = r8_;
}

void Cpu::LD_r8_n8(uint8_t& r8, uint8_t n8)
{
	mCycle += 2;

	r8 = n8;
}

void Cpu::LD_r16_n16(uint16_t& r16, uint16_t n16)
{
	mCycle += 3;

	r16 = n16;
}

void Cpu::LD_HL_r8(uint8_t& r8)
{
	mCycle += 2;

	mem_write(r.hl, r8);
}

void Cpu::LD_HL_n8(uint8_t n8)
{
	mCycle += 3;

	mem_write(r.hl, n8);
}

void Cpu::LD_r8_HL(uint8_t& r8)
{
	mCycle += 2;

	r8 = mem_read(r.hl);
}

void Cpu::LD_r16_A(uint16_t& r16)
{
	mCycle += 2;

	mem_write(r16, r.a);
}

void Cpu::LD_n16_A(uint16_t n16)
{
	mCycle += 4;

	mem_write(n16, r.a);
}

void Cpu::LDH_n16_A(uint16_t n16)
{
	mCycle += 3;

	if (n16 <= 0xFFFF && n16 >= 0xFF00)
		mem_write(n16, r.a);
}

void Cpu::LDH_C_A()
{
	mCycle += 2;

	mem_write(0xFF00 + r.c, r.a);
}

void Cpu::LD_A_r16(uint16_t& r16)
{
	mCycle += 2;

	r.a = mem_read(r16);
}

void Cpu::LD_A_n16(uint16_t n16)
{
	mCycle += 4;

	r.a = mem_read(n16);
}

void Cpu::LDH_A_n16(uint16_t n16)
{
	mCycle += 3;
	if (n16 <= 0xFFFF && n16 >= 0xFF00)
		r.a = mem_read(n16);
}

void Cpu::LDH_A_C()
{
	mCycle += 2;

	r.a = mem_read(0xFF00 + r.c);
}

void Cpu::LD_HLI_A()
{
	mCycle += 2;
	
	r.a = mem_read(r.hl);
	++r.hl;
}

void Cpu::LD_HLD_A()
{
	mCycle += 2;

	r.a = mem_read(r.hl);
	--r.hl;
}

void Cpu::LD_A_HLI()
{
	mCycle += 2;

	mem_write(r.hl, r.a);
	++r.hl;
}

void Cpu::LD_A_HLD()
{
	mCycle += 2;

	mem_write(r.hl, r.a);
	--r.hl;
}

void Cpu::ADD_HL_SP()
{
	mCycle += 2;
	
	r.hl += sp;
}

void Cpu::ADD_SP_e8(int8_t e8)
{
	mCycle += 4;

	uint16_t res = sp + e8;
	r.f &= ~0x80; //setZeroF(res);
	setSubsF(false);
	setHCarryF8(sp, e8);
	setCarryF8(res);
}

void Cpu::DEC_SP()
{
	mCycle += 2;

	--sp;
}

void Cpu::INC_SP()
{
	mCycle += 2;

	++sp;
}

void Cpu::LD_SP_n16(uint16_t n16)
{
	mCycle += 3;

	sp = n16;
}

void Cpu::LD_n16_SP(uint16_t n16)
{
	mCycle +=5;

	mem_write(n16, (sp & 0xFF));
	mem_write((n16 + 1), (sp >> 8));
}

void Cpu::LD_HL_SP_e8(int8_t e8)
{
	mCycle += 3;

	uint16_t res = sp + e8;
	r.f &= ~0x80; //setZeroF(res); need bool overlaod
	setSubsF(false);
	setHCarryF8(sp, e8);
	setCarryF8(res);
	r.hl = res;
}

void Cpu::LD_SP_HL()
{
	mCycle += 2;

	sp = r.hl;
}

void Cpu::POP_AF()
{
	mCycle += 3;

	r.f = mem_read(sp);
	++sp;
	r.a = mem_read(sp);
	++sp;

	uint8_t res = r.f;
	setZeroF(res & 0x80);
	setSubsF(res & 0x40);
	setHCarryF8(res & 0x20);
	setCarryF8(static_cast<bool>(res & 0x10));
}

void Cpu::POP_r16(uint16_t& r16)
{
	mCycle += 3;

	uint8_t lsb = mem_read(sp);
	++sp;
	uint8_t msb = mem_read(sp);
	++sp;

	r16 = (msb << 8) | lsb;
}

void Cpu::PUSH_AF()
{
	mCycle += 4;

	--sp;
	mem_write(sp, r.a);
	--sp;
	mem_write(sp, r.f);
}

void Cpu::PUSH_r16(uint16_t& r16)
{
	mCycle += 4;

	uint8_t msb = r16 >> 8;
	uint8_t lsb = (r16 << 8) >> 8;
	--sp;
	mem_write(sp, msb);
	--sp;
	mem_write(sp, lsb);
}

void Cpu::CCF()
{
	mCycle += 1;

	setSubsF(false);
	setHCarryF8(false);
	if ((r.f & 0x10) == 1)
		setCarryF8(false);
	else
		setCarryF8(true);
}

void Cpu::NOP()
{
	mCycle += 1;
}

void Cpu::SCF()
{
	mCycle += 1;

	setSubsF(false);
	setHCarryF8(false);
	setCarryF8(true);
}

void Cpu::CALL_n16(uint16_t n16)
{
	mCycle += 6;
	uint8_t data1 = static_cast<uint8_t>(n16 >> 8);
	uint8_t data2 = static_cast<uint8_t>((n16 << 8) >> 8);
	--sp;
	mem_write(sp, data1);
	--sp;
	mem_write(sp, data2);
	JP_n16(n16);
}

void Cpu::CALL_cc_n16(std::string cc, uint16_t n16)
{
	mCycle += 6;

	uint8_t data1 = static_cast<uint8_t>(n16 >> 8);
	uint8_t data2 = static_cast<uint8_t>((n16 << 8) >> 8);

	if (cc == "Z")
	{
		if ((r.f & 0x80) == 0x80);
		{
			--sp;
			mem_write(sp, data1);
			--sp;
			mem_write(sp, data2);
			JP_n16(n16);
		}
	}
	else if (cc == "NZ")
	{
		if ((r.f & 0x80) == 0);
		{
			--sp;
			mem_write(sp, data1);
			--sp;
			mem_write(sp, data2);
			JP_n16(n16);
		}
	}
	else if (cc == "C")
	{
		if ((r.f & 0x10) == 0x10);
		{
			--sp;
			mem_write(sp, data1);
			--sp;
			mem_write(sp, data2);
			JP_n16(n16);
		}
	}
	else if (cc == "NC")
	{
		if ((r.f & 0x10) == 0);
		{
			--sp;
			mem_write(sp, data1);
			--sp;
			mem_write(sp, data2);
			JP_n16(n16);
		}
	}
	else if (cc == "! cc")
		mCycle -= 3;
}

void Cpu::JP_HL()
{
	mCycle += 1;

	pc = r.hl;
}

void Cpu::JP_n16(uint16_t n16)
{
	mCycle += 4;

	pc = n16;

}

void Cpu::JP_cc_n16(std::string cc, uint16_t n16)
{
	mCycle += 4;

	if (cc == "Z")
	{
		if ((r.f & 0x80) == 0x80);
		pc = n16;
	}
	else if (cc == "NZ")
	{
		if ((r.f & 0x80) == 0);
		pc = n16;
	}
	else if (cc == "C")
	{
		if ((r.f & 0x10) == 0x10);
		pc = n16;
	}
	else if (cc == "NC")
	{
		if ((r.f & 0x10) == 0);
		pc = n16;
	}
	else if (cc == "! cc")
		mCycle -= 1;
}

void Cpu::JR_e8(int8_t e8)
{
	mCycle += 3;

	pc += e8;
}

void Cpu::JR_cc_e8(std::string cc, int8_t e8)
{
	mCycle += 3;

	if (cc == "Z")
	{
		if ((r.f & 0x80) == 0x80);
		pc += e8;
	}
	else if (cc == "NZ")
	{
		if ((r.f & 0x80) == 0);
		pc += e8;
	}
	else if (cc == "C")
	{
		if ((r.f & 0x10) == 0x10);
		pc += e8;
	}
	else if (cc == "NC")
	{
		if ((r.f & 0x10) == 0);
		pc += e8;
	}
	else if (cc == "! cc")
		mCycle -= 1;
}

void Cpu::RET_cc(std::string cc)
{
	mCycle += 5;

	if (cc == "Z")
	{
		if ((r.f & 0x80) == 0x80);
		{
			uint8_t lsb = mem_read(sp);
			++sp;
			uint8_t msb = mem_read(sp);
			++sp;

			pc = (msb << 8) | lsb;
		}
	}
	else if (cc == "NZ")
	{
		if ((r.f & 0x80) == 0);
		{
			uint8_t lsb = mem_read(sp);
			++sp;
			uint8_t msb = mem_read(sp);
			++sp;

			pc = (msb << 8) | lsb;
		}
	}
	else if (cc == "C")
	{
		if ((r.f & 0x10) == 0x10);
		{
			uint8_t lsb = mem_read(sp);
			++sp;
			uint8_t msb = mem_read(sp);
			++sp;

			pc = (msb << 8) | lsb;
		}
	}
	else if (cc == "NC")
	{
		if ((r.f & 0x10) == 0);
		{
			uint8_t lsb = mem_read(sp);
			++sp;
			uint8_t msb = mem_read(sp);
			++sp;

			pc = (msb << 8) | lsb;
		}
	}
	else if (cc == "! cc")
		mCycle -= 3;
}

void Cpu::RET()
{
	mCycle += 4;

	uint8_t lsb = mem_read(sp);
	++sp;
	uint8_t msb = mem_read(sp);
	++sp;

	pc = (msb << 8) | lsb;
}
