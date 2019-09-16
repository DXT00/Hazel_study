#include "hzpch.h"
#include "OpenGLTexture2D.h"
#include <glad/glad.h>
#include "stb_image.h"

namespace Hazel {
	OpenGLTexture2D::OpenGLTexture2D(const std::string &path)
		:m_Path(path)
	{
		glGenTextures(1, &m_RendererID);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
		/*glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);*/

		//set the texture warpping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);//����s��
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);//����t��

		//�������---�ڽ����˺����Թ���
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//������Сʱ���ڽ�����
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);//����Ŵ�ʱҲ���ڽ�����

		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		HZ_CORE_ASSERT(data, "Failed to load image!");
		m_Width = width;
		m_Height = height;

		GLenum internalFormat = 0, dataFormat = 0;
		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		HZ_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");
	

		glTexImage2D(GL_TEXTURE_2D, 0, dataFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
		//glGenerateMipmap(GL_TEXTURE_2D);//Ϊ��ǰ�󶨵������Զ�����������Ҫ�Ķ༶��Զ����

		//glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	
		//int width, height, channels;
		//stbi_set_flip_vertically_on_load(1);
		//stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		//HZ_CORE_ASSERT(data, "Failed to load image!");
		//m_Width = width;
		//m_Height = height;

		//GLenum internalFormat = 0, dataFormat = 0;
		//if (channels == 4)
		//{
		//	internalFormat = GL_RGBA8;
		//	dataFormat = GL_RGBA;
		//}
		//else if (channels == 3)
		//{
		//	internalFormat = GL_RGB8;
		//	dataFormat = GL_RGB;
		//}

		//HZ_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");

		//glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		////std::cout << glGetError() << std::endl; // ���� 1280 (�Ƿ�ö��)

		//glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);
		//std::cout << glGetError() << std::endl; // ���� 1280 (�Ƿ�ö��)

		//glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		//glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

		//stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		
		glBindTexture(slot, m_RendererID);

	}



}
