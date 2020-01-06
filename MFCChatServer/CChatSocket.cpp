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
	char szRecvBuf[200] = { 0 };
	Receive(szRecvBuf, 200, 0);
	TRACE("####Server szRecvBuf=%s", szRecvBuf);

	//2 ��ʾbuf
	USES_CONVERSION;
	CString strRecvMsg = A2T(szRecvBuf);
	CString strShow = _T("�ͻ���: ");
	CString strTime;
	dlg->m_tm = CTime::GetCurrentTime();
	strTime = dlg->m_tm.Format("%X ");
	//2019-11-17 �ͻ���:����
	strShow = strTime + strShow;
	strShow += strRecvMsg;
	dlg->m_list.AddString(strShow);
	
	CAsyncSocket::OnReceive(nErrorCode);
}
