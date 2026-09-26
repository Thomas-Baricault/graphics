/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#include "graphics/Framebuffer.hpp"


namespace tbaricault::graphics
{

    Framebuffer::Framebuffer() noexcept
    {
        glGenTextures(1, &this->_texture);
        glBindTexture(GL_TEXTURE_2D, this->_texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->_size.x, this->_size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glBindTexture(GL_TEXTURE_2D, 0);
        glGenFramebuffers(1, &this->_frameBuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, this->_frameBuffer);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->_texture, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        return;
    }

    Framebuffer::Framebuffer(Framebuffer&& other) noexcept
        : _handle(other._handle)
        , _texture(other._texture)
        , _size(other._size)
    {
        other._handle = 0;
        other._texture = 0;
        other._size = 0;
        return;
    }

    Framebuffer& Framebuffer::operator=(Framebuffer&& other) noexcept
    {
        if (&other == this)
            return (*this);
        this->_handle = other._handle;
        this->_texture = other._texture;
        this->_size = other._size;
        other._handle = 0;
        other._texture = 0;
        other._size = 0;
        return (*this);
    }

    Framebuffer::~Framebuffer() noexcept
    {
        if (this->_handle)
            glDeleteFramebuffers(1, &this->_handle);
        if (this->_texture)
            glDeleteTextures(1, &this->_texture);
        return;
    }

    Framebuffer::operator bool() const noexcept
    {
        return (this->_handle && this->_texture);
    }

    const tbaricault::math::Vector2<int>& Framebuffer::getSize() const noexcept
    {
        return (this->_size);
    }

    void Framebuffer::setSize(const tbaricault::math::Vector2<int>& value) noexcept
    {
        this->_size = value;
        glBindTexture(GL_TEXTURE_2D, this->_texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->_size.x, this->_size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glBindTexture(GL_TEXTURE_2D, 0);
        return;
    }

}
