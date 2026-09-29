/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include "Projection.hpp"
#include "View.hpp"


namespace tbaricault::graphics
{

    /**
     * @brief Camera
     */
    struct Camera
    {

        /**
         * @brief Projection
         */
        Projection projection;

        /**
         * @brief View
         */
        View view;

    };

}
