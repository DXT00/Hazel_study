#pragma once
#include "VertexArray.h"
#include "glm/glm.hpp"
namespace Hazel {
	class RendererAPI //just an Interface ≥ÈœÛ¿‡
	{
	public:

		enum class API {
			None = 0, OpenGL = 1
		}; 

		RendererAPI();
		virtual ~RendererAPI();

		virtual void Init()=0;

		static const API &GetAPI(){return s_API;}
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndex(const Ref<VertexArray> &vertexArray)=0;

		

	private:
		static API s_API;

	};


}
