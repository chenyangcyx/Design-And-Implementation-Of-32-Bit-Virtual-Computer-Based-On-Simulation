#include "execute.h"

CExecute::CExecute()
{
	SetExecuteFree();	//设置执行类的状态为空闲
}

CExecute::~CExecute()
{
}

int CExecute::SetExecuteBusy()
{
	execute_state = EXECUTE_BUSY;
	return 0;
}

int CExecute::SetExecuteFree()
{
	execute_state = EXECUTE_FREE;
	return 0;
}

int CExecute::ReturnCurrentState(int &state)
{
	state = execute_state;
	return 0;
}

int CExecute::sign_extended(int &num)
{
	int sign = (num >> 15) & 1;  //取符号
	for (int i = 16; i <= 31; i++) {
		if (sign == 1) num |= (1 << i);
		else num &= ~(1 << i);
	}
	return 0;
}

int CExecute::zero_extended(int & num)
{
	for (int i = 16; i <= 31; i++) {
		num &= ~(1 << i);
	}
	return 0;
}

int CExecute::execute_addu(InstructionStruct data, int reg[])
{
	reg[data.rd] = (unsigned int)reg[data.rs] + (unsigned int)reg[data.rt];
	return 0;
}

int CExecute::execute_subu(InstructionStruct data, int reg[])
{
	reg[data.rd] = (unsigned int)reg[data.rs] - (unsigned int)reg[data.rt];
	return 0;
}

int CExecute::execute_and(InstructionStruct data, int reg[])
{
	reg[data.rd] = reg[data.rs] & reg[data.rt];
	return 0;
}

int CExecute::execute_or(InstructionStruct data, int reg[])
{
	reg[data.rd] = reg[data.rs] | reg[data.rt];
	return 0;
}

int CExecute::execute_xor(InstructionStruct data, int reg[])
{
	reg[data.rd] = reg[data.rs] ^ reg[data.rt];
	return 0;
}

int CExecute::execute_nor(InstructionStruct data, int reg[])
{
	reg[data.rd] = !(reg[data.rs] | reg[data.rt]);
	return 0;
}

int CExecute::execute_sll(InstructionStruct data, int reg[])
{
	reg[data.rd] = reg[data.rt] << data.shamt;
	return 0;
}

int CExecute::execute_srl(InstructionStruct data, int reg[])
{
	reg[data.rd] = reg[data.rt] >> data.shamt;
	return 0;
}

int CExecute::execute_jr(InstructionStruct data, int reg[], int &PC)
{
	PC = reg[data.rs];
	return 0;
}

int CExecute::execute_addi(InstructionStruct data, int reg[])
{
	int change = data.immediate;
	sign_extended(change);
	reg[data.rt] = reg[data.rs] + change;
	return 0;
}

int CExecute::execute_andi(InstructionStruct data, int reg[])
{
	int change = data.immediate;
	zero_extended(change);
	reg[data.rt] = reg[data.rs] & change;
	return 0;
}

int CExecute::execute_ori(InstructionStruct data, int reg[])
{
	int change = data.immediate;
	zero_extended(change);
	reg[data.rt] = reg[data.rs] | change;
	return 0;
}

int CExecute::execute_xori(InstructionStruct data, int reg[])
{
	int change = data.immediate;
	zero_extended(change);
	reg[data.rt] = reg[data.rs] ^ change;
	return 0;
}

int CExecute::execute_lw(InstructionStruct data, int reg[], char mem[])
{
	int change = data.immediate;
	sign_extended(change);
	reg[data.rt] = mem[reg[data.rs] + change];
	return 0;
}

int CExecute::execute_sw(InstructionStruct data, int reg[], char mem[])
{
	int change = data.immediate;
	sign_extended(change);
	mem[reg[data.rs] + change] = reg[data.rt];
	return 0;
}

int CExecute::execute_beq(InstructionStruct data, int reg[], int &PC)
{
	int change = data.immediate;
	sign_extended(change);
	if (reg[data.rs] == reg[data.rt])
		PC = PC + (change << 2);
	return 0;
}

int CExecute::execute_j(InstructionStruct data, int &PC)
{
	PC = data.address;
	return 0;
}

int CExecute::ExecuteControl(int instruction_type, InstructionStruct instruction_data, char memory[], int reg[], int & PC)
{
	int instruction_check = ExecuteControlCheckIfOk(instruction_type, instruction_data, memory, reg, PC);
	int action_check;
	if (instruction_check != EXECUTE_CONTROL_CHECK_SUCCESS)
		return instruction_check;
	else
	{
		action_check = ExecuteControlAction(instruction_type, instruction_data, memory, reg, PC);
		return action_check;
	}
}

