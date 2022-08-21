#include "stdafx.h"
#include "gameNode.h"


gameNode::gameNode()
{
}


gameNode::~gameNode()
{

}

//����ũ�μ���Ʈ ���־� ��Ʃ��������� ����
//SUCCEDED, S_OK, E_FAIL ������
//�Լ��� ���� �ʱ�ȭ�� ����������, ������ ������ ���θ�
//���â�� ����༭ ������� ���ϰ� �ϱ�����.

//���� ����ó�� Ŭ���� ���� ���� �� ����� ���µ�
//���߿� ��Ʈ������ �Ҷ� Ŭ���� ���� ���� �Ҿ ���
//������ �����ϴ�

//�ʱ�ȭ
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

//�޸� ����
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

//������Ʈ(����)
void gameNode::update()		  
{
	InvalidateRect(_hWnd, NULL, false); 
}


//�׸���
void gameNode::render(void)
{

}

//main���� �����ؼ� ��������
LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	//HWND : ��� �����쿡�� �޽����� �߻��ϴ��� üũ���ش�
	//iMessage : �޽��� ��ȣ
	//wParam : Ű���� �Է� �� ���콺 Ŭ�� üũ
	//lParam : ���콺 ��ǥ�� �޾ƿ´�

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
