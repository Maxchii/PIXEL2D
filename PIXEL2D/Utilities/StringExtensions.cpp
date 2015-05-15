#include "StringExtensions.h"
#include <sstream>

namespace PIXL { namespace utilities {

	void GetWords(std::string s, std::vector<std::string>& words)
	{
		UInt32 end = 0;

		while (s.size() > 0)
		{
			for (unsigned int i = 0; i < s.size(); i++)
			{
				if (s[i] == ' ')
				{
					end = i;
					string word = s.substr(0, end);
					s.erase(s.begin(), s.begin() + end + 1);
					words.push_back(word);
					break;
				}
				else if (i == s.size() - 1)
				{
					end = i;
					string word = s.substr(0, end + 1);
					s.clear();
					words.push_back(word);
					break;
				}
			}

		}
	}

	std::vector<std::string> SplitString(const std::string &s, char delimeter)
	{
		std::vector<std::string> elems;
		std::stringstream ss(s);
		std::string item;
		while (std::getline(ss, item, delimeter))
		{
			elems.push_back(item);
		}
		return elems;
	}

	std::string F2S(Float32 val)
	{
		std::stringstream stream;
		stream << val;

		std::string sValue = stream.str();
		val = S2F(sValue);
		if (val == (int)val)
		{
			sValue.append(".0");
		}
		return sValue;
	}
	std::string I2S(SInt32 val)
	{
		std::stringstream stream;
		stream << val;
		return stream.str();
	}

	Float32 S2F(const std::string& s)
	{
		std::stringstream stream(s);
		float value = 0.0f;
		stream >> value;
		return value;
	}
	SInt32 S2I(const std::string& s)
	{
		std::stringstream stream(s);
		SInt32 value = 0;
		stream >> value;
		return value;
	}

} }
