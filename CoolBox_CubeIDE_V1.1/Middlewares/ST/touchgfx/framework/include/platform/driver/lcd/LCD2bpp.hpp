/**
  ******************************************************************************
  * This file is part of the TouchGFX 4.13.0 distribution.
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

#ifndef LCD2BPP_HPP
#define LCD2BPP_HPP

#include <stdarg.h>
#include <touchgfx/Bitmap.hpp>
#include <touchgfx/Font.hpp>
#include <touchgfx/TextProvider.hpp>
#include <touchgfx/TextureMapTypes.hpp>
#include <touchgfx/Unicode.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/hal/Types.hpp>
#include <touchgfx/lcd/LCD.hpp>

namespace touchgfx
{
#undef LCD
#define USE_LSB

/**
 * @class LCD2bpp LCD2bpp.hpp platform/driver/lcd/LCD2bpp.hpp
 *
 * @brief This class contains the various low-level drawing routines for drawing bitmaps.
 *
 *        This class contains the various low-level drawing routines for drawing bitmaps, texts
 *        and rectangles on 2 bits per pixel grayscale displays.
 *
 * @note All coordinates are expected to be in absolute coordinates!
 *
 * @see LCD
 */
class LCD2bpp : public LCD
{
public:
    LCD2bpp();

    virtual ~LCD2bpp()
    {
    }

    /**
     * @fn virtual void LCD2bpp::init();
     *
     * @brief Performs initialization.
     *
     *        Performs initialization.
     */
    virtual void init();

    /**
     * @fn virtual void LCD2bpp::drawPartialBitmap(const Bitmap& bitmap, int16_t x, int16_t y, const Rect& rect, uint8_t alpha = 255, bool useOptimized = true);
     *
     * @brief Draws a portion of a bitmap.
     *
     * @param bitmap       The bitmap to draw.
     * @param x            The absolute x coordinate to place pixel (0, 0) on the screen.
     * @param y            The absolute y coordinate to place pixel (0, 0) on the screen.
     * @param rect         A rectangle describing what region of the bitmap is to be drawn.
     * @param alpha        Optional alpha value. Default is 255 (solid).
     * @param useOptimized if false, do not attempt to substitute (parts of) this bitmap with
     *                     faster fillrects.
     */
    virtual void drawPartialBitmap(const Bitmap& bitmap, int16_t x, int16_t y, const Rect& rect, uint8_t alpha = 255, bool useOptimized = true);

    /**
     * @fn virtual void LCD2bpp::blitCopy(const uint16_t* sourceData, const Rect& source, const Rect& blitRect, uint8_t alpha, bool hasTransparentPixels);
     *
     * @brief Blits a 2D source-array to the framebuffer.
     *
     *        Blits a 2D source-array to the framebuffer perfoming alpha-blending (and
     *        tranparency keying) as specified Performs a software blend if HAL does not
     *        support BLIT_COPY_WITH_ALPHA and alpha != 255.
     *
     * @param sourceData           The source-array pointer (points to the beginning of the
     *                             data).  The sourceData must be stored as 16-bits RGB565
     *                             values.
     * @param source               The location and dimension of the source.
     * @param blitRect             A rectangle describing what region is to be drawn.
     * @param alpha                The alpha value to use for blending (255 = solid, no blending)
     * @param hasTransparentPixels If true, this data copy contains transparent pixels and
     *                             require hardware support for that to be enabled.
     */
    virtual void blitCopy(const uint16_t* sourceData, const Rect& source, const Rect& blitRect, uint8_t alpha, bool hasTransparentPixels);

