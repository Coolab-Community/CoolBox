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

#ifndef LCD_HPP
#define LCD_HPP

#include <stdarg.h>
#include <touchgfx/Bitmap.hpp>
#include <touchgfx/Font.hpp>
#include <touchgfx/TextProvider.hpp>
#include <touchgfx/TextureMapTypes.hpp>
#include <touchgfx/Unicode.hpp>
#include <touchgfx/Utils.hpp>
#include <touchgfx/hal/Types.hpp>

namespace touchgfx
{
struct Gradients;
struct Edge;
#undef LCD

/**
 * @class LCD LCD.hpp touchgfx/lcd/LCD.hpp
 *
 * @brief This class contains the various low-level drawing routines for drawing bitmaps, texts and
 *        rectangles.
 *
 *        This class contains the various low-level drawing routines for drawing bitmaps, texts
 *        and rectangles.
 *
 * @note All coordinates are expected to be in absolute coordinates!
 */
class LCD
{
public:
    /**
     * @fn virtual LCD::~LCD()
     *
     * @brief Destructor.
     *
     *        Destructor.
     */
    virtual ~LCD()
    {
    }

    /**
     * @fn virtual void LCD::init()
     *
     * @brief Performs initialization.
     *
     *        Performs initialization.
     */
    virtual void init()
    {
    }

    /**
    * @fn virtual void LCD::drawPartialBitmap(const Bitmap& bitmap, int16_t x, int16_t y, const Rect& rect, uint8_t alpha = 255, bool useOptimized = true) = 0;
    *
    * @brief Draws a portion of a bitmap.
    *
    *        Draws a portion of a bitmap.
    *
    * @param bitmap       The bitmap to draw.
    * @param x            The absolute x coordinate to place pixel (0,0) on the screen.
    * @param y            The absolute y coordinate to place pixel (0,0) on the screen.
    * @param rect         A rectangle describing what region of the bitmap is to be drawn.
    * @param alpha        Optional alpha value. Default is 255 (solid).
    * @param useOptimized if false, do not attempt to substitute (parts of) this bitmap with
    *                     faster fillrects.
    */
    virtual void drawPartialBitmap(const Bitmap& bitmap, int16_t x, int16_t y, const Rect& rect, uint8_t alpha = 255, bool useOptimized = true) = 0;

    /**
     * @fn virtual void LCD::blitCopy(const uint16_t* sourceData, const Rect& source, const Rect& blitRect, uint8_t alpha, bool hasTransparentPixels) = 0;
     *
     * @brief Blits a 2D source-array to the framebuffer.
     *
     *        Blits a 2D source-array to the framebuffer perfoming alpha-blending (and
     *        tranparency keying) as specified. Performs a software blend if HAL does not
     *        support BLIT_COPY_WITH_ALPHA and alpha != 255.
     *
     * @param sourceData           The source-array pointer (points to the beginning of the
     *                             data). The sourceData must be stored in a format suitable for
     *                             the selected display.
     * @param source               The location and dimension of the source.
     * @param blitRect             A rectangle describing what region is to be drawn.
     * @param alpha                The alpha value to use for blending (255 = solid, no blending)
     * @param hasTransparentPixels If true, this data copy contains transparent pixels and
     *                             require hardware support for that to be enabled.
     */
    virtual void blitCopy(const uint16_t* sourceData, const Rect& source, const Rect& blitRect, uint8_t alpha, bool hasTransparentPixels) = 0;

    /**
     * @fn virtual void LCD::blitCopy(const uint8_t* sourceData, Bitmap::BitmapFormat sourceFormat, const Rect& source, const Rect& blitRect, uint8_t alpha, bool hasTransparentPixels) = 0;
     *
     * @brief Blits a 2D source-array to the frame buffer while converting the format.
     *
     *        Blits a 2D source-array to the frame buffer performing alpha-blending (and
     *        transparency keying) as specified. Performs a software blend if HAL does not
     *        support BLIT_COPY_WITH_ALPHA and alpha != 255.
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
    virtual void blitCopy(const uint8_t* sourceData, Bitmap::BitmapFormat sourceFormat, const Rect& source, const Rect& blitRect, uint8_t alpha, bool hasTransparentPixels) = 0;

    /**
     * @fn uint16_t* LCD::copyFrameBufferRegionToMemory(const Rect& region, const BitmapId bitmapId = BITMAP_ANIMATION_STORAGE)
     *
     * @brief Copies a part of the frame buffer.
     *
     *        Copies a part of the frame buffer to a bitmap. The bitmap must be a dynamic bitmap or
     *        animation storage (default). Only the part specified with by parameter region is
     *        copied.
     *
     * @note There is only one instance of animation storage. The content of the animation storage
     *       outside the given region is undefined.
     *
     * @param region   The part to copy.
     * @param bitmapId (Optional) The bitmap to store the data in. Default parameter is Animation
     *                 Storage.
     *
     * @returns A pointer to the copy.
     *
     * @see blitCopy
     */
    uint16_t* copyFrameBufferRegionToMemory(const Rect& region, const BitmapId bitmapId = BITMAP_ANIMATION_STORAGE)
    {
        return copyFrameBufferRegionToMemory(region, region, bitmapId);
    }

    /**
     * @fn virtual uint16_t* LCD::copyFrameBufferRegionToMemory(const Rect& visRegion, const Rect& absRegion, const BitmapId bitmapId) = 0;
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
    virtual uint16_t* copyFrameBufferRegionToMemory(const Rect& visRegion, const Rect& absRegion, const BitmapId bitmapId) = 0;

    /**
     * @fn virtual void LCD::fillRect(const Rect& rect, colortype color, uint8_t alpha = 255) = 0;
     *
     * @brief Draws a filled rectangle in the specified color.
     *
     *        Draws a filled rectangle in the specified color.
     *
     * @param rect  The rectangle to draw in absolute coordinates.
     * @param color The rectangle color.
     * @param alpha The rectangle opacity (255=solid)
     */
    virtual void fillRect(const Rect& rect, colortype color, uint8_t alpha = 255) = 0;

