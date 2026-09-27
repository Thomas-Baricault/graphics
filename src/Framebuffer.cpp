/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#include "graphics/Framebuffer.hpp"


namespace tbaricault::graphics
{

    Framebuffer::BindGuard::BindGuard(const Framebuffer& framebuffer, Mode mode) noexcept
        : _mode(mode)
    {
        glGetIntegerv(
            mode == Mode::Draw
                ? GL_DRAW_FRAMEBUFFER_BINDING
                : GL_READ_FRAMEBUFFER_BINDING,
            &this->_previous
        );
        framebuffer.bind(mode);
        return;
    }

    Framebuffer::BindGuard::~BindGuard() noexcept
    {
        glBindFramebuffer(static_cast<GLenum>(this->_mode), this->_previous);
        return;
    }


    void Framebuffer::unbind(Mode mode) noexcept
    {
        glBindFramebuffer(static_cast<GLenum>(mode), 0);
        return;
    }

    Framebuffer::Framebuffer(Framebuffer&& other) noexcept
        : _handle(other._handle)
        , _texture(std::move(other._texture))
    {
        other._handle = 0;
        return;
    }

    Framebuffer& Framebuffer::operator=(Framebuffer&& other) noexcept
    {
        if (&other == this)
            return (*this);
        if (this->_handle)
            glDeleteFramebuffers(1, &this->_handle);
        this->_handle = other._handle;
        this->_texture = std::move(other._texture);
        other._handle = 0;
        return (*this);
    }

    Framebuffer::~Framebuffer() noexcept
    {
        if (this->_handle)
            glDeleteFramebuffers(1, &this->_handle);
        return;
    }

    Framebuffer::operator bool() const noexcept
    {
        return (this->_handle && this->_texture);
    }

    GLuint Framebuffer::getHandle() const noexcept
    {
        return (this->_handle);
    }

    const tbaricault::math::Vector2<int>& Framebuffer::getSize() const noexcept
    {
        return (this->_texture.getSize());
    }

    void Framebuffer::setSize(const tbaricault::math::Vector2<int>& value) noexcept
    {
        if (!this->_handle)
            glCreateFramebuffers(1, &this->_handle);
        if (!this->_handle)
            return;
        this->_texture.setSize(value);
        glNamedFramebufferTexture(
            this->_handle,
            GL_COLOR_ATTACHMENT0,
            this->_texture.getHandle(),
            0
        );
        return;
    }

    void Framebuffer::bind(Mode mode) const noexcept
    {
        glBindFramebuffer(static_cast<GLenum>(mode), this->_handle);
        return;
    }

    Framebuffer::BindGuard Framebuffer::use(Mode mode) const noexcept
    {
        return (BindGuard(*this, mode));
    }

}
