// Waveshare 12956
// /296x128, 2.9inch E-Ink display module driver
#include QMK_KEYBOARD_H
#include "epd_ws2in9V2.h"
#include "spi_master.h"
#include "hal.h"
#include "generated/img_296_blank.h"
//#include "generated/img_296_pat1.h"
//#include "generated/img_296_pat2.h"
//#include "generated/img_296_pat3.h"


const uint32_t MS_DELAY_INIT = 1000;
const uint32_t MS_HW_RESET_LOW = 1;
const uint32_t MS_HW_RESET_HIGH_POST = 2;
const uint32_t MS_DEEP_SLEEP_DELAY = 100;
const uint32_t MS_ENTER_DEEP_SLEEP_AFTER = 5000;


#if 0
static const uint8_t WS_20_30[159] =
{
0x80,	0x66,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x40,	0x0,	0x0,	0x0,
0x10,	0x66,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x20,	0x0,	0x0,	0x0,
0x80,	0x66,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x40,	0x0,	0x0,	0x0,
0x10,	0x66,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x20,	0x0,	0x0,	0x0,
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
0x14,	0x8,	0x0,	0x0,	0x0,	0x0,	0x1,
0xA,	0xA,	0x0,	0xA,	0xA,	0x0,	0x1,
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
0x14,	0x8,	0x0,	0x1,	0x0,	0x0,	0x1,
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x1,
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
0x44,	0x44,	0x44,	0x44,	0x44,	0x44,	0x0,	0x0,	0x0,
0x22,	0x17,	0x41,	0x0,	0x32,	0x36
};
#endif

#if 1
static const uint8_t WF_FULL[159] =
{
0x90,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	//VS L0	1.00S
0x60,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	//VS L1
0x90,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	//VS L2
0x60,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	//VS L3
0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	//VS L4
0x19,	0x19,	0x00,	0x00,	0x00,	0x00,	0x00,						//TP, SR, RP of Group0
0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,						//TP, SR, RP of Group1
0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,						//TP, SR, RP of Group2
0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,						//TP, SR, RP of Group3
0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,						//TP, SR, RP of Group4
0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,						//TP, SR, RP of Group5
0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,						//TP, SR, RP of Group6
0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,						//TP, SR, RP of Group7
0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,						//TP, SR, RP of Group8
0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,						//TP, SR, RP of Group9
0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,						//TP, SR, RP of Group10
0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,						//TP, SR, RP of Group11
0x24,	0x42,	0x22,	0x22,	0x23,	0x32,	0x00,	0x00,	0x00,				//FR, XON
0x22,	0x17,	0x41,	0xAE,	0x32,	0x38,							//EOPT VGH VSH1 VSH2 VSL VCOM
};
#endif
#if 1
static const uint8_t WF_PARTIAL_2IN9[159] =
{
0x0,0x40,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x80,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x40,0x40,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0A,0x0,0x0,0x0,0x0,0x0,0x1,
0x1,0x0,0x0,0x0,0x0,0x0,0x0,
0x1,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x22,0x22,0x22,0x22,0x22,0x22,0x0,0x0,0x0,
0x22,0x17,0x41,0xB0,0x32,0x36,
};
#endif

inline uint8_t low_byte(uint32_t value)
{
    return (uint8_t)value;
}

inline uint8_t high_byte(uint32_t value)
{
    return (uint8_t)(value >> 8);
}

static void epd_gpio_config(void)
{
    spi_init();
    spi_start(EPD_CS_PIN, false, 0, EPD_SPI_DIVISOR);

    gpio_set_pin_input(EPD_BUSY_PIN);
    gpio_set_pin_output(EPD_RST_PIN);
    gpio_set_pin_output(EPD_DC_PIN);


    gpio_write_pin_high(EPD_RST_PIN);
    gpio_write_pin_high(EPD_DC_PIN);
}

#if 0
static void epd_send_command(uint8_t cmd)
{
    bool first = true;
    while (gpio_read_pin(EPD_BUSY_PIN)){
        if (first){
            dprintf("send command %02x in spite of BUSY\n", cmd);
            first = false;
        }
        wait_ms(1);
    }

    gpio_write_pin_low(EPD_DC_PIN);
    spiSend(&SPI_DRIVER, 1, &cmd);
}
#endif
#if 0
static void epd_send_data(uint8_t data)
{
    gpio_write_pin_high(EPD_DC_PIN);
    spiSend(&SPI_DRIVER, 1, &data);
}
#endif

