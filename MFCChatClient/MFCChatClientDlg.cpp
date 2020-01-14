
// MFCChatClientDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCChatClient.h"
#include "MFCChatClientDlg.h"
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


// CMFCChatClientDlg 对话框



CMFCChatClientDlg::CMFCChatClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCHATCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCChatClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_SENDMSG_EDIT, m_input);
	DDX_Control(pDX, IDC_COLOR_COMBO, m_WordColorCombo);
}

BEGIN_MESSAGE_MAP(CMFCChatClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

ON_BN_CLICKED(IDC_CONNECT_BTN, &CMFCChatClientDlg::OnBnClickedConnectBtn)
ON_BN_CLICKED(IDC_SEND_BTN, &CMFCChatClientDlg::OnBnClickedSendBtn)
ON_BN_CLICKED(IDC_SAVENAME_BTN, &CMFCChatClientDlg::OnBnClickedSavenameBtn)

ON_BN_CLICKED(IDC_CLEARMSG_BTN, &CMFCChatClientDlg::OnBnClickedClearmsgBtn)
ON_BN_CLICKED(IDC_AUTOSEND_CHECK, &CMFCChatClientDlg::OnBnClickedAutosendCheck)
ON_BN_CLICKED(IDC_DISCONNECT_BTN, &CMFCChatClientDlg::OnBnClickedDisconnectBtn)
ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CMFCChatClientDlg 消息处理程序

BOOL CMFCChatClientDlg::OnInitDialog()
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

	// TODO: 在此添加额外的初始化代码
	GetDlgItem(IDC_PORT_EDIT)->SetWindowText(_T("5000"));
	GetDlgItem(IDC_IPADDRESS)->SetWindowText(_T("127.0.0.1"));
	SetDlgItemText(IDC_AUTOSENDMSG_EDIT, _T("你好,我有事不在!"));

// 	GetPrivateProfileStringW(
// 		_In_opt_ LPCWSTR lpAppName,
// 		_In_opt_ LPCWSTR lpKeyName,
// 		_In_opt_ LPCWSTR lpDefault,
// 		_Out_writes_to_opt_(nSize, return +1) LPWSTR lpReturnedString,
// 		_In_     DWORD nSize,
// 		_In_opt_ LPCWSTR lpFileName
// 	);

	WCHAR wszName[MAX_PATH];
	WCHAR strPath[MAX_PATH] = { 0 };
	//获取当前路径
	GetCurrentDirectory(MAX_PATH, strPath);
	TRACE("###strPath=%ls", strPath);
	CString strFilePath;
	strFilePath.Format(L"%s//Test.ini", strPath);
	

	DWORD dwNum= GetPrivateProfileStringW(_T("CLIENT"), _T("NAME"), NULL, wszName,MAX_PATH, strFilePath);

	if (dwNum > 0) {
		SetDlgItemText(IDC_NAME_EDIT, wszName);
		UpdateData(FALSE);
	}
	else {
		DWORD dwNum = GetPrivateProfileStringW(_T("CLIENT"), _T("NAME"), NULL, L"客户端", MAX_PATH, strFilePath);
		SetDlgItemText(IDC_NAME_EDIT, L"客户端");
		UpdateData(FALSE);
	}

	//初始化控件
	GetDlgItem(IDC_SEND_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_DISCONNECT_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_CONNECT_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_AUTOSEND_CHECK)->EnableWindow(FALSE);

	m_WordColorCombo.AddString(_T("黑色"));
	m_WordColorCombo.AddString(_T("红色"));
	m_WordColorCombo.AddString(_T("蓝色"));
	m_WordColorCombo.AddString(_T("绿色"));

	//设置当前下标为0
	m_WordColorCombo.SetCurSel(0);	//set 设置 cur current 当前的 sel select 选择
	SetDlgItemTextW(IDC_COLOR_COMBO, _T("黑色"));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCChatClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCChatClientDlg::OnPaint()
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
		bmpBackGround.LoadBitmap(IDB_sheetbackground_BITMAP);
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
HCURSOR CMFCChatClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}






void CMFCChatClientDlg::OnBnClickedConnectBtn()
{
	GetDlgItem(IDC_SEND_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_DISCONNECT_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_CONNECT_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_AUTOSEND_CHECK)->EnableWindow(TRUE);
	//把IP和端口拿到
	TRACE("##OnBnClickedConnectBtn");
	CString strPort, strIP;
	//从控件里面获取内容
	GetDlgItem(IDC_PORT_EDIT)->GetWindowTextW(strPort);
	GetDlgItem(IDC_IPADDRESS)->GetWindowText(strIP);

	//CString转char *

	USES_CONVERSION;
	
	//LPCTSTR szPort = (LPCTSTR)W2A(strPort);
	LPCWSTR wszPort= strPort;
	//LPCTSTR szIP = (LPCTSTR)W2A(strIP);
	LPCWSTR wszIP = strIP;
	TRACE(L"wszPort=%s,wszIP=%s", wszPort, wszIP);
	
	int iPort = _ttoi(strPort);
	//创建一个socket对象
	m_client = new CMySocket;

	//创建套接字 容错
	if (!m_client->Create()) {
		TRACE("m_client Create error %d", GetLastError());
		return;
	}


	//连接
	if (m_client->Connect(strIP, iPort)!=SOCKET_ERROR) {
		TRACE("m_client Connect error %d", GetLastError());
		return;
	}

	
}


