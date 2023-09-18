# Keyball44

![Keyball44](../../../../keyball44/doc/rev1/images/kb44_001.jpg)

A split keyboard with 44 vertically staggered keys and 34mm track ball.

* Keyboard Maintainer: [@Yowkees](https://twitter.com/Yowkees)
* Hardware Supported: Keyball44 PCB, ProMicro
* Hardware Availability:
    * <https://shirogane-lab.net/items/64b7a006eb6dbe00346cd0c5>

Make example for this keyboard (after setting up your build environment):

    make keyball/keyball44:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Special keycodes

See [Special Keycode](../lib/keyball/keycodes.md) file.

1. qmkのバージョンはvia使うなら0.16.xにしとくのが無難
1. `qmk compile`(あらかじめ`qmk config`でkeyboard/keymap設定しておくと楽)
1. `qmk flash`(ProMicroどちらも)

## Special keycodes

qmk version 0.16.9

Value    | Keycode    |Description
---------|------------|------------------------------------------------------------------
`0x5DA6` | `KBC_RST`  |Reset Keyball configuration
`0x5DA7` | `KBC_SAVE` |Persist Keyball configuration to EEPROM
`0x5DA8` | `CPI_I100` |Increase 100 CPI (max 12000)
`0x5DA9` | `CPI_D100` |Decrease 100 CPI (min 100)
`0x5DAA` | `CPI_I1K`  |Increase 1000 CPI (max 12000)
`0x5DAB` | `CPI_D1K`  |Decrease 1000 CPI (min 100)
`0x5DAC` | `SCRL_TO`  |Toggle scroll mode
`0x5DAD` | `SCRL_MO`  |Enable scroll mode when pressing
`0x5DAE` | `SCRL_DVI` |Increase scroll divider (max 7 = 1/128)
`0x5DAF` | `SCRL_DVD` |Decrease scroll divider (min 0 = 1/1)
---------|------------|------------
`0x5DB2` | `KC_MY_SCRL_V` | 押してる間縦スクロール
`0x5DB3` | `KC_MY_SCRL_H` | 押してる間横スクロール
`0x5DB4` | `KC_TO_CLICKABLE_INC` | スクロールモードに入るトラックボール移動量の閾値を増やす
`0x5DB5` | `KC_TO_CLICKABLE_DEC` | 〃の閾値を減らす

***NOTE***

* The values are for VIA/Remap
* The values are for QMK/0.16.3. It will be different when you use another version of QMK.
