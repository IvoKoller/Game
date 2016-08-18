#pragma once

#include <FreeImage.h>
#include <string>
#include <GL/glew.h>
#include "../utils/ImageLoad.hpp"

namespace evo {
namespace graphics {

	class Texture {
	private:
		std::string m_Name;
		std::string m_FileName;
		GLuint m_TID;
		GLsizei m_Width, m_Height;
	public:
		Texture(const std::string& filename);
		~Texture();
		void bind() const;
		void unbind() const;

		const unsigned int getID() const { return m_TID; }
		const unsigned int getWidth() const { return m_Width; }
		const unsigned int getHeight() const { return m_Height; }
	private:
		GLuint load();
	};

}}
