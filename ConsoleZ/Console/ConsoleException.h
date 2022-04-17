#pragma once

class ConsoleException
{
	public:
		ConsoleException(const std::wstring& message)
		: m_message(message)
		{
		}

		const std::wstring& GetMessage() const { return m_message; }

	private:

		std::wstring m_message;
};
