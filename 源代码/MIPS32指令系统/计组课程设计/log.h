#pragma once

#include "overalldata.h"
#include <fstream>
#include <string>
#include <time.h>
using namespace std;

class CLog
{
private:
	char regname[REGISTER_NUM][REGISTER_MAX_NAME_SIZE];	//寄存器名字
	ofstream logfile;	//写记录的文件
	bool ifnew;	//判断是否第一次写文件
	int current_log_no;	//当前记录标号
public:
	CLog();	//默认构造函数
	~CLog();	//析构函数
	int InitRegName();	//初始化寄存器名字
	string GetRegisterName(int);	//获取寄存器名字
	int InitLogNo();	//初始化记录标号 current_log_no
	string GetInstructionLogDetail(int, InstructionStruct);	//获取指令记录内容
	string GetInstructionString(int, InstructionStruct);	//获取指令内容
	int WriteLog(int, InstructionStruct);	//根据指令内容，写文件
	void LogBegin();	//开始写文件
	void LogEnd();	//结束写文件
	void ClearLog();	//删除所有记录
};