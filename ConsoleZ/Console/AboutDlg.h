// aboutdlg.h : interface of the CAboutDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

class CAboutDlg :
#ifdef _USE_AERO
  public aero::CDialogImpl<CAboutDlg>
#else
  public CDialogImpl<CAboutDlg>
#endif
{
public:
	enum { IDD = IDD_ABOUTBOX };

	BEGIN_MSG_MAP(CAboutDlg)
#ifdef _USE_AERO
    CHAIN_MSG_MAP(aero::CDialogImpl<CAboutDlg>)
		MESSAGE_HANDLER(WM_TIMER, OnTimer)
#endif
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
		COMMAND_HANDLER(IDC_BTN_HOME_PAGE, BN_CLICKED, OnClickedBtnHomePage)
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnClickedBtnHomePage(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		::ShellExecute(NULL, L"open", L"https://github.com/cbucher/console", NULL, NULL, SW_SHOWNORMAL);
		return 0;
	}

#ifdef _USE_AERO
	LRESULT OnTimer(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		CWindow staticMessage(GetDlgItem(IDC_STATIC));
		CRect rectVersion;
		staticMessage.GetWindowRect(rectVersion);
		ScreenToClient(rectVersion);

		InvalidateRect(rectVersion, FALSE);
		UpdateWindow();
		return 0;
	}

	//generate the palette
	unsigned char ColorR[256];
	unsigned char ColorG[256];
	unsigned char ColorB[256];
	unsigned char ColorA[256];

	unsigned char plasma[256][256];

	CAboutDlg()
	{
		for( int x = 0; x < 256; x++ )
		{
			ColorR[x] = 255;
			ColorG[x] = static_cast<unsigned char>(128.0 + 127.0 * cos(3.1415 * x / 128.0));
			ColorB[x] = static_cast<unsigned char>(128.0 + 127.0 * sin(3.1415 * x / 128.0));
			ColorA[x] = static_cast<unsigned char>(160.0 -  32.0 * sin(3.1415 * x / 32.0));
		}

		for( int y = 0; y < 256; y++ )
			for( int x = 0; x < 256; x++ )
			{
				plasma[y][x] = 128 +
				               static_cast<unsigned char>(32.0 * (sin(x / 16.0) +
				                                                  sin(y / 32.0) +
				                                                  sin(sqrt((x - 128.0) * (x - 128.0) + (y - 128.0) * (y - 128.0)) / 8.0) +
				                                                  sin(sqrt(x * x + y * y) / 8.0)
				                                                 ) );
			}
	}

	CBitmap m_bmIcon;

  void Paint(CDCHandle dc, RECT& rClient, RECT& rView, RECT& rDest)
  {
    aero::CDialogImpl<CAboutDlg>::Paint(dc, rClient, rView, rDest);

    CPaintDC(*this);
    Gdiplus::Graphics gr(dc);

    //create a bitmap from the ICONINFO so we can access the bitmapData
    Gdiplus::Bitmap bmpIcon(m_bmIcon, NULL);
    Gdiplus::Rect rectBounds(0, 0, bmpIcon.GetWidth(), bmpIcon.GetHeight() );

    //get the BitmapData
    Gdiplus::BitmapData bmData;
    bmpIcon.LockBits(&rectBounds, Gdiplus::ImageLockModeRead,
                     bmpIcon.GetPixelFormat(), &bmData);

    // create a new 32 bit bitmap using the bitmapData
    Gdiplus::Bitmap bmpIconAlpha(bmData.Width, bmData.Height, bmData.Stride,
                                 PixelFormat32bppARGB, (BYTE*)bmData.Scan0);
    bmpIcon.UnlockBits(&bmData);

    CWindow staticMessage(GetDlgItem(IDC_STATIC));
    CRect rectVersion;
    staticMessage.GetWindowRect(rectVersion);
    ScreenToClient(rectVersion);

		Gdiplus::Bitmap bmpPlasma(rectVersion.Width(), rectVersion.Height(), PixelFormat32bppARGB);
		Gdiplus::Rect rectPlasmaBounds(0, 0, bmpPlasma.GetWidth(), bmpPlasma.GetHeight());
		Gdiplus::BitmapData bmdPlasma;
		bmpPlasma.LockBits(&rectPlasmaBounds, Gdiplus::ImageLockModeWrite,
		                   bmpPlasma.GetPixelFormat(), &bmdPlasma);

		unsigned char * dest = static_cast<unsigned char *>(bmdPlasma.Scan0);

		DWORD paletteShift = ::GetTickCount() / 16;

		for( int ypos = 0; ypos < rectVersion.Height(); ++ypos )
		{
			unsigned char * startdest = dest;

			for( int xpos = 0; xpos < rectVersion.Width(); ++xpos )
			{
				DWORD X = ((xpos + ColorG[(ypos + paletteShift) & 0xff]) / 2) & 0xff;
				DWORD Y = ((ypos + ColorG[(xpos + paletteShift) & 0xff]) / 2) & 0xff;
				DWORD color = static_cast<DWORD>(plasma[X][Y] + paletteShift) & 0xff;
				// ARGB little endian
				*dest++ = ColorB[color]; // blue
				*dest++ = ColorG[color]; // green
				*dest++ = ColorR[color]; // red
				*dest++ = ColorA[color]; // alpha
			}

			dest = startdest + bmdPlasma.Stride;
		}

		bmpPlasma.UnlockBits(&bmdPlasma);

    INT len = min(rectVersion.Width(), rectVersion.Height());
    Gdiplus::Rect rect2(
      rectVersion.left + (rectVersion.Width() - len) / 2,
      rectVersion.top  + (rectVersion.Height() - len),
      len, len);

    gr.DrawImage(
      &bmpIconAlpha,
      rect2,
      0, 0,
      bmpIconAlpha.GetWidth(), bmpIconAlpha.GetHeight(),
      Gdiplus::Unit::UnitPixel);

		gr.DrawImage(
			&bmpPlasma,
			rectVersion.left, rectVersion.top,
			0, 0,
			bmdPlasma.Width, bmdPlasma.Height,
			Gdiplus::Unit::UnitPixel);

	INT flatLen = rectVersion.Height() / 2;

    Gdiplus::SolidBrush brush(Gdiplus::Color(200,0,0,0));
	gr.FillRectangle(
		&brush,
		Gdiplus::Rect(
			rectVersion.left, rectVersion.top,
			rectVersion.Width(), flatLen));

	Gdiplus::LinearGradientBrush linGrBrush(
		Gdiplus::Point(0, rectVersion.top + flatLen - 1),
		Gdiplus::Point(0, rectVersion.bottom),
		Gdiplus::Color(200,0,0,0),
		Gdiplus::Color(64,0,0,0));
	gr.FillRectangle(
		&linGrBrush,
		Gdiplus::Rect(
			rectVersion.left, rectVersion.top + flatLen,
			rectVersion.Width(), rectVersion.Height() - flatLen));

    DTTOPTS dtto   = { 0 };
    dtto.dwSize    = sizeof(DTTOPTS);
    dtto.iGlowSize = 16;
    dtto.crText    = RGB(240,240,240);
    dtto.dwFlags   = DTT_COMPOSITED | DTT_TEXTCOLOR | DTT_GLOWSIZE;

    std::wstring strMsgVersion = boost::str(boost::wformat(Helpers::LoadStringW(MSG_ABOUT)) % _T(VERSION_PRODUCT));

    ::SelectObject(dc, AtlGetDefaultGuiFont());
    this->DrawTextW(dc, strMsgVersion.c_str(), rectVersion, DT_CENTER, dtto);
  }

#endif
};
