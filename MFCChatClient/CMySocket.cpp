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
	Receive(szRecvBuf, SEND_MAX_BUF, 0);
	TRACE("####Server szRecvBuf=%s", szRecvBuf);

	//2 ��ʾbuf
	USES_CONVERSION;
	CString strMsg = A2T(szRecvBuf);
	CString strInfo = _T("�����: ");
	CString strShow;
	strShow = dlg->CatShowString(strInfo, strMsg);
	dlg->m_list.AddString(strShow);

	//	ѡ�е�ѡ��ť
	if (((CButton*)dlg->GetDlgItem(IDC_AUTOSEND_CHECK))->GetCheck()) {
		//�Զ��ظ�
		//1 ���༭�������
		CString strAutoSendMsg;
		dlg->GetDlgItemText(IDC_AUTOSENDMSG_EDIT, strAutoSendMsg);
		//2 ���+���ʽ  ʱ��+�ǳ�+[�Զ��ظ�]+����,Ҫ���͸�����������Ϣ
		CString strName;
		CString strAutoShow;
	
		dlg->GetDlgItemText(IDC_NAME_EDIT, strName);
		strName += _T("[�Զ��ظ�] ");
		strAutoShow = dlg->CatShowString(strName, strAutoSendMsg);
		strAutoSendMsg = strName + strAutoSendMsg;

		char* szSendBuf = T2A(strAutoSendMsg);
		Send(szSendBuf, SEND_MAX_BUF, 0);

		dlg->m_list.AddString(strAutoShow);
		dlg->UpdateData(FALSE);
	}


	


	CAsyncSocket::OnReceive(nErrorCode);
}
