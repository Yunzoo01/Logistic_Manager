//ui.h
#pragma once

void ui_GetControlHandle(HWND hDlg);

//-ComboBox-
void ui_ComboBoxInitData(HWND hDlg);

//-ListView-
void ui_ListViewCreateHeader(HWND hDlg);
void ui_ListViewPrintAll(HWND hDlg, vector<WAREHOUSE> warehouse);
void ui_DummyDataInput(HWND hDlg, vector<WAREHOUSE>* pwarehouse);
void ui_SelectListView(HWND hDlg, WPARAM wParam, LPARAM lParam);

//-���ϴܺ� ���
void ui_SelectPrint(HWND hDlg, WAREHOUSE wh);