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
	//1 �������ݵ�szRecvBuf
	TRACE("####Server OnReceive");
	CMFCChatServerDlg* dlg = (CMFCChatServerDlg*)AfxGetApp()->GetMainWnd();
	char szRecvBuf[MAX_SERVER_BUF] = { 0 };
	Receive(szRecvBuf, MAX_SERVER_BUF, 0);
	TRACE("####Server szRecvBuf=%s", szRecvBuf);

	//2 ��ʾbuf
	USES_CONVERSION;
	CString strRecvMsg = A2T(szRecvBuf);
	CString strInfo = _T("");
	
	//2019-11-17 �ͻ���:����
	CString strShow = dlg->CatShowString(strInfo,strRecvMsg);
	dlg->m_list.AddString(strShow);
	
	CAsyncSocket::OnReceive(nErrorCode);
}
