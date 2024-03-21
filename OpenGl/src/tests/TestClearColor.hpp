#pragma once

#include "Test.hpp"

namespace Test {

	class TestClearColor : public Test
	{
	public:
		TestClearColor();
		~TestClearColor();

		void OnUpdate(float delataTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		float mClearColor[4];

	};
}