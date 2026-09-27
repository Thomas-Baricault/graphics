/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include <span>

#include "Shader.hpp"
#include "Wrapper.hpp"


namespace tbaricault::graphics
{

    class Program final
        : public Wrapper
    {

        public:

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
                     * @brief Constructs the guard and bind the program
                     * 
                     * @param program Program to bind
                     */
                    BindGuard(const Program& program) noexcept;

                    /**
                     * @brief Destructor
                     * 
                     * @note Automatically restore the previous program used
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
                     * @brief Previous program used
                     */
                    GLint _previous;

            };


            /**
             * @brief Unbind any binded program
             */
            static void unbind() noexcept;

            /**
             * @brief Constructs an invalid program
             */
            Program() noexcept = default;

            /**
             * @brief Copy constructor is disabled
             */
            Program(const Program&) = delete;

            /**
             * @brief Move constructor
             * 
             * @param other Program to move
             */
            Program(Program&& other) noexcept = default;

            /**
             * @brief Constructs a program giving shaders
             * 
             * @param shaders Shaders to attach to the program
             * 
             * @throws std::runtime_error If program link failed
             */
            Program(std::span<Shader> shaders);

            /**
             * @brief Destructor
             */
            virtual ~Program() noexcept;

            /**
             * @brief Copy assignment operator is disabled
             */
            Program& operator=(const Program&) = delete;

            /**
             * @brief Move assignment operator
             * 
             * @param other Program to move
             * 
             * @return Reference to this Program
             */
            Program& operator=(Program&& other) noexcept = default;

            /**
             * @brief Bind the program
             */
            void bind() const noexcept;

            /**
             * @brief Scoped bind for the program
             * 
             * @return Bind guard for this program usage
             */
            BindGuard use() const noexcept;


        private:

            /**
             * @brief Destroys the program
             */
            void _destroy() noexcept override;

    };

}