    /**
     * @fn virtual void LCD2bpp::blitCopy(const uint8_t* sourceData, Bitmap::BitmapFormat sourceFormat, const Rect& source, const Rect& blitRect, uint8_t alpha, bool hasTransparentPixels);
     *
     * @brief Blits a 2D source-array to the framebuffer while converting the format.
     *
     *        Blits a 2D source-array to the framebuffer perfoming alpha-blending (and
     *        tranparency keying) as specified. Performs a software blend if HAL does not
     *        support BLIT_COPY_WITH_ALPHA and alpha != 255. LCD2 supports source data
     *        formats: RGB565 and ARGB8888.
     *
     * @param sourceData           The source-array pointer (points to the beginning of the
     *                             data). The sourceData must be stored in a format suitable for
     *                             the selected display.
     * @param sourceFormat         The bitmap format used in the source data.
     * @param source               The location and dimension of the source.
     * @param blitRect             A rectangle describing what region is to be drawn.
     * @param alpha                The alpha value to use for blending (255 = solid, no blending)
     * @param hasTransparentPixels If true, this data copy contains transparent pixels and
     *                             require hardware support for that to be enabled.
     */
    virtual void blitCopy(const uint8_t* sourceData, Bitmap::BitmapFormat sourceFormat, const Rect& source, const Rect& blitRect, uint8_t alpha, bool hasTransparentPixels);

    /**
     * @fn virtual uint16_t* LCD2bpp::copyFrameBufferRegionToMemory(const Rect& visRegion, const Rect& absRegion, const BitmapId bitmapId);
     *
     * @brief Copies part of the frame buffer region to memory.
     *
     *        Copies part of the framebuffer region to memory. The memory is given as BitmapId,
     *        which can be BITMAP_ANIMATION_STORAGE. The two regions given are the visible region
     *        and the absolute region on screen. This is used to copy only a part of an area. This
     *        might be the case if a SnapshotWidget is placed inside a Container where parts of the
     *        SnapshowWidget is outside the area defined by the Container. The visible region must
     *        be completely inside the absolute region.
     *
     * @note There is only one instance of animation storage. The content of the animation storage
     *       outside the given region is undefined.
     *
     * @param visRegion The visible region.
     * @param absRegion The absolute region.
     * @param bitmapId  Identifier for the bitmap.
     *
     * @returns Null if it fails, else a pointer to the data in the given bitmap.
     *
     * @see blitCopy
     */
    virtual uint16_t* copyFrameBufferRegionToMemory(const Rect& visRegion, const Rect& absRegion, const BitmapId bitmapId);

    /**
     * @fn virtual void LCD2bpp::fillRect(const Rect& rect, colortype color, uint8_t alpha = 255);
     *
     * @brief Draws a filled rectangle in the specified color.
     *
     *        Draws a filled rectangle in the specified color.
     *
     * @param rect  The rectangle to draw in absolute coordinates.
     * @param color The rectangle color.
     * @param alpha The rectangle opacity (255=solid)
     */
    virtual void fillRect(const Rect& rect, colortype color, uint8_t alpha = 255);

    /**
     * @fn virtual uint8_t LCD2bpp::bitDepth() const
     *
     * @brief Number of bits per pixel used by the display.
     *
     *        Number of bits per pixel used by the display.
     *
     * @return The number of bits per pixel.
     */
    virtual uint8_t bitDepth() const
    {
        return 2;
    }

    /**
     * @fn virtual Bitmap::BitmapFormat LCD2bpp::framebufferFormat() const
     *
     * @brief Framebuffer format used by the display
     *
     *        Framebuffer format used by the display
     *
     * @return Bitmap::GRAY2.
     */
    virtual Bitmap::BitmapFormat framebufferFormat() const
    {
        return Bitmap::GRAY2;
    }

    /**
     * @fn virtual uint16_t LCD2bpp::framebufferStride() const
     *
     * @brief Framebuffer stride in bytes
     *
     *        Framebuffer stride in bytes. The distance (in bytes) from the start of one
     *        framebuffer row, to the next.
     *
     * @return The number of bytes in one framebuffer row.
     */
    virtual uint16_t framebufferStride() const
    {
        return getFramebufferStride();
    }

    /**
     * @fn FORCE_INLINE_FUNCTION static uint16_t LCD2bpp::getFramebufferStride()
     *
     * @brief Framebuffer stride in bytes
     *
     *        Framebuffer stride in bytes. The distance (in bytes) from the start of one
     *        framebuffer row, to the next.
     *
     * @return The number of bytes in one framebuffer row.
     */
    FORCE_INLINE_FUNCTION static uint16_t getFramebufferStride()
    {
        assert(HAL::FRAME_BUFFER_WIDTH > 0 && "HAL has not been initialized yet");
        return (HAL::FRAME_BUFFER_WIDTH + 3) / 4;
    }

