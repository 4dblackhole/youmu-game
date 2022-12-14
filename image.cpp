#include "stdafx.h"
#include "image.h"

//컴파일러 지시기 나는 마소이미지(32비트) 라이브러리를 사용하겠다
#pragma comment(lib, "msimg32.lib")

//멤버 이니셜라이즈
image::image()
	: _imageInfo(NULL),
	_fileName(NULL),
	_trans(false),
	_transColor(RGB(0, 0, 0))
{
}
image::~image()
{
}

//빈 비트맵 이미지 초기화
HRESULT image::init(int width, int height)
{
	//이미지 정보가 뭔가있다면 해제해줘라
	if (_imageInfo != NULL) release();

	//DC영역을 사용하고싶을때는 가져온다
	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);		//빈 DC영역 생성
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height); //빈 비트맵 이미지 생성
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;		//이미지 크기 값 대입 받는다
	_imageInfo->height = height;

	_fileName = NULL;

	_trans = FALSE;
	_transColor = RGB(0, 0, 0);

	//비트맵이 생성이 되지않았다면
	if (_imageInfo->hBit == NULL)
	{
		//메모리 해제 시키고
		release();
		return E_FAIL;	//실패했다고 알려라
	}

	//가져온 DC를 해제
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

//파일로부터 이미지 초기화
HRESULT image::init(const char* fileName, int width, int height,
	BOOL trans, COLORREF transColor)
{
	//이미지 정보가 뭔가있다면 해제해줘라
	if (_imageInfo != NULL) release();

	//DC영역을 사용하고싶을때는 가져온다
	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);		//빈 DC영역 생성
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;		//이미지 크기 값 대입 받는다
	_imageInfo->height = height;

	//파일 길이를 알아온다
	int len = strlen(fileName);


	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	//비트맵이 생성이 되지않았다면
	if (_imageInfo->hBit == NULL)
	{
		//메모리 해제 시키고
		release();
		return E_FAIL;	//실패했다고 알려라
	}

	//가져온 DC를 해제
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

//*******************************************************************************************추가
//파일로부터 이미지 초기화           처음 시작 좌표      가로       세로
HRESULT image::init(const char* fileName, float x, float y, int width, int height,
	BOOL trans, COLORREF transColor)
{
	//이미지 정보가 뭔가있다면 해제해줘라
	if (_imageInfo != NULL) release();

	//DC영역을 사용하고싶을때는 가져온다
	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);		//빈 DC영역 생성
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;		//이미지 크기 값 대입 받는다
	_imageInfo->height = height;


	//파일 길이를 알아온다
	int len = strlen(fileName);


	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	//비트맵이 생성이 되지않았다면
	if (_imageInfo->hBit == NULL)
	{
		//메모리 해제 시키고
		release();
		return E_FAIL;	//실패했다고 알려라
	}

	//가져온 DC를 해제
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}
//***********************************************************************************추가

HRESULT image::init(const char * fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	//이미지 정보가 뭔가있다면 해제해줘라
	if (_imageInfo != NULL) release();

	//DC영역을 사용하고싶을때는 가져온다
	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);		//빈 DC영역 생성
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;		//이미지 크기 값 대입 받는다
	_imageInfo->height = height;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;

	//파일 길이를 알아온다
	int len = strlen(fileName);


	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	//비트맵이 생성이 되지않았다면
	if (_imageInfo->hBit == NULL)
	{
		//메모리 해제 시키고
		release();
		return E_FAIL;	//실패했다고 알려라
	}

	//가져온 DC를 해제
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	//이미지 정보가 뭔가있다면 해제해줘라
	if (_imageInfo != NULL) release();

	//DC영역을 사용하고싶을때는 가져온다
	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);		//빈 DC영역 생성
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;		//이미지 크기 값 대입 받는다
	_imageInfo->height = height;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;

	//파일 길이를 알아온다
	int len = strlen(fileName);


	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	//비트맵이 생성이 되지않았다면
	if (_imageInfo->hBit == NULL)
	{
		//메모리 해제 시키고
		release();
		return E_FAIL;	//실패했다고 알려라
	}

	//가져온 DC를 해제
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}
//***********************************************추가

//이미지 릴리즈
void image::release(void)
{
	//이미지정보가 있다면
	if (_imageInfo)
	{
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);

		_trans = false;
		_transColor = RGB(0, 0, 0);
	}
}


//혹시 트랜스처리를 다른 픽셀값으로 바꿔야한다면
void image::setTransColor(BOOL trans, COLORREF transColor)
{
	_trans = trans;
	_transColor = transColor;
}

