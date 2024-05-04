#include <graphics.h>
//这个头文件通常用于在 C/C++ 中进行简单的图形编程
//它提供了一些基本的图形绘制函数，如画线、画圆、填充颜色等，以及控制图形窗口的函数，如创建窗口、关闭窗口等
#include <conio.h>
//这个头文件提供了一些用于在控制台中进行输入输出的函数，主要是针对字符的输入输出操作。
//其中包括了一些用于控制光标位置、设置文本颜色、从控制台中读取字符等函数。
#include<math.h>
//这是 C/C++ 标准库中的数学函数头文件，提供了各种数学函数的声明和定义。
//它包含了一系列常用的数学函数，如三角函数、对数函数、指数函数、幂函数等。
//math.h 中的函数可以用于各种数学计算和科学计算，如数值分析、物理学、工程学等领域的计算。

#define G 9.8                      //重力加速度
#define XSIZE 512                  //屏幕大小
#define YSIZE 384
#define X 64                       //主角起始位置
#define Y 192
#define W 32                       //主角的宽和高
#define H 32
#define STEP 4                     //主角走一步相距的像素个数
#define HIGH (2*role.w+1)          //主角跳跃的最大高度

#define	CMD_LEFT 1                 //方向键的宏定义
#define	CMD_RIGHT 2	
#define	CMD_UP 4
#define CMD_DOWN 8
#define CMD_SHOOT 16
#define CMD_ESC 32
int life;                          //全局变量，主角共有多少条生命
int score;                         //全局变量，主角获得的分数
struct ROLE
{
	int id;
	int x;//横坐标
	int y;//纵坐标
	int w;//图片宽度
	int h;//图片高度
	int xleft;//水平运动的左界限 
	int xright;//水平运动的右界限
	int turn;//精灵的运动方向
	int jump;//精灵是否跳跃
	int iframe;//加载第几副精灵图，这样就能让精灵看上去动起来了
};
struct MAP        //储存地图的结构体
{
	int id;
	int x;
	int y;
};
struct BULLET      //子弹的结构体
{
	int x;
	int y;
	int turn;
	int iframe;
	int id;
};
struct COINT      //硬币的结构体
{
	int x;
	int y;
	double iframe;
};
struct ENEMY      //敌人的结构体
{
	int id;
	int x;
	int y;
	int turn;
	int iframe;
};
class game        //整个游戏只设置了这一个类
{
private:
	ROLE role;
	MAP map[350];
	BULLET bullet[20];
	COINT coint[50];
	ENEMY enemy[20];
	IMAGE img_mapsky, img_p, img_map, img_ani, img_mapbk, img_home;
	int xmapsky;           //背景天空的起始横坐标
	int xmap;              //地图的起始坐标
	double v0;             //精灵跳跃的初速度             
	double h;              //精灵跳跃的高度
	double t;              //精灵跳跃的时间
	int ibullet;           //第几颗子弹
	int xbullet;           //子弹的x坐标
	int ybullet;           //子弹的y坐标
	int get_bullet;        //是否获得武器，0表示没有获得，1表示已获得
	POINT icoint;          //储存硬币的坐标
	POINT bomb[20];        //储存哪些地方爆炸了的坐标
	POINT temp;            //临时坐标。储存哪些地方爆炸了的坐标
	double score_frame;    //下面3个double型的变量用于控制各自图片的帧，以实现动画的效果。如画面中的流水
	double bomb_frame;
	double mapbk_frame;
	int win;               //玩家是否过关
	int pause;             //玩家是否按Esc（暂停键）
public:
	game();
	~game();
	void start();          //处理游戏开始的界面，和按暂停键后的界面
	void init();           //初始化各项变量
	void move();           //控制主角移动
	void show();           //显示画面
	int isdie();           //判断主角是否已死
	int  GetCommand();	   // 获取控制命令。
	void left();           //主角向左运动
	void right();          //主角向右运动
	void up();             //主角跳跃
	void init_shoot();     //初始化发射子弹
	void fall();	       //主角自由落体或者向上跳跃
	int is_l_touch(int id);//主角的左边是否碰到墙或敌人，以及敌人是否碰到陆地的左边界
	int is_r_touch(int id);//主角的右边是否碰到墙或敌人，以及敌人是否碰到陆地的右边界
	int is_t_touch();      //主角的头是否碰到墙
	int is_b_touch(int id);//主角是否踩到敌人。
	int is_touch();        //主角是否吃到金币
	int is_land(ENEMY e);  //敌人是否站在陆地上
	void getbullet();      //获取子弹
	void shoot();          //发射子弹
	int eat(BULLET b);     //子弹是否打到敌人或者墙壁
	void end();            //处理游戏结束
};


//跟据超级玛丽的游戏总结了一些这个游戏必须有的一些元素，但暂时没考虑声音和图像,
// 只对所可能需要的头文件，物理相关的的一些宏定义，游戏相关元素，
// 以及游戏中一些操作判断进行了一些初始的定义