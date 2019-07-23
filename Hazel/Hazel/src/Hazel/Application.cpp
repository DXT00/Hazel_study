#include "hzpch.h"
#include "Application.h"

#include "Hazel/Log.h"

#include <glad/glad.h>

#include "Input.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
namespace Hazel {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)


	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		HZ_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverLay(m_ImGuiLayer);

		float vertices[3 * 7] = {
			//Position          //Color
			-0.5f,-0.5f,0.0f,	1.0f,0.0f,0.0f,1.0f,
			 0.5f,-0.5f,0.0f,	0.0f,1.0f,0.0f,1.0f,
			 0.0f, 0.5f,0.0f,	0.0f,0.0f,1.0f,1.0f,

		};
		float squareVertices[3 * 4] = {
			//Position          //Color
			-0.5f,-0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			 0.5f,0.5f, 0.0f,
			 -0.5f, 0.5f, 0.0f,

		};
		unsigned int indices[3] = { 0,1,2 };
		unsigned int squareIndices[6] = { 0,1,2,0,2,3 };

		m_VertexArray.reset(VertexArray::Create());
		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		m_IndexBuffer.reset(IndexBuffer::Create(indices, 3));


		BufferLayout layout = {
			{ ShaderDataType::Float3,"a_Position", false },
			{ ShaderDataType::Float4,"a_Color",    false },


		};
		BufferLayout squareLayout = {
			{ ShaderDataType::Float3,"a_Position", false },


		};
		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);


		m_SqareVA.reset(VertexArray::Create());
		m_SqareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		m_SqareIB.reset(IndexBuffer::Create(squareIndices, 6));

		m_SqareVB->SetLayout(squareLayout);
		m_SqareVA->AddVertexBuffer(m_SqareVB);
		m_SqareVA->SetIndexBuffer(m_SqareIB);

		/*	uint32_t index = 0;
			for (auto& element: m_VertexBuffer->GetLayout())
			{
				glEnableVertexAttribArray(index);
				glVertexAttribPointer(index,
					element.GetElementCount(),
					ShaderDataTypeToBufferType(element.Type),
					element.Normalized ? GL_TRUE : GL_FALSE,
					layout.GetStride(),
					(void *)element.Offset);
				index++;
			}*/
			/*glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), nullptr);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)12);
	*/

		const std::string vertexSrc = R"(
				#version 330 core
				
				layout(location = 0) in vec3 a_Position;
				layout(location = 1) in vec4 a_Color;

				out vec3 v_Position;
				out vec4 v_Color;

				void main()
				{
					v_Position = a_Position;
					v_Color = a_Color;
					gl_Position = vec4(a_Position,1.0);

				}


				)";
		const std::string fragmentSrc = R"(
				#version 330 core
				
				layout(location = 0) out vec4 color;
				layout(location = 1) out vec4 color1;

				in vec3 v_Position;
				in vec4 v_Color;
				
				void main()
				{

					color = v_Color;//vec4(v_Position*0.5+0.5, 1.0);

				}
				)";

		const std::string squareVertexSrc = R"(
				#version 330 core
				
				layout(location = 0) in vec3 a_Position;
				
				out vec3 v_Position;
			

				void main()
				{
					v_Position = a_Position;
				
					gl_Position = vec4(a_Position,1.0);

				}


				)";
		const std::string squareFragmentSrc = R"(
				#version 330 core
				
				layout(location = 0) out vec4 color;

				in vec3 v_Position;

				
				void main()
				{

					color =vec4(v_Position*0.5+0.5, 1.0);

				}
				)";
		//m_Shader = std::make_unique<Shader>(vertexSrc,fragmentSrc);
		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
		m_SqareShader.reset(new Shader(squareVertexSrc, squareFragmentSrc));

	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverLay(Layer* layer)
	{
		m_LayerStack.PushOverLay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_SqareShader->Bind();
			m_SqareVA->Bind();
			glDrawElements(GL_TRIANGLES, m_SqareVA->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			m_Shader->Bind();
			m_VertexArray->Bind();
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);



			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}