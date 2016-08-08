#pragma once

#include <string>

namespace sparky {
	//Global variable PathToExec
	class filepath{
	private:
		static std::string m_PathToExec;
	public:
		filepath(const std::string& path);
		static std::string makeAbsolute(std::string relativeFilepath);
	};

}
