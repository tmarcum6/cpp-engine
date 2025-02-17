//#ifndef SHADER_H
//#define SHADER_H
//
//#include <glad/glad.h>
//#include <glm/glm.hpp>
//#include <string>
//#include <fstream>
//#include <sstream>
//#include <iostream>
//
//#include "Mat44.h"
//#include "Vec3.h"
//
//class Shader
//{
//public:
//    unsigned int ID;
//
//    Shader(const char* vertexPath, const char* fragmentPath)
//    {
//        // 1. retrieve the vertex/fragment source code from filePath', .                        
//        std::string vertexCode;
//        std::string fragmentCode;
//        std::ifstream vShaderFile;
//        std::ifstream fShaderFile;
//        // ensure ifstream objects can throw exceptions:
//        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
//        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
//        try
//        {
//            // open files
//            vShaderFile.open(vertexPath);
//            fShaderFile.open(fragmentPath);
//            std::stringstream vShaderStream, fShaderStream;
//            // read file's buffer contents into streams
//            vShaderStream << vShaderFile.rdbuf();
//            fShaderStream << fShaderFile.rdbuf();
//            // close file handlers
//            vShaderFile.close();
//            fShaderFile.close();
//            // convert stream into string
//            vertexCode = vShaderStream.str();
//            fragmentCode = fShaderStream.str();
//        }
//        catch (std::ifstream::failure& e)
//        {
//            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
//        }
//        const char* vShaderCode = vertexCode.c_str();
//        const char* fShaderCode = fragmentCode.c_str();
//        // 2. compile shaders
//        unsigned int vertex, fragment;
//        // vertex shader
//        vertex = glCreateShader(GL_VERTEX_SHADER);
//        glShaderSource(vertex, 1, &vShaderCode, NULL);
//        glCompileShader(vertex);
//        checkCompileErrors(vertex, "VERTEX");
//        // fragment Shader
//        fragment = glCreateShader(GL_FRAGMENT_SHADER);
//        glShaderSource(fragment, 1, &fShaderCode, NULL);
//        glCompileShader(fragment);
//        checkCompileErrors(fragment, "FRAGMENT");
//        // shader Program
//        ID = glCreateProgram();
//        glAttachShader(ID, vertex);
//        glAttachShader(ID, fragment);
//        glLinkProgram(ID);
//        checkCompileErrors(ID, "PROGRAM");
//        // delete the shaders as they're linked into our program now and no longer necessary
//        glDeleteShader(vertex);
//        glDeleteShader(fragment);   
//    }
//
//    Shader(std::string const& vertexPath, std::string const& fragmentPath)
//    {
//        std::string fragmentFileContents;
//        std::string vertexFileContents;
//
//        // Read in the vertex shader
//        std::ifstream vertex_file;
//
//        vertex_file.open(vertexPath);
//        std::stringstream vertex_file_stream;
//        vertex_file_stream << vertex_file.rdbuf();
//        vertex_file.close();
//        vertexFileContents = vertex_file_stream.str();
//
//        // Read in the fragment shader
//        std::ifstream fragment_file;
//
//        fragment_file.open(fragmentPath);
//        std::stringstream fragment_file_stream;
//        fragment_file_stream << fragment_file.rdbuf();
//        fragment_file.close();
//        fragmentFileContents = fragment_file_stream.str();
//
//        GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
//
//        const GLchar* vertex_shader_source = vertexFileContents.c_str();
//        glShaderSource(vertex_shader, 1, &vertex_shader_source, nullptr);
//        glCompileShader(vertex_shader);
//
//        int success;
//        char infoLog[512];
//        glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
//
//        if (!success)
//        {
//            glGetShaderInfoLog(vertex_shader, 512, nullptr, infoLog);
//            std::cerr << "Error compiling vertex shader: " << infoLog << "\n";
//        }
//
//
//        GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
//
//        const GLchar* fragment_shader_source = fragmentFileContents.c_str();
//        glShaderSource(fragment_shader, 1, &fragment_shader_source, nullptr);
//        glCompileShader(fragment_shader);
//        glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
//
//        if (!success)
//        {
//            glGetShaderInfoLog(fragment_shader, 512, nullptr, infoLog);
//            std::cerr << "Error compiling fragment shader: " << infoLog << "\n";
//        }
//
//
//        mId = glCreateProgram();
//
//        glAttachShader(mId, vertex_shader);
//        glAttachShader(mId, fragment_shader);
//        glLinkProgram(mId);
//        glGetProgramiv(mId, GL_LINK_STATUS, &success);
//
//        if (!success)
//        {
//            glGetProgramInfoLog(mId, 512, nullptr, infoLog);
//            std::cerr << "Error linking shaders: " << infoLog << "\n";
//        }
//
//        glDeleteShader(vertex_shader);
//        glDeleteShader(fragment_shader);
//    }
//
//
//    void Use()
//    {
//        glUseProgram(ID);
//    }
//
//    void setBool(const std::string& name, bool value) const
//    {
//        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
//    }
//
//    void setInt(const std::string& name, int value) const
//    {
//        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
//    }
//
//    void setFloat(const std::string& name, float value) const
//    {
//        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
//    }
//
//    void setVec2(const std::string& name, const glm::vec2& value) const
//    {
//        glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
//    }
//
//    void setVec2(const std::string& name, float x, float y) const
//    {
//        glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
//    }
//
//    void setVec3(const std::string& name, const glm::vec3& value) const
//    {
//        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
//    }
//
//    void setVec3(const std::string& name, float x, float y, float z) const
//    {
//        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
//    }
//
//    void setVec4(const std::string& name, const glm::vec4& value) const
//    {
//        glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
//    }
//
//    void setVec4(const std::string& name, float x, float y, float z, float w)
//    {
//        glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
//    }
//
//    void setMat2(const std::string& name, const glm::mat2& mat) const
//    {
//        glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
//    }
//
//    void setMat3(const std::string& name, const glm::mat3& mat) const
//    {
//        glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
//    }
//
//    void setMat4(const std::string& name, const glm::mat4& mat) const
//    {
//        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
//    }
//
//    template<typename T>
//    void SetUniform(const std::string& name, const T& value)
//    {
//        if constexpr (std::is_same_v<T, Mat44>)
//        {
//            glUniformMatrix4fv(glGetUniformLocation(mId, name.c_str()), 1, GL_TRUE, (GLfloat*)value.m);
//        }
//        else if constexpr (std::is_same_v<T, Vec3>)
//        {
//            glUniform3fv(glGetUniformLocation(mId, name.c_str()), 1, (GLfloat*)&value);
//        }
//    }
//
//private:
//    GLuint mId;
//
//    void checkCompileErrors(GLuint shader, std::string type)
//    {
//        GLint success;
//        GLchar infoLog[1024];
//        if (type != "PROGRAM")
//        {
//            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
//            if (!success)
//            {
//                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
//                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
//            }
//        }
//        else
//        {
//            glGetProgramiv(shader, GL_LINK_STATUS, &success);
//            if (!success)
//            {
//                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
//                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
//            }
//        }
//    }
//};
//#endif
