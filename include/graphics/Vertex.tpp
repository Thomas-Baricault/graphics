/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include "Vertex.hpp"


namespace tbaricault::graphics
{

    template<typename This, VertexAttribute... Attributes>
    void Vertex<This, Attributes...>::_bind(GLuint vao)
    {
        GLuint index = 0;
        Vertex::_bind<Attributes...>(vao, index);
        return;
    }

    template<typename This, VertexAttribute... Attributes>
    template<VertexAttribute T, VertexAttribute... Rest>
    void Vertex<This, Attributes...>::_bind(GLuint vao, GLuint& index)
    {
        glEnableVertexArrayAttrib(vao, index);
        glVertexArrayAttribFormat(
            vao,
            index,
            VertexAttributeTraits<T>::size,
            VertexAttributeTraits<T>::type,
            VertexAttributeTraits<T>::normalized,
            This::_offsets[index]
        );
        glVertexArrayAttribBinding(vao, index, 0);
        index++;
        if constexpr (sizeof...(Rest) > 0)
            Vertex::_bind<Rest...>(vao, index);
        return;
    }

}
