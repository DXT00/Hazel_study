#include<Hazel.h>


class ExampleLayer : public Hazel::Layer{
public:
	ExampleLayer()
		:Layer("Example"){}


	void OnUpdate() override {
	//	HZ_INFO("ExampleLayer::Update");
		if(Hazel::Input::IsKeyPressed(HZ_KEY_TAB))
			HZ_INFO("Tab key is pressed");
	
	}
	void OnEvent(Hazel::Event& event) override {
		//HZ_TRACE("{0}",e);

		if (event.GetEventype() == Hazel::EventType::KeyPressed) {
			Hazel::KeyPressedEvent&e = (Hazel::KeyPressedEvent&)event;
			HZ_TRACE("{0}", (char)e.GetKeyCode());
		}


	}
};



class SandBox:public Hazel::Application
{
public:
	SandBox() {
		PushLayer(new ExampleLayer());
		PushLayer(new Hazel::ImGuiLayer());

	}
	~SandBox() {

	}
};

Hazel::Application *  Hazel::CreateApplication() {
	return new SandBox();
}