    /**
     * @fn void LCD::drawHorizontalLine(int16_t x, int16_t y, uint16_t width, uint16_t lineWidth, colortype color, uint8_t alpha = 255);
     *
     * @brief Draws a horizontal line with the specified color.
     *
     *        Draws a horizontal line with the specified color.
     *
     * @param x         The x coordinate of the starting point, in absolute coordinates.
     * @param y         The y coordinate of the starting point, in absolute coordinates.
     * @param width     The length of the line.
     * @param lineWidth The width of the line.
     * @param color     The color to use.
     * @param alpha     The alpha value to use (default=solid)
     */
    void drawHorizontalLine(int16_t x, int16_t y, uint16_t width, uint16_t lineWidth, colortype color, uint8_t alpha = 255);

    /**
     * @fn void LCD::drawVerticalLine(int16_t x, int16_t y, uint16_t height, uint16_t lineWidth, colortype color, uint8_t alpha = 255);
     *
     * @brief Draws a vertical line with the specified color.
     *
     *        Draws a vertical line with the specified color.
     *
     * @param x         The x coordinate of the starting point, in absolute coordinates.
     * @param y         The y coordinate of the starting point, in absolute coordinates.
     * @param height    The length of the line.
     * @param lineWidth The width of the line.
     * @param color     The color to use.
     * @param alpha     The alpha value to use (default=solid)
     */
    void drawVerticalLine(int16_t x, int16_t y, uint16_t height, uint16_t lineWidth, colortype color, uint8_t alpha = 255);

    /**
     * @fn void LCD::drawRect(const Rect& rect, colortype color, uint8_t alpha = 255);
     *
     * @brief Draws a rectangle using the specified line color.
     *
     *        Draws a rectangle using the specified line color. Same as calling drawBorder with
     *        a line width of 1.
     *
     * @param rect  The rectangle x, y, width, height in absolute coordinates.
     * @param color The color to use.
     * @param alpha The alpha value to use (default=solid)
     */
    void drawRect(const Rect& rect, colortype color, uint8_t alpha = 255);

    /**
     * @fn void LCD::drawBorder(const Rect& rect, uint16_t lineWidth, colortype color, uint8_t alpha = 255);
     *
     * @brief Draws a rectangle width the specified line width and color.
     *
     *        Draws a rectangle width the specified line width and color.
     *
     * @param rect      The rectangle x, y, width, height in absolute coordinates.
     * @param lineWidth The width of the line.
     * @param color     The color to use.
     * @param alpha     The alpha value to use (default=solid)
     */
    void drawBorder(const Rect& rect, uint16_t lineWidth, colortype color, uint8_t alpha = 255);

    /**
     * @struct StringVisuals LCD.hpp touchgfx/lcd/LCD.hpp
     *
     * @brief The visual elements when writing a string.
     *
     *        The visual elements when writing a string.
     */
    struct StringVisuals
    {
        const Font* font;              ///< The font to use.
        Alignment alignment;           ///< The alignment to use. Default is LEFT.
        TextDirection textDirection;   ///< The direction to use. Default is LTR
        TextRotation rotation;         ///< Orientation (rotation) of the text. Default is TEXT_ROTATE_0.
        colortype color;               ///< RGB color value. Default is 0 (black).
        int16_t linespace;             ///< Line space in pixels for multiline strings. Default is 0.
        uint8_t alpha;                 ///< 8-bit alpha value. Default is 255 (solid).
        uint8_t indentation;           ///< Indentation of text inside rectangle. Text will start this far from the left/right edge
        WideTextAction wideTextAction; ///< What to do with wide text lines

        /**
         * @fn StringVisuals()
         *
         * @brief Construct an empty StringVisuals object.
         *
         *        Construct an empty StringVisuals object.
         */
        StringVisuals()
            : font(0), alignment(LEFT), textDirection(TEXT_DIRECTION_LTR), rotation(TEXT_ROTATE_0), color(0), linespace(0), alpha(255), indentation(0), wideTextAction(WIDE_TEXT_NONE)
        {
        }

        /**
         * @fn StringVisuals(const Font* font, colortype color, uint8_t alpha, Alignment alignment, int16_t linespace, TextRotation rotation, TextDirection textDirection, uint8_t indentation, WideTextAction wideTextAction = WIDE_TEXT_NONE)
         *
         * @brief Construct a StringVisual object for rendering text.
         *
         * @param font           The Font with which to draw the text.
         * @param color          The color with which to draw the text.
         * @param alpha          Alpha blending. Default value is 255 (solid)
         * @param alignment      How to align the text.
         * @param linespace      Line space in pixels between each line, in case the text contains
         *                       newline characters.
         * @param rotation       How to rotate the text.
         * @param textDirection  The text direction.
         * @param indentation    The indentation of the text from the left and right of the text
         *                       area rectangle.
         * @param wideTextAction What to do with lines longer than the width of the TextArea.
         */
        StringVisuals(const Font* font, colortype color, uint8_t alpha, Alignment alignment, int16_t linespace, TextRotation rotation, TextDirection textDirection, uint8_t indentation, WideTextAction wideTextAction = WIDE_TEXT_NONE)
        {
            this->font = font;
            this->color = color;
            this->alpha = alpha;
            this->alignment = alignment;
            this->textDirection = textDirection;
            this->rotation = rotation;
            this->linespace = linespace;
            this->indentation = indentation;
            this->wideTextAction = wideTextAction;
        }
    };

    /**
     * @fn void LCD::drawString(Rect widgetArea, const Rect& invalidatedArea, const StringVisuals& stringVisuals, const Unicode::UnicodeChar* format, ...);
     *
     * @brief Draws the specified unicode string.
     *
     *        Draws the specified unicode string. Breaks line on newline.
     *
     * @param widgetArea      The area covered by the drawing widget in absolute coordinates.
     * @param invalidatedArea The (sub)region of the widget area to draw, expressed relative to
     *                        the widget area. If the widgetArea is (x, y, width, height) = (10,
     *                        10, 20, 20) and invalidatedArea is (x, y, width, height) = (5, 5,
     *                        6, 6) the widgetArea drawn on the LCD is (x, y, width, height) =
     *                        (15, 15, 6, 6).
     * @param stringVisuals   The string visuals (font, alignment, line space, color)
     *                        with which to draw this string.
     * @param format          A pointer to a zero terminated text string with optional
     *                        additional wildcard arguments.
     * @param ...             Variable arguments providing additional information.
     */
    void drawString(Rect widgetArea,
                    const Rect& invalidatedArea,
                    const StringVisuals& stringVisuals,
                    const Unicode::UnicodeChar* format,
                    ...);