#if 0
static void epd_send_data_block(const uint8_t* block, size_t len)
{
    gpio_write_pin_high(EPD_DC_PIN);
    spiSend(&SPI_DRIVER, len, block);
}
#endif

#if 0
static void epd_send_data_block_async(const uint8_t* block, size_t len)
{
    gpio_write_pin_high(EPD_DC_PIN);
    spiStartSend(&SPI_DRIVER, len, block);
}

static bool epd_send_data_block_wait(void)
{
    if (SPI_DRIVER.state != SPI_READY){
        return false;
    }
    return true;
}
#endif

static void epd_send_command_block(uint8_t cmd, const uint8_t* block, size_t len)
{
    bool first = true;
    while (gpio_read_pin(EPD_BUSY_PIN)){
        if (first){
            dprintf("send command %02x in spite of BUSY\n", cmd);
            first = false;
        }
        wait_ms(1);
    }

    dprintf("epd: %02x", cmd);
    int n = len < 4 ? len: 4;
    if (n > 0){        for (int i = 0; i < n; i++){
            dprintf(" %02x", block[i]);
        }
        if (len > n){
            dprint("...");
        }
    }
    dprint("\n");

    gpio_write_pin_low(EPD_DC_PIN);
    spiSend(&SPI_DRIVER, 1, &cmd);

    gpio_write_pin_high(EPD_DC_PIN);
    spiSend(&SPI_DRIVER, len, block);
}

static void epd_send_command_block_async(uint8_t cmd, const uint8_t* block, size_t len)
{
    bool first = true;
    while (gpio_read_pin(EPD_BUSY_PIN)){
        if (first){
            dprintf("send command %02x in spite of BUSY\n", cmd);
            first = false;
        }
        wait_ms(1);
    }

    dprintf("epd: %02x", cmd);
    int n = len < 4 ? len: 4;
    if (n > 0){
        for (int i = 0; i < n; i++){
            dprintf(" %02x", block[i]);
        }
        if (len > n){
            dprint("...");
        }
    }
    dprint("\n");

    gpio_write_pin_low(EPD_DC_PIN);
    spiSend(&SPI_DRIVER, 1, &cmd);

    gpio_write_pin_high(EPD_DC_PIN);
    spiStartSend(&SPI_DRIVER, len, block);
}

static bool epd_send_command_block_wait(void)
{
    if (SPI_DRIVER.state != SPI_READY){
        return false;
    }
    return true;
}

#if 0
static void epd_set_windows(uint x_start, uint y_start, uint x_end, uint y_end)
{
#if 0
    uint8_t data[4];

    // SET_RAM_X_ADDRESS_START_END_POSITION
    data[0] = (uint8_t)(x_start >> 3);
    data[1] = (uint8_t)((x_end - 1) >> 3);
    epd_send_command_block(0x44, data, 2);

    // SET_RAM_Y_ADDRESS_START_END_POSITION
    data[0] = low_byte(y_start);
    data[1] = high_byte(y_start);
    data[2] = low_byte(y_end - 1);
    data[3] = high_byte(y_end - 1);
    epd_send_command_block(0x45, data, 4);
#endif
}

static void epd_set_cursor(uint x_start, uint y_start)
{
#if 0
    (void)y_start;
    uint8_t data[2];

    // SET_RAM_X_ADDRESS_COUNTER
    data[0] = (uint8_t)(x_start >> 3);
    epd_send_command_block(0x4e, data, 1);

    // SET_RAM_Y_ADDRESS_COUNTER
    data[0] = low_byte(y_start);
    data[1] = high_byte(y_start);
    epd_send_command_block(0x4f, data, 2);
#endif
}
#endif
#if 1
static void epd_set_lut_by_host(const uint8_t* lut)
{
    epd_send_command_block(0x32, lut, 153);
    epd_send_command_block(0x3f, &lut[153], 1);
    epd_send_command_block(0x03, &lut[154], 1);
    epd_send_command_block(0x04, &lut[155], 3);
    epd_send_command_block(0x2c, &lut[158], 1);
}
#endif

///////////////////////////////////////////////////////////////////
// EPD status/stages

