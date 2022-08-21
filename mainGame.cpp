#include "stdafx.h"
#include "mainGame.h"

mainGame::mainGame(){}

mainGame::~mainGame(){}
//생성자 소멸자는 이제 안씀

//초기화
HRESULT mainGame::init(void)
{
	gameNode::init(true);  //게임노드의 init 함수에 타이머 셋팅 및 키매니져 초기화 관련 함수를 실행한다.
	
	stagefailedup			= IMAGEMANAGER->addImage("upbmp", "usingimg\\stagefailed.bmp", 960, 960, true, RGB(255, 0, 255));
	stagefailedlight		= IMAGEMANAGER->addImage("upbmp", "usingimg\\stagefailed.bmp", 960, 960, true, RGB(0,0,0));
	stagepass				= IMAGEMANAGER->addImage("passbmp", "usingimg\\stagepass.bmp", 94, 20, true, RGB(255,255,255));
	stagefaileddown			= IMAGEMANAGER->addImage("downbmp", "usingimg\\stagefailed.bmp", 960, 960, true, RGB(255, 0, 255));
	stagefailedblackline	= IMAGEMANAGER->addImage("blackbmp", "usingimg\\black640200.bmp", 640, 200, true, RGB(255, 0, 255));
	hpbar					= IMAGEMANAGER->addImage("green_hpbar", "usingimg\\hpbar.bmp", 600, 10, true, RGB(255, 0, 255));

	//타이틀
	png_start				= IMAGEMANAGER->addImage("bmp_start", "usingimg\\title001.bmp", 1024, 1024, true, RGB(255, 0, 255));
	png_result				= IMAGEMANAGER->addImage("bmp_result", "usingimg\\title001.bmp", 1024, 1024, true, RGB(255, 0, 255));
	png_option				= IMAGEMANAGER->addImage("bmp_option", "usingimg\\title001.bmp", 1024, 1024, true, RGB(255, 0, 255));
	png_exit				= IMAGEMANAGER->addImage("bmp_exit", "usingimg\\title001.bmp", 1024, 1024, true, RGB(255, 0, 255));
	png_selectdifficulty	= IMAGEMANAGER->addImage("bmp_selectdifficulty", "usingimg\\pause4x.bmp", 1024, 1024, true, RGB(255, 0, 255));
	png_bg					= IMAGEMANAGER->addImage("bmp_bg", "usingimg\\loading03h.bmp", 1000, 1000, true, RGB(255, 0, 255));

	//인게임
	png_player				= IMAGEMANAGER->addImage("bmp_player", "usingimg\\player.bmp", 256, 96, true, RGB(255, 0, 255));//32x48 x16개
	png_playersoul			= IMAGEMANAGER->addImage("bmp_playersoul", "usingimg\\player03.bmp", 256, 256, true, RGB(255, 0, 255));//196,0 32x32 8개
	png_zshot				= IMAGEMANAGER->addImage("bmp_zshot", "usingimg\\playershot.bmp", 240, 240, true, RGB(255, 0, 255));//48x48 25개
	png_enemytama			= IMAGEMANAGER->addImage("bmp_enemytama", "usingimg\\etama.bmp", 256, 256, true, RGB(255, 0, 255));//적탄 혹은 X탄에도 사용
	png_wall				= IMAGEMANAGER->addImage("bmp_wall", "usingimg\\Wall50x50.bmp", 50, 50, true, RGB(255, 0, 255));//벽 이미지
	png_enemy				= IMAGEMANAGER->addImage("bmp_enemy", "usingimg\\enemy.bmp", 512, 512, true, RGB(255, 0, 255));
	png_item				= IMAGEMANAGER->addImage("bmp_item", "usingimg\\etama2.bmp", 256, 256, true, RGB(255, 0, 255));//아이템
	png_scoretable			= IMAGEMANAGER->addImage("bmp_scoretable", "usingimg\\front1.bmp", 512, 512, true, RGB(255, 0, 255));//y112 player
	png_number				= IMAGEMANAGER->addImage("bmp_number", "usingimg\\title01.bmp", 512, 512, true, RGB(255, 0, 255));//숫자 (0,256)
	png_cbullet				= IMAGEMANAGER->addImage("bmp_cbullet", "usingimg\\cbullet.bmp", 400, 400, true, RGB(255, 0, 255));
	png_scoretablebg		= IMAGEMANAGER->addImage("bmp_scoretablebg", "usingimg\\scoretablebg.bmp", 300, 850, true, RGB(255, 0, 255));
	png_boss1				= IMAGEMANAGER->addImage("bmp_boss1", "usingimg\\st1boss.bmp", 300, 300, true, RGB(255, 0, 255));
	png_bombeffect			= IMAGEMANAGER->addImage("bmp_bombeffect", "usingimg\\etama4.bmp", 256, 256, true, RGB(255, 0, 255));
	

	//1000x850
	//오른쪽 300은 점수판
	//왼쪽 700x850중 각 50칸씩 테두리,600x750 플레이판
	rectmode = false;
	grav = 0.1;

	shotdelay = 0;
	bombcounter = 0;
	resurrect_bombcounter = 0;
	count = 0;
	playermotion = 0;//옷 펄럭임
	player_movecount = 0;
	respawn = 0;
	isrespawn = false;
	ishitted = false;
	playerhpzero = false;
	playerhpzeroscreencount = 0;
	stagepassflag = false;

	titlescreen = TITLESCREEN(TITLE);
	stage[0] = 1;
	stage[1] = 1;

	//타이틀화면
	bt_gamestart = RectMake(50, 100, 160, 64);
	bt_result = RectMake(50, bt_gamestart.bottom + 10, 192, 64);
	bt_option = RectMake(50, bt_result.bottom + 10, 224, 64);
	bt_exit = RectMake(50, bt_option.bottom + 10, 128, 64);
	for (int i = 0; i < 3; i++)
	{
		bt_difficultyselect[i] = RectMake(300, bt_gamestart.top + 74 * i, 224, 64);
	}
	difficulty = 0;
	selectplayer = 0;
	selectkey = 0;
	
	//인게임
	amount_pointitem = amount_graze = 0;
	starthp = 2;
	startbomb = 3;
	playerhp = starthp;
	playerbomb = startbomb;//체력,폭탄
	hiscore = score = 0;
	playerpower = 0;
	playerspeed = 8.0f;

	//탄 반지름 고정
	ultrasmall_b.radius = 4;
	small_b.radius = 6;
	normal_b.radius = 8;
	big_b.radius = 12;

	//그레이즈 고정
	ultrasmall_b.isgraze = false;
	small_b.isgraze = false;
	normal_b.isgraze = false;
	big_b.isgraze = false;

	playerxy.x = (WINSIZEX - 300) / 2;
	playerxy.y = WINSIZEY - 74;
	playersoulxy.x = playerxy.x + 32;
	playersoulxy.y = playerxy.y;
	playerrect = RectMakeCenter(playerxy.x, playerxy.y, 32, 48);
	isshift = isbomb = false;

	zbullet.atk = 1;

	xbullet.x = (playerrect.right + playerrect.left) / 2;
	xbullet.y = (playerrect.top + playerrect.bottom) / 2;
	xbullet.radius = 16;
	xbullet.speed = 12;
	xbullet.atk = 10;
	xbullet.angle = PI / 2;
	xbullet.release = false;
	zbullet.isgraze = xbullet.isgraze = true;

	cbullet.speed = 20;
	cbullet.angle = -PI / 2;
	cbullet.radius = 200;
	cbullet.isgraze = true;
	cbullet.release = true;

	wall[0] = { 0,0,700,50 };
	wall[1] = { 0,800,700,850 };
	wall[2] = { 0,50,50,800 };
	wall[3] = { 650,50,700,800 };

	vpoint.clear();
	vpower.clear();

	vultrasmall_b.clear();
	vsmall_b.clear();
	vnormal_b.clear();
	vbig_b.clear();

	vbulletcontainer_b.clear();
	vbulletcontainer_b.push_back(&vultrasmall_b);
	vbulletcontainer_b.push_back(&vsmall_b);
	vbulletcontainer_b.push_back(&vnormal_b);
	vbulletcontainer_b.push_back(&vbig_b);

	vzbullet.clear();
	vxbullet.clear();
	vcbullet.clear();

	vbulletcontainer.clear();
	vbulletcontainer.push_back(&vzbullet);
	vbulletcontainer.push_back(&vxbullet);
	//vbulletcontainer.push_back(&vcbullet);
		
	vmob1.clear();
	vmob2.clear();
	vmob3.clear();

	vmobcontainer.clear();
	vmobcontainer.push_back(&vmob1);
	vmobcontainer.push_back(&vmob2);
	vmobcontainer.push_back(&vmob3);

	st1b.enemycount = 0;
	st1b.spell = 2;
	
	st2b.enemycount = 0;
	st2b.spell = 3;

	mob1.item.itemtype = ITEMTYPE(ITEMPOINT);
	mob2.item.itemtype = ITEMTYPE(ITEMPOWER);
	mob3.item.itemtype = ITEMTYPE(ITEMBOMB);
	

	//리절트
	for (int i = 0; i < 10; i++)
	{
		resultscore[i] = 0;
	}

	return S_OK;
}

//메모리 해제
void mainGame::release(void)  
{
	gameNode::release(); //손대지 마셈

}

