#pragma once
#include <cstdint>
#include <iostream>
#include "register.h"
#include "instructions.h"
#include <fstream>
#include <iomanip>
#include <vector>

class Timer;

class Cpu
{
public:

	uint8_t opcode;
	uint8_t cb_opcode;
	uint8_t memory[65536]{ 0 };
	uint16_t pc;
	uint16_t sp;
	uint8_t IME;
	bool IME_Next;
	bool IME_Next_;
	int mCycle;
	bool prefixFlag;

	void fetchOpcode();
	void decodeOpcode(uint8_t opcode, uint8_t cb_opcode, bool prefixFlag);
	void executeOpcode(uint8_t x, uint8_t y, uint8_t z, uint8_t p, uint8_t q);
	void executeCBOpcode(uint8_t x, uint8_t y, uint8_t z, uint8_t p, uint8_t q);
	void cycle();
	Registers r{0xB0, 0x01, 0x13, 0x00, 0xD8, 0x00, 0x4D, 0x01};
	Cpu();
private:
	[[nodiscard]] uint8_t mem_read(const uint16_t& adr) const;
	void mem_write(const uint16_t& adr, const uint8_t& value);

	uint16_t* rp[4] = { &r.bc, &r.de, &r.hl, &sp };
	uint16_t* rp2[4] = { &r.bc, &r.de, &r.hl, &r.af };
	//uint8_t rf[8] = {r.b, r.c, r.d, r.e, r.h, r.l, 0, r.a}; //is placeholder for (HL)
	uint8_t* rf[8] = { &r.b, &r.c, &r.d, &r.e, &r.h, &r.l, &r.f, &r.a };
	uint16_t* HL = &r.hl;
	uint8_t vec[8] = {0x00,0x08,0x10,0x18,0x20,0x28,0x30,0x38};
	
	//
	void Tick(Timer& timer);

	// flag methods

	void setZeroF(uint32_t res);
	void setSubsF(bool subs); // bFlag is false for 8 bit true for 16 bit
	void setHCarryF8(uint16_t x, uint16_t y);
	void setHCarryF8(uint8_t x, uint8_t y, bool c);
	void setHCarryF16(uint16_t x, uint16_t y);
	void setHCarryF8(bool flag);
	void setHCarryF16(bool flag);
	void setCarryF8(uint16_t res);
	void setCarryF8(uint32_t res);
	void setCarryF8(bool flag);
	void setCarryF16(uint32_t res);
	void setCarryFBorrow(uint16_t x, uint16_t y);
	void setCarryFBorrow(uint16_t x, uint16_t y, bool c);
	void setHCarryFBorrow(uint8_t x, uint8_t y);
	void setHCarryFBorrow(uint8_t x, uint8_t y, bool c);
	void setCarryFShift();

	//flag method helpers

	bool is8bCarry(uint16_t res);
	bool is16bCarry(uint32_t res);
	bool isHalfCarry8(uint16_t x, uint16_t y);
	bool isHalfCarry8(uint8_t x, uint8_t y, bool c);
	bool isHalfCarry16(uint16_t x, uint16_t y);
	bool isBorrow8(uint16_t x, uint16_t y);
	bool isBorrow8(uint16_t x, uint16_t y, bool c);
	bool isBorrow4(uint8_t x, uint8_t y);
	bool isBorrow4(uint8_t x, uint8_t y, bool c);
public: //for unit test
	// Instructions
	// 
	// 8-bit Arithmetic and Logic Instructions

	void ADC_A_r8(uint8_t& r8);
	void ADC_A_HL();
	void ADC_A_n8(uint8_t n8);

	void ADD_A_r8(uint8_t& r8);
	void ADD_A_HL();
	void ADD_A_n8(uint8_t n8);

	void AND_A_r8(uint8_t& r8);
	void AND_A_HL();
	void AND_A_n8(uint8_t n8);

	void CP_A_r8(uint8_t& r8);
	void CP_A_HL();
	void CP_A_n8(uint8_t n8);

	void DEC_r8(uint8_t& r8);
	void DEC_HL();

	void INC_r8(uint8_t& r8);
	void INC_HL();

	void OR_A_r8(uint8_t& r8);
	void OR_A_HL();
	void OR_A_n8(uint8_t n8);

	void SBC_A_r8(uint8_t& r8);
	void SBC_A_HL();
	void SBC_A_n8(uint8_t n8);

	void SUB_A_r8(uint8_t& r8);
	void SUB_A_HL();
	void SUB_A_n8(uint8_t n8);

	//void SUB_A_r8(uint8_t& r8);
	//void SUB_A_HL();
	//void SUB_A_n8(uint8_t n8);

	void XOR_A_r8(uint8_t& r8);
	void XOR_A_HL();
	void XOR_A_n8(uint8_t n8);

	// 16-bit Arithmetic Instrucitons

