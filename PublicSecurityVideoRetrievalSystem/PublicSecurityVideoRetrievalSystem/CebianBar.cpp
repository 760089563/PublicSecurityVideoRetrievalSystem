#include "stdafx.h"
#include "CebianBar.h"
#include "resource.h"

CCebianDlg CCebianBar::ceDlg;

CCebianBar::CCebianBar()
{
}


CCebianBar::~CCebianBar()
{
}
BEGIN_MESSAGE_MAP(CCebianBar, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()


int CCebianBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	ceDlg.Create(IDD_DIALOG1, this);
	ceDlg.ShowWindow(SW_SHOW);
	GetClientRect(&m_rect);
	return 0;
}


void CCebianBar::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
	if (ceDlg.GetSafeHwnd())
	{
		CRect rct;
		GetClientRect(rct);
		ceDlg.MoveWindow(rct);
	}

	if (nType != SIZE_MINIMIZED) {
		int WeightOfCell = 70;
		int LengthOfLabel = 50;
		int HeightOfCell = 50;
		int LengtgOfIcon = 28;
		int FuncRect = 200;

		int btn_IDs[] = {
			IDC_AI_Save, IDC_AI_Start, IDC_NUMBER, IDC_CAMERA_SHOOTING,
			IDC_SECONDS, IDC_VIDEO_SHOOTING, IDC_PHOTO_HISTORY, 
			IDC_ON_CANERA, IDC_ESS3, IDC_ESS, IDC_IOS3, 
			IDC_IOSA, IDC_SHUT_DOWN, IDC_SETTING
		};
		int lab_IDs[] = {
			IDL_AI_Save, IDL_START, IDL_NUMBER, IDL_CAMERA_SHOOTING, 
			IDL_SECONDS, IDL_VIDEO_SHOOTING, IDL_PHOTO_HISTORY, 
			IDL_ON_CANERA, IDL_ESS3, IDL_ESS, IDL_IOS3, IDL_IOSA,
			IDL_SHUT_DOWN, IDL_SETTING
		};
		// 总共的按钮数
		int N = 14;
		// 获取窗口大小
		GetClientRect(&m_rect);
		// 每行的个数
		int n_in_col =( m_rect.Width() - 20) / WeightOfCell;
		n_in_col = (n_in_col == 0) ? 1 : n_in_col;
		// 获取间距
		n_in_col = (n_in_col > N + 1) ? N + 1 : n_in_col;
		int space_between = (m_rect.Width() - WeightOfCell * n_in_col) / (n_in_col + 1);
		// 表示控制的btn的索引
		int cur_btn_index = 0;
		// 控制行数
		for (int i = 0; i < N ; i++) {
			// 控制列数
			for (int j = 0; j < n_in_col; j++, cur_btn_index++) {
				// 控制第cur_btn_index个btn的位置
				if (cur_btn_index > N - 1)
					break;
				CWnd *cWnd_btn = ceDlg.GetDlgItem(btn_IDs[cur_btn_index]);
				// 位置坐标 = 间距 + 按钮大小
				int x = (j + 1)*space_between + j * WeightOfCell;
				int y = (i + 1) * 20 + i * HeightOfCell;
				// 控制按钮的位置
				cWnd_btn->SetWindowPos(NULL, x, y, 0, 0, SWP_NOSIZE);
				// 控制对应的label的位置
				cWnd_btn = ceDlg.GetDlgItem(lab_IDs[cur_btn_index]);
				cWnd_btn->SetWindowPos(NULL, x - 11, y + 45, 0, 0, SWP_NOSIZE);
			}
			if (cur_btn_index > N)
				break;
		}
		// 设置水平线
		CWnd *line = ceDlg.GetDlgItem(IDC_CUR_OFF_RULE);
		line->SetWindowPos(NULL, 0, (N / n_in_col + 1) * 20 +( N / n_in_col ) * WeightOfCell,
			m_rect.Width(), 1, SWP_SHOWWINDOW);
		int func_btn[] = { IDC_1,IDC_2,IDC_3,IDC_4 };
		space_between = (m_rect.Width() - 24 * 4) / 5;
		for (int i = 0; i < 4; i ++ ) {
			CWnd *cWnd_fun_btn = ceDlg.GetDlgItem(func_btn[i]);
			cWnd_fun_btn->SetWindowPos(NULL, space_between*(i+1) + i * 24,
				(N / n_in_col + 1) * 20 + (N / n_in_col) * WeightOfCell + 20,
				0, 0, SWP_NOSIZE);
		}
	}

}
