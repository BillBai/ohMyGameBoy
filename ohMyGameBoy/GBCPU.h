#pragma once

#include "GBTypes.h"
#include "GBMemoryUnit.h"

namespace GameBoy
{
	class GBCPU
	{
	public:
		GBCPU();

		// register accessors
		byte getA() const { return regA; }
		byte getB() const { return regB; }
		byte getC() const { return regC; }
		byte getD() const { return regD; }
		byte getE() const { return regE; }
		byte getH() const { return regH; }
		byte getL() const { return regL; }
		word getSP() const { return regSP; }
		word getPC() const { return regPC; }

		// flag register accessors
		// Z | N | H | C | 0 | 0 | 0 | 0
		word getFlag()			const { return regFlag; }
		bool getZeroFlag()		const { return (regFlag & 0x80) != 0; }
		bool getSubtractFlag()	const { return (regFlag & 0x40) != 0; }
		bool getHalfCarryFlag() const { return (regFlag & 0x20) != 0; }
		bool getCarryFlag()		const { return (regFlag & 0x10) != 0; }

		~GBCPU();

	private:
		// general purpose registers
		byte regA, regB, regC, regD, regE, regH, regL;
		// stack pointer register
		word regSP;
		// program counter
		word regPC;
		// flag register
		byte regFlag;

		// flag helpers
		void setZeroFlag()				{ regFlag = regFlag | 0x80; }
		void clearZeroFlag()			{ regFlag = regFlag & 0x7F; }
		void changeZeroFlag(bool b)		{ regFlag = b ? (regFlag | 0x80) : (regFlag & 0x7F); }

		void setSubtractFlag()				{ regFlag = regFlag | 0x40; }
		void clearSubtractFlag()			{ regFlag = regFlag & 0xBF; }
		void changeSubtractFlag(bool b)		{ regFlag = b ? (regFlag | 0x40) : (regFlag & 0xBF); }

		void setHalfCarryFlag()				{ regFlag = regFlag | 0x20; }
		void clearHalfCarryFlag()			{ regFlag = regFlag & 0xDF; }
		void changeHalfCarryFlag(bool b)	{ regFlag = b ? (regFlag | 0x20) : (regFlag & 0xDF); }

		void setCarryFlag()					{ regFlag = regFlag | 0x10; }
		void clearCarryFlag()				{ regFlag = regFlag & 0xEF; }
		void changeCarryFlag(bool b)		{ regFlag = b ? (regFlag | 0x10) : (regFlag & 0xEF); }


		// Memory
		GBMemoryUnit *memoryUnit;

