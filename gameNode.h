#pragma once
#include "image.h"

static image *_backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);

class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;
public:
	virtual HRESULT init();
	virtual HRESULT init(bool managerInit);

	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	image *getBackBuffer(void) { return _backBuffer; }
	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getDC() { return _hdc; }

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);

	gameNode();
	virtual ~gameNode();
};

