/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#include <cmath>

#include "graphics/Transform.hpp"


namespace tbaricault::graphics
{

    const tbaricault::math::Matrix<4, 4, float>& Transform::getMatrix() const noexcept
    {
        return (this->_matrix);
    }

    const tbaricault::math::Vector3<float>& Transform::getPosition() const noexcept
    {
        return (this->_position);
    }

    const tbaricault::math::Vector3<float>& Transform::getScale() const noexcept
    {
        return (this->_scale);
    }

    const tbaricault::math::Quaternion& Transform::getRotation() const noexcept
    {
        return (this->_rotation);
    }

    void Transform::setPosition(const tbaricault::math::Vector3<float>& value) noexcept
    {
        this->_position = value;
        this->_matrix(0, 3) = value.x;
        this->_matrix(1, 3) = value.y;
        this->_matrix(2, 3) = value.z;
        return;
    }

    void Transform::setScale(const tbaricault::math::Vector3<float>& value) noexcept
    {
        this->_scale = value;
        this->_update();
        return;
    }

    void Transform::setRotation(const tbaricault::math::Quaternion& value) noexcept
    {
        this->_rotation = value;
        this->_update();
        return;
    }

    void Transform::_update() noexcept
    {
        const tbaricault::math::Vector3<float> right = this->_rotation.rotate(tbaricault::math::Vector3<float>::right());
        const tbaricault::math::Vector3<float> up = this->_rotation.rotate(tbaricault::math::Vector3<float>::up());
        const tbaricault::math::Vector3<float> forward = this->_rotation.rotate(tbaricault::math::Vector3<float>::forward());
        this->_matrix(0, 0) = right.x * this->_scale.x;
        this->_matrix(0, 1) = up.x * this->_scale.y;
        this->_matrix(0, 2) = forward.x * this->_scale.z;
        this->_matrix(1, 0) = right.y * this->_scale.x;
        this->_matrix(1, 1) = up.y * this->_scale.y;
        this->_matrix(1, 2) = forward.y * this->_scale.z;
        this->_matrix(2, 0) = right.z * this->_scale.x;
        this->_matrix(2, 1) = up.z * this->_scale.y;
        this->_matrix(2, 2) = forward.z * this->_scale.z;
        return;
    }

}