		// GBCPU instructions
		// see http://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html for details
		// 0x00 ~ 0x0F
		void NOP();			// 0x00 NOP
		void LD_BC_nn();	// 0x01 LD BC, nn
		void LD_mBC_A();	// 0x02 LD (BC), A
		void INC_BC();		// 0x03 INC BC
		void INC_B();		// 0x04 INC B
		void DEC_B();		// 0x05 DEC B
		void LD_B_n();		// 0x06 LD B, n
		void RLCA();		// 0x07 RLCA
		void LD_mnn_SP();	// 0x08 LD (nn), SP
		void ADD_HL_BC();	// 0x09 ADD HL, BC
		void LD_A_mBC();	// 0x0A LD A, (BC)
		void DEC_BC();		// 0x0B DEC BC
		void INC_C();		// 0x0C INC C
		void DEC_C();		// 0x0D DEC C
		void LD_C_n();		// 0x0E LD C, n
		void RRCA();		// 0x0F RRCA
		// 0x10 ~ 0x1F
		void STOP();		// 0x10 STOP
		void LD_DE_nn();	// 0x11 LD DE, nn
		void LD_mDE_A();	// 0x12 LD (DE), A
		void INC_DE();		// 0x13 INC DE
		void INC_D();		// 0x14 INC D
		void DEC_D();		// 0x15 DEC D
		void LD_D_n();		// 0x16 LD D, n
		void RLA();			// 0x17 RLA
		void JR_n();		// 0x18 JR n
		void ADD_HL_DE();	// 0x19 ADD HL, DE
		void LD_A_mDE();	// 0x1A LD A, (DE)
		void DEC_DE();		// 0x1B DEC DE
		void INC_E();		// 0x1C INC E
		void DEC_E();		// 0x1D DEC E
		void LD_E_n();		// 0x1E LD E, n
		void RRA();			// 0x1F RRA
		// 0x20 ~ 0x2F
		void JR_NZ_n();		// 0x20 JR NZ n
		void LD_HL_nn();	// 0x21 LD HL, nn
		void LDI_mHL_A();	// 0x22 LDI (HL), A
		void INC_HL();		// 0x23 INC HL
		void INC_H();		// 0x24 INC H
		void DEC_H();		// 0x25 DEC H
		void LD_H_n();		// 0x26 LD H, n
		void DAA();			// 0x27 DAA
		void JR_Z_n();		// 0x28 JA Z, n
		void ADD_HL_HL();	// 0x29 ADD HL, HL
		void LDI_A_mHL();	// 0x2A LDI A, (HL)
		void DEC_HL();		// 0x2B DEC HL
		void INC_L();		// 0x2C INC L
		void DEC_L();		// 0x2D DEC L
		void LD_L_n();		// 0x2E LD L, n
		void CPL();			// 0x2F CPL
		// 0x30 ~ 0x3F
		void JR_NC_n();		// 0x30 JR NC, n
		void LD_SP_nn();	// 0x31 LD SP, nn
		void LDD_mHL_A();	// 0x32 LDD (HL), A
		void INC_SP();		// 0x33 INC SP
		void INC_mHL();		// 0x34 INC (HL)
		void DEC_mHL();		// 0x35 DEC (HL)
		void LD_mHL_n();	// 0x36 LD (HL), n
		void SCF();			// 0x37 SCF
		void JR_C_n();		// 0x38 JR C, n
		void ADD_HL_SP();	// 0x39 ADD HL, SP
		void LDD_A_mHL();	// 0x3A LDD A, (HL)
		void DEC_SP();		// 0x3B DEC A
		void INC_A();		// 0x3C INC A
		void DEC_A();		// 0x3D DEC A
		void LD_A_n();		// 0x3E LD A, n
		void CCF();			// 0x3F CCF
		// 0x40 ~ 0x4F
		void LD_B_B();		// 0x40 LD B, B
		void LD_B_C();		// 0x41 LD B, C
		void LD_B_D();		// 0x42 LD B, D
		void LD_B_E();		// 0x43 LD B, E
		void LD_B_H();		// 0x44 LD B, H
		void LD_B_L();		// 0x45 LD B, L
		void LD_B_mHL();	// 0x46 LD B, (HL)
		void LD_B_A();		// 0x47 LD B, A
		void LD_C_B();		// 0x48 LD C, B
		void LD_C_C();		// 0x49 LD C, C
		void LD_C_D();		// 0x4A LD C, D
		void LD_C_E();		// 0x4B LD C, E
		void LD_C_H();		// 0x4C LD C, H
		void LD_C_L();		// 0x4D LD C, L
		void LD_C_mHL();	// 0x4E LD C, (HL)
		void LD_C_A();		// 0x4F LD C, A
		// 0x50 ~ 0x5F
		void LD_D_B();		// 0x50 LD D, B
		void LD_D_C();		// 0x51 LD D, C
		void LD_D_D();		// 0x52 LD D, D
		void LD_D_E();		// 0x53 LD D, E
		void LD_D_H();		// 0x54 LD D, H
		void LD_D_L();		// 0x55 LD D, L
		void LD_D_mHL();	// 0x56 LD D, (HL)
		void LD_D_A();		// 0x57 LD D, A
		void LD_E_B();		// 0x58 LD E, B
		void LD_E_C();		// 0x59 LD E, C
		void LD_E_D();		// 0x5A LD E, D
		void LD_E_E();		// 0x5B LD E, E
		void LD_E_H();		// 0x5C LD E, H
		void LD_E_L();		// 0x5D LD E, L
		void LD_E_mHL();	// 0x5E LD E, (HL)
		void LD_E_A();		// 0x5F LD E, A
		// 0x60 ~ 0x6F
		void LD_H_B();		// LD H, B
		void LD_H_C();		// LD H, C
		void LD_H_D();		// LD H, D
		void LD_H_E();		// LD H, E
		void LD_H_H();		// LD H, H
		void LD_H_L();		// LD H, L
		void LD_H_mHL();	// LD H, (HL)
		void LD_H_A();		// LD H, A
		void LD_L_B();		// LD L, B
		void LD_L_C();		// LD L, C
		void LD_L_D();		// LD L, D
		void LD_L_E();		// LD L, E
		void LD_L_H();		// LD L, H
		void LD_L_L();		// LD L, L
		void LD_L_mHL();	// LD L, (HL)
		void LD_L_A();		// LD L, A
		// 0x70 ~ 0x7F
		void LD_mHL_B();	// LD (HL), B
		void LD_mHL_C();	// LD (HL), C
		void LD_mHL_D();	// LD (HL), D
		void LD_mHL_E();	// LD (HL), E
		void LD_mHL_H();	// LD (HL), H
		void LD_mHL_L();	// LD (HL), L
		void HALT();		// HALT
		void LD_mHL_A();	// LD (HL), A
		void LD_A_B();		// LD A, B
		void LD_A_C();		// LD A, C
		void LD_A_D();		// LD A, D
		void LD_A_E();		// LD A, E
		void LD_A_H();		// LD A, H
		void LD_A_L();		// LD A, L
		void LD_A_mHL();	// LD A, (HL)
		void LD_A_A();		// LD A, A
		// 0x80 ~ 0x8F
		void ADD_A_B();		// ADD A, B
		void ADD_A_C();		// ADD A, C
		void ADD_A_D();		// ADD A, D
		void ADD_A_E();		// ADD A, E
		void ADD_A_H();		// ADD A, H
		void ADD_A_L();		// ADD A, L
		void ADD_A_mHL();	// ADD A, (HL)
		void ADD_A_A();		// ADD A, A
		void ADC_A_B();		// ADC A, B
		void ADC_A_C();		// ADC A, C
		void ADC_A_D();		// ADC A, D
		void ADC_A_E();		// ADC A, E
		void ADC_A_H();		// ADC A, H
		void ADC_A_L();		// ADC A, L
		void ADC_A_mHL();	// ADC A, (HL)
		void ADC_A_A();		// ADC A, A
		// 0x90 ~ 0x9F
		void SUB_A_B();		// SUB A, B
		void SUB_A_C();		// SUB A, C
		void SUB_A_D();		// SUB A, D
		void SUB_A_E();		// SUB A, E
		void SUB_A_H();		// SUB A, H
		void SUB_A_L();		// SUB A, L
		void SUB_A_mHL();	// SUB A, (HL)
		void SUB_A_A();		// SUB A, A
		void SBC_A_B();		// SBC A, B
		void SBC_A_C();		// SBC A, C
		void SBC_A_D();		// SBC A, D
		void SBC_A_E();		// SBC A, E
		void SBC_A_H();		// SBC A, H
		void SBC_A_L();		// SBC A, L
		void SBC_A_mHL();	// SBC A, (HL)
		void SBC_A_A();		// SBC A, A
		// 0xA0 ~ 0xAF
		void AND_B();		// AND B
		void AND_C();		// AND C
		void AND_D();		// AND D
		void AND_E();		// AND E
		void AND_H();		// AND H
		void AND_L();		// AND L
		void AND_mHL();		// AND (HL)
		void AND_A();		// AND A
		void XOR_B();		// XOR B
		void XOR_C();		// XOR C
		void XOR_D();		// XOR D
		void XOR_E();		// XOR E
		void XOR_H();		// XOR H
		void XOR_L();		// XOR L
		void XOR_mHL();		// XOR (HL)
		void XOR_A();		// XOR A
		// 0xB0 ~ 0xBF
		void OR_B();		// OR B
		void OR_C();		// OR C
		void OR_D();		// OR D
		void OR_E();		// OR E
		void OR_H();		// OR H
		void OR_L();		// OR L
		void OR_mHL();		// OR (HL)
		void OR_A();		// OR A
		void CP_B();		// CP B
		void CP_C();		// CP C
		void CP_D();		// CP D
		void CP_E();		// CP E
		void CP_H();		// CP H
		void CP_L();		// CP L
		void CP_mHL();		// CP (HL)
		void CP_A();		// CP A
		// 0xC0 ~ 0xCF
		void RET_nFZ();		// RET !FZ
		void POP_BC();		// POP BC
		void JP_nFZ_nn();	// JP !FZ, nn
		void JP_nn();		// JP nn
		void CALL_nFZ_nn();	// CALL !FZ, nn
		void PUSH_BC();		// PUSH BC
		void ADD_n();		// ADD n
		void RST_0();		// RST 0
		void RET_FZ();		// RET FZ
		void RET();			// RET
		void JP_FZ_nn();	// JP FZ, nn
		void CB_op_code();	// secondary op code, begin with 0xCB
		void CALL_FZ_nn();	// CALL FZ, nn
		void CALL_nn();		// CALL nn
		void ADC_A_n();		// ADC A, n
		void RST_8();		// RST 0x8
		// 0xD0 ~ 0xDF
		void RET_nFC();		// RET !FC
		void POP_DE();		// POP DE
		void JP_nFC_nn();	// JP !FC, nn
		void Illegal_op_code_D3();	// !!! Illegal op code, should not be encountered
		void CALL_nFC_nn();	// CALL !FC, nn
		void PUSH_DE();		// PUSH DE
		void SUB_A_n();		// SUB A, n
		void RST_10();		// RST 0x10
		void RET_FC();		// RET FC
		void RETI();		// RETI
		void JP_FC_nn();	// JP FC, nn
		void Illegal_op_code_DB(); // !!! Illegal op code, should not be encountered
		void CALL_FC_nn();	// CALL FC, nn
		void Illegal_op_code_DD(); // !!! Illegal op code, should not be encountered
		void SBC_A_n();		// SBC A, n
		void RST_18();		// RST 0x18
		// 0xE0 ~ 0xEF
		void LDH_mn_A();	// LDH (0xFF00 + n), A
		void POP_HL();		// POP HL
		void LD_mC_A();		// LD (0xFF00 + C), A
		void Illegal_op_code_E3(); // !!! Illegal op code, should not be encountered
		void Illegal_op_code_E4(); // !!! Illegal op code, should not be encountered
		void PUSH_HL();		// PUSH HL
		void AND_n();		// AND n
		void RST_20();		// RST 0x20
		void ADD_SP_n();	// ADD SP, n
		void JP_mHL();		// JP (HL)
		void LD_n_A();		// LD n, A
		void Illegal_op_code_EB(); // !!! Illegal op code, should not be encountered
		void Illegal_op_code_EC(); // !!! Illegal op code, should not be encountered
		void Illegal_op_code_ED(); // !!! Illegal op code, should not be encountered
		void XOR_n();		// XOR n
		void RST_28();		// RST 0x28
		// 0xF0 ~ 0xFF
		void LDH_A_mn();	// LDH A, (n)
		void POP_AF();		// POP AF
		void LD_A_mC();		// LD A, (C)
		void DI();			// DI
		void Illegal_op_code_F4(); // !!! Illegal op code, should not be encountered
		void PUSH_AF();		// PUSH AF
		void OR_n();		// OR n
		void RST_30();		// RST 0x30
		void LDHL_SP_n();	// LDHL SP, n
		void LD_SP_HL();	// LD SP HL
		void LD_A_mnn();	// LD A, (nn)
		void EI();			// EI
		void Illegal_op_code_FC(); // !!! Illegal op code, should not be encountered
		void Illegal_op_code_FD(); // !!! Illegal op code, should not be encountered
		void CP_n();		// CP n
		void RST_38();		// RST 0x38


		// 0xCB op codes

	};
}

