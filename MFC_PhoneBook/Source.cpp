#include <afxwin.h>
#include "PhoneBook.h"
#include "resource.h"

class CMainDlg : public CDialog {
public:
    enum { IDD = IDD_MAIN_DLG };

    CMainDlg();
    ~CMainDlg();
    DECLARE_MESSAGE_MAP()
    afx_msg void InsertNewRecordInDB();
};

CMainDlg::CMainDlg() :CDialog(CMainDlg::IDD) {}
CMainDlg::~CMainDlg() {}

class CMainApp : public CWinApp {
    BOOL InitInstance() {
        CMainDlg myDlg;
        m_pMainWnd = &myDlg;
        myDlg.DoModal();
        return TRUE;
    }
};

CMainApp theApp; 
BEGIN_MESSAGE_MAP(CMainDlg, CDialog)
    ON_BN_CLICKED(IDC_BUTTON1, &CMainDlg::InsertNewRecordInDB)
END_MESSAGE_MAP()


string ConvertCString2String(CString cstring) {
    CT2A ct(cstring);
    string str(ct);
    return str;
}

void CMainDlg::InsertNewRecordInDB()
{
    CString CPhone, CName;
    GetDlgItemText(IDC_EDIT2, CPhone);
    GetDlgItemText(IDC_EDIT1, CName);

    string phone = ConvertCString2String(CPhone);
    string name = ConvertCString2String(CName);

    PhoneBook::flush(name, phone);
    MessageBox(L"Новая запись успешно добавлена",L"Phone Book");
}

