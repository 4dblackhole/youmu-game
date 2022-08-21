#pragma once
#include "gameNode.h"

enum ITEMTYPE
{
	ITEMPOINT,
	ITEMPOWER,
	ITEMHP,
	ITEMBOMB
};
enum TITLESCREEN
{
	TITLE,
	START,
	OPTION,
	RESULT
};
enum DIFF
{
	EASY,
	NORMAL,
	HARD
};
enum COLOR
{
	BLUE,
	RED,
	GREEN,
	YELLOW
};

struct bullet//�� ź ����ü
{
	float x;
	float y;//ź ��ǥ
	int atk;
	int radius;//ź ����
	float speed;//ź �ӵ�
	float angle;//ź ����
	bool release;//��������
	bool isgraze;//�׷�����
};
struct fallingitem//������ ����ü
{
	float x;//������ ��ǥ
	float y;
	int itemtype;
	int point;//������ ����
	int effect;//������ ȿ��
	float speed;//������ �ӵ�
	bool release;//��������
};


class enemy
{
public:
	enemy() {};
	virtual ~enemy() {};

	float x;
	float y;
	int hp;
	float speed, angle;
	int enemycount;//���ۼ����� �ð�����
	bool release;
	int color;
	fallingitem item;
};
class boss :public enemy
{
public:
	boss() {};
	virtual ~boss() {};

	int spell;
};


class mainGame : public gameNode
{
private:
	
	bool rectmode;
	float grav;

	fallingitem point;//������
	fallingitem power;//�Ŀ���
	fallingitem hpup;//1up
	fallingitem bombup;//��ź��

	fallingitem* ppoint = &point;
	fallingitem* ppower = &power;
	fallingitem* phpup = &hpup;
	fallingitem* pbombup = &bombup;

	bullet ultrasmall_b;//��������ź
	bullet small_b;//����ź
	bullet normal_b;//����ź
	bullet big_b;//ūź

	bullet zbullet;//zź
	bullet xbullet;//xź
	bullet cbullet;//��ź
	enemy mob1;//��1
	enemy mob2;//��2
	enemy mob3;//��3
	boss st1b;
	boss st2b;

	vector<fallingitem> vpoint;
	vector<fallingitem> vpower;
	vector<fallingitem>::iterator vipoint;
	vector<fallingitem>::iterator vipower;

	vector<bullet> vultrasmall_b;
	vector<bullet> vsmall_b;
	vector<bullet> vnormal_b;
	vector<bullet> vbig_b;
	vector<bullet>::iterator viultrasmall_b;
	vector<bullet>::iterator vismall_b;
	vector<bullet>::iterator vinormal_b;
	vector<bullet>::iterator vibig_b;

	vector< vector<bullet>* > vbulletcontainer_b;


	vector<bullet> vzbullet;
	vector<bullet> vxbullet;
	vector<bullet> vcbullet;
	vector<bullet>::iterator vizbullet;
	vector<bullet>::iterator vixbullet;
	vector<bullet>::iterator vicbullet;
	
	vector< vector<bullet>* > vbulletcontainer;


	vector<enemy> vmob1;
	vector<enemy> vmob2;
	vector<enemy> vmob3;
	vector<enemy>::iterator vimob1;
	vector<enemy>::iterator vimob2;
	vector<enemy>::iterator vimob3;

	vector< vector<enemy>* > vmobcontainer;


	int titlescreen;//Ÿ��Ʋ,�ɼ�,����ȭ�� ���
	int stage[2];//�������� ��
	int shotdelay;//�߻������

	//Ÿ��Ʋ
	RECT bt_gamestart, bt_option, bt_result, bt_exit, bt_difficultyselect[3];
	int difficulty;
	int selectplayer;
	int selectkey;
	bool isselectdiff;


	//�ΰ���
	int amount_pointitem;//������ ���� ��
	int amount_graze;//�׷����� Ƚ��
	RECT playerrect;//�÷��̾� �簢��
	POINT playerxy;
	POINT playersoulxy;
	bool isshift;//���Ӹ��
	bool isbomb;//��ź���
	bool isplayermove;
	int bombcounter;//��ź �ߵ��ð�
	bool ishitted;
	int resurrect_bombcounter;//�ܱ⸦ �Ҵµ��� �ɸ��� �ð�
	bool isrespawn;
	int respawn;

	bool playerhpzero;//���ӿ�����
	int playerhpzeroscreencount;//���ӿ���ȭ����½ð�

	int playerhp, playerbomb;//ü��,��ź
	int hiscore;//�ְ�����
	int score;//����
	int playerpower;
	float playerspeed;//�̵��ӵ�(�����̵��� 0.5��)

	int playermotion;//�� �޷���
	int player_movecount;//��Ǻ�ȭ
	int count;//�� ���忡 ���

	bool stagepassflag;

	RECT wall[4];

	image *stagefailedup;
	image *stagefailedlight;
	image *stagefaileddown;
	image *stagefailedblackline;
	image *stagepass;
	image *_background;
	image *hpbar;

	image *png_start;
	image *png_result;
	image *png_option;
	image *png_exit;
	image *png_selectdifficulty;
	image *png_bg;

	image *png_player;
	image *png_playersoul;
	image *png_zshot;
	image *png_enemytama;
	image *png_wall;
	image *png_enemy;
	image *png_item;
	image *png_scoretable;
	image *png_number;
	image *png_cbullet;
	image *png_bombeffect;
	image *png_scoretablebg;
	image *png_boss1;

	//���
	int resultscore[10];
	time_t t;

	//�ɼ�
	int starthp;
	int startbomb;

public:
	mainGame();
	~mainGame();

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render();

	void zbulletfire();
	void xbulletfire();
	void cbulletfire();
	void bulletmove();

	void Releasemob();
	void hitmob();
	void dropitem();
	void collisionplayer();
	void cbulletCanDeleteEbullet();
	void mobmove();


	void stage1_1();
	void stage1_2();
	void stage1_3();

	void stage2_1();
	void stage2_2();
	void stage2_3();
};