// epdの状態を大まかに示す
// スリープ解除中(EPD_STAT_AWAKEN_IN_PROCESS)の詳細は epd_awaken_stage で表す。
// スリープ突入中(EPD_STAT_SLEEP_IN_PROCESS)の詳細は epd_sleep_stage で表す。
typedef enum {
    EPD_STAT_SLEEP = 0,
    EPD_STAT_AWAKEN_IN_PROCESS,
    EPD_STAT_AWAKEN,
    EPD_STAT_SLEEP_IN_PROCESS
} epd_stat_t;

// 電源ONしたあとにEPDを使用する前にHW RESETをかける必要がある。
// HW RESETはSLEEPの解除でもあり、どうせ初期画面を表示するためにHW RESETをかけるので問題ない。
static epd_stat_t epd_stat = EPD_STAT_SLEEP;

typedef enum {
    EPD_POWER_STAGE_SIGNAL_ANALOG_OFF = 0,
    EPD_POWER_STAGE_SIGNAL_ANALOG_ON
} epd_power_stage_t;

// 明示的に signalとAnalogをONにするまでは OFFとして扱う。
// 電源ON後の最初の画面更新をするときに明示的にONにするので、
// すでにEPDがONなのにファームがOFFと思っていても問題がない。
static epd_power_stage_t epd_power_stage = EPD_POWER_STAGE_SIGNAL_ANALOG_OFF;


// アイドル時間を監視してスリープに突入させる状態の詳細
typedef enum {
    EPD_IDLE_STAGE_OUTSIDE = 0,
    EPD_IDLE_STAGE_WATCHING,
    EPD_IDLE_STAGE_COMPL
} epd_idle_stage_t;

static epd_idle_stage_t epd_idle_stage = EPD_IDLE_STAGE_OUTSIDE;

// epd_statがEPD_STAT_AWAKENのときに、epdの表示更新がないまま監視時間が経過するとepdスリープに入れる。
// そのための最後の表示更新のときのタイマー値を格納する。
static uint32_t tim_idle_start;

// EPD status/stages
//////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// Control Sequencer Engine

typedef enum cseq_type {
    CSEQ_TYPE_END = 0,
    CSEQ_TYPE_FUNC_BV,
    CSEQ_TYPE_FUNC_BCVP
} cseq_type_t;

typedef bool (*cseq_func_bv_t)(void);
typedef bool (*cseq_func_bcvp_t)(const void*);

typedef union cseq_elem   cseq_elem_t;

typedef struct cseq_elem_header {
    cseq_type_t type;
} cseq_elem_header_t;

typedef struct cseq_elem_func_bv {
    cseq_type_t type;
    cseq_func_bv_t func;
} cseq_elem_func_bv_t;

typedef struct cseq_elem_func_bcvp {
    cseq_type_t type;
    cseq_func_bcvp_t func;
    void* param;
} cseq_elem_func_bcvp_t;

union cseq_elem {
    cseq_elem_header_t  header;
    cseq_elem_func_bv_t func_bv;
    cseq_elem_func_bcvp_t func_bcvp;
};

#define BEGIN_SEQ(NAME) const cseq_elem_t NAME[] = {
#define END_SEQ {.header={.type=CSEQ_TYPE_END}}};

#define SEQELEM_FUNC_BV(FUNC)  {.func_bv={.type=CSEQ_TYPE_FUNC_BV, .func=(FUNC)}}
#define SEQELEM_FUNC_BCVP(FUNC, PARAM)  {.func_bcvp={.type=CSEQ_TYPE_FUNC_BCVP, .func=(const void*)(FUNC), .param=(PARAM)}}
#define SEQELEM_DPRINT(MSG) {.func_bcvp={.type=CSEQ_TYPE_FUNC_BCVP, .func=(const void*)seqelem_dprint, .param=(MSG)}}

static const cseq_elem_t*   seq_next;
static const cseq_elem_t*   pelem_cur;
static const uint8_t* image_next;
static const uint8_t* image;
static const uint8_t* image_prev;
static uint32_t tim_seq_start;

// スリープ突入のシーケンスの前方宣言
// 後ろの方で実装する
const cseq_elem_t seq_deep_sleep[];


