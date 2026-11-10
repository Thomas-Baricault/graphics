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
     * @brief View object
     */
    class View
    {

        public:

            /**
             * @brief Default constructor
             */
            View() noexcept = default;

            /**
             * @brief Copy constructor
             * 
             * @param other View to copy
             */
            View(const View& other) noexcept = default;

            /**
             * @brief Move constructor
             * 
             * @param other View to move
             */
            View(View&& other) noexcept = default;

            /**
             * @brief Destructor
             */
            ~View() noexcept = default;

            /**
             * @brief Copy assignment operator
             * 
             * @param other View to copy
             * 
             * @return Reference to this view
             */
            View& operator=(const View& other) noexcept = default;

            /**
             * @brief Move assignment operator
             * 
             * @param other View to move
             * 
             * @return Reference to this view
             */
            View& operator=(View&& other) noexcept = default;

            /**
             * @brief Returns the view matrix
             * 
             * @return View matrix
             */
            const tbaricault::math::Matrix<4, 4, float>& getMatrix() const noexcept;

            /**
             * @brief Returns the position
             * 
             * @return Position
             */
            const tbaricault::math::Vector3<float>& getPosition() const noexcept;

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
             * @brief Rotation
             */
            tbaricault::math::Quaternion _rotation;

            /**
             * @brief View matrix
             */
            tbaricault::math::Matrix<4, 4, float> _matrix = tbaricault::math::Matrix<4, 4, float>::identity();


            /**
             * @brief Update the view matrix
             */
            void _update() noexcept;

    };

}