void image::render(HDC hdc)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,				//복사될 영역의 DC
			_imageInfo->x,		//복사될 좌표 X
			_imageInfo->y,		//복사될 좌표 Y
			_imageInfo->width,	//복사될 크기(가로)
			_imageInfo->height,	//복사될 크기(세로)
			_imageInfo->hMemDC,	//복사해올 DC
			0, 0,				//복사해올 좌표X,Y
			_imageInfo->width,	//복사해올 크기
			_imageInfo->height,	//복사해올 크기
			_transColor);		//복사해올때 어떤 컬러를 빼고 가져올꺼냐
	}
	else
	{
		//백버퍼에 있는 것을 DC영역으로 고속복사해주는 함수
		BitBlt(hdc,
			_imageInfo->x,
			_imageInfo->y,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0, SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,				//복사될 영역의 DC
			destX,				//복사될 좌표 X
			destY,				//복사될 좌표 Y
			_imageInfo->width,	//복사될 크기(가로)
			_imageInfo->height,	//복사될 크기(세로)
			_imageInfo->hMemDC,	//복사해올 DC
			0, 0,				//복사해올 좌표X,Y
			_imageInfo->width,	//복사해올 크기
			_imageInfo->height,	//복사해올 크기
			_transColor);		//복사해올때 어떤 컬러를 빼고 가져올꺼냐
	}
	else
	{
		//백버퍼에 있는 것을 DC영역으로 고속복사해주는 함수
		BitBlt(hdc, destX, destY,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0, SRCCOPY);
	}
}


//렌더링함수 뿌릴DC , 뿌릴곳X(Left), 뿌릴곳Y(top)
void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					//복사될 영역DC
			destX,					//복사될 좌표 X
			destY,					//복사될 좌표 Y
			sourWidth,				//복사될 가로크기
			sourHeight,				//복사될 세로크기
			_imageInfo->hMemDC,
			sourX, sourY,			//복사해올 좌표
			sourWidth,				//복사해올 가로크기
			sourHeight,				//복사해올 세로크기
			_transColor);
	}
	else
	{
		BitBlt(hdc, destX, destY,
			sourWidth,
			sourHeight,
			_imageInfo->hMemDC,
			sourX, sourY,
			SRCCOPY);
	}
}

void image::loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY)
{
	//화면 밖으로 나가면 보정해준다
	//  -200					600				     -200   % 600
	if (offSetX < 0)
	{
		offSetX = _imageInfo->width + (offSetX % _imageInfo->width);
	}
	if (offSetY < 0)
	{
		offSetY = _imageInfo->height + (offSetY % _imageInfo->height);
	}
	//오프셋 영역을 받아올 변수
	int sourWidth;
	int sourHeight;
	//그려주는 영역
	RECT rcDest;
	RECT rcSour;

	//그려주는 영역을 잡아준다
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawAreaX;      //너비
	int drawAreaH = drawArea->bottom - drawAreaY;     //높이

	//Y축 부터
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		rcSour.top = (y + offSetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;

		sourHeight = rcSour.bottom - rcSour.top;

		//그려주는 영역의 높이보다 y축이 크면
		if (y + sourHeight > drawAreaH)
		{
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//화면밖으로 나간영역만큼 뿌려줄 위치에 산정한다
		//뿌려주는 영역
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//x축
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			rcSour.left = (x + offSetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;

			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			render(hdc, rcDest.left, rcDest.top,//뿌려줄 위치 X, Y
				rcSour.left, rcSour.top,		//뿌려올 위치
				rcSour.right - rcSour.left,		//가로크기
				rcSour.bottom - rcSour.top);	//세로크기
		}
	}
}

void image::frameRender(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,								//복사될 영역의 DC
			destX,								//복사될 좌표 X
			destY,								//복사될 좌표 Y
			_imageInfo->frameWidth,				//복사될 크기(가로)
			_imageInfo->frameHeight,			//복사될 크기(세로)
			_imageInfo->hMemDC,					//복사해올 DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,	//복사해올 좌표X,Y
			_imageInfo->frameWidth,				//복사해올 크기
			_imageInfo->frameHeight,			//복사해올 크기
			_transColor);						//복사해올때 어떤 컬러를 빼고 가져올꺼냐
	}
	else
	{
		//백버퍼에 있는 것을 DC영역으로 고속복사해주는 함수
		BitBlt(hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}
}

void image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (_trans)
	{
		GdiTransparentBlt(
			hdc,								//복사될 영역의 DC
			destX,								//복사될 좌표 X
			destY,								//복사될 좌표 Y
			_imageInfo->frameWidth,				//복사될 크기(가로)
			_imageInfo->frameHeight,			//복사될 크기(세로)
			_imageInfo->hMemDC,					//복사해올 DC
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,	//복사해올 좌표X,Y
			_imageInfo->frameWidth,				//복사해올 크기
			_imageInfo->frameHeight,			//복사해올 크기
			_transColor);						//복사해올때 어떤 컬러를 빼고 가져올꺼냐
	}
	else
	{
		//백버퍼에 있는 것을 DC영역으로 고속복사해주는 함수
		BitBlt(hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}
}