static void cseq_engine_task(void)
{
    if (pelem_cur == NULL){
        if (seq_next == NULL){
            return;
        }
        pelem_cur = seq_next;
        seq_next = NULL;
        image = image_next;
        image_next = NULL;
        epd_idle_stage = EPD_IDLE_STAGE_OUTSIDE;
        tim_seq_start = timer_read32();
    }
    switch (pelem_cur->header.type){
        case CSEQ_TYPE_END:
            dprintf("seq running time: %lu\n", timer_elapsed32(tim_seq_start));
            pelem_cur = NULL;
            if (epd_stat == EPD_STAT_AWAKEN){
                epd_idle_stage = EPD_IDLE_STAGE_WATCHING;
                tim_idle_start = timer_read32();
            }
            return;
        case CSEQ_TYPE_FUNC_BV:
            {
                const cseq_elem_func_bv_t* pefunc_bv = (const cseq_elem_func_bv_t*)pelem_cur;
                if ((pefunc_bv->func)() == false){
                    return;
                }
                break;
            }
        case CSEQ_TYPE_FUNC_BCVP:
            {
                const cseq_elem_func_bcvp_t* pefunc_bcvp = (const cseq_elem_func_bcvp_t*)pelem_cur;
                if ((pefunc_bcvp->func)(pefunc_bcvp->param) == false){
                    return;
                }
                break;
            }
    }
    pelem_cur++;
}

#if 1
static void cseq_watch_idle(void)
{
    // After ENTER_DEEP_SLEEP_AFTER_MS of not using the device,
    // put the device to deep sleep.
    if (epd_idle_stage == EPD_IDLE_STAGE_WATCHING){
        if (timer_elapsed32(tim_idle_start) < MS_ENTER_DEEP_SLEEP_AFTER){
            return;
        }
        dprint("idle timer expired\n");
        epd_idle_stage = EPD_IDLE_STAGE_COMPL;
        seq_next = seq_deep_sleep;
    }
}
#endif

static void cseq_start(const cseq_elem_t* seq, const uint8_t* image)
{
    seq_next = seq;
    image_next = image;
}

// Control Sequencer Engine
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
// Delay timer for using with the Control Sequence Elements

typedef struct {
    uint32_t    tim_start;
    uint32_t    ms_delay;
    bool        active;
} delay_ctx_t;

static delay_ctx_t delay_ctx;

void delay_async(uint32_t ms_delay)
{
    delay_ctx.ms_delay = ms_delay;
    delay_ctx.tim_start = timer_read32();
    delay_ctx.active = true;
}

bool delay_wait(void)
{
    if (timer_elapsed32(delay_ctx.tim_start) < delay_ctx.ms_delay){
        return false;
    }
    delay_ctx.active = false;
    return true;
}

// Delay timer for using with the Control Sequence Elements
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
// wait busy

static uint32_t count_busy_off;

static void wait_busy_on(void)
{
    while (gpio_read_pin(EPD_BUSY_PIN) == 0){
        count_busy_off++;
    }
}

static bool wait_busy_off(void)
{
    if (gpio_read_pin(EPD_BUSY_PIN)){
        return false;
    }
    return true;
}


// wait busy
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
// Elements of Sequence


static uint32_t tim_start_turn_on_display;


static bool seqelem_dprint(const char* msg)
{
    dprint(msg);
    return true;
}

static bool seqelem_delay_init_async(void)
{
    delay_async(MS_DELAY_INIT);
    return true;
}

static bool seqelem_delay_init_wait(void)
{
    return delay_wait();
}

static bool seqelem_hw_reset_1of3(void)
{
    if (epd_stat == EPD_STAT_AWAKEN){
        dprintf("hw reset is skipped\n");
        return true;
    }
    dprintf("seqelem_hw_reset is started\n");
    epd_stat = EPD_STAT_AWAKEN_IN_PROCESS;
    // 念のためDEEP SLEEPから復帰した後に1回 SINALとANALOGをONするように
    epd_power_stage = EPD_POWER_STAGE_SIGNAL_ANALOG_OFF;
    // RST線をLOWにする前に、HIGHであることを保証する
    gpio_write_pin_low(EPD_RST_PIN);
    delay_async(MS_HW_RESET_LOW);
    return true;
}

static bool seqelem_hw_reset_2of3(void)
{
    if (epd_stat == EPD_STAT_AWAKEN){
        return true;
    }
    if (delay_wait() == false){
        return false;
    }
    // dprintf("seqelem_hw_reset_2of4\n");
    gpio_write_pin_high(EPD_RST_PIN);
    delay_async(MS_HW_RESET_HIGH_POST);
    return true;
}

