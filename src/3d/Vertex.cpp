/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#include "graphics/3d/Vertex.hpp"


namespace tbaricault::graphics::d3
{

    Vertex::Vertex(const tbaricault::math::Vector2<float>& position, const tbaricault::math::Vector2<float>& normal, const tbaricault::math::Vector2<float>& uv) noexcept
        : position(position)
        , normal(normal)
        , uv(uv)
    {
        return;
    }


    std::size_t Vertex::_offsets[] = {
        offsetof(Vertex, position),
        offsetof(Vertex, normal),
        offsetof(Vertex, uv)
    };

}
