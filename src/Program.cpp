/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#include <stdexcept>

#include <GL/glew.h>

#include "graphics/Program.hpp"


namespace tbaricault::graphics
{

    Program::BindGuard::BindGuard(const Program& program) noexcept
    {
        glGetIntegerv(GL_CURRENT_PROGRAM, &this->_previous);
        program.bind();
        return;
    }

    Program::BindGuard::~BindGuard() noexcept
    {
        glUseProgram(this->_previous);
        return;
    }


    void Program::unbind() noexcept
    {
        glUseProgram(0);
        return;
    }

    Program::Program(std::span<Shader> shaders)
    {
        this->_handle = glCreateProgram();
        for (const auto& shader : shaders)
            glAttachShader(this->_handle, shader.getHandle());
        glLinkProgram(this->_handle);
        GLint success = GL_FALSE;
        glGetProgramiv(this->_handle, GL_LINK_STATUS, &success);
        if (!success)
        {
            GLint length = 0;
            glGetProgramiv(this->_handle, GL_INFO_LOG_LENGTH, &length);
            std::string log(length, '\0');
            glGetProgramInfoLog(this->_handle, length, nullptr, log.data());
            this->_destroy();
            throw std::runtime_error(log);
        }
        return;
    }

    Program::~Program() noexcept
    {
        this->_destroy();
        return;
    }

    void Program::setUniform(std::string_view name, bool value) const noexcept
    {
        glProgramUniform1i(
            this->_handle,
            glGetUniformLocation(this->_handle, name.data()),
            value
        );
        return;
    }

    void Program::setUniform(std::string_view name, int value) const noexcept
    {
        glProgramUniform1i(
            this->_handle,
            glGetUniformLocation(this->_handle, name.data()),
            value
        );
        return;
    }

    void Program::setUniform(std::string_view name, unsigned int value) const noexcept
    {
        glProgramUniform1ui(
            this->_handle,
            glGetUniformLocation(this->_handle, name.data()),
            value
        );
        return;
    }

    void Program::setUniform(std::string_view name, float value) const noexcept
    {
        glProgramUniform1f(
            this->_handle,
            glGetUniformLocation(this->_handle, name.data()),
            value
        );
        return;
    }

    void Program::setUniform(std::string_view name, double value) const noexcept
    {
        glProgramUniform1d(
            this->_handle,
            glGetUniformLocation(this->_handle, name.data()),
            value
        );
        return;
    }

    void Program::setUniform(std::string_view name, const tbaricault::math::Vector2<int>& value) const noexcept
    {
        glProgramUniform2iv(
            this->_handle,
            glGetUniformLocation(this->_handle, name.data()),
            1,
            &value.x
        );
        return;
    }

    void Program::setUniform(std::string_view name, const tbaricault::math::Vector2<unsigned int>& value) const noexcept
    {
        glProgramUniform2uiv(
            this->_handle,
            glGetUniformLocation(this->_handle, name.data()),
            1,
            &value.x
        );
        return;
    }

    void Program::setUniform(std::string_view name, const tbaricault::math::Vector2<float>& value) const noexcept
    {
        glProgramUniform2fv(
            this->_handle,
            glGetUniformLocation(this->_handle, name.data()),
            1,
            &value.x
        );
        return;
    }

    void Program::setUniform(std::string_view name, const tbaricault::math::Vector2<double>& value) const noexcept
    {
        glProgramUniform2dv(
            this->_handle,
            glGetUniformLocation(this->_handle, name.data()),
            1,
            &value.x
        );
        return;
    }

    void Program::setUniform(std::string_view name, const tbaricault::math::Vector3<int>& value) const noexcept
    {
        glProgramUniform3iv(
            this->_handle,
            glGetUniformLocation(this->_handle, name.data()),
            1,
            &value.x
        );
        return;
    }

    void Program::setUniform(std::string_view name, const tbaricault::math::Vector3<unsigned int>& value) const noexcept
    {
        glProgramUniform3uiv(
            this->_handle,
            glGetUniformLocation(this->_handle, name.data()),
            1,
            &value.x
        );
        return;
    }

