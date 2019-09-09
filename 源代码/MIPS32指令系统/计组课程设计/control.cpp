#include "control.h"

CControl::CControl()
{
	current_instruction_num = 0;	//当前共有的指令条数
}

CControl::~CControl()
{
}

void CControl::AllBegin()
{
	//初始化菜单
	PanelControl();
}

int CControl::PanelControl()
{
	int choose_num;
	choose_num = panel.PanelChoose();
	while (1)
	{
		switch (choose_num)
		{
		case PANEL_CHOOSE_ERROR_CODE:
			cout << endl << "程序运行错误！" << endl;
			break;
		case PANEL_1_ADD+1:
			Menu11WriteInstruction();
			PressAnyKeyBackToMainMenu();
			break;
		case PANEL_1_ADD+2:
			Menu12CheckInstructon();
			PressAnyKeyBackToMainMenu();
			break;
		case PANEL_1_ADD+3:
			Menu13EditInstruction();
			PressAnyKeyBackToMainMenu();
			break;
		case PANEL_1_ADD+4:
			Menu14ClearInstruction();
			PressAnyKeyBackToMainMenu();
			break;
		case PANEL_2_ADD+1:
			Menu21ExecuteAllInstruction();
			PressAnyKeyBackToMainMenu();
			break;
		case PANEL_2_ADD+2:
			Menu22ExecuteInstructionByStep();
			PressAnyKeyBackToMainMenu();
			break;
		case PANEL_2_ADD+3:
			Menu23CheckExecuteRecord();
			PressAnyKeyBackToMainMenu();
			break;
		case PANEL_2_ADD+4:
			Menu24ClearExecuteRecord();
			PressAnyKeyBackToMainMenu();
			break;
		case PANEL_3_ADD+1:
			Menu31InitMemoryWith0();
			PressAnyKeyBackToMainMenu();
			break;
		case PANEL_3_ADD+2:
			Menu32InitMemoryWithValue();
			PressAnyKeyBackToMainMenu();
			break;
		case PANEL_3_ADD+3:
			Menu33EditMemory();
			PressAnyKeyBackToMainMenu();
			break;
		case PANEL_3_ADD+4:
			Menu34CheckMemory();
			PressAnyKeyBackToMainMenu();
			break;
		case PANEL_4_ADD+1:
			Menu41InitRegisterWith0();
			PressAnyKeyBackToMainMenu();
			break;
		case PANEL_4_ADD+2:
			Menu42InitRegisterWithValue();
			PressAnyKeyBackToMainMenu();
			break;
		case PANEL_4_ADD+3:
			Menu43EditRegister();
			PressAnyKeyBackToMainMenu();
			break;
		case PANEL_4_ADD+4:
			Menu44CheckRegister();
			PressAnyKeyBackToMainMenu();
			break;
		case PANEL_5_ADD+1:
			Menu51CheckPipeline();
			PressAnyKeyBackToMainMenu();
			break;
		case PANEL_5_ADD+2:
			Menu52StepRunPipeline();
			PressAnyKeyBackToMainMenu();
			break;
		case PANEL_5_ADD+3:
			Menu53ClearPipeline();
			PressAnyKeyBackToMainMenu();
			break;
		case PANEL_6_ADD+1:	//使用说明
		case PANEL_7_ADD+1:	//关于
		case PANEL_RETURN_TO_MAIN_PANEL:
			choose_num = panel.PanelChoose();
			break;
		case PANEL_8_ADD+1:	//退出
			PanelMenu8Exit();
			break;
		default:
			cout << endl << "程序运行错误！请检查是否输入了非法字符！" << endl << endl;
			return 0;
			break;
		}
	}
	return 0;
}

void CControl::PressAnyKeyBackToMainMenu()
{
	cout << endl << "输入任意值以返回主菜单！";
	int x;
	cin >> x;
	PanelControl();
}

void CControl::Menu11WriteInstruction()
{
	cout << "请输入要添加的指令，以\"##\"结束：" << endl;
	char content[40] = { '\0' };
	while (1)
	{
		cin >> content;
		if (strcmp(content, "##") == 0) break;
		if (IfInstructionOK(content) != INSTRUCTION_CODE_OK)
		{
			cout << "输入的指令错误，请检查后重新输入！" << endl;
			return;
		}
		int instruction_address = memory.GetCurrentInstructionAddress();
		int instruction;
		TransformFromCharToInstruction(content, instruction);
		for (int j = 0; j < 4; j++)
		{
			memory.WriteToMemory(instruction_address + j, (char)(instruction >> (8 * (3 - j))));
		}
		memory.AddInstructionAddress();
	}
	cout << "添加完毕！";
}

