// #include<stdio.h>
// #define _CRT_SECURE_NO_WARNINGS
// #include<utility>
// #include<easyx.h>
// #include<stdlib.h>
// #include<ctype.h>
// #include<string.h>
#include <conio.h>
#include <graphics.h>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
typedef pair<int, int> pi;
// 库函数以及基础定义

bool reserved;
struct licence
{
	int a1;
	int a2;
	int a3;
	int a4;
	int a5;
	pi d1;
	pi d2;
	int score;
	bool occupied;
	bool occupy = 0;
};
int count(licence x)
{
	return x.a1 + x.a2 + x.a3 + x.a4 + x.a5;
}
int cmp(licence a, licence b)
{
	return a.score > b.score;
}
// 座位设置

struct lie
{
	int key;
	int a1;
	int a2;
	int a3;
	int a4;
	int a5;

	pi situation;
	pi situation2;
	lie *next;
};

// 以下是数据库的部分
typedef struct
{
	int seat;	 // 座位状态：  0.未占用  1.已占用
	int badseat; // 坏座位状态  0.正常   1.坏座位
	int door;	 // 门状态      0.关闭   1.打开
	int socket;	 // 插座状态    0.无插座  1.有插座
	int clean;	 // 干净状态    0.干净   1.不干净

	int scores; // 分数
	int foolr;	// 楼层
	int class_; // 教室
	int row;	// 座位行
	int rol;	// 座位列

} Floor_Classroom;

Floor_Classroom myclassroom[144]; // 基础库，之后可扩展

// 占用座位
void occupySeat(Floor_Classroom c[144], int foolr, int class_, int row, int rol)
{
	for (int i = 0; i < 144; i++)
	{
		if (c[i].foolr == foolr && c[i].class_ == class_ && c[i].row == row && c[i].rol == rol)
		{
			c[i].seat = 1;
		}
	}
}
// 设置坏座位
void setbadseat(Floor_Classroom c[144], int foolr, int class_, int row, int rol)
{
	for (int i = 0; i < 144; i++)
	{
		if (c[i].foolr == foolr && c[i].class_ == class_ && c[i].row == row && c[i].rol == rol)
		{
			c[i].badseat = 1;
		}
	}
}
// 设置不干净
void setclean(Floor_Classroom c[144], int foolr, int class_, int row, int rol)
{
	for (int i = 0; i < 144; i++)
	{
		if (c[i].foolr == foolr && c[i].class_ == class_ && c[i].row == row && c[i].rol == rol)
		{
			c[i].clean = 1;
		}
	}
}
// 数据初始化
void initClassroom(Floor_Classroom c[144])
{
	int i;
	for (i = 0; i < 144; i++)
	{
		c[i].seat = 0;
		c[i].badseat = 0;
		c[i].door = 0;
		c[i].socket = 0;
		c[i].clean = 0;
		c[i].scores = 0;
	}
	int count_rol = 1;
	int count_row = 1;
	int count_class = 1;
	int count_foolr = 1;
	for (i = 0; i < 144; i++)
	{
		if (count_rol > 4)
		{
			count_rol = 1;
		}
		if (count_row > 4)
		{
			count_row = 1;
		}
		if (count_class > 3)
		{
			count_class = 1;
		}
		if (count_foolr > 3)
		{
			count_foolr = 1;
		}
		c[i].rol = count_rol;
		c[i].row = count_row;
		c[i].class_ = count_class;
		c[i].foolr = count_foolr;
		count_rol++;
		if ((i + 1) % 4 == 0)
		{
			count_row++;
		}
		if ((i + 1) % 16 == 0)
		{
			count_class++;
		}
		if ((i + 1) % 48 == 0)
		{
			count_foolr++;
		}
	}
	// 门状态初始化
	for (i = 0; i < 144; i++)
	{
		if (c[i].row == 1 && c[i].rol == 1)
		{
			c[i].door = 1;
		}
		if (c[i].row == 4 && c[i].rol == 1)
		{
			c[i].door = 1;
		}
		if (c[i].row == 1 && c[i].rol == 4)
		{
			c[i].door = 1;
		}
		if (c[i].row == 3 && c[i].rol == 4)
		{
			c[i].door = 1;
		}
	}
	// 插座初始化
	for (i = 0; i < 144; i++)
	{
		if (c[i].row == 1)
		{
			c[i].socket = 1;
		}
	}
	// 设置占用座位
	occupySeat(c, 1, 1, 1, 2);
	occupySeat(c, 1, 1, 2, 2);
	occupySeat(c, 1, 1, 3, 1);
	occupySeat(c, 1, 2, 2, 2);
	occupySeat(c, 1, 2, 3, 2);
	occupySeat(c, 1, 2, 4, 1);
	occupySeat(c, 1, 3, 1, 4);
	occupySeat(c, 1, 3, 3, 3);
	occupySeat(c, 1, 3, 4, 2);

	occupySeat(c, 2, 2, 1, 2);
	occupySeat(c, 2, 2, 2, 2);
	occupySeat(c, 2, 2, 3, 1);
	occupySeat(c, 2, 1, 2, 2);
	occupySeat(c, 2, 1, 3, 2);
	occupySeat(c, 2, 1, 4, 1);
	occupySeat(c, 2, 3, 1, 1);
	occupySeat(c, 2, 3, 2, 3);
	occupySeat(c, 2, 3, 4, 1);

	occupySeat(c, 3, 2, 2, 2);
	occupySeat(c, 3, 2, 3, 2);
	occupySeat(c, 3, 2, 4, 1);
	occupySeat(c, 3, 1, 3, 3);
	occupySeat(c, 3, 1, 1, 2);
	occupySeat(c, 3, 1, 3, 4);
	occupySeat(c, 3, 3, 1, 2);
	occupySeat(c, 3, 3, 2, 4);
	occupySeat(c, 3, 3, 4, 3);

	// 设置损坏座位
	setbadseat(c, 1, 1, 3, 2);
	setbadseat(c, 1, 1, 1, 2);
	setbadseat(c, 1, 2, 1, 2);
	setbadseat(c, 1, 2, 4, 2);
	setbadseat(c, 1, 3, 4, 2);
	setbadseat(c, 1, 3, 3, 3);

	setbadseat(c, 2, 1, 2, 3);
	setbadseat(c, 2, 1, 1, 4);
	setbadseat(c, 2, 2, 2, 2);
	setbadseat(c, 2, 2, 4, 3);
	setbadseat(c, 2, 3, 4, 1);
	setbadseat(c, 2, 3, 2, 3);

	setbadseat(c, 3, 1, 4, 2);
	setbadseat(c, 3, 1, 1, 3);
	setbadseat(c, 3, 2, 1, 4);
	setbadseat(c, 3, 2, 3, 2);
	setbadseat(c, 3, 3, 2, 3);
	setbadseat(c, 3, 3, 4, 4);

	// 设置不干净座位
	setclean(c, 1, 1, 1, 2);
	setclean(c, 1, 1, 3, 2);
	setclean(c, 1, 2, 4, 2);
	setclean(c, 1, 2, 3, 3);
	setclean(c, 1, 3, 1, 3);
	setclean(c, 1, 3, 4, 1);

	setclean(c, 2, 1, 2, 2);
	setclean(c, 2, 1, 3, 1);
	setclean(c, 2, 2, 4, 1);
	setclean(c, 2, 2, 2, 3);
	setclean(c, 2, 3, 3, 3);
	setclean(c, 2, 3, 4, 4);

	setclean(c, 3, 1, 1, 4);
	setclean(c, 3, 1, 3, 1);
	setclean(c, 3, 2, 2, 2);
	setclean(c, 3, 2, 1, 3);
	setclean(c, 3, 3, 1, 1);
	setclean(c, 3, 3, 2, 4);
}
// 以上是座位数据库的部分

