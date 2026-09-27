/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include <string>

#include <GL/glew.h>

#include "Wrapper.hpp"


namespace tbaricault::graphics
{

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
            Shader(Type type, const std::string& src);

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






























// /*
//  * Copyright (c) 2026-present Thomas Baricault
//  *
//  * SPDX-License-Identifier: MIT
//  */


// #pragma once


// #include <string>

// #include <GL/glew.h>

// #include <tbaricault/math.hpp>


// namespace tbaricault::graphics
// {

//     /**
//      * @brief Wrapper around OpenGL shader program
//      */
//     class Shader final
//     {

//         public:

//             /**
//              * @brief Constructs an invalid shader
//              */
//             Shader() noexcept = default;

//             /**
//              * @brief Copy constructor is disabled
//              */
//             Shader(const Shader&) = delete;

//             /**
//              * @brief Move constructor
//              * 
//              * @param other Shader to move
//              */
//             Shader(Shader&& other) noexcept;

//             /**
//              * @brief Constructs a shader program from vertex and fragment shaders
//              * 
//              * @param vertex Vertex shader
//              * @param fragment Fragment shader
//              * 
//              * @throws std::runtime_error If shader creation failed
//              */
//             Shader(const std::string& vertex, const std::string& fragment);

//             /**
//              * @brief Destructor
//              */
//             ~Shader() noexcept;

//             /**
//              * @brief Copy assignment operator is disabled
//              */
//             Shader& operator=(const Shader&) = delete;

//             /**
//              * @brief Move assignment operator
//              * 
//              * @param other Shader to move
//              * 
//              * @return Reference to this shader
//              */
//             Shader& operator=(Shader&& other) noexcept;

//             /**
//              * @brief Returns whether the shader is in a valid state
//              */
//             explicit operator bool() const noexcept;


//         private:

//             /**
//              * @brief Shader identifier
//              */
//             GLuint _handle = 0;


//             /**
//              * @brief Compiles a shader from sources
//              * 
//              * @param type Shader type
//              * @param src Shader sources
//              * 
//              * @return Shader identifier
//              * 
//              * @throws std::runtime_error If shader creation or compilation failed
//              */
//             static GLuint _compile(GLenum type, const std::string& src);

//     };

// }
