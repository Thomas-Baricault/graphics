/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include <tbaricault/math.hpp>

#include "../Mesh.hpp"


namespace tbaricault::graphics::d3
{

    /**
     * @brief 3D vertex structure
     */
    struct Vertex
    {

        /**
         * @brief Vertex position
         */
        tbaricault::math::Vector3<float> position;

        /**
         * @brief Vertex normal
         */
        tbaricault::math::Vector3<float> normal;

        /**
         * @brief Vertex texture coordinates
         */
        tbaricault::math::Vector2<float> uv;

    };


    /**
     * @brief 3D mesh
     */
    class Mesh final
        : public tbaricault::graphics::Mesh<Vertex>
    {

        public:

            using tbaricault::graphics::Mesh<Vertex>::Mesh;


            /**
             * @brief Constructs an invalid mesh
             */
            Mesh() noexcept = default;

            /**
             * @brief Copy constructor is disabled
             */
            Mesh(const Mesh&) = delete;

            /**
             * @brief Move constructor
             * 
             * @param other Mesh to move
             */
            Mesh(Mesh&& other) noexcept = default;

            /**
             * @brief Destructor
             */
            virtual ~Mesh() noexcept = default;

            /**
             * @brief Copy assignment operator is disabled
             */
            Mesh& operator=(const Mesh&) = delete;

            /**
             * @brief Move assignment operator
             * 
             * @param other Mesh to move
             * 
             * @return Reference to this mesh
             */
            Mesh& operator=(Mesh&& other) noexcept = default;


        protected:

            /**
             * @brief Setups vertex attributes
             */
            virtual void _setup() noexcept override;

    };

}
