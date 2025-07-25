﻿
// gProjectDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "gProject.h"
#include "gProjectDlg.h"
#include "afxdialogex.h"
#include "iostream"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#ifdef UNICODE // 유니코드일 경우
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else // 멀티바이트일 경우
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
#endif

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.
CgProjectDlg* CgProjectDlg::pThis = NULL;

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CgProjectDlg 대화 상자



CgProjectDlg::CgProjectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GPROJECT_DIALOG, pParent),
	m_pDlgImage(nullptr),
	m_pDlgImgResult(nullptr)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CgProjectDlg::~CgProjectDlg()
{
	Clear();
}

void CgProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CgProjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_TEST, &CgProjectDlg::OnBnClickedBtnTest)
END_MESSAGE_MAP()


// CgProjectDlg 메시지 처리기

BOOL CgProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	pThis = this;
	Clear();

	MoveWindow(0, 0, CHILD ::WINDOW_WIDTH*2, CHILD::WINDOW_HEIGHT*2);
	m_pDlgImage = new CDlgImage;
	m_pDlgImage->Create(IDD_CDlgImage, this);
	m_pDlgImage->ShowWindow(SW_SHOW);
	m_pDlgImage->MoveWindow(0, 0, CHILD::WINDOW_WIDTH, CHILD::WINDOW_HEIGHT);


	m_pDlgImgResult = new CDlgImage;
	m_pDlgImgResult->Create(IDD_CDlgImage, this);
	m_pDlgImgResult->ShowWindow(SW_SHOW);
	m_pDlgImgResult->MoveWindow(CHILD::WINDOW_WIDTH, 0, CHILD::WINDOW_WIDTH, CHILD::WINDOW_HEIGHT);

	SetConsoleCtrlHandler(ConsoleHandler, TRUE);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CgProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CgProjectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

BOOL WINAPI CgProjectDlg::ConsoleHandler(DWORD dwCtrlType)
{
	switch (dwCtrlType)
	{
	case CTRL_C_EVENT:
	case CTRL_CLOSE_EVENT:
	case CTRL_BREAK_EVENT:
	case CTRL_LOGOFF_EVENT:
	case CTRL_SHUTDOWN_EVENT:
		std::cout << "Cleaning up resources...\n";
		// 🔑 리소스 해제 코드 작성
		// 예: delete, free, CloseHandle, GDI DeleteObject 등
		if(pThis)
			pThis->WindowDestroy();
		return TRUE;
	default:
		return FALSE;
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CgProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CgProjectDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	Clear();
}
void CgProjectDlg::WindowDestroy()
{
	m_pDlgImage = nullptr;
	m_pDlgImgResult = nullptr;
}

void CgProjectDlg::Clear()
{
	if (m_pDlgImage)
		delete m_pDlgImage;
	m_pDlgImage = nullptr;
	if (m_pDlgImgResult)
		delete m_pDlgImgResult;
	m_pDlgImgResult = nullptr;
}

void CgProjectDlg::OnBnClickedBtnTest()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	unsigned char* fm = (unsigned char* )m_pDlgImage->m_Image.GetBits();
	cout << "OnBnClickedBtnTest" << endl;

	int nWitdh = m_pDlgImage->m_Image.GetWidth();
	int nHeight = m_pDlgImage->m_Image.GetHeight();
	int nPitch = m_pDlgImage->m_Image.GetPitch();

	memset(fm, 0, nWitdh * nHeight);	// 0 BLACK

	for (int k = 0;k < Array::POINT_MAX;k++) {
		int x = rand() % nWitdh;
		int y = rand() % nHeight;
		fm[y * nPitch + x] = rand() % 255;
	}

	int nIndex = 0;
	int nTh = 100;
	m_pDlgImgResult->m_nDataCount = 0;
	for (int j = 0; j < nHeight; j++) {
		for (int i = 0; i < nWitdh; i++) {
			if (fm[j * nPitch + i] > nTh && m_pDlgImgResult->m_nDataCount < Array::POINT_MAX) {
				m_pDlgImgResult->m_ptData[nIndex].x = i;
				m_pDlgImgResult->m_ptData[nIndex].y = j;
				m_pDlgImgResult->m_nDataCount = ++nIndex;
				cout << nIndex << ":" << i << ","<< j << endl;
			}				
		}
	}

	m_pDlgImage->Invalidate();
	m_pDlgImgResult->Invalidate();
}