//연산은 여기서 한다
void mainGame::update(void)
{
	gameNode::update();  //손대지 마셈
	if (titlescreen == TITLESCREEN(TITLE))
	{
		if (!isselectdiff)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_UP) && selectkey > 0)
			{
				selectkey--;
			}
			if (KEYMANAGER->isOnceKeyDown(VK_DOWN) && selectkey < 3)
			{
				selectkey++;
			}

			if (KEYMANAGER->isOnceKeyDown('Z'))
			{
				if (selectkey == 0)
				{
					isselectdiff = true;
				}
				if (selectkey == 1)
				{
					titlescreen = TITLESCREEN(RESULT);
				}
				if (selectkey == 2)
				{
					titlescreen = TITLESCREEN(OPTION);
				}
				if (selectkey == 3)
				{
					PostQuitMessage(0);
				}
				selectkey = 0;
			}
		}
		if (isselectdiff)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_UP) && selectkey > 0)
			{
				selectkey--;
			}
			if (KEYMANAGER->isOnceKeyDown(VK_DOWN) && selectkey < 2)
			{
				selectkey++;
			}
			if (KEYMANAGER->isOnceKeyDown('Z'))
			{
				titlescreen = TITLESCREEN(START);
				difficulty = selectkey;
				selectkey = 0;
				isselectdiff = false;
			}
			if (KEYMANAGER->isOnceKeyDown('X'))
			{
				selectkey = 0;
				isselectdiff = false;
			}
		}
	}

	if (titlescreen == TITLESCREEN(START))
	{
		if (playerhpzero)
		{
			if (playerhpzeroscreencount == 100)
			{
				init();
			}
			playerhpzeroscreencount++;
		}
		if (KEYMANAGER->isStayKeyDown(VK_LSHIFT))
		{
			isshift = true;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LSHIFT))
		{
			isshift = false;
		}
		if (!playerhpzero)
		{
			if (KEYMANAGER->isStayKeyDown('Z'))
			{

				zbulletfire();
			}
			if (KEYMANAGER->isOnceKeyDown('X'))
			{

				xbulletfire();
			}

			if (KEYMANAGER->isOnceKeyDown('C'))
			{
				if (playerbomb > 0 && !isbomb)
				{
					playerbomb--;
					isbomb = true;
				}
			}
		}
		if (!ishitted&&!playerhpzero)
		{
			if (KEYMANAGER->isStayKeyDown('W'))
			{
				if (isshift)playerxy.y -= playerspeed / 3;
				else playerxy.y -= playerspeed;
			}
			if (KEYMANAGER->isStayKeyDown('S'))
			{
				if (isshift)playerxy.y += playerspeed / 3;
				else playerxy.y += playerspeed;
			}
			if (KEYMANAGER->isStayKeyDown('A'))
			{
				if (isshift)playerxy.x -= playerspeed / 3;
				else playerxy.x -= playerspeed;
			}
			if (KEYMANAGER->isStayKeyDown('D'))
			{
				if (isshift)playerxy.x += playerspeed / 3;
				else playerxy.x += playerspeed;
			}

			if (getDistance(_ptMouse.x, _ptMouse.y, playerxy.x, playerxy.y) >= 50)//마우스,피탄점 거리50이상이면
			{
				isplayermove = true;
				if (isshift)
				{
					playerxy.x += cosf(atan2f(_ptMouse.y - playerxy.y, _ptMouse.x - playerxy.x)) * playerspeed / 3;
					playerxy.y += sinf(atan2f(_ptMouse.y - playerxy.y, _ptMouse.x - playerxy.x)) * playerspeed / 3;
				}
				else
				{
					playerxy.x += cosf(atan2f(_ptMouse.y - playerxy.y, _ptMouse.x - playerxy.x)) * playerspeed;
					playerxy.y += sinf(atan2f(_ptMouse.y - playerxy.y, _ptMouse.x - playerxy.x)) * playerspeed;
				}
			}
			else
			{
				isplayermove = false;
			}
			if (getDistance(playerxy.x, playerxy.y, playersoulxy.x + cosf(atan2f(_ptMouse.y - playersoulxy.y, _ptMouse.x - playersoulxy.x)) * 15, playersoulxy.y + sinf(atan2f(_ptMouse.y - playersoulxy.y, _ptMouse.x - playersoulxy.x)) * 15) <= 50)//피탄점,유령 거리50밑이면
			{
				if (getDistance(_ptMouse.x, _ptMouse.y, playersoulxy.x, playersoulxy.y) > 15)//마우스,유령 거리
				{
					playersoulxy.x += cosf(atan2f(_ptMouse.y - playersoulxy.y, _ptMouse.x - playersoulxy.x)) * 15;
					playersoulxy.y += sinf(atan2f(_ptMouse.y - playersoulxy.y, _ptMouse.x - playersoulxy.x)) * 15;
				}
				else
				{
					playersoulxy.x = _ptMouse.x;
					playersoulxy.y = _ptMouse.y;
				}
			}
			else if (getDistance(playerxy.x, playerxy.y, playersoulxy.x, playersoulxy.y) >= 65)
			{
				playersoulxy.x = playerxy.x + 50 * cosf(atan2f(playersoulxy.y - playerxy.y, playersoulxy.x - playerxy.x));
				playersoulxy.y = playerxy.y + 50 * sinf(atan2f(playersoulxy.y - playerxy.y, playersoulxy.x - playerxy.x));
			}
		}
		playerrect = RectMakeCenter(playerxy.x, playerxy.y, 32, 48);

		zbullet.x = playersoulxy.x;
		zbullet.y = playersoulxy.y;
		xbullet.x = (playerrect.right + playerrect.left) / 2;
		xbullet.y = (playerrect.top + playerrect.bottom) / 2;
		for (int i = 0; i < 4; i++)
		{
			if (isCollisionReaction(wall[i], playerrect))
			{
				playerxy.x = (playerrect.right + playerrect.left) / 2;
				playerxy.y = (playerrect.bottom + playerrect.top) / 2;
			}
		}
		cbulletfire();

		Releasemob();
		hitmob();
		dropitem();
		collisionplayer();
		cbulletCanDeleteEbullet();
		mobmove();

		if (stage[0] == 1 && stage[1] == 1)stage1_1();
		if (stage[0] == 1 && stage[1] == 2)stage1_2();
		if (stage[0] == 1 && stage[1] == 3)stage1_3();
		if (stage[0] == 2 && stage[1] == 1)playerhpzero=true;

	}

	if (titlescreen == TITLESCREEN(RESULT))
	{
		if (KEYMANAGER->isOnceKeyDown('X'))//나가기
		{
			titlescreen = TITLESCREEN(TITLE);
		}
	}

	if (titlescreen == TITLESCREEN(OPTION))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_UP) && selectkey > 0)
		{
			selectkey--;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN) && selectkey < 1)
		{
			selectkey++;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			if (selectkey == 0 && starthp > 0)starthp--;
			if (selectkey == 1 && startbomb > 0)startbomb--;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			if (selectkey == 0 && starthp < 5)starthp++;
			if (selectkey == 1 && startbomb < 5)startbomb++;
		}
		if (KEYMANAGER->isOnceKeyDown('X'))//나가기
		{
			titlescreen = TITLESCREEN(TITLE);
			playerhp = starthp;
			playerbomb = startbomb;//체력,폭탄
			selectkey = 0;
		}
	}
	
	if (KEYMANAGER->isOnceKeyDown(VK_TAB))
	{
		if(rectmode)rectmode = false;
		else rectmode = true;
	}

	bulletmove();
}

