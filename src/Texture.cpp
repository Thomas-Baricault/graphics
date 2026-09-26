/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#include <algorithm>
#include <cmath>

#include "graphics/Texture.hpp"


namespace tbaricault::graphics
{

    Texture::BindGuard::BindGuard(unsigned int unit, const Texture& texture) noexcept
        : _unit(unit)
    {
        glGetIntegeri_v(GL_TEXTURE_BINDING_2D, this->_unit, &this->_previous);
        texture.bind(unit);
        return;
    }

    Texture::BindGuard::~BindGuard() noexcept
    {
        glBindTextureUnit(this->_unit, this->_previous);
        return;
    }


    int Texture::mipmapLevels(const tbaricault::math::Vector2<int>& size)
    {
        if (size.isZero())
            return (1);
        return (1 + static_cast<int>(std::floor(std::log2(std::max(size.x, size.y)))));
    }

    void Texture::unbind(unsigned int unit) noexcept
    {
        glBindTextureUnit(unit, 0);
        return;
    }

    Texture::Texture(Texture&& other) noexcept
        : _handle(other._handle)
        , _size(other._size)
        , _mipmaps(other._mipmaps)
    {
        other._handle = 0;
        other._size = 0;
        other._mipmaps = 1;
        return;
    }

    Texture::Texture(const tbaricault::math::Vector2<int>& size) noexcept
    {
        this->setSize(size);
        return;
    }

    Texture::Texture(const tbaricault::images::Image& image, int mipmaps)
    {
        this->_mipmaps = mipmaps == 0
            ? Texture::mipmapLevels(image.getSize())
            : mipmaps;
        this->setSize(image.getSize());
        if (this->_handle)
            this->setMipmap(0, image);
        return;
    }

    Texture::~Texture()
    {
        if (this->_handle)
            glDeleteTextures(1, &this->_handle);
        return;
    }

    Texture& Texture::operator=(Texture&& other) noexcept
    {
        if (&other == this)
            return (*this);
        if (this->_handle)
            glDeleteTextures(1, &this->_handle);
        this->_handle = other._handle;
        this->_size = other._size;
        this->_mipmaps = other._mipmaps;
        other._handle = 0;
        other._size = 0;
        other._mipmaps = 1;
        return (*this);
    }

    Texture::operator bool() const noexcept
    {
        return (this->_handle != 0);
    }

    Texture::operator tbaricault::images::Image() const
    {
        if (this->_handle == 0)
            return (tbaricault::images::Image());
        tbaricault::colors::RGBA* data = new tbaricault::colors::RGBA[this->_size.x * this->_size.y];
        glGetTextureImage(this->_handle, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->_size.x * this->_size.y * 4, data);
        return (tbaricault::images::Image(this->_size, data, false));
    }

    GLuint Texture::getHandle() const noexcept
    {
        return (this->_handle);
    }

    Texture::Filter Texture::getMinFilter() const noexcept
    {
        GLint result;
        glGetTextureParameteriv(this->_handle, GL_TEXTURE_MIN_FILTER, &result);
        return (static_cast<Filter>(result));
    }

    Texture::Filter Texture::getMagFilter() const noexcept
    {
        GLint result;
        glGetTextureParameteriv(this->_handle, GL_TEXTURE_MAG_FILTER, &result);
        return (static_cast<Filter>(result));
    }

    Texture::Wrap Texture::getWrapS() const noexcept
    {
        GLint result;
        glGetTextureParameteriv(this->_handle, GL_TEXTURE_WRAP_S, &result);
        return (static_cast<Wrap>(result));
    }

    Texture::Wrap Texture::getWrapT() const noexcept
    {
        GLint result;
        glGetTextureParameteriv(this->_handle, GL_TEXTURE_WRAP_T, &result);
        return (static_cast<Wrap>(result));
    }

    tbaricault::colors::Color Texture::getBorderColor() const noexcept
    {
        GLfloat result[4];
        glGetTextureParameterfv(this->_handle, GL_TEXTURE_BORDER_COLOR, result);
        return (tbaricault::colors::Color(
            result[0] * 255,
            result[1] * 255,
            result[2] * 255,
            result[3] * 255
        ));
    }

    const tbaricault::math::Vector2<int>& Texture::getSize() const noexcept
    {
        return (this->_size);
    }

    int Texture::getMipmaps() const noexcept
    {
        return (this->_mipmaps);
    }

    void Texture::setMinFilter(Filter value) noexcept
    {
        glTextureParameteri(this->_handle, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(value));
        return;
    }

    void Texture::setMagFilter(Filter value) noexcept
    {
        glTextureParameteri(this->_handle, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(value));
        return;
    }

    void Texture::setWrapS(Wrap value) noexcept
    {
        glTextureParameteri(this->_handle, GL_TEXTURE_WRAP_S, static_cast<GLint>(value));
        return;
    }

    void Texture::setWrapT(Wrap value) noexcept
    {
        glTextureParameteri(this->_handle, GL_TEXTURE_WRAP_T, static_cast<GLint>(value));
        return;
    }

    void Texture::setBorderColor(const tbaricault::colors::Color& value) noexcept
    {
        float color[] = {
            value.r / 255.0f,
            value.g / 255.0f,
            value.b / 255.0f,
            value.a / 255.0f,
        };
        glTextureParameterfv(this->_handle, GL_TEXTURE_BORDER_COLOR, color);
        return;
    }

    void Texture::setSize(const tbaricault::math::Vector2<int>& value) noexcept
    {
        if (this->_handle)
            glDeleteTextures(1, &this->_handle);
        if (value.x <= 0 || value.y <= 0)
        {
            this->_handle = 0;
            this->_size = 0;
            return;
        }
        this->_size = value;
        glCreateTextures(GL_TEXTURE_2D, 1, &this->_handle);
        if (this->_handle)
            glTextureStorage2D(this->_handle, this->_mipmaps, GL_RGBA8, this->_size.x, this->_size.y);
        return;
    }

    void Texture::setMipmap(int level, const tbaricault::images::Image& image, const tbaricault::math::Vector2<int>& offset) noexcept
    {
        if (this->_handle == 0 || level < 0 || level >= this->_mipmaps || !image)
            return;
        glTextureSubImage2D(
            this->_handle,
            level,
            offset.x, offset.y,
            image.getSize().x, image.getSize().y,
            GL_RGBA, GL_UNSIGNED_BYTE,
            image.getPixels()
        );
    }

    void Texture::generateMipmap() noexcept
    {
        glGenerateTextureMipmap(this->_handle);
        return;
    }

    void Texture::bind(unsigned int unit) const noexcept
    {
        glBindTextureUnit(unit, this->_handle);
        return;
    }

    Texture::BindGuard Texture::use(unsigned int unit) const noexcept
    {
        return (BindGuard(unit, *this));
    }

}