void CControl::Menu12CheckInstructon()
{
	int s = 0;	//start
	unsigned int ins = 0;
	char data = 0;
	//指令相关的数据
	InstructionStruct ins_data;
	int type;
	string str;
	cout << "内存中的所有指令如下：" << endl;
	for (int i = 0; i < MEMORY_INSTRUCTION_SIZE; i += 4, ins = 0)
	{
		s = (i / 4) * 4;	//计算得到每条指令的起始位置
		for (int j = 0; j < 4; j++)
		{
			memory.ReadFromMemory(s + j, data);
			unsigned int data_transfer = (unsigned int)data;
			data_transfer &= 0x00ff;	//去除前面的符号位扩展
			ins |= (data_transfer << (8 * (3 - j)));
		}
		if (ins != 0)
		{
			if (s < 0x10)
				cout << "0" << setiosflags(ios::uppercase) << hex << s << "H：";
			else
				cout << setiosflags(ios::uppercase) << hex << s << "H：";
			decoding.InstructionsDecoding(ins, ins_data, type);
			str = log.GetInstructionString(type, ins_data);
			cout << str << endl;
		}
	}
}

void CControl::Menu13EditInstruction()
{
	cout << "请输入要修改的指令所在地址（任意一个包含的地址即可）： ";
	int add;
	cin >> add;
	if (add >= MEMORY_INSTRUCTION_SIZE || add < 0)
	{
		cout << "输入的地址非法！" << endl;
		return;
	}
	int add_start = (add / 4) * 4;
	char str_content[40];
	int ins;
	if (add_start < 0x10)
		cout << "请输入要在地址" << setiosflags(ios::uppercase) << hex << "0" << add_start << "H修改的指令内容： ";
	else
		cout << "请输入要在地址" << setiosflags(ios::uppercase) << hex << add_start << "H修改的指令内容： ";
	cin >> str_content;
	int ifok = IfInstructionOK(str_content);
	if (ifok==INSTRUCTION_CODE_OK)
	{
		TransformFromCharToInstruction(str_content, ins);
		for (int j = 0; j < 4; j++)
			memory.WriteToMemory(add_start + j, (char)(ins >> (8 * (3 - j))));
		cout << "修改完成！" << endl;
	}
	else
	{
		cout << "输入的指令错误，请检查后重新输入！" << endl;
	}
}

void CControl::Menu14ClearInstruction()
{
	for (int i = 0; i < MEMORY_INSTRUCTION_SIZE; i++)
	{
		memory.WriteToMemory(i, 0);
	}
	fetch.ResetPC();	//清空指令，PC指针复位
	ResetCurrentInstructionNum();	//现有的指令条数清零
	memory.ResetCurrentInstructionAddress();	//重置指令的添加位置
	cout << "从 0" << setiosflags(ios::uppercase) << hex << 0 << "H 到 " << setiosflags(ios::uppercase) << hex << MEMORY_INSTRUCTION_SIZE << "H 的内存指令区域已经清空！" << endl;
}

void CControl::ResetCurrentInstructionNum()
{
	current_instruction_num = 0;
}

void CControl::RefershCurrentInstructionNum()
{
	int ins_num = 0;
	for (int i = 0; i < MEMORY_INSTRUCTION_SIZE; i += 4)
	{
		char n1, n2, n3, n4;
		memory.ReadFromMemory(i, n1);
		memory.ReadFromMemory(i + 1, n2);
		memory.ReadFromMemory(i + 2, n3);
		memory.ReadFromMemory(i + 3, n4);
		if (n1 != 0 || n2 != 0 || n3 != 0 || n4 != 0)
			ins_num++;
	}
	current_instruction_num = ins_num;
}

int CControl::RegZeroCheck()
{
	int reg0_value;
	reg.ReadFromOneRegister(0, reg0_value);
	if (reg0_value != 0)
	{
		cout << "检测到$zero寄存器值改变！已经阻止该指令的执行！" << endl;
		reg.WriteToOneRegister(0, 0);	//将$zero寄存器的值改写为0
		return REG_ZERO_CHANGED;
	}
	return REG_ZERO_NOCHANGED;
}

