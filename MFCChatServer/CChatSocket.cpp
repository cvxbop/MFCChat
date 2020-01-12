#include "pch.h"
#include "CChatSocket.h"
#include "MFCChatServerDlg.h"

CChatSocket::CChatSocket()
{
}

CChatSocket::~CChatSocket()
{
}

void CChatSocket::OnReceive(int nErrorCode)
{
	//1 接收数据到szRecvBuf
	TRACE("####Server OnReceive");
	CMFCChatServerDlg* dlg = (CMFCChatServerDlg*)AfxGetApp()->GetMainWnd();
	char szRecvBuf[MAX_SERVER_BUF] = { 0 };
	Receive(szRecvBuf, MAX_SERVER_BUF, 0);
	TRACE("####Server szRecvBuf=%s", szRecvBuf);

	//2 显示buf
	USES_CONVERSION;
	CString strRecvMsg = A2T(szRecvBuf);
	CString strInfo = _T("");
	
	//2019-11-17 客户端:内容
	CString strShow = dlg->CatShowString(strInfo,strRecvMsg);
	dlg->m_list.AddString(strShow);
	
	CAsyncSocket::OnReceive(nErrorCode);
}
