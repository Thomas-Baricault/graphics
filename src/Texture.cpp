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
        glGetIntegeri_v(
            GL_TEXTURE_BINDING_2D,
            this->_unit,
            &this->_previous
        );
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

    Texture::Texture(const tbaricault::math::Vector2<int>& size) noexcept
    {
        this->setSize(size);
        return;
    }

    Texture::Texture(const tbaricault::images::Image& image, int mipmaps) noexcept
    {
        this->_mipmaps = mipmaps == 0
            ? Texture::mipmapLevels(image.getSize())
            : mipmaps;
        this->setSize(image.getSize());
        if (this->_handle)
            this->setMipmap(0, image);
        return;
    }

    Texture::~Texture() noexcept
    {
        this->_destroy();
        return;
    }

    Texture::operator tbaricault::images::Image() const
    {
        if (!this->_handle)
            return (tbaricault::images::Image());
        tbaricault::colors::RGBA* data = new tbaricault::colors::RGBA[this->_size.x * this->_size.y];
        glGetTextureImage(
            this->_handle,
            0,
            GL_RGBA, GL_UNSIGNED_BYTE,
            this->_size.x * this->_size.y * 4,
            data
        );
        return (tbaricault::images::Image(this->_size, data, false));
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

    int Texture::getMipmapBaseLevel() const noexcept
    {
        GLint result;
        glGetTextureParameteriv(this->_handle, GL_TEXTURE_BASE_LEVEL, &result);
        return (result);
    }

    int Texture::getMipmapMaxLevel() const noexcept
    {
        GLint result;
        glGetTextureParameteriv(this->_handle, GL_TEXTURE_MAX_LEVEL, &result);
        return (result);
    }

    float Texture::getMinLOD() const noexcept
    {
        GLfloat result;
        glGetTextureParameterfv(this->_handle, GL_TEXTURE_MIN_LOD, &result);
        return (result);
    }

    float Texture::getMaxLOD() const noexcept
    {
        GLfloat result;
        glGetTextureParameterfv(this->_handle, GL_TEXTURE_MAX_LOD, &result);
        return (result);
    }

    float Texture::getLODBias() const noexcept
    {
        GLfloat result;
        glGetTextureParameterfv(this->_handle, GL_TEXTURE_LOD_BIAS, &result);
        return (result);
    }

    Texture::Compare Texture::getCompare() const noexcept
    {
        GLint result;
        glGetTextureParameteriv(this->_handle, GL_TEXTURE_COMPARE_MODE, &result);
        if (result == GL_NONE)
            return (Compare::None);
        glGetTextureParameteriv(this->_handle, GL_TEXTURE_COMPARE_FUNC, &result);
        return (static_cast<Compare>(result));
    }

    const tbaricault::math::Vector2<int>& Texture::getSize() const noexcept
    {
        return (this->_size);
    }

    int Texture::getMipmapLevels() const noexcept
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

    void Texture::setMipmapBaseLevel(int value) noexcept
    {
        glTextureParameteri(this->_handle, GL_TEXTURE_BASE_LEVEL, value);
        return;
    }

    void Texture::setMipmapMaxLevel(int value) noexcept
    {
        glTextureParameteri(this->_handle, GL_TEXTURE_MAX_LEVEL, value);
        return;
    }

    void Texture::setMinLOD(float value) noexcept
    {
        glTextureParameterf(this->_handle, GL_TEXTURE_MIN_LOD, value);
        return;
    }

    void Texture::setMaxLOD(float value) noexcept
    {
        glTextureParameterf(this->_handle, GL_TEXTURE_MAX_LOD, value);
        return;
    }

    void Texture::setLODBias(float value) noexcept
    {
        glTextureParameterf(this->_handle, GL_TEXTURE_LOD_BIAS, value);
        return;
    }

    void Texture::setCompare(Compare value) noexcept
    {
        if (value == Compare::None)
            glTextureParameteri(this->_handle, GL_TEXTURE_COMPARE_MODE, static_cast<GLint>(value));
        else
        {
            glTextureParameteri(this->_handle, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
            glTextureParameteri(this->_handle, GL_TEXTURE_COMPARE_FUNC, static_cast<GLint>(value));
        }
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
        {
            glTextureStorage2D(
                this->_handle,
                this->_mipmaps,
                GL_RGBA8,
                this->_size.x, this->_size.y
            );
            if (this->_mipmaps == 1)
                this->setMagFilter(Filter::NearestMipmapLinear);
        }
        return;
    }

    void Texture::setMipmap(int level, const tbaricault::images::Image& image, const tbaricault::math::Vector2<int>& offset) noexcept
    {
        if (!this->_handle || level < 0 || level >= this->_mipmaps || !image)
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

    void Texture::_destroy() noexcept
    {
        if (this->_handle)
        {
            glDeleteTextures(1, &this->_handle);
            this->_handle = 0;
        }
        return;
    }

}