    void Program::setUniform(std::string_view name, const tbaricault::math::Vector3<float>& value) const noexcept
    {
        glProgramUniform3fv(
            this->_handle,
            glGetUniformLocation(this->_handle, name.data()),
            1,
            &value.x
        );
        return;
    }

    void Program::setUniform(std::string_view name, const tbaricault::math::Vector3<double>& value) const noexcept
    {
        glProgramUniform3dv(
            this->_handle,
            glGetUniformLocation(this->_handle, name.data()),
            1,
            &value.x
        );
        return;
    }

    void Program::setUniform(std::string_view name, const tbaricault::math::Vector4<int>& value) const noexcept
    {
        glProgramUniform4iv(
            this->_handle,
            glGetUniformLocation(this->_handle, name.data()),
            1,
            &value.x
        );
        return;
    }

    void Program::setUniform(std::string_view name, const tbaricault::math::Vector4<unsigned int>& value) const noexcept
    {
        glProgramUniform4uiv(
            this->_handle,
            glGetUniformLocation(this->_handle, name.data()),
            1,
            &value.x
        );
        return;
    }

    void Program::setUniform(std::string_view name, const tbaricault::math::Vector4<float>& value) const noexcept
    {
        glProgramUniform4fv(
            this->_handle,
            glGetUniformLocation(this->_handle, name.data()),
            1,
            &value.x
        );
        return;
    }

    void Program::setUniform(std::string_view name, const tbaricault::math::Vector4<double>& value) const noexcept
    {
        glProgramUniform4dv(
            this->_handle,
            glGetUniformLocation(this->_handle, name.data()),
            1,
            &value.x
        );
        return;
    }

    void Program::setUniform(std::string_view name, const tbaricault::math::Matrix<2, 2, float>& value) const noexcept
    {
        glProgramUniformMatrix2fv(
            this->_handle,
            glGetUniformLocation(this->_handle, name.data()),
            1,
            GL_TRUE,
            &value(0, 0)
        );
        return;
    }

    void Program::setUniform(std::string_view name, const tbaricault::math::Matrix<2, 2, double>& value) const noexcept
    {
        glProgramUniformMatrix2dv(
            this->_handle,
            glGetUniformLocation(this->_handle, name.data()),
            1,
            GL_TRUE,
            &value(0, 0)
        );
        return;
    }

    void Program::setUniform(std::string_view name, const tbaricault::math::Matrix<3, 3, float>& value) const noexcept
    {
        glProgramUniformMatrix3fv(
            this->_handle,
            glGetUniformLocation(this->_handle, name.data()),
            1,
            GL_TRUE,
            &value(0, 0)
        );
        return;
    }

    void Program::setUniform(std::string_view name, const tbaricault::math::Matrix<3, 3, double>& value) const noexcept
    {
        glProgramUniformMatrix3dv(
            this->_handle,
            glGetUniformLocation(this->_handle, name.data()),
            1,
            GL_TRUE,
            &value(0, 0)
        );
        return;
    }

    void Program::setUniform(std::string_view name, const tbaricault::math::Matrix<4, 4, float>& value) const noexcept
    {
        glProgramUniformMatrix4fv(
            this->_handle,
            glGetUniformLocation(this->_handle, name.data()),
            1,
            GL_TRUE,
            &value(0, 0)
        );
        return;
    }

    void Program::setUniform(std::string_view name, const tbaricault::math::Matrix<4, 4, double>& value) const noexcept
    {
        glProgramUniformMatrix4dv(
            this->_handle,
            glGetUniformLocation(this->_handle, name.data()),
            1,
            GL_TRUE,
            &value(0, 0)
        );
        return;
    }

    void Program::setUniform(std::string_view name, const tbaricault::math::Matrix<2, 3, float>& value) const noexcept
    {
        glProgramUniformMatrix2x3fv(
            this->_handle,
            glGetUniformLocation(this->_handle, name.data()),
            1,
            GL_TRUE,
            &value(0, 0)
        );
        return;
    }

