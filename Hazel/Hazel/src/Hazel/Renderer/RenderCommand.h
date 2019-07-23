#pragma once
#include"RendererAPI.h"
namespace Hazel {
	//static wrapper for the actual implementation
	//One Command do one thing!
	class RenderCommand
	{
	public:
		inline static void DrawIndex(const std::shared_ptr<VertexArray>& vertexArray) {
			s_RenderAPI->DrawIndex(vertexArray);
		}
		inline static void SetClearColor(const glm::vec4& color) {
			s_RenderAPI->SetClearColor(color);
		}
		inline static void Clear() {
			s_RenderAPI->Clear();
		}

	
	private:
		//����ָ��һ��RendererAPI��ָ��,���ָ�����ָ��OpenGLRendererAPI������DirectXRendrerAPI...
		//s_RenderAPI is a pointer to a class with no member! so it is just one Byte memery leak
		static RendererAPI* s_RenderAPI;
	};

}

