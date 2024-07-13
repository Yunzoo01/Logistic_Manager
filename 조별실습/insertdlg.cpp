//insertdlg.cpp

#include "std.h"

BOOL CALLBACK InsertDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static WAREHOUSE* pwarehouse = NULL;
	static HWND hcombo;

	switch (msg)
	{
	case WM_INITDIALOG:
	{
		pwarehouse = (WAREHOUSE*)lParam;

		hcombo = GetDlgItem(hDlg, IDC_COMBO1);

		SendMessage(hcombo, CB_ADDSTRING, 0, (LPARAM)TEXT("���"));
		SendMessage(hcombo, CB_ADDSTRING, 0, (LPARAM)TEXT("�԰�"));

		return TRUE;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			//��Ʈ�ѿ� ��µ� ������ ���޵� �ּҷ� ����...
			pwarehouse->id = GetDlgItemInt(hDlg, IDC_EDIT1, 0, 0);
			GetDlgItemText(hDlg, IDC_EDIT2, pwarehouse->name, _countof(pwarehouse->name));
			GetDlgItemText(hDlg, IDC_EDIT3, pwarehouse->day, _countof(pwarehouse->day));

			int idx = SendMessage(hcombo, CB_GETCURSEL, 0, 0);  //0 or 1
			if (idx == 0)
				pwarehouse->type = TRUE;
			else if (idx == 1)
				pwarehouse->type = FALSE;

			EndDialog(hDlg, IDOK);
			return TRUE;
		}

		case IDCANCEL:
			EndDialog(hDlg, IDCANCEL);
			return TRUE;
		}
	}
	}
	return FALSE;
}