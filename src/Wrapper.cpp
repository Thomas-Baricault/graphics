/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#include "graphics/Wrapper.hpp"


namespace tbaricault::graphics
{

    Wrapper::Wrapper(Wrapper&& other) noexcept
        : _handle(other._handle)
    {
        other._handle = 0;
        return;
    }

    Wrapper& Wrapper::operator=(Wrapper&& other) noexcept
    {
        if (&other == this)
            return (*this);
        this->_destroy();
        this->_handle = other._handle;
        other._handle = 0;
        return (*this);
    }

    Wrapper::operator bool() const noexcept
    {
        return (this->_handle != 0);
    }

    GLuint Wrapper::getHandle() const noexcept
    {
        return (this->_handle);
    }

}
