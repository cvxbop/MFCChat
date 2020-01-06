#include "pch.h"
#include "CMySocket.h"
#include "MFCChatClient.h"
#include "MFCChatClientDlg.h"

CMySocket::CMySocket()
{
}

CMySocket::~CMySocket()
{
}

void CMySocket::OnConnect(int nErrorCode)	//Alt+G   VA  �鿴��������
{
	TRACE("####OnConnect");
	CMFCChatClientDlg* dlg = (CMFCChatClientDlg*)AfxGetApp()->GetMainWnd();
	CString strShow;
	CString strMsg = _T("����������ӳɹ�");
	CString strInfo = _T("");
	strShow = dlg->CatShowString(strInfo, strMsg);
	dlg->m_list.AddString(strShow);
	CAsyncSocket::OnConnect(nErrorCode);
}

void CMySocket::OnReceive(int nErrorCode)
{
	TRACE("####CMySocket OnReceive");
	//1 �������ݵ�szRecvBuf
	CMFCChatClientDlg* dlg = (CMFCChatClientDlg*)AfxGetApp()->GetMainWnd();
	char szRecvBuf[SEND_MAX_BUF] = { 0 };
	Receive(szRecvBuf, 200, 0);
	TRACE("####Server szRecvBuf=%s", szRecvBuf);

	//2 ��ʾbuf
	USES_CONVERSION;
	CString strMsg = A2T(szRecvBuf);
	CString strInfo = _T("�����: ");
	CString strShow;
	strShow = dlg->CatShowString(strInfo, strMsg);
	dlg->m_list.AddString(strShow);
	//dlg->UpdateData(FALSE);
	CAsyncSocket::OnReceive(nErrorCode);
}
