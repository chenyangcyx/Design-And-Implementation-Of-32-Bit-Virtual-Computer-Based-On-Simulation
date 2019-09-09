#include "pipeline.h"

CPipeline::CPipeline()
{
	ResetAll();
}

CPipeline::~CPipeline()
{
}

void CPipeline::ResetAll()
{
	ResetPipelineCoordinates();
	ResetInstructionStartAddress();
	ResetRegsiterTimeState();
	ResetFunctionState();
	ResetIfWrite();
}

void CPipeline::ResetPipelineCoordinates()
{
	for (int i = 0; i < PIPELINE_X_NUM; i++)
	{
		for (int j = 0; j < PIPELINE_Y_NUM; j++)
		{
			pipeline_coordinates[i][j] = PIPELINE_PERIOD_NAME_SHORTEN[6];
			pipeline_coordinates_type_2[i][j] = PIPELINE_PERIOD_NAME_SHORTEN[6];
		}
	}
}

void CPipeline::ResetRegsiterTimeState()
{
	for (int i = 0; i < PIPELINE_Y_NUM; i++)
		register_time_state[i] = 0;
}

void CPipeline::ResetFunctionState()
{
	for (int i = 0; i < PIPELINE_Y_NUM; i++)
		function_state[i] = 0;
}

void CPipeline::ResetInstructionStartAddress()
{
	for (int i = 0; i < PIPELINE_X_NUM; i++)
		instruction_start[i] = i;
}

void CPipeline::ResetIfWrite()
{
	for (int i = 0; i < PIPELINE_X_NUM; i++)
		if_write[i] = false;
}

void CPipeline::WriteBan(int instruction_no,int instruction_type,InstructionStruct data)
{
	int start = instruction_start[instruction_no];	//指令在坐标系中的起始位置
	int k = 0;	//位置计数器

	//判断F是否被占用
	while (CheckBit(function_state[start + k], 1) != 0)	//F部件被占用
	{
		pipeline_coordinates[instruction_no][start + k] = PIPELINE_PERIOD_NAME_SHORTEN[6];	//因为是F，所以直接写入'X'
		k++;
	}
	//F部件可以使用
	pipeline_coordinates[instruction_no][start + k] = PIPELINE_PERIOD_NAME_SHORTEN[1];	//写入'F'
	WriteBitToInt(function_state[start + k], 1, 1);	//F部件占用
	k++;

	//判断D部件是否被占用
	while (CheckBit(function_state[start + k], 2) != 0)	//D部件被占用
	{
		pipeline_coordinates[instruction_no][start + k] = PIPELINE_PERIOD_NAME_SHORTEN[0];	//等待
		WriteBitToInt(function_state[start + k], 1, 1);	//F部件被占用
		k++;
	}
	//D部件可以使用
	pipeline_coordinates[instruction_no][start + k] = PIPELINE_PERIOD_NAME_SHORTEN[2];	//写入'D'
	WriteBitToInt(function_state[start + k], 2, 1);	//D部件被占用
	k++;
	pipeline_coordinates[instruction_no][start + k] = PIPELINE_PERIOD_NAME_SHORTEN[7];

	//本条指令所对应的行已被占用
	if_write[instruction_no] = true;
}

int CPipeline::WhichNeedRead(int instruction_type,InstructionStruct data)
{
	int content = 0;
	switch (instruction_type)
	{
	case R_TYPE_ADDU_NO:
	case R_TYPE_SUBU_NO:
	case R_TYPE_AND_NO:
	case R_TYPE_OR_NO:
	case R_TYPE_XOR_NO:
	case R_TYPE_NOR_NO:
		WriteBitToInt(content, data.rs, REGISTER_TIME_READ);
		WriteBitToInt(content, data.rt, REGISTER_TIME_READ);
		break;
	case R_TYPE_SLL_NO:
	case R_TYPE_SRL_NO:
		WriteBitToInt(content, data.rt, REGISTER_TIME_READ);
		break;
	case R_TYPE_JR_NO:
		WriteBitToInt(content, data.rs, REGISTER_TIME_READ);
		break;
	case I_TYPE_ADDI_NO:
	case I_TYPE_ANDI_NO:
	case I_TYPE_ORI_NO:
	case I_TYPE_XORI_NO:
	case I_TYPE_LW_NO:
		WriteBitToInt(content, data.rs, REGISTER_TIME_READ);
		break;
	case I_TYPE_SW_NO:
	case I_TYPE_BEQ_NO:
		WriteBitToInt(content, data.rs, REGISTER_TIME_READ);
		WriteBitToInt(content, data.rt, REGISTER_TIME_READ);
		break;
	case J_TYPE_J_NO:
		break;
	default:
		break;
	}
	return content;
}

