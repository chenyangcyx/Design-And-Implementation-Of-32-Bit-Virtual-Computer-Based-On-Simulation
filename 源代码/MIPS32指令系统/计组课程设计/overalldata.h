#pragma once

//寄存器的参数
constexpr int REGISTER_BUSY = 1;
constexpr int REGISTER_FREE = 0;
constexpr int REGISTER_NUM = 32;
constexpr int REGISTER_INIT_DATA = 0;
constexpr int REGISTER_MAX_NAME_SIZE = 6;

//内存的参数
constexpr int MEMORY_BUSY = 1;
constexpr int MEMORY_FREE = 0;
constexpr int MEMORY_NUM = 768;	//内存区域长度
constexpr int MEMORY_INIT_DATA = 0;
constexpr int MEMORY_INSTRUCTION_SIZE = 256;	//指令区长度
constexpr int MEMORY_DATA_SIZE = MEMORY_NUM - MEMORY_INSTRUCTION_SIZE;	//数据区域长度

//取指类的参数
constexpr int FETCH_BUSY = 1;
constexpr int FETCH_FREE = 0;
constexpr int FETCH_PC_INIT_DATA = 0;
constexpr int PC_ADD_VALUE = 4;

//译码类的参数
constexpr int DECODING_BUSY = 1;
constexpr int DECODING_FREE = 0;
struct InstructionStruct
{
	char rs;
	char rt;
	char rd;
	char shamt;
	short immediate;
	short address;
};	//指令中译码得到的所有参数 结构体
constexpr char RS_RT_RD_ERROR_CODE = 127;
constexpr short IMMEDIATE_ADDRESS_ERROR_CODE = -1;
constexpr int INSTRUCTION_TYPE_ERROR_CODE = -1;
constexpr int SHAMT_ERROR_CODE = 127;
//指令中的FUNC标识状况
constexpr int R_TYPE_OP = 0x00;
constexpr int R_TYPE_ADDU_FUNC = 0x21;
constexpr int R_TYPE_SUBU_FUNC = 0x23;
constexpr int R_TYPE_AND_FUNC = 0x24;
constexpr int R_TYPE_OR_FUNC = 0x25;
constexpr int R_TYPE_XOR_FUNC = 0x26;
constexpr int R_TYPE_NOR_FUNC = 0x27;
constexpr int R_TYPE_SLL_FUNC = 0x00;
constexpr int R_TYPE_SRL_FUNC = 0x02;
constexpr int R_TYPE_JR_FUNC = 0x08;
constexpr int I_TYPE_ADDI = 0x08;
constexpr int I_TYPE_ANDI = 0x0c;
constexpr int I_TYPE_ORI = 0x0d;
constexpr int I_TYPE_XORI = 0x0e;
constexpr int I_TYPE_LW = 0x23;
constexpr int I_TYPE_SW = 0x2b;
constexpr int I_TYPE_BEQ = 0x04;
constexpr int J_TYPE_J = 0x02;
//17条命令的对应序号
constexpr int R_TYPE_ADDU_NO = 1;
constexpr int R_TYPE_SUBU_NO = 2;
constexpr int R_TYPE_AND_NO = 3;
constexpr int R_TYPE_OR_NO = 4;
constexpr int R_TYPE_XOR_NO = 5;
constexpr int R_TYPE_NOR_NO = 6;
constexpr int R_TYPE_SLL_NO = 7;
constexpr int R_TYPE_SRL_NO = 8;
constexpr int R_TYPE_JR_NO = 9;
constexpr int I_TYPE_ADDI_NO = 10;
constexpr int I_TYPE_ANDI_NO = 11;
constexpr int I_TYPE_ORI_NO = 12;
constexpr int I_TYPE_XORI_NO = 13;
constexpr int I_TYPE_LW_NO = 14;
constexpr int I_TYPE_SW_NO = 15;
constexpr int I_TYPE_BEQ_NO = 16;
constexpr int J_TYPE_J_NO = 17;

