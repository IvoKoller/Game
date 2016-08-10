#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "filepath.hpp"

namespace evo {

	static std::string read_file(const std::string relativeFilepath){
		std::string filepath = filepath::makeAbsolute(relativeFilepath);

		std::string result;
		std::string line;
		std::ifstream file;

		file.open(filepath);

		if(!file.is_open()){
			std::cout << "File could not be opened!" << std::endl;
		}else{
			while(std::getline(file, line)){
				result += line + '\n';
			}
			file.close();
		}

		return result;
	}

	static std::string read_file(const char* relativeFilepath){
		std::string relpath(relativeFilepath);
		std::string filepath = filepath::makeAbsolute(relpath);

		std::string result;
		std::string line;
		std::ifstream file;

		file.open(filepath);

		std::cout << filepath << std::endl;

		if(!file.is_open()){
			std::cout << "File could not be opened!" << std::endl;
		}else{
			while(std::getline(file, line)){
				result += line + '\n';
			}
			file.close();
		}

		return result;
	}

}
