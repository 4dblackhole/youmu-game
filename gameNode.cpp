#include "stdafx.h"
#include "gameNode.h"


gameNode::gameNode()
{
}


gameNode::~gameNode()
{

}

//마이크로소프트 비주얼 스튜디오에서만 존재
//SUCCEDED, S_OK, E_FAIL 등으로
//함수에 대한 초기화가 성공적인지, 에러가 났는지 여부를
//출력창에 띄워줘서 디버깅을 편하게 하기위함.

//물론 지금처럼 클래스 수가 적을 땐 상관이 없는데
//나중에 포트폴리오 할때 클래스 수가 많이 불어날 경우
//굉장히 유용하다

//초기화
HRESULT gameNode::init()	  
{
	_hdc = GetDC(_hWnd);
	_managerInit = false;

	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;
	if (_managerInit)
	{
		SetTimer(_hWnd, 1, 18, NULL);
		KEYMANAGER->init();
		IMAGEMANAGER->init();
	}
	return S_OK;
}

//메모리 해제
void gameNode::release()	  
{
	if (_managerInit)
	{
		KillTimer(_hWnd, 1);
		KEYMANAGER->release();
		KEYMANAGER->releaseSingleton();
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();
	}
	ReleaseDC(_hWnd, _hdc);
}

//업데이트(갱신)
void gameNode::update()		  
{
	InvalidateRect(_hWnd, NULL, false); 
}


//그리기
void gameNode::render(void)
{

}

//main에서 복사해서 가져오기
LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	//HWND : 어느 윈도우에서 메시지가 발생하는지 체크해준다
	//iMessage : 메시지 번호
	//wParam : 키보드 입력 및 마우스 클릭 체크
	//lParam : 마우스 좌표를 받아온다

	HDC hdc;				//Handel Device Context
	PAINTSTRUCT ps;

	static RECT _rc;

	switch (iMessage)
	{
	case WM_CREATE:
	{
	}
	break;
	case WM_TIMER:
		this->update();
	break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		this->render();
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		case VK_LEFT:
			break;
		case VK_RIGHT:
			break;
		case VK_UP:
			break;
		case VK_DOWN:
			break;
		}
	}
	break;
	case WM_MOUSEMOVE:
	{
		_ptMouse.x = static_cast<float>LOWORD(lParam);
		_ptMouse.y = static_cast<float>HIWORD(lParam);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
