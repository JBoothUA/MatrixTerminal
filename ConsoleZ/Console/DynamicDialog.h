#pragma once

#ifndef __cplusplus
#error ATL requires C++ compilation (use a .cpp suffix)
#endif

#ifndef __ATLAPP_H__
#error DynamicDialog.h requires atlapp.h to be included first
#endif

#ifndef __ATLWIN_H__
#error DynamicDialog.h requires atlwin.h to be included first
#endif

namespace WTL
{
	template<class T>
	class ATL_NO_VTABLE CDynamicDialogImpl: public CDialogImplBase
	{
	public:
		// Message map for IDOK & IDCANCEL
		BEGIN_MSG_MAP(CDynamicDialogImpl)
			COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
			COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
		END_MSG_MAP()

		CDynamicDialogImpl(ATL::_U_STRINGorID caption, DWORD dwStyle, DWORD dwExStyle, LPRECT pRect, short sFontSize = 0, ATL::_U_STRINGorID fontName = (UINT)0, ATL::_U_STRINGorID menu = (UINT)0, ATL::_U_STRINGorID wndClass = (UINT)0)
			: m_bModal(false)
			, m_memory(nullptr)
			, m_size(0)
			, m_capacity(0)
		{
			ATLASSERT((dwStyle & DS_SHELLFONT) != DS_SHELLFONT);

			if( fontName.m_lpstr )
				dwStyle |= DS_SETFONT;
			else
				dwStyle &= ~DS_SETFONT;

			// Get the size of the template
			size_t size = _CreateDlgTemplate(nullptr, caption, dwStyle, dwExStyle, pRect, sFontSize, fontName, menu, wndClass);

			// Allocate the template buffer
			DLGTEMPLATE* pDlgTemplate = static_cast<DLGTEMPLATE*>(_ExtendMemory(size));
			if( pDlgTemplate )
				// Fill the template buffer
				_CreateDlgTemplate(pDlgTemplate, caption, dwStyle, dwExStyle, pRect, sFontSize, fontName, menu, wndClass);

			/*
			Following the DLGTEMPLATE header in a standard dialog box template are one or more DLGITEMTEMPLATE structures that define the dimensions and style of the controls in the dialog box.
			*/
		}

		virtual ~CDynamicDialogImpl()
		{
			free(m_memory);
		}

		// Add control
		bool AddDlgControl(ATL::_U_STRINGorID wndClass, ATL::_U_STRINGorID caption, DWORD dwStyle, DWORD dwExStyle, LPRECT pRect, WORD wId, short sCreateDataSize = 0, void* pCreateData = NULL)
		{
			ATLASSERT(!pCreateData == !sCreateDataSize);

			// Windows does not support more than 255 controls, create them in OnInitDialog()
			{
				DLGTEMPLATE* pDlgTemplate = GetDlgTemplate();
				ATLASSERT(pDlgTemplate && pDlgTemplate->cdit < 255);
				if( pDlgTemplate && pDlgTemplate->cdit == 255 ) return false;
			}

			// Get the size of the template
			size_t size = _AddDlgControl(nullptr, wndClass, caption, dwStyle, dwExStyle, pRect, wId, sCreateDataSize, pCreateData);

			// Allocate the template buffer
			DLGITEMTEMPLATE* pDlgItemTemplate = static_cast<DLGITEMTEMPLATE*>(_ExtendMemory(size));
			if( pDlgItemTemplate )
			{
				// Fill the template buffer
				_AddDlgControl(pDlgItemTemplate, wndClass, caption, dwStyle, dwExStyle, pRect, wId, sCreateDataSize, pCreateData);

				/*
				The cdit member specifies the number of DLGITEMTEMPLATE structures in the template.
				*/
				DLGTEMPLATE* pDlgTemplate = GetDlgTemplate();
				pDlgTemplate->cdit++;

				return true;
			}

			return false;
		}

		HWND Create(HWND hWndParent = ::GetActiveWindow(), LPARAM dwInitParam = NULL)
		{
			m_bModal	= false;

			HWND retVal = 0;
			DLGTEMPLATE* pDlgTemplate = GetDlgTemplate();
			if (pDlgTemplate)
			{
				// Add window data
				_Module.AddCreateWndData(&m_thunk.cd, static_cast<CDialogImplBase*>(this));

				// Display the dialog
				retVal = ::CreateDialogIndirectParam(GetModuleHandle(NULL), pDlgTemplate, hWndParent, T::StartDialogProc, dwInitParam);

				ATLASSERT(m_hWnd == retVal);
			}

			return retVal;
		}

		INT_PTR DoModal(HWND hWndParent = ::GetActiveWindow(), LPARAM dwInitParam = NULL)
		{
			m_bModal = true;

			INT_PTR retVal = 0;
			DLGTEMPLATE* pDlgTemplate = GetDlgTemplate();
			if (pDlgTemplate)
			{
				// Add window data
				_Module.AddCreateWndData(&m_thunk.cd, static_cast<CDialogImplBase*>(this));

				// Display the dialog
				retVal = ::DialogBoxIndirectParam(::GetModuleHandle(NULL), pDlgTemplate, hWndParent, T::StartDialogProc, dwInitParam);

				ATLASSERT(retVal > 0);
			}

			return retVal;
		}