int CControl::ExecuteOneInstruction(int instruction_no)
{
	//取指
	int instruction = 0;	//指令的编码
	fetch.FetchInstructionFromMemory(fetch.GetPC(), memory.mem, instruction);
	//译码
	int instruction_type;	//指令类型
	InstructionStruct instruction_data;	//指令的所有提取的数据
	decoding.InstructionsDecoding(instruction, instruction_data, instruction_type);
	if (instruction == 0) return INSTRUCTION_ACTION_ERROR;	//检测指令是否有效
	//执行
	int execute_code = execute.ExecuteControl(instruction_type, instruction_data, memory.mem, reg.reg, fetch.PC);
	if (execute_code != EXECUTE_CONTROL_ACTION_SUCCESS)
	{
		if (execute_code == EXECUTE_CONTROL_TYPE_ERROR)
		{
			cout << "指令格式错误！该条指令拒绝执行！" << endl;
		}
		if (execute_code == EXECUTE_CONTROL_RD_ERROR)
		{
			cout << "RD范围错误！该条指令拒绝执行！" << endl;
		}
		if (execute_code == EXECUTE_CONTROL_RT_ERROR)
		{
			cout << "RT范围错误！该条指令拒绝执行！" << endl;
		}
		if (execute_code == EXECUTE_CONTROL_RS_ERROR)
		{
			cout << "RS范围错误！该条指令拒绝执行！" << endl;
		}
		if (execute_code == EXECUTE_CONTROL_SHAMT_ERROR)
		{
			cout << "SHAMT范围错误！该条指令拒绝执行！" << endl;
		}
		if (execute_code == EXECUTE_CONTROL_IMMEDIATE_ERROR)
		{
			cout << "IMMEDIATE范围错误！该条指令拒绝执行！" << endl;
		}
		if (execute_code == EXECUTE_CONTROL_ADDRESS_ERROR)
		{
			cout << "ADDRESS范围错误！该条指令拒绝执行！" << endl;
		}
		fetch.PCSelfAdd();	//PC指针自增
		return INSTRUCTION_ACTION_ERROR;
	}
	else
	{
		//显示指令执行状况
		string action_instruction_message = log.GetInstructionLogDetail(instruction_type, instruction_data);
		cout << action_instruction_message << "指令执行成功！" << endl << endl;
		//写入文件
		log.WriteLog(instruction_type, instruction_data);
	}
	//访存  //写回      //包含在执行过程中，无需再写代码
	fetch.PCSelfAdd();	//PC指针自增
	//检测$zero寄存器
	RegZeroCheck();
	return INSTRUCTION_ACTION_OK;
}

void CControl::Menu21ExecuteAllInstruction()
{
	RefershCurrentInstructionNum();	//刷新当前内存中共有的指令条数
	int instruction_num = current_instruction_num;	//当前共有的指令条数
	log.LogBegin();
	for (int i = 0; i < instruction_num; i++)
		ExecuteOneInstruction(i);
	log.LogEnd();
	if (instruction_num > 1)
	{
		char buffer[200];
		_getcwd(buffer, 200);
		cout << endl << "指令执行记录已经保存在： " << endl << buffer << "\\record.txt" << endl << "你可以手动打开或者通过本程序查看！" << endl;
	}
}

void CControl::Menu22ExecuteInstructionByStep()
{
	RefershCurrentInstructionNum();	//刷新当前内存中共有的指令条数
	int instruction_num = current_instruction_num;	//当前共有的指令条数
	log.LogBegin();
	int choice = 2;
	int k = 0;	//k为当前指令条数计数
	cout << "开始单步执行：" << endl;
	while (1)
	{
		if (ExecuteOneInstruction(k++) == INSTRUCTION_ACTION_ERROR)	//执行一条指令
		{
			log.LogEnd();
			break;
		}
		cout << endl << "单步执行完成，如果继续请按1，如果退出请按0： ";
		cin >> choice;
		while (choice!=0&&choice!=1)
		{
			cout << "输入错误，请重新输入： ";
			cin >> choice;
		}
		if (choice == 0)
		{
			log.LogEnd();
			return;
		}
		else if (choice == 1) continue;
	}
}

