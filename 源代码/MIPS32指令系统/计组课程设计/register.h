#pragma once

#include "overalldata.h"
#include <string>
using namespace std;

class CRegister
{
public:int reg[REGISTER_NUM];	//所有的32个寄存器
private:
	int register_state;	//寄存器当前状态
public:
	CRegister();	//默认构造函数
	~CRegister();	//析构函数
	int SetRegisterBusy();	//设置寄存器为忙碌
	int SetRegisterFree();	//设置寄存器为空闲
	int ReturnCurrentState(int &);	//返回寄存器当前状态
	int InitAllRegisterWith0();	//初始化全部寄存器 0
	int InitAllRegisterWithValue(int);	//初始化全部寄存器 指定值
	int WriteToOneRegister(int, int);	//向指定的寄存器中写入数据
	int ReadFromOneRegister(int, int &);	//从指定的寄存器中读取数据
};