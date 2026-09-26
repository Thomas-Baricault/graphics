/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#include <tbaricault/colors.hpp>

#include "graphics/Texture.hpp"


namespace tbaricault::graphics
{

    void Texture::unuse(GLenum unit) noexcept
    {
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(GL_TEXTURE_2D, 0);
        return;
    }

    Texture::Texture(const Texture& other)
    {
        if (other._handle)
        {
            this->_size = other._size;
            tbaricault::colors::RGBA* data = other._extractData();
            this->_handle = Texture::_createTexture(this->_size, data);
            delete[] data;
        }
        return;
    }

    Texture::Texture(Texture&& other) noexcept
        : _handle(other._handle)
        , _size(other._size)
    {
        other._handle = 0;
        other._size = 0;
        return;
    }

    Texture::Texture(const tbaricault::math::Vector2<int>& size) noexcept
    {
        
    }

    Texture::Texture(const tbaricault::images::Image& image)
    {
        if (image)
        {
            this->_size = image.getSize();
            this->_handle = Texture::_createTexture(this->_size, image.getPixels());
        }
        return;
    }

    Texture::~Texture()
    {
        if (this->_handle)
            glDeleteTextures(1, &this->_handle);
        return;
    }

    Texture& Texture::operator=(const Texture& other)
    {
        if (&other == this)
            return (*this);
        if (this->_handle)
            glDeleteTextures(1, &this->_handle);
        if (other._handle)
        {
            this->_size = other._size;
            tbaricault::colors::RGBA* data = other._extractData();
            this->_handle = Texture::_createTexture(this->_size, data);
            delete[] data;
        }
        else
        {
            this->_handle = 0;
            this->_size = tbaricault::math::Vector2<int>();
        }
        return (*this);
    }

    Texture& Texture::operator=(Texture&& other) noexcept
    {
        if (&other == this)
            return (*this);
        if (this->_handle)
            glDeleteTextures(1, &this->_handle);
        this->_handle = other._handle;
        this->_size = other._size;
        other._handle = 0;
        other._size = 0;
        return (*this);
    }

    Texture::operator bool() const noexcept
    {
        return (this->_handle != 0);
    }

    Texture::operator tbaricault::images::Image() const
    {
        return (tbaricault::images::Image(this->_size, this->_extractData(), false));
    }

    GLuint Texture::getHandle() const noexcept
    {
        return (this->_handle);
    }

    const tbaricault::math::Vector2<int>& Texture::getSize() const noexcept
    {
        return (this->_size);
    }

    void Texture::use(GLenum unit) const noexcept
    {
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(GL_TEXTURE_2D, this->_handle);
        return;
    }

    GLuint Texture::_createTexture(const tbaricault::math::Vector2<int>& size, const tbaricault::colors::RGBA* data) noexcept
    {
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glBindTexture(GL_TEXTURE_2D, 0);
        return (texture);
    }

    tbaricault::colors::RGBA* Texture::_extractData() const
    {
        if (this->_handle == 0)
            return (nullptr);
        tbaricault::colors::RGBA* data = new tbaricault::colors::RGBA[this->_size.x * this->_size.y];
        glBindTexture(GL_TEXTURE_2D, this->_handle);
        glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glBindTexture(GL_TEXTURE_2D, 0);
        return (data);
    }

}