void CControl::Menu23CheckExecuteRecord()
{
	cout << endl << "指令的执行记录如下：" << endl;
	ifstream execute_record;
	execute_record.open("record.txt", ios::in);
	if (!execute_record.is_open())
	{
		cout << "文件打开失败！请确保文件存在！" << endl;
		return;
	}
	char c;
	execute_record >> noskipws;
	while (!execute_record.eof())
	{
		execute_record >> c;
		cout << c;
	}
	execute_record.close();
}

void CControl::Menu24ClearExecuteRecord()
{
	log.ClearLog();
	cout << endl << "record.txt文件已经清空！" << endl;
}

void CControl::Menu31InitMemoryWith0()
{
	memory.InitAllMemoryWith0();
	cout << "已经将从地址 ";
	cout << setiosflags(ios::uppercase) << hex << MEMORY_INSTRUCTION_SIZE;
	cout << "H 到地址 ";
	cout << setiosflags(ios::uppercase) << hex << MEMORY_NUM - 1;
	cout << "H 全部初始化为 0 ！" << endl;
}

void CControl::Menu32InitMemoryWithValue()
{
	int init_num;
	cout << "请输入指定值以初始化全部内存： ";
	cin >> init_num;
	if (init_num < 0 || init_num>127)
	{
		cout << "不能够用此值进行初始化！" << endl;
		cout << "能够使用的值范围为：" << setiosflags(ios::uppercase) << hex << 0 << " - " << setiosflags(ios::uppercase) << hex << 127 << endl;
		return;
	}
	memory.InitAllMemoryWithValue(init_num);
	cout << "已经将从地址 ";
	cout << setiosflags(ios::uppercase) << hex << MEMORY_INSTRUCTION_SIZE;
	cout << "H 到地址 ";
	cout << setiosflags(ios::uppercase) << hex << MEMORY_NUM - 1;
	if(init_num<0x10)
		cout << "H 全部初始化为 0" << init_num << "H ！" << endl;
	else
		cout << "H 全部初始化为 " << init_num << "H ！" << endl;
}

void CControl::Menu33EditMemory()
{
	int edit_address, edit_data;
	cout << "请输入要修改的内存地址及要修改的值： ";
	cin >> edit_address >> edit_data;
	if (edit_address < MEMORY_INSTRUCTION_SIZE - 1)
	{
		cout << "不能修改指令区域中的值！" << endl;
		cout << "能够修改的地址范围为：" << setiosflags(ios::uppercase) << hex << MEMORY_INSTRUCTION_SIZE << "H - " << setiosflags(ios::uppercase) << hex << MEMORY_NUM << "H" << endl;
		return;
	}
	if (edit_address > MEMORY_NUM - 1)
	{
		cout << "不存在这样的区域！" << endl;
		cout << "能够修改的地址范围为：" << setiosflags(ios::uppercase) << hex << MEMORY_INSTRUCTION_SIZE << "H - " << setiosflags(ios::uppercase) << hex << MEMORY_NUM << "H" << endl;
		return;
	}
	if (edit_data < 0 || edit_data>127)
	{
		cout << "不能够用此值进行修改！" << endl;
		cout << "能够使用的值范围为：" << setiosflags(ios::uppercase) << hex << 0 << "H - " << setiosflags(ios::uppercase) << hex << 127 << "H" << endl;
		return;
	}
	memory.WriteToMemory(edit_address, edit_data);
	cout << "已经将地址为 " << setiosflags(ios::uppercase) << hex << edit_address << "H 地址的数据修改为 " << setiosflags(ios::uppercase) << hex << edit_data << "H ！" << endl;
}

void CControl::Menu34CheckMemory()
{
	int add = 0 - 16, cal = 0;
	char data;

	cout << endl << "指令区域：";
	for (int i = 0; i < MEMORY_INSTRUCTION_SIZE; i++)
	{
		if (cal % 16 == 0)
		{
			add += 16;
			if (add < 0x10)
				cout << endl << "0";
			else
				cout << endl;
			cout << setiosflags(ios::uppercase) << hex << add << "H\t";
		}
		memory.ReadFromMemory(i, data);
		cout << HEXNAME[(data >> 4) & 0x0f] << HEXNAME[(data >> 0) & 0x0f] << "H  ";
		cal++;
	}

	add = MEMORY_INSTRUCTION_SIZE - 16, cal = 0;
	cout << endl << endl << "数据区域：";
	for (int i = MEMORY_INSTRUCTION_SIZE; i < MEMORY_NUM; i++)
	{
		if (cal % 16 == 0)
		{
			add += 16;
			if (add < 0x10)
				cout << "0";
			cout << endl << setiosflags(ios::uppercase) << hex << add << "H\t";
		}
		memory.ReadFromMemory(i, data);
		cout << HEXNAME[(data >> 4) & 0x0f] << HEXNAME[(data >> 0) & 0x0f] << "H  ";
		cal++;
	}
	cout << endl;
}

