#pragma once
#include "Hazel/Input.h"
//#include "Hazel/Core.h"


namespace Hazel {

	class  WindowsInput :public Input
	{
	
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override; // "virtual" here is just a reminder!

		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual std::pair<float, float> GetMousePositionImpl()override;

		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;

	};


}