//그리는 것은 이제 여기에다
void mainGame::render()
{
	//윈도우 창 영역만큼의 흰색도화지를 깔아준다 
	//예전에는 흰색 비트맵 이미지를 깔아두기도 했었다
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================== 이 위는 손대지 마시오 =========================
	if (titlescreen == TITLESCREEN(TITLE))
	{
		png_bg->render(getMemDC(), 0, 0, 0, 0, 1000, 1000);
		if (selectkey == 0 || isselectdiff)
		{
			png_start->render(getMemDC(), bt_gamestart.left, bt_gamestart.top, 0, 0, 160, 64);

		}
		else
		{
			png_start->render(getMemDC(),bt_gamestart.left, bt_gamestart.top, 0, 128, 160, 64);
		}
		if (isselectdiff)
		{
			png_result->render(getMemDC(), bt_result.left, bt_result.top, 192, 192, 192, 64);
			png_option->render(getMemDC(), bt_option.left, bt_option.top, 816, 960, 208, 64);
			png_exit->render(getMemDC(), bt_exit.left, bt_exit.top, 776, 448, 128, 64);

			png_selectdifficulty->render(getMemDC(), bt_difficultyselect[0].left, bt_difficultyselect[0].top, 784, 0, 240, 64);
			png_selectdifficulty->render(getMemDC(), bt_difficultyselect[1].left, bt_difficultyselect[1].top, 784, 64, 240, 64);
			png_selectdifficulty->render(getMemDC(), bt_difficultyselect[2].left, bt_difficultyselect[2].top, 520, 0, 240, 64);
			if (selectkey == 0) { EllipseMake(getMemDC(), bt_difficultyselect[0].right + 10, bt_difficultyselect[0].top, 20, 20); }
			else if (selectkey == 1) { EllipseMake(getMemDC(), bt_difficultyselect[1].right + 10, bt_difficultyselect[1].top, 20, 20); }
			else if (selectkey == 2) { EllipseMake(getMemDC(), bt_difficultyselect[2].right + 10, bt_difficultyselect[2].top, 20, 20); }
		}
		else
		{
			if (selectkey == 1)
			{
				png_result->render(getMemDC(), bt_result.left, bt_result.top, 192, 64, 192, 64);
			}
			else
			{
				png_result->render(getMemDC(), bt_result.left, bt_result.top, 192, 192, 192, 64);
			}
			if (selectkey == 2)
			{
				png_option->render(getMemDC(), bt_option.left, bt_option.top, 816, 832, 208, 64);
			}
			else
			{
				png_option->render(getMemDC(), bt_option.left, bt_option.top, 816, 960, 208, 64);
			}
			if (selectkey == 3)
			{
				png_exit->render(getMemDC(), bt_exit.left, bt_exit.top, 776, 320, 128, 64);
			}
			else
			{
				png_exit->render(getMemDC(), bt_exit.left, bt_exit.top, 776, 448, 128, 64);
			}
		}
	}

	if (titlescreen == TITLESCREEN(START))
	{
		//c탄
		vicbullet = vcbullet.begin();
		for (vicbullet; vicbullet != vcbullet.end(); ++vicbullet)
		{
			if (vicbullet->release)
			{
				png_cbullet->render(getMemDC(), (int)vicbullet->x - (int)vicbullet->radius, (int)vicbullet->y - (int)vicbullet->radius, 0, 0, 400, 400);
			}
			
		}
		if (isbomb)
		{
			png_bombeffect->render(getMemDC(), (int)playerxy.x - 128, (int)playerxy.y - 128, 0, 0, 256, 256);
		}
		//플레이어 모션
		if (respawn % 2 == 0)
		{
			if (!isplayermove)//움직이지 않는다면
			{
				playermotion++;
				if (playermotion == 5 * 4)playermotion = 0;
				player_movecount = 0;
				if (cosf(atan2f(_ptMouse.y - playerxy.y, _ptMouse.x - playerxy.x)) <= 0)
				{
					if (playermotion < 5)png_player->render(getMemDC(), playerrect.left, playerrect.top, 0, 0, 32, 48);
					else if (playermotion < 10)png_player->render(getMemDC(), playerrect.left, playerrect.top, 32, 0, 32, 48);
					else if (playermotion < 15)png_player->render(getMemDC(), playerrect.left, playerrect.top, 64, 0, 32, 48);
					else if (playermotion < 20)png_player->render(getMemDC(), playerrect.left, playerrect.top, 96, 0, 32, 48);
				}
				else if (cosf(atan2f(_ptMouse.y - playerxy.y, _ptMouse.x - playerxy.x)) > 0)
				{
					if (playermotion < 5)png_player->render(getMemDC(), playerrect.left, playerrect.top, 224, 0, 32, 48);
					else if (playermotion < 10)png_player->render(getMemDC(), playerrect.left, playerrect.top, 192, 0, 32, 48);
					else if (playermotion < 15)png_player->render(getMemDC(), playerrect.left, playerrect.top, 160, 0, 32, 48);
					else if (playermotion < 20)png_player->render(getMemDC(), playerrect.left, playerrect.top, 128, 0, 32, 48);

				}
			}
			else//움직일 경우
			{
				if (cosf(atan2f(_ptMouse.y - playerxy.y, _ptMouse.x - playerxy.x)) > 0)//우측
				{
					if (player_movecount < 0)player_movecount = 0;
					if (player_movecount < 32)player_movecount++;
				}
				else//좌측
				{
					if (player_movecount > 0)player_movecount = 0;
					if (player_movecount > -32)player_movecount--;
				}
				if (player_movecount > 0 && player_movecount <= 8 * 1)png_player->render(getMemDC(), playerrect.left, playerrect.top, 32 * 7, 48, 32, 48);
				else if (player_movecount > 8 * 1 && player_movecount <= 8 * 2)png_player->render(getMemDC(), playerrect.left, playerrect.top, 32 * 6, 48, 32, 48);
				else if (player_movecount > 8 * 2 && player_movecount <= 8 * 3)png_player->render(getMemDC(), playerrect.left, playerrect.top, 32 * 5, 48, 32, 48);
				else if (player_movecount > 8 * 3 && player_movecount <= 8 * 4)png_player->render(getMemDC(), playerrect.left, playerrect.top, 32 * 4, 48, 32, 48);

				if (player_movecount < 0 && player_movecount >= -8 * 1)png_player->render(getMemDC(), playerrect.left, playerrect.top, 32 * 0, 48, 32, 48);
				else if (player_movecount < -8 * 1 && player_movecount >= -8 * 2)png_player->render(getMemDC(), playerrect.left, playerrect.top, 32 * 1, 48, 32, 48);
				else if (player_movecount < -8 * 2 && player_movecount >= -8 * 3)png_player->render(getMemDC(), playerrect.left, playerrect.top, 32 * 2, 48, 32, 48);
				else if (player_movecount < -8 * 3 && player_movecount >= -8 * 4)png_player->render(getMemDC(), playerrect.left, playerrect.top, 32 * 3, 48, 32, 48);
			}
		}
		//위에까지 플레이어모션
		if (isshift)
		{
			EllipseMakeCenter(getMemDC(), playerxy.x, playerxy.y, 6, 6);
		}
		//유령
		png_playersoul->render(getMemDC(), (int)playersoulxy.x - 16, (int)playersoulxy.y - 16, 0, 192, 32, 32);

		//아이템
		vipoint = vpoint.begin();
		for (vipoint; vipoint != vpoint.end(); ++vipoint)
		{
			if (vipoint->release)
			{
				if (vipoint->itemtype == ITEMTYPE(ITEMPOINT))
				{
					png_item->render(getMemDC(), (int)vipoint->x - 8, (int)vipoint->y - 8, 16, 64, 16, 16);
				}
				if (vipoint->itemtype == ITEMTYPE(ITEMPOWER))
				{
					png_item->render(getMemDC(), (int)vipoint->x - 8, (int)vipoint->y - 8, 0, 64, 16, 16);
				}
				if (vipoint->itemtype == ITEMTYPE(ITEMHP))
				{
					png_item->render(getMemDC(), (int)vipoint->x - 8, (int)vipoint->y - 8, 80, 64, 16, 16);
				}
				if (vipoint->itemtype == ITEMTYPE(ITEMBOMB))
				{
					png_item->render(getMemDC(), (int)vipoint->x - 8, (int)vipoint->y - 8, 48, 64, 16, 16);
				}
			}
		}

		//몹
		vimob1 = vmob1.begin();
		for (vimob1; vimob1 != vmob1.end(); ++vimob1)
		{
			if (vimob1->release)
			{
				png_enemy->render(getMemDC(), (int)vimob1->x - 16, (int)vimob1->y - 16, 0, (vimob1->color * 32), 32, 32);
			}
		}

		vimob2 = vmob2.begin();
		for (vimob2; vimob2 != vmob2.end(); ++vimob2)
		{
			if (vimob2->release)
			{
				png_enemy->render(getMemDC(), (int)vimob2->x - 16, (int)vimob2->y - 16, 0, 256 + (vimob2->color * 32), 32, 32);
			}
		}

		vimob3 = vmob3.begin();
		for (vimob3; vimob3 != vmob3.end(); ++vimob3)
		{
			if (vimob3->release)
			{
				png_enemy->render(getMemDC(), (int)vimob3->x - 16, (int)vimob3->y - 16, vimob3->color * 32, 192, 32, 32);
			}
		}

		if (st1b.release)
		{
			png_boss1->render(getMemDC(), (int)st1b.x - 150, (int)st1b.y - 150, 0, 0, 300, 300);
		}

		//초소형탄
		viultrasmall_b = vultrasmall_b.begin();
		for (viultrasmall_b; viultrasmall_b != vultrasmall_b.end(); ++viultrasmall_b)
		{
			if (viultrasmall_b->release)
			{
				png_enemytama->render(getMemDC(), (int)viultrasmall_b->x - viultrasmall_b->radius, (int)viultrasmall_b->y - viultrasmall_b->radius, 0, 248, 8, 8);
			}
		}

		vismall_b = vsmall_b.begin();
		for (vismall_b; vismall_b != vsmall_b.end(); ++vismall_b)
		{
			if (vismall_b->release)
			{
				png_enemytama->render(getMemDC(), (int)vismall_b->x - 8, (int)vismall_b->y - 8, 96, 240, 16, 16);
			}
		}

		vinormal_b = vnormal_b.begin();
		for (vinormal_b; vinormal_b != vnormal_b.end(); ++vinormal_b)
		{
			if (vinormal_b->release)
			{
				png_enemytama->render(getMemDC(), (int)vinormal_b->x - 8, (int)vinormal_b->y - 8, 0, 48, 16, 16);
			}
		}

		vibig_b = vbig_b.begin();
		for (vibig_b; vibig_b != vbig_b.end(); ++vibig_b)
		{
			if (vibig_b->release)
			{
				png_enemytama->render(getMemDC(), (int)vibig_b->x - 16, (int)vibig_b->y - 16, 128, 112, 32, 32);
			}
		}

		//z탄
		for (int i = 0; i < vzbullet.size(); i++)
		{
			if (vzbullet[i].release)
			{
				if (vzbullet[i].angle < PI * 13 / 24 && vzbullet[i].angle >= PI * 11 / 24)png_zshot->render(getMemDC(), (int)vzbullet[i].x - 24, (int)vzbullet[i].y - 24, 48 * 0, 48 * 4, 48, 48);
				if (vzbullet[i].angle < PI * 11 / 24 && vzbullet[i].angle >= PI * 9 / 24)png_zshot->render(getMemDC(), (int)vzbullet[i].x - 24, (int)vzbullet[i].y - 24, 48 * 1, 48 * 4, 48, 48);
				if (vzbullet[i].angle < PI * 9 / 24 && vzbullet[i].angle >= PI * 7 / 24)png_zshot->render(getMemDC(), (int)vzbullet[i].x - 24, (int)vzbullet[i].y - 24, 48 * 2, 48 * 4, 48, 48);
				if (vzbullet[i].angle < PI * 7 / 24 && vzbullet[i].angle >= PI * 5 / 24)png_zshot->render(getMemDC(), (int)vzbullet[i].x - 24, (int)vzbullet[i].y - 24, 48 * 3, 48 * 4, 48, 48);
				if (vzbullet[i].angle < PI * 5 / 24 && vzbullet[i].angle >= PI * 3 / 24)png_zshot->render(getMemDC(), (int)vzbullet[i].x - 24, (int)vzbullet[i].y - 24, 48 * 4, 48 * 4, 48, 48);
				if (vzbullet[i].angle < PI * 3 / 24 && vzbullet[i].angle >= PI * 1 / 24)png_zshot->render(getMemDC(), (int)vzbullet[i].x - 24, (int)vzbullet[i].y - 24, 48 * 4, 48 * 3, 48, 48);
				if (vzbullet[i].angle < PI * 1 / 24 && vzbullet[i].angle >= PI * -1 / 24)png_zshot->render(getMemDC(), (int)vzbullet[i].x - 24, (int)vzbullet[i].y - 24, 48 * 3, 48 * 3, 48, 48);
				if (vzbullet[i].angle < PI * -1 / 24 && vzbullet[i].angle >= PI * -3 / 24)png_zshot->render(getMemDC(), (int)vzbullet[i].x - 24, (int)vzbullet[i].y - 24, 48 * 2, 48 * 3, 48, 48);
				if (vzbullet[i].angle < PI * -3 / 24 && vzbullet[i].angle >= PI * -5 / 24)png_zshot->render(getMemDC(), (int)vzbullet[i].x - 24, (int)vzbullet[i].y - 24, 48 * 1, 48 * 3, 48, 48);
				if (vzbullet[i].angle < PI * -5 / 24 && vzbullet[i].angle >= PI * -7 / 24)png_zshot->render(getMemDC(), (int)vzbullet[i].x - 24, (int)vzbullet[i].y - 24, 48 * 0, 48 * 3, 48, 48);
				if (vzbullet[i].angle < PI * -7 / 24 && vzbullet[i].angle >= PI * -9 / 24)png_zshot->render(getMemDC(), (int)vzbullet[i].x - 24, (int)vzbullet[i].y - 24, 48 * 0, 48 * 2, 48, 48);
				if (vzbullet[i].angle < PI * -9 / 24 && vzbullet[i].angle >= PI * -11 / 24)png_zshot->render(getMemDC(), (int)vzbullet[i].x - 24, (int)vzbullet[i].y - 24, 48 * 1, 48 * 2, 48, 48);

				if (vzbullet[i].angle < PI * -11 / 24 && vzbullet[i].angle >= PI * -13 / 24)png_zshot->render(getMemDC(), (int)vzbullet[i].x - 24, (int)vzbullet[i].y - 24, 48 * 4, 48 * 0, 48, 48);
				if (vzbullet[i].angle < PI * -13 / 24 && vzbullet[i].angle >= PI * -15 / 24)png_zshot->render(getMemDC(), (int)vzbullet[i].x - 24, (int)vzbullet[i].y - 24, 48 * 3, 48 * 0, 48, 48);
				if (vzbullet[i].angle < PI * -15 / 24 && vzbullet[i].angle >= PI * -17 / 24)png_zshot->render(getMemDC(), (int)vzbullet[i].x - 24, (int)vzbullet[i].y - 24, 48 * 2, 48 * 0, 48, 48);
				if (vzbullet[i].angle < PI * -17 / 24 && vzbullet[i].angle >= PI * -19 / 24)png_zshot->render(getMemDC(), (int)vzbullet[i].x - 24, (int)vzbullet[i].y - 24, 48 * 1, 48 * 0, 48, 48);
				if (vzbullet[i].angle < PI * -19 / 24 && vzbullet[i].angle >= PI * -21 / 24)png_zshot->render(getMemDC(), (int)vzbullet[i].x - 24, (int)vzbullet[i].y - 24, 48 * 0, 48 * 0, 48, 48);
				if (vzbullet[i].angle < PI * -21 / 24 && vzbullet[i].angle >= PI * -23 / 24)png_zshot->render(getMemDC(), (int)vzbullet[i].x - 24, (int)vzbullet[i].y - 24, 48 * 0, 48 * 1, 48, 48);
				if (vzbullet[i].angle < PI * -23 / 24 && vzbullet[i].angle >= PI * 23 / 24)png_zshot->render(getMemDC(), (int)vzbullet[i].x - 24, (int)vzbullet[i].y - 24, 48 * 1, 48 * 1, 48, 48);
				if (vzbullet[i].angle < PI * 23 / 24 && vzbullet[i].angle >= PI * 21 / 24)png_zshot->render(getMemDC(), (int)vzbullet[i].x - 24, (int)vzbullet[i].y - 24, 48 * 2, 48 * 1, 48, 48);
				if (vzbullet[i].angle < PI * 21 / 24 && vzbullet[i].angle >= PI * 19 / 24)png_zshot->render(getMemDC(), (int)vzbullet[i].x - 24, (int)vzbullet[i].y - 24, 48 * 3, 48 * 1, 48, 48);
				if (vzbullet[i].angle < PI * 19 / 24 && vzbullet[i].angle >= PI * 17 / 24)png_zshot->render(getMemDC(), (int)vzbullet[i].x - 24, (int)vzbullet[i].y - 24, 48 * 4, 48 * 1, 48, 48);
				if (vzbullet[i].angle < PI * 17 / 24 && vzbullet[i].angle >= PI * 15 / 24)png_zshot->render(getMemDC(), (int)vzbullet[i].x - 24, (int)vzbullet[i].y - 24, 48 * 4, 48 * 2, 48, 48);
				if (vzbullet[i].angle < PI * 15 / 24 && vzbullet[i].angle >= PI * 13 / 24)png_zshot->render(getMemDC(), (int)vzbullet[i].x - 24, (int)vzbullet[i].y - 24, 48 * 3, 48 * 2, 48, 48);
			}
		}
		//x탄
		for (int i = 0; i < vxbullet.size(); i++)
		{
			if (vxbullet[i].release)
			{
				png_enemytama->render(getMemDC(), (int)vxbullet[i].x - 16, (int)vxbullet[i].y - 16, 128, 208, 32, 32);
			}
		}

		/*char ss[128];
		sprintf_s(ss, sizeof(ss), "%d", count);
		TextOut(getMemDC(), 500, 500, ss, strlen(ss));*/
		if (playerhpzero)//셔터쾅
		{
				if (playerhpzeroscreencount < 15)
				{
					int& i = playerhpzeroscreencount;
					stagefailedup->render(getMemDC(), 50, 50 + i * 10, 1, 0, 600, 233);
					stagefaileddown->render(getMemDC(), 50, 800 - 227 - i * 10, 1, 235, 600, 227);
					stagefailedblackline->render(getMemDC(), 50, 50 + i * 10 - 198);
					stagefailedblackline->render(getMemDC(), 50, 800 - 227 - i * 10 + 198);
				}
				if (playerhpzeroscreencount >= 15)
				{
					stagefailedup->render(getMemDC(), 50, 425 - 233 + 6, 1, 0, 600, 233);
					stagefaileddown->render(getMemDC(), 50, 425 - 6, 1, 235, 600, 227);
					stagefailedblackline->render(getMemDC(), 50, 425 - 233 + 6 - 198);
					stagefailedblackline->render(getMemDC(), 50, 425 - 6 + 198);
					stagefailedlight->render(getMemDC(), (WINSIZEX - 300) / 2 - 53, WINSIZEY / 2 - 3, 1, 464, 106, 8);
					if(stagepassflag)stagepass->render(getMemDC(), (WINSIZEX - 300) / 2 - 47, WINSIZEY / 2 - 10);
				}
			
		}
		png_scoretablebg->render(getMemDC(), WINSIZEX - 300, 0, 0, 0, 300, 850);
		//벽700x850
		for (int i = 0; i < 14; i++)
		{
			png_wall->render(getMemDC(), i * 50, 0, 0, 0, 50, 50);
			png_wall->render(getMemDC(), i * 50, 800, 0, 0, 50, 50);
		}
		for (int i = 0; i < 15; i++)
		{
			png_wall->render(getMemDC(), 0, 50 + i * 50, 0, 0, 50, 50);
			png_wall->render(getMemDC(), 650, 50 + i * 50, 0, 0, 50, 50);
		}
		if (st1b.release)
		{
			hpbar->render(getMemDC(), 50, 30, 0, 0, st1b.hp * 6 / 5, 10);
		}

		png_scoretable->render(getMemDC(), WINSIZEX - 280, 168, 0, 192, 96, 160);

		//score
		for (int pp = 1; pp < 8; pp++)
		{
			for (int i = 0; i < 10; i++)
			{
				if ((score % (int)pow(10, pp)) / (int)pow(10, pp - 1) == i)
				{
					png_number->render(getMemDC(), WINSIZEX - 180 + 20 * (7 - pp), 168, 32 * i, 256, 32, 32);
				}

			}
		}
		//player
		for (int i = 0; i < playerhp; i++)
		{
			png_scoretable->render(getMemDC(), WINSIZEX - 180 + i * 32, 200, 128, 160, 32, 32);
		}
		//bomb
		for (int i = 0; i < playerbomb; i++)
		{
			png_scoretable->render(getMemDC(), WINSIZEX - 180 + i * 32, 232, 160, 160, 32, 32);
		}
		//power
		for (int i = 0; i < 10; i++)
		{
			if (playerpower / 10 == i)
			{
				png_number->render(getMemDC(), WINSIZEX - 180, 264, 32 * i, 256, 32, 32);
			}
			if (playerpower % 10 == i)
			{
				png_number->render(getMemDC(), WINSIZEX - 160, 264, 32 * i, 256, 32, 32);
			}
		}
		//graze
		for (int pp = 1; pp < 5; pp++)
		{
			for (int i = 0; i < 10; i++)
			{
				if ((amount_graze % (int)pow(10, pp)) / (int)pow(10, pp - 1) == i && amount_graze >= (int)pow(10, pp - 1))
				{
					png_number->render(getMemDC(), WINSIZEX - 180 + 20 * (4 - pp), 296, 32 * i, 256, 32, 32);
				}

			}
		}
		if (amount_graze == 0)
		{
			png_number->render(getMemDC(), WINSIZEX - 120, 296, 0, 256, 32, 32);
		}
		//point
		for (int pp = 1; pp < 5; pp++)
		{
			for (int i = 0; i < 10; i++)
			{
				if (((int)amount_pointitem % (int)pow(10, pp)) / (int)pow(10, pp - 1) == i && amount_pointitem >= (int)pow(10, pp - 1))
				{
					png_number->render(getMemDC(), WINSIZEX - 180 + 20 * (4 - pp), 328, 32 * i, 256, 32, 32);
				}
			}
		}
		if (amount_pointitem == 0)
		{
			png_number->render(getMemDC(), WINSIZEX - 120, 328, 0, 256, 32, 32);
		}
		if (difficulty == DIFF(EASY))
		{
			png_selectdifficulty->render(getMemDC(), WINSIZEX - 270, 20, 784, 0, 240, 64);
		}
		if (difficulty == DIFF(NORMAL))
		{
			png_selectdifficulty->render(getMemDC(), WINSIZEX - 270, 20, 784, 64, 240, 64);
		}
		if (difficulty == DIFF(HARD))
		{
			png_selectdifficulty->render(getMemDC(), WINSIZEX - 270, 20, 520, 0, 240, 64);
		}
	}

	if (titlescreen == TITLESCREEN(RESULT))
	{


		png_bg->render(getMemDC(), 0, 0, 0, 0, 1000, 1000);
		char ss[128];
		sprintf_s(ss, sizeof(ss), "세이브파일 만드는법 몰라서 안만듬(X키 누르면 뒤로감)");
		TextOut(getMemDC(), WINSIZEX / 2 - 250, WINSIZEY / 2, ss, strlen(ss));
	}
	if (titlescreen == TITLESCREEN(OPTION))
	{

		png_bg->render(getMemDC(), 0, 0, 0, 0, 1000, 1000);
		for (int i = 0; i < 2; i++)
		{
			if (selectkey == 0)
			{
				png_option->render(getMemDC(), 100, 200, 0, 256, 184, 64);
				png_option->render(getMemDC(), 100, 264, 160, 896, 184, 64);
			}
			if (selectkey == 1)
			{
				png_option->render(getMemDC(), 100, 200, 0, 384, 184, 64);
				png_option->render(getMemDC(), 100, 264, 160, 768, 184, 64);
			}
		}
		for (int i = 0; i < 6; i++)
		{
			if (starthp == i)
			{
				png_option->render(getMemDC(), 300 + 64 * i, 200, 64 * i, 512, 64, 64);//흰색
			}
			else
			{
				png_option->render(getMemDC(), 300 + 64 * i, 200, 64 * i, 640, 64, 64);//반투명
			}
			if (startbomb == i)
			{
				png_option->render(getMemDC(), 300 + 64 * i, 264, 64 * i, 512, 64, 64);//흰색
			}
			else
			{
				png_option->render(getMemDC(), 300 + 64 * i, 264, 64 * i, 640, 64, 64);//반투명
			}
		}
	}
	
	if(rectmode)//사각형
	{
		if (titlescreen == TITLESCREEN(TITLE))
		{
			RectangleMake(getMemDC(), bt_gamestart);
			RectangleMake(getMemDC(), bt_result);
			RectangleMake(getMemDC(), bt_option);
			RectangleMake(getMemDC(), bt_exit);
			if (isselectdiff)
			{
				for (int i = 0; i < 3; i++)
				{
					RectangleMake(getMemDC(), bt_difficultyselect[i]);
				}
			}
		}
		else if (titlescreen == TITLESCREEN(START))
		{
			
			RectangleMake(getMemDC(), playerrect);
			EllipseMakeCenter(getMemDC(), playerxy.x, playerxy.y, 6, 6);
			for (int i = 0; i < vzbullet.size(); i++)
			{
				if (vzbullet[i].release)
				{
					Ellipse(getMemDC(), vzbullet[i].x - vzbullet[i].radius, vzbullet[i].y - vzbullet[i].radius, vzbullet[i].x + vzbullet[i].radius, vzbullet[i].y + vzbullet[i].radius);
					/*char sss[128];
					sprintf_s(sss, sizeof(sss), "%d", i);
					TextOut(getMemDC(), vzbullet[i].x, vzbullet[i].y, sss, strlen(sss));*/
				}
			}
			for (int i = 0; i < vxbullet.size(); i++)
			{
				if (vxbullet[i].release)
				{
					Ellipse(getMemDC(), vxbullet[i].x - vxbullet[i].radius, vxbullet[i].y - vxbullet[i].radius, vxbullet[i].x + vxbullet[i].radius, vxbullet[i].y + vxbullet[i].radius);
					/*char ss[128];
					sprintf_s(ss, sizeof(ss), "%d", i);
					TextOut(getMemDC(), vxbullet[i].x, vxbullet[i].y, ss, strlen(ss));*/
				}
			}

			for (int i = 0; i < vmob1.size(); i++)
			{
				if (vmob1[i].release)
				{
					RectangleMake(getMemDC(), vmob1[i].x - 16, vmob1[i].y - 16, 32, 32);
					/*char ss[128];
					sprintf_s(ss, sizeof(ss), "%d", i);
					TextOut(getMemDC(), vxbullet[i].x, vxbullet[i].y, ss, strlen(ss));*/
				}
			}

			for (int i = 0; i < 4; i++)
			{
				RectangleMake(getMemDC(), wall[i]);
			}

			EllipseMakeCenter(getMemDC(), playersoulxy.x, playersoulxy.y, 32, 32);
		}
	}


	//================== 이 아래는 손대지 마시오 ========================
	this->getBackBuffer()->render(getDC(), 0, 0);//hdc영역에 그려준다 
}