    /**
     * @fn virtual colortype LCD2bpp::getColorFrom24BitRGB(uint8_t red, uint8_t green, uint8_t blue) const
     *
     * @brief Generates a color representation to be used on the LCD, based on 24 bit RGB values.
     *
     *        Generates a color representation to be used on the LCD, based on 24 bit RGB values.
     *
     * @param red   Value of the red part (0-255).
     * @param green Value of the green part (0-255).
     * @param blue  Value of the blue part (0-255).
     *
     * @return The color representation depending on LCD color format.
     */
    virtual colortype getColorFrom24BitRGB(uint8_t red, uint8_t green, uint8_t blue) const
    {
        return getColorFromRGB(red, green, blue);
    }

    /**
     * @fn FORCE_INLINE_FUNCTION static colortype LCD2bpp::getColorFromRGB(uint8_t red, uint8_t green, uint8_t blue)
     *
     * @brief Generates a color representation to be used on the LCD, based on 24 bit RGB values.
     *
     *        Generates a color representation to be used on the LCD, based on 24 bit RGB values.
     *
     * @param red   Value of the red part (0-255).
     * @param green Value of the green part (0-255).
     * @param blue  Value of the blue part (0-255).
     *
     * @return The color representation depending on LCD color format.
     */
    FORCE_INLINE_FUNCTION static colortype getColorFromRGB(uint8_t red, uint8_t green, uint8_t blue)
    {
        // Find the GRAY value (http://en.wikipedia.org/wiki/Luma_%28video%29) rounded to nearest integer
        return (red * 54 + green * 183 + blue * 19) >> 14;
    }

    /**
     * @fn virtual uint8_t LCD2bpp::getRedColor(colortype color) const
     *
     * @brief Gets the red color part of a color.
     *
     *        Gets the red color part of a color. As this function must work for all color depths,
     *        it can be somewhat slow if used in speed critical sections. Consider finding the
     *        color in another way, if possible.
     *
     * @param color The color value.
     *
     * @return The red part of the color.
     */
    virtual uint8_t getRedColor(colortype color) const
    {
        return getRedFromColor(color);
    }

    /**
     * @fn virtual uint8_t LCD2bpp::getRedFromColor(colortype color) const
     *
     * @brief Gets red from color
     *
     * @param color The color.
     *
     * @return The red from color.
     */
    virtual uint8_t getRedFromColor(colortype color) const
    {
        return (color & 0x3) * 0x55;
    }

    /**
     * @fn virtual uint8_t LCD2bpp::getGreenColor(colortype color) const
     *
     * @brief Gets the green color part of a color.
     *
     *        Gets the green color part of a color. As this function must work for all color depths,
     *        it can be somewhat slow if used in speed critical sections. Consider finding the
     *        color in another way, if possible.
     *
     * @param color The 16 bit color value.
     *
     * @return The green part of the color.
     */
    virtual uint8_t getGreenColor(colortype color) const
    {
        return getGreenFromColor(color);
    }

    /**
     * @fn FORCE_INLINE_FUNCTION static uint8_t LCD2bpp::getGreenFromColor(colortype color)
     *
     * @brief Gets green from color
     *
     * @param color The color.
     *
     * @return The green from color.
     */
    FORCE_INLINE_FUNCTION static uint8_t getGreenFromColor(colortype color)
    {
        return (color & 0x3) * 0x55;
    }

    /**
     * @fn virtual uint8_t LCD2bpp::getBlueColor(colortype color) const
     *
     * @brief Gets the blue color part of a color.
     *
     *        Gets the blue color part of a color. As this function must work for all color depths,
     *        it can be somewhat slow if used in speed critical sections. Consider finding the
     *        color in another way, if possible.
     *
     * @param color The 16 bit color value.
     *
     * @return The blue part of the color.
     */
    virtual uint8_t getBlueColor(colortype color) const
    {
        return getBlueFromColor(color);
    }

    /**
     * @fn FORCE_INLINE_FUNCTION static uint8_t LCD2bpp::getBlueFromColor(colortype color)
     *
     * @brief Gets blue from color
     *
     * @param color The color.
     *
     * @return The blue from color.
     */
    FORCE_INLINE_FUNCTION static uint8_t getBlueFromColor(colortype color)
    {
        return (color & 0x3) * 0x55;
    }