int CPipeline::WhichNeedWrite(int instruction_type, InstructionStruct data)
{
	int content = 0;
	switch (instruction_type)
	{
	case R_TYPE_ADDU_NO:
	case R_TYPE_SUBU_NO:
	case R_TYPE_AND_NO:
	case R_TYPE_OR_NO:
	case R_TYPE_XOR_NO:
	case R_TYPE_NOR_NO:
		WriteBitToInt(content, data.rd, REGISTER_TIME_WRITE);
		break;
	case R_TYPE_SLL_NO:
	case R_TYPE_SRL_NO:
		WriteBitToInt(content, data.rd, REGISTER_TIME_WRITE);
		break;
	case R_TYPE_JR_NO:
		break;
	case I_TYPE_ADDI_NO:
	case I_TYPE_ANDI_NO:
	case I_TYPE_ORI_NO:
	case I_TYPE_XORI_NO:
	case I_TYPE_LW_NO:
		WriteBitToInt(content, data.rt, REGISTER_TIME_WRITE);
		break;
	case I_TYPE_SW_NO:
	case I_TYPE_BEQ_NO:
		break;
	case J_TYPE_J_NO:
		break;
	default:
		break;
	}
	return content;
}

void CPipeline::WriteBitToInt(int &content, int address, int mode)
{
	if (mode == 1)	//写入1
	{
		content |= (1 << address);
	}
	else if (mode == 0)	//写入0
	{
		content &= ~(1 << address);
	}
}

int CPipeline::CheckBit(int content, int address)
{
	if ((content & (1 << address)) != 0) return 1;
	else return 0;
}

int CPipeline::CheckInstructionNum()
{
	int num = 0;
	for (int i = 0; i < PIPELINE_X_NUM; i++)
	{
		int sum = 0;
		for (int j = 0; j < PIPELINE_Y_NUM; j++)
			sum += pipeline_coordinates[i][j];
		if (sum != 'X'*PIPELINE_Y_NUM)
			num++;
	}
	return num;
}

bool CPipeline::CheckPreviousInstructionIfDown(int instruction_no, int time_address)
{
	for(int i = instruction_no - 1; i >= 1; i--)
	{
		if (CheckPreviousOneInstructionIfDown(i, time_address) == false)
			return false;
	}
	return true;
}

bool CPipeline::CheckPreviousOneInstructionIfDown(int instruction_no,int time_address)
{
	for (int i = instruction_start[instruction_no]; i < time_address; i++)
	{
		if (pipeline_coordinates[instruction_no][i] == PIPELINE_PERIOD_NAME_SHORTEN[7])
			return true;
		if (pipeline_coordinates[instruction_no][i] == PIPELINE_PERIOD_NAME_SHORTEN[5])
			return true;
	}
	return false;
}

