#include "log.h"

CLog::CLog()
{
	//初始化寄存器名字
	InitRegName();
	//初始化ifnew变量
	ifnew = true;
	//初始化记录数量
	InitLogNo();
}

CLog::~CLog()
{
}

int CLog::InitRegName()
{
	strcpy(regname[0], "$zero");
	strcpy(regname[1], "$at");
	strcpy(regname[2], "$v0");
	strcpy(regname[3], "$v1");
	strcpy(regname[4], "$a0");
	strcpy(regname[5], "$a1");
	strcpy(regname[6], "$a2");
	strcpy(regname[7], "$a3");
	strcpy(regname[8], "$t0");
	strcpy(regname[9], "$t1");
	strcpy(regname[10], "$t2");
	strcpy(regname[11], "$t3");
	strcpy(regname[12], "$t4");
	strcpy(regname[13], "$t5");
	strcpy(regname[14], "$t6");
	strcpy(regname[15], "$t7");
	strcpy(regname[16], "$s0");
	strcpy(regname[17], "$s1");
	strcpy(regname[18], "$s2");
	strcpy(regname[19], "$s3");
	strcpy(regname[20], "$s4");
	strcpy(regname[21], "$s5");
	strcpy(regname[22], "$s6");
	strcpy(regname[23], "$s7");
	strcpy(regname[24], "$t8");
	strcpy(regname[25], "$t9");
	strcpy(regname[26], "$k0");
	strcpy(regname[27], "$k1");
	strcpy(regname[28], "$gp");
	strcpy(regname[29], "$sp");
	strcpy(regname[30], "$fp");
	strcpy(regname[31], "$ra");
	return 0;
}

string CLog::GetRegisterName(int reg_no)
{
	string str;
	str = regname[reg_no];
	return str;
}

int CLog::InitLogNo()
{
	current_log_no = 1;
	return 0;
}