    /**
     * @fn void LCD2bpp::enableTextureMapperAll();
     *
     * @brief Enables the texture mappers for all image formats.
     *
     *        Enables the texture mappers for all image formats. This allows drawing any image
     *        using Bilinear Interpolation and Nearest Neighbor algorithms, but might use a
     *        lot of memory for the drawing algorithms.
     */
    void enableTextureMapperAll();

    /**
     * @fn void LCD2bpp::enableTextureMapperGRAY2();
     *
     * @brief Enables the texture mappers for GRAY2 image format.
     *
     *        Enables the texture mappers for GRAY2 image format. This allows drawing
     *        GRAY2 images using Bilinear Interpolation and Nearest Neighbor algorithms.
     *
     * @see enableTextureMapperGRAY2_BilinearInterpolation
     * @see enableTextureMapperGRAY2_NearestNeighbor
     */
    void enableTextureMapperGRAY2();

    /**
     * @fn void LCD2bpp::enableTextureMapperGRAY2_BilinearInterpolation();
     *
     * @brief Enables the texture mappers for GRAY2 image format for Bilinear Interpolation algorithm.
     *
     *        Enables the texture mappers for GRAY2 image format. This allows drawing
     *        GRAY2 images using Bilinear Interpolation algorithm.
     *
     * @see enableTextureMapperGRAY2
     * @see enableTextureMapperGRAY2_NearestNeighbor
     */
    void enableTextureMapperGRAY2_BilinearInterpolation();

    /**
     * @fn void LCD2bpp::enableTextureMapperGRAY2_NearestNeighbor();
     *
     * @brief Enables the texture mappers for GRAY2 image format for Nearest Neighbor algorithm.
     *
     *        Enables the texture mappers for GRAY2 image format. This allows drawing
     *        GRAY2 images using Nearest Neighbor algorithm.
     *
     * @see enableTextureMapperGRAY2
     * @see enableTextureMapperGRAY2_BilinearInterpolation
     */
    void enableTextureMapperGRAY2_NearestNeighbor();

protected:
    static const uint8_t alphaTable2bpp[256]; ///< The alpha lookup table to avoid arithmetics when alpha blending

    /**
     * @fn virtual DrawTextureMapScanLineBase* LCD2bpp::getTextureMapperDrawScanLine(const TextureSurface& texture, RenderingVariant renderVariant, uint8_t alpha);
     *
     * @brief Gets pointer to object that can draw a texture mapper scan line for the given
     *        renderVariant.
     *
     *        Gets pointer to object that can draw a texture mapper scan line for the given
     *        renderVariant. Allows for highly specialized versions of these functions for
     *        improved speed.
     *
     * @param texture       The texture surface.
     * @param renderVariant The render variant.
     * @param alpha             The global alpha value.
     *
     * @return Null if it fails, else the texture mapper draw scan line.
     */
    virtual DrawTextureMapScanLineBase* getTextureMapperDrawScanLine(const TextureSurface& texture, RenderingVariant renderVariant, uint8_t alpha);

    /**
     * @fn static int LCD2bpp::nextPixel(bool rotatedDisplay, TextRotation textRotation);
     *
     * @brief Find out how much to advance in the display buffer to get to the next pixel.
     *
     *        Find out how much to advance in the display buffer to get to the next pixel.
     *
     * @param rotatedDisplay Is the display running in portrait mode?
     * @param textRotation   Rotation to perform.
     *
     * @return How much to advance to get to the next pixel.
     */
    static int nextPixel(bool rotatedDisplay, TextRotation textRotation);

    /**
     * @fn static int LCD2bpp::nextLine(bool rotatedDisplay, TextRotation textRotation);
     *
     * @brief Find out how much to advance in the display buffer to get to the next line.
     *
     *        Find out how much to advance in the display buffer to get to the next line.
     *
     * @param rotatedDisplay Is the display running in portrait mode?
     * @param textRotation   Rotation to perform.
     *
     * @return How much to advance to get to the next line.
     */
    static int nextLine(bool rotatedDisplay, TextRotation textRotation);