void mainGame::zbulletfire()
{
	if (shotdelay == 0)
	{
		zbullet.x = playersoulxy.x;
		zbullet.y = playersoulxy.y;
		zbullet.radius = 10;
		zbullet.speed = 20;
		zbullet.release = true;
		if (playerpower < 8)
		{
			zbullet.angle = atan2f(playerxy.y - playersoulxy.y, playersoulxy.x - playerxy.x);
			vzbullet.push_back(zbullet);
			
		}
		else if (playerpower < 16)
		{
			zbullet.angle = atan2f(playerxy.y - playersoulxy.y, playersoulxy.x - playerxy.x) - 0.04;
			vzbullet.push_back(zbullet);

			zbullet.angle = atan2f(playerxy.y - playersoulxy.y, playersoulxy.x - playerxy.x) + 0.04;
			vzbullet.push_back(zbullet);
		}
		else if (playerpower < 24)
		{
			zbullet.angle = atan2f(playerxy.y - playersoulxy.y, playersoulxy.x - playerxy.x);
			vzbullet.push_back(zbullet);

			zbullet.angle = atan2f(playerxy.y - playersoulxy.y, playersoulxy.x - playerxy.x) - 0.08;
			vzbullet.push_back(zbullet);

			zbullet.angle = atan2f(playerxy.y - playersoulxy.y, playersoulxy.x - playerxy.x) + 0.08;
			vzbullet.push_back(zbullet);
		}
		else if (playerpower < 32)
		{
			zbullet.angle = atan2f(playerxy.y - playersoulxy.y, playersoulxy.x - playerxy.x) - 0.04;
			vzbullet.push_back(zbullet);

			zbullet.angle = atan2f(playerxy.y - playersoulxy.y, playersoulxy.x - playerxy.x) + 0.04;
			vzbullet.push_back(zbullet);

			zbullet.angle = atan2f(playerxy.y - playersoulxy.y, playersoulxy.x - playerxy.x) - 0.12;
			vzbullet.push_back(zbullet);

			zbullet.angle = atan2f(playerxy.y - playersoulxy.y, playersoulxy.x - playerxy.x) + 0.12;
			vzbullet.push_back(zbullet);
		}
		else
		{
			zbullet.angle = atan2f(playerxy.y - playersoulxy.y, playersoulxy.x - playerxy.x);
			vzbullet.push_back(zbullet);

			zbullet.angle = atan2f(playerxy.y - playersoulxy.y, playersoulxy.x - playerxy.x) - 0.08;
			vzbullet.push_back(zbullet);

			zbullet.angle = atan2f(playerxy.y - playersoulxy.y, playersoulxy.x - playerxy.x) + 0.08;
			vzbullet.push_back(zbullet);

			zbullet.angle = atan2f(playerxy.y - playersoulxy.y, playersoulxy.x - playerxy.x) - 0.16;
			vzbullet.push_back(zbullet);

			zbullet.angle = atan2f(playerxy.y - playersoulxy.y, playersoulxy.x - playerxy.x) + 0.16;
			vzbullet.push_back(zbullet);
		}
		if(playerpower >= 46)
		{
			zbullet.atk = 2;
		}
	}
	shotdelay++;
	if (shotdelay > 2)shotdelay = 0;
}
void mainGame::xbulletfire()
{
	xbullet.atk = zbullet.atk * 10;
	if (vxbullet.size()<5)vxbullet.push_back(xbullet); //화면내에 5개까지
	for (int i = 0; i < vxbullet.size(); i++)
	{
		if (!vxbullet[i].release)
		{
			vxbullet[i].release = true;
			break;
		}
		/*if (vxbullet[i].release)continue;
		vxbullet[i].release = true;
		break;*/
	}
}
void mainGame::cbulletfire()
{
	if (isbomb)
	{
		if (bombcounter == 0)
		{
			cbullet.x = (WINSIZEX - 300) / 2;
			cbullet.y = WINSIZEY;
			vcbullet.push_back(cbullet);
		}
		if (bombcounter == 20)
		{
			cbullet.x = (WINSIZEX - 300) / 2 - 100;
			cbullet.y = WINSIZEY;
			vcbullet.push_back(cbullet);
			cbullet.x = (WINSIZEX - 300) / 2 + 100;
			cbullet.y = WINSIZEY;
			vcbullet.push_back(cbullet);
		}
		if (bombcounter == 40)
		{
			cbullet.x = (WINSIZEX - 300) / 2 - 200;
			cbullet.y = WINSIZEY;
			vcbullet.push_back(cbullet);
			cbullet.x = (WINSIZEX - 300) / 2 + 200;
			cbullet.y = WINSIZEY;
			vcbullet.push_back(cbullet);
		}
		bombcounter++;
		if (bombcounter == 50)
		{
			isbomb = false;
			bombcounter = 0;
		}
	}
}

