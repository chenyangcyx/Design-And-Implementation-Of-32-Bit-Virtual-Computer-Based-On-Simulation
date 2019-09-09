#pragma once

#include "overalldata.h"
#include "decoding.h"
#include "execute.h"
#include "fetch.h"
#include "log.h"
#include "memory.h"
#include "panel.h"
#include "pipeline.h"
#include "register.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <direct.h>
using namespace std;

class CControl
{
private:
	CDecoding decoding;
	CExecute execute;
	CFetch fetch;
	CLog log;
	CMemory memory;
	CPanel panel;
	CPipeline pipeline;
	CRegister reg;
	int current_instruction_num;	//当前共有的指令条数
public:
	CControl();	//默认构造函数
	~CControl();	//析构函数

	/*程序入口相关的函数*/
	void AllBegin();	//程序入口处，直接调用
	int PanelControl();	//面板控制
	void PressAnyKeyBackToMainMenu();	//按任意键返回主菜单

	/*详细功能*/
	/*菜单1-指令控制*/
	int TransformFromCharToInstruction(char[], int&);	//将输入的字符串转化为指令
	int IfInstructionOK(char []);	//检查输入的指令是否违法
	void Menu11WriteInstruction();	//输入指令
	void Menu12CheckInstructon();	//查看指令
	void Menu13EditInstruction();	//修改指令
	void Menu14ClearInstruction();	//清空指令
	/*菜单2-指令执行*/
	void ResetCurrentInstructionNum();	//重置当前的所有的指令条数
	void RefershCurrentInstructionNum();	//刷新当前的所有的指令条数
	int RegZeroCheck();	//检测$zero寄存器的状态，并重置为0
	int ExecuteOneInstruction(int);	//执行一条指令
	void Menu21ExecuteAllInstruction();	//执行全部指令
	void Menu22ExecuteInstructionByStep();	//单步执行指令
	void Menu23CheckExecuteRecord();	//检查指令执行记录
	void Menu24ClearExecuteRecord();	//清除指令执行记录
	/*菜单3-内存控制*/
	void Menu31InitMemoryWith0();	//初始化内存 全0
	void Menu32InitMemoryWithValue();	//初始化内存 指定值
	void Menu33EditMemory();	//修改内存
	void Menu34CheckMemory();	//查看内存
	/*菜单4-寄存器控制*/
	void Menu41InitRegisterWith0();	//初始化寄存器 全0
	void Menu42InitRegisterWithValue();	//初始化寄存器 指定值
	void Menu43EditRegister();	//修改寄存器
	void Menu44CheckRegister();	//查看寄存器
	/*菜单5-流水线*/
	void Menu51CheckPipeline();	//查看流水线图
	void Menu52StepRunPipeline();	//单步模拟执行流水线
	void ShowPC();	//查看当前PC指针的值
	void Menu53ClearPipeline();	//清空流水线
	/*菜单6-使用说明*/
	//--此菜单无需函数实现
	/*菜单7-关于*/
	//--此菜单无需函数实现
	/*菜单8-退出*/
	void PanelMenu8Exit();
};