uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(1,KC_BSPC):
            // 100だとかなり短いので、このあたりが妥当？
            return 120;
        default:
            return TAPPING_TERM;
    }
}