    /**
     * @fn virtual uint8_t LCD::bitDepth() const = 0;
     *
     * @brief Number of bits per pixel used by the display.
     *
     *        Number of bits per pixel used by the display.
     *
     * @return The number of bits per pixel.
     */
    virtual uint8_t bitDepth() const = 0;

    /**
     * @fn virtual Bitmap::BitmapFormat LCD::framebufferFormat() const = 0;
     *
     * @brief Framebuffer format used by the display
     *
     *        Framebuffer format used by the display
     *
     * @return A Bitmap::BitmapFormat.
     */
    virtual Bitmap::BitmapFormat framebufferFormat() const = 0;

    /**
     * @fn virtual uint16_t LCD::framebufferStride() const = 0;
     *
     * @brief Framebuffer stride in bytes
     *
     *        Framebuffer stride in bytes. The distance (in bytes) from the start of one
     *        framebuffer row, to the next.
     *
     * @return The number of bytes in one framebuffer row.
     */
    virtual uint16_t framebufferStride() const = 0;

    /**
     * @fn virtual colortype LCD::getColorFrom24BitRGB(uint8_t red, uint8_t green, uint8_t blue) const = 0;
     *
     * @brief Generates a color representation to be used on the LCD, based on 24 bit RGB values.
     *        Depending on your chosen color bit depth, the color will be interpreted internally as
     *        either a 16 bit or 24 bit color value.
     *
     *        Generates a color representation to be used on the LCD, based on 24 bit RGB values.
     *        Depending on your chosen color bit depth, the color will be interpreted internally as
     *        either a 16 bit or 24 bit color value. This function can be safely used regardless of
     *        whether your application is configured for 16 or 24 bit colors.
     *
     * @param red   Value of the red part (0-255).
     * @param green Value of the green part (0-255).
     * @param blue  Value of the blue part (0-255).
     *
     * @return The color representation depending on LCD color format.
     */
    virtual colortype getColorFrom24BitRGB(uint8_t red, uint8_t green, uint8_t blue) const = 0;

    /**
     * @fn virtual uint8_t LCD::getRedColor(colortype color) const = 0;
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
    virtual uint8_t getRedColor(colortype color) const = 0;

    /**
     * @fn virtual uint8_t LCD::getGreenColor(colortype color) const = 0;
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
    virtual uint8_t getGreenColor(colortype color) const = 0;

    /**
     * @fn virtual uint8_t LCD::getBlueColor(colortype color) const = 0;
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
    virtual uint8_t getBlueColor(colortype color) const = 0;

    /**
     * @fn void LCD::setDefaultColor(colortype color)
     *
     * @brief Sets default color as used by alpha level only bitmap formats, e.g. A4.
     *
     *        Sets default color as used by alpha level only bitmap formats, e.g. A4. The
     *        default color, if no color is set, is black.
     *
     * @param color The color.
     *
     * @see getDefaultColor
     */
    void setDefaultColor(colortype color)
    {
        defaultColor = color;
    }

    /**
     * @fn colortype LCD::getDefaultColor() const
     *
     * @brief Gets default color previously set using setDefaultColor.
     *
     *        Gets default color previously set using setDefaultColor.
     *
     * @return The default color.
     *
     * @see setDefaultColor
     */
    colortype getDefaultColor() const
    {
        return defaultColor;
    }

    /**
     * @fn void LCD::drawTextureMapTriangle(const DrawingSurface& dest, const Point3D* vertices, const TextureSurface& texture, const Rect& absoluteRect, const Rect& dirtyAreaAbsolute, RenderingVariant renderVariant, uint8_t alpha = 255, uint16_t subDivisionSize = 12);
     *
     * @brief Texture map triangle. Draw a perspective correct texture mapped triangle. The
     *        vertices describes the surface, the x,y,z coordinates and the u,v coordinates of
     *        the texture. The texture contains the image data to be drawn The triangle line
     *        will be placed and clipped using the absolute and dirty rectangles The alpha will
     *        determine how the triangle should be alpha blended. The subDivisionSize will
     *        determine the size of the piecewise affine texture mapped portions of the
     *        triangle.
     *
     * @param dest              The description of where the texture is drawn - can be used to
     *                          issue a draw off screen.
     * @param vertices          The vertices of the triangle.
     * @param texture           The texture.
     * @param absoluteRect      The containing rectangle in absolute coordinates.
     * @param dirtyAreaAbsolute The dirty area in absolute coordinates.
     * @param renderVariant     The render variant - includes the algorithm and the pixel format.
     * @param alpha             the alpha. Default = 255.
     * @param subDivisionSize   the size of the subdivisions of the scan line. Default = 12.
     */
    void drawTextureMapTriangle(const DrawingSurface& dest,
                                const Point3D* vertices,
                                const TextureSurface& texture,
                                const Rect& absoluteRect,
                                const Rect& dirtyAreaAbsolute,
                                RenderingVariant renderVariant,
                                uint8_t alpha = 255,
                                uint16_t subDivisionSize = 12);

    /**
     * @fn FORCE_INLINE_FUNCTION static uint8_t LCD::div255(uint16_t num)
     *
     * @brief Approximates an integer division of a 16bit value by 255.
     *
     *        Divides numerator num (e.g. the sum resulting from an alpha-blending operation) by
     *        255.
     *
     * @param [in] num The numerator to divide by 255.
     *
     * @return The result of a division by 255.
     */
    FORCE_INLINE_FUNCTION static uint8_t div255(uint16_t num)
    {
        return (num + 1 + (num >> 8)) >> 8;
    }

    /**
     * @fn FORCE_INLINE_FUNCTION static uint32_t LCD::div255rb(uint32_t pixelxAlpha)
     *
     * @brief Divides the red and blue components of pixelxAlpha by 255.
     *
     *        Divides the red and blue components of pixelxAlpha by 255.
     *
     * @param [in] pixelxAlpha The red and blue components of a 32bit ARGB pixel multiplied by an
     *                         alpha factor.
     *
     * @return pixelxAlpha with its red and blue components divided by 255.
     */
    FORCE_INLINE_FUNCTION static uint32_t div255rb(uint32_t pixelxAlpha)
    {
        return ((pixelxAlpha + 0x10001 + ((pixelxAlpha >> 8) & 0xFF00FF)) >> 8) & 0xFF00FF;
    }

