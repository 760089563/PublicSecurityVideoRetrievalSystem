// CExplorer.cpp: 实现文件
//
#include "stdafx.h"
// #include "pch.h"
#include "PublicSecurityVideoRetrievalSystem.h"
#include "CExplorer.h"
#include "afxdialogex.h"


// CExplorer 对话框

IMPLEMENT_DYNAMIC(CExplorer, CDialogEx)

CExplorer::CExplorer(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EXPLORER, pParent)
{

}

CExplorer::~CExplorer()
{
}

void CExplorer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CExplorer, CDialogEx)
END_MESSAGE_MAP()


// CExplorer 消息处理程序