void mainGame::bulletmove()//탄 움직임
{
	
	//발사탄
	for (int i = 0; i < vbulletcontainer.size(); i++)
	{
		vector<bullet>& bulletcontainer = *vbulletcontainer[i];

		for (int k = 0; k < bulletcontainer.size(); k++)
		{

			bulletcontainer[k].x += cosf(bulletcontainer[k].angle)*bulletcontainer[k].speed;
			bulletcontainer[k].y -= sinf(bulletcontainer[k].angle)*bulletcontainer[k].speed;

			//탄 소멸
			if (bulletcontainer[k].x - bulletcontainer[k].radius < 0)
			{
				bulletcontainer[k].release = false;
			}
			if (bulletcontainer[k].y - bulletcontainer[k].radius < 0)
			{
				bulletcontainer[k].release = false;
			}
			if (bulletcontainer[k].x + bulletcontainer[k].radius > WINSIZEX - 300)
			{
				bulletcontainer[k].release = false;
			}
			if (bulletcontainer[k].y + bulletcontainer[k].radius > WINSIZEY)
			{
				bulletcontainer[k].release = false;
			}

			if (!bulletcontainer[k].release)
			{
				bulletcontainer.erase(bulletcontainer.begin() + k);
				k--;
				continue;
			}
		}
	}
	
	//zx탄 통합됨
	/*
	//Z탄발사
	for (int i = 0; i < vzbullet.size(); i++)
	{

		vzbullet[i].x += cosf(vzbullet[i].angle)*vzbullet[i].speed;
		vzbullet[i].y -= sinf(vzbullet[i].angle)*vzbullet[i].speed;

		//Z탄 소멸
		if (vzbullet[i].x - vzbullet[i].radius < 0)
		{
			vzbullet[i].release = false;
		}
		if (vzbullet[i].y - vzbullet[i].radius < 0)
		{
			vzbullet[i].release = false;
		}
		if (vzbullet[i].x + vzbullet[i].radius > WINSIZEX - 300)
		{
			vzbullet[i].release = false;
		}
		if (vzbullet[i].y + vzbullet[i].radius > WINSIZEY)
		{
			vzbullet[i].release = false;
		}

		if (!vzbullet[i].release)
		{
			vzbullet.erase(vzbullet.begin() + i);
			continue;
		}
	}
	//X탄발사
	for (int i = 0; i < vxbullet.size(); i++)
	{
		vxbullet[i].x += cosf(vxbullet[i].angle)*vxbullet[i].speed;
		vxbullet[i].y -= sinf(vxbullet[i].angle)*vxbullet[i].speed;

		//X탄 소멸
		if (vxbullet[i].x - vxbullet[i].radius < 0)
		{
			vxbullet[i].release = false;
			vixbullet = vxbullet.erase(vixbullet);
		}
		if (vxbullet[i].y - vxbullet[i].radius < 0)
		{
			vxbullet[i].release = false;
			vixbullet = vxbullet.erase(vixbullet);
		}
		if (vxbullet[i].x + vxbullet[i].radius > WINSIZEX - 300)
		{
			vxbullet[i].release = false;
			vixbullet = vxbullet.erase(vixbullet);
		}
		if (vxbullet[i].y + vxbullet[i].radius > WINSIZEY)
		{
			vxbullet[i].release = false;
			vixbullet = vxbullet.erase(vixbullet);
		}
		if (!vxbullet[i].release)
		{
			vxbullet.erase(vxbullet.begin() + i);
			continue;
		}
	}*/

	//c탄발사
	for (int i = 0; i < vcbullet.size(); i++)
	{

		vcbullet[i].x += cosf(vcbullet[i].angle)*vcbullet[i].speed;
		vcbullet[i].y += sinf(vcbullet[i].angle)*vcbullet[i].speed;
		if (vcbullet[i].y + vcbullet[i].radius < 0)
		{
			vcbullet[i].release = false;
		}

		if (!vcbullet[i].release)
		{
			vcbullet.erase(vcbullet.begin() + i);
			i--;
			continue;
		}
	}

	//적 탄
	for (int i = 0; i < vbulletcontainer_b.size(); i++)
	{
		vector<bullet>& bulletcontainer_b = *vbulletcontainer_b[i];

		for (int k = 0; k < bulletcontainer_b.size(); k++)
		{
			while (bulletcontainer_b[k].angle > PI)bulletcontainer_b[k].angle -= PI2;
			while (bulletcontainer_b[k].angle < -PI)bulletcontainer_b[k].angle += PI2;

			if (bulletcontainer_b[k].release)//발사할 경우
			{
				bulletcontainer_b[k].x += cosf(bulletcontainer_b[k].angle)*bulletcontainer_b[k].speed;
				bulletcontainer_b[k].y += sinf(bulletcontainer_b[k].angle)*bulletcontainer_b[k].speed;
			}

			if (bulletcontainer_b[k].x - bulletcontainer_b[k].radius < 0)
			{
				bulletcontainer_b[k].release = false;
			}
			if (bulletcontainer_b[k].y - bulletcontainer_b[k].radius < 0)
			{
				bulletcontainer_b[k].release = false;
			}
			if (bulletcontainer_b[k].x + bulletcontainer_b[k].radius > WINSIZEX - 300)
			{
				bulletcontainer_b[k].release = false;
			}
			if (bulletcontainer_b[k].y + bulletcontainer_b[k].radius > WINSIZEY)
			{
				bulletcontainer_b[k].release = false;
			}
			if (!bulletcontainer_b[k].release)
			{
				bulletcontainer_b.erase(bulletcontainer_b.begin() + k);
				k--;
			}
		}
	
	}

	//적탄 통합
	/*
	//초소형탄 소멸
	for (int i = 0 ; i< vultrasmall_b.size(); i++)
	{
		if (viultrasmall_b->angle > PI)viultrasmall_b->angle -= PI2;
		if (viultrasmall_b->angle < -PI)viultrasmall_b->angle += PI2;
		
		if (viultrasmall_b->x - viultrasmall_b->radius < 0)
		{
			viultrasmall_b->release = false;
		}
		if (viultrasmall_b->y - viultrasmall_b->radius < 0)
		{
			viultrasmall_b->release = false;
		}
		if (viultrasmall_b->x + viultrasmall_b->radius > WINSIZEX - 300)
		{
			viultrasmall_b->release = false;
		}
		if (viultrasmall_b->y + viultrasmall_b->radius > WINSIZEY)
		{
			viultrasmall_b->release = false;
		}
		if(!viultrasmall_b->release)
		{
			vultrasmall_b.erase(viultrasmall_b);
		}
	}

	//소형탄 소멸
	vismall_b = vsmall_b.begin();
	for (vismall_b; vismall_b != vsmall_b.end(); ++vismall_b)
	{
		if (vismall_b->angle > PI)vismall_b->angle -= PI2;
		if (vismall_b->angle < -PI)vismall_b->angle += PI2;

		if (vismall_b->x - vismall_b->radius < 0)
		{
			vismall_b->release = false;
		}
		if (vismall_b->y - vismall_b->radius < 0)
		{
			vismall_b->release = false;
		}
		if (vismall_b->x + vismall_b->radius > WINSIZEX - 300)
		{
			vismall_b->release = false;
		}
		if (vismall_b->y + vismall_b->radius > WINSIZEY)
		{
			vismall_b->release = false;
		}
		if(!vismall_b->release)
		{
			vsmall_b.erase(vismall_b);
			//--vismall_b;
		}

	}

	//중형탄 소멸
	vinormal_b = vnormal_b.begin();
	for (vinormal_b; vinormal_b != vnormal_b.end(); ++vinormal_b)
	{
		if (vinormal_b->angle > PI)vinormal_b->angle -= PI2;
		if (vinormal_b->angle < -PI)vinormal_b->angle += PI2;

		if (vinormal_b->x - vinormal_b->radius < 0)
		{
			vinormal_b->release = false;
		}
		if (vinormal_b->y - vinormal_b->radius < 0)
		{
			vinormal_b->release = false;
		}
		if (vinormal_b->x + vinormal_b->radius > WINSIZEX - 300)
		{
			vinormal_b->release = false;
		}
		if (vinormal_b->y + vinormal_b->radius > WINSIZEY)
		{
			vinormal_b->release = false;
		}
		if (!vinormal_b->release)
		{
			vnormal_b.erase(vinormal_b);
		}
	}

	//대형탄 소멸
	vibig_b = vbig_b.begin();
	for (vibig_b; vibig_b != vbig_b.end(); ++vibig_b)
	{
		if (vibig_b->angle > PI)vibig_b->angle -= PI2;
		if (vibig_b->angle < -PI)vibig_b->angle += PI2;

		if (vibig_b->x - vibig_b->radius < 0)
		{
			vibig_b->release = false;
		}
		if (vibig_b->y - vibig_b->radius < 0)
		{
			vibig_b->release = false;
		}
		if (vibig_b->x + vibig_b->radius > WINSIZEX - 300)
		{
			vibig_b->release = false;
		}
		if (vibig_b->y + vibig_b->radius > WINSIZEY)
		{
			vibig_b->release = false;
		}
		if (!vibig_b->release)
		{
			vbig_b.erase(vibig_b);
		}
	}
	*/

	/*viultrasmall_b = vultrasmall_b.begin();
	for (viultrasmall_b; viultrasmall_b != vultrasmall_b.end(); ++viultrasmall_b)
	{
		if (viultrasmall_b->release)//발사할 경우
		{
			viultrasmall_b->x += cosf(viultrasmall_b->angle)*viultrasmall_b->speed;
			viultrasmall_b->y += sinf(viultrasmall_b->angle)*viultrasmall_b->speed;
		}
	}

	vismall_b = vsmall_b.begin();
	for (vismall_b; vismall_b != vsmall_b.end(); ++vismall_b)
	{
		if (vismall_b->release)//발사할 경우
		{
			vismall_b->x += cosf(vismall_b->angle)*vismall_b->speed;
			vismall_b->y += sinf(vismall_b->angle)*vismall_b->speed;
		}
	}
	vinormal_b = vnormal_b.begin();
	for (vinormal_b; vinormal_b != vnormal_b.end(); ++vinormal_b)
	{
		if (vinormal_b->release)//발사할 경우
		{
			vinormal_b->x += cosf(vinormal_b->angle)*vinormal_b->speed;
			vinormal_b->y += sinf(vinormal_b->angle)*vinormal_b->speed;
		}
	}

	vibig_b = vbig_b.begin();
	for (vibig_b; vibig_b != vbig_b.end(); ++vibig_b)
	{
		if (vibig_b->release)//발사할 경우
		{
			vibig_b->x += cosf(vibig_b->angle)*vibig_b->speed;
			vibig_b->y += sinf(vibig_b->angle)*vibig_b->speed;
		}
	}*/

}

