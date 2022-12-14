// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <iostream>
#include <vector>
#include <time.h>

#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "KeyManager.h"
#include "utiles.h"
#include "collision.h"
#include "imageManager.h"

using namespace std;
using namespace Netune_UTIL;

#define WINNAME (LPTSTR)TEXT("Neptune API")
#define WINSTARTX 50
#define WINSTARTY 50
#define WINSIZEX 1000
#define WINSIZEY 850
#define WINSTYLE WS_CAPTION | WS_SYSMENU


#define RND randomFunction::getSingleton()
#define KEYMANAGER KeyManager::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()

//안전한 메모리 관리
#define SAFE_DELETE(p) { if(p) {delete(p); (p) = NULL; }}      //생성된 오브젝트 및 포인터를 안전하게 삭제하는 방안을 미리 작성해놓은 것
#define SAFE_RELEASE(p) {if(p) {(p)->release(); (p)=NULL; }}

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
extern HINSTANCE	_hInstance;		//인스턴스 핸들
extern HWND			_hWnd;			//핸들
extern POINT        _ptMouse;       //마우스