	void ADD_HL_r16(uint16_t r16);
	void DEC_r16(uint16_t& r16);
	void INC_r16(uint16_t& r16);

	// Bit Operations Instructions

	void BIT_u3_r8(uint8_t& r8, uint8_t u3);
	void BIT_u3_HL(uint8_t u3);

	void RES_u3_r8(uint8_t& r8, uint8_t u3);
	void RES_u3_HL(uint8_t u3);

	void SET_u3_r8(uint8_t& r8, uint8_t u3);
	void SET_u3_HL(uint8_t u3);

	void SWAP_r8(uint8_t& r8);
	void SWAP_HL();

	// Bit Shift Instructions

	void RL_r8(uint8_t& r8);
	void RL_HL();
	void RLA();
	void RLC_r8(uint8_t& r8);
	void RLC_HL();
	void RLCA();

	void RR_r8(uint8_t& r8);
	void RR_HL();

	void RRA();
	void RRC_r8(uint8_t& r8);
	void RRC_HL();
	void RRCA();

	void SLA_r8(uint8_t& r8);
	void SLA_HL();

	void SRA_r8(uint8_t& r8);
	void SRA_HL();

	void SRL_r8(uint8_t& r8);
	void SRL_HL();

	// Load Instructions

	void LD_r8_r8(uint8_t& r8, uint8_t& r8_);
	void LD_r8_n8(uint8_t& r8, uint8_t n8);
	void LD_r16_n16(uint16_t& r16, uint16_t n16);
	void LD_HL_r8(uint8_t& r8);
	void LD_HL_n8(uint8_t n8);
	void LD_r8_HL(uint8_t& r8);
	void LD_r16_A(uint16_t& r16);
	void LD_n16_A(uint16_t n16);

	void LDH_n16_A(uint8_t n8);
	void LDH_C_A();

	void LD_A_r16(uint16_t& r16);
	void LD_A_n16(uint16_t n16);

	void LDH_A_n16(uint8_t n8);
	void LDH_A_C();

	void LD_HLI_A();
	void LD_HLD_A();
	void LD_A_HLI();
	void LD_A_HLD();

	// Jumps and Subroutines

	void CALL_n16(uint16_t n16);
	void CALL_cc_n16(uint8_t cc, uint16_t n16);

	void JP_HL();
	void JP_n16(uint16_t n16);
	void JP_cc_n16(uint8_t cc, uint16_t n16);
	void JR_e8(int8_t e8);
	void JR_cc_e8(uint8_t cc, int8_t e8);

	void RET_cc(uint8_t cc);
	void RET();
	void RETI();

	void RST_vec(uint8_t vec);
	
	// Stack Operations Instructions

	void ADD_HL_SP();
	void ADD_SP_e8(int8_t e8);

	void DEC_SP();
	void INC_SP();

	void LD_SP_n16(uint16_t n16);
	void LD_n16_SP(uint16_t n16);
	void LD_HL_SP_e8(int8_t e8);
	void LD_SP_HL();

	void POP_AF();
	void POP_r16(uint16_t& r16);

	void PUSH_AF();
	void PUSH_r16(uint16_t& r16);

	// Miscellaneous Instructions

	void CCF();
	void CPL();
	void DAA();
	void DI();
	void EI();
	void HALT();
	void NOP();
	void SCF();
	void STOP();

	typedef void (Cpu::*functionPointer)(uint8_t &r8);
	functionPointer ALU_r8[8] = { &Cpu::ADD_A_r8, &Cpu::ADC_A_r8, &Cpu::SUB_A_r8, &Cpu::SBC_A_r8, &Cpu::AND_A_r8, &Cpu::XOR_A_r8, &Cpu::OR_A_r8, &Cpu::CP_A_r8 };

	typedef void (Cpu::* functionPointerHL)();
	functionPointerHL ALU_r8_HL[8] = { &Cpu::ADD_A_HL, &Cpu::ADC_A_HL, &Cpu::SUB_A_HL, &Cpu::SBC_A_HL, &Cpu::AND_A_HL, &Cpu::XOR_A_HL, &Cpu::OR_A_HL, &Cpu::CP_A_HL };

	functionPointer ROT_r8[8] = { &Cpu::RLC_r8, &Cpu::RRC_r8, &Cpu::RL_r8, &Cpu::RR_r8, &Cpu::SLA_r8, &Cpu::SRA_r8, &Cpu::SWAP_r8, &Cpu::SRL_r8 };
	functionPointerHL ROT_HL[8] = { &Cpu::RLC_HL, &Cpu::RRC_HL, &Cpu::RL_HL, &Cpu::RR_HL, &Cpu::SLA_HL, &Cpu::SRA_HL, &Cpu::SWAP_HL, &Cpu::SRL_HL };
	void writeLog() const;
	std::vector<uint8_t> readROM(const std::string& filePath);
};