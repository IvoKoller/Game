#pragma once

#include <string>
#include <sstream>
#include <vector>

namespace evo {

	static std::vector<std::string> split_string(const std::string &s, char delimeter) {
		std::vector<std::string> elems;
		std::stringstream ss(s);
		std::string item;
		while (std::getline(ss, item, delimeter)) {
			elems.push_back(item);
		}
		return elems;
	}
	//Global variable PathToExec
	class filepath{
	private:
		static std::string m_PathToExec;
	public:
		filepath(const std::string& path);
		static std::string makeAbsolute(std::string relativeFilepath);
	};

}