    /**
     * @fn FORCE_INLINE_FUNCTION static uint32_t LCD::div255g(uint32_t pixelxAlpha)
     *
     * @brief Divides the green component of pixelxAlpha by 255.
     *
     *        Divides the green component of pixelxAlpha by 255.
     *
     * @param [in] pixelxAlpha The green component of a 32bit ARGB pixel multiplied by an alpha
     *                         factor.
     *
     * @return pixelxAlpha with its green component divided by 255.
     */
    FORCE_INLINE_FUNCTION static uint32_t div255g(uint32_t pixelxAlpha)
    {
        return ((pixelxAlpha + 0x100 + (pixelxAlpha >> 8)) >> 8) & 0x00FF00;
    }

protected:
    static const uint16_t newLine = 10; ///< NewLine value.

    static colortype defaultColor; ///< Default Color to use when displaying transparency-only elements, e.g. A4 bitmaps

    /**
     * @class DrawTextureMapScanLineBase LCD.hpp touchgfx/lcd/LCD.hpp
     *
     * @brief Base class for drawing scanline by the texture mapper.
     *
     *        Base class for drawing scanline by the texture mapper.
     */
    class DrawTextureMapScanLineBase
    {
    public:
        /**
         * @fn virtual DrawTextureMapScanLineBase::~DrawTextureMapScanLineBase()
         *
         * @brief Default destructor
         */
        virtual ~DrawTextureMapScanLineBase()
        {
        }

        /**
         * @fn virtual void DrawTextureMapScanLineBase::drawTextureMapScanLineSubdivisions(int subdivisions, const int widthModLength, int pixelsToDraw, const int affineLength, float oneOverZRight, float UOverZRight, float VOverZRight, fixed16_16 U, fixed16_16 V, fixed16_16 deltaU, fixed16_16 deltaV, float ULeft, float VLeft, float URight, float VRight, float ZRight, const DrawingSurface& dest, const int destX, const int destY, const int16_t bitmapWidth, const int16_t bitmapHeight, const TextureSurface& texture, uint8_t alpha, const float dOneOverZdXAff, const float dUOverZdXAff, const float dVOverZdXAff) = 0;
         *
         * @brief Draw texture map scan line subdivisions
         *
         * @param subdivisions   The number of subdivisions.
         * @param widthModLength Remainder of length (after subdivisions).
         * @param pixelsToDraw   The pixels to draw.
         * @param affineLength   Length of one subdivision.
         * @param oneOverZRight  1/Z right.
         * @param UOverZRight    U/Z right.
         * @param VOverZRight    V/Z right.
         * @param U              U Coordinate in fixed16_16 notation.
         * @param V              V Coordinate in fixed16_16 notation.
         * @param deltaU         U delta to get to next pixel coordinate.
         * @param deltaV         V delta to get to next pixel coordinate.
         * @param ULeft          The left U.
         * @param VLeft          The left V.
         * @param URight         The right U.
         * @param VRight         The right V.
         * @param ZRight         The right Z.
         * @param dest           Destination drawing surface.
         * @param destX          Destination x coordinate.
         * @param destY          Destination y coordinate.
         * @param bitmapWidth    Width of the bitmap.
         * @param bitmapHeight   Height of the bitmap.
         * @param texture        The texture.
         * @param alpha          The global alpha.
         * @param dOneOverZdXAff 1/ZdX affine.
         * @param dUOverZdXAff   U/ZdX affine.
         * @param dVOverZdXAff   V/ZdX affine.
         */
        virtual void drawTextureMapScanLineSubdivisions(int subdivisions, const int widthModLength, int pixelsToDraw, const int affineLength, float oneOverZRight, float UOverZRight, float VOverZRight, fixed16_16 U, fixed16_16 V, fixed16_16 deltaU, fixed16_16 deltaV, float ULeft, float VLeft, float URight, float VRight, float ZRight, const DrawingSurface& dest, const int destX, const int destY, const int16_t bitmapWidth, const int16_t bitmapHeight, const TextureSurface& texture, uint8_t alpha, const float dOneOverZdXAff, const float dUOverZdXAff, const float dVOverZdXAff) = 0;

    protected:
        static const fixed16_16 half = 0x8000; ///< 1/2 in fixed16_16 format

        /**
         * @fn FORCE_INLINE_FUNCTION void DrawTextureMapScanLineBase::drawTextureMapNextSubdivision(float& ULeft, float& VLeft, float& ZRight, float& URight, float& VRight, float& oneOverZRight, const float dOneOverZdXAff, float& UOverZRight, const float dUOverZdXAff, float& VOverZRight, const float dVOverZdXAff, const int affineLength, fixed16_16& U, fixed16_16& V, fixed16_16& deltaU, fixed16_16& deltaV)
         *
         * @brief Draw texture map next subdivision
         *
         * @param [out]    ULeft          U left.
         * @param [out]    VLeft          V left.
         * @param [out]    ZRight         Z right.
         * @param [out]    URight         U right.
         * @param [out]    VRight         V right.
         * @param [in,out] oneOverZRight  1/Z right.
         * @param          dOneOverZdXAff d1/ZdX affine.
         * @param [in,out] UOverZRight    U/Z right.
         * @param          dUOverZdXAff   dU/ZdX affine.
         * @param [in,out] VOverZRight    V/Z right.
         * @param          dVOverZdXAff   dV/ZdX affine.
         * @param          affineLength   Length of the affine.
         * @param [out]    U              Bitmap X in fixed16_16.
         * @param [out]    V              Bitmap Y in fixed16_16.
         * @param [out]    deltaU         U delta.
         * @param [out]    deltaV         V delta.
         */
        FORCE_INLINE_FUNCTION void drawTextureMapNextSubdivision(float& ULeft, float& VLeft, float& ZRight, float& URight, float& VRight, float& oneOverZRight, const float dOneOverZdXAff, float& UOverZRight, const float dUOverZdXAff, float& VOverZRight, const float dVOverZdXAff, const int affineLength, fixed16_16& U, fixed16_16& V, fixed16_16& deltaU, fixed16_16& deltaV)
        {
            ULeft = URight;
            VLeft = VRight;

            oneOverZRight += dOneOverZdXAff;
            UOverZRight += dUOverZdXAff;
            VOverZRight += dVOverZdXAff;

            ZRight = 1 / oneOverZRight;
            URight = ZRight * UOverZRight;
            VRight = ZRight * VOverZRight;

            U = floatToFixed16_16(ULeft);
            V = floatToFixed16_16(VLeft);
            deltaU = floatToFixed16_16(URight - ULeft) / affineLength;
            deltaV = floatToFixed16_16(VRight - VLeft) / affineLength;
        }

