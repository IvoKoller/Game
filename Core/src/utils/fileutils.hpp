#pragma once

#include <iostream>
#include <fstream>
#include <string>

namespace sparky {

	static std::string read_file(const char* filepath){

		std::string result;
		std::string line;
		std::ifstream file;
		//TODO: need a way to get current working directory...
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

}