int nowacc_num = 0; // 当前账号个数
typedef struct account
{
	char s_Num[30];	 // 账号
	char s_Mima[30]; // 密码
} account;
bool isReserved = false;
// 以上是账号定义

// 以下是函数库

// 以下是登录界面函数库
void menu();
void InputInfor();
void SaveInfor();
int cha();
void Printfind();
void ModiInfor();
void ReadInfor();
void Inputzhang();
void InputMima();

// 主界面函数
void menu2();

// 座位推荐页面函数
void Zuoweituijian();

// 以下为教室预览界面函数库
int sign_jian(int n);
int sign_jia(int n);
int sign_bubian(int n);
void creat(Floor_Classroom c[144], int n);
void click(int n);
void basic();
void jiaoshiyulan();

// 以下为签到签退界面函数库
void menuzhanghao();
void Qiandao();
void Qiantui();

// 以下为图形设置库
typedef struct
{
	int bottom;
	int top;
	int right;
	int left;
	int elwid;
	int elhei;
} bstl;

bstl blmain[3] =
	{
		{336, 170, 564, 210, 40, 40},
		{336, 240, 564, 280, 40, 40},
		{336, 310, 564, 350, 40, 40}
	};

account s[30];
int r1[] = {50, 200, 350, 275, 30, 30};
int r2[] = {50, 250, 350, 325, 30, 30};
int r3[] = {50, 375, 195, 450, 30, 30};
int r4[] = {205, 375, 350, 450, 30, 30};

int R1[] = {150, 75, 750, 175};
int r11[] = {200, 225, 700, 300, 80, 80};
int r21[] = {200, 350, 700, 425, 80, 80};
int r31[] = {350, 455, 550, 515, 80, 80};
int Fill1 = 0;
int deng1 = 0;
int x1, y1, x2, y2;