static bool seqelem_hw_reset_3of3(void)
{
    if (epd_stat == EPD_STAT_AWAKEN){
        return true;
    }
    if (delay_wait() == false){
        return false;
    }
    epd_stat = EPD_STAT_AWAKEN;
    return true;
}

static bool seqelem_sw_reset_async(void)
{
    dprint("seqelem_sw_reset_async\n");

    // soft reset
    epd_send_command_block(0x12, NULL, 0);
    wait_busy_on();

    return true;
}

static bool seqelem_sw_reset_wait(void)
{
    if (wait_busy_off() == false){
        return false;
    }
    return true;
}

static bool seqelem_init_async(void)
{
    uint8_t data[3];

    dprint("seqelem_init_async\n");
#if 0
    // Driver output control
    data[0] = low_byte(EPD_HEIGHT - 1);
    data[1] = high_byte(EPD_HEIGHT - 1);
    data[2] = 0x00;
    epd_send_command_block(0x01, data, 3);
#endif
    // Driver output control
    data[0] = low_byte(EPD_HEIGHT - 1);
    data[1] = high_byte(EPD_HEIGHT - 1);
    data[2] = 0x01;
    epd_send_command_block(0x01, data, 3);

#if 0
    // Booster Soft start Control
    data[0] = 0xd7;
    data[1] = 0xd6;
    data[2] = 0x9d;
    epd_send_command_block(0x0c, data, 3);
#endif
#if 0
    // Data entry sequence setting
    data[0] = 0x03;
    epd_send_command_block(0x11, data, 1);
#endif
#if 1
    // Border Waveform Control
    data[0] = 0x05;
    epd_send_command_block(0x3c, data, 1);
#endif
#if 0
    // Display Update Control
    data[0] = 0x00;
    data[1] = 0x80;
    epd_send_command_block(0x21, data, 2);
#endif
    // Temperature Sensor Selection
    data[0] = 0x80;  // Internal temperature sensor
    epd_send_command_block(0x18, data, 1);
#if 0
    // Display Update Control
    data[0] = 0x00;
    data[1] = 0x80;
    epd_send_command_block(0x21, data, 2);
#endif
#if 1
    epd_set_lut_by_host(WF_FULL);
#endif
#if 0
    epd_set_windows(0, 0, EPD_WIDTH, EPD_HEIGHT);
    epd_set_cursor(0, 0);
#endif
#if 0
    // data[0] = 0xf4;
    data[0] = 0xb1;
    epd_send_command_block(0x22, data, 1);
    epd_send_command(0x20);
    wait_busy_on();
    epd_power_stage = EPD_POWER_STAGE_SIGNAL_ANALOG_ON;
#endif
    return true;
}

static bool seqelem_init_wait(void)
{
#if 0
    if (wait_busy_off() == false){
        return false;
    }
#endif
    return true;
}

#if 1
static const uint8_t DATA_37_FOR_PARTIAL_UPDATE[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00
};
static const uint32_t SIZE_DATA_37_FOR_PARTIAL_UPDATE = sizeof(DATA_37_FOR_PARTIAL_UPDATE);

static bool seqelem_prepare_partial(void)
{
#if 0
    uint8_t data[2];
#endif
#if 1
    epd_set_lut_by_host(WF_PARTIAL_2IN9);
#endif
    // Write Register for Display Option
    epd_send_command_block(0x37, DATA_37_FOR_PARTIAL_UPDATE, SIZE_DATA_37_FOR_PARTIAL_UPDATE);
#if 0
    // Border Waveform Control
    data[0] = 0x80;
    epd_send_command_block(0x3c, data, 1);
#endif
#if 0
    data[0] = 0x00;
    data[1] = 0x00;
    epd_send_command_block(0x21, data, 2);
#endif
#if 0
    epd_set_windows(0, 0, EPD_WIDTH, EPD_HEIGHT);
    epd_set_cursor(0, 0);
#endif
    return true;
}
#endif

#if 0
static bool seqelem_clear_bw_ram_async(void)
{
#if 0
    epd_set_windows(0, 0, EPD_WIDTH, EPD_HEIGHT);
    epd_set_cursor(0, 0);
#endif
    epd_send_command_block_async(0x24, img_296_blank, COUNT_BYTES_IN_IMAGE);
    return true;
}

