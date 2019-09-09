#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <graphics.h>

constexpr int MEMORY_INSTRUCTION_SIZE = 256;	//指令区长度
constexpr int PIPELINE_X_NUM = MEMORY_INSTRUCTION_SIZE / 4;
constexpr int PIPELINE_Y_NUM = 1000;
constexpr int DRAW_START_LEFT = 100;
constexpr int DRAW_START_UP = 100;
constexpr int RECTANGLE_WIDTH = 50;
constexpr int RECTANGLE_HEIGHT = 25;
TCHAR INSTRUCTION_NUM[71][3] = { _T("00"),_T("01"),_T("02"), _T("03"), _T("04"), _T("05"), _T("06"), _T("07"), _T("08"), _T("09"),_T("10"),
											_T("11"),_T("12"), _T("13"), _T("14"), _T("15"), _T("16"), _T("17"), _T("18"), _T("19"),_T("20"),
											_T("21"),_T("22"), _T("23"), _T("24"), _T("25"), _T("26"), _T("27"), _T("28"), _T("29"),_T("30"),
											_T("31"),_T("32"), _T("33"), _T("34"), _T("35"), _T("36"), _T("37"), _T("38"), _T("39"),_T("40"),
											_T("41"),_T("42"), _T("43"), _T("44"), _T("45"), _T("46"), _T("47"), _T("48"), _T("49"),_T("50"),
											_T("51"),_T("52"), _T("53"), _T("54"), _T("55"), _T("56"), _T("57"), _T("58"), _T("59"),_T("60"),
											_T("61"),_T("62"), _T("63"), _T("64"), _T("65"), _T("66"), _T("67"), _T("68"), _T("69"),_T("70"),
																																			};
#define EMPTY_COLOR RGB(255,255,255)
#define FETCH_COLOR RGB(146,208,80)
#define FETCH_WAIT_COLOR RGB(192,230,162)
#define DECODE_COLOR RGB(234,184,130)
#define DECODE_WAIT_COLOR RGB(242,213,181)
#define EXECUTE_COLOR RGB(241,139,149)
#define EXECUTE_WAIT_COLOR RGB(247,189,194)
#define MEMORY_COLOR RGB(128,117,235)
#define MEMORY_WAIT_COLOR RGB(181,175,243)
#define WRITEBACK_COLOR RGB(232,140,48)
#define BAN_COLOR RGB(255,0,0)

void CreateText(int left, int up, char mode)
{
	settextcolor(BLACK);
	if (mode == 'F')
		setbkcolor(FETCH_COLOR);
	if (mode == 'D')
		setbkcolor(DECODE_COLOR);
	if (mode == 'E')
		setbkcolor(EXECUTE_COLOR);
	if (mode == 'M')
		setbkcolor(MEMORY_COLOR);
	if (mode == 'W')
		setbkcolor(WRITEBACK_COLOR);
	if (mode == 'B')
		setbkcolor(BAN_COLOR);
	if (mode == 'G')	//Fetch Wait
		setbkcolor(FETCH_WAIT_COLOR);
	if (mode == 'S')	//Decode Wait
		setbkcolor(DECODE_WAIT_COLOR);
	if (mode == 'R')	//Execute Wait
		setbkcolor(EXECUTE_WAIT_COLOR);
	if (mode == 'N')	//Memory Wait
		setbkcolor(MEMORY_WAIT_COLOR);
	settextstyle(24, 0, _T("Courier New"));
	if (mode == 'G')
	{
		outtextxy(left + RECTANGLE_WIDTH / 2 - 5, up + RECTANGLE_HEIGHT / 2 - 11, 'F');
		return;
	}
	if (mode == 'S')
	{
		outtextxy(left + RECTANGLE_WIDTH / 2 - 5, up + RECTANGLE_HEIGHT / 2 - 11, 'D');
		return;
	}
	if (mode == 'R')
	{
		outtextxy(left + RECTANGLE_WIDTH / 2 - 5, up + RECTANGLE_HEIGHT / 2 - 11, 'E');
		return;
	}
	if (mode == 'N')
	{
		outtextxy(left + RECTANGLE_WIDTH / 2 - 5, up + RECTANGLE_HEIGHT / 2 - 11, 'M');
		return;
	}
	outtextxy(left + RECTANGLE_WIDTH / 2 - 5, up + RECTANGLE_HEIGHT / 2 - 11, mode);
}

