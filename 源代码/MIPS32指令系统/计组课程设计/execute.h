#pragma once

#include <string>
#include "overalldata.h"
using namespace std;

class CExecute
{
private:
	int execute_state;	//当前执行的状态
	int instruction_num;	//当前指令数量
public:
	CExecute();	//默认构造函数
	~CExecute();	//析构函数
	int SetExecuteBusy();	//设置当前执行的状态为忙碌
	int SetExecuteFree();	//设置当前执行的状态为空闲
	int ReturnCurrentState(int &);	//返回取指类当前状态
	int sign_extended(int &);	//对数据进行符号位扩展
	int zero_extended(int &);	//对数据进行0扩展
	//R-Type
	int execute_addu(InstructionStruct, int[]);	//addu指令
	int execute_subu(InstructionStruct, int[]);	//subu指令
	int execute_and(InstructionStruct, int[]);	//and指令
	int execute_or(InstructionStruct, int[]);	//or指令
	int execute_xor(InstructionStruct, int[]);	//xor指令
	int execute_nor(InstructionStruct, int[]);	//nor指令
	int execute_sll(InstructionStruct, int[]);	//sll指令
	int execute_srl(InstructionStruct, int[]);	//srl指令
	int execute_jr(InstructionStruct, int[], int &);	//jr指令
	//I-Type
	int execute_addi(InstructionStruct, int[]);	//addi指令
	int execute_andi(InstructionStruct, int[]);	//andi指令
	int execute_ori(InstructionStruct, int[]);	//ori指令
	int execute_xori(InstructionStruct, int[]);	//xori指令
	int execute_lw(InstructionStruct, int[], char[]);	//lw指令
	int execute_sw(InstructionStruct, int[], char[]);	//sw指令
	int execute_beq(InstructionStruct, int[], int &);	//beq指令
	//J-Type
	int execute_j(InstructionStruct, int &);	//j指令

	//指令执行控制
	int ExecuteControl(int instruction_type, InstructionStruct instruction_data, char memory[], int reg[], int &PC);
	int ExecuteControlCheckIfOk(int instruction_type, InstructionStruct instruction_data, char memory[], int reg[], int &PC);
	int ExecuteControlAction(int instruction_type, InstructionStruct instruction_data, char memory[], int reg[], int &PC);

	//指令过程预知
	string KnowExecuteDetail(int instruction_type, InstructionStruct data, char mem[], int reg[], int &PC);
	int KnowExecuteResult(int instruction_type, InstructionStruct data, char mem[], int reg[], int &PC);
	int KnowMemoryReadContent(int instruction_type, InstructionStruct data, char mem[], int reg[]);
	string KnowWhichToWriteTo(int instruction_type, InstructionStruct data, char mem[], int reg[]);
};