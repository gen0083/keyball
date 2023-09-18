# Keyball Series

![Keyball61](./keyball61/doc/rev1/images/kb61_001.jpg)

Keyball series is keyboard family which have 100% track ball.
## 使用準備

qmk_firmwareをホームディレクトリ、Keyballを~/program/keyboardに配置した場合の例

1. [qmk_firmware](https://github.com/qmk/qmk_firmware)をcloneする
2. [gen0083/keyball](https://github.com/gen0083/keyball)のclone
3. symbolic linkを貼る（`ln -s ~/program/keyboard/keyball_gen0083/qmk_firmware/keyboards/keyball ~/qmk_firmware/keyboards/keyball`）[^1]
4. qmk_firmwareのバージョンを合わせる（`git checkout 0.19.x`）
5. qmk_firmwareでビルド（`qmk compile -kb <keyboard> -km <keymap>`）[^2]
6. `qmk flash`で書き込み

[^1]: symbolic linkの削除は `unlink`
[^2]: 細かい設定はドキュメント参照　https://docs.qmk.fm/#/newbs_building_firmware

## Firmware build guide

Keyboards in the family are:

* Available
    * Keyball39: split + 39 keys + a track ball
    * Keyball44: split + 44 keys + a track ball
    * Keyball61: split + 61 keys + a track ball
* Unavailable
    * Keyball46 (first one!)
    * One47

## Where to Buy

|Keyboard   |Yushakobo / 遊舎工房                       |Shirogane Lab / 白金ラボ                                   |
|-----------|-------------------------------------------|-----------------------------------------------------------|
|Keyball39  |<https://shop.yushakobo.jp/products/5357>  |<https://shirogane-lab.net/items/64b8f8693ee3fd0045280190> |
|Keyball44  |N/A                                        |<https://shirogane-lab.net/items/64b7a006eb6dbe00346cd0c5> |
|Keyball61  |<https://shop.yushakobo.jp/products/5358>  |<https://shirogane-lab.net/items/64b8ed191435c1002bc4cd30> |

## Build Guide

*   Keyball39:
    [English/英語](/keyball39/doc/rev1/buildguide_en.md),
    [日本語/Japanese (ピンヘッダ版)](./keyball39/doc/rev1/buildguide_jp.md),
    [日本語/Japanese (コンスルー版)](./keyball39/doc/rev1/buildguide_jp_conth.md)
*   Keyball44: ~~English/英語~~ (Sorry, unavailable),
    [日本語/Japanese (ピンヘッダ版)](./keyball44/doc/rev1/buildguide_jp.md),
    [日本語/Japanese (コンスルー版)](./keyball44/doc/rev1/buildguide_jp_conth.md)
*   Keyball46:
    [English/英語](./keyball46/doc/rev1/buildguide_en.md),
    [日本語/Japanese](./keyball46/doc/rev1/buildguide_jp.md)
*   Keyball61:
    [English/英語](./keyball61/doc/rev1/buildguide_en.md),
    [日本語/Japanese (ピンヘッダ版)](./keyball61/doc/rev1/buildguide_jp.md),
    [日本語/Japanese (コンスルー版)](./keyball61/doc/rev1/buildguide_jp_conth.md)

## Firmware

See [document for firmware source code](./qmk_firmware/keyboards/keyball/readme.md).

### Pre-compiled Firmwares

(TO BE DOCUMENTED)
