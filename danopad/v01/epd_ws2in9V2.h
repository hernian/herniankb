#pragma once

#include <stdint.h>


#define EPD_WIDTH   128
#define EPD_HEIGHT  296
#define COUNT_BYTES_IN_LINE ((EPD_WIDTH + 7) / 8)
#define COUNT_BYTES_IN_IMAGE (EPD_HEIGHT * COUNT_BYTES_IN_LINE)


void epd_display_image_partial(const uint8_t* image);

void epd_task_init(const uint8_t* image);
void epd_task(void);

void epd_test(void);
