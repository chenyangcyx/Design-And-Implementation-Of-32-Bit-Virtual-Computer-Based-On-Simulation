#include "memory.h"

CMemory::CMemory()
{
	SetMemoryFree();	//内存默认为空闲状态
	InitAllMemoryWithValue(MEMORY_INIT_DATA);	//默认初始化全部内存为0
	instruction_size = MEMORY_INSTRUCTION_SIZE;	//存放指令区域大小
	data_size = MEMORY_DATA_SIZE;	//存放数据区域大小
	current_instruction_address = 0;	//指令区域当前的起始位置
}

CMemory::~CMemory()
{
}

int CMemory::SetMemoryBusy()
{
	memory_state = MEMORY_BUSY;
	return 0;
}

int CMemory::SetMemoryFree()
{
	memory_state = MEMORY_FREE;
	return 0;
}

int CMemory::ReturnCurrentState(int &state)
{
	state = memory_state;
	return 0;
}

int CMemory::InitAllMemoryWith0()
{
	for (int i = instruction_size; i < MEMORY_NUM; i++)
		mem[i] = 0;
	return 0;
}

int CMemory::InitAllMemoryWithValue(int init_num)
{
	for (int i = instruction_size; i < MEMORY_NUM; i++)
		mem[i] = init_num;
	return 0;
}

int CMemory::WriteToMemory(int memory_num, char write_data)
{
	mem[memory_num] = write_data;
	return 0;
}

int CMemory::ReadFromMemory(int memory_num, char &read_data)
{
	read_data = mem[memory_num];
	return 0;
}

int CMemory::ResetCurrentInstructionAddress()
{
	current_instruction_address = 0;
	return 0;
}

int CMemory::GetCurrentInstructionAddress()
{
	return current_instruction_address;
}

int CMemory::AddInstructionAddress()
{
	current_instruction_address += 4;
	return 0;
}