void CControl::Menu41InitRegisterWith0()
{
	reg.InitAllRegisterWith0();
	cout << "已经初始化全部寄存器为0（$zero除外）！" << endl;
}

void CControl::Menu42InitRegisterWithValue()
{
	cout << resetiosflags(ios::uppercase) << dec;
	int init_num;
	cout << "请输入要初始化的值： ";
	cin >> init_num;
	reg.InitAllRegisterWithValue(init_num);
	cout << "已经初始化全部寄存器为" << init_num << "（$zero除外）！" << endl;
}

void CControl::Menu43EditRegister()
{
	cout << resetiosflags(ios::uppercase) << dec;
	int edit_no, edit_data;
	cout << "请输入要修改的寄存器序号、值： ";
	cin >> edit_no >> edit_data;
	if (edit_no == 0)
	{
		cout << "$zero 恒为0，无法修改值！" << endl;
		return;
	}
	else if (edit_no < 0 || (edit_no > REGISTER_NUM - 1))
	{
		cout << "无法找到序号为 " << edit_no << " 的寄存器！" << endl;
		return;
	}
	reg.WriteToOneRegister(edit_no, edit_data);
	cout << "寄存器 " << log.GetRegisterName(edit_no) << " 的值已经修改为 " << edit_data << " ！" << endl;
}

void CControl::Menu44CheckRegister()
{
	cout << resetiosflags(ios::uppercase) << dec;
	cout << "所有寄存器的值为：" << endl;
	int reg_data, cal = 0;
	for (int i = 0; i < REGISTER_NUM; i++)
	{
		reg.ReadFromOneRegister(i, reg_data);
		cout << log.GetRegisterName(i) << "：" << reg_data << "\t\t";
		cal++;
		if (cal % 4 == 0)
			cout << endl;
	}
}

void CControl::Menu51CheckPipeline()
{
	fetch.ResetPC();//使PC指针归位
	pipeline.ResetAll();
	RefershCurrentInstructionNum();	//刷新当前内存中共有的指令条数
	int instruction_num = current_instruction_num;	//当前共有的指令条数
	for (int i = 0; i < instruction_num; i++)
	{
		int instruction = 0;	//指令的编码
		fetch.FetchInstructionFromMemory(fetch.GetPC(), memory.mem, instruction);
		int instruction_type;	//指令类型
		InstructionStruct instruction_data;	//指令的所有提取的数据
		decoding.InstructionsDecoding(instruction, instruction_data, instruction_type);
		if (decoding.InstructionCheckZero(instruction_type, instruction_data) == true)	//查看指令是否写$zero0
		{
			pipeline.WriteBan(i, instruction_type, instruction_data);
		}
		else
		{
			pipeline.CreatePipeline(i, instruction_type, instruction_data);
		}
		fetch.PCSelfAdd();	//PC指针自增
	}

	pipeline.WriteCoordinatesToFile();

	cout << endl << "流水线图如下：" << endl << endl;
	ifstream pipeline_record;
	pipeline_record.open("pipeline.txt", ios::in);
	if (!pipeline_record.is_open())
	{
		cout << "文件打开失败！请确保文件存在！" << endl;
		return;
	}
	char c;
	pipeline_record >> noskipws;
	while (!pipeline_record.eof())
	{
		pipeline_record >> c;
		cout << c;
	}
	pipeline_record.close();
}

