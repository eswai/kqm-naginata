# Keyboard Quantizer Miniで薙刀式

Releaseページのファームウェアをインストールして、Vialでkqm-naginata.vilをロードする。

かな入力モードで、Unicode入力モードを切り替え
* F1: Windows (WinCompose)
* F2: Mac (Karabiner-Elements + unicode_hex_input_switcher.json)
* F3: Linux

### ファームウェアのビルド

```
docker compose build
docker compose run --rm compile
```