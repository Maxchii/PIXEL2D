#include "Debug.h"
#include <stdio.h>
#include <cstdio>
#include <stdarg.h>


namespace PIXL{ namespace debugging {

	const int Debug::MAX_DEBUG_STRING_LENGTH = 2048;

	
	void Debug::Log(const char* message)
	{
		printf("[LOG]: %s\n", message);
	}

	void Debug::LogWarning(const char* header, const char* message)
	{
		if (header != nullptr)
		{
			printf("[WARNING in %s]: %s\n",header, message);
		}
		else
		{
			printf("[WARNING]: %s\n", message);
		}
	}

	void Debug::LogError(const char* header, const char* message)
	{
		if (header != nullptr)
		{
			printf("[ERROR in %s]: %s\n", header, message);
		}
		else
		{
			printf("[ERROR]: %s\n", message);
		}
	}
}
}