int CExecute::ExecuteControlCheckIfOk(int instruction_type, InstructionStruct instruction_data, char memory[], int reg[], int & PC)
{
	//检测指令是否非法
	if (instruction_type == INSTRUCTION_TYPE_ERROR_CODE)
		return EXECUTE_CONTROL_TYPE_ERROR;
	switch (instruction_type)
	{
	case R_TYPE_ADDU_NO:
		//检测数据是否合法
		if (instruction_data.rd == RS_RT_RD_ERROR_CODE || instruction_data.rd > 31 || instruction_data.rd < 0)
			return EXECUTE_CONTROL_RD_ERROR;
		if (instruction_data.rs == RS_RT_RD_ERROR_CODE || instruction_data.rs > 31 || instruction_data.rs < 0)
			return EXECUTE_CONTROL_RS_ERROR;
		if (instruction_data.rt == RS_RT_RD_ERROR_CODE || instruction_data.rt > 31 || instruction_data.rt < 0)
			return EXECUTE_CONTROL_RT_ERROR;
		break;
	case R_TYPE_SUBU_NO:
		//检测数据是否合法
		if (instruction_data.rd == RS_RT_RD_ERROR_CODE || instruction_data.rd > 31 || instruction_data.rd < 0)
			return EXECUTE_CONTROL_RD_ERROR;
		if (instruction_data.rs == RS_RT_RD_ERROR_CODE || instruction_data.rs > 31 || instruction_data.rs < 0)
			return EXECUTE_CONTROL_RS_ERROR;
		if (instruction_data.rt == RS_RT_RD_ERROR_CODE || instruction_data.rt > 31 || instruction_data.rt < 0)
			return EXECUTE_CONTROL_RT_ERROR;
		break;
	case R_TYPE_AND_NO:
		//检测数据是否合法
		if (instruction_data.rd == RS_RT_RD_ERROR_CODE || instruction_data.rd > 31 || instruction_data.rd < 0)
			return EXECUTE_CONTROL_RD_ERROR;
		if (instruction_data.rs == RS_RT_RD_ERROR_CODE || instruction_data.rs > 31 || instruction_data.rs < 0)
			return EXECUTE_CONTROL_RS_ERROR;
		if (instruction_data.rt == RS_RT_RD_ERROR_CODE || instruction_data.rt > 31 || instruction_data.rt < 0)
			return EXECUTE_CONTROL_RT_ERROR;
		break;
	case R_TYPE_OR_NO:
		//检测数据是否合法
		if (instruction_data.rd == RS_RT_RD_ERROR_CODE || instruction_data.rd > 31 || instruction_data.rd < 0)
			return EXECUTE_CONTROL_RD_ERROR;
		if (instruction_data.rs == RS_RT_RD_ERROR_CODE || instruction_data.rs > 31 || instruction_data.rs < 0)
			return EXECUTE_CONTROL_RS_ERROR;
		if (instruction_data.rt == RS_RT_RD_ERROR_CODE || instruction_data.rt > 31 || instruction_data.rt < 0)
			return EXECUTE_CONTROL_RT_ERROR;
		break;
	case R_TYPE_XOR_NO:
		//检测数据是否合法
		if (instruction_data.rd == RS_RT_RD_ERROR_CODE || instruction_data.rd > 31 || instruction_data.rd < 0)
			return EXECUTE_CONTROL_RD_ERROR;
		if (instruction_data.rs == RS_RT_RD_ERROR_CODE || instruction_data.rs > 31 || instruction_data.rs < 0)
			return EXECUTE_CONTROL_RS_ERROR;
		if (instruction_data.rt == RS_RT_RD_ERROR_CODE || instruction_data.rt > 31 || instruction_data.rt < 0)
			return EXECUTE_CONTROL_RT_ERROR;
		break;
	case R_TYPE_NOR_NO:
		//检测数据是否合法
		if (instruction_data.rd == RS_RT_RD_ERROR_CODE || instruction_data.rd > 31 || instruction_data.rd < 0)
			return EXECUTE_CONTROL_RD_ERROR;
		if (instruction_data.rs == RS_RT_RD_ERROR_CODE || instruction_data.rs > 31 || instruction_data.rs < 0)
			return EXECUTE_CONTROL_RS_ERROR;
		if (instruction_data.rt == RS_RT_RD_ERROR_CODE || instruction_data.rt > 31 || instruction_data.rt < 0)
			return EXECUTE_CONTROL_RT_ERROR;
		break;
	case R_TYPE_SLL_NO:
		//检测数据是否合法
		if (instruction_data.rd == RS_RT_RD_ERROR_CODE || instruction_data.rd > 31 || instruction_data.rd < 0)
			return EXECUTE_CONTROL_RD_ERROR;
		if (instruction_data.rt == RS_RT_RD_ERROR_CODE || instruction_data.rt > 31 || instruction_data.rt < 0)
			return EXECUTE_CONTROL_RT_ERROR;
		if (instruction_data.shamt == SHAMT_ERROR_CODE || instruction_data.shamt > 31 || instruction_data.shamt < 0)
			return EXECUTE_CONTROL_SHAMT_ERROR;
		break;
	case R_TYPE_SRL_NO:
		//检测数据是否合法
		if (instruction_data.rd == RS_RT_RD_ERROR_CODE || instruction_data.rd > 31 || instruction_data.rd < 0)
			return EXECUTE_CONTROL_RD_ERROR;
		if (instruction_data.rt == RS_RT_RD_ERROR_CODE || instruction_data.rt > 31 || instruction_data.rt < 0)
			return EXECUTE_CONTROL_RT_ERROR;
		if (instruction_data.shamt == SHAMT_ERROR_CODE || instruction_data.shamt > 31 || instruction_data.shamt < 0)
			return EXECUTE_CONTROL_SHAMT_ERROR;
		break;
	case R_TYPE_JR_NO:
		//检测数据是否合法
		if (instruction_data.rs == RS_RT_RD_ERROR_CODE || instruction_data.rs > 31 || instruction_data.rs < 0)
			return EXECUTE_CONTROL_RS_ERROR;
		break;
	case I_TYPE_ADDI_NO:
		//检测数据是否合法
		if (instruction_data.rs == RS_RT_RD_ERROR_CODE || instruction_data.rs > 31 || instruction_data.rs < 0)
			return EXECUTE_CONTROL_RS_ERROR;
		if (instruction_data.rt == RS_RT_RD_ERROR_CODE || instruction_data.rt > 31 || instruction_data.rt < 0)
			return EXECUTE_CONTROL_RT_ERROR;
		if (instruction_data.immediate == IMMEDIATE_ADDRESS_ERROR_CODE || instruction_data.immediate > 65535 || instruction_data.immediate < 0)
			return EXECUTE_CONTROL_IMMEDIATE_ERROR;
		break;
	case I_TYPE_ANDI_NO:
		//检测数据是否合法
		if (instruction_data.rs == RS_RT_RD_ERROR_CODE || instruction_data.rs > 31 || instruction_data.rs < 0)
			return EXECUTE_CONTROL_RS_ERROR;
		if (instruction_data.rt == RS_RT_RD_ERROR_CODE || instruction_data.rt > 31 || instruction_data.rt < 0)
			return EXECUTE_CONTROL_RT_ERROR;
		if (instruction_data.immediate == IMMEDIATE_ADDRESS_ERROR_CODE || instruction_data.immediate > 65535 || instruction_data.immediate < 0)
			return EXECUTE_CONTROL_IMMEDIATE_ERROR;
		break;
	case I_TYPE_ORI_NO:
		//检测数据是否合法
		if (instruction_data.rs == RS_RT_RD_ERROR_CODE || instruction_data.rs > 31 || instruction_data.rs < 0)
			return EXECUTE_CONTROL_RS_ERROR;
		if (instruction_data.rt == RS_RT_RD_ERROR_CODE || instruction_data.rt > 31 || instruction_data.rt < 0)
			return EXECUTE_CONTROL_RT_ERROR;
		if (instruction_data.immediate == IMMEDIATE_ADDRESS_ERROR_CODE || instruction_data.immediate > 65535 || instruction_data.immediate < 0)
			return EXECUTE_CONTROL_IMMEDIATE_ERROR;
		break;
	case I_TYPE_XORI_NO:
		//检测数据是否合法
		if (instruction_data.rs == RS_RT_RD_ERROR_CODE || instruction_data.rs > 31 || instruction_data.rs < 0)
			return EXECUTE_CONTROL_RS_ERROR;
		if (instruction_data.rt == RS_RT_RD_ERROR_CODE || instruction_data.rt > 31 || instruction_data.rt < 0)
			return EXECUTE_CONTROL_RT_ERROR;
		if (instruction_data.immediate == IMMEDIATE_ADDRESS_ERROR_CODE || instruction_data.immediate > 65535 || instruction_data.immediate < 0)
			return EXECUTE_CONTROL_IMMEDIATE_ERROR;
		break;
	case I_TYPE_LW_NO:
		//检测数据是否合法
		if (instruction_data.rs == RS_RT_RD_ERROR_CODE || instruction_data.rs > 31 || instruction_data.rs < 0)
			return EXECUTE_CONTROL_RS_ERROR;
		if (instruction_data.rt == RS_RT_RD_ERROR_CODE || instruction_data.rt > 31 || instruction_data.rt < 0)
			return EXECUTE_CONTROL_RT_ERROR;
		if (instruction_data.immediate == IMMEDIATE_ADDRESS_ERROR_CODE || instruction_data.immediate > 65535 || instruction_data.immediate < 0)
			return EXECUTE_CONTROL_IMMEDIATE_ERROR;
		break;
	case I_TYPE_SW_NO:
		//检测数据是否合法
		if (instruction_data.rs == RS_RT_RD_ERROR_CODE || instruction_data.rs > 31 || instruction_data.rs < 0)
			return EXECUTE_CONTROL_RS_ERROR;
		if (instruction_data.rt == RS_RT_RD_ERROR_CODE || instruction_data.rt > 31 || instruction_data.rt < 0)
			return EXECUTE_CONTROL_RT_ERROR;
		if (instruction_data.immediate == IMMEDIATE_ADDRESS_ERROR_CODE || instruction_data.immediate > 65535 || instruction_data.immediate < 0)
			return EXECUTE_CONTROL_IMMEDIATE_ERROR;
		break;
	case I_TYPE_BEQ_NO:
		//检测数据是否合法
		if (instruction_data.rs == RS_RT_RD_ERROR_CODE || instruction_data.rs > 31 || instruction_data.rs < 0)
			return EXECUTE_CONTROL_RS_ERROR;
		if (instruction_data.rt == RS_RT_RD_ERROR_CODE || instruction_data.rt > 31 || instruction_data.rt < 0)
			return EXECUTE_CONTROL_RT_ERROR;
		if (instruction_data.immediate == IMMEDIATE_ADDRESS_ERROR_CODE || instruction_data.immediate > 65535 || instruction_data.immediate < 0)
			return EXECUTE_CONTROL_IMMEDIATE_ERROR;
		break;
	case J_TYPE_J_NO:
		//检测数据是否合法
		if (instruction_data.address == IMMEDIATE_ADDRESS_ERROR_CODE || (instruction_data.address > (MEMORY_INSTRUCTION_SIZE / 4 - 1)) || instruction_data.address < 0)
			return EXECUTE_CONTROL_ADDRESS_ERROR;
		break;
	default:
		return EXECUTE_CONTROL_TYPE_ERROR;
		break;
	}
	return EXECUTE_CONTROL_CHECK_SUCCESS;
}

