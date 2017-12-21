#include "lets_split.h"
#include "bootloader.h"
#include "action_layer.h"
#include "eeconfig.h"
#include "LUFA/Drivers/Peripheral/TWI.h"
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif
int cleanmatrix=0;
extern keymap_config_t keymap_config;




// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2


enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,


};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};


// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
//Macros
#define M_SAMPLE M(KC_SAMPLEMACRO)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,------------------------------------------------.      ,------------------------------------------------.
 * |    ` |   1  |   2  |   3  |   4  |   5  |   6  |      |   7  |   8  |   9  |   0  |   -  | =    | Bspc |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |  Esc | Q    |   W  |   E  |   R  |   T  |   Y  |      |   U  |   I  |   O  |   P  |   [  |   ]  |   \  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * | Tab  | A    |   S  |   D  |   F  |   G  |   H  |      |   J  |   K  |   L  |   ;  |   '  |   _  |INS   |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * | Shift| Z    |   X  |   C  |   V  |   B  |   N  |      |   M  |   ,  |   .  |   /  | prnt | Up   |del   |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * | Ctrl |Win   | alt  | Caps | Lower|Space |Space |      |enter |enter | raise| pscr |Left  | Down | Right|
 * `------------------------------------------------'      `------------------------------------------------'
 */
[_QWERTY] = KEYMAP( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,   KC_BSPC,\
  KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,  KC_BSLS, \
  KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_PASTE, KC_INS, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_COPY, KC_UP,    KC_DEL, \
  KC_LCTRL,KC_LGUI, KC_LALT, KC_CAPS, LOWER,   KC_SPC,  KC_SPC,  KC_ENT,  KC_ENT,  RAISE,   KC_PSCR, KC_LEFT, KC_DOWN,  KC_UP \
),





/* Lower
 * ,------------------------------------------------.      ,------------------------------------------------.
 * |      |   /  |  *   |  -   |  bspc| Copy |paste |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |   7  |   8  |  9   |   +  |   #  |   $  | CUT  |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |   4  |   5  |  6   |  =   |  ^   |  (   |  )   |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |   1  |   2  |  3   | enter|      |  [   |    ] |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      |  0   |      | enter|      |      |      |      |      |      |      |      |      |      |      |
 * `------------------------------------------------'      `------------------------------------------------'
 */
[_LOWER] =KEYMAP( \
KC_TRNS,  KC_SLSH,    KC_PAST,    KC_PMNS,    KC_BSPC,    KC_COPY,    KC_PASTE,   KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,  KC_TRNS,   KC_TRNS,\
KC_7,     KC_8,       KC_9,       KC_PPLS,    KC_HASH,    KC_PERC,    KC_CUT,     KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,  KC_TRNS,   KC_TRNS, \
KC_4,     KC_5,       KC_6,       KC_EQL,     KC_CIRC,    KC_LPRN,    KC_RPRN,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,  KC_TRNS,   KC_TRNS, \
KC_1,     KC_2,       KC_3,       KC_ENT,     KC_NO,      KC_LBRC,    KC_RBRC,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,  KC_TRNS,   KC_TRNS, \
KC_TRNS,  KC_0,       KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,  KC_TRNS,   KC_TRNS \
),
/* Raise
 * ,------------------------------------------------.      ,------------------------------------------------.
 * |  F1  |  F3  |  F3  |  F4  |  F5  |  F6  |  V+  |      |  F7  |  F8  |  F9  | F10  | F11  | F12  |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |  F7  |  F8  |  F9  | F10  | F11  | F12  |  V-  |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * | prnt |insert| PGUP |      |      |      | MUTE |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |delete| home | PGDN |      |      |      | END  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * `------------------------------------------------'      `------------------------------------------------'
 */
[_RAISE] = KEYMAP( \
KC_F1,    KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_VOLU,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,  KC_TRNS,   KC_TRNS,\
KC_F7,    KC_F8,      KC_F9,      KC_F10,     KC_F11,     KC_F12,     KC_VOLD,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,  KC_TRNS,   KC_TRNS, \
KC_PSCR,  KC_INS,     KC_PGUP,    KC_TRNS,    KC_MUTE,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,  KC_TRNS,   KC_TRNS, \
KC_DEL,   KC_HOME,    KC_PGDN,    KC_TRNS,    KC_END,     KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,  KC_TRNS,   KC_TRNS, \
KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,  KC_TRNS,   KC_TRNS \
),




};


