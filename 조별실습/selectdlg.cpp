//selectdlg.cpp

#include "std.h"

extern HWND g_child;

BOOL CALLBACK SelectDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static int* pid = NULL;

	switch (msg)
	{
	case WM_INITDIALOG:
	{
		pid = (int*)lParam;

		return TRUE;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			*pid = GetDlgItemInt(hDlg, IDC_EDIT1, 0, 0);
			SendMessage(GetParent(hDlg), WM_APPLY, 0, 0);

			return TRUE;
		}

		case IDCANCEL:
			g_child = NULL; //<-------------------------------
			EndDialog(hDlg, IDCANCEL);
			return TRUE;
		}
	}
	}
	return FALSE;
}
