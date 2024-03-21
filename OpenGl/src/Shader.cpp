#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.hpp"
#include "Shader.hpp"




Shader::Shader(const std::string& filePath) : 
    mFilePath(filePath), mRendererId(0)
{
    ShaderProgramSource source = ParseShader();
    mRendererId = CreateShader(source.VertexSource, source.FragmentSource);
    
}

Shader::~Shader()
{
    glDeleteProgram(mRendererId);
}

void Shader::Bind() const
{
    glUseProgram(mRendererId);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

void Shader::SetUnform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    //cache the location
    glUniform4f(GetUnformLocation(name), v0, v1, v2,v3);
}

void Shader::SetUnform1i(const std::string& name, int value)
{
    glUniform1i(GetUnformLocation(name), value);
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
    //opengl expects columns
    glUniformMatrix4fv(GetUnformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

int Shader::GetUnformLocation(const std::string& name)
{
    if (mUniformLocation.end() == mUniformLocation.find(name))
    {
        int location = glGetUniformLocation(mRendererId, name.c_str());
        if (-1 == location)
        {
            std::cout << __FUNCSIG__ << " - Warning Uniform " << name << "doesnt exist" << std::endl;
        }
        else
        {
            mUniformLocation[name] = location;
        }
    }

    return mUniformLocation[name];
}

//There should be a faster way
//Also horrible error handling.
ShaderProgramSource  Shader::ParseShader()
{
    std::ifstream stream(mFilePath);

    std::string line;
    ShaderType type = ShaderType::NONE;
    std::stringstream ss[2];

    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }

    return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    //careful the source is set yo
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    //TODO: Error handling
    int result = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result); //integer vector
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);

        std::cout << type << " Compile Failed: " << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);  //program 1 (compiled)
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader); //program 2 (compiled)

    glAttachShader(program, vs); //(compile)
    glAttachShader(program, fs); //(compile)
    glLinkProgram(program);// (link)
    glValidateProgram(program);

    //may be better to detachshader instead of delete.  for debuggers
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}
