#include "MessageBuilder.hpp"


namespace http
{
	MessageBuilder::MessageBuilder() :
		myMajorVersion(1), myMinorVersion(0)
	{

	}

	MessageBuilder::MessageBuilder(const Message& message) : 
		myMajorVersion(1), myMinorVersion(0)
	{
		if(message.headers_complete())
		{
			myMajorVersion = message.major_version();
			myMinorVersion = message.minor_version();
			myFlags = message.flags();
			myHeaders = message.headers();
		}
	}

	int MessageBuilder::major_version() const
	{
		return myMajorVersion;
	}

	void MessageBuilder::set_major_version(int majorVersion)
	{
		myMajorVersion = majorVersion;
	}

	int MessageBuilder::minor_version() const
	{
		return myMinorVersion;
	}

	void MessageBuilder::set_minor_version(int minorVersion)
	{
		myMinorVersion = minorVersion;
	}

	const Flags& MessageBuilder::flags() const
	{
		return myFlags;
	}

	Flags& MessageBuilder::flags()
	{
		return myFlags;
	}

	void MessageBuilder::set_flags(const Flags& flags)
	{
		myFlags = flags;
	}

	std::string MessageBuilder::version_to_string() const
	{
		std::string versionString("HTTP/");
		char majorVersion[16] = {0};
		char minorVersion[16] = {0};

#ifdef WIN32
		_itoa_s(major_version(), majorVersion, 16, 10);
		_itoa_s(minor_version(), minorVersion, 16, 10);
#else
		itoa(major_version(), majorVersion, 10);
		itoa(minor_version(), minorVersion, 10);
#endif

		versionString += majorVersion;
		versionString += ".";
		versionString += minorVersion;

		return versionString;
	}

	std::string MessageBuilder::headers_to_string() const
	{
		std::string headersString;
		for(Message::Headers::const_iterator cit = myHeaders.cbegin(); cit != myHeaders.cend(); ++cit)
		{
			headersString += cit->first;
			headersString += ": ";
			headersString += cit->second;
			headersString += "\r\n";
		}

		return headersString;
	}
}