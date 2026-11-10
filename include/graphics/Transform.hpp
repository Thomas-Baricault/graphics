/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include <tbaricault/math.hpp>


namespace tbaricault::graphics
{

    /**
     * @brief Transformation object
     */
    class Transform
    {

        public:

            /**
             * @brief Default constructor
             */
            Transform() noexcept = default;

            /**
             * @brief Copy constructor
             * 
             * @param other Transform to copy
             */
            Transform(const Transform& other) noexcept = default;

            /**
             * @brief Move constructor
             * 
             * @param other Transform to move
             */
            Transform(Transform&& other) noexcept = default;

            /**
             * @brief Destructor
             */
            ~Transform() noexcept = default;

            /**
             * @brief Copy assignment operator
             * 
             * @param other Transform to copy
             * 
             * @return Reference to this transform
             */
            Transform& operator=(const Transform& other) noexcept = default;

            /**
             * @brief Move assignment operator
             * 
             * @param other Transform to move
             * 
             * @return Reference to this transform
             */
            Transform& operator=(Transform&& other) noexcept = default;

            /**
             * @brief Returns the transformation matrix
             * 
             * @return Transformation matrix
             */
            const tbaricault::math::Matrix<4, 4, float>& getMatrix() const noexcept;

            /**
             * @brief Returns the position
             * 
             * @return Position
             */
            const tbaricault::math::Vector3<float>& getPosition() const noexcept;

            /**
             * @brief Returns the scale
             * 
             * @return Scale
             */
            const tbaricault::math::Vector3<float>& getScale() const noexcept;

            /**
             * @brief Returns the rotation
             * 
             * @return Rotation
             */
            const tbaricault::math::Quaternion& getRotation() const noexcept;

            /**
             * @brief Sets the position
             * 
             * @param value New position
             */
            void setPosition(const tbaricault::math::Vector3<float>& value) noexcept;

            /**
             * @brief Sets the scale
             * 
             * @param value New scale
             */
            void setScale(const tbaricault::math::Vector3<float>& value) noexcept;

            /**
             * @brief Sets the rotation
             * 
             * @param value New rotation
             */
            void setRotation(const tbaricault::math::Quaternion& value) noexcept;


        private:

            /**
             * @brief Position
             */
            tbaricault::math::Vector3<float> _position;

            /**
             * @brief Scale
             */
            tbaricault::math::Vector3<float> _scale = tbaricault::math::Vector3<float>::one();

            /**
             * @brief Rotation
             */
            tbaricault::math::Quaternion _rotation;

            /**
             * @brief Transformation matrix
             */
            tbaricault::math::Matrix<4, 4, float> _matrix = tbaricault::math::Matrix<4, 4, float>::identity();


            /**
             * @brief Update the transformation matrix
             */
            void _update() noexcept;

    };

}