//执行类的参数
constexpr int EXECUTE_BUSY = 1;	//处理类忙
constexpr int EXECUTE_FREE = 0;	//处理类空闲
constexpr int EXECUTE_CONTROL_TYPE_ERROR = 1000;	//指令种类错误
constexpr int EXECUTE_CONTROL_RD_ERROR = 2000;	//RD数据错误
constexpr int EXECUTE_CONTROL_RT_ERROR = 3000;	//RT数据错误
constexpr int EXECUTE_CONTROL_RS_ERROR = 4000;	//RS数据错误
constexpr int EXECUTE_CONTROL_SHAMT_ERROR = 5000;	//SHAMT数据错误
constexpr int EXECUTE_CONTROL_IMMEDIATE_ERROR = 6000;	//IMMEDIATE数据错误
constexpr int EXECUTE_CONTROL_ADDRESS_ERROR = 7000;	//ADDRESS数据错误
constexpr int EXECUTE_CONTROL_CHECK_SUCCESS = 7777;	//指令执行成功
constexpr int EXECUTE_CONTROL_ACTION_SUCCESS = 666;	//指令执行成功
constexpr int REG_ZERO_CHANGED = 1;	//$zero寄存器值改变
constexpr int REG_ZERO_NOCHANGED = 0;	//$zero寄存器值未改变
constexpr char ALLREGISTERNAME[32][6] = { "$zero","$at","$v0","$v1","$a0","$a1","$a2","$a3","$t0","$t1","$t2","$t3","$t4","$t5",
										"$t6","$t7","$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7","$t8","$t9","$k0","$k1",
										"$gp","$sp","$fp","$ra" };

//控制类的参数
constexpr char HEXNAME[17] = "0123456789ABCDEF";
constexpr int INSTRUCTION_TRANSFORM_ERROR_CODE = -1;
constexpr int INSTRUCTION_CODE_OK = 1;  //指令语法正确
constexpr int INSTRUCTION_CODE_ERROR = -1;	//指令语法错误
//constexpr int INSTRUCTION_CODE_USELESS = 0;	//指令语法正确，但不适合本程序
constexpr int INSTRUCTION_ACTION_OK = 1;	//执行正确
constexpr int INSTRUCTION_ACTION_ERROR = 0;	//执行错误

//面板选择类的参数
constexpr int PANEL_MAIN_ADD = 100;	//主面板选择的唯一标识
constexpr int PANEL_1_ADD = 1000;	//主面板 1-指令控制 选择的唯一标识
constexpr int PANEL_2_ADD = 2000;	//主面板 2-指令执行 选择的唯一标识
constexpr int PANEL_3_ADD = 3000;	//主面板 3-内存控制 选择的唯一标识
constexpr int PANEL_4_ADD = 4000;	//主面板 4-寄存器控制 选择的唯一标识
constexpr int PANEL_5_ADD = 5000;	//主面板 5-流水线 选择的唯一标识
constexpr int PANEL_6_ADD = 6000;	//主面板 6-使用说明 选择的唯一标识
constexpr int PANEL_7_ADD = 7000;	//主面板 7-关于 选择的唯一标识
constexpr int PANEL_8_ADD = 8000;	//主面板 8-退出 选择的唯一标识
constexpr int PANEL_CHOOSE_ERROR_CODE = 9999;	//错误代码
constexpr int PANEL_RETURN_TO_MAIN_PANEL = 999;	//返回到主菜单

//流水线类的参数
constexpr int PIPELINE_X_NUM = MEMORY_INSTRUCTION_SIZE / 4;
constexpr int PIPELINE_Y_NUM = 1000;
constexpr char PIPELINE_PERIOD_NAME[5][11] = { "Fetch","Decode","Execute","ReadMemory","WriteBack" };
constexpr char PIPELINE_PERIOD_NAME_SHORTEN[9] = "UFDEMWXB";	//U-等待；F-取值；D-译码；E-执行；M-访存；W-写回；X-无内容
constexpr int REGISTER_TIME_READ = 1;	//读
constexpr int REGISTER_TIME_WRITE = 1;	//写
constexpr int NOTEXISTTHISINSTRUCTIONONONETIME = -1;	//该条指令在这个时间点不存在