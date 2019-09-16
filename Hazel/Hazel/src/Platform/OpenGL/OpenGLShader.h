#pragma once
#include <string>
#include<glm/glm.hpp>
#include "Hazel/Renderer/Shader.h"
//#include "glad/glad.h"
//TODO:REMOVE!
typedef unsigned int GLenum;
namespace Hazel {

	class OpenGLShader:public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~OpenGLShader();
		virtual void Bind()const override;
		virtual void Unbind() const override;


		void SetUniformInt(const std::string &name,  int value);

		void SetUniformFloat(const std::string &name,  float value);
		void SetUniformFloat2(const std::string &name, const glm::vec2 &value);
		void SetUniformFloat3(const std::string &name, const glm::vec3 &value);
		void SetUniformFloat4(const std::string &name, const glm::vec4 &value);

		void SetUniformMat3(const std::string &name, const glm::mat3 &mat);
		void SetUniformMat4(const std::string &name, const glm::mat4 &mat);
	private:
		uint32_t m_RendererID;

	private:
		std::string ReadFile(std::string filepath);
		std::unordered_map<GLenum,std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
		
	};

}