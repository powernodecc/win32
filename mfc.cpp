#include "afxwin.h"

class MyApp : public CWinApp {
    BOOL InitInstance() override {
        auto wnd = new CFrameWnd;
        wnd->Create(nullptr, _T("Hello World!1212"));
        wnd->ShowWindow(SW_SHOW);

        m_pMainWnd = wnd;
        return TRUE;
    }
};

//MyApp theApp;