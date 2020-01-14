
// MFCChatServerDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCChatServer.h"
#include "MFCChatServerDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMFCChatServerDlg 对话框



CMFCChatServerDlg::CMFCChatServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCHATSERVER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCChatServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSG_LIST, m_list);
	DDX_Control(pDX, IDC_COLOR_COMBO, m_WordColorCombo);
}

BEGIN_MESSAGE_MAP(CMFCChatServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START_BUTTON, &CMFCChatServerDlg::OnBnClickedStartButton)
	ON_BN_CLICKED(IDC_SEND_BUTTON, &CMFCChatServerDlg::OnBnClickedSendButton)
	ON_BN_CLICKED(IDC_CLEAR_BUTTON, &CMFCChatServerDlg::OnBnClickedClearButton)
	ON_BN_CLICKED(IDC_STOP_BUTTON, &CMFCChatServerDlg::OnBnClickedStopButton)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CAL_BUTTON, &CMFCChatServerDlg::OnBnClickedCalButton)
	ON_BN_CLICKED(IDC_MAIL_BUTTON, &CMFCChatServerDlg::OnBnClickedMailButton)
	ON_BN_CLICKED(IDC_QQ_BUTTON, &CMFCChatServerDlg::OnBnClickedQqButton)
END_MESSAGE_MAP()


// CMFCChatServerDlg 消息处理程序

BOOL CMFCChatServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	GetDlgItem(IDC_PORT_EDIT)->SetWindowText(_T("5000"));
	// TODO: 在此添加额外的初始化代码

	//控制控件
	GetDlgItem(IDC_START_BUTTON)->EnableWindow(TRUE);
	GetDlgItem(IDC_STOP_BUTTON)->EnableWindow(FALSE);
	GetDlgItem(IDC_SEND_BUTTON)->EnableWindow(FALSE);

	m_WordColorCombo.AddString(_T("黑色"));
	m_WordColorCombo.AddString(_T("红色"));
	m_WordColorCombo.AddString(_T("蓝色"));
	m_WordColorCombo.AddString(_T("绿色"));

	//设置当前下标为0
	m_WordColorCombo.SetCurSel(0);	//set 设置 cur current 当前的 sel select 选择
	SetDlgItemTextW(IDC_COLOR_COMBO, _T("黑色"));
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCChatServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCChatServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{	
		//1.定义dc
		CPaintDC dc(this); // 用于绘制的设备上下文
		//2.确定绘制的区域
		CRect rect;
		GetClientRect(&rect);

		//3 定义并创建一个内存设备环境 创建兼容性DC
		CDC dcBmp;
		dcBmp.CreateCompatibleDC(&dcBmp);
		//4载入资源图片
		CBitmap bmpBackGround;
		bmpBackGround.LoadBitmap(IDB_BlueTiles_BITMAP);
		//5.将图片资源载入到位图里面 bBitMap位图
		BITMAP bBitmap;
		bmpBackGround.GetBitmap(&bBitmap);
		//6.将位图选入临时的内存设备环境
		CBitmap* pbmpOld = dcBmp.SelectObject(&bmpBackGround);
		//7	开始绘制
		//将位图从源矩形和设备移动到目标矩形，如有必要，拉伸或压缩位图以适合目标矩形的尺寸。
		/*_AFXWIN_INLINE BOOL CDC::StretchBlt(int x, int y, int nWidth, int nHeight, CDC * pSrcDC,
			int xSrc, int ySrc, int nSrcWidth, int nSrcHeight, DWORD dwRop)
		{
			ASSERT(m_hDC != NULL); return ::StretchBlt(m_hDC, x, y, nWidth, nHeight,
				pSrcDC->GetSafeHdc(), xSrc, ySrc, nSrcWidth, nSrcHeight,
				dwRop);
		}*/
		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcBmp, 0, 0, bBitmap.bmWidth, bBitmap.bmHeight, SRCCOPY);

		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCChatServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCChatServerDlg::OnBnClickedStartButton()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_START_BUTTON)->EnableWindow(FALSE);
	GetDlgItem(IDC_STOP_BUTTON)->EnableWindow(TRUE);
	GetDlgItem(IDC_SEND_BUTTON)->EnableWindow(TRUE);


	TRACE("##OnBnClickedStartButton");
	CString strPort;
	//从控件里面获取内容
	GetDlgItem(IDC_PORT_EDIT)->GetWindowText(strPort);
	

	//CString转char *
	USES_CONVERSION;
	LPCTSTR szPort = (LPCTSTR)T2A(strPort);
	TRACE("szPort=%s", szPort);
	int iPort = _ttoi(strPort);
	//创建服务器Socket的对象
	m_server = new CServerSocket;
	//创建socket	
	if (!m_server->Create(iPort)) {
		TRACE("m_server Create error %d", GetLastError());
		return;
	}
	else
	{
		TRACE("m_server Create Success");
	}
	

	if (!m_server->Listen()) {
		TRACE("m_server Listen error %d", GetLastError());
		return;
	}

	
	CString strShow;
	CString strMsg= _T("");
	CString strInfo= _T("建立服务");
	strShow = CatShowString(strInfo, strMsg);
	m_list.AddString(strShow);
	UpdateData(FALSE);

}


