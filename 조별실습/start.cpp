//start.cpp

#include "std.h"

//회원정보 저장소
vector<WAREHOUSE> g_warehouse;

//자식 윈도의 핸들(selectDlg의 핸들)
HWND g_child = NULL;

BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		//최초 호출 시점.
	case WM_INITDIALOG:		 return OnInitDialog(hDlg, wParam, lParam);

	case WM_COMMAND:		 return OnCommand(hDlg, wParam, lParam);
	case WM_APPLY:			 return OnApply(hDlg, wParam, lParam);
	case WM_NOTIFY:			 return OnNotify(hDlg, wParam, lParam);
	}
	return FALSE;	//메시지를 처리하지 않았다.-> 이 다음에 대화상자 처리하는 default프로시저
}

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpCmdLine, int nShowCmd)
{
	UINT ret = DialogBox(hInst,// instance
		MAKEINTRESOURCE(IDD_DIALOG1), // 다이얼로그 선택
		0, // 부모 윈도우
		DlgProc); // Proc..


	return 0;
}