string CLog::GetInstructionLogDetail(int instruction_type, InstructionStruct data)
{
	string str = "";
	switch (instruction_type)
	{
	case R_TYPE_ADDU_NO:
		str = str + to_string(current_log_no) + "-\t";
		str = str + "addu rd, rs, rt\t" + "rd <- rs + rt" + "\n";
		str = str + "\t" + "rd=" + regname[data.rd] + ", rs=" + regname[data.rs] + ", rt=" + regname[data.rt] + "\n";
		break;
	case R_TYPE_SUBU_NO:
		str = str +  to_string(current_log_no) + "-\t";
		str = str +  "subu rd, rs, rt\t" + "rd <- rs - rt" + "\n";
		str = str +  "\t" + "rd=" + regname[data.rd] + ", rs=" + regname[data.rs] + ", rt=" + regname[data.rt] + "\n";
		break;
	case R_TYPE_AND_NO:
		str = str +  to_string(current_log_no) + "-\t";
		str = str +  "and rd, rs, rt\t" + "rd <- rs & rt" + "\n";
		str = str +  "\t" + "rd=" + regname[data.rd] + ", rs=" + regname[data.rs] + ", rt=" + regname[data.rt] + "\n";
		break;
	case R_TYPE_OR_NO:
		str = str +  to_string(current_log_no) + "-\t";
		str = str +  "or rd, rs, rt\t" + "rd <- rs | rt" + "\n";
		str = str +  "\t" + "rd=" + regname[data.rd] + ", rs=" + regname[data.rs] + ", rt=" + regname[data.rt] + "\n";
		break;
	case R_TYPE_XOR_NO:
		str = str +  to_string(current_log_no) + "-\t";
		str = str +  "xor rd, rs, rt\t" + "rd <- rs ^ rt" + "\n";
		str = str +  "\t" + "rd=" + regname[data.rd] + ", rs=" + regname[data.rs] + ", rt=" + regname[data.rt] + "\n";
		break;
	case R_TYPE_NOR_NO:
		str = str +  to_string(current_log_no) + "-\t";
		str = str +  "nor rd, rs, rt\t" + "rd <- ~(rs | rt)" + "\n";
		str = str +  "\t" + "rd=" + regname[data.rd] + ", rs=" + regname[data.rs] + ", rt=" + regname[data.rt] + "\n";
		break;
	case R_TYPE_SLL_NO:
		str = str +  to_string(current_log_no) + "-\t";
		str = str +  "sll rd, rt, shamt\t" + "rd <- rt + shamt" + "\n";
		str = str +  "\t" + "rd=" + regname[data.rd] + ", rt=" + regname[data.rt] + ", shamt=" + to_string((int)data.shamt) + "\n";
		break;
	case R_TYPE_SRL_NO:
		str = str +  to_string(current_log_no) + "-\t";
		str = str +  "srl rd, rt, shamt\t" + "rd <- rt >> shamt" + "\n";
		str = str +  "\t" + "rd=" + regname[data.rd] + ", rt=" + regname[data.rt] + ", shamt=" + to_string((int)data.shamt) + "\n";
		break;
	case R_TYPE_JR_NO:
		str = str +  to_string(current_log_no) + "-\t";
		str = str +  "jr rs\t" + "PC <- rs" + "\n";
		str = str +  "\t" + "rs=" + regname[data.rs] + "\n";
		break;
	case I_TYPE_ADDI_NO:
		str = str +  to_string(current_log_no) + "-\t";
		str = str +  "addi rs, rt, imm\t" + "rt <- rs + (sign-extend)immediate" + "\n";
		str = str +  "\t" + "rs=" + regname[data.rs] + ", rt=" + regname[data.rt] + ", imm=" + to_string(data.immediate) + "\n";
		break;
	case I_TYPE_ANDI_NO:
		str = str +  to_string(current_log_no) + "-\t";
		str = str +  "andi rs, rt, imm\t" + "rt <- rs & (zero-extend)immediate" + "\n";
		str = str +  "\t" + "rs=" + regname[data.rs] + ", rt=" + regname[data.rt] + ", imm=" + to_string(data.immediate) + "\n";
		break;
	case I_TYPE_ORI_NO:
		str = str +  to_string(current_log_no) + "-\t";
		str = str +  "ori rs, rt, imm\t" + "rt <- rs | (zero-extend)immediate" + "\n";
		str = str +  "\t" + "rs=" + regname[data.rs] + ", rt=" + regname[data.rt] + ", imm=" + to_string(data.immediate) + "\n";
		break;
	case I_TYPE_XORI_NO:
		str = str +  to_string(current_log_no) + "-\t";
		str = str +  "xori rs, rt, imm\t" + "rt <- rs ^ (zero-extend)immediate" + "\n";
		str = str +  "\t" + "rs=" + regname[data.rs] + ", rt=" + regname[data.rt] + ", imm=" + to_string(data.immediate) + "\n";
		break;
	case I_TYPE_LW_NO:
		str = str +  to_string(current_log_no) + "-\t";
		str = str +  "lw rt, imm\t" + "rt <- memory[rs + (sign-extend)immediate]" + "\n";
		str = str +  "\t" + "rt=" + regname[data.rt] + ", rs=" + regname[data.rs] + ", imm=" + to_string(data.immediate) + "\n";
		break;
	case I_TYPE_SW_NO:
		str = str +  to_string(current_log_no) + "-\t";
		str = str +  "sw rt, imm\t" + "memory[rs + (sign-extend)immediate] <- rt" + "\n";
		str = str +  "\t" + "rs=" + regname[data.rs] + ", rt=" + regname[data.rt] + ", imm=" + to_string(data.immediate) + "\n";
		break;
	case I_TYPE_BEQ_NO:
		str = str +  to_string(current_log_no) + "-\t";
		str = str +  "beq rs, rt, imm\t" + "if (rs == rt) PC <- PC + 4 + (sign-extend)immediate + 2" + "\n";
		str = str +  "\t" + "rs=" + regname[data.rs] + ", rt=" + regname[data.rt] + ", imm=" + to_string(data.immediate) + "\n";
		break;
	case J_TYPE_J_NO:
		str = str +  to_string(current_log_no) + "-\t";
		str = str +  "j address\t" + "PC <- address" + "\n";
		str = str +  "\t" + "address=" + to_string(data.address) + "\n";
		break;
	default:
		str = str + to_string(current_log_no) + "-\t";
		str = str + "error instruction\t" + "can not decode";
		break;
	}
	return str;
}

