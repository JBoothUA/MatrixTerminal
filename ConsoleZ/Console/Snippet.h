#pragma once

/*
<?xml version="1.0" encoding="utf-8"?>
<ConsoleZSnippets>
	<DownloadUrl>https://raw.githubusercontent.com/cbucher/console/master/Snippets/test.xml</DownloadUrl>
	<Snippet>
		<Header>
			<Title>test</Title>
			<Description>This is a test.</Description>
			<Author Url="https://github.com/cbucher/console" Email="cbucher@users.sourceforge.net">cbucher</Author>
			<Version>1.0</Version>
			<ShellTypes>
				<ShellType>cmd</ShellType>
				<ShellType>bash</ShellType>
			</ShellTypes>
		</Header>
		<Declarations>
			<Literal>
				<ID>first</ID>
				<ToolTip>The first param</ToolTip>
				<Default>one</Default>
			</Literal>
			<Literal>
				<ID>second</ID>
				<ToolTip>The second param</ToolTip>
				<Default>two</Default>
			</Literal>
			<Literal>
				<ID>third</ID>
				<ToolTip>The third param</ToolTip>
				<Default>three</Default>
			</Literal>
		</Declarations>
		<Code Delimiter="$">
			<![CDATA[echo "$first$" "$second$" "$third$"]]>
		</Code>
	</Snippet>
</ConsoleZSnippets>
*/

class SnippetsFile
{
public:
	SnippetsFile(const std::wstring& fullFileName)
		: m_fullFileName(fullFileName)
		, m_downloadUrl()
	{ }

	inline const auto& fullFileName(void) const { return m_fullFileName; }
	inline const auto& downloadUrl (void) const { return m_downloadUrl;  }

	bool load(const CComPtr<IXMLDOMElement>& xmlNodeSnippets);

private:
	std::wstring m_fullFileName;
	std::wstring m_downloadUrl;
};

class Snippet
{
public:
	Snippet(std::shared_ptr<SnippetsFile> file)
		: m_header()
		, m_declarations()
		, m_code()
		, m_file(file)
	{
	}

	struct Header
	{
		std::wstring              title;
		std::wstring              description;
		std::wstring              author;
		std::wstring              authorUrl;
		std::wstring              authorEmail;
		std::wstring              version;
		std::vector<std::wstring> shellTypes;
	};

	struct Literal
	{
		std::wstring id;
		std::wstring toolTip;
		std::wstring default;
	};

	struct Code
	{
		std::wstring delimiter;
		std::wstring raw;
	};

	inline const auto& header      (void) const { return m_header;       }
	inline const auto& declarations(void) const { return m_declarations; }
	inline const auto& code        (void) const { return m_code;         }
	inline const auto& file        (void) const { return m_file;         }

	bool load(const CComPtr<IXMLDOMElement>& xmlNodeSnippet);

private:
	Header                                m_header;
	std::vector<std::shared_ptr<Literal>> m_declarations;
	Code                                  m_code;
  std::shared_ptr<SnippetsFile>         m_file;
};

class SnippetCollection
{
public:
	void reset(void);
	bool load(const std::wstring& folder);

	inline const auto& snippets(void) const { return m_snippets; }
	inline const auto& files   (void) const { return m_files;    }

private:
	bool loadSnippets(const std::wstring& fullSnippetsFileName);

private:
	std::vector<std::shared_ptr<Snippet>>      m_snippets;
	std::vector<std::shared_ptr<SnippetsFile>> m_files;
};