/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include <GL/glew.h>


namespace tbaricault::graphics
{

    /**
     * @brief Abstract base class for OpenGL wrappers
     */
    class Wrapper
    {

        public:

            /**
             * @brief Constructs an invalid object
             */
            Wrapper() noexcept = default;

            /**
             * @brief Copy constructor is disabled
             */
            Wrapper(const Wrapper&) = delete;

            /**
             * @brief Move constructor
             * 
             * @param other Object to move
             */
            Wrapper(Wrapper&& other) noexcept;

            /**
             * @brief Destructor
             */
            virtual ~Wrapper() noexcept = default;

            /**
             * @brief Copy assignment operator is disabled
             */
            Wrapper& operator=(const Wrapper&) = delete;

            /**
             * @brief Move assignment operator
             * 
             * @param other Object to move
             * 
             * @return Reference to this object
             */
            Wrapper& operator=(Wrapper&& other) noexcept;

            /**
             * @brief Returns whether the object is in a valid state
             */
            explicit operator bool() const noexcept;

            /**
             * @brief Returns the OpenGL object identifier
             * 
             * @return Object identifier
             */
            GLuint getHandle() const noexcept;


        protected:

            /**
             * @brief Handled object identifier
             */
            GLuint _handle = 0;


            /**
             * @brief Destroys the handled object
             */
            virtual void _destroy() noexcept = 0;

    };

}
