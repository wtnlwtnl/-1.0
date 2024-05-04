#include <graphics.h>
//���ͷ�ļ�ͨ�������� C/C++ �н��м򵥵�ͼ�α��
//���ṩ��һЩ������ͼ�λ��ƺ������续�ߡ���Բ�������ɫ�ȣ��Լ�����ͼ�δ��ڵĺ������紴�����ڡ��رմ��ڵ�
#include <conio.h>
//���ͷ�ļ��ṩ��һЩ�����ڿ���̨�н�����������ĺ�������Ҫ������ַ����������������
//���а�����һЩ���ڿ��ƹ��λ�á������ı���ɫ���ӿ���̨�ж�ȡ�ַ��Ⱥ�����
#include<math.h>
//���� C/C++ ��׼���е���ѧ����ͷ�ļ����ṩ�˸�����ѧ�����������Ͷ��塣
//��������һϵ�г��õ���ѧ�����������Ǻ���������������ָ���������ݺ����ȡ�
//math.h �еĺ����������ڸ�����ѧ����Ϳ�ѧ���㣬����ֵ����������ѧ������ѧ������ļ��㡣

#define G 9.8                      //�������ٶ�
#define XSIZE 512                  //��Ļ��С
#define YSIZE 384
#define X 64                       //������ʼλ��
#define Y 192
#define W 32                       //���ǵĿ�͸�
#define H 32
#define STEP 4                     //������һ���������ظ���
#define HIGH (2*role.w+1)          //������Ծ�����߶�

#define	CMD_LEFT 1                 //������ĺ궨��
#define	CMD_RIGHT 2	
#define	CMD_UP 4
#define CMD_DOWN 8
#define CMD_SHOOT 16
#define CMD_ESC 32
int life;                          //ȫ�ֱ��������ǹ��ж���������
int score;                         //ȫ�ֱ��������ǻ�õķ���
struct ROLE
{
	int id;
	int x;//������
	int y;//������
	int w;//ͼƬ���
	int h;//ͼƬ�߶�
	int xleft;//ˮƽ�˶�������� 
	int xright;//ˮƽ�˶����ҽ���
	int turn;//������˶�����
	int jump;//�����Ƿ���Ծ
	int iframe;//���صڼ�������ͼ�����������þ��鿴��ȥ��������
};
struct MAP        //�����ͼ�Ľṹ��
{
	int id;
	int x;
	int y;
};
struct BULLET      //�ӵ��Ľṹ��
{
	int x;
	int y;
	int turn;
	int iframe;
	int id;
};
struct COINT      //Ӳ�ҵĽṹ��
{
	int x;
	int y;
	double iframe;
};
struct ENEMY      //���˵Ľṹ��
{
	int id;
	int x;
	int y;
	int turn;
	int iframe;
};
class game        //������Ϸֻ��������һ����
{
private:
	ROLE role;
	MAP map[350];
	BULLET bullet[20];
	COINT coint[50];
	ENEMY enemy[20];
	IMAGE img_mapsky, img_p, img_map, img_ani, img_mapbk, img_home;
	int xmapsky;           //������յ���ʼ������
	int xmap;              //��ͼ����ʼ����
	double v0;             //������Ծ�ĳ��ٶ�             
	double h;              //������Ծ�ĸ߶�
	double t;              //������Ծ��ʱ��
	int ibullet;           //�ڼ����ӵ�
	int xbullet;           //�ӵ���x����
	int ybullet;           //�ӵ���y����
	int get_bullet;        //�Ƿ���������0��ʾû�л�ã�1��ʾ�ѻ��
	POINT icoint;          //����Ӳ�ҵ�����
	POINT bomb[20];        //������Щ�ط���ը�˵�����
	POINT temp;            //��ʱ���ꡣ������Щ�ط���ը�˵�����
	double score_frame;    //����3��double�͵ı������ڿ��Ƹ���ͼƬ��֡����ʵ�ֶ�����Ч�����续���е���ˮ
	double bomb_frame;
	double mapbk_frame;
	int win;               //����Ƿ����
	int pause;             //����Ƿ�Esc����ͣ����
public:
	game();
	~game();
	void start();          //������Ϸ��ʼ�Ľ��棬�Ͱ���ͣ����Ľ���
	void init();           //��ʼ���������
	void move();           //���������ƶ�
	void show();           //��ʾ����
	int isdie();           //�ж������Ƿ�����
	int  GetCommand();	   // ��ȡ�������
	void left();           //���������˶�
	void right();          //���������˶�
	void up();             //������Ծ
	void init_shoot();     //��ʼ�������ӵ�
	void fall();	       //���������������������Ծ
	int is_l_touch(int id);//���ǵ�����Ƿ�����ǽ����ˣ��Լ������Ƿ�����½�ص���߽�
	int is_r_touch(int id);//���ǵ��ұ��Ƿ�����ǽ����ˣ��Լ������Ƿ�����½�ص��ұ߽�
	int is_t_touch();      //���ǵ�ͷ�Ƿ�����ǽ
	int is_b_touch(int id);//�����Ƿ�ȵ����ˡ�
	int is_touch();        //�����Ƿ�Ե����
	int is_land(ENEMY e);  //�����Ƿ�վ��½����
	void getbullet();      //��ȡ�ӵ�
	void shoot();          //�����ӵ�
	int eat(BULLET b);     //�ӵ��Ƿ�򵽵��˻���ǽ��
	void end();            //������Ϸ����
};


//���ݳ�����������Ϸ�ܽ���һЩ�����Ϸ�����е�һЩԪ�أ�����ʱû����������ͼ��,
// ֻ����������Ҫ��ͷ�ļ���������صĵ�һЩ�궨�壬��Ϸ���Ԫ�أ�
// �Լ���Ϸ��һЩ�����жϽ�����һЩ��ʼ�Ķ���