        /**
         * @fn FORCE_INLINE_FUNCTION bool DrawTextureMapScanLineBase::is1Inside(int value, int limit)
         *
         * @brief Check if value is inside [0..limit[
         *
         *        Check if value is inside [0..limit[
         *
         * @param [in] value Value to check.
         * @param [in] limit Upper limit.
         *
         * @return true if value is inside given limit.
         */
        FORCE_INLINE_FUNCTION bool is1Inside(int value, int limit)
        {
            return (value >= 0 && value < limit);
        }

        /**
         * @fn FORCE_INLINE_FUNCTION bool DrawTextureMapScanLineBase::is1x1Inside(int x, int y, int width, int height)
         *
         * @brief Check if (x,y) is inside ([0..width[, [0..height[)
         *
         *        Check if (x,y) is inside ([0..width[, [0..height[)
         *
         * @param [in] x      X coordinate.
         * @param [in] y      Y coordinate.
         * @param [in] width  X limit.
         * @param [in] height Y limit.
         *
         * @return true if (x,y) is inside given limits.
         */
        FORCE_INLINE_FUNCTION bool is1x1Inside(int x, int y, int width, int height)
        {
            return is1Inside(x, width) && is1Inside(y, height);
        }

        /**
         * @fn FORCE_INLINE_FUNCTION bool DrawTextureMapScanLineBase::is2Inside(int value, int limit)
         *
         * @brief Check if both value and value+1 are inside [0..limit[
         *
         *        Check if both value and value+1 are inside [0..limit[
         *
         * @param [in] value Value to check.
         * @param [in] limit Upper limit.
         *
         * @return true if value and value+1 are inside given limit.
         */
        FORCE_INLINE_FUNCTION bool is2Inside(int value, int limit)
        {
            return (value >= 0 && value + 1 < limit);
        }

        /**
         * @fn FORCE_INLINE_FUNCTION bool DrawTextureMapScanLineBase::is2x2Inside(int x, int y, int width, int height)
         *
         * @brief Check if both (x,y) and (x+1,y+1) are inside ([0..width[,[0..height[)
         *
         *        Check if both (x,y) and (x+1,y+1) are inside ([0..width[,[0..height[)
         *
         * @param [in] x      X coordinate.
         * @param [in] y      Y coordinate.
         * @param [in] width  X limit.
         * @param [in] height Y limit.
         *
         * @return true if (x,y) and (x+1,y+1) are inside given limits.
         */
        FORCE_INLINE_FUNCTION bool is2x2Inside(int x, int y, int width, int height)
        {
            return is2Inside(x, width) && is2Inside(y, height);
        }

        /**
         * @fn FORCE_INLINE_FUNCTION bool DrawTextureMapScanLineBase::is2PartiallyInside(int value, int limit)
         *
         * @brief Check if either value or value+1 is inside [0..limit[
         *
         *        Check if either value or value+1 is inside [0..limit[
         *
         * @param [in] value Value to check.
         * @param [in] limit Upper limit.
         *
         * @return true if either value or value+1 is inside given limit.
         */
        FORCE_INLINE_FUNCTION bool is2PartiallyInside(int value, int limit)
        {
            return (value >= -1 && value < limit);
        }

        /**
         * @fn FORCE_INLINE_FUNCTION bool DrawTextureMapScanLineBase::is2x2PartiallyInside(int x, int y, int width, int height)
         *
         * @brief Check if either (x,y) or (x+1,y+1) is inside ([0..width[,[0..height[)
         *
         *        Check if either (x,y) or (x+1,y+1) is inside ([0..width[,[0..height[)
         *
         * @param [in] x      X coordinate.
         * @param [in] y      Y coordinate.
         * @param [in] width  X limit.
         * @param [in] height Y limit.
         *
         * @return true if either (x,y) or (x+1,y+1) is inside given limits.
         */
        FORCE_INLINE_FUNCTION bool is2x2PartiallyInside(int x, int y, int width, int height)
        {
            return is2PartiallyInside(x, width) && is2PartiallyInside(y, height);
        }
    };

    /**
     * @fn virtual DrawTextureMapScanLineBase* LCD::getTextureMapperDrawScanLine(const TextureSurface& texture, RenderingVariant renderVariant, uint8_t alpha);
     *
     * @brief Gets pointer to object that can draw a scan line.
     *
     *        Gets pointer to object that can draw a scan line which allows for highly specialized and optimized implementation.
     *
     * @param texture       The texture Surface.
     * @param renderVariant The render variant.
     * @param alpha         The global alpha.
     *
     * @return Null if it fails, else the pointer to the texture mapper draw scan line object.
     */
    virtual DrawTextureMapScanLineBase* getTextureMapperDrawScanLine(const TextureSurface& texture, RenderingVariant renderVariant, uint8_t alpha);

    /**
     * @fn virtual void LCD::drawTextureMapScanLine(const DrawingSurface& dest, const Gradients& gradients, const Edge* leftEdge, const Edge* rightEdge, const TextureSurface& texture, const Rect& absoluteRect, const Rect& dirtyAreaAbsolute, RenderingVariant renderVariant, uint8_t alpha, uint16_t subDivisionSize);
     *
     * @brief Draw scan line. Draw one horizontal line of the texture map on screen. The scan line
     *        will be drawn using perspective correct texture mapping. The appearance of the
     *        line is determined by the left and right edge and the gradients structure. The
     *        edges contain the information about the x,y,z coordinates of the left and right
     *        side respectively and also information about the u,v coordinates of the texture
     *        map used. The gradients structure contains information about how to interpolate
     *        all the values across the scan line. The data drawn should be present in the
     *        texture argument.
     *
     *        The scan line will be drawn using the additional arguments. The scan line will be
     *        placed and clipped using the absolute and dirty rectangles The alpha will
     *        determine how the scan line should be alpha blended. The subDivisionSize will
     *        determine the size of the piecewise affine texture mapped lines.
     *
     * @param dest              The description of where the texture is drawn - can be used to
     *                          issue a draw off screen.
     * @param gradients         The gradients using in interpolation across the scan line.
     * @param leftEdge          The left edge of the scan line.
     * @param rightEdge         The right edge of the scan line.
     * @param texture           The texture.
     * @param absoluteRect      The containing rectangle in absolute coordinates.
     * @param dirtyAreaAbsolute The dirty area in absolute coordinates.
     * @param renderVariant     The render variant - includes the algorithm and the pixel format.
     * @param alpha             The alpha.
     * @param subDivisionSize   The size of the subdivisions of the scan line. A value of 1 will
     *                          give a completely perspective correct texture mapped scan line. A
     *                          large value will give an affine texture mapped scan line.
     */
    virtual void drawTextureMapScanLine(const DrawingSurface& dest, const Gradients& gradients, const Edge* leftEdge, const Edge* rightEdge, const TextureSurface& texture, const Rect& absoluteRect, const Rect& dirtyAreaAbsolute, RenderingVariant renderVariant, uint8_t alpha, uint16_t subDivisionSize);

