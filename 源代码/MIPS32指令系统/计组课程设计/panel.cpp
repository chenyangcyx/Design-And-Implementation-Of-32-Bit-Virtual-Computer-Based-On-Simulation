#include <iostream>
#include "panel.h"
#include <stdlib.h>
using namespace std;

int CPanel::PanelChoose()
{
	int choose_num = 0, two_choose_num = 0;
	choose_num = ShowMainPanel();
	switch (choose_num)
	{
	case PANEL_MAIN_ADD + 1:
		two_choose_num = ShowChoose1Panel();
		break;
	case PANEL_MAIN_ADD + 2:
		two_choose_num = ShowChoose2Panel();
		break;
	case PANEL_MAIN_ADD + 3:
		two_choose_num = ShowChoose3Panel();
		break;
	case PANEL_MAIN_ADD + 4:
		two_choose_num = ShowChoose4Panel();
		break;
	case PANEL_MAIN_ADD + 5:
		two_choose_num = ShowChoose5Panel();
		break;
	case PANEL_MAIN_ADD + 6:
		two_choose_num = ShowChoose6Panel();
		break;
	case PANEL_MAIN_ADD + 7:
		two_choose_num = ShowChoose7Panel();
		break;
	case PANEL_MAIN_ADD + 8:
		two_choose_num = ShowChoose8Panel();
		break;
	default:
		two_choose_num = PANEL_CHOOSE_ERROR_CODE;
		break;
	}
	return two_choose_num;
}

int CPanel::ShowMainPanel()
{
	system("cls");
	cout << "********************MIPS32指令系统********************" << endl;
	cout << "*                                                    *" << endl;
	cout << "*                                                    *" << endl;
	cout << "*           1-指令控制           2-指令执行          *" << endl;
	cout << "*                                                    *" << endl;
	cout << "*           3-内存控制           4-寄存器控制        *" << endl;
	cout << "*                                                    *" << endl;
	cout << "*           5-流水线             6-使用说明          *" << endl;
	cout << "*                                                    *" << endl;
	cout << "*           7-关于               8-退出              *" << endl;
	cout << "*                                                    *" << endl;
	cout << "*                                                    *" << endl;
	cout << "******************************************************" << endl;
	cout << endl << "请输入执行序号：  ";
	int choose_num = 0;
	cin >> choose_num;
	while (choose_num < 1 || choose_num > 8)
	{
		cout << endl << "输入错误！请重新输入：  ";
		cin >> choose_num;
	}
	return choose_num + PANEL_MAIN_ADD;
}

//指令控制
int CPanel::ShowChoose1Panel()
{
	system("cls");
	cout << "***********指令控制***********" << endl;
	cout << "*                            *" << endl;
	cout << "*         1-输入指令         *" << endl;
	cout << "*                            *" << endl;
	cout << "*         2-查看指令         *" << endl;
	cout << "*                            *" << endl;
	cout << "*         3-修改指令         *" << endl;
	cout << "*                            *" << endl;
	cout << "*         4-清空指令         *" << endl;
	cout << "*                            *" << endl;
	cout << "******************************" << endl;
	cout << endl << "请输入执行序号（0返回上级菜单）：  ";
	int choose_num = 0;
	cin >> choose_num;
	if (choose_num == 0)
		return PANEL_RETURN_TO_MAIN_PANEL;
	while (choose_num < 1 || choose_num > 4)
	{
		cout << endl << "输入错误！请重新输入：  ";
		cin >> choose_num;
	}
	if (choose_num == 0)
		return PANEL_RETURN_TO_MAIN_PANEL;
	return choose_num + PANEL_1_ADD;
}

//指令执行
int CPanel::ShowChoose2Panel()
{
	system("cls");
	cout << "***********指令执行***********" << endl;
	cout << "*                            *" << endl;
	cout << "*         1-全部执行         *" << endl;
	cout << "*                            *" << endl;
	cout << "*         2-单步执行         *" << endl;
	cout << "*                            *" << endl;
	cout << "*         3-执行记录         *" << endl;
	cout << "*                            *" << endl;
	cout << "*         4-清除记录         *" << endl;
	cout << "*                            *" << endl;
	cout << "******************************" << endl;
	cout << endl << "请输入执行序号（0返回上级菜单）：  ";
	int choose_num = 0;
	cin >> choose_num;
	if (choose_num == 0)
		return PANEL_RETURN_TO_MAIN_PANEL;
	while (choose_num < 1 || choose_num > 4)
	{
		cout << endl << "输入错误！请重新输入：  ";
		cin >> choose_num;
	}
	if (choose_num == 0)
		return PANEL_RETURN_TO_MAIN_PANEL;
	return choose_num + PANEL_2_ADD;
}

