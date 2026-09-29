/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include <concepts>

#include <GL/glew.h>

#include <tbaricault/math.hpp>


namespace tbaricault::graphics
{

    /**
     * @brief Unspecialized vertex attribute traits
     * 
     * @tparam T Attribute type
     */
    template<typename T>
    struct VertexAttributeTraits;

    /**
     * @brief Vertex attribute traits specilization for two-dimensional floating point vector
     */
    template<>
    struct VertexAttributeTraits<tbaricault::math::Vector2<float>>
    {

        static constexpr GLint size = 2;
        static constexpr GLenum type = GL_FLOAT;
        static constexpr GLboolean normalized = GL_FALSE;

    };

    /**
     * @brief Vertex attribute traits specilization for three-dimensional floating point vector
     */
    template<>
    struct VertexAttributeTraits<tbaricault::math::Vector3<float>>
    {

        static constexpr GLint size = 3;
        static constexpr GLenum type = GL_FLOAT;
        static constexpr GLboolean normalized = GL_FALSE;

    };


    /**
     * @brief Concept for vertex attribute type
     * 
     * @tparam T Type to check
     */
    template<typename T>
    concept VertexAttribute = requires {
        { VertexAttributeTraits<T>::size } -> std::convertible_to<GLint>;
        { VertexAttributeTraits<T>::type } -> std::convertible_to<GLenum>;
        { VertexAttributeTraits<T>::normalized } -> std::convertible_to<GLboolean>;
    };

    /**
     * @brief Concept for vertex type
     * 
     * @tparam T Type to check
     */
    template<typename T>
    concept VertexType = requires {
        T::_offsets;
        requires std::is_array_v<decltype(T::_offsets)>;
        requires std::same_as<
            std::remove_extent_t<decltype(T::_offsets)>,
            std::size_t
        >;
    };


    class Mesh;


    /**
     * @brief Base class for vertices
     * 
     * @tparam This Concrete derived type
     * @tparam Attributes Vertex attributes
     */
    template<typename This, VertexAttribute... Attributes>
    class Vertex
    {

        private:

            /**
             * @brief Binds vertex attributes to a VAO
             * 
             * @param vao VAO to bind to
             */
            static void _bind(GLuint vao);

            /**
             * @brief Binds vertex attribute to a VAO
             * 
             * @tparam T Attribute type
             * @tparam Rest Remaining attributes to bind
             * 
             * @param vao VAO to bind to
             * @param index Attribute index
             */
            template<VertexAttribute T, VertexAttribute... Rest>
            static void _bind(GLuint vao, GLuint& index);


        friend class Mesh;

    };

}


#include "Vertex.tpp"
