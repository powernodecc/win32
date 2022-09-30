#include "mfc.h"

MyApp theApp;

BOOL MyApp::InitInstance() {
    auto frame = new MyFrame();
    frame->Create(nullptr, L"mfc");
    frame->ShowWindow(SW_SHOWNORMAL);
    frame->UpdateWindow();
    m_pMainWnd = frame;
    return TRUE;
}

BEGIN_MESSAGE_MAP(MyFrame, CFrameWnd)
                    ON_WM_LBUTTONDOWN()
                    ON_WM_CHAR()
                    ON_WM_PAINT()
END_MESSAGE_MAP()

MyFrame::MyFrame() = default;


void MyFrame::OnLButtonDown(UINT nHitTest, CPoint point) {
    CString str;
    str.Format(L"x = %d, y = %d", point.x, point.y);
    MessageBox(str);
}

void MyFrame::OnChar(UINT key, UINT, UINT) {
    CString str;
    str.Format(L"%c", key);
    HWND h = ::FindWindow(nullptr, L"计算器");
    if (nullptr == h) {
//        MessageBox(L"nullptr");
    }
//    MessageBox(str);

    CString cs = CString("ccc");
    CStringA tmp(cs);
    char *p = tmp.GetBuffer();
    MessageBox(cs);
}

void MyFrame::OnPaint() {
    CPaintDC dc(this);
    dc.TextOutW(100, 100, L"为了部落");
    dc.Ellipse(10, 10, 100, 100);
}





















