#pragma once
#include "Hazel/Input.h"
#include "Hazel/Core.h"


namespace Hazel {

	class HAZEL_API WindowsInput :public Input
	{
	public:
		WindowsInput();
		~WindowsInput();


	protected:
		virtual bool IsKeyPressedImpl(int keycode) override; // "virtual" here is just a reminder!

		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
		virtual std::pair<float, float> GetMousePositionImpl()override;

	};


}
