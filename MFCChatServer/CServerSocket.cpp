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
//�ص�  ΪʲôҪ��д?����������;?
void CServerSocket::OnAccept(int nErrorCode)
{	
	TRACE("####OnAccept");
	CMFCChatServerDlg* dlg = (CMFCChatServerDlg*)AfxGetApp()->GetMainWnd();
	dlg->m_chat = new CChatSocket;
	Accept(*(dlg->m_chat));

	CString strShow;
	CString strMsg= _T("");
	CString strInfo= _T("�ͻ������ӳɹ�");
	strShow = dlg->CatShowString(strInfo, strMsg);
	dlg->m_list.AddString(strShow);
	dlg->UpdateData(FALSE);
	CAsyncSocket::OnAccept(nErrorCode);
}