#ifdef AUDIO_ENABLE

float tone_startup[][2]    = SONG(STARTUP_SOUND);
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
float tone_plover[][2]     = SONG(PLOVER_SOUND);
float tone_plover_gb[][2]  = SONG(PLOVER_GOODBYE_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);
float tone_goodbye[][2]    = SONG(GOODBYE_SOUND);
#endif








void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif

}

//SSD1306 OLED init and update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED
void matrix_master_OLED_init (void) {
    TWI_Init(TWI_BIT_PRESCALE_1, TWI_BITLENGTH_FROM_FREQ(1, 800000));
	iota_gfx_init();   // turns on the display
	iota_gfx_task();
	iota_gfx_flush();
	iota_gfx_off();
	iota_gfx_init();
	

}

void matrix_scan_user(void) {
     iota_gfx_task();  // this is what updates the display continuously
	 if(cleanmatrix<1301){
	 cleanmatrix++;
		 
	 }
	 if(cleanmatrix==1300){
		iota_gfx_init();   // turns on the display

		 
	 }


}
#endif

#ifdef AUDIO_ENABLE

void startup_user()
{
 
 
}

void shutdown_user()
{
    PLAY_SONG(tone_goodbye);
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void)
{
    music_scale_user();
}

void music_scale_user(void)
{
    PLAY_SONG(music_scale);
}

#endif

/*
 * Macro definition
 */
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    if (!eeconfig_is_enabled()) {
      eeconfig_init();
    }

    switch (id) {
      case KC_SAMPLEMACRO:
        if (record->event.pressed){
          return MACRO (I(10), T(H), T(E), T(L), T(L), T(O), T(SPACE), T(W), T(O), T(R), T(L), T(D), END);
        }

    }

    return MACRO_NONE;
}


void matrix_update(struct CharacterMatrix *dest,
                          const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

//assign the right code to your layers for OLED display
#define L_BASE 0
#define L_LOWER 1
#define L_RAISE 2
#define L_FNLAYER 64
#define L_NUMLAY 128
#define L_NLOWER 136
#define L_NFNLAYER 192
#define L_MOUSECURSOR 256
#define L_ADJUST 65560

void iota_gfx_task_user(void) {
#if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#endif

  struct CharacterMatrix matrix;

  matrix_clear(&matrix);
  //matrix_write_P(&matrix, PSTR("USB: "));
//#ifdef PROTOCOL_LUFA
  //switch (USB_DeviceState) {
    //case DEVICE_STATE_Unattached:
      //matrix_write_P(&matrix, PSTR("Unattached"));
      //break;
    //case DEVICE_STATE_Suspended:
      //matrix_write_P(&matrix, PSTR("Suspended"));
      //break;
    //case DEVICE_STATE_Configured:
      //matrix_write_P(&matrix, PSTR("Connected"));
      //break;
    //case DEVICE_STATE_Powered:
      //matrix_write_P(&matrix, PSTR("Powered"));
      //break;
    //case DEVICE_STATE_Default:
      //matrix_write_P(&matrix, PSTR("Default"));
      //break;
    //case DEVICE_STATE_Addressed:
      //matrix_write_P(&matrix, PSTR("Addressed"));
      //break;
    //default:
      //matrix_write_P(&matrix, PSTR("Invalid"));
  //}
//#endif

// Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below

  char buf[40];
  snprintf(buf,sizeof(buf), "Undef-%ld", layer_state);
  matrix_write_P(&matrix, PSTR("Layer: "));
    switch (layer_state) {
        case L_BASE:
           matrix_write_P(&matrix, PSTR("Default"));
           break;
        case L_RAISE:
           matrix_write_P(&matrix, PSTR("Raise"));
           break;
        case L_LOWER:
           matrix_write_P(&matrix, PSTR("Lower"));
           break;
        case L_ADJUST:
           matrix_write_P(&matrix, PSTR("ADJUST"));
           break;
        default:
           matrix_write(&matrix, buf);
 }

  // Host Keyboard LED Status
  char led[40];
    snprintf(led, sizeof(led), "\n\n%s ",
            (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) ? "CAPS" : "    ");
  matrix_write(&matrix, led);
  matrix_update(&display, &matrix);
}