#pragma once

#include "overalldata.h"
#include <fstream>
using namespace std;

class CPipeline
{
private:
	char pipeline_coordinates[PIPELINE_X_NUM][PIPELINE_Y_NUM];	//流水线的二维XY坐标系
	char pipeline_coordinates_type_2[PIPELINE_X_NUM][PIPELINE_Y_NUM];	//流水线的二维XY坐标系，用于单步执行
	int register_time_state[PIPELINE_Y_NUM];	//每个时刻的寄存器状态
	int function_state[PIPELINE_Y_NUM];	//每个时刻的五个部件的状态
	int instruction_start[PIPELINE_X_NUM];	//每一条指令的开始位置
	bool if_write[PIPELINE_X_NUM];	//二维XY坐标系中每一行是否被用

public:
	CPipeline();	//默认构造函数
	~CPipeline();	//析构函数
	void ResetAll();	//初始化全部数据
	void ResetPipelineCoordinates();	//初始化XY坐标系
	void ResetRegsiterTimeState();	//初始化每时刻的寄存器状态数组
	void ResetFunctionState();	//初始化每时刻五个部件的状态数组
	void ResetInstructionStartAddress();	//初始化每条指令的开始位置
	void ResetIfWrite();	//初始化每条指令是否已被解析
	void WriteBan(int,int,InstructionStruct);	//写入Ban指令
	int WhichNeedRead(int, InstructionStruct);	//判断指令需要读的寄存器，返回一个int类型的32位数据，对应表示32个寄存器
	int WhichNeedWrite(int, InstructionStruct);	//判断指令需要写的寄存器，返回一个int类型的32位数据，对应表示32个寄存器
	void WriteBitToInt(int &, int, int);	//对传入的数据，在特定位置写入特定的 1 / 0
	int CheckBit(int content, int address);	//返回某一位的值
	int CheckInstructionNum();	//返回当前二维XY坐标系中已经用的流水线条数
	bool CheckPreviousInstructionIfDown(int, int);	//检查前面的指令是否已经执行完毕
	bool CheckPreviousOneInstructionIfDown(int, int);	//检查某一条指令是否已经执行完毕
	int CreatePipeline(int, int, InstructionStruct);	//对单条指令进行解析，生成流水线
	int CreatePipelineStep(int step_num);	//单步模拟执行流水线
	bool CheckAnyInstruction(int step_num);	//判断当前时间点是否还有指令需要执行
	void WriteCoordinatesToFile();	//将二维XY坐标系中的数据写入到文件中
	void WriteCoordinatesToFileType2(int);	//将二维XY坐标系中的数据写入到单步执行记录文件中
	int IfExistInstructionOnOneTime(int, char);	//判断是否在某一时间点存在某一动作，如果存在则返回该指令的编号，如果不存在，则返回特定值
};