void CMFCChatClientDlg::OnBnClickedSendBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	//1 获取编辑框内容

	CString strMsg;
	GetDlgItem(IDC_SENDMSG_EDIT)->GetWindowText(strMsg);
	CString strInfo;
	GetDlgItemText(IDC_NAME_EDIT, strInfo);
	strInfo += _T(":");
	strMsg = strInfo +strMsg;
	USES_CONVERSION;
	char* szSendBuf = T2A(strMsg);
	//2 发送给服务端
	m_client->Send(szSendBuf, SEND_MAX_BUF, 0);

	//3 显示到列表框
	CString strShow;
	
	
	
	strShow = CatShowString(_T(""), strMsg);

	m_list.AddString(strShow);
	UpdateData(FALSE);
	//清空编辑框
	GetDlgItem(IDC_SENDMSG_EDIT)->SetWindowTextW(_T(""));
}

CString CMFCChatClientDlg::CatShowString(CString strInfo, CString strMsg)
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



void CMFCChatClientDlg::OnBnClickedSavenameBtn()
{
	// 保存昵称
// 	WritePrivateProfileStringW(
// 		_In_opt_ LPCWSTR lpAppName,//项		
// 		_In_opt_ LPCWSTR lpKeyName,//键
// 		_In_opt_ LPCWSTR lpString,
// 		_In_opt_ LPCWSTR lpFileName
// 	);
	CString strName;
	GetDlgItemText(IDC_NAME_EDIT, strName);
	if (strName.GetLength() <= 0) {
		MessageBoxW(_T("昵称不能为空"));
		return;
	}
	if (IDOK == AfxMessageBox(L"真的要修改昵称吗?", MB_OKCANCEL) ){
		
		WCHAR strPath[MAX_PATH] = { 0 };
		//获取当前路径
		GetCurrentDirectory(MAX_PATH, strPath);
		TRACE("###strPath=%ls", strPath);
		CString strFilePath;
		strFilePath.Format(L"%s//Test.ini", strPath);
		

		WritePrivateProfileStringW(_T("CLIENT"), _T("NAME"), strName, strFilePath);
		UpdateData(FALSE);
	}
	
}





void CMFCChatClientDlg::OnBnClickedClearmsgBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	m_list.ResetContent();
}


void CMFCChatClientDlg::OnBnClickedAutosendCheck()
{
	// TODO: 在此添加控件通知处理程序代码
	if (((CButton*)GetDlgItem(IDC_AUTOSEND_CHECK))->GetCheck()) {
		((CButton*)GetDlgItem(IDC_AUTOSEND_CHECK))->SetCheck(FALSE);
	}
	else {
		((CButton*)GetDlgItem(IDC_AUTOSEND_CHECK))->SetCheck(TRUE);
	}
}


void CMFCChatClientDlg::OnBnClickedDisconnectBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	//1 控制控件
	GetDlgItem(IDC_SEND_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_DISCONNECT_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_CONNECT_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_AUTOSEND_CHECK)->EnableWindow(FALSE);

	//2 回收资源
	m_client->Close();
	if (m_client) {
		delete m_client;
		m_client = NULL;
	}
	//3显示到列表框
	CString strShow;
	strShow = CatShowString(_T(""), _T("断开与服务器连接"));
	m_list.AddString(strShow);
	UpdateData(FALSE);
}


HBRUSH CMFCChatClientDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	CString strColor;
	m_WordColorCombo.GetWindowText(strColor);

	if (IDC_LIST1 == pWnd->GetDlgCtrlID() || IDC_SENDMSG_EDIT == pWnd->GetDlgCtrlID())
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


BOOL CMFCChatClientDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	//规避回车键
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam==VK_RETURN) {
		return TRUE;

	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_SPACE) {
		return TRUE;
	}
	//添加快捷键 ctrl+x 退出整个对话框 组合键
	if (pMsg->message == WM_KEYDOWN)
	{
		if (GetKeyState(VK_CONTROL)<0)//ctrl 是否按下
		{	
			TRACE("按下CTRL");
			if (pMsg->wParam=='X')
			{
				TRACE("按下CTRL+X");
				CDialogEx::OnOK();
			}
		}
		return FALSE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
