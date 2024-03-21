#include "TestClearColor.hpp"
#include "Renderer.hpp"
#include "imgui/imgui.h"

Test::TestClearColor::TestClearColor() :
	mClearColor{0.2f,0.3f,0.8f,1.0f}
{
}

Test::TestClearColor::~TestClearColor()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Test::TestClearColor::OnUpdate(float delataTime)
{
}

void Test::TestClearColor::OnRender()
{
	glClearColor(mClearColor[0], mClearColor[1], mClearColor[2], mClearColor[3]);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Test::TestClearColor::OnImGuiRender()
{
	ImGui::ColorEdit4("Clear Color", mClearColor);
}
