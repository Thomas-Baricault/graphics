/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#include <GL/glew.h>

#include "Mesh.hpp"


namespace tbaricault::graphics
{

    template<typename T>
    Mesh<T>::Mesh(Mesh&& other) noexcept
        : _vao(other._vao)
        , _vbo(other._vbo)
        , _nVertices(other._nVertices)
    {
        other._vao = 0;
        other._vbo = 0;
        other._nVertices = 0;
        return;
    }

    template<typename T>
    Mesh<T>::Mesh(std::span<T> vertices) noexcept
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
        this->_setup();
        return;
    }

    template<typename T>
    Mesh<T>::~Mesh() noexcept
    {
        if (this->_vao)
            glDeleteVertexArrays(1, &this->_vao);
        if (this->_vbo)
            glDeleteBuffers(1, &this->_vbo);
        return;
    }

    template<typename T>
    Mesh<T>& Mesh<T>::operator=(Mesh&& other) noexcept
    {
        if (&other == this)
            return (*this);
        if (this->_vao)
            glDeleteVertexArrays(1, &this->_vao);
        if (this->_vbo)
            glDeleteBuffers(1, &this->_vbo);
        this->_vao = other._vao;
        this->_vbo = other._vbo;
        this->_nVertices = other._nVertices;
        other._vao = 0;
        other._vbo = 0;
        other._nVertices = 0;
        return (*this);
    }

    template<typename T>
    Mesh<T>::operator bool() const noexcept
    {
        return (this->_vao && this->_vbo);
    }

    template<typename T>
    void Mesh<T>::draw() const noexcept
    {
        glBindVertexArray(this->_vao);
        glDrawArrays(GL_TRIANGLES, 0, this->_nVertices);
        glBindVertexArray(0);
        return;
    }

}
