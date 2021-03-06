// 4.13.0 dither_algorithm=2 alpha_dither=yes layout_rotation=0 opaque_image_format=RGB888 non_opaque_image_format=ARGB8888 section=ExtFlashSection extra_section=ExtFlashSection generate_png=no 0x179d6fd1
// Generated by imageconverter. Please, do not edit!

#include <BitmapDatabase.hpp>
#include <touchgfx/Bitmap.hpp>
#include <touchgfx/lcd/LCD.hpp>
#include <platform/driver/lcd/LCD24bpp.hpp>

extern const unsigned char _background[]; // BITMAP_BACKGROUND_ID = 0, Size: 480x272 pixels
extern const unsigned char _blue_progressindicators_bg_large_circle_indicator_bg_line_half[]; // BITMAP_BLUE_PROGRESSINDICATORS_BG_LARGE_CIRCLE_INDICATOR_BG_LINE_HALF_ID = 1, Size: 184x94 pixels

const touchgfx::Bitmap::BitmapData bitmap_database[] =
{
    { _background, 0, 480, 272, 0, 0, 480, (uint8_t)(touchgfx::Bitmap::RGB888) >> 3, 272, (uint8_t)(touchgfx::Bitmap::RGB888) & 0x7 },
    { _blue_progressindicators_bg_large_circle_indicator_bg_line_half, 0, 184, 94, 62, 5, 60, (uint8_t)(touchgfx::Bitmap::ARGB8888) >> 3, 14, (uint8_t)(touchgfx::Bitmap::ARGB8888) & 0x7 }
};

namespace BitmapDatabase
{
const touchgfx::Bitmap::BitmapData* getInstance()
{
    return bitmap_database;
}

uint16_t getInstanceSize()
{
    return (uint16_t)(sizeof(bitmap_database) / sizeof(touchgfx::Bitmap::BitmapData));
}
}
