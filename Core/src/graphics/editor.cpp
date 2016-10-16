#include "editor.hpp"

namespace evo {
namespace graphics {

    Shader* Editor::m_Shader;
    Window* Editor::m_Window;
    bool Editor::m_ActiveColors[3];

    void Editor::update() {
        m_Shader->setUniform4f("filter",
        maths::vec4(m_ActiveColors[0],m_ActiveColors[1],m_ActiveColors[2],1));
    }

} }