    /**
     * @fn virtual void LCD2bpp::drawGlyph(uint16_t* wbuf, Rect widgetArea, int16_t x, int16_t y, uint16_t offsetX, uint16_t offsetY, const Rect& invalidatedArea, const GlyphNode* glyph, const uint8_t* glyphData, uint8_t dataFormatA4, colortype color, uint8_t bitsPerPixel, uint8_t alpha, TextRotation rotation);
     *
     * @brief Private version of draw-glyph with explicit destination buffer pointer argument.
     *
     *        Private version of draw-glyph with explicit destination buffer pointer argument.
     *        For all parameters (except the buffer pointer) see the public function drawString().
     *
     * @param [in] wbuf       The destination (frame) buffer to draw to.
     * @param widgetArea      The canvas to draw the glyph inside.
     * @param x               Horizontal offset to start drawing the glyph.
     * @param y               Vertical offset to start drawing the glyph.
     * @param offsetX         Horizontal offset in the glyph to start drawing from.
     * @param offsetY         Vertical offset in the glyph to start drawing from.
     * @param invalidatedArea The area to draw within.
     * @param glyph           Specifications of the glyph to draw.
     * @param glyphData       Data containing the actual glyph (dense format)
     * @param dataFormatA4    The glyph is saved using ST A4 format.
     * @param color           The color of the glyph.
     * @param bitsPerPixel    Bit depth of the glyph.
     * @param alpha           The transparency of the glyph.
     * @param rotation        Rotation to do before drawing the glyph.
     */
    virtual void drawGlyph(uint16_t* wbuf, Rect widgetArea, int16_t x, int16_t y, uint16_t offsetX, uint16_t offsetY, const Rect& invalidatedArea, const GlyphNode* glyph, const uint8_t* glyphData, uint8_t dataFormatA4, colortype color, uint8_t bitsPerPixel, uint8_t alpha, TextRotation rotation);

    /**
     * @fn static void LCD2bpp::blitCopyAlphaPerPixel(const uint16_t* sourceData16, const uint8_t* sourceAlphaData, const Rect& source, const Rect& blitRect, uint8_t alpha);
     *
     * @brief Blit a 2D source-array to the framebuffer.
     *
     *        Blit a 2D source-array to the framebuffer performing alpha-blending per pixel as
     *        specified Performs always a software blend.
     *
     * @param sourceData16    The source-array pointer (points to the beginning of the data). The
     *                        sourceData must be stored as 2bpp GRAY2 values.
     * @param sourceAlphaData The alpha channel array pointer (points to the beginning of the data)
     * @param source          The location and dimension of the source.
     * @param blitRect        A rectangle describing what region is to be drawn.
     * @param alpha           The alpha value to use for blending applied to the whole image (255 =
     *                        solid, no blending)
     */
    static void blitCopyAlphaPerPixel(const uint16_t* sourceData16, const uint8_t* sourceAlphaData, const Rect& source, const Rect& blitRect, uint8_t alpha);

    /**
     * @fn void LCD2bpp::copyRect(const uint8_t* srcAddress, uint16_t srcStride, uint8_t srcPixelOffset, uint8_t* RESTRICT dstAddress, uint16_t dstStride, uint8_t dstPixelOffset, uint16_t width, uint16_t height) const;
     *
     * @brief Copies a rectangular area.
     *
     *        Copies a rectangular area.
     *
     * @param      srcAddress     Source address (byte address).
     * @param      srcStride      Source stride (number of bytes to advance to next line).
     * @param      srcPixelOffset Source pixel offset (first pixel in first source byte).
     * @param [in] dstAddress     If destination address (byte address).
     * @param      dstStride      Destination stride (number of bytes to advance to next line).
     * @param      dstPixelOffset Destination pixel offset (first pixel in destination byte).
     * @param      width          The width of area (in pixels).
     * @param      height         The height of area (in pixels).
     */
    void copyRect(const uint8_t* srcAddress, uint16_t srcStride, uint8_t srcPixelOffset, uint8_t* RESTRICT dstAddress, uint16_t dstStride, uint8_t dstPixelOffset, uint16_t width, uint16_t height) const;

private:
    DrawTextureMapScanLineBase* textureMapper_GRAY2_NonOpaque_NearestNeighbor_GA;
    DrawTextureMapScanLineBase* textureMapper_GRAY2_Opaque_NearestNeighbor_GA;
    DrawTextureMapScanLineBase* textureMapper_GRAY2_NonOpaque_BilinearInterpolation_GA;
    DrawTextureMapScanLineBase* textureMapper_GRAY2_Opaque_BilinearInterpolation_GA;

