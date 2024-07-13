//handler.cpp

#include "std.h"

extern vector<WAREHOUSE> g_warehouse;
extern HWND g_child;

int g_selectid;

BOOL OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	ui_GetControlHandle(hDlg);
	ui_ComboBoxInitData(hDlg);
	ui_ListViewCreateHeader(hDlg);

	//���߿� ����
	ui_DummyDataInput(hDlg, &g_warehouse);

	return TRUE;
}

BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	case IDCANCEL:		EndDialog(hDlg, IDCANCEL);  return TRUE;
	case IDC_BUTTON1:	OnInsert(hDlg);				return TRUE;
	case IDC_BUTTON2:	OnSelect(hDlg);				return TRUE;
	//case IDC_BUTTON3:   OnUpdate(hDlg);				return TRUE;
	//case IDC_BUTTON4:   OnDelete(hDlg);				return TRUE;
	}
	return TRUE;
}

BOOL OnApply(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	for (int i = 0; i < (int)g_warehouse.size(); i++)
	{
		WAREHOUSE mem = g_warehouse[i];
		if (mem.id == g_selectid)
		{
			ui_SelectPrint(hDlg, mem);
			return TRUE;
		}
	}
	MessageBox(hDlg, TEXT("���� ��ȣ�Դϴ�."), TEXT("�˸�"), MB_OK);

	return TRUE;
}

BOOL OnNotify(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	ui_SelectListView(hDlg, wParam, lParam);

	return TRUE;
}

void OnInsert(HWND hDlg)
{
	WAREHOUSE temp;

	UINT ret = DialogBoxParam(GetModuleHandle(0), MAKEINTRESOURCE(IDD_DIALOG2),
		hDlg, InsertDlgProc, (LPARAM)&temp);

	if (ret == IDOK)
	{
		g_warehouse.push_back(temp);

		//�»�� ���
		TCHAR buf[20];
		wsprintf(buf, TEXT("ǰ��� : %d��"), g_warehouse.size());
		SetDlgItemText(hDlg, IDC_STATIC1, buf);

		//ȸ������Ʈ ���
		ui_ListViewPrintAll(hDlg, g_warehouse);
	}
}

void OnSelect(HWND hDlg)
{

	if (g_child == NULL)
	{
		g_child = CreateDialogParam(GetModuleHandle(0), MAKEINTRESOURCE(IDD_DIALOG3),
			hDlg, SelectDlgProc, (LPARAM)&g_selectid);
		ShowWindow(g_child, SW_SHOW);
	}
	else
	{
		SetFocus(g_child);
	}
}

//void OnUpdate(HWND hDlg)
//{
//	WAREHOUSE wh;
//
//	SetDlgItemInt(hDlg, IDC_EDIT1, wh.id, 0);
//	SetDlgItemText(hDlg, IDC_EDIT2, wh.name);
//	SetDlgItemText(hDlg, IDC_EDIT3, wh.day);
//	if (wh.type == TRUE)
//		SendMessage(g_hComboBox, CB_SETCURSEL, 0, 0);
//	else
//		SendMessage(g_hComboBox, CB_SETCURSEL, 1, 0);
//
//
//	for (int i = 0; i < (int)g_warehouse.size(); i++)
//		{
//			if (wh.id = g_selectid)
//			{
//				//----------------------------------------------------
//				// �ؽ�Ʈ�� �̹����� ���� �����۵��� ����Ѵ�.
//				LVITEM LI;
//				LI.mask = LVIF_TEXT;
//
//				LI.iItem = i;     //����Ʈ�信 ��µǴ� ���� ��ġ
//				LI.iSubItem = 0;
//
//				TCHAR temp[20];
//				wsprintf(temp, TEXT("%d"), wh.id); // ù ��° ������
//				LI.pszText = temp;
//				SendMessage(g_hListView, LVM_INSERTITEM, 0, (LPARAM)&LI);
//
//				LI.iSubItem = 1;
//				LI.pszText = wh.name;
//				SendMessage(g_hListView, LVM_SETITEM, 0, (LPARAM)&LI);
//
//				LI.iSubItem = 2;
//				LI.pszText = wh.day;
//				SendMessage(g_hListView, LVM_SETITEM, 0, (LPARAM)&LI);
//
//				LI.iSubItem = 3;
//				wsprintf(temp, TEXT("%s"), (wh.type == TRUE ? TEXT("���") : TEXT("�԰�")));
//				LI.pszText = temp;
//				SendMessage(g_hListView, LVM_SETITEM, 0, (LPARAM)&LI);
//			}
//	}
//}

//void OnDelete(HWND hDlg)
//{
//
//}