void mainGame::Releasemob()//몹 소멸
{
	for (int i = 0; i < vmobcontainer.size(); i++)
	{
		vector<enemy>& mobcontainer = *vmobcontainer[i];

		for (int k = 0; k < mobcontainer.size(); k++)
		{
			if (mobcontainer[k].x < 0)
			{
				mobcontainer[k].release = false;
			}
			if (mobcontainer[k].y < 0)
			{
				mobcontainer[k].release = false;
			}
			if (mobcontainer[k].x > WINSIZEX - 300)
			{
				mobcontainer[k].release = false;
			}
			if (mobcontainer[k].y > WINSIZEY)
			{
				mobcontainer[k].release = false;
			}
			if (mobcontainer[k].hp <= 0) {
				if (mobcontainer[k].release)
				{
					mobcontainer[k].item.x = mobcontainer[k].x;
					mobcontainer[k].item.y = mobcontainer[k].y;
					mobcontainer[k].item.speed = 5;
					mobcontainer[k].item.release = true;
					vpoint.push_back(mobcontainer[k].item);

					mobcontainer[k].release = false;
					/*point.x = mobcontainer[k].x;
					point.y = mobcontainer[k].y;
					point.itemtype = ITEMTYPE(ITEMPOINT);
					point.speed = 5;
					point.release = true;
					vpoint.push_back(point);

					vimob1->release = false;*/
				}
			}
			if (!mobcontainer[k].release)
			{
				mobcontainer.erase(mobcontainer.begin() + k);
				k--;
			}
		}

	}
	
	/*vimob1 = vmob1.begin();
	for (vimob1; vimob1 != vmob1.end(); ++vimob1)
	{
		if (vimob1->x < 0)
		{
			vimob1->release = false;
		}
		if (vimob1->y < 0)
		{
			vimob1->release = false;
		}
		if (vimob1->x > WINSIZEX - 300)
		{
			vimob1->release = false;
		}
		if (vimob1->y > WINSIZEY)
		{
			vimob1->release = false;
		}
		if (vimob1->hp <= 0) {
			if (vimob1->release)
			{
				point.x = vimob1->x;
				point.y = vimob1->y;
				point.itemtype = ITEMTYPE(ITEMPOINT);
				point.speed = 5;
				point.release = true;
				vpoint.push_back(point);

				vimob1->release = false;
			}
		}
		if (!vimob1->release)
		{
			vmob1.erase(vimob1);
		}
	}

	vimob2 = vmob2.begin();
	for (vimob2; vimob2 != vmob2.end(); ++vimob2)
	{
		if (vimob2->x < 0)
		{
			vimob2->release = false;
		}
		if (vimob2->y < 0)
		{
			vimob2->release = false;
		}
		if (vimob2->x > WINSIZEX - 300)
		{
			vimob2->release = false;
		}
		if (vimob2->y > WINSIZEY)
		{
			vimob2->release = false;
		}
		if (vimob2->hp <= 0) {
			if (vimob2->release)
			{
				point.x = vimob2->x;
				point.y = vimob2->y;
				point.itemtype = ITEMTYPE(ITEMPOWER);
				point.speed = 5;
				point.release = true;
				vpoint.push_back(point);

				vimob2->release = false;
			}
		}
		if (!vimob2->release)
		{
			vmob2.erase(vimob2);
		}
	}
	vimob3 = vmob3.begin();
	for (vimob3; vimob3 != vmob3.end(); ++vimob3)
	{
		if (vimob3->x < 0)
		{
			vimob3->release = false;
		}
		if (vimob3->y < 0)
		{
			vimob3->release = false;
		}
		if (vimob3->x > WINSIZEX - 300)
		{
			vimob3->release = false;
		}
		if (vimob3->y > WINSIZEY)
		{
			vimob3->release = false;
		}
		if (vimob3->hp <= 0) {
			if (vimob3->release)
			{
				point.x = vimob3->x;
				point.y = vimob3->y;
				if (vimob3->color == COLOR(RED)) { point.itemtype = ITEMTYPE(ITEMPOWER); }
				else { point.itemtype = ITEMTYPE(ITEMBOMB); }
				point.speed = 5;
				point.release = true;
				vpoint.push_back(point);

				vimob3->release = false;
			}
		}
		if (!vimob3->release)
		{
			vmob3.erase(vimob3);
		}
	}*/

}

void mainGame::hitmob()
{
	//몹1,Z탄 충돌
	for (int u = 0; u < vmobcontainer.size(); u++)
	{
		vector<enemy>& mobcontainer = *vmobcontainer[u];

		for (int i = 0; i < mobcontainer.size(); i++)
		{
			for (int m = 0; m < vbulletcontainer.size(); m++)
			{
				vector<bullet>& bulletcontainer = *vbulletcontainer[m];

				for (int k = 0; k < bulletcontainer.size(); k++)
				{
					if (getDistance(mobcontainer[i].x, mobcontainer[i].y, bulletcontainer[k].x, bulletcontainer[k].y) <= 16 + bulletcontainer[k].radius&&bulletcontainer[k].release&&mobcontainer[i].release)
					{
						mobcontainer[i].hp -= bulletcontainer[k].atk;
						score++;
						bulletcontainer[k].release = false;
						bulletcontainer.erase(bulletcontainer.begin() + k);
						k--;
					}
				}
			}
		}
	}
	
	/*vimob1 = vmob1.begin();
	for (vimob1; vimob1 != vmob1.end(); ++vimob1)
	{
		vizbullet = vzbullet.begin();
		for (vizbullet; vizbullet != vzbullet.end(); ++vizbullet)
		{
			if (getDistance(vimob1->x, vimob1->y, vizbullet->x, vizbullet->y) <= 16 + vizbullet->radius&&vizbullet->release&&vimob1->release)
			{
				vimob1->hp -= atk;
				score++;
				vizbullet->release = false;
				vizbullet = vzbullet.erase(vizbullet);
			}
		}
		vixbullet = vxbullet.begin();
		for (vixbullet; vixbullet != vxbullet.end(); ++vixbullet)
		{
			if (getDistance(vimob1->x, vimob1->y, vixbullet->x, vixbullet->y) <= 16 + vixbullet->radius&&vixbullet->release&&vimob1->release)
			{
				vimob1->hp -= atk*3;
				score+=5;
				vixbullet->release = false;
				vixbullet = vxbullet.erase(vixbullet);
			}
		}
	}

	vimob2 = vmob2.begin();
	for (vimob2; vimob2 != vmob2.end(); ++vimob2)
	{
		vizbullet = vzbullet.begin();
		for (vizbullet; vizbullet != vzbullet.end(); ++vizbullet)
		{
			if (getDistance(vimob2->x, vimob2->y, vizbullet->x, vizbullet->y) <= 16 + vizbullet->radius&&vizbullet->release&&vimob2->release)
			{
				vimob2->hp -= atk;
				score++;
				vizbullet->release = false;
				vizbullet = vzbullet.erase(vizbullet);
			}
		}
		vixbullet = vxbullet.begin();
		for (vixbullet; vixbullet != vxbullet.end(); ++vixbullet)
		{
			if (getDistance(vimob2->x, vimob2->y, vixbullet->x, vixbullet->y) <= 16 + vixbullet->radius&&vixbullet->release&&vimob2->release)
			{
				vimob2->hp -= atk*3;
				score+=5;
				vixbullet->release = false;
				vixbullet = vxbullet.erase(vixbullet);
			}
		}
	}
	vimob3 = vmob3.begin();
	for (vimob3; vimob3 != vmob3.end(); ++vimob3)
	{
		vizbullet = vzbullet.begin();
		for (vizbullet; vizbullet != vzbullet.end(); ++vizbullet)
		{
			if (getDistance(vimob3->x, vimob3->y, vizbullet->x, vizbullet->y) <= 16 + vizbullet->radius&&vizbullet->release&&vimob3->release)
			{
				vimob3->hp -= atk;
				score++;
				vizbullet->release = false;
				vizbullet = vzbullet.erase(vizbullet);
			}
		}
		vixbullet = vxbullet.begin();
		for (vixbullet; vixbullet != vxbullet.end(); ++vixbullet)
		{
			if (getDistance(vimob3->x, vimob3->y, vixbullet->x, vixbullet->y) <= 16 + vixbullet->radius&&vixbullet->release&&vimob3->release)
			{
				vimob3->hp -= atk*3;
				score+=5;
				vixbullet->release = false;
				vixbullet = vxbullet.erase(vixbullet);
			}
		}
	}
	*/

	//boss collision
	for (int i = 0; i < vzbullet.size(); i++)
	{
		if (getDistance(st1b.x, st1b.y, vzbullet[i].x, vzbullet[i].y) <= 160 + vzbullet[i].radius&&vzbullet[i].release&&st1b.release)
		{
			st1b.hp -= zbullet.atk;
			score += 1;
			vzbullet[i].release = false;
			vzbullet.erase(vzbullet.begin() + i);
			i--;
		}
	}

	for (int i = 0; i < vxbullet.size(); i++)
	{
		if (getDistance(st1b.x, st1b.y, vxbullet[i].x, vxbullet[i].y) <= 160 + vxbullet[i].radius&&vxbullet[i].release&&st1b.release)
		{
			st1b.hp -= xbullet.atk;
			score += 5;
			vxbullet[i].release = false;
			vxbullet.erase(vxbullet.begin() + i);
			i--;
		}
	}
}

