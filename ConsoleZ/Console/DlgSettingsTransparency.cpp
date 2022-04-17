#include "stdafx.h"
#include "resource.h"

#include "DlgSettingsTransparency.h"

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

DlgSettingsTransparency::DlgSettingsTransparency(CComPtr<IXMLDOMElement>& pOptionsRoot)
: DlgSettingsBase(pOptionsRoot)
{
	IDD = IDD_SETTINGS_TRANSPARENCY;
}

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

LRESULT DlgSettingsTransparency::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	m_transparencySettings.Load(m_pOptionsRoot);

	m_tabCtrl.Attach(GetDlgItem(IDC_TABS_TRANSPARENCY));

	m_tabCtrl.InsertItem(0, Helpers::LoadStringW(IDS_SETTINGS_WINDOWED).c_str());
	m_tabCtrl.InsertItem(1, Helpers::LoadStringW(IDS_SETTINGS_FULLSCREEN).c_str());

	m_sliderActiveAlpha.Attach(GetDlgItem(IDC_ACTIVE_ALPHA));
	m_sliderActiveAlpha.SetRange(0, 255 - TransparencySettings::minAlpha);
	m_sliderActiveAlpha.SetTicFreq(5);
	m_sliderActiveAlpha.SetPageSize(5);

	m_sliderInactiveAlpha.Attach(GetDlgItem(IDC_INACTIVE_ALPHA));
	m_sliderInactiveAlpha.SetRange(0, 255 - TransparencySettings::minAlpha);
	m_sliderInactiveAlpha.SetTicFreq(5);
	m_sliderInactiveAlpha.SetPageSize(5);

	m_sliderActiveAlpha.SetPos(255 - m_transparencySettings.ActiveAlpha());
	m_sliderInactiveAlpha.SetPos(255 - m_transparencySettings.InactiveAlpha());

	UpdateSliderText(m_sliderActiveAlpha.m_hWnd);
	UpdateSliderText(m_sliderInactiveAlpha.m_hWnd);

	EnableTransparencyControls();

	DoDataExchange(DDX_LOAD);
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

LRESULT DlgSettingsTransparency::OnCtlColorStatic(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CWindow		staticCtl(reinterpret_cast<HWND>(lParam));
	CDCHandle	dc(reinterpret_cast<HDC>(wParam));

	if (staticCtl.m_hWnd == GetDlgItem(IDC_KEY_COLOR))
	{
		CBrush	brush(::CreateSolidBrush(m_transparencySettings.ColorKey()));
		CRect	rect;

		staticCtl.GetClientRect(&rect);
		dc.FillRect(&rect, brush);
		return 0;
	}

	bHandled = FALSE;
	return 0;
}

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

LRESULT DlgSettingsTransparency::OnHScroll(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
	UpdateSliderText(reinterpret_cast<HWND>(lParam));
	return 0;
}

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