int CExecute::ExecuteControlAction(int instruction_type, InstructionStruct instruction_data, char memory[], int reg[], int & PC)
{
	switch (instruction_type)
	{
	case R_TYPE_ADDU_NO:
		execute_addu(instruction_data, reg);
		break;
	case R_TYPE_SUBU_NO:
		execute_subu(instruction_data, reg);
		break;
	case R_TYPE_AND_NO:
		execute_and(instruction_data, reg);
		break;
	case R_TYPE_OR_NO:
		execute_or(instruction_data, reg);
		break;
	case R_TYPE_XOR_NO:
		execute_xor(instruction_data, reg);
		break;
	case R_TYPE_NOR_NO:
		execute_nor(instruction_data, reg);
		break;
	case R_TYPE_SLL_NO:
		execute_sll(instruction_data, reg);
		break;
	case R_TYPE_SRL_NO:
		execute_srl(instruction_data, reg);
		break;
	case R_TYPE_JR_NO:
		execute_jr(instruction_data, reg, PC);
		break;
	case I_TYPE_ADDI_NO:
		execute_addi(instruction_data, reg);
		break;
	case I_TYPE_ANDI_NO:
		execute_andi(instruction_data, reg);
		break;
	case I_TYPE_ORI_NO:
		execute_ori(instruction_data, reg);
		break;
	case I_TYPE_XORI_NO:
		execute_xori(instruction_data, reg);
		break;
	case I_TYPE_LW_NO:
		execute_lw(instruction_data, reg, memory);
		break;
	case I_TYPE_SW_NO:
		execute_sw(instruction_data, reg, memory);
		break;
	case I_TYPE_BEQ_NO:
		execute_beq(instruction_data, reg, PC);
		break;
	case J_TYPE_J_NO:
		execute_j(instruction_data, PC);
		break;
	default:
		return EXECUTE_CONTROL_TYPE_ERROR;
		break;
	}
	return EXECUTE_CONTROL_ACTION_SUCCESS;
}

