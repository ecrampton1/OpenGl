#include "Renderer.hpp"
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"
#include "tests/TestClearColor.hpp"
#include "tests/TestTexture2D.hpp"
#include <array>

enum class TestIndex
{
    NONE,
    CLEAR_COLOR,
    TEXTURE_2D
};


struct TestsToRun
{
    std::string Name;
    TestIndex Test;
};

static void close_callback(GLFWwindow* window)
{
    printf("Closed  WIndow\n");
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    //Get out to the game
    switch (action)
    {
    case GLFW_PRESS:
    {
        std::cout << "Pressed: " << key << std::endl;
        break;
    }
    case GLFW_RELEASE:
    {
        std::cout << "Released: " << key << std::endl;
        break;
    }
    case GLFW_REPEAT:
    {
        std::cout << "Repeat: " << key << std::endl;
        break;
    }
    }
}


static void CreateTestInstance(Test::Test** test, TestIndex index)
{

    if (nullptr != *test) {
        delete* test;
    }

    switch (index)
    {
    case TestIndex::CLEAR_COLOR:
        *test = new Test::TestClearColor();
        break;
    case TestIndex::TEXTURE_2D:
        *test = new Test::TestTexture2D();
        break;
    case TestIndex::NONE:
    default:
        *test = nullptr;
    }
}

int main(void)
{
    GLFWwindow* window = nullptr;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    //specify the version (core vs compatibility)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error" << std::endl;
    }

    glfwSetKeyCallback(window, key_callback);
    glfwSetWindowCloseCallback(window, close_callback);

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(MessageCallback, NULL);

    std::cout << glGetString(GL_VERSION) << std::endl;


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Renderer renderer;

    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(window, true);
    ImGui::StyleColorsDark();

    Test::Test* current_test = nullptr;
    TestIndex current_index = TestIndex::NONE;

    std::array< TestsToRun, 3> run_tests{ {
        {"None",TestIndex::NONE},
        {"Clear Color Test",TestIndex::CLEAR_COLOR},
        {"Texture 2D",TestIndex::TEXTURE_2D}
    } };

    bool test_check = false;
    int counter = 0;
    std::string selected_test = "None";
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.clear();



        ImGui_ImplGlfwGL3_NewFrame();

        if (nullptr != current_test)
        {
            if (ImGui::Button("<-"))                            // Buttons return true when clicked (NB: most widgets return true when edited/activated)
            {
                CreateTestInstance(&current_test, TestIndex::NONE);
            }
        }
        else
        {
            for (auto& item : run_tests) {
                if (ImGui::Button(item.Name.c_str()))                            // Buttons return true when clicked (NB: most widgets return true when edited/activated)
                {
                    CreateTestInstance(&current_test, item.Test);
                    selected_test = item.Name;
                    break;
                }
            }
        }

        ImGui::Text("%s", selected_test.c_str());


        if (nullptr != current_test)
        {
            current_test->OnUpdate(0.0f);
            current_test->OnRender();
            current_test->OnImGuiRender();
        }

        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

        //glDrawElementss.... used as well.
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    //glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}