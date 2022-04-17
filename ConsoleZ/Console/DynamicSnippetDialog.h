#pragma once

class CDynamicSnippetDialog
	: public CDynamicDialogImpl<CDynamicSnippetDialog>
	, public CWinDataExchange<CDynamicSnippetDialog>
{
public:
	// Message map
	BEGIN_MSG_MAP(CDynamicSnippetDialog)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
		COMMAND_RANGE_CODE_HANDLER(ID_SNIPPET_ID_FIRST, ID_SNIPPET_ID_LAST, EN_CHANGE, OnTextChange)
		COMMAND_ID_HANDLER(IDC_SNIPPET_INFORMATION, OnCheckboxClicked)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_COMMAND, OnCommand)
		CHAIN_MSG_MAP(CDynamicDialogImpl<CDynamicSnippetDialog>)
	END_MSG_MAP()

	BEGIN_DDX_MAP(CDynamicDialog)
		DDX_CHECK(IDC_SNIPPET_INFORMATION, m_bShowInformation);
		for( size_t i = 0; i < m_DDXText.size(); ++i )
		{
			DDX_TEXT(static_cast<WORD>(i + ID_SNIPPET_ID_FIRST), m_DDXText[i]);
		}
	END_DDX_MAP()

	CDynamicSnippetDialog(const std::shared_ptr<Snippet> snippet)
		: CDynamicDialogImpl<CDynamicSnippetDialog>(snippet->header().title.c_str(), DS_SETFONT | DS_MODALFRAME | WS_POPUP | WS_CAPTION, 0, nullptr, 8, L"MS Shell Dlg")
		, m_snippet(snippet)
		, m_bInitialized(false)
		, m_rectShowInformation()
		, m_rectHideInformation()
	{
		const int iLabelWidth    = 50;
		const int iLabelHeight   = 10;
		const int iTextBoxWidth  = 100;
		const int iTextBoxHeight = 14;
		const int iResultHeight  = 42;
		const int iMarginWidth   = 5;
		const int iMarginHeight  = 5;
		const int iButtonWidth   = 50;
		const int iButtonHeight  = 14;

		const int iLabelPaddingHeight   = (iLabelHeight >= iTextBoxHeight) ? 0 : (iTextBoxHeight - iLabelHeight) / 2;
		const int iTextBoxPaddingHeight = (iTextBoxHeight >= iLabelHeight) ? 0 : (iLabelHeight - iTextBoxHeight) / 2;

		CRect rect(
			0, 0,
			iMarginWidth + iLabelWidth + iMarginWidth + iTextBoxWidth + iMarginWidth,
			iMarginHeight);

		WORD wEditControlId = ID_SNIPPET_ID_FIRST;

		for( auto declaration = m_snippet->declarations().begin();
		     declaration != m_snippet->declarations().end();
		     ++declaration )
		{
			this->AddDlgControl(
				MAKEINTRESOURCE(0x0082),
				(*declaration)->id.c_str(),
				ES_RIGHT, 0,
				CRect(
					iMarginWidth,
					rect.bottom + iLabelPaddingHeight + 1,
					iMarginWidth + iLabelWidth,
					rect.bottom + iLabelPaddingHeight + iLabelHeight),
				static_cast<WORD>(IDC_STATIC));

			this->AddEdit(
				(*declaration)->default.c_str(),
				CRect(
					iMarginWidth + iLabelWidth + iMarginWidth,
					rect.bottom + iTextBoxPaddingHeight + 1,
					iMarginWidth + iLabelWidth + iMarginWidth + iTextBoxWidth,
					rect.bottom + iTextBoxPaddingHeight + iTextBoxHeight),
				wEditControlId);

			rect.bottom += (max(iLabelHeight, iTextBoxHeight) + iMarginHeight);

			if( wEditControlId == ID_SNIPPET_ID_LAST ) break;
			wEditControlId++;
		}

		// result area
		this->AddDlgControl(
			MAKEINTRESOURCE(0x0081),
			m_snippet->code().raw.c_str(),
			ES_MULTILINE | ES_CENTER | ES_AUTOVSCROLL | ES_READONLY | WS_BORDER, 0,
			CRect(
				iMarginWidth,
				rect.bottom + 1,
				iMarginWidth + iLabelWidth + iMarginWidth + iTextBoxWidth,
				rect.bottom + iResultHeight),
			IDC_SNIPPET_RESULT);

		rect.bottom += (iResultHeight + iMarginHeight);

		// ok/cancel buttons
		this->AddDlgControl(
			MAKEINTRESOURCE(0x0080),
			Helpers::LoadStringW(IDOK).c_str(),
			BS_DEFPUSHBUTTON, 0,
			CRect(
				rect.right - iMarginWidth - iButtonWidth,
				rect.bottom + 1,
				rect.right - iMarginWidth,
				rect.bottom + iButtonHeight),
			IDOK);

		this->AddDlgControl(
			MAKEINTRESOURCE(0x0080),
			Helpers::LoadStringW(IDCANCEL).c_str(),
			0, 0,
			CRect(
				rect.right - iMarginWidth - iButtonWidth - iMarginWidth - iButtonWidth,
				rect.bottom + 1,
				rect.right - iMarginWidth - iButtonWidth - iMarginWidth,
				rect.bottom + iButtonHeight),
			IDCANCEL);

		rect.bottom += (iButtonHeight + iMarginHeight);

		// checkbox snippet information
		this->AddDlgControl(
			MAKEINTRESOURCE(0x0080),
			Helpers::LoadStringW(IDC_SNIPPET_INFORMATION).c_str(),
			BS_AUTOCHECKBOX, 0,
			CRect(
				iMarginWidth,
				rect.bottom + 1,
				iMarginWidth + iLabelWidth + iMarginWidth + iTextBoxWidth,
				rect.bottom + iLabelHeight),
			IDC_SNIPPET_INFORMATION);

		rect.bottom += (iLabelHeight + iMarginHeight);

		m_rectHideInformation = rect;

		// author
		this->AddDlgControl(
			MAKEINTRESOURCE(0x0082),
			Helpers::LoadStringW(IDS_SNIPPET_AUTHOR).c_str(),
			ES_LEFT, 0,
			CRect(
				iMarginWidth,
				rect.bottom + 1,
				iMarginWidth + iLabelWidth + iMarginWidth + iTextBoxWidth - 20,
				rect.bottom + iLabelHeight),
			static_cast<WORD>(IDC_STATIC));

		// author email
		this->AddDlgControl(
			MAKEINTRESOURCE(0x0082),
			L"\u2709",
			0, 0,
			CRect(
				iMarginWidth + iLabelWidth + iMarginWidth + iTextBoxWidth - 29,
				rect.bottom + 1,
				iMarginWidth + iLabelWidth + iMarginWidth + iTextBoxWidth - 20,
				rect.bottom + iLabelHeight),
			IDC_SNIPPET_AUTHOR_EMAIL);

		// author URL
		this->AddDlgControl(
			MAKEINTRESOURCE(0x0082),
			L"www",
			0 , 0,
			CRect(
				iMarginWidth + iLabelWidth + iMarginWidth + iTextBoxWidth - 19,
				rect.bottom + 1,
				iMarginWidth + iLabelWidth + iMarginWidth + iTextBoxWidth,
				rect.bottom + iLabelHeight),
			IDC_SNIPPET_AUTHOR_URL);

		rect.bottom += (iLabelHeight + iMarginHeight);

		this->AddDlgControl(
			MAKEINTRESOURCE(0x0081),
			m_snippet->header().author.c_str(),
			ES_READONLY | WS_BORDER, 0,
			CRect(
				iMarginWidth,
				rect.bottom + 1,
				iMarginWidth + iLabelWidth + iMarginWidth + iTextBoxWidth,
				rect.bottom + iTextBoxHeight),
			static_cast<WORD>(IDC_STATIC));

		rect.bottom += (iTextBoxHeight + iMarginHeight);

		// description
		this->AddDlgControl(
			MAKEINTRESOURCE(0x0082),
			Helpers::LoadStringW(IDS_SNIPPET_DESCRIPTION).c_str(),
			ES_LEFT, 0,
			CRect(
				iMarginWidth,
				rect.bottom + 1,
				iMarginWidth + iLabelWidth + iMarginWidth + iTextBoxWidth,
				rect.bottom + iLabelHeight),
			static_cast<WORD>(IDC_STATIC));

		rect.bottom += (iLabelHeight + iMarginHeight);

		this->AddDlgControl(
			MAKEINTRESOURCE(0x0081),
			m_snippet->header().description.c_str(),
			ES_MULTILINE | ES_READONLY | WS_BORDER, 0,
			CRect(
				iMarginWidth,
				rect.bottom + 1,
				iMarginWidth + iLabelWidth + iMarginWidth + iTextBoxWidth,
				rect.bottom + iResultHeight),
			static_cast<WORD>(IDC_STATIC));

		rect.bottom += (iResultHeight + iMarginHeight);

		// version
		this->AddDlgControl(
			MAKEINTRESOURCE(0x0082),
			Helpers::LoadStringW(IDS_SNIPPET_VERSION).c_str(),
			ES_LEFT, 0,
			CRect(
				iMarginWidth,
				rect.bottom + 1,
				iMarginWidth + iLabelWidth + iMarginWidth + iTextBoxWidth,
				rect.bottom + iLabelHeight),
			static_cast<WORD>(IDC_STATIC));

		rect.bottom += (iLabelHeight + iMarginHeight);

		this->AddDlgControl(
			MAKEINTRESOURCE(0x0081),
			m_snippet->header().version.c_str(),
			ES_READONLY | WS_BORDER, 0,
			CRect(
				iMarginWidth,
				rect.bottom + 1,
				iMarginWidth + iLabelWidth + iMarginWidth + iTextBoxWidth,
				rect.bottom + iTextBoxHeight),
			static_cast<WORD>(IDC_STATIC));

		rect.bottom += (iTextBoxHeight + iMarginHeight);

		// snippet code
		this->AddDlgControl(
			MAKEINTRESOURCE(0x0082),
			Helpers::LoadStringW(IDS_SNIPPET_CODE).c_str(),
			ES_LEFT, 0,
			CRect(
				iMarginWidth,
				rect.bottom + 1,
				iMarginWidth + iLabelWidth + iMarginWidth + iTextBoxWidth - 40,
				rect.bottom + iLabelHeight),
			static_cast<WORD>(IDC_STATIC));

		// snippet code edit
		this->AddDlgControl(
			MAKEINTRESOURCE(0x0082),
			Helpers::LoadStringW(IDC_SNIPPET_EDIT).c_str(),
			ES_RIGHT, 0,
			CRect(
				iMarginWidth + iLabelWidth + iMarginWidth + iTextBoxWidth - 39,
				rect.bottom + 1,
				iMarginWidth + iLabelWidth + iMarginWidth + iTextBoxWidth,
				rect.bottom + iLabelHeight),
			IDC_SNIPPET_EDIT);

		rect.bottom += (iLabelHeight + iMarginHeight);
		this->AddDlgControl(
			MAKEINTRESOURCE(0x0081),
			m_snippet->code().raw.c_str(),
			ES_MULTILINE | ES_CENTER | ES_AUTOVSCROLL | ES_READONLY | WS_BORDER, 0,
			CRect(
				iMarginWidth,
				rect.bottom + 1,
				iMarginWidth + iLabelWidth + iMarginWidth + iTextBoxWidth,
				rect.bottom + iResultHeight),
			static_cast<WORD>(IDC_STATIC));

		rect.bottom += (iResultHeight + iMarginHeight);

		m_rectShowInformation = rect;

		this->ResizeDialog(m_rectHideInformation);
	}

	bool AddEdit(ATL::_U_STRINGorID caption, LPRECT pRect, WORD wId)
	{
		if( AddDlgControl(MAKEINTRESOURCE(0x0081), caption, ES_LEFT | ES_AUTOHSCROLL | WS_BORDER | WS_TABSTOP, 0, pRect, wId) )
		{
			m_DDXText.push_back(static_cast<wchar_t*>(nullptr));
			return true;
		}

		return false;
	}

	const CString GetResult(void) const
	{
		return m_result;
	}

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		m_tooltip.Create(m_hWnd, NULL, NULL, TTS_ALWAYSTIP | TTS_NOPREFIX | TTS_USEVISUALSTYLE);

		ATLVERIFY(m_tooltip.m_hWnd != nullptr);

		m_tooltip.SetMaxTipWidth( 0 );
		m_tooltip.Activate( TRUE );

		m_tooltip.SetDelayTime(TTDT_INITIAL, 1000);
		m_tooltip.SetDelayTime(TTDT_AUTOPOP, 5000);
		m_tooltip.SetDelayTime(TTDT_RESHOW,  20000);

		WORD wEditControlId = ID_SNIPPET_ID_FIRST;
		for( auto declaration = m_snippet->declarations().begin();
		     declaration != m_snippet->declarations().end();
		     ++declaration )
		{
			// This creates a tool tip for the id's control
			CToolInfo toolInfo(
				TTF_IDISHWND | TTF_SUBCLASS,
				GetDlgItem(wEditControlId), 0,
				nullptr,
				const_cast<wchar_t *>((*declaration)->toolTip.c_str()));

			m_tooltip.AddTool(&toolInfo);

			if( wEditControlId == ID_SNIPPET_ID_LAST ) break;
			wEditControlId++;
		}

		DoDataExchange(DDX_SAVE);
		FormatResult();

		if( !m_snippet->header().authorEmail.empty() )
		{
			m_linkAuthorEmail.SubclassWindow(GetDlgItem(IDC_SNIPPET_AUTHOR_EMAIL));
			m_linkAuthorEmail.SetHyperLinkExtendedStyle(HLINK_UNDERLINEHOVER);
			m_linkAuthorEmail.SetHyperLink((std::wstring(L"mailto:") + m_snippet->header().authorEmail + std::wstring(L"?Subject=[ConsoleZ snippet]%20") + m_snippet->header().title + std::wstring(L"%20version%20") + m_snippet->header().version).c_str());
		}
		else
		{
			CWindow(GetDlgItem(IDC_SNIPPET_AUTHOR_EMAIL)).EnableWindow(FALSE);
		}

		if( !m_snippet->header().authorUrl.empty() )
		{
			m_linkAuthorUrl.SubclassWindow(GetDlgItem(IDC_SNIPPET_AUTHOR_URL));
			m_linkAuthorUrl.SetHyperLinkExtendedStyle(HLINK_UNDERLINEHOVER);
			m_linkAuthorUrl.SetHyperLink(m_snippet->header().authorUrl.c_str());
		}
		else
		{
			CWindow(GetDlgItem(IDC_SNIPPET_AUTHOR_URL)).EnableWindow(FALSE);
		}

		m_linkEdit.SubclassWindow(GetDlgItem(IDC_SNIPPET_EDIT));
		m_linkEdit.SetHyperLinkExtendedStyle(HLINK_UNDERLINEHOVER | HLINK_COMMANDBUTTON);
		m_linkEdit.SetToolTipText(m_snippet->file()->fullFileName().c_str());

		// Center the dialog in the parent window
		CenterWindow(GetParent());

		m_bInitialized = true;

		bHandled = FALSE;
		return 0;
	}

	LRESULT OnCloseCmd(UINT, int, HWND, BOOL& bHandled)
	{
		DoDataExchange(DDX_SAVE);

		bHandled = FALSE;
		return 0;
	}

	LRESULT OnTextChange(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if( m_bInitialized == false ) return 0;

		CWindow(GetDlgItem(wID)).GetWindowText(m_DDXText[wID - ID_SNIPPET_ID_FIRST]);

		FormatResult();

		return 0;
	}

	LRESULT OnCheckboxClicked(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		DoDataExchange(DDX_SAVE);

		CRect rect = m_bShowInformation ? m_rectShowInformation : m_rectHideInformation;
		MapDialogRect(&rect);

		ResizeClient(rect.Width(), rect.Height(), TRUE);

		return 0;
	}

	LRESULT OnMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		if( m_tooltip.IsWindow() )
			m_tooltip.RelayEvent((LPMSG)GetCurrentMessage());

		bHandled = FALSE;
		return 0;
	}

	LRESULT OnCommand(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
	{
		if( LOWORD(wParam) == IDC_SNIPPET_EDIT )
		{
			SHELLEXECUTEINFO shExeInfo = { sizeof(SHELLEXECUTEINFO), 0, 0, L"edit", m_snippet->file()->fullFileName().c_str(), 0, 0, SW_SHOWNORMAL, 0, 0, 0, 0, 0, 0, 0 };
			::ShellExecuteEx(&shExeInfo);
		}
		else
		{
			bHandled = FALSE;
		}
		return 0;
	}

private:
	void FormatResult(void)
	{
		m_result = m_snippet->code().raw.c_str();

		for( size_t i = 0; i < m_snippet->declarations().size(); ++i )
		{
			m_result.Replace((m_snippet->code().delimiter + m_snippet->declarations()[i]->id + m_snippet->code().delimiter).c_str(), m_DDXText[i]);
		}

		CWindow(GetDlgItem(IDC_SNIPPET_RESULT)).SetWindowText(m_result);
	}

private:
	const std::shared_ptr<Snippet> m_snippet;
	std::vector<CString>           m_DDXText;
	CString                        m_result;
	bool                           m_bInitialized;
	bool                           m_bShowInformation;
	WTL::CToolTipCtrl              m_tooltip;
	CRect                          m_rectShowInformation;
	CRect                          m_rectHideInformation;
	CHyperLink                     m_linkAuthorEmail;
	CHyperLink                     m_linkAuthorUrl;
	CHyperLink                     m_linkEdit;
};
