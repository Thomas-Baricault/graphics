/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#include "Mesh.hpp"


namespace tbaricault::graphics
{

    template<VertexType T>
    Mesh::Mesh(std::span<T> vertices) noexcept
    {
        glCreateVertexArrays(1, &this->_vao);
        if (!this->_vao)
            return;
        glCreateBuffers(1, &this->_vbo);
        if (!this->_vbo)
            return;
        this->_nVertices = vertices.size();
        glNamedBufferData(
            this->_vbo,
            vertices.size() * sizeof(T),
            vertices.data(),
            GL_STATIC_DRAW
        );
        glVertexArrayVertexBuffer(
            this->_vao,
            0,
            this->_vbo,
            0,
            sizeof(T)
        );
        T::_bind(this->_vao);
        return;
    }

}
