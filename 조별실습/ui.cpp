//ui.cpp

#include "std.h"

HWND g_hListView, g_hComboBox;

void ui_GetControlHandle(HWND hDlg)
{
	g_hListView = GetDlgItem(hDlg, IDC_LIST3);
	g_hComboBox = GetDlgItem(hDlg, IDC_COMBO1);
}

void ui_ComboBoxInitData(HWND hDlg)
{
	SendMessage(g_hComboBox, CB_ADDSTRING, 0, (LPARAM)TEXT("출고"));
	SendMessage(g_hComboBox, CB_ADDSTRING, 0, (LPARAM)TEXT("입고"));
}

void ui_ListViewCreateHeader(HWND hDlg)
{
	// 헤더를 추가한다.
	LVCOLUMN COL;

	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;
	COL.cx = 100;
	COL.pszText = (LPTSTR)TEXT("물류번호");				// 첫 번째 헤더
	COL.iSubItem = 0;
	SendMessage(g_hListView, LVM_INSERTCOLUMN, 0, (LPARAM)&COL);

	COL.cx = 150;
	COL.pszText = (LPTSTR)TEXT("품목");			// 두 번째 헤더
	COL.iSubItem = 1;
	SendMessage(g_hListView, LVM_INSERTCOLUMN, 1, (LPARAM)&COL);

	COL.cx = 150;
	COL.pszText = (LPTSTR)TEXT("날짜");				// 세 번째 헤더
	COL.iSubItem = 2;
	SendMessage(g_hListView, LVM_INSERTCOLUMN, 2, (LPARAM)&COL);

	COL.cx = 100;
	COL.pszText = (LPTSTR)TEXT("유형");				// 네 번째 헤더
	COL.iSubItem = 3;
	SendMessage(g_hListView, LVM_INSERTCOLUMN, 3, (LPARAM)&COL);

	ListView_SetExtendedListViewStyle(g_hListView, LVS_EX_FULLROWSELECT |
		LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP);
}

void ui_ListViewPrintAll(HWND hDlg, vector<WAREHOUSE> warehouse)
{
	//리스트뷰 출력된 정보를 clear
	ListView_DeleteAllItems(g_hListView);

	for (int i = 0; i < (int)warehouse.size(); i++)
	{
		WAREHOUSE wh = warehouse[i];

		//----------------------------------------------------
		// 텍스트와 이미지를 가진 아이템들을 등록한다.
		LVITEM LI;
		LI.mask = LVIF_TEXT;

		LI.iItem = i;     //리스트뷰에 출력되는 행의 위치
		LI.iSubItem = 0;

		TCHAR temp[20];
		wsprintf(temp, TEXT("%d"), wh.id); // 첫 번째 아이템
		LI.pszText = temp;
		SendMessage(g_hListView, LVM_INSERTITEM, 0, (LPARAM)&LI);

		LI.iSubItem = 1;
		LI.pszText = wh.name;
		SendMessage(g_hListView, LVM_SETITEM, 0, (LPARAM)&LI);

		LI.iSubItem = 2;
		LI.pszText = wh.day;
		SendMessage(g_hListView, LVM_SETITEM, 0, (LPARAM)&LI);

		LI.iSubItem = 3;
		wsprintf(temp, TEXT("%s"), (wh.type == TRUE ? TEXT("출고") : TEXT("입고")));
		LI.pszText = temp;
		SendMessage(g_hListView, LVM_SETITEM, 0, (LPARAM)&LI);
		//----------------------------------------------------------
	}
}

void ui_SelectListView(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	LPNMHDR hdr;
	LPNMLISTVIEW nlv;
	hdr = (LPNMHDR)lParam;
	nlv = (LPNMLISTVIEW)lParam;

	if (hdr->hwndFrom == g_hListView)
	{
		switch (hdr->code)
		{
			// 선택된 항목을 에디트에 보여준다.
		case LVN_ITEMCHANGED:
			if (nlv->uChanged == LVIF_STATE && nlv->uNewState == (LVIS_SELECTED | LVIS_FOCUSED))
			{
				LVITEM LI;
				LI.iItem = nlv->iItem;
				LI.iSubItem = 0;
				ListView_GetItem(g_hListView, &LI);

				//UI작업-------------------------------------------------
				TCHAR temp[20];
				ListView_GetItemText(g_hListView, nlv->iItem, 0, temp, _countof(temp));
				SetDlgItemText(hDlg, IDC_EDIT1, temp);

				ListView_GetItemText(g_hListView, nlv->iItem, 1, temp, _countof(temp));
				SetDlgItemText(hDlg, IDC_EDIT2, temp);

				ListView_GetItemText(g_hListView, nlv->iItem, 2, temp, _countof(temp));
				SetDlgItemText(hDlg, IDC_EDIT3, temp);

				ListView_GetItemText(g_hListView, nlv->iItem, 3, temp, _countof(temp));

				if (_tcscmp(temp, TEXT("출고")) == 0)
					SendMessage(g_hComboBox, CB_SETCURSEL, 0, 0);
				else
					SendMessage(g_hComboBox, CB_SETCURSEL, 1, 0);
				//-------------------------------------------------------
			}
		}
	}
}

void ui_DummyDataInput(HWND hDlg, vector<WAREHOUSE>* pwarehouse)
{
	WAREHOUSE mem1 = { 1, TEXT("냉장고"), TEXT("2022-03-08"), TRUE };
	pwarehouse->push_back(mem1);

	WAREHOUSE mem2 = { 2, TEXT("세탁기"), TEXT("2022-03-05"), FALSE };
	pwarehouse->push_back(mem2);

	WAREHOUSE mem3 = { 3, TEXT("식기세척기"), TEXT("2022-03-01"), TRUE };
	pwarehouse->push_back(mem3);

	ui_ListViewPrintAll(hDlg, *pwarehouse);
}

void ui_SelectPrint(HWND hDlg, WAREHOUSE wh)
{
	SetDlgItemInt(hDlg, IDC_EDIT1, wh.id, 0);
	SetDlgItemText(hDlg, IDC_EDIT2, wh.name);
	SetDlgItemText(hDlg, IDC_EDIT3, wh.day);
	if (wh.type == TRUE)
		SendMessage(g_hComboBox, CB_SETCURSEL, 0, 0);
	else
		SendMessage(g_hComboBox, CB_SETCURSEL, 1, 0);
}