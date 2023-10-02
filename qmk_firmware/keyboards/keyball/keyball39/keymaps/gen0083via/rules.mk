RGBLIGHT_ENABLE = yes

# to enable debug, set OLED_ENABLE = no
OLED_ENABLE = yes
ifeq ($(strip $(OLED_ENABLE)), no)
  CONSOLE_ENABLE = yes
endif

VIA_ENABLE = yes

LTO_ENABLE = yes
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no