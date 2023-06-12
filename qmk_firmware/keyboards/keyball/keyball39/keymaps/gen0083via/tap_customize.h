uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(1,KC_BSPC):
            // レイヤー切り替えとの併用のためタップの判定値を短めにす
            return 120;
        case LT(5,KC_L):
            // liとタイピングするときにずらすように同時押しした場合に反応しないためその対策
            return TAPPING_TERM + 200;
        default:
            return TAPPING_TERM;
    }
}