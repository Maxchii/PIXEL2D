#pragma once
#include "..//Core/ValueTypes.h"
#include <string>
#include <vector>

namespace PIXL { namespace utilities {

	void GetWords(std::string s, std::vector<std::string>& words);
	std::vector<std::string> SplitString(const std::string &s, char delimeter);
	std::string F2S(Float32 val);
	std::string I2S(SInt32 val);
	Float32 S2F(const std::string& s);
	SInt32 S2I(const std::string& s);

} }
