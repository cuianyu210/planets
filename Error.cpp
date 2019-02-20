// Error.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "Error.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CError dialog


CError::CError(CWnd* pParent /*=NULL*/)
	: CDialog(CError::IDD, pParent)
{
	//{{AFX_DATA_INIT(CError)
	m_sMessage = _T("");
	//}}AFX_DATA_INIT
}


void CError::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CError)
	DDX_Text(pDX, IDC_ERR_MESSAGE, m_sMessage);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CError, CDialog)
	//{{AFX_MSG_MAP(CError)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CError message handlers

int CError::ShowError(CString mes)
{
	m_sMessage = mes;
	DoModal();
	return 1;
}
