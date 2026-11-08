/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#include "graphics/Mesh.hpp"


namespace tbaricault::graphics
{

    Mesh::Mesh(Mesh&& other) noexcept
        : _vao(other._vao)
        , _vbo(other._vbo)
        , _nVertices(other._nVertices)
    {
        other._vao = 0;
        other._vbo = 0;
        other._nVertices = 0;
        return;
    }

    Mesh::~Mesh() noexcept
    {
        this->destroy();
        return;
    }

    Mesh& Mesh::operator=(Mesh&& other) noexcept
    {
        if (&other == this)
            return (*this);
        this->destroy();
        this->_vao = other._vao;
        this->_vbo = other._vbo;
        this->_nVertices = other._nVertices;
        other._vao = 0;
        other._vbo = 0;
        other._nVertices = 0;
        return (*this);
    }

    Mesh::operator bool() const noexcept
    {
        return (this->_vao && this->_vbo);
    }

    void Mesh::destroy() noexcept
    {
        if (this->_vao)
        {
            glDeleteVertexArrays(1, &this->_vao);
            this->_vao = 0;
        }
        if (this->_vbo)
        {
            glDeleteBuffers(1, &this->_vbo);
            this->_vbo = 0;
        }
        return;
    }

    void Mesh::draw() const noexcept
    {
        glBindVertexArray(this->_vao);
        glDrawArrays(GL_TRIANGLES, 0, this->_nVertices);
        glBindVertexArray(0);
        return;
    }

}
