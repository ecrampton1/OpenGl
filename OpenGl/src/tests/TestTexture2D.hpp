#pragma once

#include "Test.hpp"
#include "Texture.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include <memory>

namespace Test {

	class TestTexture2D : public Test
	{
	public:
		TestTexture2D();
		~TestTexture2D();

		void OnUpdate(float delataTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		
		glm::vec3 mTranslationA, mTranslationB;
		std::unique_ptr<VertexArray> mVao;
		std::unique_ptr < IndexBuffer> mIndexBuffer;
		std::unique_ptr < Shader> mShader;
		std::unique_ptr<Texture> mTexture;
		glm::mat4 mProj;
		glm::mat4 mView;
		std::unique_ptr < VertexBuffer> mVertexBuffer;
	};
}