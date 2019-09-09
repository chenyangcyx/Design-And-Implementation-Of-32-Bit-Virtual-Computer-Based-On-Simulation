#pragma once

#include "overalldata.h"

class CMemory
{
public:char mem[MEMORY_NUM];	//内存
private:
	int instruction_size;	//内存指令区域的长度
	int data_size;	//内存数据区域的长度
	int memory_state;	//当前内存状态
	int current_instruction_address;	//当前指令地址
public:
	CMemory();	//默认构造函数
	~CMemory();	//析构函数
	int SetMemoryBusy();	//设置内存状态为忙碌
	int SetMemoryFree();	//设置内存状态为空闲
	int ReturnCurrentState(int &);	//返回内存当前状态
	int InitAllMemoryWith0();	//初始化全部内存 0
	int InitAllMemoryWithValue(int);	//初始化全部内存 指定值
	int WriteToMemory(int, char);	//向指定内存写入数据
	int ReadFromMemory(int, char &);	//从指定内存读取数据
	int ResetCurrentInstructionAddress();	//重置当前的添加指令位置
	int GetCurrentInstructionAddress();	//获取当前的添加指令位置
	int AddInstructionAddress();	//指令位置自增
};