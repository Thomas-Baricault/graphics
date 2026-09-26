/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include <GL/glew.h>

#include <tbaricault/math.hpp>


namespace tbaricault::graphics
{

    /**
     * @brief Wrapper around OpenGL framebuffer
     */
    class Framebuffer final
    {

        public:

            /**
             * @brief Constructs an empty framebuffer
             */
            Framebuffer() noexcept = default;

            /**
             * @brief Copy constructor is disabled
             */
            Framebuffer(const Framebuffer&) = delete;

            /**
             * @brief Move constructor
             * 
             * @param other Framebuffer to move
             */
            Framebuffer(Framebuffer&& other) noexcept;

            /**
             * @brief Destructor
             */
            ~Framebuffer();

            /**
             * @brief Copy assignment operator is disabled
             */
            Framebuffer& operator=(const Framebuffer&) = delete;

            /**
             * @brief Move assignment operator
             * 
             * @param other Framebuffer to move
             * 
             * @return Reference to this framebuffer
             */
            Framebuffer& operator=(Framebuffer&& other) noexcept;

            /**
             * @brief Returns whether the framebuffer is in a valid state
             */
            explicit operator bool() const noexcept;

            /**
             * @brief Returns the size of the framebuffer
             * 
             * @return Framebuffer size in pixels
             */
            const tbaricault::math::Vector2<int>& getSize() const noexcept;

            /**
             * @brief Resizes the framebuffer
             * 
             * @param value New size in pixels
             */
            void setSize(const tbaricault::math::Vector2<int>& value) noexcept;


        private:

            /**
             * @brief Framebuffer identifier
             */
            GLuint _handle = 0;

            /**
             * @brief Texture identifier
             */
            GLuint _texture = 0;

            /**
             * @brief Framebuffer dimensions
             */
            tbaricault::math::Vector2<int> _size;

    };

}
