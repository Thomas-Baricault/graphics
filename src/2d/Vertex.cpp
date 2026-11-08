/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#include "graphics/2d/Vertex.hpp"


namespace tbaricault::graphics::d2
{

    Vertex::Vertex(const tbaricault::math::Vector2<float>& position, const tbaricault::math::Vector2<float>& uv) noexcept
        : position(position)
        , uv(uv)
    {
        return;
    }


    std::size_t Vertex::_offsets[] = {
        offsetof(Vertex, position),
        offsetof(Vertex, uv)
    };

}
