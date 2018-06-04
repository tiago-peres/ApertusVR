/*MIT License

Copyright (c) 2018 MTA SZTAKI

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/

#include "ApeLogManagerImpl.h"

Ape::LogManagerImpl::LogManagerImpl()
	: mStream(&std::cout)
{
	msSingleton = this;
	system("color 0F");
	mOutFileStream = std::ofstream("ApertusVR.log");
}

Ape::LogManagerImpl::~LogManagerImpl()
{
	mOutFileStream.close();

	delete mStream;
	mStream = NULL;
}

std::string Ape::LogManagerImpl::getFileNameFromPath(const std::string& path)
{
	std::size_t found = path.find_last_of("/\\");
	return path.substr(found + 1);
}

void Ape::LogManagerImpl::setLevel(int level)
{
	mLevel = level;
}

void Ape::LogManagerImpl::registerStream(std::ostream& stream)
{
	mStream = &stream;
}

void Ape::LogManagerImpl::log(std::stringstream& ss, int level)
{
	std::lock_guard<std::mutex> guard(g_pages_mutex);

	std::stringstream ssOut;
	int levelToCheck = mLevel;
	if (mLevel != level)
		levelToCheck = level;

	switch (levelToCheck)
	{
	case LOG_TYPE_INFO:
		ssOut << COLOR_LIGHT_GREEN << "INFO" << COLOR_TERM << ":" << std::setfill(' ') << std::setw(5) << " ";
		break;
	case LOG_TYPE_DEBUG:
		ssOut << COLOR_LIGHT_BLUE << "DEBUG" << COLOR_TERM << ":" << std::setfill(' ') << std::setw(4) << " ";
		break;
	case LOG_TYPE_TRACE:
		ssOut << COLOR_LIGHT_CYAN << "TRACE" << COLOR_TERM << ":" << std::setfill(' ') << std::setw(4) << " ";
		break;
	case LOG_TYPE_WARNING:
		ssOut << COLOR_LIGHT_YELLOW << "WARNING" << COLOR_TERM << ":" << std::setfill(' ') << std::setw(2) << " ";
		break;
	case LOG_TYPE_ERROR:
		ssOut << COLOR_LIGHT_RED << "ERROR" << COLOR_TERM << ":" << std::setfill(' ') << std::setw(4) << " ";
		break;
	}

	ssOut << ss.str();

	*mStream << ssOut.str();
	mStream->flush();

	mOutFileStream << ssOut.str();
	mOutFileStream.flush();
}