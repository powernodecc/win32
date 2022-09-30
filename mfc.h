#include "afxwin.h"

class MyApp : public CWinApp {
public:
    BOOL InitInstance() override;
};

// CFrameWnd 窗口框架类
class MyFrame : public CFrameWnd {
DECLARE_MESSAGE_MAP()

public:
    MyFrame();

    afx_msg void OnLButtonDown(UINT nHitTest, CPoint point);

    afx_msg void OnChar(UINT, UINT, UINT);

    afx_msg void OnPaint();
};