		virtual BOOL DestroyWindow()
		{
			ATLASSERT(::IsWindow(m_hWnd));
			ATLASSERT(!m_bModal);
			return ::DestroyWindow(m_hWnd);
		}

		inline bool IsModal() const { return m_bModal; }
		inline UINT GetControlsCount() const { DLGTEMPLATE* pDlgTemplate = GetDlgTemplate(); return pDlgTemplate ? pDlgTemplate->cdit : 0; }

		void ResizeDialog(LPRECT pRect)
		{
			DLGTEMPLATE* pDlgTemplate = GetDlgTemplate();

			if( pDlgTemplate )
			{
				CRect rect(pRect);
				pDlgTemplate->x               = static_cast<short>(rect.left);
				pDlgTemplate->y               = static_cast<short>(rect.top);
				pDlgTemplate->cx              = static_cast<short>(rect.Width());
				pDlgTemplate->cy              = static_cast<short>(rect.Height());
			}
		}

	private:

		inline DLGTEMPLATE* GetDlgTemplate() const {return static_cast<DLGTEMPLATE*>(m_memory);}

		void EndDialog(INT_PTR iResult)
		{
			ATLASSERT(::IsWindow(m_hWnd));
			if (m_bModal)
				::EndDialog(m_hWnd, iResult);
			else
				DestroyWindow();
		}

		LRESULT OnCloseCmd(UINT, int iId, HWND, BOOL&)
		{
			EndDialog(iId);
			return 0;
		}

	private:
		size_t _CreateDlgTemplate(DLGTEMPLATE* pDlgTemplate,
		                          ATL::_U_STRINGorID caption,
		                          DWORD dwStyle, DWORD dwExStyle,
		                          LPRECT pRect,
		                          short sFontSize, ATL::_U_STRINGorID fontName,
		                          ATL::_U_STRINGorID menu,
		                          ATL::_U_STRINGorID wndClass)
		{
			size_t size  = sizeof(DLGTEMPLATE);
			WORD*  ptr   = nullptr;

			// Set the DLGTEMPLATE data
			if (pDlgTemplate)
			{
				CRect rect(pRect);
				pDlgTemplate->style           = dwStyle;
				pDlgTemplate->dwExtendedStyle = dwExStyle;
				pDlgTemplate->cdit            = 0;
				pDlgTemplate->x               = static_cast<short>(rect.left);
				pDlgTemplate->y               = static_cast<short>(rect.top);
				pDlgTemplate->cx              = static_cast<short>(rect.Width());
				pDlgTemplate->cy              = static_cast<short>(rect.Height());

				// Set the pointer
				ptr = reinterpret_cast<WORD*>(pDlgTemplate + 1);
			}

			/*
			Immediately following the DLGTEMPLATE structure is a menu array that identifies a menu resource for the dialog box.
			If the first element of this array is 0x0000, the dialog box has no menu and the array has no other elements.
			If the first element is 0xFFFF, the array has one additional element that specifies the ordinal value of a menu resource in an executable file.
			If the first element has any other value, the system treats the array as a null-terminated Unicode string that specifies the name of a menu resource in an executable file.
			*/
			size += WriteString(ptr, menu.m_lpstr, true);
			/*
			Following the menu array is a class array that identifies the window class of the control.
			If the first element of the array is 0x0000, the system uses the predefined dialog box class for the dialog box and the array has no other elements.
			If the first element is 0xFFFF, the array has one additional element that specifies the ordinal value of a predefined system window class. 
			f the first element has any other value, the system treats the array as a null-terminated Unicode string that specifies the name of a registered window class. 
			*/
			size += WriteString(ptr, wndClass.m_lpstr, true);
			/*
			Following the class array is a title array that specifies a null-terminated Unicode string that contains the title of the dialog box.
			If the first element of this array is 0x0000, the dialog box has no title and the array has no other elements.
			*/
			size += WriteString(ptr, caption.m_lpstr);

			/*
			The 16-bit point size value and the typeface array follow the title array, but only if the style member specifies the DS_SETFONT style.
			The point size value specifies the point size of the font to use for the text in the dialog box and its controls.
			The typeface array is a null-terminated Unicode string specifying the name of the typeface for the font.
			*/
			if( dwStyle & DS_SETFONT )
			{
				size += 2;
				if( ptr && fontName.m_lpstr )
					*ptr++ = sFontSize;
				size += WriteString(ptr, fontName.m_lpstr);
			}

			// Align the pointer to DWORD
			size_t unalignedSize = size;
			size = (size + 3) & (~3);
			if (ptr) // Add zero-padding
				memset(ptr, 0, size - unalignedSize);

			return size;
		}

