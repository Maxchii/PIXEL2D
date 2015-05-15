#pragma once

namespace PIXL{ namespace debugging {

	/*!
	* \brief Debug class provides various debugging functions
	*/
	class Debug
	{
	public:
		~Debug(){}

		/*!
		* \brief Writes a message to the console in Log format.
		*
		* <param name="message">The message to log about</param>
		*/
		static void log(const char* message);

		/*!
		* \brief Writes a message to the console in Warning format.
		*
		* <param name="header">The header of the logging location. This can be null, it will just result in not writing a header</param>
		* <param name="message">The message to log about</param>
		*/
		static void logWarning(const char* header, const char* message);

		/*!
		* \brief Writes a message to the console in Error format.
		*
		* <param name="header">The header of the logging location. This can be null, it will just result in not writing a header</param>
		* <param name="message">The message to log about</param>
		*/
		static void logError(const char* header, const char* message);

	private:
		Debug(){}

		/**
		* The maximum length of the debug string for [LogType]Format methods.. (Currently set to 2048).
		*/
		static const int MAX_DEBUG_STRING_LENGTH;
	};

} }