#include "pch.h"
#include "CServerSocket.h"
#include "MFCChatServer.h"
#include "MFCChatServerDlg.h"

CServerSocket::CServerSocket()
{
}

CServerSocket::~CServerSocket()
{
}
//回调  为什么要重写?我有特殊用途?
void CServerSocket::OnAccept(int nErrorCode)
{	
	TRACE("####OnAccept");
	CMFCChatServerDlg* dlg = (CMFCChatServerDlg*)AfxGetApp()->GetMainWnd();
	dlg->m_chat = new CChatSocket;
	Accept(*(dlg->m_chat));

	CString strShow;
	CString strMsg= _T("");
	CString strInfo= _T("客户端连接成功");
	strShow = dlg->CatShowString(strInfo, strMsg);
	dlg->m_list.AddString(strShow);
	dlg->UpdateData(FALSE);
	CAsyncSocket::OnAccept(nErrorCode);
}