		size_t _AddDlgControl(DLGITEMTEMPLATE* pDlgItemTemplate,
		                      ATL::_U_STRINGorID wndClass,
		                      ATL::_U_STRINGorID caption,
		                      DWORD dwStyle, DWORD dwExStyle,
		                      LPRECT pRect,
		                      WORD wId,
		                      short sCreateDataSize, void* pCreateData)
		{
			/*
			Each DLGITEMTEMPLATE structure in the template must be aligned on a DWORD boundary.
			The class and title arrays must be aligned on WORD boundaries.
			The creation data array must be aligned on a WORD boundary.
			*/

			size_t size = sizeof(DLGITEMTEMPLATE);
			WORD*  ptr	= nullptr;

			ATLASSERT(!pCreateData == !sCreateDataSize);

			if (pDlgItemTemplate)
			{
				CRect rect(pRect);
				pDlgItemTemplate->style           = dwStyle | WS_VISIBLE | WS_CHILD;
				pDlgItemTemplate->dwExtendedStyle = dwExStyle;
				pDlgItemTemplate->x               = static_cast<short>(rect.left);
				pDlgItemTemplate->y               = static_cast<short>(rect.top);
				pDlgItemTemplate->cx	              = static_cast<short>(rect.Width());
				pDlgItemTemplate->cy	              = static_cast<short>(rect.Height());
				pDlgItemTemplate->id	              = wId;

				ptr = reinterpret_cast<WORD*>(pDlgItemTemplate + 1);
			}

			/*
			In a standard template for a dialog box, the DLGITEMTEMPLATE structure is always immediately followed by three variable-length arrays specifying
			the class, title, and creation data for the control. Each array consists of one or more 16-bit elements.
			*/
			size += WriteString(ptr, wndClass.m_lpstr, true);
			size += WriteString(ptr, caption.m_lpstr);

			// Set creation data
			size += sCreateDataSize + 2;
			if (ptr)
			{
				if (pCreateData)
				{
					// Write data size & data
					*ptr = sCreateDataSize + 2;
					memcpy(ptr + 1, pCreateData, sCreateDataSize);
					// Increase the pointer
					ptr += *ptr;
				}
				else
				{
					// Set data to zero and increase
					*ptr++ = 0;
				}
			}

			// Align the pointer to DWORD
			size_t unalignedSize = size;
			size = (size + 3) & (~3);
			if (ptr) // Add zero-padding
				::memset(ptr, 0, size - unalignedSize);

			return size;
		}

		size_t WriteString(WORD* &dest, LPCTSTR pszString, bool bSpecialResourceMarker = false)
		{
			size_t len = 0;

			if( IS_INTRESOURCE(pszString) )
			{
				if( bSpecialResourceMarker )
				{
					/* If the first element of the array is 0x0000, ... and the array has no other elements.*/
					/* If the first element is 0xFFFF, the array has one additional element ...*/

					if( pszString == nullptr )
						len = 1;
					else
						len = 2;

					if( dest )
					{
						if( pszString == nullptr )
							*dest++ = 0;
						else
						{
							*dest++ = 0xFFFF;
							*dest++ = LOWORD(pszString);
						}
					}
				}
				else if( pszString == 0 )
				{
					// empty string
					len = 1;

					if( dest )
					{
						*dest++ = 0;
					}
				}
				else
				{
					// Load a string from a resource
					UINT uID = PtrToUint(pszString);

					CAtlString localized;
					if( !localized.LoadStringW(uID) )
					{
						localized = L"LoadString failed";
					}
					len = localized.GetLength() + 1 /* terminating null character */;

					if( dest )
					{
						::memcpy(dest, localized.GetString(), len * sizeof(wchar_t));
						dest += len;
					}
				}
			}
			else
			{
				// copy the string
				len = ::wcslen(pszString) + 1 /* terminating null character */;

				if( dest )
				{
					::memcpy(dest, pszString, len * sizeof(wchar_t));
					dest += len;
				}
			}

			return len * sizeof(WORD);
		}

		void* _ExtendMemory(size_t size)
		{
			if( size == 0 )
				return nullptr;

			size_t newSize = m_size + size;
			void*  ret     = nullptr;

			if( newSize > m_capacity )
			{
				// allocate multiples of pages
				size_t pageSize = 1 << 10;
				size_t newCapacity = (newSize + pageSize - 1) & ~(pageSize - 1);

				void* p = realloc(m_memory, newCapacity);

				if( p )
				{
					m_memory = p;
					m_capacity = newCapacity;
				}
				else
				{
					// allocation failed
					return nullptr;
				}
			}

			ret = static_cast<BYTE*>(m_memory) + m_size;
			m_size = newSize;

			return ret;
		}

		bool   m_bModal;

		void*  m_memory;     // Pointer to the template data
		size_t m_size;       // Size of memory used
		size_t m_capacity;   // Size of memory available
	};

}
