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

struct bullet//적 탄 구조체
{
	float x;
	float y;//탄 좌표
	int atk;
	int radius;//탄 지름
	float speed;//탄 속도
	float angle;//탄 각도
	bool release;//존재유무
	bool isgraze;//그레이즈
};
struct fallingitem//아이템 구조체
{
	float x;//아이템 좌표
	float y;
	int itemtype;
	int point;//아이템 점수
	int effect;//아이템 효과
	float speed;//아이템 속도
	bool release;//존재유무
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
	int enemycount;//동작설정용 시간변수
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

	fallingitem point;//점수템
	fallingitem power;//파워템
	fallingitem hpup;//1up
	fallingitem bombup;//폭탄업

	fallingitem* ppoint = &point;
	fallingitem* ppower = &power;
	fallingitem* phpup = &hpup;
	fallingitem* pbombup = &bombup;

	bullet ultrasmall_b;//아주작은탄
	bullet small_b;//작은탄
	bullet normal_b;//보통탄
	bullet big_b;//큰탄

	bullet zbullet;//z탄
	bullet xbullet;//x탄
	bullet cbullet;//폭탄
	enemy mob1;//몹1
	enemy mob2;//몹2
	enemy mob3;//몹3
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


	int titlescreen;//타이틀,옵션,시작화면 등등
	int stage[2];//스테이지 수
	int shotdelay;//발사딜레이

	//타이틀
	RECT bt_gamestart, bt_option, bt_result, bt_exit, bt_difficultyselect[3];
	int difficulty;
	int selectplayer;
	int selectkey;
	bool isselectdiff;


	//인게임
	int amount_pointitem;//템점수 먹은 수
	int amount_graze;//그레이즈 횟수
	RECT playerrect;//플레이어 사각형
	POINT playerxy;
	POINT playersoulxy;
	bool isshift;//저속모드
	bool isbomb;//폭탄모드
	bool isplayermove;
	int bombcounter;//폭탄 발동시간
	bool ishitted;
	int resurrect_bombcounter;//잔기를 잃는데에 걸리는 시간
	bool isrespawn;
	int respawn;

	bool playerhpzero;//게임오버시
	int playerhpzeroscreencount;//게임오버화면띄우는시간

	int playerhp, playerbomb;//체력,폭탄
	int hiscore;//최고점수
	int score;//점수
	int playerpower;
	float playerspeed;//이동속도(저속이동은 0.5배)

	int playermotion;//옷 펄럭임
	int player_movecount;//모션변화
	int count;//몹 등장에 사용

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

	//결과
	int resultscore[10];
	time_t t;

	//옵션
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