string CExecute::KnowExecuteDetail(int instruction_type, InstructionStruct data, char mem[], int reg[], int & PC)
{
	string str = "";
	int change = 0;
	switch (instruction_type)
	{
	case R_TYPE_ADDU_NO:
		str = str + "(unsigned)" + ALLREGISTERNAME[data.rs] + " + (unsigned)" + ALLREGISTERNAME[data.rt];
		break;
	case R_TYPE_SUBU_NO:
		str = str + "(unsigned)" + ALLREGISTERNAME[data.rs] + " - (unsigned)" + ALLREGISTERNAME[data.rt];
		break;
	case R_TYPE_AND_NO:
		str = str + ALLREGISTERNAME[data.rs] + " AND " + ALLREGISTERNAME[data.rt];
		break;
	case R_TYPE_OR_NO:
		str = str + ALLREGISTERNAME[data.rs] + " OR " + ALLREGISTERNAME[data.rt];
		break;
	case R_TYPE_XOR_NO:
		str = str + ALLREGISTERNAME[data.rs] + " XOR " + ALLREGISTERNAME[data.rt];
		break;
	case R_TYPE_NOR_NO:
		str = str + ALLREGISTERNAME[data.rs] + " NOR " + ALLREGISTERNAME[data.rt];
		break;
	case R_TYPE_SLL_NO:
		str = str + ALLREGISTERNAME[data.rt] + " << " + to_string(data.shamt);
		break;
	case R_TYPE_SRL_NO:
		str = str + ALLREGISTERNAME[data.rt] + " >> " + to_string(data.shamt);
		break;
	case R_TYPE_JR_NO:
		str = str + "PC <- " + ALLREGISTERNAME[data.rt];
		break;
	case I_TYPE_ADDI_NO:
		change = data.immediate;
		sign_extended(change);
		str = str + ALLREGISTERNAME[data.rs] + " + " + to_string(change);
		break;
	case I_TYPE_ANDI_NO:
		change = data.immediate;
		zero_extended(change);
		str = str + ALLREGISTERNAME[data.rs] + " AND " + to_string(change);
		break;
	case I_TYPE_ORI_NO:
		change = data.immediate;
		zero_extended(change);
		str = str + ALLREGISTERNAME[data.rs] + " OR " + to_string(change);
		break;
	case I_TYPE_XORI_NO:
		change = data.immediate;
		zero_extended(change);
		str = str + ALLREGISTERNAME[data.rs] + " XOR " + to_string(change);
		break;
	case I_TYPE_LW_NO:
		change = data.immediate;
		sign_extended(change);
		str = str + "等待访存过程执行";
		break;
	case I_TYPE_SW_NO:
		change = data.immediate;
		sign_extended(change);
		str = str + "等待访存过程执行";
		break;
	case I_TYPE_BEQ_NO:
		change = data.immediate;
		sign_extended(change);
		if (reg[data.rs] == reg[data.rt])
			str = str + "PC + " + to_string(change) + "<<2";
		else str = str + "，寄存器值不相等，不执行";
		break;
	case J_TYPE_J_NO:
		str = str + to_string(data.address);
		break;
	default:
		return 0;
		break;
	}
	return str;
}

