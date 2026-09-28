/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#include <stdexcept>

#include "graphics/Shader.hpp"


namespace tbaricault::graphics
{

    Shader::Shader(Type type, std::string_view src)
    {
        this->_handle = glCreateShader(static_cast<GLenum>(type));
        if (!this->_handle)
            return;
        const char* ptr = src.data();
        glShaderSource(this->_handle, 1, &ptr, nullptr);
        glCompileShader(this->_handle);
        GLint success = GL_FALSE;
        glGetShaderiv(this->_handle, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            GLint length = 0;
            glGetShaderiv(this->_handle, GL_INFO_LOG_LENGTH, &length);
            std::string log(length, '\0');
            glGetShaderInfoLog(this->_handle, length, nullptr, log.data());
            this->_destroy();
            throw std::runtime_error(log);
        }
        return;
    }

    Shader::~Shader() noexcept
    {
        this->_destroy();
        return;
    }

    void Shader::_destroy() noexcept
    {
        if (this->_handle)
        {
            glDeleteShader(this->_handle);
            this->_handle = 0;
        }
        return;
    }

}
