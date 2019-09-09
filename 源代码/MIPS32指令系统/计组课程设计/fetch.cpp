#include "fetch.h"

CFetch::CFetch()
{
	SetFetchFree();	//将取指状态默认设置为空闲
	PC = FETCH_PC_INIT_DATA;	//初始化PC指针的值
}

CFetch::~CFetch()
{
}

int CFetch::SetFetchBusy()
{
	fetch_state = FETCH_BUSY;
	return 0;
}

int CFetch::SetFetchFree()
{
	fetch_state = FETCH_FREE;
	return 0;
}

int CFetch::ReturnCurrentState(int &state)
{
	state = fetch_state;
	return 0;
}

int CFetch::GetPC()
{
	return PC;
}

int CFetch::PCSelfAdd()
{
	PC += PC_ADD_VALUE;
	return 0;
}

int CFetch::EditPC(int edit_num)
{
	PC = edit_num;
	return 0;
}

int CFetch::ResetPC()
{
	PC = FETCH_PC_INIT_DATA;
	return 0;
}

int CFetch::FetchInstructionFromMemory(int memory_num, char mem[], int &instruction_data)
{
	char data;
	unsigned int data_transfer;
	for (int i = 0; i < 4; i++)
	{
		data = mem[memory_num + i];
		data_transfer = (unsigned int)data;
		data_transfer &= 0x00ff;	//去掉前面的符号位扩展
		instruction_data |= (data_transfer << (8 * (3 - i)));
	}
	return 0;
}