    /**
     * @fn virtual void LCD::drawGlyph(uint16_t* wbuf, Rect widgetArea, int16_t x, int16_t y, uint16_t offsetX, uint16_t offsetY, const Rect& invalidatedArea, const GlyphNode* glyph, const uint8_t* glyphData, uint8_t dataFormatA4, colortype color, uint8_t bitsPerPixel, uint8_t alpha, TextRotation rotation) = 0;
     *
     * @brief Private version of draw-glyph.
     *
     *        Private version of draw-glyph with explicit destination buffer pointer argument.
     *        For all parameters (except the buffer pointer) see the public function drawString().
     *
     * @param [out] wbuf      The destination (frame) buffer to draw to.
     * @param widgetArea      The canvas to draw the glyph inside.
     * @param x               Horizontal offset to start drawing the glyph.
     * @param y               Vertical offset to start drawing the glyph.
     * @param offsetX         Horizontal offset in the glyph to start drawing from.
     * @param offsetY         Vertical offset in the glyph to start drawing from.
     * @param invalidatedArea The area to draw inside.
     * @param glyph           Specifications of the glyph to draw.
     * @param glyphData       Data containing the actual glyph (dense format)
     * @param dataFormatA4    The glyph is saved using ST A4 format.
     * @param color           The color of the glyph.
     * @param bitsPerPixel    Bit depth of the glyph.
     * @param alpha           The transparency of the glyph.
     * @param rotation        Rotation to do before drawing the glyph.
     */
    virtual void drawGlyph(uint16_t* wbuf, Rect widgetArea, int16_t x, int16_t y, uint16_t offsetX, uint16_t offsetY, const Rect& invalidatedArea, const GlyphNode* glyph, const uint8_t* glyphData, uint8_t dataFormatA4, colortype color, uint8_t bitsPerPixel, uint8_t alpha, TextRotation rotation) = 0;

    /**
     * @fn static void LCD::rotateRect(Rect& rect, const Rect& canvas, const TextRotation rotation);
     *
     * @brief Rotate a rectangle inside another rectangle.
     *
     *        Rotate a rectangle inside another rectangle.
     *
     * @param [in,out] rect The rectangle to rotate.
     * @param canvas        The rectangle containing the rect to rotate.
     * @param rotation      Rotation to perform on rect.
     */
    static void rotateRect(Rect& rect, const Rect& canvas, const TextRotation rotation);

    /**
     * @fn static int LCD::realX(const Rect& widgetArea, int16_t x, int16_t y, TextRotation rotation);
     *
     * @brief Find the real, absolute x coordinate of a point inside a widget.
     *
     *        Find the real, absolute x coordinate of a point inside a widget with regards to
     *        rotation.
     *
     * @param [in] widgetArea The widget containing the point.
     * @param x               The x coordinate.
     * @param y               The y coordinate.
     * @param rotation        Rotation to perform.
     *
     * @return The absolute x coordinate after applying appropriate rotation.
     */
    static int realX(const Rect& widgetArea, int16_t x, int16_t y, TextRotation rotation);

    /**
     * @fn static int LCD::realY(const Rect& widgetArea, int16_t x, int16_t y, TextRotation rotation);
     *
     * @brief Find the real, absolute y coordinate of a point inside a widget.
     *
     *        Find the real, absolute y coordinate of a point inside a widget with regards to
     *        rotation.
     *
     * @param [in] widgetArea The widget containing the point.
     * @param x               The x coordinate.
     * @param y               The y coordinate.
     * @param rotation        Rotation to perform.
     *
     * @return The absolute y coordinate after applying appropriate rotation.
     */
    static int realY(const Rect& widgetArea, int16_t x, int16_t y, TextRotation rotation);

    /**
     * @fn void LCD::drawStringLTR(Rect widgetArea, const Rect& invalidatedArea, const StringVisuals& visuals, const Unicode::UnicodeChar* format, va_list pArg);
     *
     * @brief Draws the specified unicode string.
     *
     *        Draws the specified unicode string. Breaks line on newline. The string is assumed
     *        to contain only latin characters written left-to-right.
     *
     * @param widgetArea      The area covered by the drawing widget in absolute coordinates.
     * @param invalidatedArea The (sub)region of the widget area to draw, expressed relative to the
     *                        widget area. If the widgetArea is (x, y, width, height) = (10, 10,
     *                        20, 20) and invalidatedArea is (x, y, width, height) = (5, 5, 6,
     *                        6) the widgetArea drawn on the LCD is (x, y, width, height) = (15,
     *                        15, 6, 6).
     * @param [in] visuals    The string visuals (font, alignment, line space, color)
     *                        with which to draw this string.
     * @param format          A pointer to a zero terminated text string with optional additional
     *                        wildcard arguments.
     * @param pArg            Variable arguments providing additional information.
     *
     * @see drawString
     */
    void drawStringLTR(const Rect& widgetArea,
                       const Rect& invalidatedArea,
                       const StringVisuals& visuals,
                       const Unicode::UnicodeChar* format,
                       va_list pArg);