int CLog::WriteLog(int instruction_type, InstructionStruct data)
{
	//初始化FILE文件指针，读取、写入、初始位置文件尾
	logfile.open("record.txt", ios::out | ios::app);
	if (ifnew == false)	//进行第二轮输入，则空两行
		logfile << endl;
	ifnew = false;	//已经开始写入
	time_t calendar_time = time(NULL);
	struct tm * tm_local = localtime(&calendar_time);
	char time_str[100];	//字符串，存储时间
	strftime(time_str, sizeof(time_str), "%G-%m-%d %H:%M:%S", tm_local);
	logfile << "执行时间：" << time_str << endl;
	string str = GetInstructionLogDetail(instruction_type, data);
	logfile << str;
	current_log_no++;
	logfile.close();
	return 0;
}

void CLog::LogBegin()
{
	logfile.open("record.txt", ios::out | ios::app);
	logfile << "-------BEGIN-------" << endl << endl;
	InitLogNo();
	logfile.close();
}

void CLog::LogEnd()
{
	logfile.open("record.txt", ios::out | ios::app);
	logfile << endl << "-------END-------" << endl << endl << endl;
	InitLogNo();
	ifnew = true;
	logfile.close();
}

void CLog::ClearLog()
{
	logfile.open("record.txt", ios::trunc);	//清空文件内容
	logfile.close();
}

string CLog::GetInstructionString(int instruction_type, InstructionStruct data)
{
	string str = "";
	switch (instruction_type)
	{
	case R_TYPE_ADDU_NO:
		str = str + "addu " + regname[data.rd] + ", " + regname[data.rs] + ", " + regname[data.rt];
		break;
	case R_TYPE_SUBU_NO:
		str = str + "subu " + regname[data.rd] + ", " + regname[data.rs] + ", " + regname[data.rt];
		break;
	case R_TYPE_AND_NO:
		str = str + "and " + regname[data.rd] + ", " + regname[data.rs] + ", " + regname[data.rt];
		break;
	case R_TYPE_OR_NO:
		str = str + "or " + regname[data.rd] + ", " + regname[data.rs] + ", " + regname[data.rt];
		break;
	case R_TYPE_XOR_NO:
		str = str + "xor " + regname[data.rd] + ", " + regname[data.rs] + ", " + regname[data.rt];
		break;
	case R_TYPE_NOR_NO:
		str = str + "nor " + regname[data.rd] + ", " + regname[data.rs] + ", " + regname[data.rt];
		break;
	case R_TYPE_SLL_NO:
		str = str + "sll " + regname[data.rd] + ", " + regname[data.rt] + ", " + to_string((int)data.shamt);
		break;
	case R_TYPE_SRL_NO:
		str = str + "srl " + regname[data.rd] + ", " + regname[data.rt] + ", " + to_string((int)data.shamt);
		break;
	case R_TYPE_JR_NO:
		str = str + "jr " + regname[data.rs];
		break;
	case I_TYPE_ADDI_NO:
		str = str + "addi " + regname[data.rs] + ", " + regname[data.rt] + ", " + to_string(data.immediate);
		break;
	case I_TYPE_ANDI_NO:
		str = str + "andi " + regname[data.rs] + ", " + regname[data.rt] + ", " + to_string(data.immediate);
		break;
	case I_TYPE_ORI_NO:
		str = str + "ori " + regname[data.rs] + ", " + regname[data.rt] + ", " + to_string(data.immediate);
		break;
	case I_TYPE_XORI_NO:
		str = str + "xori " + regname[data.rs] + ", " + regname[data.rt] + ", " + to_string(data.immediate);
		break;
	case I_TYPE_LW_NO:
		str = str + "lw " + regname[data.rt] + ", " + to_string(data.immediate);
		break;
	case I_TYPE_SW_NO:
		str = str + "sw " + regname[data.rt] + ", " + to_string(data.immediate);
		break;
	case I_TYPE_BEQ_NO:
		str = str + "beq " + regname[data.rs] + ", " + regname[data.rt] + ", " + to_string(data.immediate);
		break;
	case J_TYPE_J_NO:
		str = str + "j " + to_string(data.address);
		break;
	default:
		str = str + "error instruction, can not decode";
		break;
	}
	return str;
}