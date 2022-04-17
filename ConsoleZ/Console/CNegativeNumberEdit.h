#pragma once

// /!\ with ES_NUMBER style, you can only enter digits 0 to 9, so we need to modify the behavior to support negative numbers
// but minus sign is supported when you paste tesxt !?!
// and only the pasted text is verified: so you can past -45 into 123 and obtain 1-4523 (epic fail Microsoft!)

namespace WTL
{

class CNegativeNumberEdit: public CWindowImpl<CNegativeNumberEdit, CEdit,CControlWinTraits>
{
public:
	DECLARE_WND_SUPERCLASS(_T("WTL_CNegativeNumberEdit"), CEdit::GetWndClassName())

	BEGIN_MSG_MAP(CNegativeNumberEdit)
		MESSAGE_HANDLER(WM_CREATE,OnCreate)
		MESSAGE_HANDLER(WM_CHAR, OnChar)
#if 0
		MESSAGE_HANDLER(WM_PASTE, OnPaste)
#endif
	END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL& /*bHandled*/)
	{
		LRESULT lRes = DefWindowProc(uMsg,wParam,lParam);
		return lRes;
	}

	LRESULT OnChar(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
	{
		bHandled = FALSE;

		if( wParam == '-' )
		{
			int nStartChar = -1, nEndChar = -1;
			this->GetSel(nStartChar , nEndChar);
			if( nStartChar == 0 )
			{
				CString strText;
				this->GetWindowTextW(strText);
				for( int i = nEndChar; i < strText.GetLength(); ++i )
				{
					if( strText[i] == L'-' )
						return 0;
				}
				this->ReplaceSel(L"-", TRUE);
				bHandled = TRUE;
			}
		}

		return 0;
	}

#if 0
	LRESULT OnPaste(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		bHandled = FALSE;

		if (!IsClipboardFormatAvailable(CF_UNICODETEXT)) return 0;

		if (!OpenClipboard()) return 0;

		HGLOBAL hglb = GetClipboardData(CF_UNICODETEXT);
		if( hglb )
		{
			std::unique_ptr<void, GlobalUnlockHelper> lock(::GlobalLock(hglb));
			if( lock.get() )
			{
				int nStartChar = -1, nEndChar = -1;
				this->GetSel(nStartChar, nEndChar);

				CString strPastedText = static_cast<wchar_t*>(lock.get());

				CString strText;
				this->GetWindowTextW(strText);

				int nIdx = 0;
				bool bSuccess = true;
				for( int i = 0; i < nStartChar; ++i, ++nIdx )
				{
					if( (strText[i] == L'-' && nIdx == 0) || (strText[i] >= L'0' && strText[i] <= L'9') )
						continue;

					bSuccess = false;
					break;
				}

				if( bSuccess )
				{
					for( int i = 0; i < strPastedText.GetLength(); ++i, ++nIdx )
					{
						if( (strPastedText[i] == L'-' && nIdx == 0) || (strPastedText[i] >= L'0' && strPastedText[i] <= L'9') )
							continue;

						bSuccess = false;
						break;
					}
				}

				if( bSuccess )
				{
					for( int i = nEndChar; i < strText.GetLength(); ++i, ++nIdx )
					{
						if( (strText[i] == L'-' && nIdx == 0) || (strText[i] >= L'0' && strText[i] <= L'9') )
							continue;

						bSuccess = false;
						break;
					}
				}

				if( bSuccess )
				{
					this->ReplaceSel(strPastedText, TRUE);
					bHandled = TRUE;
				}
			}
		}

		CloseClipboard();

		return 0;
	}
#endif
};

}; // namespace WTL
