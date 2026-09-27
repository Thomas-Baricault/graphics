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
