/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include <GL/glew.h>

#include <tbaricault/math.hpp>

#include "Texture.hpp"


namespace tbaricault::graphics
{

    /**
     * @brief Wrapper around OpenGL framebuffer
     */
    class Framebuffer final
    {

        public:

            /**
             * @brief Framebuffer operation mode
             */
            enum class Mode
            {

                /**
                 * @brief Drawing operations
                 */
                Draw = GL_DRAW_FRAMEBUFFER,

                /**
                 * @brief Reading operations
                 */
                Read = GL_READ_FRAMEBUFFER,

            };


            /**
             * @brief Manages a framebuffer binding lifetime
             */
            class BindGuard
            {

                public:

                    /**
                     * @brief Default constructor is disabled
                     */
                    BindGuard() = delete;

                    /**
                     * @brief Copy constructor is disabled
                     */
                    BindGuard(const BindGuard&) = delete;

                    /**
                     * @brief Move constructor is disabled
                     */
                    BindGuard(BindGuard&&) = delete;

                    /**
                     * @brief Constructs the guard and bind the framebuffer
                     * 
                     * @param framebuffer Framebuffer to bind
                     */
                    BindGuard(const Framebuffer& framebuffer, Mode mode = Mode::Draw) noexcept;

                    /**
                     * @brief Destructor
                     * 
                     * @note Automatically restore the previous framebuffer used
                     */
                    ~BindGuard() noexcept;

                    /**
                     * @brief Copy assignment operator is disabled
                     */
                    BindGuard& operator=(const BindGuard&) = delete;

                    /**
                     * @brief Move assignment operator is disabled
                     */
                    BindGuard& operator=(BindGuard&&) = delete;


                private:

                    /**
                     * @brief Framebuffer binding mode
                     */
                    Mode _mode;

                    /**
                     * @brief Previous framebuffer used
                     */
                    GLint _previous;

            };


            /**
             * @brief Unbind any binded framebuffer
             * 
             * @param mode Binding mode
             */
            static void unbind(Mode mode = Mode::Draw) noexcept;

            /**
             * @brief Constructs an empty framebuffer
             */
            Framebuffer() noexcept;

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
            ~Framebuffer() noexcept;

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
             * @brief Returns the OpenGL framebuffer identifier
             * 
             * @return Framebuffer identifier
             */
            GLuint getHandle() const noexcept;

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

            /**
             * @brief Bind the framebuffer
             * 
             * @param mode Binding mode
             */
            void bind(Mode mode = Mode::Draw) const noexcept;

            /**
             * @brief Scoped bind for the framebuffer
             * 
             * @param mode Binding mode
             * 
             * @return Bind guard for this framebuffer usage
             */
            BindGuard use(Mode mode = Mode::Draw) const noexcept;


        private:

            /**
             * @brief Framebuffer identifier
             */
            GLuint _handle = 0;

            /**
             * @brief Framebuffer texture
             */
            Texture _texture;

    };

}