    FORCE_INLINE_FUNCTION static uint8_t bilinearInterpolate8(uint8_t c00, uint8_t c10, uint8_t x)
    {
        assert(x < 16);
        uint16_t xy10 = 16 * x;
        uint16_t xy00 = 256 - xy10;

        return (c00 * xy00 + c10 * xy10) >> 8;
    }

    FORCE_INLINE_FUNCTION static uint8_t bilinearInterpolate8(uint8_t c00, uint8_t c10, uint8_t c01, uint8_t c11, uint8_t x, uint8_t y)
    {
        assert(x < 16 && y < 16);
        uint16_t xy11 = x * y;
        uint16_t xy10 = 16 * x - xy11;
        uint16_t xy01 = 16 * y - xy11;
        uint16_t xy00 = 256 - (xy11 + xy10 + xy01);

        return (c00 * xy00 + c10 * xy10 + c01 * xy01 + c11 * xy11) >> 8;
    }

    FORCE_INLINE_FUNCTION static uint8_t div255_2(uint16_t value)
    {
        return div255(value * 0x55) >> 6;
    }

    class DrawTextureMapScanLineBase2 : public DrawTextureMapScanLineBase
    {
    protected:
        FORCE_INLINE_FUNCTION bool overrunCheckBilinearInterpolation(uint32_t& destOffset, int& pixelsToDraw, fixed16_16& U, fixed16_16& V, fixed16_16 deltaU, fixed16_16 deltaV, const int16_t maxWidth, const int16_t maxHeight);
        FORCE_INLINE_FUNCTION bool overrunCheckNearestNeighbor(uint32_t& destOffset, int& pixelsToDraw, fixed16_16& U, fixed16_16& V, fixed16_16 deltaU, fixed16_16 deltaV, const int16_t maxWidth, const int16_t maxHeight);
    };

    class TextureMapper_GRAY2_NonOpaque_BilinearInterpolation_GA : public DrawTextureMapScanLineBase2
    {
    public:
        virtual void drawTextureMapScanLineSubdivisions(int subdivisions, const int widthModLength, int pixelsToDraw, const int affineLength, float oneOverZRight, float UOverZRight, float VOverZRight, fixed16_16 U, fixed16_16 V, fixed16_16 deltaU, fixed16_16 deltaV, float ULeft, float VLeft, float URight, float VRight, float ZRight, const DrawingSurface& dest, const int destX, const int destY, const int16_t bitmapWidth, const int16_t bitmapHeight, const TextureSurface& texture, uint8_t alpha, const float dOneOverZdXAff, const float dUOverZdXAff, const float dVOverZdXAff);

    private:
        FORCE_INLINE_FUNCTION void writePixel(uint16_t* destAddress, uint32_t const destOffset, const uint16_t* const textureBits, const uint8_t* const alphaBits, const int16_t bitmapStride, const int UInt, const int VInt, const uint8_t UFrac, const uint8_t VFrac, const uint8_t alpha);
        void writePixelOnEdge(uint16_t* destAddress, uint32_t const destOffset, const uint16_t* const textureBits, const uint8_t* const alphaBits, const int16_t bitmapStride, const int16_t bitmapWidth, const int16_t bitmapHeight, const int UInt, const int VInt, const uint8_t UFrac, const uint8_t VFrac, const uint8_t alpha);
    };

    class TextureMapper_GRAY2_Opaque_BilinearInterpolation_GA : public DrawTextureMapScanLineBase2
    {
    public:
        virtual void drawTextureMapScanLineSubdivisions(int subdivisions, const int widthModLength, int pixelsToDraw, const int affineLength, float oneOverZRight, float UOverZRight, float VOverZRight, fixed16_16 U, fixed16_16 V, fixed16_16 deltaU, fixed16_16 deltaV, float ULeft, float VLeft, float URight, float VRight, float ZRight, const DrawingSurface& dest, const int destX, const int destY, const int16_t bitmapWidth, const int16_t bitmapHeight, const TextureSurface& texture, uint8_t alpha, const float dOneOverZdXAff, const float dUOverZdXAff, const float dVOverZdXAff);

