#include "Debug.h"
#include <stdio.h>
#include <cstdio>
#include <stdarg.h>


namespace PIXL{ namespace debugging {

	const int Debug::MAX_DEBUG_STRING_LENGTH = 2048;

	void Debug::log(const char* message)
	{
		printf("[%s][LOG]: %s\n", __TIME__, message);
	}

	void Debug::logWarning(const char* header, const char* message)
	{
		if (header != nullptr)
		{
			printf("[%s][WARNING in %s]: %s\n", __TIME__, header, message);
		}
		else
		{
			printf("[%s][WARNING]: %s\n", __TIME__, message);
		}
	}

	void Debug::logError(const char* header, const char* message)
	{
		if (header != nullptr)
		{
			printf("[%s][ERROR in %s]: %s\n", __TIME__, header, message);
		}
		else
		{
			printf("[%s][ERROR]: %s\n", __TIME__, message);
		}
	}
}
}