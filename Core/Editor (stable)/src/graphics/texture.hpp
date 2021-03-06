#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <FreeImage.h>
#include <string>
#include <cstring>
#include <GL/glew.h>
#include "../utils/ImageLoad.hpp"

#include "../managers/staticManager.hpp"

namespace evo {
namespace graphics {

	class Texture : public StaticManager<Texture>{
	private:
		std::string m_FileName;
		GLuint m_TID;
		GLsizei m_Width, m_Height;
		const unsigned int m_Rows, m_Columns;
	public:
		Texture(const char* name, const std::string& filename, const unsigned int& rows = 1, const unsigned int& columns = 1);
		~Texture();
		void bind() const;
		void unbind() const;

		const unsigned int getID() const { return m_TID; }
		const unsigned int getWidth() const { return m_Width; }
		const unsigned int getHeight() const { return m_Height; }
		const unsigned int getRows() const { return m_Rows; }
		const unsigned int getColumns() const { return m_Columns; }
	private:
		GLuint load();
	};

}}
#endif /* end of include guard: TEXTURE_HPP */
