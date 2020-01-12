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

void CMySocket::OnConnect(int nErrorCode)	//Alt+G   VA  查看函数申明
{
	TRACE("####OnConnect");
	CMFCChatClientDlg* dlg = (CMFCChatClientDlg*)AfxGetApp()->GetMainWnd();
	CString strShow;
	CString strMsg = _T("与服务器连接成功");
	CString strInfo = _T("");
	strShow = dlg->CatShowString(strInfo, strMsg);
	dlg->m_list.AddString(strShow);
	CAsyncSocket::OnConnect(nErrorCode);
}

void CMySocket::OnReceive(int nErrorCode)
{
	TRACE("####CMySocket OnReceive");
	//1 接收数据到szRecvBuf
	CMFCChatClientDlg* dlg = (CMFCChatClientDlg*)AfxGetApp()->GetMainWnd();
	char szRecvBuf[SEND_MAX_BUF] = { 0 };
	Receive(szRecvBuf, SEND_MAX_BUF, 0);
	TRACE("####Server szRecvBuf=%s", szRecvBuf);

	//2 显示buf
	USES_CONVERSION;
	CString strMsg = A2T(szRecvBuf);
	CString strInfo = _T("服务端: ");
	CString strShow;
	strShow = dlg->CatShowString(strInfo, strMsg);
	dlg->m_list.AddString(strShow);

	//	选中单选框按钮
	if (((CButton*)dlg->GetDlgItem(IDC_AUTOSEND_CHECK))->GetCheck()) {
		//自动回复
		//1 读编辑框的内容
		CString strAutoSendMsg;
		dlg->GetDlgItemText(IDC_AUTOSENDMSG_EDIT, strAutoSendMsg);
		//2 封包+组格式  时间+昵称+[自动回复]+内容,要发送给服务器的消息
		CString strName;
		CString strAutoShow;
	
		dlg->GetDlgItemText(IDC_NAME_EDIT, strName);
		strName += _T("[自动回复] ");
		strAutoShow = dlg->CatShowString(strName, strAutoSendMsg);
		strAutoSendMsg = strName + strAutoSendMsg;

		char* szSendBuf = T2A(strAutoSendMsg);
		Send(szSendBuf, SEND_MAX_BUF, 0);

		dlg->m_list.AddString(strAutoShow);
		dlg->UpdateData(FALSE);
	}


	


	CAsyncSocket::OnReceive(nErrorCode);
}
