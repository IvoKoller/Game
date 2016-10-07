#include "filepath.hpp"

namespace evo {

    filepath::filepath(const std::string& path) {
        m_PathToExec = path.substr(0,path.find_last_of("/\\")+1);
    }

    std::string filepath::makeAbsolute(std::string relativeFilepath) {
        std::string result = m_PathToExec + relativeFilepath;
        return result;
    }

    std::string filepath::m_PathToExec;
}