    /**
     * @fn void LCD::drawStringRTL(Rect widgetArea, const Rect& invalidatedArea, const StringVisuals& visuals, const Unicode::UnicodeChar* format, va_list pArg);
     *
     * @brief Draws the specified unicode string.
     *
     *        Draws the specified unicode string. Breaks line on newline. The string can be
     *        either right-to-left or left-to-right and may contain sequences of Arabic /Hebrew
     *        and Latin characters.
     *
     * @param widgetArea      The area covered by the drawing widget in absolute coordinates.
     * @param invalidatedArea The (sub)region of the widget area to draw, expressed relative to the
     *                        widget area. If the widgetArea is (x, y, width, height) = (10, 10,
     *                        20, 20) and invalidatedArea is (x, y, width, height) = (5, 5, 6,
     *                        6) the widgetArea drawn on the LCD is (x, y, width, height) = (15,
     *                        15, 6, 6).
     * @param [in] visuals    The string visuals (font, alignment, line space, color)
     *                        with which to draw this string.
     * @param format          A pointer to a zero terminated text string with optional additional
     *                        wildcard arguments.
     * @param pArg            Variable arguments providing additional information.
     *
     * @see drawString
     */
    void drawStringRTL(const Rect& widgetArea,
                       const Rect& invalidatedArea,
                       const StringVisuals& visuals,
                       const Unicode::UnicodeChar* format,
                       va_list pArg);

    /**
     * @fn static uint16_t LCD::stringWidth(TextProvider& textProvider, const Font& font, const int numChars, TextDirection textDirection);
     *
     * @brief Find string width.
     *
     *        Find string with of the given number of ligatures read from the given
     *        TextProvider. After the introduction of Arabic, Thai, Hindi and other
     *        languages, ligatures are counted instead of characters. For Latin
     *        languages, number of characters equal number of ligatures.
     *
     * @param [in,out] textProvider The text provider.
     * @param font                  The font.
     * @param numChars              Number of characters (ligatures).
     * @param textDirection         The text direction.
     *
     * @return An int16_t.
     */
    static uint16_t stringWidth(TextProvider& textProvider, const Font& font, const int numChars, TextDirection textDirection);

    /**
     * @fn static uint16_t LCD::getNumLines(TextProvider& textProvider, WideTextAction wideTextAction, TextDirection textDirection, const Font* font, int16_t width);
     *
     * @brief Gets number lines.
     *
     *        Gets number of lines for a given text taking word wrap into consideration. The
     *        font and width are required to find the number of lines in case word wrap is true.
     *
     * @param [in] textProvider The text provider.
     * @param wideTextAction    The wide text action in case lines are longer than the width of the text area.
     * @param textDirection     The text direction (LTR or RTL).
     * @param font              The font.
     * @param width             The width.
     *
     * @return The number lines.
     */
    static uint16_t getNumLines(TextProvider& textProvider, WideTextAction wideTextAction, TextDirection textDirection, const Font* font, int16_t width);

    friend class Font;
    friend class TextArea;
    friend class TextAreaWithWildcardBase;

    /**
     * @fn FORCE_INLINE_FUNCTION static uint8_t LCD::getAlphaFromA4(const uint16_t* data, uint32_t offset)
     *
     * @brief Gets alpha from A4 image at given offset
     *
     *        Gets alpha from A4 image at given offset. The value is scaled up from range 0-15
     *        to 0-255.
     *
     * @param data   A pointer to the start of the A4 data.
     * @param offset The offset into the A4 image.
     *
     * @return The alpha from A4 (0-255).
     */
    FORCE_INLINE_FUNCTION static uint8_t getAlphaFromA4(const uint16_t* data, uint32_t offset)
    {
        uint8_t byte = reinterpret_cast<const uint8_t*>(data)[offset / 2];
        return ((offset & 1) == 0 ? byte & 0xF : byte >> 4) * 0x11;
    }

private:
    DrawTextureMapScanLineBase* textureMapperClass; ///< Used during faster TextureMapper rendering
    typedef void (LCD::*DrawStringFunctionPointer)(const Rect& widgetArea, const Rect& invalidatedArea, const StringVisuals& stringVisuals, const Unicode::UnicodeChar* format, va_list _pArg);
    static DrawStringFunctionPointer drawStringFunction; ///< The draw string function, either LTR or RTL

    class DrawStringInternalStruct
    {
    public:
        uint16_t* frameBuffer;
        const Rect* widgetArea;
        int16_t widgetRectY;
        const Rect* toDraw;
        const StringVisuals* stringVisuals;
        TextProvider* drawTextProvider;

        DrawStringInternalStruct()
            : frameBuffer(0), widgetArea(0), widgetRectY(0), toDraw(0), stringVisuals(0), drawTextProvider(0)
        {
        }
    };
    typedef void (LCD::*DrawStringInternalFunctionPointer)(int16_t& offset, const Font* font, const TextDirection textDirection, TextProvider& widthTextProvider, const int numChars, const bool useEllipsis, DrawStringInternalStruct const* data);
    bool drawStringRTLLine(int16_t& offset, const Font* font, TextDirection textDirection, Unicode::UnicodeChar& currChar, TextProvider& textProvider, TextProvider& widthTextProvider, DrawStringInternalFunctionPointer internalFunction, const int numChars, const bool useEllipsis, DrawStringInternalStruct const* data);
    void drawStringWidthInternal(int16_t& offset, const Font* font, const TextDirection textDirection, TextProvider& textProvider, const int numChars, const bool useEllipsis, DrawStringInternalStruct const* data);
    void drawStringRTLInternal(int16_t& offset, const Font* font, const TextDirection textDirection, TextProvider& widthTextProvider, const int numChars, const bool useEllipsis, DrawStringInternalStruct const* data);
    bool drawStringInternal(uint16_t* frameBuffer, Rect const* widgetArea, int16_t widgetRectY, int16_t& offset, const Rect& invalidatedArea, StringVisuals const* stringVisuals, const TextDirection textDirection, TextProvider& textProvider, const int numChars, bool useEllipsis);

