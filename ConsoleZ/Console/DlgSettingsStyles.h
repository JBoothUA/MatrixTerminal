
#pragma once

#include "DlgSettingsBase.h"

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

class DlgSettingsStyles
	: public DlgSettingsBase
{
	public:

		DlgSettingsStyles(CComPtr<IXMLDOMElement>& pOptionsRoot);

		BEGIN_DDX_MAP(DlgSettingsStyles)
			DDX_CHECK(IDC_CHECK_STYLE_CAPTION, m_stylesSettings.bCaption)
			DDX_CHECK(IDC_CHECK_STYLE_RESIZABLE, m_stylesSettings.bResizable)
			DDX_CHECK(IDC_CHECK_STYLE_BORDER, m_stylesSettings.bBorder)
			DDX_CHECK(IDC_CHECK_STYLE_TASKBAR, m_stylesSettings.bTaskbarButton)
			DDX_CHECK(IDC_CHECK_STYLE_TRAY, m_stylesSettings.bTrayIcon)
			DDX_CHECK(IDC_CHECK_STYLE_QUAKE, m_stylesSettings.bQuake)
			DDX_CHECK(IDC_CHECK_USE_JUMPLIST, m_stylesSettings.bJumplist)
			DDX_CHECK(IDC_CHECK_INTEGRATED_IME, m_stylesSettings.bIntegratedIME)
			DDX_CHECK(IDC_CHECK_HIDE_WHEN_INACTIVE, m_stylesSettings.bHideWhenInactive)
			DDX_CHECK(IDC_CHECK_PER_MONITOR_DPI, m_stylesSettings.bPerMonitorDpi)
			DDX_CHECK(IDC_CHECK_KEEP_VIEW_THEME, m_stylesSettings.bKeepViewTheme)
			DDX_UINT(IDC_INSIDE_BORDER, m_stylesSettings.dwInsideBorder)
			DDX_UINT(IDC_SPLIT_BAR_SIZE, m_stylesSettings.dwSplitBarSize)
			DDX_UINT(IDC_QUAKE_ANIMATION_TIME, m_stylesSettings.dwQuakeAnimationTime)
		END_DDX_MAP()

		BEGIN_MSG_MAP(DlgSettingsStyles)
			MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
			MESSAGE_HANDLER(WM_CTLCOLORSTATIC, OnCtlColorStatic)
			COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
			COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
			COMMAND_HANDLER(IDC_CHECK_STYLE_QUAKE, BN_CLICKED, OnClickedQuake)
			COMMAND_HANDLER(IDC_SELECTION_COLOR, BN_CLICKED, OnClickedSelColor)
			COMMAND_HANDLER(IDC_HIGHLIGHT_COLOR, BN_CLICKED, OnClickedHiColor)
		END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//		LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//		LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//		LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

		LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
		LRESULT OnCtlColorStatic(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

		LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
		LRESULT OnClickedQuake(WORD /*wNotifyCode*/, WORD /*wID*/, HWND hWndCtl, BOOL& /*bHandled*/);
		LRESULT OnClickedSelColor(WORD /*wNotifyCode*/, WORD /*wID*/, HWND hWndCtl, BOOL& /*bHandled*/);
		LRESULT OnClickedHiColor(WORD /*wNotifyCode*/, WORD /*wID*/, HWND hWndCtl, BOOL& /*bHandled*/);

	private:

		void EnableQuakeControls();

	private:

		StylesSettings        m_stylesSettings;
};

//////////////////////////////////////////////////////////////////////////////
