//std.h
#pragma once

#pragma comment (linker, "/subsystem:windows")		// "/subsystem:console"

#include <Windows.h>
#include <tchar.h>
#include <commctrl.h>
#include "resource1.h"
#include <vector>
using namespace std;

//사용자 정의 통지 메시지
#define WM_APPLY WM_USER+100

#include "warehouse.h"
#include "handler.h"
#include "ui.h"
#include "insertdlg.h"
#include "selectdlg.h"