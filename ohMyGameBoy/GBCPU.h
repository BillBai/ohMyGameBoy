#pragma once

#include "GBTypes.h"
#include "GBMemoryUnit.h"

namespace GameBoy {
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
		bool getZeroFlag()		const { return regFlag & 0x80; }
		bool getSubtractFlag()	const { return regFlag & 0x40; }
		bool getHalfCarryFlag() const { return regFlag & 0x20; }
		bool getCarryFlag()		const { return regFlag & 0x10; }

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
		void setZeroFlag()			{ regFlag = regFlag | 0x80; }
		void clearZeroFlag()		{ regFlag = regFlag & 0x7F; }
		void setSubtractFlag()		{ regFlag = regFlag | 0x40; }
		void clearSubtractFlag()	{ regFlag = regFlag & 0xBF; }
		void setHalfCarryFlag()		{ regFlag = regFlag | 0x20; }
		void clearHalfCarryFlag()	{ regFlag = regFlag & 0xDF; }
		void setCarryFlag()			{ regFlag = regFlag | 0x10; }
		void clearCarryFlag()		{ regFlag = regFlag & 0xEF; }

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
		void DEC_A();		// 0x3B DEC A
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

	};
}