    private:
        FORCE_INLINE_FUNCTION void writePixel(uint16_t* destAddress, uint32_t const destOffset, const uint16_t* const textureBits, const int16_t bitmapStride, const int UInt, const int VInt, const uint8_t UFrac, const uint8_t VFrac, const uint8_t alpha);
        void writePixelOnEdge(uint16_t* destAddress, uint32_t const destOffset, const uint16_t* const textureBits, const int16_t bitmapStride, const int16_t bitmapWidth, const int16_t bitmapHeight, const int UInt, const int VInt, const uint8_t UFrac, const uint8_t VFrac, const uint8_t alpha);
    };

    class TextureMapper_GRAY2_NonOpaque_NearestNeighbor_GA : public DrawTextureMapScanLineBase2
    {
    public:
        virtual void drawTextureMapScanLineSubdivisions(int subdivisions, const int widthModLength, int pixelsToDraw, const int affineLength, float oneOverZRight, float UOverZRight, float VOverZRight, fixed16_16 U, fixed16_16 V, fixed16_16 deltaU, fixed16_16 deltaV, float ULeft, float VLeft, float URight, float VRight, float ZRight, const DrawingSurface& dest, const int destX, const int destY, const int16_t bitmapWidth, const int16_t bitmapHeight, const TextureSurface& texture, uint8_t alpha, const float dOneOverZdXAff, const float dUOverZdXAff, const float dVOverZdXAff);

    private:
        FORCE_INLINE_FUNCTION void writePixel(uint16_t* destAddress, uint32_t const destOffset, const uint16_t* const textureBits, const uint8_t* const alphaBits, const int16_t bitmapStride, const int UInt, const int VInt, const uint8_t alpha);
    };

    class TextureMapper_GRAY2_Opaque_NearestNeighbor_GA : public DrawTextureMapScanLineBase2
    {
    public:
        virtual void drawTextureMapScanLineSubdivisions(int subdivisions, const int widthModLength, int pixelsToDraw, const int affineLength, float oneOverZRight, float UOverZRight, float VOverZRight, fixed16_16 U, fixed16_16 V, fixed16_16 deltaU, fixed16_16 deltaV, float ULeft, float VLeft, float URight, float VRight, float ZRight, const DrawingSurface& dest, const int destX, const int destY, const int16_t bitmapWidth, const int16_t bitmapHeight, const TextureSurface& texture, uint8_t alpha, const float dOneOverZdXAff, const float dUOverZdXAff, const float dVOverZdXAff);

    private:
        FORCE_INLINE_FUNCTION void writePixel(uint16_t* destAddress, uint32_t const destOffset, const uint16_t* const textureBits, const int16_t bitmapStride, const int UInt, const int VInt, const uint8_t alpha);
    };

    class TextureMapper_A4_NearestNeighbor_GA : public DrawTextureMapScanLineBase2
    {
    public:
        virtual void drawTextureMapScanLineSubdivisions(int subdivisions, const int widthModLength, int pixelsToDraw, const int affineLength, float oneOverZRight, float UOverZRight, float VOverZRight, fixed16_16 U, fixed16_16 V, fixed16_16 deltaU, fixed16_16 deltaV, float ULeft, float VLeft, float URight, float VRight, float ZRight, const DrawingSurface& dest, const int destX, const int destY, const int16_t bitmapWidth, const int16_t bitmapHeight, const TextureSurface& texture, uint8_t alpha, const float dOneOverZdXAff, const float dUOverZdXAff, const float dVOverZdXAff);

    private:
        FORCE_INLINE_FUNCTION void writePixel(uint16_t* const destAddress, const uint32_t destOffset, const uint8_t a4, const uint8_t alpha);
    };