    void Program::setUniform(std::string_view name, const tbaricault::math::Matrix<2, 3, double>& value) const noexcept
    {
        glProgramUniformMatrix2x3dv(
            this->_handle,
            glGetUniformLocation(this->_handle, name.data()),
            1,
            GL_TRUE,
            &value(0, 0)
        );
        return;
    }

    void Program::setUniform(std::string_view name, const tbaricault::math::Matrix<2, 4, float>& value) const noexcept
    {
        glProgramUniformMatrix2x4fv(
            this->_handle,
            glGetUniformLocation(this->_handle, name.data()),
            1,
            GL_TRUE,
            &value(0, 0)
        );
        return;
    }

    void Program::setUniform(std::string_view name, const tbaricault::math::Matrix<2, 4, double>& value) const noexcept
    {
        glProgramUniformMatrix2x4dv(
            this->_handle,
            glGetUniformLocation(this->_handle, name.data()),
            1,
            GL_TRUE,
            &value(0, 0)
        );
        return;
    }

    void Program::setUniform(std::string_view name, const tbaricault::math::Matrix<3, 2, float>& value) const noexcept
    {
        glProgramUniformMatrix3x2fv(
            this->_handle,
            glGetUniformLocation(this->_handle, name.data()),
            1,
            GL_TRUE,
            &value(0, 0)
        );
        return;
    }

    void Program::setUniform(std::string_view name, const tbaricault::math::Matrix<3, 2, double>& value) const noexcept
    {
        glProgramUniformMatrix3x2dv(
            this->_handle,
            glGetUniformLocation(this->_handle, name.data()),
            1,
            GL_TRUE,
            &value(0, 0)
        );
        return;
    }

    void Program::setUniform(std::string_view name, const tbaricault::math::Matrix<3, 4, float>& value) const noexcept
    {
        glProgramUniformMatrix3x4fv(
            this->_handle,
            glGetUniformLocation(this->_handle, name.data()),
            1,
            GL_TRUE,
            &value(0, 0)
        );
        return;
    }

    void Program::setUniform(std::string_view name, const tbaricault::math::Matrix<3, 4, double>& value) const noexcept
    {
        glProgramUniformMatrix3x4dv(
            this->_handle,
            glGetUniformLocation(this->_handle, name.data()),
            1,
            GL_TRUE,
            &value(0, 0)
        );
        return;
    }

    void Program::setUniform(std::string_view name, const tbaricault::math::Matrix<4, 2, float>& value) const noexcept
    {
        glProgramUniformMatrix4x2fv(
            this->_handle,
            glGetUniformLocation(this->_handle, name.data()),
            1,
            GL_TRUE,
            &value(0, 0)
        );
        return;
    }

    void Program::setUniform(std::string_view name, const tbaricault::math::Matrix<4, 2, double>& value) const noexcept
    {
        glProgramUniformMatrix4x2dv(
            this->_handle,
            glGetUniformLocation(this->_handle, name.data()),
            1,
            GL_TRUE,
            &value(0, 0)
        );
        return;
    }

    void Program::setUniform(std::string_view name, const tbaricault::math::Matrix<4, 3, float>& value) const noexcept
    {
        glProgramUniformMatrix4x3fv(
            this->_handle,
            glGetUniformLocation(this->_handle, name.data()),
            1,
            GL_TRUE,
            &value(0, 0)
        );
        return;
    }

    void Program::setUniform(std::string_view name, const tbaricault::math::Matrix<4, 3, double>& value) const noexcept
    {
        glProgramUniformMatrix4x3dv(
            this->_handle,
            glGetUniformLocation(this->_handle, name.data()),
            1,
            GL_TRUE,
            &value(0, 0)
        );
        return;
    }

    void Program::bind() const noexcept
    {
        glUseProgram(this->_handle);
        return;
    }

    Program::BindGuard Program::use() const noexcept
    {
        return (BindGuard(*this));
    }

    void Program::_destroy() noexcept
    {
        if (this->_handle)
        {
            glDeleteProgram(this->_handle);
            this->_handle = 0;
        }
        return;
    }

}