LRESULT DlgSettingsTransparency::OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if (wID == IDOK)
	{
		DoDataExchange(DDX_SAVE);

		m_transparencySettings.ActiveAlpha()	= static_cast<BYTE>(255 - m_sliderActiveAlpha.GetPos());
		m_transparencySettings.InactiveAlpha()	= static_cast<BYTE>(255 - m_sliderInactiveAlpha.GetPos());

		TransparencySettings& transparencySettings= g_settingsHandler->GetAppearanceSettings().transparencySettings;

		transparencySettings = m_transparencySettings;

		m_transparencySettings.Save(m_pOptionsRoot);
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

LRESULT DlgSettingsTransparency::OnClickedKeyColor(WORD /*wNotifyCode*/, WORD /*wID*/, HWND hWndCtl, BOOL& /*bHandled*/)
{
	CColorDialog	dlg(m_transparencySettings.ColorKey(), CC_FULLOPEN);

	if (dlg.DoModal() == IDOK)
	{
		// update color
		m_transparencySettings.ColorKey() = dlg.GetColor();
		CWindow(hWndCtl).Invalidate();
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

LRESULT DlgSettingsTransparency::OnClickedTransType(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	DoDataExchange(DDX_SAVE);
	EnableTransparencyControls();
	return 0;
}

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

void DlgSettingsTransparency::UpdateSliderText(HWND hwndSlider)
{
	CTrackBarCtrl	trackBar;
	CWindow			wndStaticCtrl;

	if (hwndSlider == m_sliderActiveAlpha.m_hWnd)
	{
		trackBar.Attach(hwndSlider);
		wndStaticCtrl.Attach(GetDlgItem(IDC_STATIC_ACTIVE_ALPHA));
	}
	else if (hwndSlider == m_sliderInactiveAlpha.m_hWnd)
	{
		trackBar.Attach(hwndSlider);
		wndStaticCtrl.Attach(GetDlgItem(IDC_STATIC_INACTIVE_ALPHA));
	}
	else
	{
		return;
	}

	CString strStaticText;
	strStaticText.Format(L"%i", trackBar.GetPos());

	wndStaticCtrl.SetWindowText(strStaticText);

	wndStaticCtrl.Detach();
	trackBar.Detach();
}

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

void DlgSettingsTransparency::EnableTransparencyControls()
{
	GetDlgItem(IDC_STATIC_ACTIVE_WINDOW).EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_INACTIVE_WINDOW).EnableWindow(FALSE);
	GetDlgItem(IDC_ACTIVE_ALPHA).EnableWindow(FALSE);
	GetDlgItem(IDC_INACTIVE_ALPHA).EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_ACTIVE_ALPHA).EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_INACTIVE_ALPHA).EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_KEY_COLOR).EnableWindow(FALSE);
	GetDlgItem(IDC_KEY_COLOR).EnableWindow(FALSE);

	if (m_transparencySettings.TransType() == transAlpha ||
	    m_transparencySettings.TransType() == transAlphaAndColorKey ||
	    m_transparencySettings.TransType() == transGlass)
	{
		GetDlgItem(IDC_STATIC_ACTIVE_WINDOW).EnableWindow();
		GetDlgItem(IDC_STATIC_INACTIVE_WINDOW).EnableWindow();
		GetDlgItem(IDC_ACTIVE_ALPHA).EnableWindow();
		GetDlgItem(IDC_INACTIVE_ALPHA).EnableWindow();
		GetDlgItem(IDC_STATIC_ACTIVE_ALPHA).EnableWindow();
		GetDlgItem(IDC_STATIC_INACTIVE_ALPHA).EnableWindow();
	}

	if (m_transparencySettings.TransType() == transColorKey ||
	    m_transparencySettings.TransType() == transAlphaAndColorKey)
  {
		GetDlgItem(IDC_STATIC_KEY_COLOR).EnableWindow();
		GetDlgItem(IDC_KEY_COLOR).EnableWindow();
	}
}

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

LRESULT DlgSettingsTransparency::OnTabItemChanged(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)
{
	// save FULLSCREEN or WINDOWED settings
	DoDataExchange(DDX_SAVE);

	m_transparencySettings.ActiveAlpha() = static_cast<BYTE>(255 - m_sliderActiveAlpha.GetPos());
	m_transparencySettings.InactiveAlpha() = static_cast<BYTE>(255 - m_sliderInactiveAlpha.GetPos());

	// switch FULLSCREEN <-> WINDOWED
	m_transparencySettings.bIsFullScreen = m_tabCtrl.GetCurSel() == 1;

	DoDataExchange(DDX_LOAD);

	m_sliderActiveAlpha.SetPos(255 - m_transparencySettings.ActiveAlpha());
	m_sliderInactiveAlpha.SetPos(255 - m_transparencySettings.InactiveAlpha());

	UpdateSliderText(m_sliderActiveAlpha.m_hWnd);
	UpdateSliderText(m_sliderInactiveAlpha.m_hWnd);

	EnableTransparencyControls();

	return 0;
}

//////////////////////////////////////////////////////////////////////////////
