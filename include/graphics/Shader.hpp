/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include <string_view>

#include <GL/glew.h>

#include "Wrapper.hpp"


namespace tbaricault::graphics
{

    /**
     * @brief Wrapper around OpenGL shader
     */
    class Shader final
        : public Wrapper
    {

        public:

            /**
             * @brief Shader type
             */
            enum class Type
            {

                /**
                 * @brief Fragment shader
                 */
                Fragment = GL_FRAGMENT_SHADER,

                /**
                 * @brief Vertex shader
                 */
                Vertex = GL_VERTEX_SHADER,

            };


            /**
             * @brief Constructs an invalid shader
             */
            Shader() noexcept = default;

            /**
             * @brief Copy constructor is disabled
             */
            Shader(const Shader&) = delete;

            /**
             * @brief Move constructor
             * 
             * @param other Shader to move
             */
            Shader(Shader&& other) noexcept = default;

            /**
             * @brief Constructs and compiles a shader
             * 
             * @param type Shader type
             * @param src Shader sources
             * 
             * @throws std::runtime_error If shader compilation failed
             */
            Shader(Type type, std::string_view src);

            /**
             * @brief Destructor
             */
            virtual ~Shader() noexcept;

            /**
             * @brief Copy assignment operator is disabled
             */
            Shader& operator=(const Shader&) = delete;

            /**
             * @brief Move assignment operator
             * 
             * @param other Shader to move
             * 
             * @return Reference to this shader
             */
            Shader& operator=(Shader&& other) noexcept = default;


        private:

            /**
             * @brief Destroys the shader
             */
            void _destroy() noexcept override;

    };

}
