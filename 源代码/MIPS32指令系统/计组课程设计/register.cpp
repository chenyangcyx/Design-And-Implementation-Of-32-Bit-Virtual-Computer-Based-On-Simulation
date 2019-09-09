#include "register.h"

CRegister::CRegister()
{
	SetRegisterFree();	//寄存器开始默认不被使用
	InitAllRegisterWith0();	//将所有寄存器默认初始为0
	reg[0] = 0;	//$0恒为0
}

CRegister::~CRegister()
{
}

int CRegister::SetRegisterBusy()
{
	register_state = REGISTER_BUSY;
	return 0;
}

int CRegister::SetRegisterFree()
{
	register_state = REGISTER_FREE;
	return 0;
}

int CRegister::ReturnCurrentState(int &state)
{
	state = register_state;
	return 0;
}

int CRegister::InitAllRegisterWithValue(int init_num)	//注意！$0恒为0，不能够初始化
{
	for (int i = 1/*将$0寄存器排除*/; i < REGISTER_NUM; i++)
		reg[i] = init_num;
	return 0;
}

int CRegister::InitAllRegisterWith0()	//注意！$0恒为0，不能够初始化
{
	for (int i = 1/*将$0寄存器排除*/; i < REGISTER_NUM; i++)
		reg[i] = 0;
	return 0;
}

int CRegister::WriteToOneRegister(int register_num, int write_num)
{
	reg[register_num] = write_num;
	return 0;
}

int CRegister::ReadFromOneRegister(int register_num, int &read_data)
{
	read_data = reg[register_num];
	return 0;
}