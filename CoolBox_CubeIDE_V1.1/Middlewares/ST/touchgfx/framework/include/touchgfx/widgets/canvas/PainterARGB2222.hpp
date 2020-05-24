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

#ifndef PAINTERARGB2222_HPP
#define PAINTERARGB2222_HPP

#include <stdint.h>
#include <touchgfx/widgets/canvas/AbstractPainterARGB2222.hpp>
#include <touchgfx/hal/Types.hpp>

namespace touchgfx
{
/**
 * @class PainterARGB2222 PainterARGB2222.hpp touchgfx/widgets/canvas/PainterARGB2222.hpp
 *
 * @brief A Painter that will paint using a color and an alpha value.
 *
 *        The PainterARGB2222 class allows a shape to be filled with a given color and alpha
 *        value. This allows transparent, anti-aliased elements to be drawn.
 *
 * @see AbstractPainter
 */
class PainterARGB2222 : public AbstractPainterARGB2222
{
public:
    /**
     * @fn PainterARGB2222::PainterARGB2222(colortype color = 0, uint8_t alpha = 255);
     *
     * @brief Constructor.
     *
     *        Constructor.
     *
     * @param color the color.
     * @param alpha the alpha.
     */
    PainterARGB2222(colortype color = 0, uint8_t alpha = 255);

    /**
     * @fn void PainterARGB2222::setColor(colortype color, uint8_t alpha = 255);
     *
     * @brief Sets color and alpha to use when drawing the CanvasWidget.
     *
     *        Sets color and alpha to use when drawing the CanvasWidget.
     *
     * @param color The color.
     * @param alpha The alpha.
     */
    void setColor(colortype color, uint8_t alpha = 255);

    /**
     * @fn colortype PainterARGB2222::getColor() const;
     *
     * @brief Gets the current color.
     *
     *        Gets the current color.
     *
     * @return The color.
     */
    colortype getColor() const;

    /**
     * @fn void PainterARGB2222::setAlpha(uint8_t alpha);
     *
     * @brief Sets an alpha value for the painter.
     *
     *        Sets an alpha value for the painter.
     *
     * @param alpha The alpha value to use.
     */
    void setAlpha(uint8_t alpha);

    /**
     * @fn uint8_t PainterARGB2222::getAlpha() const;
     *
     * @brief Gets the current alpha value.
     *
     *        Gets the current alpha value.
     *
     * @return The current alpha value.
     *
     * @see setAlpha
     */
    uint8_t getAlpha() const;

    virtual void render(uint8_t* ptr, int x, int xAdjust, int y, unsigned count, const uint8_t* covers);

protected:
    virtual bool renderNext(uint8_t& red, uint8_t& green, uint8_t& blue, uint8_t& alpha);

    uint8_t painterColor;   ///< The color
    uint8_t painterRed;     ///< The red part of the color, scaled up to [0..255]
    uint8_t painterGreen;   ///< The green part of the color, scaled up to [0..255]
    uint8_t painterBlue;    ///< The blue part of the color, scaled up to [0..255]
    uint8_t  painterAlpha;  ///< The alpha value
}; // class PainterARGB2222
} // namespace touchgfx

#endif // PAINTERARGB2222_HPP
