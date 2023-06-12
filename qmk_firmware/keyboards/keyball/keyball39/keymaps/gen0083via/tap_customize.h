uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // レイヤー切り替えとの併用のためタップの判定値を短めにする
        case LT(1,KC_BSPC):
            return 120;
        case LT(2,KC_MINS):
            return 120;

        // liとタイピングするときにずらすように同時押しした場合に反応しないためその対策
        case LT(5,KC_L):
            return TAPPING_TERM + 200;

        default:
            return TAPPING_TERM;
    }
}