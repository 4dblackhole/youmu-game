#pragma once
#include "singletonBase.h"
#include "image.h"
#include <map>
class imageManager :public singletonBase<imageManager>
{
private:
	typedef map<string, image*>             mapImageList;
	typedef map<string, image*>::iterator   mapImageIter;

private:
	mapImageList _mImageList;
public:
	HRESULT init(void);
	void release(void);

	image* addImage(string strKey, int width, int height);
	image* addImage(string strKey, const char* fileName, int width, int height, bool trans, COLORREF transColor);
	image* addImage(string strKey, const char* fileName,float x, float y, int width, int height, bool trans, COLORREF transColor);

	image* addFrameImage(string strKey, const char* fileName,float x, float y, int width, int height, int frameX,int frameY, bool trans, COLORREF transColor);
	image* addFrameImage(string strKey, const char* fileName,int width, int height, int frameX, int frameY, bool trans,COLORREF transColor);

	image* findImage(string strKey);

	BOOL deleteImage(string strKey);

	BOOL deleteALL(void);

	void render(string strKey, HDC hdc);
	void render(string strKey, HDC hdc, int destX, int destY);
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	//«¡∑π¿”∑ª¥ı
	void frameRender(string strKey, HDC hdc, int destX, int destY);
	void frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
	//∑Á«¡∑ª¥ı
	void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offSetX, int offSetY);
	imageManager();
	~imageManager();
};

