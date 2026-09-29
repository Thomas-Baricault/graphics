/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#include <cmath>

#include "graphics/Projection.hpp"


namespace tbaricault::graphics
{

    Projection::Projection() noexcept
    {
        this->_update();
        return;
    }

    bool Projection::isInvertedX() const noexcept
    {
        return (this->_invertX);
    }

    bool Projection::isInvertedY() const noexcept
    {
        return (this->_invertY);
    }

    const tbaricault::math::Matrix<4, 4, float>& Projection::getMatrix() const noexcept
    {
        return (this->_matrix);
    }

    Projection::Type Projection::getType() const noexcept
    {
        return (this->_type);
    }

    const tbaricault::math::Rect<float>& Projection::getRect() const noexcept
    {
        return (this->_rect);
    }

    const tbaricault::math::Vector2<float>& Projection::getDistances() const noexcept
    {
        return (this->_distances);
    }

    float Projection::getFOV() const noexcept
    {
        return (this->_fov);
    }

    float Projection::getAspectRatio() const noexcept
    {
        return (this->_aspectRatio);
    }

    void Projection::setType(Type value) noexcept
    {
        this->_type = value;
        this->_update();
    }

    void Projection::setInvertX(bool value) noexcept
    {
        this->_invertX = value;
        this->_update();
    }

    void Projection::setInvertY(bool value) noexcept
    {
        this->_invertY = value;
        this->_update();
    }

    void Projection::setRect(const tbaricault::math::Rect<float>& value) noexcept
    {
        this->_rect = value;
        this->_update();
    }

    void Projection::setDistances(const tbaricault::math::Vector2<float>& value) noexcept
    {
        this->_distances = value;
        this->_update();
    }

    void Projection::setFOV(float value) noexcept
    {
        this->_fov = value;
        this->_update();
    }

    void Projection::setAspectRatio(float value) noexcept
    {
        this->_aspectRatio = value;
        this->_update();
    }

    void Projection::_update() noexcept
    {
        const float near = _distances.x;
        const float far = _distances.y;
        switch (this->_type)
        {
            case Type::Orthographic:
            {
                const float left = this->_rect.x;
                const float right = this->_rect.x + this->_rect.w;
                const float bottom = this->_rect.y;
                const float top = this->_rect.y + this->_rect.h;
                const float signX = this->_invertX ? -1.0f : 1.0f;
                const float signY = this->_invertY ? -1.0f : 1.0f;
                this->_matrix(0, 0) = signX * 2.0f / (right - left);
                this->_matrix(0, 3) = -signX * (left + right) / (right - left);
                this->_matrix(1, 1) = -signY * 2.0f / (top - bottom);
                this->_matrix(1, 3) = signY * (bottom + top) / (top - bottom);
                this->_matrix(2, 2) = -2.0f / (far - near);
                this->_matrix(2, 3) = -(near + far) / (far - near);
                this->_matrix(3, 2) = 0.0f;
                this->_matrix(3, 3) = 1.0f;
                break;
            }
            case Type::Perspective:
            {
                const float f = 1.0f / std::tan(this->_fov * 0.5f);
                this->_matrix(0, 0) = f / (this->_aspectRatio);
                this->_matrix(0, 3) = 0.0f;
                this->_matrix(1, 1) = f;
                this->_matrix(1, 3) = 0.0f;
                this->_matrix(2, 2) = -(near + far) / (far - near);
                this->_matrix(2, 3) = -(near * far * 2.0f) / (far - near);
                this->_matrix(3, 2) = -1.0f;
                this->_matrix(3, 3) = 0.0f;
                break;
            }
        }
        return;
    }

}
