#include<Hazel.h>


class ExampleLayer : public Hazel::Layer{
public:
	ExampleLayer()
		:Layer("Example"){}


	void OnUpdate() override {
	//	HZ_INFO("ExampleLayer::Update");
	
	}
	void OnEvent(Hazel::Event& e) override {
		HZ_TRACE("{0}",e);

	}
};



class SandBox:public Hazel::Application
{
public:
	SandBox() {
		PushLayer(new ExampleLayer());
	}
	~SandBox() {

	}
};

Hazel::Application *  Hazel::CreateApplication() {
	return new SandBox();
}
