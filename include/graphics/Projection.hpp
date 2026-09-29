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
     * @brief Projection object
     */
    class Projection
    {

        public:

            /**
             * @brief Projection type
             */
            enum class Type
            {

                /**
                 * @brief Orthographic projection
                 */
                Orthographic,

                /**
                 * @brief Perspective projection
                 */
                Perspective,

            };


            /**
             * @brief Default constructor
             */
            Projection() noexcept;

            /**
             * @brief Copy constructor
             * 
             * @param other Projection to copy
             */
            Projection(const Projection& other) noexcept = default;

            /**
             * @brief Move constructor
             * 
             * @param other Projection to move
             */
            Projection(Projection&& other) noexcept = default;

            /**
             * @brief Destructor
             */
            ~Projection() noexcept = default;

            /**
             * @brief Copy assignment operator
             * 
             * @param other Projection to copy
             * 
             * @return Reference to this projection
             */
            Projection& operator=(const Projection& other) noexcept = default;

            /**
             * @brief Move assignment operator
             * 
             * @param other Projection to move
             * 
             * @return Reference to this projection
             */
            Projection& operator=(Projection&& other) noexcept = default;

            /**
             * @brief Returns whether the projection is horizontally inverted
             * 
             * @return `true` if inverted, `false` otherwise
             */
            bool isInvertedX() const noexcept;

            /**
             * @brief Returns whether the projection is vertically inverted
             * 
             * @return `true` if inverted, `false` otherwise
             */
            bool isInvertedY() const noexcept;

            /**
             * @brief Returns the projection matrix
             * 
             * @return Projection matrix
             */
            const tbaricault::math::Matrix<4, 4, float>& getMatrix() const noexcept;

            /**
             * @brief Returns the projection type
             * 
             * @return Projection type
             */
            Type getType() const noexcept;

            /**
             * @brief Returns the rectangle
             * 
             * @return Rectangle
             */
            const tbaricault::math::Rect<float>& getRect() const noexcept;

            /**
             * @brief Returns the distances
             * 
             * @return Distances
             */
            const tbaricault::math::Vector2<float>& getDistances() const noexcept;

            /**
             * @brief Returns the field of view
             * 
             * @return Field of view
             */
            float getFOV() const noexcept;

            /**
             * @brief Returns the aspect ratio
             * 
             * @return Aspect ratio
             */
            float getAspectRatio() const noexcept;

            /**
             * @brief Sets the projection type
             * 
             * @param value New projection type
             */
            void setType(Type value) noexcept;

            /**
             * @brief Sets whether the projection is horizontally inverted
             * 
             * @param value `true` if inverted, `false` otherwise
             */
            void setInvertX(bool value) noexcept;

            /**
             * @brief Sets whether the projection is vertically inverted
             * 
             * @param value `true` if inverted, `false` otherwise
             */
            void setInvertY(bool value) noexcept;

            /**
             * @brief Sets the rectangle
             * 
             * @param value New rectangle
             */
            void setRect(const tbaricault::math::Rect<float>& value) noexcept;

            /**
             * @brief Sets the distances
             * 
             * @param value New distances
             */
            void setDistances(const tbaricault::math::Vector2<float>& value) noexcept;

            /**
             * @brief Sets the field of view
             * 
             * @param value New field of view
             */
            void setFOV(float value) noexcept;

            /**
             * @brief Sets the aspect ratio
             * 
             * @param value New aspect ratio
             */
            void setAspectRatio(float value) noexcept;


        private:

            /**
             * @brief Projection type
             */
            Type _type = Type::Orthographic;

            /**
             * @brief Whether the projection is horizontally inverted
             */
            bool _invertX = false;

            /**
             * @brief Whether the projection is vertically inverted
             */
            bool _invertY = false;

            /**
             * @brief Projection rectangle
             */
            tbaricault::math::Rect<float> _rect;

            /**
             * @brief Projection distances
             */
            tbaricault::math::Vector2<float> _distances;

            /**
             * @brief Field of view
             */
            float _fov = 1.0471975512f;

            /**
             * @brief Aspect ratio
             */
            float _aspectRatio = 1;

            /**
             * @brief Projection matrix
             */
            tbaricault::math::Matrix<4, 4, float> _matrix;


            /**
             * @brief Update the projection matrix
             */
            void _update() noexcept;

    };

}
