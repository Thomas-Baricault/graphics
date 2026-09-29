/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#include "graphics/View.hpp"


namespace tbaricault::graphics
{

    const tbaricault::math::Matrix<4, 4, float>& View::getMatrix() const noexcept
    {
        return (this->_matrix);
    }

    const tbaricault::math::Vector3<float>& View::getPosition() const noexcept
    {
        return (this->_position);
    }

    const tbaricault::math::Quaternion& View::getRotation() const noexcept
    {
        return (this->_rotation);
    }

    void View::setPosition(const tbaricault::math::Vector3<float>& value) noexcept
    {
        this->_position = value;
        this->_update();
        return;
    }

    void View::setRotation(const tbaricault::math::Quaternion& value) noexcept
    {
        this->_rotation = value;
        this->_update();
        return;
    }

    void View::_update() noexcept
    {
        const tbaricault::math::Quaternion inverse = this->_rotation.inverse();
        const tbaricault::math::Vector3<float> right = inverse.rotate(tbaricault::math::Vector3<float>::right());
        const tbaricault::math::Vector3<float> up = inverse.rotate(tbaricault::math::Vector3<float>::up());
        const tbaricault::math::Vector3<float> forward = inverse.rotate(tbaricault::math::Vector3<float>::forward());
        const tbaricault::math::Vector3<float> translation = inverse.rotate(-this->_position);
        this->_matrix(0, 0) = right.x;
        this->_matrix(0, 1) = right.y;
        this->_matrix(0, 2) = right.z;
        this->_matrix(1, 0) = up.x;
        this->_matrix(1, 1) = up.y;
        this->_matrix(1, 2) = up.z;
        this->_matrix(2, 0) = forward.x;
        this->_matrix(2, 1) = forward.y;
        this->_matrix(2, 2) = forward.z;
        this->_matrix(0, 3) = translation.x;
        this->_matrix(1, 3) = translation.y;
        this->_matrix(2, 3) = translation.z;
        return;
    }

}
