//handler.h

#pragma once

BOOL OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam);
BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam);
BOOL OnApply(HWND hDlg, WPARAM wParam, LPARAM lParam);
BOOL OnNotify(HWND hDlg, WPARAM wParam, LPARAM lParam);

void OnInsert(HWND hDlg);
void OnSelect(HWND hDlg);
//void OnUpdate(HWND hDlg);
void OnDelete(HWND hDlg);