int CPipeline::CreatePipeline(int instruction_no, int instruction_type, InstructionStruct data)
{
	int start = instruction_start[instruction_no];	//指令在坐标系中的起始位置
	int k = 0;	//位置计数器

	//判断F是否被占用
	while (CheckBit(function_state[start + k], 1) != 0)	//F部件被占用
	{
		pipeline_coordinates[instruction_no][start + k] = PIPELINE_PERIOD_NAME_SHORTEN[6];	//因为是F，所以直接写入'X'
		k++;
	}
	//F部件可以使用
	pipeline_coordinates[instruction_no][start + k] = PIPELINE_PERIOD_NAME_SHORTEN[1];	//写入'F'
	WriteBitToInt(function_state[start + k], 1, 1);	//F部件占用
	k++;

	//判断D部件是否被占用
	while (CheckBit(function_state[start + k], 2) != 0)	//D部件被占用
	{
		pipeline_coordinates[instruction_no][start + k] = PIPELINE_PERIOD_NAME_SHORTEN[0];	//等待
		WriteBitToInt(function_state[start + k], 1, 1);	//F部件被占用
		k++;
	}
	//D部件可以使用
	pipeline_coordinates[instruction_no][start + k] = PIPELINE_PERIOD_NAME_SHORTEN[2];	//写入'D'
	WriteBitToInt(function_state[start + k], 2, 1);	//D部件被占用
	//对读后写的延时处理
	int which_need_read = WhichNeedRead(instruction_type, data);	//需要读的寄存器
	int which_need_write = WhichNeedWrite(instruction_type, data);	//需要写的寄存器
	register_time_state[start + k] |= which_need_write;
	k++;
	while (1)
	{
		if ((which_need_read & register_time_state[start + k]) == 0)
			break;
		//延时等待
		pipeline_coordinates[instruction_no][start + k] = PIPELINE_PERIOD_NAME_SHORTEN[0];
		WriteBitToInt(function_state[start + k], 2, 1);	//D部件被占用
		k++;
	}

	//判断E部件是否被占用
	while (CheckBit(function_state[start + k], 3) != 0)	//E部件被占用
	{
		pipeline_coordinates[instruction_no][start + k] = PIPELINE_PERIOD_NAME_SHORTEN[0];	//等待
		WriteBitToInt(function_state[start + k], 2, 1);	//D部件被占用
		register_time_state[start + k] |= which_need_write;
		k++;
	}
	//E部件可以使用
	pipeline_coordinates[instruction_no][start + k] = PIPELINE_PERIOD_NAME_SHORTEN[3];	//写入'E'
	WriteBitToInt(function_state[start + k], 3, 1);	//E部件被占用
	register_time_state[start + k] |= which_need_write;
	k++;

	//判断M部件是否被占用
	while (CheckBit(function_state[start + k], 4) != 0)	//M部件被占用
	{
		pipeline_coordinates[instruction_no][start + k] = PIPELINE_PERIOD_NAME_SHORTEN[0];	//等待
		WriteBitToInt(function_state[start + k], 3, 1);	//E部件被占用
		register_time_state[start + k] |= which_need_write;
		k++;
	}
	//M部件可以使用
	pipeline_coordinates[instruction_no][start + k] = PIPELINE_PERIOD_NAME_SHORTEN[4];	//写入'M'
	WriteBitToInt(function_state[start + k], 4, 1);	//M部件被占用
	register_time_state[start + k] |= which_need_write;
	k++;

	//判断指令是否有超前结束的可能
	if (instruction_no >= 1)
	{
		while (CheckPreviousInstructionIfDown(instruction_no, start + k) != true)
		{
			pipeline_coordinates[instruction_no][start + k] = PIPELINE_PERIOD_NAME_SHORTEN[0];
			register_time_state[start + k] |= which_need_write;
			k++;
		}
	}
	//判断W部件是否被占用
	while (CheckBit(function_state[start + k], 5) != 0)	//W部件被占用
	{
		pipeline_coordinates[instruction_no][start + k] = PIPELINE_PERIOD_NAME_SHORTEN[0];	//等待
		WriteBitToInt(function_state[start + k], 4, 1);	//M部件被占用
		register_time_state[start + k] |= which_need_write;
		k++;
	}
	//W部件可以使用
	pipeline_coordinates[instruction_no][start + k] = PIPELINE_PERIOD_NAME_SHORTEN[5];	//写入'W'
	WriteBitToInt(function_state[start + k], 5, 1);	//W部件被占用
	register_time_state[start + k] |= which_need_write;
	k++;

	//对本条指令所占用的寄存器进行释放
	register_time_state[start + k + 1] &= ~which_need_write;
	//本条指令所对应的行已被占用
	if_write[instruction_no] = true;
	return 0;
}