//内存控制
int CPanel::ShowChoose3Panel()
{
	system("cls");
	cout << "*************内存控制*************" << endl;
	cout << "*                                *" << endl;
	cout << "*       1-初始化内存（全0）      *" << endl;
	cout << "*                                *" << endl;
	cout << "*       2-初始化内存（指定值）   *" << endl;
	cout << "*                                *" << endl;
	cout << "*       3-修改内存               *" << endl;
	cout << "*                                *" << endl;
	cout << "*       4-查看内存               *" << endl;
	cout << "*                                *" << endl;
	cout << "**********************************" << endl;
	cout << endl << "请输入执行序号（0返回上级菜单）：  ";
	int choose_num = 0;
	cin >> choose_num;
	if (choose_num == 0)
		return PANEL_RETURN_TO_MAIN_PANEL;
	while (choose_num < 1 || choose_num > 4)
	{
		cout << endl << "输入错误！请重新输入：  ";
		cin >> choose_num;
	}
	if (choose_num == 0)
		return PANEL_RETURN_TO_MAIN_PANEL;
	return choose_num + PANEL_3_ADD;
}

//寄存器控制
int CPanel::ShowChoose4Panel()
{
	system("cls");
	cout << "*************寄存器控制*************" << endl;
	cout << "*                                  *" << endl;
	cout << "*       1-初始化寄存器（全0）      *" << endl;
	cout << "*                                  *" << endl;
	cout << "*       2-初始化寄存器（指定值）   *" << endl;
	cout << "*                                  *" << endl;
	cout << "*       3-修改寄存器               *" << endl;
	cout << "*                                  *" << endl;
	cout << "*       4-查看寄存器               *" << endl;
	cout << "*                                  *" << endl;
	cout << "***********************************" << endl;
	cout << endl << "请输入执行序号（0返回上级菜单）：  ";
	int choose_num = 0;
	cin >> choose_num;
	if (choose_num == 0)
		return PANEL_RETURN_TO_MAIN_PANEL;
	while (choose_num < 1 || choose_num > 4)
	{
		cout << endl << "输入错误！请重新输入：  ";
		cin >> choose_num;
	}
	if (choose_num == 0)
		return PANEL_RETURN_TO_MAIN_PANEL;
	return choose_num + PANEL_4_ADD;
}

//流水线
int CPanel::ShowChoose5Panel()
{
	system("cls");
	cout << "************流水线**********" << endl;
	cout << "*                          *" << endl;
	cout << "*       1-生成流水线       *" << endl;
	cout << "*                          *" << endl;
	cout << "*       2-单步执行         *" << endl;
	cout << "*                          *" << endl;
	cout << "*       3-清空流水线       *" << endl;
	cout << "*                          *" << endl;
	cout << "****************************" << endl;
	cout << endl << "请输入执行序号（0返回上级菜单）：  ";
	int choose_num = 0;
	cin >> choose_num;
	if (choose_num == 0)
		return PANEL_RETURN_TO_MAIN_PANEL;
	while (choose_num < 1 || choose_num > 3)
	{
		cout << endl << "输入错误！请重新输入：  ";
		cin >> choose_num;
	}
	if (choose_num == 0)
		return PANEL_RETURN_TO_MAIN_PANEL;
	return choose_num + PANEL_5_ADD;
}

