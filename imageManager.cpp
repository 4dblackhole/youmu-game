#include "stdafx.h"
#include "imageManager.h"

imageManager::imageManager(){}

imageManager::~imageManager(){}

HRESULT imageManager::init(void)
{
	return S_OK;
}
void imageManager::release(void)
{
	deleteALL();
}

image * imageManager::addImage(string strKey, int width, int height)
{
	image* img = findImage(strKey);
	//�̹����� �̹� �ִٸ� �� �̹����� ��ȯ
	if (img) return img;
	//�װ� �ƴ϶�� ���μ����� ������� �´�.
	img = new image;

	if (FAILED(img->init(width, height)))
	{
		SAFE_DELETE(img);
		return NULL;
	}
	_mImageList.insert(make_pair(strKey, img));
	
	return img;
}

image * imageManager::addImage(string strKey, const char * fileName, int width, int height, bool trans, COLORREF transColor)
{
	image* img = findImage(strKey);
	//�̹����� �̹� �ִٸ� �� �̹����� ��ȯ
	if (img) return img;
	//�װ� �ƴ϶�� ���������� ������� �´�.
	img = new image;

	if (FAILED(img->init(fileName, width, height, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::addImage(string strKey, const char * fileName, float x, float y, int width, int height, bool trans, COLORREF transColor)
{
	image* img = findImage(strKey);
	//�̹����� �̹� �ִٸ� �� �̹����� ��ȯ
	if (img) return img;
	//�װ� �ƴ϶�� ���������� ������� �´�.
	img = new image;

	if (FAILED(img->init(fileName, x, y, width, height, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::addFrameImage(string strKey, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor)
{
	image* img = findImage(strKey);
	//�̹����� �̹� �ִٸ� �� �̹����� ��ȯ
	if (img) return img;
	//�װ� �ƴ϶�� ���������� ������� �´�.
	img = new image;

	if (FAILED(img->init(fileName, x, y, width, height, frameX, frameY, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::addFrameImage(string strKey, const char * fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor)
{
	image* img = findImage(strKey);
	//�̹����� �̹� �ִٸ� �� �̹����� ��ȯ
	if (img) return img;
	//�װ� �ƴ϶�� ���������� ������� �´�.
	img = new image;

	if (FAILED(img->init(fileName, width, height, frameX, frameY, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::findImage(string strKey)
{
	mapImageIter key = _mImageList.find(strKey);

	//ã�Ҵ�.
	if (key != _mImageList.end())
	{
		return key->second;
	}
	return NULL;
}

BOOL imageManager::deleteImage(string strKey)
{
	mapImageIter key = _mImageList.find(strKey);

	//ã�Ҵ�.
	if (key != _mImageList.end())
	{
		key->second->release();
		SAFE_DELETE(key->second);
		_mImageList.erase(key);

		return true;
	}
	return false;
}

BOOL imageManager::deleteALL(void)
{
	mapImageIter iter = _mImageList.begin();

	//ã�Ҵ�.
	for (;iter != _mImageList.end();)
	{
		//�̹��� ������ ���� �ִ�
		if (iter->second != NULL)
		{
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
		}
		else ++iter;
	}
	_mImageList.clear();
	
	return TRUE;
}

void imageManager::render(string strKey, HDC hdc)
{
	image* img = findImage(strKey);
	if (img) img->render(hdc);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY)
{
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
}

void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY)
{
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY);
}

void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}
void imageManager::loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offSetX, int offSetY)
{
	image* img = findImage(strKey);
	if (img) img->loopRender(hdc, drawArea, offSetX, offSetY);
}