// 登录界面
void menu()
{
	ReadInfor();
	initgraph(400, 550);
	ExMessage m1;
	cleardevice();
	IMAGE img;
	loadimage(&img, "C:\\Users\\POMPEII\\Desktop\\fd5c543b0c2ac49f4cf6838bf9f868b.jpg", 400, 550);
	putimage(0, 0, &img);
	setbkmode(TRANSPARENT);
	setlinecolor(BLACK);
	setfillcolor(WHITE);
	fillroundrect(r1[0], r1[1], r1[2], r1[3], r1[4], r1[5]); // 画矩形，即按钮
	fillroundrect(r2[0], r2[1], r2[2], r2[3], r2[4], r2[5]);
	fillroundrect(r3[0], r3[1], r3[2], r3[3], r3[4], r3[5]); // 画矩形，即按钮
	fillroundrect(r4[0], r4[1], r4[2], r4[3], r4[4], r4[5]);
	RECT R2 = {r1[0], r1[1], r1[2], r1[3]};
	RECT R3 = {r2[0], r2[1], r2[2], r2[3]};
	RECT R4 = {r3[0], r3[1], r3[2], r3[3]};
	RECT R5 = {r4[0], r4[1], r4[2], r4[3]};
	LOGFONT f;		  // 字体样式指针
	gettextstyle(&f); // 获取字体样式
	f.lfHeight = 32;
	_tcscpy(f.lfFaceName, _T("楷体")); // 字体
	f.lfQuality = ANTIALIASED_QUALITY; // 抗锯齿
	settextstyle(&f);				   // 设置字体样式
	setbkmode(TRANSPARENT);			   // 字体背景透明
	settextcolor(BLACK);
	setlinestyle(PS_SOLID);
	line(50, 265, 350, 265);
	drawtext("输入账号", &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("输入密码", &R3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("登录", &R4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("注册", &R5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	while (1)
	{
		m1 = getmessage(); // 获取鼠标操作

		if (m1.x > r4[0] && m1.x < r4[2] && m1.y > r4[1] && m1.y < r4[3])
		{
			setlinecolor(RED);
			roundrect(r4[0], r4[1], r4[2], r4[3], r4[4], r4[5]);
			if (m1.message == WM_LBUTTONDOWN)
			{
				InputInfor(); // 注册
			}
		}
		else if (m1.x > r1[0] && m1.x < r1[2] && m1.y > r1[1] && m1.y < r1[3])
		{
			setlinecolor(YELLOW);
			roundrect(r1[0], r1[1], r1[2], r1[3], r1[4], r1[5]);
			if (m1.message == WM_LBUTTONDOWN)
			{
				Inputzhang(); // 输入账号
			}
		}
		else if (m1.x > r2[0] && m1.x < r2[2] && m1.y > r2[1] && m1.y < r2[3])
		{
			setlinecolor(YELLOW);
			roundrect(r2[0], r2[1], r2[2], r2[3], r2[4], r2[5]);
			if (m1.message == WM_LBUTTONDOWN)
			{
				InputMima(); // 输入密码
			}
		}
		else if (m1.x > r3[0] && m1.x < r3[2] && m1.y > r3[1] && m1.y < r3[3])
		{
			setlinecolor(RED);
			roundrect(r3[0], r3[1], r3[2], r3[3], r3[4], r3[5]);
			if (m1.message == WM_LBUTTONDOWN)
			{
				ModiInfor(); // 登录
			}
		}
		else
		{
			setlinecolor(WHITE);
			roundrect(r1[0], r1[1], r1[2], r1[3], r1[4], r1[5]);
			roundrect(r2[0], r2[1], r2[2], r2[3], r2[4], r2[5]);
			roundrect(r3[0], r3[1], r3[2], r3[3], r3[4], r3[5]);
			roundrect(r4[0], r4[1], r4[2], r4[3], r4[4], r4[5]);
		}
	}
}
void InputInfor()
{
	// 通过循环来检查是否有重复的

	// 输入学号
	while (1)
	{
		InputBox(s[nowacc_num].s_Num, 9, "请设置您的账号");

		int FlagInput2 = 0;
		// 计算输入的字符串长度
		int nums = strlen(s[nowacc_num].s_Num);

		if (FlagInput2 == 0)
		{
			// 判断是否输入重复
			int FlagInput1 = 0;
			for (int i = 0; i < nowacc_num; i++)
			{
				if (strcmp(s[nowacc_num].s_Num, s[i].s_Num) == 0)
				{
					FlagInput1 = 1;
				}
			}
			if (FlagInput1 == 1)
			{
				HWND hwndInput1 = GetHWnd();
				int isok = MessageBox(hwndInput1, "该账号已存在，请重新设置", "提示", MB_OK);
			}
			if (FlagInput1 == 0)
			{
				break;
			}
		}
	}
	InputBox(s[nowacc_num].s_Mima, 10, "请设置您的密码");
	SaveInfor(); // 保存数据
}
void SaveInfor()
{
	// 如果学号和姓名都不是空的才写入文件
	if (strlen(s[nowacc_num].s_Num) != 0 && strlen(s[nowacc_num].s_Mima) != 0)
	{
		FILE *fp = fopen("accountInfo.txt", "a"); // 追加
		if (fp == NULL)
		{
			return;
		}
		fprintf(fp, "%s\t%s\n",
				s[nowacc_num].s_Num,
				s[nowacc_num].s_Mima);
		fclose(fp);
		// 保存完毕人数++
		nowacc_num++;
	}
}
int cha() // 查找
{
	char Input[30];
	InputBox(Input, 10, "请输入您的账号");
	for (int k = 0; k < nowacc_num; k++)
	{
		if (strcmp(s[k].s_Num, Input) == 0 || strcmp(s[k].s_Mima, Input) == 0) // 两个字符串相等
		{
			return k;
		}
	}

	return -1;
}
void Printfind() // 调用cha()
{
	int fan1 = cha(); // 返回值
	if (fan1 == -1)	  // 没找到
	{
		// 获取窗口句柄
		HWND hndtipsF = GetHWnd();
		int isok = MessageBox(hndtipsF, "密码错误/账户不存在!", "提示", MB_OK);
	}
}
void ModiInfor() // 登录
{
	if (deng1 == 2)
	{

		menu2();
	}
}
void ReadInfor()
{
	FILE *fp = fopen("accountInfo.txt", "r");
	if (fp == NULL)
	{
		return;
	}
	// 将文件中的数据读取到当前的结构体数组中
	for (int i = 0; i < 15; i++)
	{

		fscanf(fp, "%s\t%s\t\n",
			   s[i].s_Num,
			   s[i].s_Mima);
	}

	int FileaccountNums = 0;
	// 读取出文件中数据的人数个数
	for (int j = 0; j < 15; j++)
	{
		if (strlen(s[j].s_Mima) != 0)
		{
			nowacc_num = ++FileaccountNums;
		}
	}
	fclose(fp);
}
void Inputzhang()
{
	while (1)
	{
		InputBox(s[nowacc_num].s_Num, 10, "请输入您的账号");
		int FlagInput2 = 0;
		// 计算输入的字符串长度
		int nums = strlen(s[nowacc_num].s_Num);

		if (FlagInput2 == 0)
		{
			// 判断是否输入重复
			int FlagInput1 = 0;
			for (int i = 0; i < nowacc_num; i++)
			{
				if (strcmp(s[nowacc_num].s_Num, s[i].s_Num) == 0)
				{
					FlagInput1 = 1;
					deng1 = 1;
				}
			}
			if (FlagInput1 == 0)
			{
				HWND hwndInput1 = GetHWnd();
				int isok = MessageBox(hwndInput1, "账号不存在", "提示", MB_OK);
				break;
			}
			if (FlagInput1 == 1)
			{
				break;
			}
		}
	}
	SaveInfor();
}
void InputMima()
{
	if (deng1 == 1)
	{

		while (1)
		{
			InputBox(s[nowacc_num].s_Num, 10, "请输入您的密码");
			int FlagInput2 = 0;
			// 计算输入的字符串长度
			int nums = strlen(s[nowacc_num].s_Num);

			if (FlagInput2 == 0)
			{
				// 判断是否输入重复
				int FlagInput1 = 0;
				for (int i = 0; i < nowacc_num; i++)
				{
					if (strcmp(s[nowacc_num].s_Num, s[i].s_Num) == 0)
					{
						FlagInput1 = 1;
					}
				}
				if (FlagInput1 == 0)
				{
					HWND hwndInput1 = GetHWnd();
					int isok = MessageBox(hwndInput1, "密码错误", "提示", MB_OK);
					break;
				}
				if (FlagInput1 == 1)
				{
					break;
				}
			}
		}
		deng1 = 2;
		SaveInfor();
	}
}

// 主界面
void menu2()
{
	initgraph(900, 556);
	IMAGE img;
	loadimage(&img, "C:\\Users\\POMPEII\\Desktop\\微信图片_20241218125323.jpg", 900, 556);
	putimage(0, 0, &img);

	setfillcolor(WHITE);
	fillroundrect(336, 170, 564, 210, 40, 40);
	fillroundrect(336, 240, 564, 280, 40, 40);
	fillroundrect(336, 310, 564, 350, 40, 40);

	settextstyle(20, 0, "楷体");
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	char button[] = "控制长度";
	char button1[3][11] = {
		"推荐座位",
		"座位预览",
		"账号状态"};
	int x = (228 - textwidth(button)) / 2; // 长度
	int y = (40 - textheight(button)) / 2; // 高度
	for (int i = 0; i < 3; i++)
	{
		outtextxy(336 + x, blmain[i].top + y, button1[i]);
	}

	ExMessage m;
	while (1)
	{
		m = getmessage();
		if (m.x >= 336 && m.x <= 564 && m.y >= 170 && m.y <= 210)
		{
			setlinecolor(RED);
			roundrect(336, 170, 564, 210, 40, 40);
			if (m.message == WM_LBUTTONDOWN)
			{
				Zuoweituijian();
			}
		}
		else if (m.x >= 336 && m.x <= 564 && m.y >= 240 && m.y <= 280)
		{
			setlinecolor(RED);
			roundrect(336, 240, 564, 280, 40, 40);
			if (m.message == WM_LBUTTONDOWN)
			{
				jiaoshiyulan();
			}
		}
		else if (m.x >= 336 && m.x <= 564 && m.y >= 310 && m.y <= 350)
		{
			setlinecolor(RED);
			roundrect(336, 310, 564, 350, 40, 40);
			if (m.message == WM_LBUTTONDOWN)
			{
				menuzhanghao(); // 帐号状态
			}
		}
		else
		{
			setlinecolor(WHITE);
			roundrect(336, 170, 564, 210, 40, 40);
			roundrect(336, 240, 564, 280, 40, 40);
			roundrect(336, 310, 564, 350, 40, 40);
		}
	}
	_getch();
	closegraph();
}

// 教室预览界面
void Zuoweituijian()
{
	licence sat[4][4];
	vector<licence> b;
	initClassroom(myclassroom);
	int cnt = 0;
	for (int t = 0; t < 9; t++)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				sat[i][j].a1 = myclassroom[cnt].seat;
				sat[i][j].a2 = myclassroom[cnt].badseat;
				sat[i][j].a3 = myclassroom[cnt].door;
				sat[i][j].a4 = myclassroom[cnt].socket;
				sat[i][j].a5 = myclassroom[cnt].clean;
				sat[i][j].d1.first = myclassroom[cnt].rol;
				sat[i][j].d1.second = myclassroom[cnt].row;
				sat[i][j].d2.first = myclassroom[cnt].foolr;
				sat[i][j].d2.second = myclassroom[cnt].class_;
				sat[i][j].score = count(sat[i][j]);
				cnt++;
			}
		}

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				b.push_back(sat[i][j]);
			}
		}
	}
	sort(b.begin(), b.end(), cmp);
	lie *hd;
	lie *fst = new lie;
	hd = fst;
	fst->next = NULL;
	lie *p = fst;
	for (vector<licence>::iterator i = b.begin(); i != b.end(); i++)
	{
		lie *temp = new lie;
		if ((*i).occupy == 1)
		{
			continue;
		}
		temp->key = (*i).score;
		temp->a1 = (*i).a1;
		temp->a2 = (*i).a2;
		temp->a3 = (*i).a3;
		temp->a4 = (*i).a4;
		temp->a5 = (*i).a5;
		temp->situation = (*i).d1;
		temp->situation2 = (*i).d2;
		temp->next = NULL;
		p->next = temp;
		p = temp;
	}

	//    cout<<()
	lie *txto = hd->next;
	char seat[10];
	char badseat[10];
	char door[10];
	char socket[10];
	char clean[10];
	char rol[10];
	char row[10];
	char foolr[10];
	char class_[10];

	initgraph(900, 556);

	cleardevice();

	do
	{
		// 背景图
		IMAGE img;
		//      	loadimage(&img,"C:\\Users\\POMPEII\\Desktop\\00001-2141735407.png",900,556);
		putimage(0, 0, &img);
		// 鼠标操作1
		ExMessage m1;
		settextstyle(48, 0, "楷体");
		// 设置文字颜色
		settextcolor(WHITE);
		//   settextcolor(RGB(64,64,64));
		setbkmode(TRANSPARENT);
		// 绘制文字

		setfillcolor(WHITE);
		setfillstyle(BS_HATCHED, HS_DIAGCROSS);
		setlinecolor(WHITE);

		RECT R31 = {360, 480, 550, 540};
		RECT R32 = {80, 480, 170, 540};
		RECT R33 = {560, 480, 750, 540};
		drawtext("返回", &R32, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext("换一换", &R31, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext("预约", &R33, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		sprintf(seat, "%d", txto->a1);
		sprintf(badseat, "%d", txto->a2);
		sprintf(door, "%d", txto->a3);
		sprintf(socket, "%d", txto->a4);
		sprintf(clean, "%d", txto->a5);
		sprintf(rol, "%d", txto->situation.first);
		sprintf(row, "%d", txto->situation.second);
		sprintf(foolr, "%d", txto->situation2.first);
		sprintf(class_, "%d", txto->situation2.second);
		outtextxy(360, 20, "推荐座位");
		outtextxy(60, 100, "楼层班级");
		outtextxy(60, 180, "座位行列");
		outtextxy(60, 260, "干净状态");
		outtextxy(60, 340, "插座状态");
		outtextxy(60, 420, "门窗状态");
		//	outtextxy(500, 420, a.foolr);
		outtextxy(340, 100, foolr);
		outtextxy(380, 100, "层");
		//	outtextxy(500, 420, a.class_);
		outtextxy(460, 100, class_);
		outtextxy(500, 100, "室");
		//	outtextxy(500, 420, a.row);
		outtextxy(340, 180, row);
		outtextxy(380, 180, "行");
		//	outtextxy(500, 420, a.rol);
		outtextxy(460, 180, rol);
		outtextxy(500, 180, "列");
		//	outtextxy(500, 420, a.clean);
		if (txto->a5 == 1)
		{
			outtextxy(400, 260, "不干净");
		}
		else
		{
			outtextxy(400, 260, "干净");
		}

		//	outtextxy(500, 420, a.sock);
		if (txto->a4 == 1)
		{
			outtextxy(380, 340, "有插座");
		}
		else
		{
			outtextxy(380, 340, "无插座");
		}
		//	outtextxy(500, 420, a.door);
		if (txto->a3 == 1)
		{
			outtextxy(380, 420, "靠门窗");
		}
		else
		{
			outtextxy(380, 420, "无门窗");
		}
		m1 = getmessage(); // 获取鼠标操作
		if (m1.x > 360 && m1.x < 550 && m1.y > 480 && m1.y < 540)
		{
			setlinecolor(YELLOW);
			roundrect(360, 480, 550, 540, 100, 100);
			if (m1.message == WM_LBUTTONDOWN)
			{
				txto = txto->next;
				cleardevice();
			}
		}
		else if (m1.x > 80 && m1.x < 170 && m1.y > 480 && m1.y < 540)
		{
			setlinecolor(YELLOW);
			roundrect(80, 480, 170, 540, 100, 100);
			if (m1.message == WM_LBUTTONDOWN)
			{
				menu2(); // 返回到主页面函数
			}
		}
		else if (m1.x > 560 && m1.x < 750 && m1.y > 480 && m1.y < 540)
		{

			setlinecolor(YELLOW);
			roundrect(560, 480, 750, 540, 100, 100);
			if (m1.message == WM_LBUTTONDOWN)
			{
				// 检查是否已经预约
				bool isReserved = false;
				vector<licence>::iterator reserveIt;
				for (vector<licence>::iterator i = b.begin(); i != b.end(); i++)
				{
					if ((*i).d1 == txto->situation && (*i).d2 == txto->situation2)
					{
						if (reserved)
						{
							isReserved = true;
							reserveIt = i; // 记录迭代器位置
							break;
						}
					}
				}

				if (!isReserved)
				{
					// 更新预约状态
					for (vector<licence>::iterator i = b.begin(); i != b.end(); i++)
					{
						if ((*i).d1 == txto->situation && (*i).d2 == txto->situation2)
						{
							reserved = true;
							reserveIt = i; // 记录迭代器位置
							break;
						}
					}

					// 同步更新链表中的状态
					lie *current = hd->next;
					while (current != NULL)
					{
						if (current->situation == txto->situation && current->situation2 == txto->situation2)
						{
							reserved = true;
							break;
						}
						current = current->next;
					}

					outtextxy(360, 500, "预约成功！");
				}
				else
				{
					outtextxy(360, 500, "该座位已被预约！");
				}
			}
		}
		else
		{
			setlinecolor(TRANSPARENT);
			roundrect(360, 480, 550, 540, 100, 100);
			roundrect(80, 480, 170, 540, 100, 100);
		}
	} while (1);
	closegraph();
}

// 教室预览函数组
int sign_jian(int n) // 一开始赋值为1，用于标记教室，调用一次减一
{
	if (n > 1)
		n--;
	else
		n = 9;
	return n;
}
int sign_jia(int n) // 一开始赋值为1，用于标记教室，调用一次加一
{
	if (n > 8)
		n = 1;
	else
		n++;
	return n;
}
int sign_bubian(int n) // 保存n的值
{
	return n;
}
void click(int n) // 鼠标操作
{
	ExMessage m;
	while (1)
	{
		while (peekmessage(&m, EM_MOUSE))
		{
			if (m.x > 155 && m.x < 235 && m.y > 400 && m.y < 500 && m.message == WM_LBUTTONDOWN) // 点上一个
			{
				n = sign_jian(n);
				creat(myclassroom, n);
				click(n);
			}
			else if (m.x > 75 && m.x < 155 && m.y > 400 && m.y < 500 && m.message == WM_LBUTTONDOWN) // 点下一个
			{
				n = sign_jia(n);
				creat(myclassroom, n);
				click(n);
			}
			else if (m.x > 75 && m.x < 235 && m.y > 275 && m.y < 375 && m.message == WM_LBUTTONDOWN)
			{
				menu2();
			}
			else if (m.x > 375 && m.x < 425 && m.y > 175 && m.y < 225 && m.message == WM_LBUTTONDOWN) // 点座位变色并返回坐标（楼层，教室，行，列）
			{
				setfillcolor(RGB(247, 137.4, 137.4));
				fillcircle(400, 200, 25);
				settextstyle(50, 50, "楷体");
				settextcolor(WHITE);
				outtextxy(350, 450, "预约成功");
				if (n % 3 != 0)
					printf("%d %d %d %d", n / 3 + 1, n % 3, 1, 1);
				else
					printf("%d %d %d %d", n / 3, 3, 1, 1);
			}
			else if (m.x > 375 && m.x < 425 && m.y > 275 && m.y < 325 && m.message == WM_LBUTTONDOWN)
			{
				setfillcolor(RGB(247, 137.4, 137.4));
				fillcircle(400, 300, 25);
				settextstyle(50, 50, "楷体");
				settextcolor(WHITE);
				outtextxy(350, 450, "预约成功");
				if (n % 3 != 0)
					printf("%d %d %d %d", n / 3 + 1, n % 3, 1, 2);
				else
					printf("%d %d %d %d", n / 3, 3, 1, 2);
			}
			else if (m.x > 375 && m.x < 425 && m.y > 375 && m.y < 425 && m.message == WM_LBUTTONDOWN)
			{
				setfillcolor(RGB(247, 137.4, 137.4));
				fillcircle(400, 400, 25);
				settextstyle(50, 50, "楷体");
				settextcolor(WHITE);
				outtextxy(350, 450, "预约成功");
				if (n % 3 != 0)
					printf("%d %d %d %d", n / 3 + 1, n % 3, 1, 3);
				else
					printf("%d %d %d %d", n / 3, 3, 1, 3);
			}
			else if (m.x > 375 && m.x < 425 && m.y > 475 && m.y < 525 && m.message == WM_LBUTTONDOWN)
			{
				setfillcolor(RGB(247, 137.4, 137.4));
				fillcircle(400, 500, 25);
				settextstyle(50, 50, "楷体");
				settextcolor(WHITE);
				outtextxy(350, 450, "预约成功");
				if (n % 3 != 0)
					printf("%d %d %d %d", n / 3 + 1, n % 3, 1, 4);
				else
					printf("%d %d %d %d", n / 3, 3, 1, 4);
			}
			else if (m.x > 475 && m.x < 525 && m.y > 175 && m.y < 225 && m.message == WM_LBUTTONDOWN)
			{
				setfillcolor(RGB(247, 137.4, 137.4));
				fillcircle(500, 200, 25);
				settextstyle(50, 50, "楷体");
				settextcolor(WHITE);
				outtextxy(350, 450, "预约成功");
				if (n % 3 != 0)
					printf("%d %d %d %d", n / 3 + 1, n % 3, 2, 1);
				else
					printf("%d %d %d %d", n / 3, 3, 2, 1);
			}
			else if (m.x > 475 && m.x < 525 && m.y > 275 && m.y < 325 && m.message == WM_LBUTTONDOWN)
			{
				setfillcolor(RGB(247, 137.4, 137.4));
				fillcircle(500, 300, 25);
				settextstyle(50, 50, "楷体");
				settextcolor(WHITE);
				outtextxy(350, 450, "预约成功");
				if (n % 3 != 0)
					printf("%d %d %d %d", n / 3 + 1, n % 3, 2, 2);
				else
					printf("%d %d %d %d", n / 3, 3, 2, 2);
			}
			else if (m.x > 475 && m.x < 525 && m.y > 375 && m.y < 425 && m.message == WM_LBUTTONDOWN)
			{
				setfillcolor(RGB(247, 137.4, 137.4));
				fillcircle(500, 400, 25);
				settextstyle(50, 50, "楷体");
				settextcolor(WHITE);
				outtextxy(350, 450, "预约成功");
				if (n % 3 != 0)
					printf("%d %d %d %d", n / 3 + 1, n % 3, 2, 3);
				else
					printf("%d %d %d %d", n / 3, 3, 2, 3);
			}
			else if (m.x > 475 && m.x < 525 && m.y > 475 && m.y < 525 && m.message == WM_LBUTTONDOWN)
			{
				setfillcolor(RGB(247, 137.4, 137.4));
				fillcircle(500, 500, 25);
				settextstyle(50, 50, "楷体");
				settextcolor(WHITE);
				outtextxy(350, 450, "预约成功");
				if (n % 3 != 0)
					printf("%d %d %d %d", n / 3 + 1, n % 3, 2, 4);
				else
					printf("%d %d %d %d", n / 3, 3, 2, 4);
			}
			else if (m.x > 575 && m.x < 625 && m.y > 175 && m.y < 225 && m.message == WM_LBUTTONDOWN)
			{
				setfillcolor(RGB(247, 137.4, 137.4));
				fillcircle(600, 200, 25);
				settextstyle(50, 50, "楷体");
				settextcolor(WHITE);
				outtextxy(350, 450, "预约成功");
				if (n % 3 != 0)
					printf("%d %d %d %d", n / 3 + 1, n % 3, 3, 1);
				else
					printf("%d %d %d %d", n / 3, 3, 3, 1);
			}
			else if (m.x > 575 && m.x < 625 && m.y > 275 && m.y < 325 && m.message == WM_LBUTTONDOWN)
			{
				setfillcolor(RGB(247, 137.4, 137.4));
				fillcircle(600, 300, 25);
				settextstyle(50, 50, "楷体");
				settextcolor(WHITE);
				outtextxy(350, 450, "预约成功");
				if (n % 3 != 0)
					printf("%d %d %d %d", n / 3 + 1, n % 3, 3, 2);
				else
					printf("%d %d %d %d", n / 3, 3, 3, 2);
			}
			else if (m.x > 575 && m.x < 625 && m.y > 375 && m.y < 425 && m.message == WM_LBUTTONDOWN)
			{
				setfillcolor(RGB(247, 137.4, 137.4));
				fillcircle(600, 400, 25);
				settextstyle(50, 50, "楷体");
				settextcolor(WHITE);
				outtextxy(350, 450, "预约成功");
				if (n % 3 != 0)
					printf("%d %d %d %d", n / 3 + 1, n % 3, 3, 3);
				else
					printf("%d %d %d %d", n / 3, 3, 3, 3);
			}
			else if (m.x > 575 && m.x < 625 && m.y > 475 && m.y < 525 && m.message == WM_LBUTTONDOWN)
			{
				setfillcolor(RGB(247, 137.4, 137.4));
				fillcircle(600, 500, 25);
				settextstyle(50, 50, "楷体");
				settextcolor(WHITE);
				outtextxy(350, 450, "预约成功");
				if (n % 3 != 0)
					printf("%d %d %d %d", n / 3 + 1, n % 3, 3, 4);
				else
					printf("%d %d %d %d", n / 3, 3, 3, 4);
			}
			else if (m.x > 675 && m.x < 725 && m.y > 175 && m.y < 225 && m.message == WM_LBUTTONDOWN)
			{
				setfillcolor(RGB(247, 137.4, 137.4));
				fillcircle(700, 200, 25);
				settextstyle(50, 50, "楷体");
				settextcolor(WHITE);
				outtextxy(350, 450, "预约成功");
				if (n % 3 != 0)
					printf("%d %d %d %d", n / 3 + 1, n % 3, 4, 1);
				else
					printf("%d %d %d %d", n / 3, 3, 4, 1);
			}
			else if (m.x > 675 && m.x < 725 && m.y > 275 && m.y < 325 && m.message == WM_LBUTTONDOWN)
			{
				setfillcolor(RGB(247, 137.4, 137.4));
				fillcircle(700, 300, 25);
				settextstyle(50, 50, "楷体");
				settextcolor(WHITE);
				outtextxy(350, 450, "预约成功");
				if (n % 3 != 0)
					printf("%d %d %d %d", n / 3 + 1, n % 3, 4, 2);
				else
					printf("%d %d %d %d", n / 3, 3, 4, 2);
			}
			else if (m.x > 675 && m.x < 725 && m.y > 375 && m.y < 425 && m.message == WM_LBUTTONDOWN)
			{
				setfillcolor(RGB(247, 137.4, 137.4));
				fillcircle(700, 400, 25);
				settextstyle(50, 50, "楷体");
				settextcolor(WHITE);
				outtextxy(350, 450, "预约成功");
				if (n % 3 != 0)
					printf("%d %d %d %d", n / 3 + 1, n % 3, 4, 3);
				else
					printf("%d %d %d %d", n / 3, 3, 4, 3);
			}
			else if (m.x > 675 && m.x < 725 && m.y > 475 && m.y < 525 && m.message == WM_LBUTTONDOWN)
			{
				setfillcolor(RGB(247, 137.4, 137.4));
				fillcircle(700, 500, 25);
				settextstyle(50, 50, "楷体");
				settextcolor(WHITE);
				outtextxy(350, 450, "预约成功");
				if (n % 3 != 0)
					printf("%d %d %d %d", n / 3 + 1, n % 3, 4, 4);
				else
					printf("%d %d %d %d", n / 3, 3, 4, 4);
			}
		}
	}
}
void creat(Floor_Classroom c[144], int n)
{
	initgraph(900, 556);
	setbkcolor(WHITE);
	setbkmode(TRANSPARENT);
	cleardevice();
	IMAGE img;
	loadimage(&img, "C:\\Users\\POMPEII\\Desktop\\00001-2141735407.png", 900, 556);
	putimage(0, 0, &img);
	{ // 讲台标题
		setlinecolor(BLACK);
		fillrectangle(460, 50, 635, 130);
		settextcolor(BLACK);
		settextstyle(25, 25, "楷体");
		outtextxy(425, 10, "座  位  预  览");
		settextstyle(25, 25, "楷体");
		outtextxy(510, 90, "讲台");
	}
	{ // 门窗
		settextstyle(15, 15, "楷体");
		outtextxy(825, 90, "门");
		setfillcolor(WHITE);
		fillrectangle(775, 50, 800, 130);
		outtextxy(825, 450, "门");
		setfillcolor(WHITE);
		fillrectangle(775, 395, 800, 495);
		outtextxy(265, 90, "窗户");
		setfillcolor(WHITE);
		fillrectangle(325, 50, 355, 130);
		outtextxy(265, 275, "窗户");
		setfillcolor(WHITE);
		fillrectangle(325, 225, 355, 325);
		outtextxy(265, 445, "窗户");
		setfillcolor(WHITE);
		fillrectangle(325, 395, 355, 495);
	}
	int w[144] = {400, 400, 400, 400, 500, 500, 500, 500, 600, 600, 600, 600, 700, 700, 700, 700, 400, 400, 400, 400, 500, 500, 500, 500, 600, 600, 600, 600, 700, 700, 700, 700, 400, 400, 400, 400, 500, 500, 500, 500, 600, 600, 600, 600, 700, 700, 700, 700, 400, 400, 400, 400, 500, 500, 500, 500, 600, 600, 600, 600, 700, 700, 700, 700, 400, 400, 400, 400, 500, 500, 500, 500, 600, 600, 600, 600, 700, 700, 700, 700, 400, 400, 400, 400, 500, 500, 500, 500, 600, 600, 600, 600, 700, 700, 700, 700, 400, 400, 400, 400, 500, 500, 500, 500, 600, 600, 600, 600, 700, 700, 700, 700, 400, 400, 400, 400, 500, 500, 500, 500, 600, 600, 600, 600, 700, 700, 700, 700, 400, 400, 400, 400, 500, 500, 500, 500, 600, 600, 600, 600, 700, 700, 700, 700}; // 宽度
	int h[144] = {200, 300, 400, 500, 200, 300, 400, 500, 200, 300, 400, 500, 200, 300, 400, 500, 200, 300, 400, 500, 200, 300, 400, 500, 200, 300, 400, 500, 200, 300, 400, 500, 200, 300, 400, 500, 200, 300, 400, 500, 200, 300, 400, 500, 200, 300, 400, 500, 200, 300, 400, 500, 200, 300, 400, 500, 200, 300, 400, 500, 200, 300, 400, 500, 200, 300, 400, 500, 200, 300, 400, 500, 200, 300, 400, 500, 200, 300, 400, 500, 200, 300, 400, 500, 200, 300, 400, 500, 200, 300, 400, 500, 200, 300, 400, 500, 200, 300, 400, 500, 200, 300, 400, 500, 200, 300, 400, 500, 200, 300, 400, 500, 200, 300, 400, 500, 200, 300, 400, 500, 200, 300, 400, 500, 200, 300, 400, 500, 200, 300, 400, 500, 200, 300, 400, 500, 200, 300, 400, 500, 200, 300, 400, 500}; // 高度
	int r = 25;
	int i = 0;
	i = (n - 1) * 16;
	int count = 0;
	while (count < 16)
	{
		if (c[i].seat == 0 && c[i].badseat == 0)
		{
			setfillcolor(RGB(133.4, 206.2, 97.4));
			fillcircle(w[i], h[i], r);
		}
		else
		{
			setfillcolor(RGB(247, 137.4, 137.4));
			fillcircle(w[i], h[i], r);
		}
		i++;
		count++;
	}
	{ // 空闲
		setfillcolor(RGB(133.4, 206.2, 97.4));
		settextstyle(15, 15, "楷体");
		outtextxy(150, 25, "空闲");
		fillcircle(100, 25, 25);
		;
	}
	{
		setfillcolor(RGB(247, 137.4, 137.4));
		outtextxy(150, 100, "占用");
		fillcircle(100, 100, 25); // 占用
	}
	{
		roundrect(75, 300, 150, 400, 10, 10);
		outtextxy(120, 350, "搜索");
	}
	{
		settextstyle(10, 10, "楷体");
		roundrect(75, 275, 235, 375, 10, 10);
		outtextxy(130, 325, "返回");
		roundrect(75, 400, 155, 500, 10, 10);
		outtextxy(90, 450, "上一个");
		roundrect(155, 400, 235, 500, 10, 10);
		outtextxy(165, 450, "下一个");
	}
	{
		setfillcolor(BLACK);
		fillrectangle(240, 0, 241, 556);
	}

	click(n);
	getchar();
}
void jiaoshiyulan() // 总的
{
	int n = 1;
	creat(myclassroom, n);
	click(n);
}

// 签到签退函数组
void menuzhanghao()
{
	initgraph(900, 550); // 界面大小
	// 鼠标操作1
	ExMessage m1;
	cleardevice();
	// 背景图
	IMAGE img;
	loadimage(&img, "C:\\Users\\POMPEII\\Desktop\\00001-2141735407.png", 900, 550);
	putimage(0, 0, &img);

	setbkmode(TRANSPARENT);
	setfillcolor(WHITE);
	fillroundrect(r11[0], r11[1], r11[2], r11[3], r11[4], r11[5]); // 画矩形，即按钮
	fillroundrect(r21[0], r21[1], r21[2], r21[3], r21[4], r21[5]);
	fillroundrect(r31[0], r31[1], r31[2], r31[3], r31[4], r31[5]);

	RECT R11 = {R1[0], R1[1], R1[2], R1[3]};
	RECT R21 = {r11[0], r11[1], r11[2], r11[3]};
	RECT R31 = {r21[0], r21[1], r21[2], r21[3]};
	RECT R41 = {r31[0], r31[1], r31[2], r31[3]};

	LOGFONT f;		  // 字体样式指针
	gettextstyle(&f); // 获取字体样式
	f.lfHeight = 60;
	_tcscpy(f.lfFaceName, _T("楷体")); // 宋体
	f.lfQuality = ANTIALIASED_QUALITY; // 抗锯齿
	settextstyle(&f);				   // 设置字体样式
	setbkmode(TRANSPARENT);			   // 字体背景透明
	settextcolor(BLACK);

	drawtext("祝您学习愉快", &R11, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("签到", &R21, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("签退", &R31, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("返回", &R41, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	while (1)
	{
		m1 = getmessage(); // 获取鼠标操作
		int Fill1;
		if (m1.x > r11[0] && m1.x < r11[2] && m1.y > r11[1] && m1.y < r11[3])
		{
			setlinecolor(YELLOW);
			roundrect(r11[0], r11[1], r11[2], r11[3], r11[4], r11[5]);
			if (m1.message == WM_LBUTTONDOWN)
			{
				Qiandao(); // 签到
			}
		}
		else if (m1.x >= r21[0] && m1.x <= r21[2] && m1.y >= r21[1] && m1.y <= r21[3])
		{
			setlinecolor(YELLOW);
			roundrect(r21[0], r21[1], r21[2], r21[3], r21[4], r21[5]);
			if (m1.message == WM_LBUTTONDOWN)
			{
				Qiantui(); // 签退
			}
		}
		else if (m1.x > r31[0] && m1.x < r31[2] && m1.y > r31[1] && m1.y < r31[3])
		{
			setlinecolor(YELLOW);
			roundrect(r31[0], r31[1], r31[2], r31[3], r31[4], r31[5]);
			if (m1.message == WM_LBUTTONDOWN)
			{
				menu2(); // 返回
			}
		}
		else
		{
			setlinecolor(WHITE);
			roundrect(r11[0], r11[1], r11[2], r11[3], r11[4], r11[5]);
			roundrect(r21[0], r21[1], r21[2], r21[3], r21[4], r21[5]);
			roundrect(r31[0], r31[1], r31[2], r31[3], r31[4], r31[5]);
		}
	}
}
void Qiandao()
{
	if (!reserved)
	{
		HWND hndtipsF = GetHWnd();
		int isok = MessageBox(hndtipsF, "您尚未预约教室，无法签到!", "提示", MB_OK);
		return; // 如果没有预约教室，直接返回，不执行签到操作
	}

	HWND hndtipsF = GetHWnd();
	int isok = MessageBox(hndtipsF, "签到成功!", "提示", MB_OK);
	Fill1 = 1;
	printf("%d", Fill1);
}
void Qiantui()
{
	if (!reserved)
	{
		HWND hndtipsF = GetHWnd();
		int isok = MessageBox(hndtipsF, "您尚未预约教室，无法签退!", "提示", MB_OK);
		return; // 如果没有预约教室，直接返回，不执行签退操作
	}

	if (Fill1 == 1)
	{
		HWND hndtipsF = GetHWnd();
		int isok = MessageBox(hndtipsF, "签退成功!", "提示", MB_OK);
	}
	else
	{
		HWND hndtipsF = GetHWnd();
		int isok = MessageBox(hndtipsF, "未进行签到!", "提示", MB_OK);
	}
}
void Menuzhang()
{
	menuzhanghao();
}

// 主函数
int main()
{
	menu();
	getchar();
	closegraph();
	return 0;
}