void mainGame::dropitem()
{
	for (int i=0;i<vpoint.size();i++)
	{
		vpoint[i].y -= vpoint[i].speed;
		if (vpoint[i].speed > -5)
		{
			vpoint[i].speed -= grav;
		}
		if (getDistance(vpoint[i].x, vpoint[i].y, playerxy.x, playerxy.y) < 50)//거리50이내에 들어오면
		{
			if (vpoint[i].release)
			{
				if (vpoint[i].itemtype == ITEMTYPE(ITEMPOINT))
				{
					amount_pointitem++;
					score += 20;
				}
				if (vpoint[i].itemtype == ITEMTYPE(ITEMPOWER))
				{
					if (playerpower < 46)
					{
						playerpower++;
					}
					else
					{
						amount_pointitem++;
						score += 20;
					}
				}
				if (vpoint[i].itemtype == ITEMTYPE(ITEMHP))
				{
					playerhp++;
				}
				if (vpoint[i].itemtype == ITEMTYPE(ITEMBOMB))
				{
					playerbomb++;
				}
			}
			vpoint[i].release = false;
		}
		if (vpoint[i].y > WINSIZEY)
		{
			vpoint[i].release = false;
		}
		if (!vpoint[i].release)
		{
			vpoint.erase(vpoint.begin() + i);
			i--;
		}
	}
	/*vipoint = vpoint.begin();
	for (vipoint; vipoint != vpoint.end();)
	{
		vipoint->y -= vipoint->speed;
		if (vipoint->speed > -5)
		{
			vipoint->speed -= grav;
		}
		if (getDistance(vipoint->x, vipoint->y, playerxy.x, playerxy.y) < 50)//거리50이내에 들어오면
		{
			if (vipoint->release)
			{
				if (vipoint->itemtype == ITEMTYPE(ITEMPOINT))
				{
					amount_pointitem++;
					score += 20;
				}
				if (vipoint->itemtype == ITEMTYPE(ITEMPOWER))
				{
					if (playerpower < 46)
					{
						playerpower++;
					}
					else
					{
						amount_pointitem++;
						score += 20;
					}
				}
				if (vipoint->itemtype == ITEMTYPE(ITEMHP))
				{
					playerhp++;
				}
				if (vipoint->itemtype == ITEMTYPE(ITEMBOMB))
				{
					playerbomb++;
				}
			}
			vipoint->release = false;
		}
		if (vipoint->y > WINSIZEY)
		{
			vipoint->release = false;
		}
		if (!vipoint->release)
		{
			vpoint.erase(vipoint);
		}
		else ++vipoint;
	}*/
}

void mainGame::collisionplayer()//탄환과 플레이어간의 상호작용
{
	viultrasmall_b = vultrasmall_b.begin();
	vismall_b = vsmall_b.begin();
	vinormal_b = vnormal_b.begin();
	vibig_b = vbig_b.begin();
	for (viultrasmall_b; viultrasmall_b != vultrasmall_b.end(); ++viultrasmall_b)
	{
		if (getDistance(viultrasmall_b->x, viultrasmall_b->y, playerxy.x, playerxy.y) < 30 && !viultrasmall_b->isgraze)
		{
			amount_graze++;
			score += 10;
			viultrasmall_b->isgraze = true;
		}
		if (getDistance(viultrasmall_b->x, viultrasmall_b->y, playerxy.x, playerxy.y) < 3 + viultrasmall_b->radius && !isbomb && !isrespawn&&viultrasmall_b->release)
		{
			ishitted = true;
			viultrasmall_b->release = false;
		}
	}
	for (vismall_b; vismall_b != vsmall_b.end(); ++vismall_b)
	{
		if (getDistance(vismall_b->x, vismall_b->y, playerxy.x, playerxy.y) < 30 && !vismall_b->isgraze)
		{
			amount_graze++;
			score += 10;
			vismall_b->isgraze = true;
		}
		if (getDistance(vismall_b->x, vismall_b->y, playerxy.x, playerxy.y) < 3 + vismall_b->radius && !isbomb && !isrespawn&&vismall_b->release)
		{
			ishitted = true;
			vismall_b->release = false;
		}
	}
	for (vinormal_b; vinormal_b != vnormal_b.end(); ++vinormal_b)
	{
		if (getDistance(vinormal_b->x, vinormal_b->y, playerxy.x, playerxy.y) < 30 && !vinormal_b->isgraze)
		{
			amount_graze++;
			score += 10;
			vinormal_b->isgraze = true;
		}
		if (getDistance(vinormal_b->x, vinormal_b->y, playerxy.x, playerxy.y) < 3 + vinormal_b->radius && !isbomb && !isrespawn&&vinormal_b->release)
		{
			ishitted = true;
			vinormal_b->release = false;
		}
	}
	for (vibig_b; vibig_b != vbig_b.end(); ++vibig_b)
	{
		if (getDistance(vibig_b->x, vibig_b->y, playerxy.x, playerxy.y) < 30 && !vibig_b->isgraze)
		{
			amount_graze++;
			score += 10;
			vibig_b->isgraze = true;
		}
		if (getDistance(vibig_b->x, vibig_b->y, playerxy.x, playerxy.y) < 3 + vibig_b->radius && !isbomb && !isrespawn&&vibig_b->release)
		{
			ishitted = true;
			vibig_b->release = false;
		}
	}
	if (ishitted)
	{
		resurrect_bombcounter++;
		if (resurrect_bombcounter == 10)
		{
			playerhp--;
			resurrect_bombcounter = 0;
			ishitted = false;
			isrespawn = true;
			playerxy.x = (WINSIZEX - 300) / 2;
			playerxy.y = WINSIZEY - 74;
		}
		if (isbomb)
		{
			resurrect_bombcounter = 0;
			ishitted = false;
		}
	}
	if (isrespawn)
	{
		respawn++;
		if (respawn == 50) { isrespawn = false; }
	}
	if (!isrespawn)respawn = 0;

	if (playerhp < 0)
	{
		playerhpzero = true;
	}
}

void mainGame::cbulletCanDeleteEbullet()
{
	vicbullet = vcbullet.begin();
	for(vicbullet; vicbullet!=vcbullet.end(); ++vicbullet)
	{
		viultrasmall_b = vultrasmall_b.begin();
		for (viultrasmall_b; viultrasmall_b != vultrasmall_b.end(); ++viultrasmall_b)
		{
			if (getDistance(vicbullet->x, vicbullet->y, viultrasmall_b->x, viultrasmall_b->y) <= vicbullet->radius + viultrasmall_b->radius)
			{
				score++;
				viultrasmall_b->release = false;
			}
		}
		vismall_b = vsmall_b.begin();
		for (vismall_b; vismall_b != vsmall_b.end(); ++vismall_b)
		{
			if (getDistance(vicbullet->x, vicbullet->y, vismall_b->x, vismall_b->y) <= vicbullet->radius + vismall_b->radius)
			{
				score++;
				vismall_b->release = false;
			}
		}
		vinormal_b = vnormal_b.begin();
		for (vinormal_b; vinormal_b != vnormal_b.end(); ++vinormal_b)
		{
			if (getDistance(vicbullet->x, vicbullet->y, vinormal_b->x, vinormal_b->y) <= vicbullet->radius + vinormal_b->radius)
			{
				score++;
				vinormal_b->release = false;
			}
		}
		vibig_b = vbig_b.begin();
		for (vibig_b; vibig_b != vbig_b.end(); ++vibig_b)
		{
			if (getDistance(vicbullet->x, vicbullet->y, vibig_b->x, vibig_b->y) <= vicbullet->radius + vibig_b->radius)
			{
				score++;
				vibig_b->release = false;
			}
		}
	}
}

void mainGame::mobmove()
{
	vimob1 = vmob1.begin();
	for (vimob1; vimob1 != vmob1.end(); ++vimob1)
	{
		vimob1->x += cosf(vimob1->angle)*vimob1->speed;
		vimob1->y += sinf(vimob1->angle)*vimob1->speed;
	}

	vimob2 = vmob2.begin();
	for (vimob2; vimob2 != vmob2.end(); ++vimob2)
	{
		vimob2->x += cosf(vimob2->angle)*vimob2->speed;
		vimob2->y += sinf(vimob2->angle)*vimob2->speed;
	}

	vimob3 = vmob3.begin();
	for (vimob3; vimob3 != vmob3.end(); ++vimob3)
	{
		vimob3->x += cosf(vimob3->angle)*vimob3->speed;
		vimob3->y += sinf(vimob3->angle)*vimob3->speed;
	}
}

void mainGame::stage1_1()
{
	/*PI=180도
	PI/180=1도
	*/
	count++;
	for (int q = 0; q < 10; q++)
	{
		if (count == 100 + 10 * q)
		{
			mob1.x = (WINSIZEX - 300) / 2 - 100;
			mob1.y = 50;
			mob1.hp = 2;
			mob1.speed = 5;
			mob1.enemycount = 0;
			mob1.angle = PI * 110 / 180;
			mob1.release = true;
			mob1.color = BLUE;
			vmob1.push_back(mob1);
		}

		if (count == 250 + 10 * q)
		{
			mob1.x = (WINSIZEX - 300) / 2 + 100;
			mob1.y = 50;
			mob1.hp = 2;
			mob1.speed = 5;
			mob1.enemycount = 0;
			mob1.angle = PI * 70 / 180;
			mob1.release = true;
			mob1.color = BLUE;
			vmob1.push_back(mob1);
		}

		if (count == 400 + 10 * q)
		{
			if (q < 9)
			{
				mob1.x = (WINSIZEX - 300) / 2 + 200;
				mob1.y = 50;
				mob1.hp = 2;
				mob1.speed = 4;
				mob1.enemycount = 0;
				mob1.angle = PI * 90 / 180;
				mob1.release = true;
				mob1.color = RED;
				vmob1.push_back(mob1);
				mob1.x = (WINSIZEX - 300) / 2 - 200;
				vmob1.push_back(mob1);
			}
			if (q == 9)
			{
				mob2.x = (WINSIZEX - 300) / 2 + 200;
				mob2.y = 50;
				mob2.hp = 2;
				mob2.speed = 4;
				mob2.enemycount = 0;
				mob2.angle = PI * 90 / 180;
				mob2.release = true;
				mob2.color = RED;
				vmob2.push_back(mob2);
				mob2.x = (WINSIZEX - 300) / 2 - 200;
				vmob2.push_back(mob2);
			}
		}
	}
	
	vimob1 = vmob1.begin();
	//mob1 움직임
	for (vimob1; vimob1 != vmob1.end(); ++vimob1)
	{
		vimob1->enemycount++;
		if (vimob1->enemycount == 50&&vimob1->release)
		{
			vimob1->speed = 4;
			vimob1->angle = (vimob1->angle - PI / 2)*-4 + PI / 2;

			ultrasmall_b.angle = atan2f(playerxy.y - vimob1->y, playerxy.x - vimob1->x);
			ultrasmall_b.x = vimob1->x;
			ultrasmall_b.y = vimob1->y;
			ultrasmall_b.speed = 5;
			ultrasmall_b.release = true;
			vultrasmall_b.push_back(ultrasmall_b);
			if (difficulty > DIFF(EASY))
			{
				ultrasmall_b.x = vimob1->x;
				ultrasmall_b.y = vimob1->y;
				ultrasmall_b.angle = atan2f(playerxy.y - vimob1->y, playerxy.x - vimob1->x) - 0.2;
				vultrasmall_b.push_back(ultrasmall_b);
				ultrasmall_b.x = vimob1->x;
				ultrasmall_b.y = vimob1->y;
				ultrasmall_b.angle = atan2f(playerxy.y - vimob1->y, playerxy.x - vimob1->x) + 0.2;
				vultrasmall_b.push_back(ultrasmall_b);
			}
		}
	}

	vimob2 = vmob2.begin();
	for (vimob2; vimob2 != vmob2.end(); ++vimob2)
	{
		vimob2->enemycount++;
		if (vimob2->enemycount == 50 && vimob2->release)
		{
			ultrasmall_b.angle = atan2f(playerxy.y - vimob2->y, playerxy.x - vimob2->x);
			ultrasmall_b.x = vimob2->x;
			ultrasmall_b.y = vimob2->y;
			ultrasmall_b.speed = 5;
			ultrasmall_b.release = true;
			vultrasmall_b.push_back(ultrasmall_b);
			if (difficulty > DIFF(EASY))
			{
				ultrasmall_b.x = vimob2->x;
				ultrasmall_b.y = vimob2->y;
				ultrasmall_b.angle = atan2f(playerxy.y - vimob2->y, playerxy.x - vimob2->x) - 0.2;
				vultrasmall_b.push_back(ultrasmall_b);
				ultrasmall_b.x = vimob2->x;
				ultrasmall_b.y = vimob2->y;
				ultrasmall_b.angle = atan2f(playerxy.y - vimob2->y, playerxy.x - vimob2->x) + 0.2;
				vultrasmall_b.push_back(ultrasmall_b);
			}
		}
	}
	
	if (count == 600)
	{
		stage[1] = 2;
		count = 0;
	}

}

