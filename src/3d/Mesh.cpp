/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#include <GL/glew.h>

#include "graphics/3d/Mesh.hpp"


namespace tbaricault::graphics::d3
{

    void Mesh::_setup() noexcept
    {
        glEnableVertexArrayAttrib(this->_vao, 0);
        glVertexArrayAttribFormat(
            this->_vao,
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            offsetof(Vertex, position)
        );
        glVertexArrayAttribBinding(this->_vao, 0, 0);
        glEnableVertexArrayAttrib(this->_vao, 1);
        glVertexArrayAttribFormat(
            this->_vao,
            1,
            3,
            GL_FLOAT,
            GL_FALSE,
            offsetof(Vertex, uv)
        );
        glVertexArrayAttribBinding(this->_vao, 1, 0);
        glEnableVertexArrayAttrib(this->_vao, 2);
        glVertexArrayAttribFormat(
            this->_vao,
            2,
            2,
            GL_FLOAT,
            GL_FALSE,
            offsetof(Vertex, normal)
        );
        glVertexArrayAttribBinding(this->_vao, 2, 0);
        return;
    }

}