int CExecute::KnowExecuteResult(int instruction_type, InstructionStruct data, char mem[], int reg[], int & PC)
{
	int change = 0;
	switch (instruction_type)
	{
	case R_TYPE_ADDU_NO:
		return ((unsigned int)reg[data.rs] + (unsigned int)reg[data.rt]);
		break;
	case R_TYPE_SUBU_NO:
		return ((unsigned int)reg[data.rs] - (unsigned int)reg[data.rt]);
		break;
	case R_TYPE_AND_NO:
		return (reg[data.rs] & reg[data.rt]);
		break;
	case R_TYPE_OR_NO:
		return (reg[data.rs] | reg[data.rt]);
		break;
	case R_TYPE_XOR_NO:
		return (reg[data.rs] ^ reg[data.rt]);
		break;
	case R_TYPE_NOR_NO:
		return (!(reg[data.rs] | reg[data.rt]));
		break;
	case R_TYPE_SLL_NO:
		return (reg[data.rt] << data.shamt);
		break;
	case R_TYPE_SRL_NO:
		return (reg[data.rt] >> data.shamt);
		break;
	case R_TYPE_JR_NO:
		return (reg[data.rs]);
		break;
	case I_TYPE_ADDI_NO:
		change = data.immediate;
		sign_extended(change);
		return (reg[data.rs] + change);
		break;
	case I_TYPE_ANDI_NO:
		change = data.immediate;
		zero_extended(change);
		return (reg[data.rs] & change);
		break;
	case I_TYPE_ORI_NO:
		change = data.immediate;
		zero_extended(change);
		return (reg[data.rs] | change);
		break;
	case I_TYPE_XORI_NO:
		change = data.immediate;
		zero_extended(change);
		return (reg[data.rs] ^ change);
		break;
	case I_TYPE_LW_NO:
		change = data.immediate;
		sign_extended(change);
		return (mem[reg[data.rs] + change]);
		break;
	case I_TYPE_SW_NO:
		change = data.immediate;
		sign_extended(change);
		return (reg[data.rs] + change);
		break;
	case I_TYPE_BEQ_NO:
		change = data.immediate;
		sign_extended(change);
		if (reg[data.rs] == reg[data.rt])
			return (PC + (change << 2));
		else return 0;
		break;
	case J_TYPE_J_NO:
		return (data.address);
		break;
	default:
		return 0;
		break;
	}
	return 0;
}