void mainGame::stage1_2()
{
	count++;
	for (int q = 0; q < 5; q++)
	{
		if (count == 100 + 20 * q)
		{
			mob2.x = 50;
			mob2.y = 150;
			mob2.hp = 2;
			mob2.speed = 10;
			mob2.enemycount = 0;
			mob2.angle = 0;
			mob2.release = true;
			mob2.color = GREEN;
			vmob2.push_back(mob2);
		}

		if (count == 250 + 20 * q)
		{
			mob2.x = (WINSIZEX - 300) - 50;
			mob2.y = 180;
			mob2.hp = 2;
			mob2.speed = 10;
			mob2.enemycount = 0;
			mob2.angle = PI;
			mob2.release = true;
			mob2.color = GREEN;
			vmob2.push_back(mob2);
		}

		if (count == 500 + 30 * q)
		{
			mob2.x = (WINSIZEX - 300) / 2 - 200 + q * 100;
			mob2.y = 50;
			mob2.hp = 5;
			mob2.speed = 5;
			mob2.enemycount = 0;
			mob2.angle = PI / 2;
			mob2.release = true;
			mob2.color = YELLOW;
			vmob2.push_back(mob2);
		}

		if (count == 650 + 30 * q)
		{
			mob2.x = (WINSIZEX - 300) / 2 + 200 - q * 100;
			mob2.y = 50;
			mob2.hp = 5;
			mob2.speed = 5;
			mob2.enemycount = 0;
			mob2.angle = PI / 2;
			mob2.release = true;
			mob2.color = YELLOW;
			vmob2.push_back(mob2);
		}
		
	}
	
	vimob2 = vmob2.begin();
	for (vimob2; vimob2 != vmob2.end(); ++vimob2)
	{
		vimob2->enemycount++;
		if (count < 500)
		{
			if (vimob2->enemycount == 40 && vimob2->release)
			{
				small_b.angle = atan2f(playerxy.y - vimob2->y, playerxy.x - vimob2->x);
				small_b.x = vimob2->x;
				small_b.y = vimob2->y;
				small_b.speed = 5;
				small_b.release = true;
				vsmall_b.push_back(small_b);
				small_b.angle = atan2f(playerxy.y - vimob2->y, playerxy.x - vimob2->x) - 0.2;
				vsmall_b.push_back(small_b);
				small_b.angle = atan2f(playerxy.y - vimob2->y, playerxy.x - vimob2->x) + 0.2;
				vsmall_b.push_back(small_b);
				if (difficulty > DIFF(EASY))
				{
					small_b.angle = atan2f(playerxy.y - vimob2->y, playerxy.x - vimob2->x) - 0.4;
					vsmall_b.push_back(small_b);
					small_b.angle = atan2f(playerxy.y - vimob2->y, playerxy.x - vimob2->x) + 0.4;
					vsmall_b.push_back(small_b);
				}
			}
		}
		if (count >= 500)
		{
			if (vimob2->enemycount == 40 && vimob2->release)
			{
				normal_b.angle = atan2f(playerxy.y - vimob2->y, playerxy.x - vimob2->x);
				normal_b.x = vimob2->x;
				normal_b.y = vimob2->y;
				normal_b.speed = 5;
				normal_b.release = true;
				vnormal_b.push_back(normal_b);
				normal_b.angle = atan2f(playerxy.y - vimob2->y, playerxy.x - vimob2->x) - 0.3;
				vnormal_b.push_back(normal_b);
				normal_b.angle = atan2f(playerxy.y - vimob2->y, playerxy.x - vimob2->x) + 0.3;
				vnormal_b.push_back(normal_b);
				if (difficulty > DIFF(EASY))
				{
					normal_b.angle = atan2f(playerxy.y - vimob2->y, playerxy.x - vimob2->x) - 0.15;
					vnormal_b.push_back(normal_b);
					normal_b.angle = atan2f(playerxy.y - vimob2->y, playerxy.x - vimob2->x) + 0.15;
					vnormal_b.push_back(normal_b);
					normal_b.angle = atan2f(playerxy.y - vimob2->y, playerxy.x - vimob2->x) - 0.45;
					vnormal_b.push_back(normal_b);
					normal_b.angle = atan2f(playerxy.y - vimob2->y, playerxy.x - vimob2->x) + 0.45;
					vnormal_b.push_back(normal_b);
				}
			}
			if (vimob2->enemycount > 40)
			{
				if (vimob2->angle > 0.3 - PI / 2)
				{
					vimob2->angle -= 0.3;
				}
			}
		}
	}
	if (count == 800)
	{
		stage[1] = 3;
		count = 0;
	}
}

void mainGame::stage1_3()
{
	count++;
	if (count < 100 && st1b.spell == 2)
	{
		st1b.x = (WINSIZEX - 300) / 2;
		st1b.y = 50 + count;
		st1b.angle = PI / 2;
		st1b.hp = 500;
		st1b.release = true;
	}
	if (count == 100 && st1b.spell == 2)
	{
		st1b.x = (WINSIZEX - 300) / 2;
		st1b.y = 150;
		st1b.angle = PI / 2;
		st1b.hp = 500;
		st1b.release = true;
		st1b.spell = 1;
		count = 0;
	}

	if (st1b.spell == 1)
	{
		if (count % 20 == 0 && count % 120 != 0)
		{
			big_b.angle = atan2f(playerxy.y - st1b.y, playerxy.x - st1b.x);
			big_b.x = st1b.x;
			big_b.y = st1b.y;
			big_b.speed = 6;
			big_b.release = true;
			vbig_b.push_back(big_b);
			big_b.angle = atan2f(playerxy.y - st1b.y, playerxy.x - st1b.x) + 0.3;
			vbig_b.push_back(big_b);
			big_b.angle = atan2f(playerxy.y - st1b.y, playerxy.x - st1b.x) - 0.3;
			vbig_b.push_back(big_b);
			big_b.angle = atan2f(playerxy.y - st1b.y, playerxy.x - st1b.x) + 0.6;
			vbig_b.push_back(big_b);
			big_b.angle = atan2f(playerxy.y - st1b.y, playerxy.x - st1b.x) - 0.6;
			vbig_b.push_back(big_b);
			if (difficulty > DIFF(EASY))
			{
				big_b.angle = atan2f(playerxy.y - st1b.y, playerxy.x - st1b.x) + 0.15;
				vbig_b.push_back(big_b);
				big_b.angle = atan2f(playerxy.y - st1b.y, playerxy.x - st1b.x) - 0.15;
				vbig_b.push_back(big_b);
				big_b.angle = atan2f(playerxy.y - st1b.y, playerxy.x - st1b.x) + 0.45;
				vbig_b.push_back(big_b);
				big_b.angle = atan2f(playerxy.y - st1b.y, playerxy.x - st1b.x) - 0.45;
				vbig_b.push_back(big_b);
			}
		}
		if (count % 40 == 10)
		{
			mob2.angle = PI;
			mob2.x = st1b.x;
			mob2.y = st1b.y;
			mob2.color = BLUE;
			mob2.hp = 1;
			mob2.speed = 2;
			mob2.release = true;
			vmob2.push_back(mob2);
			mob2.angle = 0;
			vmob2.push_back(mob2);

			vimob2 = vmob2.begin();
			for (vimob2; vimob2 != vmob2.end(); ++vimob2)
			{
				if (vimob2->enemycount % 60 == 0 && vimob2->release)
				{
					normal_b.angle = atan2f(playerxy.y - vimob2->y, playerxy.x - vimob2->x);
					normal_b.x = vimob2->x;
					normal_b.y = vimob2->y;
					normal_b.speed = 12;
					normal_b.release = true;
					vnormal_b.push_back(normal_b);
					if (difficulty > DIFF(EASY)) 
					{
						normal_b.speed = 9;
						vnormal_b.push_back(normal_b);
						normal_b.speed = 6;
						vnormal_b.push_back(normal_b);
					}
				}
			}
		}
		if (st1b.hp < 0 || count>9999)
		{
			st1b.spell = 0;
			st1b.hp = 500;
			count = 0;
		}
	}
	if (st1b.spell == 0)
	{
		if (count % 20 == 0)
		{
			st1b.x = RND->getFromIntTo(50, 650);
			st1b.y = RND->getFromIntTo(50, 100);
		}
		if (count % 6 == 0)
		{
			small_b.angle = 0 + count * 0.01;
			small_b.x = st1b.x;
			small_b.y = st1b.y;
			small_b.speed = 8;
			small_b.release = true;
			vsmall_b.push_back(small_b);
			small_b.angle = PI / 2 + count * 0.01;
			vsmall_b.push_back(small_b);
			small_b.angle = PI + count * 0.01;
			vsmall_b.push_back(small_b);
			small_b.angle = -PI / 2 + count * 0.01;
			vsmall_b.push_back(small_b);
			if (difficulty > DIFF(EASY))
			{
				small_b.speed = 12;
				small_b.angle = 0 + count * 0.01;
				vsmall_b.push_back(small_b);
				small_b.angle = PI / 2 + count * 0.01;
				vsmall_b.push_back(small_b);
				small_b.angle = PI + count * 0.01;
				vsmall_b.push_back(small_b);
				small_b.angle = -PI / 2 + count * 0.01;
				vsmall_b.push_back(small_b);
			}
		}
		if (count % 20 == 0)
		{
			normal_b.angle = atan2f(playerxy.y - st1b.y, playerxy.x - st1b.x);
			normal_b.x = st1b.x;
			normal_b.y = st1b.y;
			normal_b.speed = 6;
			normal_b.release = true;
			vnormal_b.push_back(normal_b);
			if (difficulty > DIFF(EASY))
			{
				normal_b.angle = atan2f(playerxy.y - st1b.y, playerxy.x - st1b.x)+0.04;
				vnormal_b.push_back(normal_b);
				normal_b.angle = atan2f(playerxy.y - st1b.y, playerxy.x - st1b.x)-0.04;
				vnormal_b.push_back(normal_b);
			}
		}
		if (st1b.hp < 0 || count>9999)
		{
			st1b.release = false;
			stage[0] = 2;
			stage[1] = 1;
			stagepassflag = true;
			count = 0;
		}
	}
}