void DrawEmpty(int left, int up, int right, int down)
{
	setfillstyle(BS_SOLID);
	setlinecolor(EMPTY_COLOR);
	setfillcolor(EMPTY_COLOR);
	fillrectangle(left, up, right, down);
}
void DrawFetch(int left, int up, int right, int down)
{
	setfillstyle(BS_SOLID);
	setlinecolor(BLACK);
	setfillcolor(FETCH_COLOR);
	fillrectangle(left, up, right, down);
	CreateText(left, up, 'F');
}
void DrawFetchWait(int left, int up, int right, int down)
{
	setfillstyle(BS_SOLID);
	setlinecolor(BLACK);
	setfillcolor(FETCH_WAIT_COLOR);
	fillrectangle(left, up, right, down);
	CreateText(left, up, 'G');
}
void DrawDecode(int left, int up, int right, int down)
{
	setfillstyle(BS_SOLID);
	setlinecolor(BLACK);
	setfillcolor(DECODE_COLOR);
	fillrectangle(left, up, right, down);
	CreateText(left, up, 'D');
}
void DrawDecodeWait(int left, int up, int right, int down)
{
	setfillstyle(BS_SOLID);
	setlinecolor(BLACK);
	setfillcolor(DECODE_WAIT_COLOR);
	fillrectangle(left, up, right, down);
	CreateText(left, up, 'S');
}
void DrawExecute(int left, int up, int right, int down)
{
	setfillstyle(BS_SOLID);
	setlinecolor(BLACK);
	setfillcolor(EXECUTE_COLOR);
	fillrectangle(left, up, right, down);
	CreateText(left, up, 'E');
}
void DrawExecuteWait(int left, int up, int right, int down)
{
	setfillstyle(BS_SOLID);
	setlinecolor(BLACK);
	setfillcolor(EXECUTE_WAIT_COLOR);
	fillrectangle(left, up, right, down);
	CreateText(left, up, 'R');
}
void DrawMemory(int left, int up, int right, int down)
{
	setfillstyle(BS_SOLID);
	setlinecolor(BLACK);
	setfillcolor(MEMORY_COLOR);
	fillrectangle(left, up, right, down);
	CreateText(left, up, 'M');
}
void DrawMemoryWait(int left, int up, int right, int down)
{
	setfillstyle(BS_SOLID);
	setlinecolor(BLACK);
	setfillcolor(MEMORY_WAIT_COLOR);
	fillrectangle(left, up, right, down);
	CreateText(left, up, 'N');
}
void DrawWriteBack(int left, int up, int right, int down)
{
	setfillstyle(BS_SOLID);
	setlinecolor(BLACK);
	setfillcolor(WRITEBACK_COLOR);
	fillrectangle(left, up, right, down);
	CreateText(left, up, 'W');
}
void DrawBan(int left, int up, int right, int down)
{
	setfillstyle(BS_SOLID);
	setlinecolor(BLACK);
	setfillcolor(BAN_COLOR);
	fillrectangle(left, up, right, down);
	CreateText(left, up, 'B');
}