int CPanel::ShowChoose6Panel()
{
	system("cls");
	cout << "1.1.1 指令控制" << endl;
	cout << "	本功能模块负责指令的输入输出。程序在运行之前，必须有已经输入的指令序列，否则将不能够正常执行而直接退出。如果用户想要正常的使用该程序，则必须将已经准备好的指令序列输入。因为该虚拟计算机基于MIPS32指令集，所以每一条指令的长度固定为32位长度的0/1序列。" << endl;
	cout << "在输入时，用户可以选择单行或多行输入，但是在输入完毕后，必须另起一行，并以”##”作为结束标识，否则程序将不能够正确读取并译码。" << endl;
	cout << "	在该模块下，有4个子模块，提供更加准确的指令控制，分别为：输入指令、查看指令、修改指令、清空指令，详细介绍如下：" << endl;
	cout << "	（1）输入指令：提供单行或多行输入指令的功能，输入的指令将顺序存储在内存的00H-FFH区域。每一条32位的指令占用4个内存空间。" << endl;
	cout << "	（2）查看指令：从内存的00H开始读取，直至FFH，若读取的内存区域不为00H内容，则判断有指令。程序调用“译码”功能，将32位的指令译码为能够阅读的汇编代码。" << endl;
	cout << "	（3）修改指令：用户指定一个需要修改的指令地址，并给出要修改的指令。程序将根据指令地址与指令内容修改。注意，如果提供的指令地址与指令内容非法，程序将拒绝执行，要求用户重新提供正确的地址与内容。" << endl;
	cout << "	（4）清空指令：清空程序内存区域中指令区域的所有指令内容，即将内存00H-FFH区域全部强制填为00H。" << endl;
	cout << "" << endl;
	cout << "1.1.2 指令执行" << endl;
	cout << "	本功能模块负责指令的执行控制。当用户输入指令后，便可以使用该功能模块模拟执行指令。注意，此功能模块所提供的指令执行是串行执行方法，与“项目简介”中所描述的“流水线”功能无关。" << endl;
	cout << "	该功能模块下可细分为4个子模块，分别为：全部执行、单步执行、执行记录、清除记录，详细介绍如下：" << endl;
	cout << "	（1）全部执行：一步执行完（内存指令区域的）全部指令，当执行完后，程序会列出所执行过的全部指令内容 。" << endl;
	cout << "	（2）单步执行：每次执行一条（内存指令区域）指令，当执行完后，程序会列出所执行过的指令的指令内容。" << endl;
	cout << "	在“全部执行”与“单步执行”过程中，程序每次执行一条指令，都会向”record.txt”文件中写入一条执行记录，写入方式为追加写入，每次执行都会新起一行，不会修改之前写入过的记录。执行记录详细记录了指令执行的各项细节，包括：执行时间、指令内容、指令解释、涉及到的寄存器。用户可以在程序目录下的”record.txt”文件中查看具体的细节。" << endl;
	cout << "	（3）执行记录：查看存储在程序同目录下”record.txt”文件中的内容，即所有的指令执行记录。" << endl;
	cout << "	（4）清除记录：将存储在程序同目录下”record.txt”文件中的内容全部清空。" << endl;
	cout << "" << endl;
	cout << "1.1.3 内存控制" << endl;
	cout << "	本功能模块负责内存内容的添加修改。模拟计算机提供了内存模块，来存储与程序运行相关的数据。内存模块具体分为指令区域与数据区域，指令区域的地址范围为：00H-FFH，数据区域的地址范围为：100H-2FFH。对指令操作时，只影响指令区域，不影响数据区域；对数据操作时，只影响数据区域，不影响指令区域。" << endl;
	cout << "	本功能模块下可细分为4个子模块，分别为：初始化内存（全0）、初始化内存（指定值）、修改内存、查看内存，详细介绍如下：" << endl;
	cout << "	（1）初始化内存（全0）：将内存数据区域100H-2FFH全部修改为00H。" << endl;
	cout << "	（2）初始化内存（指定值）：用户给出需要修改的指定值，程序将数据区域100H-2FFH全部修改为用户给出的指定值。" << endl;
	cout << "	（3）修改内存：该功能可以指定修改某一特定地址的内存值为某指定值。程序将会要求用户给出需要修改的内存地址与要修改的内存的值并做出修改。注意，若用户给出的内存地址与数据非法，程序将会拒绝执行，并要求用户重新给出可用的数据。" << endl;
	cout << "	（4）查看内存：程序按照内存地址顺序给出每一个地址的内容。在显示数据时，将先按照指令区域、数据区域进行分类，然后，以每行10个展示。" << endl;
	cout << "" << endl;
	cout << "1.1.4 寄存器控制" << endl;
	cout << "	本功能模块负责寄存器内容的添加修改。模拟计算机提供了寄存器模块，来存储程序运行所需要的各个寄存器数据与寄存器本身。根据MIPS32指令集的设计，程序中共有32个不同的寄存器 ，对应不同的功能。" << endl;
	cout << "	本功能模块下可细分为4个子模块，分别为：初始化寄存器（全0）、初始化寄存器（指定值）、修改寄存器、查看寄存器，详细介绍如下：" << endl;
	cout << "	（1）初始化寄存器（全0）：将32个寄存器全部修改为00H。" << endl;
	cout << "	（2）初始化寄存器（指定值）：用户给出需要修改的指定值，程序将32个寄存器统一修改为用户给出的指定值。" << endl;
	cout << "	（3）修改寄存器：该功能可以指定修改某一特定的寄存器值。程序将会要求用户给出需要修改的寄存器序号与要修改的寄存器值并做出修改。注意，若用户给出的寄存器序号与数据非法，程序将会拒绝执行，并要求用户重新给出可用的数据。" << endl;
	cout << "	（4）查看寄存器：程序读取32个寄存器的值，并将他们的数据以16进制的方式显示出来，供使用者查阅。" << endl;
	cout << "" << endl;
	cout << "1.1.5 流水线" << endl;
	cout << "	本功能模块负责将程序中已有的指令序列使用流水线的方式展示并运行。该功能模块是整个程序的核心，也是整个程序设计的精华所在，笔者设计的程序架构、模块划分及整合以及独特的算法思想，将在这一模块中集中体现。" << endl;
	cout << "	为了能够区别模拟计算机中“流水线”功能的独特与其优越性，故单独设计这一功能模块并将它和其他模块区别是有必要的。" << endl;
	cout << "	该功能模块为用户详细了解程序内部流水线的运行机制提供了方法，利用图形化的方法 展示了流水线五个步骤 的详细划分。" << endl;
	cout << "	本功能模块下可细分为3个功能模块，分别为：生成流水线、单步执行、清空流水线，详细介绍如下：" << endl;
	cout << "	（1）生成流水线：程序根据当前内存指令区域的指令，依照“流水线算法”（该算法在后文将会详细介绍），生成程序的流水线过程。由于该模拟计算机对于流水线阻滞的处理方法为暂停执行，故采用了图示的方式进行展示。注意，使用该功能，只会生成流水线图，但程序并不会真正执行指令，所以使用完该功能后，程序的PC指针位置、内存数据、寄存器数据都不会改变。同时，生成的流水线图将存储在程序目录下的”pipeline.txt”和”graphics.txt”文件中。其中，”pipeline.txt”文件为记录文件，供读者查阅使用，”graphics.txt”文件为图像生成缓存，供“流水线绘图.exe”调用绘图。" << endl;
	cout << "	（2）单步执行：程序根据当前内存指令区域的指令，依照“流水线算法”（该算法在后文将会详细介绍），单步生成程序的流水线过程。根据流水线时间划分的原则，使用单步执行也将逐个时间点展示具体的操作过程。每执行一步，程序将会暂停，展示流水线当前的推进情况、所有寄存器中的数据、每一条指令当前所处的状态，同时，PC指针、内存、寄存器中的值都会根据实际的情况改变。用户可以选择是否继续单步执行，若选择返回菜单，则流水线的推进过程直接结束。单步执行的记录存储于程序目录下的”pipeline_step.txt”文件中，同时，也会生成一份图像生成缓存，存储在”graphics.txt”文件中，供“流水线绘图.exe”调用绘图。" << endl;
	cout << "	（3）清空流水线：程序将位于程序目录下的”pipeline.txt”、”pipeline_step.txt”与”graphics.txt”文件全部清空。" << endl;
	cout << "" << endl;
	cout << "1.1.6 使用说明" << endl;
	cout << "	本功能模块具体介绍了程序的使用说明与注意事项。该功能模块中所提供的使用说明与注意事项与本文档的第二部分“功能描述”完全一致，若读者已经熟读并记住了本节内容，则不必再重复查看程序的这一部分。" << endl;
	cout << "" << endl;
	cout << "1.1.7 关于" << endl;
	cout << "	本功能模块介绍了程序的作者信息。具体的信息有：项目名称、作者、学号、班级。" << endl;
	cout << "" << endl;
	cout << "1.1.8 退出" << endl;
	cout << "	本功能模块负责对程序所使用的内存空间进行释放，并安全的结束程序运行，退出程序。" << endl;
	cout << "" << endl;
	cout << "1.1.9 流水线绘图" << endl;
	cout << "	“流水线绘图”程序是一个单独的、使用C语言编写的、基于graphics图形库的程序，目的是将图像生成缓存生成为具体的流水线图形图像。对于“流水线绘图”程序的设计方法将在后文作具体的介绍。该程序没有具体的使用说明，只需要执行即可。注意，要使得改程序能够正常执行，请保证在该程序目录下有”graphics.txt”文档以供读取，同时，也要保证”graphics.txt”的格式正确。" << endl;
	cout << endl << "输入任意字符返回上级菜单：  ";
	int choose_num = 0;
	cin >> choose_num;
	return PANEL_6_ADD + 1;
}

int CPanel::ShowChoose7Panel()
{
	system("cls");
	cout << "**************关于**************" << endl;
	cout << "*                              *" << endl;
	cout << "*     项目：MIPS32指令系统     *" << endl;
	cout << "*                              *" << endl;
	cout << "*     作者：陈扬               *" << endl;
	cout << "*                              *" << endl;
	cout << "*     学号：19316117           *" << endl;
	cout << "*                              *" << endl;
	cout << "*     班级：网络工程161班      *" << endl;
	cout << "*                              *" << endl;
	cout << "********************************" << endl;
	cout << endl << "输入任意字符返回上级菜单：  ";
	int choose_num = 0;
	cin >> choose_num;
	return PANEL_7_ADD + 1;
}

int CPanel::ShowChoose8Panel()
{
	return PANEL_8_ADD + 1;	//退出代码
}
