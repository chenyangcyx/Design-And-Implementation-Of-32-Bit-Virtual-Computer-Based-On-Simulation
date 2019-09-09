#pragma once

#include "overalldata.h"

class CFetch
{
public:int PC;	//PC指针
private:
	int fetch_state;	//当前取指令状态
public:
	CFetch();	//默认构造函数
	~CFetch();	//析构函数
	int SetFetchBusy();	//设置当前取指状态为忙碌
	int SetFetchFree();	//设置当前取指状态为空闲
	int ReturnCurrentState(int &);	//返回取指类当前状态
	int GetPC();	//获取PC指针的值
	int PCSelfAdd();	//PC指针自增
	int EditPC(int);	//修改PC指针的值
	int ResetPC();	//重置PC指针的值
	int FetchInstructionFromMemory(int, char[], int &);	//从内存的指定区域取指令
};