int CPipeline::CreatePipelineStep(int step_num)
{

	for (int i = 0; i <= CheckInstructionNum() - 1; i++)
	{
		for (int j = 0; j <=step_num; j++)
		{
			pipeline_coordinates_type_2[i][j] = pipeline_coordinates[i][j];
		}
	}
	return 0;
}

bool CPipeline::CheckAnyInstruction(int step_num)
{
	int sum = 0;
	for (int i = 0; i < PIPELINE_X_NUM; i++)
	{
		sum += pipeline_coordinates[i][step_num];
	}
	if (sum == PIPELINE_PERIOD_NAME_SHORTEN[6] * PIPELINE_X_NUM)
		return false;
	return true;
}

void CPipeline::WriteCoordinatesToFile()
{
	ofstream outfile, graphics;
	outfile.open("pipeline.txt", ios::out);
	graphics.open("graphics.txt", ios::out);
	for (int i = CheckInstructionNum() - 1; i >= 0; i--)
	{
		outfile << i << "\t";
		for (int j = 0;; j++)
		{
			if (pipeline_coordinates[i][j - 1] == PIPELINE_PERIOD_NAME_SHORTEN[7])
				break;
			if (pipeline_coordinates[i][j - 1] == PIPELINE_PERIOD_NAME_SHORTEN[5])
				break;
			if (pipeline_coordinates[i][j] == PIPELINE_PERIOD_NAME_SHORTEN[0])	//U等待
			{
				outfile << "U ";
				graphics << "U";
			}
			else if (pipeline_coordinates[i][j] == PIPELINE_PERIOD_NAME_SHORTEN[6])	//X空
			{
				outfile << "  ";
				graphics << "X";
			}
			else if (pipeline_coordinates[i][j] == PIPELINE_PERIOD_NAME_SHORTEN[7])	//B禁止
			{
				outfile << "B ";
				graphics << "B";
			}
			else
			{
				outfile << pipeline_coordinates[i][j] << " ";
				graphics << pipeline_coordinates[i][j];
			}
		}
		outfile << "\n";
		graphics << "\n";
	}
	outfile.close();
	graphics.close();
}

void CPipeline::WriteCoordinatesToFileType2(int step_num)
{
	ofstream outfile, graphics;
	outfile.open("pipeline_step.txt", ios::out);
	graphics.open("graphics.txt", ios::out);
	for (int i = CheckInstructionNum() - 1; i >= 0; i--)
	{
		outfile << i << "\t";
		for (int j = 0; j <= step_num; j++)
		{
			if (pipeline_coordinates_type_2[i][j - 1] == PIPELINE_PERIOD_NAME_SHORTEN[7])
				break;
			if (pipeline_coordinates_type_2[i][j - 1] == PIPELINE_PERIOD_NAME_SHORTEN[5])
				break;
			if (pipeline_coordinates_type_2[i][j] == PIPELINE_PERIOD_NAME_SHORTEN[0])	//U等待
			{
				outfile << "U ";
				graphics << "U";
			}
			else if (pipeline_coordinates_type_2[i][j] == PIPELINE_PERIOD_NAME_SHORTEN[6])	//X空
			{
				outfile << "  ";
				graphics << "X";
			}
			else if (pipeline_coordinates_type_2[i][j] == PIPELINE_PERIOD_NAME_SHORTEN[7])	//B禁止
			{
				outfile << "B ";
				graphics << "B";
			}
			else
			{
				outfile << pipeline_coordinates_type_2[i][j] << " ";
				graphics << pipeline_coordinates_type_2[i][j];
			}
		}
		outfile << "\n";
		graphics << "\n";
	}
	outfile.close();
	graphics.close();
}

int CPipeline::IfExistInstructionOnOneTime(int time, char mode)
{
	for (int i = 0; i < PIPELINE_X_NUM; i++)
	{
		if (pipeline_coordinates_type_2[i][time] == mode)
			return i;
	}
	return NOTEXISTTHISINSTRUCTIONONONETIME;
}