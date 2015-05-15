#pragma once
#include <stdint.h>
#include <string>

namespace PIXL
{
	//See minimum size of the data types defined by the standard at
	//http://www.open-std.org/JTC1/SC22/WG14/www/docs/n1256.pdf 
	//Sec 5.2.4.2.1 Sizes of Integer Types page 21-22

	// unsigned char
	typedef unsigned char       UInt8;
	// unsigned short
	typedef unsigned short      UInt16;
	// unsigned long 
	typedef unsigned long       UInt32;
	// unsigned long long
	typedef unsigned long long  UInt64;
	// signed char
	typedef signed char         SInt8;
	// signed short 
	typedef signed short        SInt16;
	// signed long 
	typedef signed long         SInt32;
	// signed long long
	typedef signed long long    SInt64;
	// float
	typedef float               Float32;
	// double
	typedef double              Float64;
	// uintptr_t
	typedef uintptr_t           IntPtr;
	// std::string
	typedef std::string			string;
}