int main()
{
	initgraph(1400, 600);
	while (1)
	{
		FILE *read = fopen("graphics.txt", "r");
		if (read == NULL) exit(0);
		char coordinates[PIPELINE_X_NUM][PIPELINE_Y_NUM] = { '\0' };
		char read_char;
		int read_line = 0, address = 0;
		while (!feof(read))
		{
			fscanf(read, "%c", &read_char);
			if (read_char == '\n')
			{
				read_line++;
				address = 0;
				continue;
			}
			coordinates[read_line][address++] = read_char;
		}
		//for (int i = 0; i < PIPELINE_X_NUM; i++)
		//{
		//	if (coordinates[i][0] == '\0')
		//		break;
		//	for (int j = 0; j < PIPELINE_Y_NUM; j++)
		//		if (coordinates[i][j] != '\0')
		//			printf("%c", coordinates[i][j]);
		//	printf("\n");
		//}
		fclose(read);

		//开始绘图
		setbkcolor(WHITE);	//设置背景颜色为白色
		cleardevice();

		char last_state='X';
		int i = 0, j = 0, max_j = 0;
		for (i = 0; i < PIPELINE_X_NUM; i++)
		{
			if (coordinates[i][0] == '\0')
				break;
			for (j = 0; j < PIPELINE_Y_NUM; j++)
			{
				max_j = j > max_j ? j : max_j;
				if (coordinates[i][j] == 'F')
				{
					DrawFetch(DRAW_START_LEFT + j * RECTANGLE_WIDTH, DRAW_START_UP + i * RECTANGLE_HEIGHT, DRAW_START_LEFT + (j + 1) * RECTANGLE_WIDTH, DRAW_START_UP + (i + 1) * RECTANGLE_HEIGHT);
					last_state = 'F';
				}
				if (coordinates[i][j] == 'D')
				{
					DrawDecode(DRAW_START_LEFT + j * RECTANGLE_WIDTH, DRAW_START_UP + i * RECTANGLE_HEIGHT, DRAW_START_LEFT + (j + 1) * RECTANGLE_WIDTH, DRAW_START_UP + (i + 1) * RECTANGLE_HEIGHT);
					last_state = 'D';
				}
				if (coordinates[i][j] == 'E')
				{
					DrawExecute(DRAW_START_LEFT + j * RECTANGLE_WIDTH, DRAW_START_UP + i * RECTANGLE_HEIGHT, DRAW_START_LEFT + (j + 1) * RECTANGLE_WIDTH, DRAW_START_UP + (i + 1) * RECTANGLE_HEIGHT);
					last_state = 'E';
				}
				if (coordinates[i][j] == 'M')
				{
					DrawMemory(DRAW_START_LEFT + j * RECTANGLE_WIDTH, DRAW_START_UP + i * RECTANGLE_HEIGHT, DRAW_START_LEFT + (j + 1) * RECTANGLE_WIDTH, DRAW_START_UP + (i + 1) * RECTANGLE_HEIGHT);
					last_state = 'M';
				}
				if (coordinates[i][j] == 'W')
				{
					DrawWriteBack(DRAW_START_LEFT + j * RECTANGLE_WIDTH, DRAW_START_UP + i * RECTANGLE_HEIGHT, DRAW_START_LEFT + (j + 1) * RECTANGLE_WIDTH, DRAW_START_UP + (i + 1) * RECTANGLE_HEIGHT);
				}
				if (coordinates[i][j] == 'X')
					DrawEmpty(DRAW_START_LEFT + j * RECTANGLE_WIDTH, DRAW_START_UP + i * RECTANGLE_HEIGHT, DRAW_START_LEFT + (j + 1) * RECTANGLE_WIDTH, DRAW_START_UP + (i + 1) * RECTANGLE_HEIGHT);
				if (coordinates[i][j] == 'B')
					DrawBan(DRAW_START_LEFT + j * RECTANGLE_WIDTH, DRAW_START_UP + i * RECTANGLE_HEIGHT, DRAW_START_LEFT + (j + 1) * RECTANGLE_WIDTH, DRAW_START_UP + (i + 1) * RECTANGLE_HEIGHT);
				if (coordinates[i][j] == 'U')
				{
					if (last_state == 'F')
						DrawFetchWait(DRAW_START_LEFT + j * RECTANGLE_WIDTH, DRAW_START_UP + i * RECTANGLE_HEIGHT, DRAW_START_LEFT + (j + 1) * RECTANGLE_WIDTH, DRAW_START_UP + (i + 1) * RECTANGLE_HEIGHT);
					if (last_state == 'D')
						DrawDecodeWait(DRAW_START_LEFT + j * RECTANGLE_WIDTH, DRAW_START_UP + i * RECTANGLE_HEIGHT, DRAW_START_LEFT + (j + 1) * RECTANGLE_WIDTH, DRAW_START_UP + (i + 1) * RECTANGLE_HEIGHT);
					if (last_state == 'E')
						DrawExecuteWait(DRAW_START_LEFT + j * RECTANGLE_WIDTH, DRAW_START_UP + i * RECTANGLE_HEIGHT, DRAW_START_LEFT + (j + 1) * RECTANGLE_WIDTH, DRAW_START_UP + (i + 1) * RECTANGLE_HEIGHT);
					if (last_state == 'M')
						DrawMemoryWait(DRAW_START_LEFT + j * RECTANGLE_WIDTH, DRAW_START_UP + i * RECTANGLE_HEIGHT, DRAW_START_LEFT + (j + 1) * RECTANGLE_WIDTH, DRAW_START_UP + (i + 1) * RECTANGLE_HEIGHT);
				}
				if (coordinates[i][j + 1] == '\0')
					break;
			}
		}
		//建立XY坐标系
		setlinestyle(PS_SOLID, 3);
		line(DRAW_START_LEFT / 2 + 40, DRAW_START_UP / 2, DRAW_START_LEFT / 2 + 40, DRAW_START_UP + (i + 2) * RECTANGLE_HEIGHT + 10);
		line(DRAW_START_LEFT / 2, DRAW_START_UP + (i + 1)*RECTANGLE_HEIGHT - RECTANGLE_HEIGHT / 2-3, DRAW_START_LEFT + (max_j+2) * RECTANGLE_WIDTH, DRAW_START_UP + (i + 1)*RECTANGLE_HEIGHT - RECTANGLE_HEIGHT / 2-3);
		//恢复画笔的粗细
		setlinestyle(PS_SOLID);
		//标出指令的序号
		for (int q = i; q > 0; q--)
		{
			settextcolor(BLACK);
			setbkcolor(WHITE);
			settextstyle(24, 0, _T("Courier New"));
			outtextxy(DRAW_START_LEFT / 2, DRAW_START_UP + (q - 1) * RECTANGLE_HEIGHT, INSTRUCTION_NUM[i-q]);
		}
		//标出时间片
		for (int e = 0; e <= max_j; e++)
		{
			settextcolor(BLACK);
			setbkcolor(WHITE);
			settextstyle(24, 0, _T("Courier New"));
			outtextxy(DRAW_START_LEFT + e * RECTANGLE_WIDTH + RECTANGLE_WIDTH / 3, DRAW_START_UP + (i + 0.6) * RECTANGLE_HEIGHT + RECTANGLE_HEIGHT / 2 - 11, INSTRUCTION_NUM[e]);
		}
		Sleep(1000);
	}
	system("PAUSE");
	return 0;
}