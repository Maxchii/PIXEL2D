#pragma once
#include "..//Core/ValueTypes.h"
#include <string>
#include <fstream>
#include "..\Debugging\Debug.h"

namespace PIXL { namespace utilities{

	static string ReadTextFromFile(const char* filepath)
	{
		//TODO Add error handling when file not found

		FILE* file;
		fopen_s(&file, filepath, "rt");
		if (file == nullptr)
		{
			debugging::Debug::LogError(nullptr,string("Failed to load ").append(filepath).c_str());
			return "";
		}
		fseek(file, 0, SEEK_END);
		unsigned long length = ftell(file);
		char* data = new char[length + 1];
		memset(data, 0, length + 1);
		fseek(file, 0, SEEK_SET);
		fread(data, 1, length, file);
		fclose(file);

		std::string result(data);
		delete[] data;
		return result;
	}

} }