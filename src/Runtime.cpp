/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#include <ft2build.h>
#include FT_FREETYPE_H

#include <GL/glew.h>

#include "graphics/Runtime.hpp"
#include "graphics/Font.hpp"


namespace tbaricault::graphics
{

    Runtime::Runtime()
    {
        glewInit();
        if (FT_Init_FreeType(&Font::_ftLibrary))
            return;
        this->_valid = true;
        return;
    }

    Runtime::~Runtime() noexcept
    {
        if (!this->_valid)
            return;
        FT_Done_FreeType(Font::_ftLibrary);
        return;
    }

    Runtime::operator bool() const noexcept
    {
        return (this->_valid);
    }

}
