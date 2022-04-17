#include "stdafx.h"
#include "XmlHelper.h"

bool SnippetsFile::load(const CComPtr<IXMLDOMElement>& xmlNodeSnippets)
{
	return XmlHelper::GetChildNodeText(xmlNodeSnippets, CComBSTR(L"DownloadUrl"), this->m_downloadUrl);
}

bool Snippet::load(const CComPtr<IXMLDOMElement>& xmlElementSnippet)
{
	// Header
	{
		CComPtr<IXMLDOMElement> xmlElementHeader;
		if( FAILED(XmlHelper::GetDomElement(xmlElementSnippet, CComBSTR(L"Header"), xmlElementHeader)) ) return false;

		// Title
		if( !(XmlHelper::GetChildNodeText(xmlElementHeader, CComBSTR(L"Title"), this->m_header.title)) ) return false;

		// Description
		if( !(XmlHelper::GetChildNodeText(xmlElementHeader, CComBSTR(L"Description"), this->m_header.description)) ) return false;

		// Author
		{
			CComPtr<IXMLDOMElement> xmlElementAuthor;
			if( FAILED(XmlHelper::GetDomElement(xmlElementHeader, CComBSTR(L"Author"), xmlElementAuthor)) ) return false;
			if( !(XmlHelper::GetNodeText(xmlElementAuthor, this->m_header.author)) ) return false;

			// Url
			XmlHelper::GetAttribute(xmlElementAuthor, CComBSTR(L"Url"), this->m_header.authorUrl, std::wstring());

			// Email
			XmlHelper::GetAttribute(xmlElementAuthor, CComBSTR(L"Email"), this->m_header.authorEmail, std::wstring());
		}

		// Version
		if( !(XmlHelper::GetChildNodeText(xmlElementHeader, CComBSTR(L"Version"), this->m_header.version)) ) return false;
	}

	// Declarations
	{
		CComPtr<IXMLDOMElement> xmlElementDeclarations;
		if( SUCCEEDED(XmlHelper::GetDomElement(xmlElementSnippet, CComBSTR(L"Declarations"), xmlElementDeclarations)) )
		{
			CComPtr<IXMLDOMNodeList> xmlNodeList;
			if (FAILED(xmlElementDeclarations->selectNodes(CComBSTR(L"Literal"), &xmlNodeList))) return false;

			long lListLength;
			if( FAILED(xmlNodeList->get_length(&lListLength)) ) return false;
			for( long i = 0; i < lListLength; ++i )
			{
				// Literal
				CComPtr<IXMLDOMNode> xmlNode;
				if (FAILED(xmlNodeList->get_item(i, &xmlNode))) continue;
				CComPtr<IXMLDOMElement> xmlElementLiteral;
				if (FAILED(xmlNode.QueryInterface(&xmlElementLiteral))) continue;

				std::shared_ptr<Literal> literal(new Literal);

				// ID
				if( !(XmlHelper::GetChildNodeText(xmlElementLiteral, CComBSTR(L"ID"), literal->id)) ) continue;
				// ToolTip
				if( !(XmlHelper::GetChildNodeText(xmlElementLiteral, CComBSTR(L"ToolTip"), literal->toolTip)) ) continue;
				// Default
				if( !(XmlHelper::GetChildNodeText(xmlElementLiteral, CComBSTR(L"Default"), literal->default)) ) continue;

				this->m_declarations.push_back(literal);
			}
		}
	}

	// Code
	{
		CComPtr<IXMLDOMElement> xmlElementCode;
		if( FAILED(XmlHelper::GetDomElement(xmlElementSnippet, CComBSTR(L"Code"), xmlElementCode)) ) return false;

		// raw
		if( !(XmlHelper::GetNodeText(xmlElementCode, this->m_code.raw)) ) return false;
		// Delimiter
		XmlHelper::GetAttribute(xmlElementCode, CComBSTR(L"Code"), this->m_code.delimiter, L"$");
	}

	return true;
}

bool SnippetCollection::loadSnippets(const std::wstring& fullSnippetsFileName)
{
	// load the xml file
	CComPtr<IXMLDOMDocument> xmlDocumentSnippets;
	CComPtr<IXMLDOMElement>  xmlElementSnippets;
	std::wstring strParseError;
	HRESULT hr = XmlHelper::OpenXmlDocument(
		fullSnippetsFileName,
		xmlDocumentSnippets,
		xmlElementSnippets,
		strParseError);
	if( FAILED(hr) ) return false;
	if( hr == S_FALSE )
	{
		::MessageBox(NULL, strParseError.c_str(), Helpers::LoadString(IDS_CAPTION_ERROR).c_str(), MB_ICONERROR | MB_OK);
		return false;
	}

	std::shared_ptr<SnippetsFile> snippetsFile(new SnippetsFile(fullSnippetsFileName));
	if( !snippetsFile->load(xmlElementSnippets) ) return false;
	this->m_files.push_back(snippetsFile);

	CComPtr<IXMLDOMNodeList> xmlNodeList;
	if( FAILED(xmlElementSnippets->selectNodes(CComBSTR(L"/ConsoleZSnippets/Snippet"), &xmlNodeList)) ) return false;

	long lListLength;
	if( FAILED(xmlNodeList->get_length(&lListLength)) ) return false;
	for( long i = 0; i < lListLength; ++i )
	{
		// Snippet
		CComPtr<IXMLDOMNode> xmlNode;
		if( FAILED(xmlNodeList->get_item(i, &xmlNode)) ) return false;
		CComPtr<IXMLDOMElement> xmlElementSnippet;
		if( FAILED(xmlNode.QueryInterface(&xmlElementSnippet)) ) return false;

		std::shared_ptr<Snippet> snippet(new Snippet(snippetsFile));

		if( !snippet->load(xmlElementSnippet) ) return false;

		this->m_snippets.push_back(snippet);
	}

	return true;
}

void SnippetCollection::reset(void)
{
	m_snippets.clear();
	m_files.clear();
}

bool SnippetCollection::load(const std::wstring& folder)
{
	try
	{
		std::wstring folderex = Helpers::ExpandEnvironmentStrings(folder);

		// parse all files with extension xml
		WIN32_FIND_DATA findData;

		std::unique_ptr<void, FindCloseHelper> hFind(::FindFirstFile((folderex + L"\\*.xml").c_str(), &findData));
		if( hFind.get() == INVALID_HANDLE_VALUE )
		{
			// If the function fails because no matching files can be found,
			// the GetLastError function returns ERROR_FILE_NOT_FOUND.
			if( ::GetLastError() == ERROR_FILE_NOT_FOUND )
				return true;

			Win32Exception::ThrowFromLastError("FindFirstFile");
		}

		do
		{
			if( findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
				continue;

			std::wstring fileName = findData.cFileName;

			loadSnippets(folderex + std::wstring(L"\\") + fileName);
		}
		while( ::FindNextFile(hFind.get(), &findData) );

		if( ::GetLastError() != ERROR_NO_MORE_FILES )
			Win32Exception::ThrowFromLastError("FindNextFile");
	}
	catch( std::exception& )
	{
		return false;
	}

	return true;
}
