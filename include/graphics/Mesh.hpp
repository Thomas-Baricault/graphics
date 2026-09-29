/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include <span>

#include <GL/glew.h>

#include "Vertex.hpp"


namespace tbaricault::graphics
{

    /**
     * @brief Mesh wrapper around OpenGL VAO/VBO
     */
    class Mesh
    {

        public:

            /**
             * @brief Constructs an invalid mesh
             */
            Mesh() noexcept = default;

            /**
             * @brief Copy constructor is disabled
             */
            Mesh(const Mesh&) = delete;

            /**
             * @brief Move constructor
             * 
             * @param other Mesh to move
             */
            Mesh(Mesh&& other) noexcept;

            /**
             * @brief Constructs a mesh from its vertices
             * 
             * @tparam T Vertex type
             * 
             * @param vertices Vertices
             */
            template<VertexType T>
            Mesh(std::span<T> vertices) noexcept;

            /**
             * @brief Destructor
             */
            virtual ~Mesh() noexcept;

            /**
             * @brief Copy assignment operator is disabled
             */
            Mesh& operator=(const Mesh&) = delete;

            /**
             * @brief Move assignment operator
             * 
             * @param other Mesh to move
             * 
             * @return Reference to this mesh
             */
            Mesh& operator=(Mesh&& other) noexcept;

            /**
             * @brief Returns whether the mesh is in a valid state
             */
            explicit operator bool() const noexcept;

            /**
             * @brief Draw the mesh
             */
            void draw() const noexcept;


        protected:

            /**
             * @brief Vertex array object identifier
             */
            GLuint _vao = 0;

            /**
             * @brief Vertex buffer object identifier
             */
            GLuint _vbo = 0;

            /**
             * @brief Number of vertices
             */
            GLsizei _nVertices = 0;

    };

}


#include "Mesh.tpp"