static bool seqelem_clear_bw_ram_wait(void)
{
    if (epd_send_command_block_wait() == false){
        return false;
    }
    return true;
}
#endif
#if 0
static bool seqelem_clear_red_ram_async(void)
{
#if 0
    epd_set_windows(0, 0, EPD_WIDTH, EPD_HEIGHT);
    epd_set_cursor(0, 0);
#endif
    epd_send_command_block_async(0x26, img_296_blank, COUNT_BYTES_IN_IMAGE);
    return true;
}

static bool seqelem_clear_red_ram_wait(void)
{
    if (epd_send_command_block_wait() == false){
        return false;
    }
    return true;
}
#endif
#if 0
static bool seqelem_set_lut_20_30(void)
{
    epd_set_lut_by_host(WS_20_30);
    return true;
}

static bool seqelem_set_lut_full(void)
{
    epd_set_lut_by_host(WF_FULL);
    return true;
}

static bool seqelem_set_lut_partial(void)
{
    epd_set_lut_by_host(WF_PARTIAL_2IN9);
    return true;
}

static bool seqelem_clear(void)
{
    epd_set_windows(0, 0, EPD_WIDTH, EPD_HEIGHT);
    epd_set_cursor(0, 0);

    epd_send_command(0x24);
    epd_send_data_repeatedly(0xff, COUNT_IMAGE_BYTES);
    epd_send_command(0x26);
    epd_send_data_repeatedly(0xff, COUNT_IMAGE_BYTES);
    return true;
}
#endif

static bool seqelem_send_image_async(void)
{
    dprintf("seqelem_send_image_async image: %p\n", image);
    epd_send_command_block_async(0x24, image, COUNT_BYTES_IN_IMAGE);
    return true;
}

static bool seqelem_send_image_wait(void)
{
    if (epd_send_command_block_wait() == false){
        return false;
    }
    image_prev = image;
    return true;
}

static bool seqelem_send_prev_image_async(void)
{
    if (image_prev == NULL){
        return true;
    }
    dprintf("seqelem_send_prev_image_async image: %p\n", image_prev);
    epd_send_command_block_async(0x24, image_prev, COUNT_BYTES_IN_IMAGE);
    return true;
}

static bool seqelem_send_prev_image_wait(void)
{
    if (image_prev == NULL){
        return true;
    }
    if (epd_send_command_block_wait() == false){
        return false;
    }
    image_prev = NULL;
    return true;
}

static bool seqelem_send_back_image_async(void)
{
    dprintf("seqelem_send_back_image_async image: %p\n", image);
    epd_send_command_block_async(0x26, image, COUNT_BYTES_IN_IMAGE);
    return true;
}

static bool seqelem_send_back_image_wait(void)
{
    if (epd_send_command_block_wait() == false){
        return false;
    }
    return true;
}

static bool seqelem_turn_on_display_async(void)
{
    tim_start_turn_on_display = timer_read32();

#if 1
    // 必要な時だけclock signalとAnalogをONにする。
    // epdの表示更新処理を数十msec短くできる。
    // clock signalとAnalogはSleepに入る直前までONのままとする。
    uint8_t data = 0x34;
    if (epd_power_stage != EPD_POWER_STAGE_SIGNAL_ANALOG_ON){
        epd_power_stage = EPD_POWER_STAGE_SIGNAL_ANALOG_ON;
        data |= 0xc0;
    }
#else
    uint8_t data = 0x37;
#endif
    epd_send_command_block(0x22, &data, 1);
    epd_send_command_block(0x20, NULL, 0);
    wait_busy_on();
    return true;
}

static bool seqelem_turn_on_display_wait(void)
{
    if (wait_busy_off() == false){
        return false;
    }
    dprintf("turn on display: %lu[ms]\n", timer_elapsed32(tim_start_turn_on_display));
    return true;
}

static int count_disp_partial = 0;

static bool seqelem_turn_on_display_partial_async(void)
{
    tim_start_turn_on_display = timer_read32();
#if 1
    // 必要な時だけclock signalとAnalogをONにする。
    // clock signalとAnalogはDeep Sleepに入る直前までONのままとする。
    uint8_t data = 0x3c;
    if (epd_power_stage != EPD_POWER_STAGE_SIGNAL_ANALOG_ON){
        epd_power_stage = EPD_POWER_STAGE_SIGNAL_ANALOG_ON;
        data |= 0xc0;
    }
#else
    uint8_t data = 0x3f;
#endif
    epd_send_command_block(0x22, &data, 1);
    epd_send_command_block(0x20, NULL, 0);
    wait_busy_on();
    return true;
}

