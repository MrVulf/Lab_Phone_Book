#include <afxwin.h>
#include <iostream>
#include "PhoneBook.h"
#include "resource.h"

class CMainDlg : public CDialog {
public:
    enum { IDD = IDD_MAIN_DLG };

    CMainDlg();
    ~CMainDlg();
    DECLARE_MESSAGE_MAP()
    afx_msg void InsertNewRecordInDB();
    afx_msg void FindRecordInDB();
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
    ON_BN_CLICKED(IDC_BUTTON2, &CMainDlg::FindRecordInDB)
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

    try {
        PhoneBook::flush(name, phone);
    }
    catch (std::exception& error) {
        CString message = error.what();
        MessageBox(message, L"ERROR");
        return;
    };
    MessageBox(L"Новая запись успешно добавлена",L"Phone Book");
}

void CMainDlg::FindRecordInDB()
{
    CString CKey;
    GetDlgItemText(IDC_EDIT3, CKey);
    string key = ConvertCString2String(CKey);
    string name, phone;

    int checkRadioButton = GetCheckedRadioButton(IDC_RADIO1, IDC_RADIO2);
    try {
        switch (checkRadioButton) {
        case IDC_RADIO1:
            PhoneBook::findByName(key, &name, &phone);
            break;
        case IDC_RADIO2:
            PhoneBook::findByPhone(key, &name, &phone);
            break;
        default:
            MessageBox(L"Выберите один формат поиска", L"Phone Book");
            return;
        }
    }
    catch (std::exception& error) {
        CString message = error.what();
        MessageBox(message, L"ERROR");
        return;
    };

    string message = "Result:\nNAME   = " + name + "\nPHONE = " + phone + "\n";
    CString CMessage = message.c_str();
    MessageBox(CMessage, L"Phone Book");
}
