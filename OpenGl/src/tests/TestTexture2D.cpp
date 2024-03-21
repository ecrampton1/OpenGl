#include "TestTexture2D.hpp"
#include "Renderer.hpp"
#include "imgui/imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


Test::TestTexture2D::TestTexture2D() :
    mTranslationA(200, 200, 0),
    mTranslationB(200,200,0)
{
    float positions[] = {
        100.0f, 100.0f, 0.0f, 0.0f, //0  
        200.0f, 100.0f, 1.0f, 0.0f, //1
        200.0f, 267.0f, 1.0f, 1.0f,//2
        100.0f, 267.0f, 0.0f, 1.0f //3
    };

    unsigned int indices[] = {
        0,1,2,
        2,3,0
    };

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    mShader = std::make_unique<Shader>("res/shaders/basic.shader");
    mVao = std::make_unique<VertexArray>();
    mVertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    mVao->AddBuffer(*mVertexBuffer, layout);
    mIndexBuffer = std::make_unique<IndexBuffer>(indices, 6);

    //This is the viewanthiny outside this space will not be rendered 0
    //converts positions into -1 to 1 on the opengl screen
    mProj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
    mView = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));
    mShader->Bind();

    mTexture = std::make_unique<Texture>("res/textures/image.png");
    mShader->SetUnform1i("u_Texture", 0);//binds to texture 0

}

Test::TestTexture2D::~TestTexture2D()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Test::TestTexture2D::OnUpdate(float delataTime)
{
}

void Test::TestTexture2D::OnRender()
{
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    Renderer renderer;
    mTexture->Bind();

    {
        glm::mat4 model = glm::translate(glm::mat4x4(1.0f), mTranslationA);
        glm::mat4 mvp = mProj * mView * model;
        mShader->Bind();
        mShader->SetUniformMat4f("u_MVP", mvp);//this will multiple the position to get into a fix space
        renderer.Draw(*mVao, *mIndexBuffer, *mShader);
    }

    {
        glm::mat4 model = glm::translate(glm::mat4x4(1.0f), mTranslationB);
        glm::mat4 mvp = mProj * mView * model;
        mShader->Bind();
        mShader->SetUniformMat4f("u_MVP", mvp);//this will multiple the position to get into a fix space
        renderer.Draw(*mVao, *mIndexBuffer, *mShader);
    }

	
}

void Test::TestTexture2D::OnImGuiRender()
{

    ImGui::SliderFloat3("Translation A", &mTranslationA.x, 0.0f, 960.0f);
    ImGui::SliderFloat3("Translation B", &mTranslationB.x, 0.0f, 960.0f);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}