static bool seqelem_turn_on_display_partial_wait(void)
{
    if (wait_busy_off() == false){
        return false;
    }
    ++count_disp_partial;
    dprintf("turn on display partial: %lu[ms], count: %u\n", timer_elapsed32(tim_start_turn_on_display), count_disp_partial);
    return true;
}

static bool seqelem_signal_analog_off_async(void)
{
    epd_stat = EPD_STAT_SLEEP_IN_PROCESS;
    if (epd_power_stage == EPD_POWER_STAGE_SIGNAL_ANALOG_OFF){
        dprint("skip signal/analog off\n");
        return true;
    }
    uint8_t data = 0x03;
    epd_send_command_block(0x22, &data, 1);
    epd_send_command_block(0x20, NULL, 0);
    wait_busy_on();
    return true;
}

static bool seqelem_signal_analog_off_wait(void)
{
    if (epd_power_stage == EPD_POWER_STAGE_SIGNAL_ANALOG_OFF){
        return true;
    }
    if (wait_busy_off() == false){
        return false;
    }
    epd_power_stage = EPD_POWER_STAGE_SIGNAL_ANALOG_OFF;
    return true;
}

#if 1
static bool seqelem_deep_sleep_async(void)
{
    uint8_t data = 0x01;
    epd_send_command_block(0x10, &data, 1);
    delay_async(MS_DEEP_SLEEP_DELAY);
    return true;
}

static bool seqelem_deep_sleep_wait(void)
{
    if (delay_wait() == false){
        return false;
    }
    epd_stat = EPD_STAT_SLEEP;
    return true;
}
#endif


static uint32_t tim_show_image_partial_start;

static bool seqelem_show_image_partial_start(void)
{
    dprint("seqelm_show_image_partial_start\n");
    tim_show_image_partial_start = timer_read32();
    return true;
}


static bool seqelem_show_image_partial_end(void)
{
    dprintf("seqelm_show_image_partial_end: %lu[msec]\n", timer_elapsed32(tim_show_image_partial_start));
    return true;
}

bool seqelem_set_image_blank(void)
{
    image = img_296_blank;
    return true;
}

#if 0
bool seqelem_set_image_pat1(void)
{
    image = img_296_pat1;
    return true;
}

bool seqelem_set_image_pat2(void)
{
    image = img_296_pat2;
    return true;
}

bool seqelem_set_image_pat3(void)
{
    image = img_296_pat3;
    return true;
}
#endif


bool seqelem_delay_3s_async(void)
{
    delay_async(3000);
    return true;
}

bool seqelem_delay_3s_wait(void)
{
    return delay_wait();
}

bool seqelem_delay_60s_async(void)
{
    delay_async(5000);
    return true;
}

bool seqelem_delay_60s_wait(void)
{
    return delay_wait();
}

// Elements of Sequence
////////////////////////////////////////////////////

////////////////////////////////////////////////////
// Sequences

BEGIN_SEQ(seq_init)
    SEQELEM_DPRINT("seq_init start\n"),
    SEQELEM_FUNC_BV(seqelem_delay_init_async),
    SEQELEM_FUNC_BV(seqelem_delay_init_wait),
    SEQELEM_FUNC_BV(seqelem_hw_reset_1of3),
    SEQELEM_FUNC_BV(seqelem_hw_reset_2of3),
    SEQELEM_FUNC_BV(seqelem_hw_reset_3of3),
    SEQELEM_FUNC_BV(seqelem_sw_reset_async),
    SEQELEM_FUNC_BV(seqelem_sw_reset_wait),
    SEQELEM_FUNC_BV(seqelem_init_async),
    SEQELEM_FUNC_BV(seqelem_init_wait),
//    SEQELEM_FUNC_BV(seqelem_clear_bw_ram_async),
//    SEQELEM_FUNC_BV(seqelem_clear_bw_ram_wait),
    SEQELEM_FUNC_BV(seqelem_send_image_async),
    SEQELEM_FUNC_BV(seqelem_send_image_wait),
    SEQELEM_FUNC_BV(seqelem_send_back_image_async),
    SEQELEM_FUNC_BV(seqelem_send_back_image_wait),