void CControl::Menu52StepRunPipeline()
{
	//准备工作 开始
	fetch.ResetPC();//使PC指针归位
	pipeline.ResetAll();
	RefershCurrentInstructionNum();	//刷新当前内存中共有的指令条数
	int instruction_num = current_instruction_num;	//当前共有的指令条数
	for (int i = 0; i < instruction_num; i++)
	{
		int instruction = 0;	//指令的编码
		fetch.FetchInstructionFromMemory(fetch.GetPC(), memory.mem, instruction);
		int instruction_type;	//指令类型
		InstructionStruct instruction_data;	//指令的所有提取的数据
		decoding.InstructionsDecoding(instruction, instruction_data, instruction_type);
		if (decoding.InstructionCheckZero(instruction_type, instruction_data) == true)	//查看指令是否写$zero0
		{
			pipeline.WriteBan(i, instruction_type, instruction_data);
		}
		else
		{
			pipeline.CreatePipeline(i, instruction_type, instruction_data);
		}
		fetch.PCSelfAdd();	//PC指针自增
	}
	//准备工作 结束
	cout << "开始单步模拟执行流水线" << endl << endl;
	int step = 0;	//当前步数
	int choice;
	fetch.ResetPC();//使PC指针归位
	while (1)
	{
		pipeline.CreatePipelineStep(step);
		pipeline.WriteCoordinatesToFileType2(step);
		//读取文件
		cout << endl;
		ifstream pipeline_record;
		pipeline_record.open("pipeline_step.txt", ios::in);
		if (!pipeline_record.is_open())
		{
			cout << "文件打开失败！请确保文件存在！" << endl;
			return;
		}
		char c;
		pipeline_record >> noskipws;
		while (!pipeline_record.eof())
		{
			pipeline_record >> c;
			cout << c;
		}
		pipeline_record.close();

		//检查5个状态是否存在
		//Fetch取指状态
		if (pipeline.IfExistInstructionOnOneTime(step, 'F') != NOTEXISTTHISINSTRUCTIONONONETIME)
		{
			int q = pipeline.IfExistInstructionOnOneTime(step, 'F');
			cout << "序号" << q << "指令：Fetch取指\t取指内容：";
			int instruction = 0;	//指令的编码
			fetch.FetchInstructionFromMemory(q * 4, memory.mem, instruction);
			for (int p = 31; p >= 0; p--)	//输出二进制形式
				cout << ((instruction >> p) & 1);
			cout << endl;
		}
		//Decode译码状态
		if (pipeline.IfExistInstructionOnOneTime(step, 'D') != NOTEXISTTHISINSTRUCTIONONONETIME)
		{
			int q = pipeline.IfExistInstructionOnOneTime(step, 'D');
			cout << "序号" << q << "指令：Decode译码\t译码内容：";
			int instruction = 0;	//指令的编码
			fetch.FetchInstructionFromMemory(q * 4, memory.mem, instruction);
			int instruction_type;	//指令类型
			InstructionStruct instruction_data;	//指令的所有提取的数据
			decoding.InstructionsDecoding(instruction, instruction_data, instruction_type);
			string str = log.GetInstructionString(instruction_type, instruction_data);
			cout << str << endl;
		}
		//Wait等待状态
		if (pipeline.IfExistInstructionOnOneTime(step, 'U') != NOTEXISTTHISINSTRUCTIONONONETIME)
		{
			int q = pipeline.IfExistInstructionOnOneTime(step, 'U');
			cout << "序号" << q << "指令：Wait等待\t指令暂停执行" << endl;
		}
		//Ban禁止状态
		if (pipeline.IfExistInstructionOnOneTime(step, 'B') != NOTEXISTTHISINSTRUCTIONONONETIME)
		{
			int q = pipeline.IfExistInstructionOnOneTime(step, 'B');
			cout << "序号" << q << "指令：Ban禁止\t要写入$zero，指令直接禁止执行！" << endl;
		}
		//Execute执行状态
		if (pipeline.IfExistInstructionOnOneTime(step, 'E') != NOTEXISTTHISINSTRUCTIONONONETIME)
		{
			int q = pipeline.IfExistInstructionOnOneTime(step, 'E');
			cout << "序号" << q << "指令：Execute执行\t执行内容：";
			int instruction = 0;	//指令的编码
			fetch.FetchInstructionFromMemory(q * 4, memory.mem, instruction);
			int instruction_type;	//指令类型
			InstructionStruct instruction_data;	//指令的所有提取的数据
			decoding.InstructionsDecoding(instruction, instruction_data, instruction_type);
			int p = execute.KnowExecuteResult(instruction_type, instruction_data, memory.mem, reg.reg, fetch.PC);
			string str = execute.KnowExecuteDetail(instruction_type, instruction_data, memory.mem, reg.reg, fetch.PC);
			cout << str << "\t执行结果：" << p << endl;
		}
		//Memory执行状态
		if (pipeline.IfExistInstructionOnOneTime(step, 'M') != NOTEXISTTHISINSTRUCTIONONONETIME)
		{
			int q = pipeline.IfExistInstructionOnOneTime(step, 'M');
			cout << "序号" << q << "指令：Memory访存\t访存内容：";
			int instruction = 0;	//指令的编码
			fetch.FetchInstructionFromMemory(q * 4, memory.mem, instruction);
			int instruction_type;	//指令类型
			InstructionStruct instruction_data;	//指令的所有提取的数据
			decoding.InstructionsDecoding(instruction, instruction_data, instruction_type);
			if (instruction_type == I_TYPE_SW_NO || instruction_type == I_TYPE_LW_NO)	//只有这两条指令需要访存
			{
				int p = execute.KnowMemoryReadContent(instruction_type, instruction_data, memory.mem, reg.reg);
			}
			else
			{
				cout << "该指令无需访存！此过程为空！" << endl;
			}
		}
		//WriteBack执行状态
		if (pipeline.IfExistInstructionOnOneTime(step, 'W') != NOTEXISTTHISINSTRUCTIONONONETIME)
		{
			int q = pipeline.IfExistInstructionOnOneTime(step, 'W');
			cout << "序号" << q << "指令：WriteBack写回\t写回内容：";
			int instruction = 0;	//指令的编码
			fetch.FetchInstructionFromMemory(q * 4, memory.mem, instruction);
			int instruction_type;	//指令类型
			InstructionStruct instruction_data;	//指令的所有提取的数据
			decoding.InstructionsDecoding(instruction, instruction_data, instruction_type);
			string des = execute.KnowWhichToWriteTo(instruction_type, instruction_data, memory.mem, reg.reg);
			int p = execute.KnowExecuteResult(instruction_type, instruction_data, memory.mem, reg.reg, fetch.PC);
			cout << des << " <- " << p << endl;
			execute.ExecuteControlAction(instruction_type, instruction_data, memory.mem, reg.reg, fetch.PC);
		}

		//列出所有寄存器
		cout << endl;
		Menu44CheckRegister();
		ShowPC();	//列出PC的值

		//键盘控制
		cout << endl << "如果要继续，请输入1，否则输入0返回主菜单： ";
		cin >> choice;
		if (choice == 0) return;
		step++;
		fetch.PCSelfAdd();
		if (pipeline.CheckAnyInstruction(step) == false)
			return;
	}
}

