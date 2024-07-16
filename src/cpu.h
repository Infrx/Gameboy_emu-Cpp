#pragma once
#include <cstdint>
#include <iostream>
#include "register.h"
#include "instructions.h"


class Cpu
{
public:

	uint8_t opcode;
	uint8_t cb_opcode;
	uint8_t memory[65536];
	uint16_t pc;
	uint16_t sp;
	bool IME;
	int mCycle;
	bool prefixFlag;
	Cpu();
	void fetchOpcode();
	void decodeOpcode(uint8_t opcode, uint8_t cb_opcode, bool prefixFlag);
	void executeOpcode(uint8_t x, uint8_t y, uint8_t z, uint8_t p, uint8_t q);
	void executeCBOpcode(uint8_t x, uint8_t y, uint8_t z, uint8_t p, uint8_t q);
	Registers r;
private:
	uint8_t mem_read(const uint16_t adr) const;
	void mem_write(const uint16_t adr, uint8_t value);

	

	// flag methods

	void setZeroF(uint32_t res);
	void setSubsF(bool subs); // bFlag is false for 8 bit true for 16 bit
	void setHCarryF8(uint16_t x, uint16_t y);
	void setHCarryF16(uint16_t x, uint16_t y);
	void setHCarryF8(bool flag);
	void setHCarryF16(bool flag);
	void setCarryF8(uint16_t res);
	void setCarryF8(uint32_t res);
	void setCarryF8(bool flag);
	void setCarryF16(uint32_t res);
	void setCarryFBorrow(uint16_t x, uint16_t y);
	void setHCarryFBorrow(uint16_t x, uint16_t y);
	void setCarryFShift();

	//flag method helpers

	bool is8bCarry(uint16_t res);
	bool is16bCarry(uint32_t res);
	bool isHalfCarry8(uint16_t x, uint16_t y);
	bool isHalfCarry16(uint16_t x, uint16_t y);
	bool isBorrow8(uint16_t x, uint16_t y);
	bool isBorrow4(uint16_t x, uint16_t y);

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
	void DEC_r16(uint16_t r16);
	void INC_r16(uint16_t r16);

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

	void LDH_n16_A(uint16_t n16);
	void LDH_C_A();

	void LD_A_r16(uint16_t& r16);
	void LD_A_n16(uint16_t n16);

	void LDH_A_n16(uint16_t n16);
	void LDH_A_C();

	void LD_HLI_A();
	void LD_HLD_A();
	void LD_A_HLI();
	void LD_A_HLD();

	// Jumps and Subroutines

	void CALL_n16(uint16_t n16);
	void CALL_cc_n16(std::string cc, uint16_t n16);

	void JP_HL();
	void JP_n16(uint16_t n16);
	void JP_cc_n16(std::string cc, uint16_t n16);
	void JR_e8(int8_t e8);
	void JR_cc_e8(std::string cc, int8_t e8);

	void RET_cc(std::string cc);
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
};