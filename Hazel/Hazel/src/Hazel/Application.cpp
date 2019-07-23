#include "hzpch.h"
#include "Application.h"

#include "Hazel/Log.h"

#include "Renderer/Renderer.h"

#include "Input.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include <glad/glad.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <GLFW/glfw3.h>
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

		m_MainCamera = std::unique_ptr<OrthographicCamera>(new OrthographicCamera());

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

		BufferLayout layout = {
				{ ShaderDataType::Float3,"a_Position", false },
				{ ShaderDataType::Float4,"a_Color",    false },


		};
		BufferLayout squareLayout = {
			{ ShaderDataType::Float3,"a_Position", false },


		};

		std::shared_ptr<VertexBuffer>vertexBuffer;
		std::shared_ptr<IndexBuffer> indexBuffer;
		m_VertexArray.reset(VertexArray::Create());
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		indexBuffer.reset(IndexBuffer::Create(indices, 3));

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);
		m_VertexArray->SetIndexBuffer(indexBuffer);


		std::shared_ptr<VertexBuffer>squareVB;
		std::shared_ptr<IndexBuffer> squareIB;
		m_SquareVA.reset(VertexArray::Create());
		squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareIB.reset(IndexBuffer::Create(squareIndices, 6));

		squareVB->SetLayout(squareLayout);
		m_SquareVA->AddVertexBuffer(squareVB);
		m_SquareVA->SetIndexBuffer(squareIB);

		m_MainCamera->SetViewMatrix(glm::mat4(1.0f));
		m_MainCamera->SetProjectionMatrix(glm::mat4(1.0f));

		
		
		const std::string vertexSrc = R"(
				#version 330 core
				
				layout(location = 0) in vec3 a_Position;
				layout(location = 1) in vec4 a_Color;

				out vec3 v_Position;
				out vec4 v_Color;

				uniform mat4 model;
				uniform mat4 view;
				uniform mat4 projection;

				void main()
				{
					v_Position = a_Position;
					v_Color = a_Color;
					gl_Position = projection*view*model*vec4(a_Position,1.0f);

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
		m_SquareShader.reset(new Shader(squareVertexSrc, squareFragmentSrc));
		

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
			
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			RenderCommand::Clear();
			Renderer::BeginScene();
			
			m_SquareShader->Bind();
			Renderer::Submit(m_SquareVA);

			m_Shader->Bind();
			glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
			glm::mat4 view = glm::mat4(1.0f);
			glm::mat4 projection = glm::mat4(1.0f);
			model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
			projection = glm::perspective(glm::radians(45.0f), (float)m_Window->GetWidth() / (float)m_Window->GetHeight(), 0.1f, 100.0f);
			m_Shader->setUniformMat4("view", view);
			m_Shader->setUniformMat4("projection", projection);
			m_Shader->setUniformMat4("model", model);
			Renderer::Submit(m_VertexArray);

			

			Renderer::EndScene();

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