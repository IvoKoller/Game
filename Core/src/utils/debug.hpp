#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "filepath.hpp"

#define Log(x,y)  _log(x,y, __FILE__, __LINE__)
#define CheckError()  _checkError( __FILE__, __LINE__)

namespace evo {

    enum LogType {Note, Warning, Error};

    class Debug {
        static std::ofstream m_Log;
    public:
        Debug(const std::string& relativeFilepath);
        static void _checkError(const char *file, int line);
        static void _log(const std::string& message, LogType logtype,  const char* file, int line);
    };

}

#endif /* end of include guard: DEBUG_H */
