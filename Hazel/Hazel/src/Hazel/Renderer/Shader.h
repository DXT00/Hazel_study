#pragma once
#include <string>
#include<glm/glm.hpp>
namespace Hazel {

	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();
		void Bind()const;
		void Unbind() const;
		uint32_t GetUniformLocation(const std::string& name) const;
		void setUniformMat4(const std::string &name, const glm::mat4 &mat) const;
	private:
		uint32_t m_RendererID;


	};

}