#include "texture.hpp"

namespace evo {
namespace graphics {

	Texture::Texture(const char* name, const std::string& filename, const unsigned int& rows, const unsigned int& columns)
		: StaticManager(name), m_FileName(filename), m_Rows(rows), m_Columns(columns) {
		m_TID = load();
	}

	Texture::~Texture() {
		//TODO: write destructor for texture
	}

	GLuint Texture::load() {
		BYTE* pixels = load_image(m_FileName.c_str(), &m_Width, &m_Height);

		GLuint result;
		glGenTextures(1, &result);
		glBindTexture(GL_TEXTURE_2D, result);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixels);
		glBindTexture(GL_TEXTURE_2D, 0);

		delete[] pixels;

		return result;
	}

	void Texture::bind() const {
		glBindTexture(GL_TEXTURE_2D, m_TID);
	}

	void Texture::unbind() const {
		glBindTexture(GL_TEXTURE_2D, 0);
	}

} }
