#pragma once

#define SPI_DRIVER SPID0
#define SPI_SCK_PIN GP2
#define SPI_MOSI_PIN GP3
#define SPI_MISO_PIN NO_PIN

#define EPD_BUSY_PIN    GP27
#define EPD_RST_PIN     GP26
#define EPD_DC_PIN      GP0
//#define EPD_CS_PIN      GP1
// EPD_CS_PIN を NO_PIN にする場合、mcuconf.h で #define SPI_SELECT_MODE SPI_SELECT_MODE_NONE とすること
#define EPD_CS_PIN      NO_PIN
#define EPD_SCK_PIN     SPI_SCK_PIN
#define EPD_MOSI_PIN    SPI_MOSI_PIN

// RP2040のペリフェラルクロックは125MHz
// Waveshare e-paperのSPIクロックは20Hz
// SPI DIVISORは2のべき乗でないとダメ
// 125/20 = 6.25 であり直近の2のべき乗は8となり、そのときのSPIクロックは15.625である。
// しかしSPI DIVISORが8だとデータ化けが起きるらしく、16へ変更して様子をみることにした。
#define EPD_SPI_DIVISOR 16

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET // Activates the double-tap behavior
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1000U // Timeout window in ms in which the double tap can occur.
