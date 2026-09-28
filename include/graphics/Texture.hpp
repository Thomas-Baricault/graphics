/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include <GL/glew.h>

#include <tbaricault/colors.hpp>
#include <tbaricault/images.hpp>
#include <tbaricault/math.hpp>

#include "Wrapper.hpp"


namespace tbaricault::graphics
{

    /**
     * @brief Wrapper around OpenGL 2D texture
     */
    class Texture final
        : public Wrapper
    {

        public:

            /**
             * @brief Level-of-detail functions
             */
            enum class Filter
            {

                /**
                 * @brief Returns the weighted average of the four texture elements that are closest to the specified texture coordinates
                 */
                Linear = GL_LINEAR,

                /**
                 * @brief Chooses the two mipmap that most closely matches the size of the pixel being textured and uses the `Linear` criterion
                 */
                LinearMipmapLinear = GL_LINEAR_MIPMAP_LINEAR,

                /**
                 * @brief Chooses the mipmap that most closely matches the size of the pixel being textured and uses the `Linear` criterion
                 */
                LinearMipmapNearest = GL_LINEAR_MIPMAP_NEAREST,

                /**
                 * @brief Returns the value of the texture element that is nearest (in Manhattan distance) to the specified texture coordinates
                 */
                Nearest = GL_NEAREST,

                /**
                 * @brief Chooses the two mipmaps that most closely match the size of the pixel being textured and uses the `Nearest` criterion
                 */
                NearestMipmapLinear = GL_NEAREST_MIPMAP_LINEAR,

                /**
                 * @brief Chooses the mipmap that most closely matches the size of the pixel being textured and uses the `Nearest` criterion
                 */
                NearestMipmapNearest = GL_NEAREST_MIPMAP_NEAREST,

            };

            /**
             * @brief Wrap functions
             */
            enum class Wrap
            {

                /**
                 * @brief Use a specific border color for out-of-bounds coordinates
                 */
                ClampToBorder = GL_CLAMP_TO_BORDER,

                /**
                 * @brief Stretches the edges of the texture to avoid artifacts at the ends
                 */
                ClampToEdge = GL_CLAMP_TO_EDGE,

                /**
                 * @brief Combines a mirror effect with edge clamping
                 */
                MirrorClampToEdge = GL_MIRROR_CLAMP_TO_EDGE,

                /**
                 * @brief Repeat the texture by mirroring every other pattern
                 */
                MirroredRepeat = GL_MIRRORED_REPEAT,

                /**
                 * @brief Repeats the texture, ignoring the integer part of the coordinates
                 */
                Repeat = GL_REPEAT,

            };

            /**
             * @brief Texture comparison mode for currently bound depth textures
             */
            enum class CompareMode
            {

                /**
                 * @brief Specifies that the interpolated and clamped r texture coordinate should be compared to the value in the currently bound depth texture
                 */
                RefToTexture = GL_COMPARE_REF_TO_TEXTURE,

            };

            /**
             * @brief Comparison operator
             */
            enum class Compare
            {

                /**
                 * @brief Specifies that the red channel should be assigned the appropriate value from the currently bound depth texture
                 */
                None = GL_NONE,

                /**
                 * @brief Specifies that the interpolated and clamped r texture coordinate should be compared to the value in the currently bound depth texture with function `result = 1`
                 */
                Always = GL_ALWAYS,

                /**
                 * @brief Specifies that the interpolated and clamped r texture coordinate should be compared to the value in the currently bound depth texture with function `result = (r == Dt)`
                 */
                Equal = GL_EQUAL,

                /**
                 * @brief Specifies that the interpolated and clamped r texture coordinate should be compared to the value in the currently bound depth texture with function `result = (r >= Dt)`
                 */
                GEqual = GL_GEQUAL,

                /**
                 * @brief Specifies that the interpolated and clamped r texture coordinate should be compared to the value in the currently bound depth texture with function `result = (r > Dt)`
                 */
                Greater = GL_GREATER,

                /**
                 * @brief Specifies that the interpolated and clamped r texture coordinate should be compared to the value in the currently bound depth texture with function `result = (r <= Dt)`
                 */
                LEqual = GL_LEQUAL,

                /**
                 * @brief Specifies that the interpolated and clamped r texture coordinate should be compared to the value in the currently bound depth texture with function `result = (r < Dt)`
                 */
                Less = GL_LESS,

                /**
                 * @brief Specifies that the interpolated and clamped r texture coordinate should be compared to the value in the currently bound depth texture with function `result = 0`
                 */
                Never = GL_NEVER,

                /**
                 * @brief Specifies that the interpolated and clamped r texture coordinate should be compared to the value in the currently bound depth texture with function `result = (r != Dt)`
                 */
                NotEqual = GL_NOTEQUAL,

            };

            /**
             * @brief Manages a texture binding lifetime
             */
            class BindGuard
            {

                public:

                    /**
                     * @brief Default constructor is disabled
                     */
                    BindGuard() = delete;

                    /**
                     * @brief Copy constructor is disabled
                     */
                    BindGuard(const BindGuard&) = delete;

                    /**
                     * @brief Move constructor is disabled
                     */
                    BindGuard(BindGuard&&) = delete;

                    /**
                     * @brief Constructs the guard and bind the texture
                     * 
                     * @param unit Texture unit to bind to
                     * @param texture Texture to bind
                     */
                    BindGuard(unsigned int unit, const Texture& texture) noexcept;

                    /**
                     * @brief Destructor
                     * 
                     * @note Automatically restore the previous texture used
                     */
                    ~BindGuard() noexcept;

                    /**
                     * @brief Copy assignment operator is disabled
                     */
                    BindGuard& operator=(const BindGuard&) = delete;

                    /**
                     * @brief Move assignment operator is disabled
                     */
                    BindGuard& operator=(BindGuard&&) = delete;


                private:

                    /**
                     * @brief Texture unit used
                     */
                    unsigned int _unit;

                    /**
                     * @brief Previous texture used
                     */
                    GLint _previous;

            };


            /**
             * @brief Returns the standard number of mipmap levels for texture dimensions
             * 
             * @param size Texture dimensions
             */
            static int mipmapLevels(const tbaricault::math::Vector2<int>& size);

            /**
             * @brief Clear a texture unit
             */
            static void unbind(unsigned int unit = 0) noexcept;

            /**
             * @brief Constructs an invalid texture
             */
            Texture() noexcept = default;

            /**
             * @brief Copy constructor is disabled
             */
            Texture(const Texture&) = delete;

            /**
             * @brief Move constructor
             * 
             * @param other Texture to move
             */
            Texture(Texture&& other) noexcept = default;

            /**
             * @brief Constructs a texture specifying its dimensions
             * 
             * @param size Texture dimensions
             */
            Texture(const tbaricault::math::Vector2<int>& size) noexcept;

            /**
             * @brief Constructs a texture from an image
             * 
             * @param image Source image
             * @param mipmaps Number of mipmap levels, `0` to auto determine
             */
            Texture(const tbaricault::images::Image& image, int mipmaps = 1) noexcept;

            /**
             * @brief Destructor
             */
            virtual ~Texture() noexcept;

            /**
             * @brief Copy assignment operator is disabled
             */
            Texture& operator=(const Texture&) = delete;

            /**
             * @brief Move assignement operator
             * 
             * @param other Texture to move
             * 
             * @return Reference to this texture
             */
            Texture& operator=(Texture&& other) noexcept = default;

            /**
             * @brief Converts the texture to image
             */
            operator tbaricault::images::Image() const;

            /**
             * @brief Returns the minifying function
             * 
             * @return Filter function
             */
            Filter getMinFilter() const noexcept;

            /**
             * @brief Returns the magnification function
             * 
             * @return Filter function
             */
            Filter getMagFilter() const noexcept;

            /**
             * @brief Returns the wrapping function for horizontal axis
             * 
             * @return Wrapping function
             */
            Wrap getWrapS() const noexcept;

            /**
             * @brief Returns the wrapping function for vertical axis
             * 
             * @return Wrapping function
             */
            Wrap getWrapT() const noexcept;

            /**
             * @brief Returns the index of the lowest mipmap level used for texture sampling
             * 
             * @return Level index
             */
            int getMipmapBaseLevel() const noexcept;

            /**
             * @brief Returns the index of the highest mipmap level used for texture sampling
             * 
             * @return Level index
             */
            int getMipmapMaxLevel() const noexcept;

            /**
             * @brief Returns the minimum level-of-detail
             * 
             * @return Level-of-detail
             */
            float getMinLOD() const noexcept;

            /**
             * @brief Returns the maximum level-of-detail
             * 
             * @return Level-of-detail
             */
            float getMaxLOD() const noexcept;

            /**
             * @brief Returns the level-of-detail fixed bias
             * 
             * @return Bias
             */
            float getLODBias() const noexcept;

            /**
             * @brief Returns the texture comparison mode for currently bound depth textures
             * 
             * @returns Comparison mode
             */
            Compare getCompare() const noexcept;

            /**
             * @brief Returns the texture border color
             * 
             * @return Color
             */
            tbaricault::colors::Color getBorderColor() const noexcept;

            /**
             * @brief Returns the texture dimensions
             * 
             * @return Texture size (width, height)
             */
            const tbaricault::math::Vector2<int>& getSize() const noexcept;

            /**
             * @brief Returns the number of mipmap levels of the texture
             * 
             * @return Number of mipmap levels
             */
            int getMipmapLevels() const noexcept;

            /**
             * @brief Sets the minifying function
             * 
             * @param value Filter function
             */
            void setMinFilter(Filter value) noexcept;

            /**
             * @brief Sets the magnification function
             * 
             * @param value Filter function
             * 
             * @note The magnification filter only accept `Nearest` and `Linear`
             */
            void setMagFilter(Filter value) noexcept;

            /**
             * @brief Sets the wrapping function for horizontal axis
             * 
             * @param value Wrapping function
             */
            void setWrapS(Wrap value) noexcept;

            /**
             * @brief Sets the wrapping function for vertical axis
             * 
             * @param value Wrapping function
             */
            void setWrapT(Wrap value) noexcept;

            /**
             * @brief Sets the texture border color
             * 
             * @param value Color
             */
            void setBorderColor(const tbaricault::colors::Color& value) noexcept;

            /**
             * @brief Sets the index of the lowest defined mipmap level
             * 
             * @param value Level index
             */
            void setMipmapBaseLevel(int value) noexcept;

            /**
             * @brief Sets the index of the highest defined mipmap level
             * 
             * @param value Level index
             */
            void setMipmapMaxLevel(int value) noexcept;

            /**
             * @brief Sets the minimum level-of-detail
             * 
             * @param value Level-of-detail
             */
            void setMinLOD(float value) noexcept;

            /**
             * @brief Sets the maximum level-of-detail
             * 
             * @param value Level-of-detail
             */
            void setMaxLOD(float value) noexcept;

            /**
             * @brief Sets the fixed bias value that is to be added to the level-of-detail for the texture before texture sampling
             * 
             * @param value Level-of-detail
             */
            void setLODBias(float value) noexcept;

            /**
             * @brief Specifies the texture comparison mode for currently bound depth textures
             * 
             * @param value Comparison mode
             */
            void setCompare(Compare value) noexcept;

            /**
             * @brief Resizes the texture
             * 
             * @param value New size in pixels
             * 
             * @note This operation will destroy the texture content
             */
            void setSize(const tbaricault::math::Vector2<int>& value) noexcept;

            /**
             * @brief Sets an image for a specific mipmap level
             * 
             * @param level Mipmap level to set
             * @param image Image to use
             * @param offset Image offset
             */
            void setMipmap(int level, const tbaricault::images::Image& image, const tbaricault::math::Vector2<int>& offset = 0) noexcept;

            /**
             * @brief Generates mipmap levels for this texture
             */
            void generateMipmap() noexcept;

            /**
             * @brief Binds the texture to a texture unit
             * 
             * @param unit Texture unit to bind to
             */
            void bind(unsigned int unit = 0) const noexcept;

            /**
             * @brief Scoped bind for the texture
             * 
             * @param unit Texture unit to bind to
             * 
             * @return Bind guard for this texture usage
             */
            BindGuard use(unsigned int unit = 0) const noexcept;


        protected:

            /**
             * @brief OpenGL texture identifier
             */
            GLuint _handle = 0;

            /**
             * @brief Texture dimensions
             */
            tbaricault::math::Vector2<int> _size;

            /**
             * @brief Number of mipmap levels
             */
            int _mipmaps = 1;


            /**
             * @brief Destroys the texture
             */
            void _destroy() noexcept override;

    };

}
