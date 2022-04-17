
#pragma once

#include "DlgSettingsBase.h"

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

class DlgSettingsControls
	: public DlgSettingsBase
{
	public:

		DlgSettingsControls(CComPtr<IXMLDOMElement>& pOptionsRoot);

		BEGIN_DDX_MAP(DlgSettingsControls)
			DDX_CHECK(IDC_CHECK_SHOW_MENU, m_controlsSettings.ShowMenu())
			DDX_CHECK(IDC_CHECK_SHOW_TOOLBAR, m_controlsSettings.ShowToolbar())
			DDX_CHECK(IDC_CHECK_SHOW_SEARCH_BAR, m_controlsSettings.ShowSearchbar())
			DDX_CHECK(IDC_CHECK_SHOW_STATUS, m_controlsSettings.ShowStatusbar())
			DDX_CHECK(IDC_CHECK_SHOW_TABS, m_controlsSettings.ShowTabs())
			DDX_CHECK(IDC_CHECK_HIDE_SINGLE_TAB, m_controlsSettings.HideSingleTab())
			DDX_CHECK(IDC_CHECK_TABS_ON_BOTTOM, m_controlsSettings.TabsOnBottom())
			DDX_CHECK(IDC_CHECK_SHOW_SCROLLBARS, m_controlsSettings.ShowScrollbars())
			DDX_CHECK(IDC_CHECK_HIDE_TAB_ICONS, m_controlsSettings.HideTabIcons())
			DDX_CHECK(IDC_CHECK_HIDE_TAB_CLOSE_BUTTON, m_controlsSettings.HideTabCloseButton())
			DDX_CHECK(IDC_CHECK_HIDE_TAB_NEW_BUTTON, m_controlsSettings.HideTabNewButton())
		END_DDX_MAP()

		BEGIN_MSG_MAP(DlgSettingsControls)
			MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
			COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
			COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
			COMMAND_HANDLER(IDC_CHECK_SHOW_TABS, BN_CLICKED, OnClickedShowTabs)
			NOTIFY_CODE_HANDLER(TCN_SELCHANGE, OnTabItemChanged)
		END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//		LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//		LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//		LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

		LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

		LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
		LRESULT OnClickedShowTabs(WORD /*wNotifyCode*/, WORD /*wID*/, HWND hWndCtl, BOOL& /*bHandled*/);
		LRESULT OnTabItemChanged(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/);

	private:

		void EnableTabControls();

	private:

		CTabCtrl              m_tabCtrl;

		ControlsSettings      m_controlsSettings;
};

//////////////////////////////////////////////////////////////////////////////