void CMFCChatServerDlg::OnBnClickedSendButton()
{
	// TODO: 在此添加控件通知处理程序代码
	//1 获取编辑框内容
	CString strTmpMsg;
	GetDlgItem(IDC_SEND_EDIT)->GetWindowTextW(strTmpMsg);

	USES_CONVERSION;
	char* szSendBuf = T2A(strTmpMsg);
	//2 发送给服务端
	m_chat->Send(szSendBuf, MAX_SERVER_BUF, 0);

	//3 显示到列表框
	CString strInfo = _T("服务端: ");
	//2019-11-17 服务端:内容
	CString strShow = CatShowString(strInfo, strTmpMsg);
	


	m_list.AddString(strShow);
	UpdateData(FALSE);
	//清空编辑框
	GetDlgItem(IDC_SEND_EDIT)->SetWindowTextW(_T(""));
}
CString CMFCChatServerDlg::CatShowString(CString strInfo, CString strMsg)
{
	//时间+信息(昵称)+消息
	CString strTime;
	CTime tmNow;
	tmNow = CTime::GetCurrentTime();
	strTime = tmNow.Format("%X ");
	CString strShow;
	strShow = strTime + strInfo + strMsg;
	return strShow;
}

void CMFCChatServerDlg::OnBnClickedClearButton()
{
	// TODO: 在此添加控件通知处理程序代码
	m_list.ResetContent();
}


void CMFCChatServerDlg::OnBnClickedStopButton()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_START_BUTTON)->EnableWindow(TRUE);
	GetDlgItem(IDC_STOP_BUTTON)->EnableWindow(FALSE);
	GetDlgItem(IDC_SEND_BUTTON)->EnableWindow(FALSE);

	//2 回收资源
	m_server->Close();
	if (m_server) {
		delete m_server;
		m_server = NULL;
	}

	
	if (m_chat) {
		delete m_chat;
		m_chat = NULL;
	}

	//3显示到列表框
	CString strShow;
	strShow = CatShowString(_T(""), _T("服务器停止"));
	m_list.AddString(strShow);
	UpdateData(FALSE);
}


HBRUSH CMFCChatServerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	CString strColor;
	m_WordColorCombo.GetWindowText(strColor);

	if (IDC_MSG_LIST == pWnd->GetDlgCtrlID() || IDC_SEND_EDIT == pWnd->GetDlgCtrlID())
	{
		if (strColor == L"黑色")
		{
			pDC->SetTextColor(RGB(0, 0, 0));
		}
		else if (strColor == L"红色")
		{
			pDC->SetTextColor(RGB(255, 0, 0));
		}
		else if (strColor == L"蓝色")
		{
			pDC->SetTextColor(RGB(0, 0, 255));
		}
		else if (strColor == L"绿色")
		{
			pDC->SetTextColor(RGB(0, 255, 0));
		}
	}
	return hbr;
}


void CMFCChatServerDlg::OnBnClickedCalButton()
{
	// TODO: 在此添加控件通知处理程序代码
	//执行shell命令
// 	SHSTDAPI_(HINSTANCE) ShellExecuteW(_In_opt_ HWND hwnd, _In_opt_ LPCWSTR lpOperation, _In_ LPCWSTR lpFile, _In_opt_ LPCWSTR lpParameters,
// 		_In_opt_ LPCWSTR lpDirectory, _In_ INT nShowCmd);
	ShellExecute(NULL, L"open", L"calc.exe", NULL, NULL, SW_SHOWNORMAL);
}


void CMFCChatServerDlg::OnBnClickedMailButton()
{
	// TODO: 在此添加控件通知处理程序代码
	ShellExecute(NULL, L"open", L"https://mail.qq.com", NULL, NULL, SW_SHOWNORMAL);
}


void CMFCChatServerDlg::OnBnClickedQqButton()
{
	// TODO: 在此添加控件通知处理程序代码
	ShellExecute(NULL, L"open", L"D:\\Program Files (x86)\\Tencent\\QQLite\\Bin\\QQScLauncher.exe", NULL, NULL, SW_SHOWNORMAL);
}


BOOL CMFCChatServerDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	//规避回车键
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) {
		return TRUE;

	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_SPACE) {
		return TRUE;
	}
	//添加快捷键 ctrl+x 退出整个对话框 组合键
	if (pMsg->message == WM_KEYDOWN) {
		if (GetKeyState(VK_CONTROL) < 0)//ctrl 是否按下
		{
			TRACE("按下CTRL");
			if (pMsg->wParam == 'X')
			{
				TRACE("按下CTRL+X");
				CDialogEx::OnOK();
			}
		}
		return FALSE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
