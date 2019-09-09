#pragma once

#include "overalldata.h"

class CDecoding
{
private:
	int decoding_state;	//当前译码状态
public:
	CDecoding();	//默认构造函数
	~CDecoding();	//析构函数
	int SetDecodingBusy();	//设置当前译码状态为忙碌
	int SetDecodingFree();	//设置当前译码状态为空闲
	int ReturnCurrentState(int &);	//返回取指类当前状态
	int BitSelectTransform(int, int, int, int &);	//提取从m位到n位的值
	int InstructionsDecoding(int, InstructionStruct &, int &);	//对指令进行译码
	bool InstructionCheckZero(int instruction_type, InstructionStruct data);	//检测该指令是否为写入$zero0寄存器的指令
};