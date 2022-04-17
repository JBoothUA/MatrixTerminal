#pragma once

#include <msxml.h>

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

class XmlHelper
{
	public:

		static HRESULT OpenXmlDocument(const std::wstring& strFilename, CComPtr<IXMLDOMDocument>& pXmlDocument, CComPtr<IXMLDOMElement>& pRootElement, std::wstring& strParseError);
		static HRESULT OpenXmlDocumentFromResource(const std::wstring& strFilename, CComPtr<IXMLDOMDocument>& pXmlDocument, CComPtr<IXMLDOMElement>& pRootElement);
		static HRESULT OpenXmlDocumentFromContent(const std::vector<char>& content, CComPtr<IXMLDOMDocument>& pXmlDocument, CComPtr<IXMLDOMElement>& pRootElement);

		static HRESULT GetDomElement(const CComPtr<IXMLDOMElement>& pRootElement, const CComBSTR& bstrPath, CComPtr<IXMLDOMElement>& pElement);
		static HRESULT AddDomElementIfNotExist(const CComPtr<IXMLDOMElement>& pElement, const CComBSTR& bstrName, CComPtr<IXMLDOMElement>& pNewElement);
		static HRESULT CreateDomElement(const CComPtr<IXMLDOMElement>& pElement, const CComBSTR& bstrName, CComPtr<IXMLDOMElement>& pNewElement);
		static HRESULT AddTextNode(const CComPtr<IXMLDOMElement>& pElement, const CComBSTR& bstrText);
		static HRESULT RemoveAllChildNodes(const CComPtr<IXMLDOMElement>& pElement);

		static void GetAttribute(const CComPtr<IXMLDOMElement>& pElement, const CComBSTR& bstrName, DWORD& dwValue, DWORD dwDefaultValue);
		static void GetAttribute(const CComPtr<IXMLDOMElement>& pElement, const CComBSTR& bstrName, int& nValue, int nDefaultValue);
		static void GetAttribute(const CComPtr<IXMLDOMElement>& pElement, const CComBSTR& bstrName, BYTE& byValue, BYTE byDefaultValue);
		static void GetAttribute(const CComPtr<IXMLDOMElement>& pElement, const CComBSTR& bstrName, bool& bValue, bool bDefaultValue);
		static void GetAttribute(const CComPtr<IXMLDOMElement>& pElement, const CComBSTR& bstrName, std::wstring& strValue, const std::wstring& strDefaultValue);

		static void GetRGBAttribute(const CComPtr<IXMLDOMElement>& pElement, COLORREF& crValue, COLORREF crDefaultValue);

		static bool GetNodeText(const CComPtr<IXMLDOMElement>& pElement, std::wstring& strValue);
		static bool GetChildNodeText(const CComPtr<IXMLDOMElement>& pElement, const CComBSTR& bstrChildName, std::wstring& strValue);

		static void SetAttribute(const CComPtr<IXMLDOMElement>& pElement, const CComBSTR& bstrName, DWORD dwValue);
		static void SetAttribute(const CComPtr<IXMLDOMElement>& pElement, const CComBSTR& bstrName, int nValue);
		static void SetAttribute(const CComPtr<IXMLDOMElement>& pElement, const CComBSTR& bstrName, BYTE byValue);
		static void SetAttribute(const CComPtr<IXMLDOMElement>& pElement, const CComBSTR& bstrName, bool bValue);
		static void SetAttribute(const CComPtr<IXMLDOMElement>& pElement, const CComBSTR& bstrName, const std::wstring& strValue);

		static void SetRGBAttribute(const CComPtr<IXMLDOMElement>& pElement, const COLORREF& crValue);
		static void SaveColors(CComPtr<IXMLDOMElement>& pElement, const COLORREF colors[16], BYTE opacity);
		static bool LoadColors(const CComPtr<IXMLDOMElement>& pElement, COLORREF colors[16], BYTE & opacity);
};

//////////////////////////////////////////////////////////////////////////////