void CControl::ShowPC()
{
	int PC_value = fetch.GetPC();
	cout << "----当前PC指针的值：" << HEXNAME[(PC_value >> 4) & 0x0f] << HEXNAME[(PC_value >> 0) & 0x0f] << "H----" << endl;
}

void CControl::Menu53ClearPipeline()
{
	pipeline.ResetPipelineCoordinates();
	pipeline.ResetFunctionState();
	pipeline.ResetInstructionStartAddress();
	pipeline.ResetRegsiterTimeState();
	pipeline.ResetIfWrite();
}

void CControl::PanelMenu8Exit()
{
	exit(0);
}

int CControl::TransformFromCharToInstruction(char instru_str[],int &instru_result)
{
	for (int i = 0; i < 32; i++)
	{
		if (instru_str[i] != '0'&&instru_str[i] != '1')
		{
			instru_result = INSTRUCTION_TRANSFORM_ERROR_CODE;
		}
	}
	for (int i = 0; i < 32; i++)
	{
		if (instru_str[i] == '1') instru_result |= (1 << (31 - i));
		else if (instru_str[i] == '0') instru_result &= ~(1 << (31 - i));
	}
	return 0;
}

int CControl::IfInstructionOK(char str[])
{
	//第一次循环，检查是否有其他字符
	for (int i = 0; i < strlen(str); i++)
		if (str[i] != '0' && str[i] != '1')
			return INSTRUCTION_CODE_ERROR;
	//第二次循环，检查是否长度符合规范
	if (strlen(str) != 32) return INSTRUCTION_CODE_ERROR;
	return INSTRUCTION_CODE_OK;
}
