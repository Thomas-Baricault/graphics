/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#include <GL/glew.h>

#include "graphics/2d/Mesh.hpp"


namespace tbaricault::graphics::d2
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
            0
        );
        glVertexArrayAttribBinding(this->_vao, 0, 0);
        return;
    }

}