int CExecute::KnowMemoryReadContent(int instruction_type, InstructionStruct data, char mem[], int reg[])
{
	int change = 0;
	switch (instruction_type)
	{
	case I_TYPE_LW_NO:
		change = data.immediate;
		sign_extended(change);
		return mem[reg[data.rs] + change];
	case I_TYPE_SW_NO:
		change = data.immediate;
		sign_extended(change);
		return mem[reg[data.rs] + change];
	default:
		return 0;
		break;
	}
	return 0;
}

string CExecute::KnowWhichToWriteTo(int instruction_type, InstructionStruct data, char mem[], int reg[])
{
	string str = "";
	int change = 0;
	switch (instruction_type)
	{
	case R_TYPE_ADDU_NO:
		str = str + ALLREGISTERNAME[data.rd];
		break;
	case R_TYPE_SUBU_NO:
		str = str + ALLREGISTERNAME[data.rd];
		break;
	case R_TYPE_AND_NO:
		str = str + ALLREGISTERNAME[data.rd];
		break;
	case R_TYPE_OR_NO:
		str = str + ALLREGISTERNAME[data.rd];
		break;
	case R_TYPE_XOR_NO:
		str = str + ALLREGISTERNAME[data.rd];
		break;
	case R_TYPE_NOR_NO:
		str = str + ALLREGISTERNAME[data.rd];
		break;
	case R_TYPE_SLL_NO:
		str = str + ALLREGISTERNAME[data.rd];
		break;
	case R_TYPE_SRL_NO:
		str = str + ALLREGISTERNAME[data.rd];
		break;
	case R_TYPE_JR_NO:
		str = str + "PC";
		break;
	case I_TYPE_ADDI_NO:
		str = str + ALLREGISTERNAME[data.rt];
		break;
	case I_TYPE_ANDI_NO:
		str = str + ALLREGISTERNAME[data.rt];
		break;
	case I_TYPE_ORI_NO:
		str = str + ALLREGISTERNAME[data.rt];
		break;
	case I_TYPE_XORI_NO:
		str = str + ALLREGISTERNAME[data.rt];
		break;
	case I_TYPE_LW_NO:
		str = str + ALLREGISTERNAME[data.rt];
		break;
	case I_TYPE_SW_NO:
		change = data.immediate;
		sign_extended(change);
		str = str + "MEMORY[" + to_string(reg[data.rs] + change) + "]";
		break;
	case I_TYPE_BEQ_NO:
		change = data.immediate;
		sign_extended(change);
		if (reg[data.rs] == reg[data.rt])
			str = str + "PC";
		else str = str + "，寄存器值不相等，不写回";
		break;
	case J_TYPE_J_NO:
		str = str + "PC";
		break;
	default:
		return 0;
		break;
	}
	return str;
}
