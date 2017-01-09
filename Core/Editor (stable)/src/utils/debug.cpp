#include "debug.hpp"

#include <GL/glew.h>

namespace evo {
    std::ofstream Debug::m_Log;

    Debug::Debug(const std::string& relativeFilepath){
        std::string filepath = filepath::makeAbsolute(relativeFilepath);

        std::time_t now_time = std::time(nullptr);
        filepath += std::ctime(&now_time);
        filepath.pop_back();
        filepath += ".txt";

        m_Log.open(filepath, std::ios::app);
        std::cerr.rdbuf(m_Log.rdbuf());
    }

    void Debug::_checkError(const char* file, int line){
        GLenum err(glGetError());

         while(err != GL_NO_ERROR) {
            std::string error;
            switch(err) {
                case GL_INVALID_OPERATION: error="Invalid operation";      break;
                case GL_INVALID_ENUM:      error="Invalid enum";           break;
                case GL_INVALID_VALUE:     error="Invalid value";          break;
                case GL_OUT_OF_MEMORY:     error="Out of memory";          break;
                case GL_INVALID_FRAMEBUFFER_OPERATION:  error="Invalid framebuffer operation";  break;
            }

            std::cerr << "OpenGL error: " << error.c_str() << " - " << file << " : " << line << std::endl;
            std::cout << "OpenGL error: " << error.c_str() << " - " << file << " : " << line << std::endl;
            err = glGetError();
         }
    }

    void Debug::_log(const std::string& message, LogType logtype, const char* file, int line){
        std::string type;
        switch(logtype){
            case LogType::Note :    type = "Note: ";    break;
            case LogType::Warning : type = "Warning: "; break;
            case LogType::Error :   type = "Error: ";   break;
        }
        std::cerr << type << message << " - " << file << " : " << line << std::endl;
        std::cout << type << message << " - " << file << " : " << line << std::endl;
    }

}
