#pragma once

#include "overalldata.h"

class CPanel
{
private:
public:
	int PanelChoose();
	//主菜单
	int ShowMainPanel();	//显示主菜单
	//选项1：指令控制
	int ShowChoose1Panel();	//指令控制菜单
	//选项2：指令执行
	int ShowChoose2Panel();	//指令执行菜单
	//选项3：内存控制
	int ShowChoose3Panel();	//内存控制菜单
	//选项4：寄存器控制
	int ShowChoose4Panel();	//寄存器控制菜单
	//选项5：流水线
	int ShowChoose5Panel();	//流水线菜单
	//选项6：使用说明
	int ShowChoose6Panel();	//使用说明菜单
	//选项7：关于
	int ShowChoose7Panel();	//关于菜单
	//选项8：退出
	int ShowChoose8Panel();	//退出菜单
};