#include "decoding.h"

CDecoding::CDecoding()
{
	SetDecodingFree();	//默认设置译码为空闲
}

CDecoding::~CDecoding()
{
}

int CDecoding::SetDecodingBusy()
{
	decoding_state = DECODING_BUSY;
	return 0;
}

int CDecoding::SetDecodingFree()
{
	decoding_state = DECODING_FREE;
	return 0;
}

int CDecoding::ReturnCurrentState(int &state)
{
	state = decoding_state;
	return 0;
}

int CDecoding::BitSelectTransform(int instruction, int m, int n, int &result)
{
	int bit, bitnum = 0;
	for (int i = m; i <= n; i++)
	{
		bit = (instruction >> i) & 1;
		if (bit == 1)
			bitnum |= (1 << (i - m));
		else if (bit == 0)
			bitnum &= (~(1 << (i - m)));
	}
	result = bitnum;
	return 0;
}

int CDecoding::InstructionsDecoding(int instru, InstructionStruct &data,int &instru_type)
{
	int op, rs, rt, rd, shamt, func, immediate, address;
	BitSelectTransform(instru, 26, 31, op);
	BitSelectTransform(instru, 21, 25, rs);
	BitSelectTransform(instru, 16, 20, rt);
	BitSelectTransform(instru, 11, 15, rd);
	BitSelectTransform(instru, 6, 10, shamt);
	BitSelectTransform(instru, 0, 5, func);
	BitSelectTransform(instru, 0, 15, immediate);
	BitSelectTransform(instru, 0, 25, address);
	switch (op)
	{
	case R_TYPE_OP:	//R-Type
		switch (func)
		{
		case R_TYPE_ADDU_FUNC:	//R-Type addu指令
			data.rs = rs;
			data.rt = rt;
			data.rd = rd;
			data.shamt = SHAMT_ERROR_CODE;
			data.immediate = IMMEDIATE_ADDRESS_ERROR_CODE;
			data.address = IMMEDIATE_ADDRESS_ERROR_CODE;
			instru_type = R_TYPE_ADDU_NO;
			break;
		case R_TYPE_SUBU_FUNC:	//R-Type subu指令
			data.rs = rs;
			data.rt = rt;
			data.rd = rd;
			data.shamt = SHAMT_ERROR_CODE;
			data.immediate = IMMEDIATE_ADDRESS_ERROR_CODE;
			data.address = IMMEDIATE_ADDRESS_ERROR_CODE;
			instru_type = R_TYPE_SUBU_NO;
			break;
		case R_TYPE_AND_FUNC:	//R-Type and指令
			data.rs = rs;
			data.rt = rt;
			data.rd = rd;
			data.shamt = SHAMT_ERROR_CODE;
			data.immediate = IMMEDIATE_ADDRESS_ERROR_CODE;
			data.address = IMMEDIATE_ADDRESS_ERROR_CODE;
			instru_type = R_TYPE_AND_NO;
			break;
		case R_TYPE_OR_FUNC:	//R-Type or指令
			data.rs = rs;
			data.rt = rt;
			data.rd = rd;
			data.shamt = SHAMT_ERROR_CODE;
			data.immediate = IMMEDIATE_ADDRESS_ERROR_CODE;
			data.address = IMMEDIATE_ADDRESS_ERROR_CODE;
			instru_type = R_TYPE_OR_NO;
			break;
		case R_TYPE_XOR_FUNC:	//R-Type xor指令
			data.rs = rs;
			data.rt = rt;
			data.rd = rd;
			data.shamt = SHAMT_ERROR_CODE;
			data.immediate = IMMEDIATE_ADDRESS_ERROR_CODE;
			data.address = IMMEDIATE_ADDRESS_ERROR_CODE;
			instru_type = R_TYPE_XOR_NO;
			break;
		case R_TYPE_NOR_FUNC:	//R-Type nor指令
			data.rs = rs;
			data.rt = rt;
			data.rd = rd;
			data.shamt = SHAMT_ERROR_CODE;
			data.immediate = IMMEDIATE_ADDRESS_ERROR_CODE;
			data.address = IMMEDIATE_ADDRESS_ERROR_CODE;
			instru_type = R_TYPE_NOR_NO;
			break;
		case R_TYPE_SLL_FUNC:	//R-Type sll指令
			data.rs = 0x00;
			data.rt = rt;
			data.rd = rd;
			data.shamt = shamt;
			data.immediate = IMMEDIATE_ADDRESS_ERROR_CODE;
			data.address = IMMEDIATE_ADDRESS_ERROR_CODE;
			instru_type = R_TYPE_SLL_NO;
			break;
		case R_TYPE_SRL_FUNC:	//R-Type srl指令
			data.rs = 0x00;
			data.rt = rt;
			data.rd = rd;
			data.shamt = shamt;
			data.immediate = IMMEDIATE_ADDRESS_ERROR_CODE;
			data.address = IMMEDIATE_ADDRESS_ERROR_CODE;
			instru_type = R_TYPE_SRL_NO;
			break;
		case R_TYPE_JR_FUNC:	//R-Type jr指令
			data.rs = rs;
			data.rt = RS_RT_RD_ERROR_CODE;
			data.rd = RS_RT_RD_ERROR_CODE;
			data.shamt = SHAMT_ERROR_CODE;
			data.immediate = IMMEDIATE_ADDRESS_ERROR_CODE;
			data.address = IMMEDIATE_ADDRESS_ERROR_CODE;
			instru_type = R_TYPE_JR_NO;
			break;
		}
		break;
	case I_TYPE_ADDI:	//I-Type addi指令
		data.rs = rs;
		data.rt = rt;
		data.immediate = immediate;
		data.rd = RS_RT_RD_ERROR_CODE;
		data.shamt = SHAMT_ERROR_CODE;
		data.address = IMMEDIATE_ADDRESS_ERROR_CODE;
		instru_type = I_TYPE_ADDI_NO;
		break;
	case I_TYPE_ANDI:	//I-Type andi指令
		data.rs = rs;
		data.rt = rt;
		data.immediate = immediate;
		data.rd = RS_RT_RD_ERROR_CODE;
		data.shamt = SHAMT_ERROR_CODE;
		data.address = IMMEDIATE_ADDRESS_ERROR_CODE;
		instru_type = I_TYPE_ANDI_NO;
		break;
	case I_TYPE_ORI:	//I-Type ori指令
		data.rs = rs;
		data.rt = rt;
		data.immediate = immediate;
		data.rd = RS_RT_RD_ERROR_CODE;
		data.shamt = SHAMT_ERROR_CODE;
		data.address = IMMEDIATE_ADDRESS_ERROR_CODE;
		instru_type = I_TYPE_ORI_NO;
		break;
	case I_TYPE_XORI:	//I-Type xori指令
		data.rs = rs;
		data.rt = rt;
		data.immediate = immediate;
		data.rd = RS_RT_RD_ERROR_CODE;
		data.shamt = SHAMT_ERROR_CODE;
		data.address = IMMEDIATE_ADDRESS_ERROR_CODE;
		instru_type = I_TYPE_XORI_NO;
		break;
	case I_TYPE_LW:		//I-Type lw指令
		data.rs = rs;
		data.rt = rt;
		data.immediate = immediate;
		data.rd = RS_RT_RD_ERROR_CODE;
		data.shamt = SHAMT_ERROR_CODE;
		data.address = IMMEDIATE_ADDRESS_ERROR_CODE;
		instru_type = I_TYPE_LW_NO;
		break;
	case I_TYPE_SW:		//I-Type sw指令
		data.rs = rs;
		data.rt = rt;
		data.immediate = immediate;
		data.rd = RS_RT_RD_ERROR_CODE;
		data.shamt = SHAMT_ERROR_CODE;
		data.address = IMMEDIATE_ADDRESS_ERROR_CODE;
		instru_type = I_TYPE_SW_NO;
		break;
	case I_TYPE_BEQ:	//I-Type beq指令
		data.rs = rs;
		data.rt = rt;
		data.immediate = immediate;
		data.rd = RS_RT_RD_ERROR_CODE;
		data.shamt = SHAMT_ERROR_CODE;
		data.address = IMMEDIATE_ADDRESS_ERROR_CODE;
		instru_type = I_TYPE_BEQ_NO;
		break;
	case J_TYPE_J:		//J-Type j指令
		data.address = address;
		data.rs = RS_RT_RD_ERROR_CODE;
		data.rt = RS_RT_RD_ERROR_CODE;
		data.rd = RS_RT_RD_ERROR_CODE;
		data.shamt = SHAMT_ERROR_CODE;
		data.immediate = IMMEDIATE_ADDRESS_ERROR_CODE;
		instru_type = J_TYPE_J_NO;
		break;
	default:
		data.rs = RS_RT_RD_ERROR_CODE;
		data.rt = RS_RT_RD_ERROR_CODE;
		data.rd = RS_RT_RD_ERROR_CODE;
		data.shamt = SHAMT_ERROR_CODE;
		data.immediate = IMMEDIATE_ADDRESS_ERROR_CODE;
		data.address = IMMEDIATE_ADDRESS_ERROR_CODE;
		instru_type = INSTRUCTION_TYPE_ERROR_CODE;
		break;
	}
	return 0;
}

bool CDecoding::InstructionCheckZero(int instruction_type, InstructionStruct data)
{
	switch (instruction_type)
	{
	case R_TYPE_ADDU_NO:
	case R_TYPE_SUBU_NO:
	case R_TYPE_AND_NO:
	case R_TYPE_OR_NO:
	case R_TYPE_XOR_NO:
	case R_TYPE_NOR_NO:
	case R_TYPE_SLL_NO:
	case R_TYPE_SRL_NO:
		if (data.rd == 0)
			return true;
		break;
	case R_TYPE_JR_NO:
		break;
	case I_TYPE_ADDI_NO:
	case I_TYPE_ANDI_NO:
	case I_TYPE_ORI_NO:
	case I_TYPE_XORI_NO:
	case I_TYPE_LW_NO:
		if (data.rt == 0)
			return true;
		break;
	case I_TYPE_SW_NO:
		break;
	case I_TYPE_BEQ_NO:
	case J_TYPE_J_NO:
		break;
	default:
		break;
	}
	return false;
}