    class TextureMapper_A4_BilinearInterpolation_GA : public DrawTextureMapScanLineBase2
    {
    public:
        virtual void drawTextureMapScanLineSubdivisions(int subdivisions, const int widthModLength, int pixelsToDraw, const int affineLength, float oneOverZRight, float UOverZRight, float VOverZRight, fixed16_16 U, fixed16_16 V, fixed16_16 deltaU, fixed16_16 deltaV, float ULeft, float VLeft, float URight, float VRight, float ZRight, const DrawingSurface& dest, const int destX, const int destY, const int16_t bitmapWidth, const int16_t bitmapHeight, const TextureSurface& texture, uint8_t alpha, const float dOneOverZdXAff, const float dUOverZdXAff, const float dVOverZdXAff);

    private:
        FORCE_INLINE_FUNCTION void writePixel(uint16_t* const destAddress, const uint32_t destOffset, const uint16_t* const textureBits, const uint32_t offset, const int16_t bitmapStride, const uint8_t UFrac, const uint8_t VFrac, const uint8_t alpha);
        void writePixelOnEdge(uint16_t* const destAddress, const uint32_t destOffset, const uint16_t* const textureBits, const uint16_t bitmapStride, const int16_t bitmapWidth, const int16_t bitmapHeight, const int UInt, const int VInt, const uint8_t UFrac, const uint8_t VFrac, const uint8_t alpha);
    };
};

/**
 * @fn FORCE_INLINE_FUNCTION int LCD2shiftVal(int offset)
 *
 * @brief Shift value to get the right pixel in a byte.
 *
 * @param offset The offset.
 *
 * @return The shift value.
 */
FORCE_INLINE_FUNCTION int LCD2shiftVal(int offset)
{
#ifdef USE_LSB
    return (offset & 3) << 1;
#else
    return (3 - (offset & 3)) << 1;
#endif
}

/**
 * @fn FORCE_INLINE_FUNCTION uint8_t LCD2getPixel(const uint8_t* addr, int offset)
 *
 * @brief Get pixel from buffer/image.
 *
 * @param addr   The address.
 * @param offset The offset.
 *
 * @return The pixel value.
 */
FORCE_INLINE_FUNCTION uint8_t LCD2getPixel(const uint8_t* addr, int offset)
{
    return (addr[offset >> 2] >> LCD2shiftVal(offset)) & 3;
}

/**
 * @fn FORCE_INLINE_FUNCTION uint8_t LCD2getPixel(const uint16_t* addr, int offset)
 *
 * @brief Get pixel from buffer/image.
 *
 * @param addr   The address.
 * @param offset The offset.
 *
 * @return The pixel value.
 */
FORCE_INLINE_FUNCTION uint8_t LCD2getPixel(const uint16_t* addr, int offset)
{
    return LCD2getPixel(reinterpret_cast<const uint8_t*>(addr), offset);
}

/**
 * @fn FORCE_INLINE_FUNCTION void LCD2setPixel(uint8_t* addr, int offset, uint8_t value)
 *
 * @brief Set pixel in buffer.
 *
 * @param [in] addr The address.
 * @param offset    The offset.
 * @param value     The value.
 */
FORCE_INLINE_FUNCTION void LCD2setPixel(uint8_t* addr, int offset, uint8_t value)
{
    int shift = LCD2shiftVal(offset);
    addr[offset >> 2] = (addr[offset >> 2] & ~(3 << shift)) | ((value & 3) << shift);
}

/**
 * @fn FORCE_INLINE_FUNCTION void LCD2setPixel(uint16_t* addr, int offset, uint8_t value)
 *
 * @brief Set pixel in buffer.
 *
 * @param [in] addr The address.
 * @param offset    The offset.
 * @param value     The value.
 */
FORCE_INLINE_FUNCTION void LCD2setPixel(uint16_t* addr, int offset, uint8_t value)
{
    LCD2setPixel(reinterpret_cast<uint8_t*>(addr), offset, value);
}

/**
 * @class LCD2DebugPrinter LCD2bpp.hpp platform/driver/lcd/LCD2bpp.hpp
 *
 * @brief The class LCD2DebugPrinter implements the DebugPrinter interface for printing debug messages on top of 24bit framebuffer.
 *
 *        The class LCD2DebugPrinter implements the DebugPrinter interface for printing debug messages on top of 24bit framebuffer.
 *
 * @see DebugPrinter
 */
class LCD2DebugPrinter : public DebugPrinter
{
public:
    virtual void draw(const Rect& rect) const;
};
} // namespace touchgfx
#endif // LCD2BPP_HPP
