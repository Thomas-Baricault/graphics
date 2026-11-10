/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include <tbaricault/math.hpp>

#include "../Vertex.hpp"


namespace tbaricault::graphics::d3
{

    /**
     * @brief Three dimentional vertex
     */
    class Vertex
        : public tbaricault::graphics::Vertex<Vertex, tbaricault::math::Vector3<float>, tbaricault::math::Vector3<float>, tbaricault::math::Vector2<float>>
    {

        public:

            /**
             * @brief Position
             */
            tbaricault::math::Vector2<float> position;

            /**
             * @brief Normal
             */
            tbaricault::math::Vector2<float> normal;

            /**
             * @brief Texture coordinates
             */
            tbaricault::math::Vector2<float> uv;


            /**
             * @brief Default constructor is disabled
             */
            Vertex() = delete;

            /**
             * @brief Copy constructor
             * 
             * @param other Vertex to copy
             */
            Vertex(const Vertex& other) noexcept = default;

            /**
             * @brief Move constructor
             * 
             * @param other Vertex to move
             */
            Vertex(Vertex&& other) noexcept = default;

            /**
             * @brief Constructs a vertex
             * 
             * @param position Vertex position
             * @param normal Vertex normal
             * @param uv Texture position
             */
            Vertex(const tbaricault::math::Vector2<float>& position, const tbaricault::math::Vector2<float>& normal, const tbaricault::math::Vector2<float>& uv) noexcept;

            /**
             * @brief Destructor
             */
            ~Vertex() noexcept = default;

            /**
             * @brief Copy assignment operator
             * 
             * @param other Vertex to copy
             * 
             * @return Reference to this vertex
             */
            Vertex& operator=(const Vertex& other) noexcept = default;

            /**
             * @brief Move assignment operator
             * 
             * @param other Vertex to move
             * 
             * @return Reference to this vertex
             */
            Vertex& operator=(Vertex&& other) noexcept = default;


        private:

            /**
             * @brief Components offsets
             */
            static std::size_t _offsets[];


        friend class tbaricault::graphics::Vertex<Vertex, tbaricault::math::Vector3<float>, tbaricault::math::Vector3<float>, tbaricault::math::Vector2<float>>;

    };

}
