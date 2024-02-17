## Programlama: ##

Alakart’a yüklenecek olan .hex veya .bin dosyası, ilave bir programlayıcı olmadan direkt olarak Usb Type-C kablo ile karta yüklenebilir. Yükleme için kullanılan bilgisayarın işletim sistemine göre aşağıdaki araçlar kullanılabilir:

<br>

### FlashMagic (Windows ve MacOS): ###
[FlashMagic Tool](https://www.flashmagictool.com/) programı ile, Device kısmından LPC800 -> UART ->LPC824M201JHI33 seçilerek arayüz üzerinden programlama yapılabilir.

<img src="https://desird.com/wp-content/uploads/2023/10/flashmagic.png" width="660" height="472" > </img>

<br>

### lpcsp.exe (Windows): ###
FlashMagic’e komut satırı alternatifi olarak; [http://elm-chan.org/works/sp78k/lpcsp.zip](http://elm-chan.org/works/sp78k/lpcsp.zip) içerisindeki lpcsp.exe kullanılabilir:

```ps
lpcsp.exe -C3 -P2:115200 main.hex
```

<img src="https://desird.com/wp-content/uploads/2023/10/lpcsp.png" width="370" height="101"  > </img>

<br>

### lpc21isp (Linux) ###

Kurulum:

```bash
git clone https://gitlab.com/desird/alakart/alakart-sw/lpc21isp.git
cd lpc21isp
make
sudo cp lpc21isp /usr/bin/
```

Programlanacak .hex dosyasının olduğu dizinde, aşağıdaki gibi yükleme gerçekleştirilir:


```ps
lpc21isp main.hex -control /dev/ttyUSB0 115200 14746
```
