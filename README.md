# keyball

Keyball is split keyboard has 100% track ball

## 使用準備

qmk_firmwareをホームディレクトリ、Keyballを~/program/keyboardに配置した場合の例

1. [qmk_firmware](https://github.com/qmk/qmk_firmware)をcloneする
2. [gen0083/keyball](https://github.com/gen0083/keyball)のclone
3. symbolic linkを貼る（`ln -s ~/program/keyboard/keyball_gen0083/qmk_firmware/keyboards/keyball ~/qmk_firmware/keyboards/keyball`）[^1]
4. qmk_firmwareのバージョンを合わせる（`git checkout 0.16.9`）
5. qmk_firmwareでビルド（`qmk compile -kb <keyboard> -km <keymap>`）[^2][^3]
6. `qmk flash`で書き込み

[^1]: symbolic linkの削除は `unlink`
[^2]: 細かい設定はドキュメント参照　https://docs.qmk.fm/#/newbs_building_firmware
[^3]: `qmk config user.keyboard=keyball/keyball39`や`qmk config user.keybamp=gen0083via`で設定しておけば`qmk compile`だけですむ。ちなみに設定値の削除は`qmk config user.keyboard=None`のようにNoneを指定すれば削除できる。

- keyball/keyball39/gen0083via
- keyball/keyball44/gen0083via
はqmk 0.16.9で設定（remap使える）

keyball/keyball39/gen0083はqmkのバージョン最新で（remap使えない）

## Firmware build guide

Keyball46 have separate firmwares for each of PCBs w/ trackball and w/o
trackball.  You can build those with this commands in root of QMK firmware
source tree.

```console
$ make keyball/rev1/ball:via
$ make keyball/rev1/noball:via
```

You will get two files:

* `keyball_rev1_ball_via.hex` - Trackball PCB firmware with VIA support.
* `keyball_rev1_noball_via.hex` - No trackball PCB firmware with VIA support.

Write each firmwares to correct PCB's Pro Micro.

In generally, you can build fimwares with this command.

```console
$ make keyball/rev1/ball:{YOUR_FAVORITE_KEYMAP}
$ make keyball/rev1/noball:{YOUR_FAVORITE_KEYMAP}
```

### Keyamaps

Keyball46 provides some keymaps as default:

* `via` - VIA support, trackball is on right side
* `via_Left` - VIA support, trackball is on left side
* `test` - Test for building/soldering Keyball46 (w/ right trackball)
* `default` - Template for customized keymap (w/ right trackball)

### Prerequirements to build firmware

1. Checkout [QMK firmware source codes](https://github.com/qmk/qmk_firmware)
2. Setup QMK correctly ([See also](https://beta.docs.qmk.fm/tutorial/newbs_getting_started))
3. Copy `./qmk_firmware/keyboards/keyball/` directory in this repository to QMK firmware's dir as `{QMK_FIRMWARE_ROOT}/keyboards/keyball`.
4. Build Keyball46 firmwares (See above section)

    ```console
    $ make keyball/rev1/ball:via
    $ make keyball/rev1/noball:via
    ```