//    SEQELEM_FUNC_BV(seqelem_clear_red_ram_async),
//    SEQELEM_FUNC_BV(seqelem_clear_red_ram_wait),
    SEQELEM_FUNC_BV(seqelem_turn_on_display_async),
    SEQELEM_FUNC_BV(seqelem_turn_on_display_wait),
    SEQELEM_FUNC_BV(seqelem_prepare_partial),
//    SEQELEM_FUNC_BV(seqelem_send_image_async),
//    SEQELEM_FUNC_BV(seqelem_send_image_wait),
//    SEQELEM_FUNC_BV(seqelem_turn_on_display_partial_async),
//    SEQELEM_FUNC_BV(seqelem_turn_on_display_partial_wait),
    SEQELEM_DPRINT("seq_init end\n"),
END_SEQ

BEGIN_SEQ(seq_show_image_partial)
    SEQELEM_FUNC_BV(seqelem_show_image_partial_start),
    SEQELEM_FUNC_BV(seqelem_hw_reset_1of3),
    SEQELEM_FUNC_BV(seqelem_hw_reset_2of3),
    SEQELEM_FUNC_BV(seqelem_hw_reset_3of3),
    SEQELEM_FUNC_BV(seqelem_send_image_async),
    SEQELEM_FUNC_BV(seqelem_send_image_wait),
    SEQELEM_FUNC_BV(seqelem_turn_on_display_partial_async),
    SEQELEM_FUNC_BV(seqelem_turn_on_display_partial_wait),
    SEQELEM_FUNC_BV(seqelem_show_image_partial_end),
END_SEQ

BEGIN_SEQ(seq_deep_sleep)
    SEQELEM_DPRINT("seq_deep_sleep start\n"),
    SEQELEM_FUNC_BV(seqelem_send_prev_image_async),
    SEQELEM_FUNC_BV(seqelem_send_prev_image_wait),
    SEQELEM_FUNC_BV(seqelem_signal_analog_off_async),
    SEQELEM_FUNC_BV(seqelem_signal_analog_off_wait),
    SEQELEM_FUNC_BV(seqelem_deep_sleep_async),
    SEQELEM_FUNC_BV(seqelem_deep_sleep_wait),
    SEQELEM_DPRINT("seq_deep_sleep end\n"),
END_SEQ

// Sequences
////////////////////////////////////////////////////

typedef enum {
    IDLE_TIMER_PHASE_FREE = 0,
    IDLE_TIMER_PHARE_START,
    IDLE_TIMER_PHARE_EXPIRED
} idle_timer_phase_t;

static idle_timer_phase_t idle_timer_phase = IDLE_TIMER_PHASE_FREE;
static uint32_t tim_idle_start;


void epd_display_image_partial(const uint8_t* image)
{
    idle_timer_phase = IDLE_TIMER_PHASE_FREE;
    cseq_start(seq_show_image_partial, image);
}

void epd_task_init(const uint8_t* image)
{
    idle_timer_phase = IDLE_TIMER_PHASE_FREE;
    epd_gpio_config();
    cseq_start(seq_init, image);
}


void epd_task(void)
{
    cseq_engine_task();
    cseq_watch_idle();
}

const uint8_t TEST_PATTERN[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


volatile int dummy;

static uint8_t test_bmp[COUNT_BYTES_IN_IMAGE];

void epd_init_bmp(void)
{
    memset(test_bmp, 0xff, COUNT_BYTES_IN_IMAGE);
    uint x = 0;
    for (int y = 0; y < EPD_HEIGHT; y++){
        uint offset_x = x >> 3;
        uint8_t patt = 0x80 >> (x % 8);
        test_bmp[y * COUNT_BYTES_IN_LINE + offset_x] = ~patt;
        x++;
        if (x >= EPD_WIDTH){
            x = 0;
        }
    }
}

void epd_init_bmp2(void)
{
    memset(test_bmp, 0xff, COUNT_BYTES_IN_IMAGE);
    for (int y = 0; y < 4; y++){
        uint8_t* line = &test_bmp[y * COUNT_BYTES_IN_LINE];
        for (int x = 0; x < EPD_WIDTH; x += 8){
            line[x / 8] = 0xf0;
        }
    }
}