    class WideTextInternalStruct
    {
    public:
        WideTextInternalStruct(TextProvider& _textProvider, uint16_t _maxWidth, TextDirection _textDirection, const Font* _font, WideTextAction action)
            : currChar(0), textProvider(_textProvider), textDirection(_textDirection), wideTextAction(action), font(_font), maxWidth(_maxWidth), charsRead(0), width(0), charsReadAhead(0), widthAhead(0), widthWithoutWhiteSpaceAtEnd(0), ellipsisGlyphWidth(0), useEllipsis(false)
        {
            Unicode::UnicodeChar ellipsisChar = font->getEllipsisChar();
            if (ellipsisChar != 0)
            {
                const GlyphNode* ellipsisGlyph = font->getGlyph(ellipsisChar);
                ellipsisGlyphWidth = ellipsisGlyph->advance();
                if (wideTextAction == WIDE_TEXT_CHARWRAP_DOUBLE_ELLIPSIS)
                {
                    ellipsisGlyphWidth += font->getKerning(ellipsisChar, ellipsisGlyph) + ellipsisGlyph->advance();
                }
            }
        }
        void addWord(uint16_t widthBeforeCurrChar, uint16_t widthBeforeWhiteSpaceAtEnd, uint16_t charsReadTooMany);
        void getStringLengthForLine(bool useWideTextEllipsisFlag);
        bool isSpace(Unicode::UnicodeChar ch)
        {
            return ch == ' ' || ch == 0x200B;
        }
        Unicode::UnicodeChar getCurrChar() const
        {
            return currChar;
        }
        uint16_t getLineWidth() const
        {
            return widthWithoutWhiteSpaceAtEnd;
        }
        uint16_t getCharsRead() const
        {
            return charsRead;
        }
        bool getUseEllipsis() const
        {
            return useEllipsis;
        }

    private:
        Unicode::UnicodeChar currChar;
        TextProvider& textProvider;
        TextDirection textDirection;
        WideTextAction wideTextAction;
        const Font* font;
        uint16_t maxWidth;
        uint16_t charsRead;
        uint16_t width;
        uint16_t charsReadAhead;
        uint16_t widthAhead;
        uint16_t widthWithoutWhiteSpaceAtEnd;
        uint16_t ellipsisGlyphWidth;
        bool useEllipsis;
    };
};

/**
 * @class DebugPrinter LCD.hpp touchgfx/lcd/LCD.hpp
 *
 * @brief The class DebugPrinter defines the interface for printing debug messages on top of the framebuffer.
 *
 *        The class DebugPrinter defines the interface for printing debug messages on top of the framebuffer.
 */
class DebugPrinter
{
public:
    DebugPrinter()
        : debugString(0), debugRegion(Rect(0, 0, 0, 0)), debugForegroundColor(colortype(0xffffffff)), debugScale(1)
    {
    }

    virtual ~DebugPrinter()
    {
    }

    /**
     * @fn void setString(const char* string);
     *
     * @brief Sets the debug string to be displayed on top of the framebuffer.
     *
     *        Sets the debug string to be displayed on top of the framebuffer.
     *
     * @param [in] string The string to be displayed.
     */
    void setString(const char* string)
    {
        debugString = string;
    }

    /**
     * @fn void setPosition(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
     *
     * @brief Sets the position of the debug string.
     *
     *        Sets the position onscreen where the debug string will be displayed.
     *
     * @param [in] x The coordinate of the region where the debug string is displayed.
     * @param [in] y The coordinate of the region where the debug string is displayed.
     * @param [in] w The width of the region where the debug string is displayed.
     * @param [in] h The height of the region where the debug string is displayed.
     */
    void setPosition(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
    {
        debugRegion = Rect(x, y, w, h);
    }

    /**
     * @fn void setScale(uint8_t scale);
     *
     * @brief Sets the font scale of the debug string.
     *
     *        Sets the font scale of the debug string.
     *
     * @param [in] scale The font scale of the debug string.
     */
    void setScale(uint8_t scale)
    {
        if (!scale)
        {
            scale = 1;
        }

        debugScale = scale;
    }

    /**
     * @fn void setColor(colortype fg);
     *
     * @brief Sets the foreground color of the debug string.
     *
     *        Sets the foreground color of the debug string.
     *
     * @param [in] fg The foreground color of the debug string.
     */
    void setColor(colortype fg)
    {
        debugForegroundColor = fg;
    }

    /**
     * @fn virtual void draw(const Rect& rect) const = 0;
     *
     * @brief Draws the debug string on top of the framebuffer content.
     *
     *        Draws the debug string on top of the framebuffer content.
     *
     * @param [in] rect The rect to draw inside.
     */
    virtual void draw(const Rect& rect) const = 0;

    /**
     * @fn const Rect& getRegion();
     *
     * @brief Returns the region of the debug string.
     *
     *        Returns the region where the debug string is displayed.
     *
     * @return Rect The debug string region.
     */
    const Rect& getRegion() const
    {
        return debugRegion;
    }

protected:
    /**
     * @fn uint16_t DebugPrinter::getGlyph(uint8_t c) const
     *
     * @brief Gets a glyph
     *
     *        Gets a glyph (15 bits) arranged with 3 bits wide, 5 bits high in a single
     *        uint16_t value
     *
     * @param c The character to get a glyph for.
     *
     * @return The glyph.
     */
    uint16_t getGlyph(uint8_t c) const
    {
        static const uint16_t builtin_debug_font[] =
        {
            000000, 022202, 055000, 057575, 026532, 051245, 025253, 022000,
            012221, 042224, 005250, 002720, 000024, 000700, 000002, 011244,
            025752, 026222, 061247, 061216, 045571, 074616, 034652, 071222,
            025252, 025312, 002020, 002024, 012421, 007070, 042124, 061202,
            025543, 025755, 065656, 034443, 065556, 074647, 074644, 034553,
            055755, 072227, 011152, 055655, 044447, 057555, 015754, 025552,
            065644, 025573, 065655, 034216, 072222, 055557, 055522, 055575,
            055255, 055222, 071247, 032223, 044211, 062226, 025000, 000007,
            042000, 003553, 046556, 003443, 013553, 002743, 012722, 002716,
            046555, 020627, 010316, 045655, 062227, 006777, 006555, 002552,
            006564, 003531, 006544, 003636, 022721, 005553, 005522, 005575,
            005255, 005316, 007247, 032623, 022222, 062326, 063000, 077777
        };

        if (c < ' ' || c > '~')
        {
            c = 0x7F;
        }
        return builtin_debug_font[c - ' '];
    }

    const char* debugString;        ///< Debug string to be displayed onscreen.
    Rect debugRegion;               ///< Region onscreen where the debug message is displayed.
    colortype debugForegroundColor; ///< Font color to use when displaying the debug string.
    uint8_t debugScale;             ///< Font scaling factor to use when displaying the debug string.
};
} // namespace touchgfx

#endif // LCD_HPP
