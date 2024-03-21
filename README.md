# RTC-TEMP_SW

## Zaman ve Çevresel Değerlerin Takibi: RTC-DS1307 ve DHT11 ile Nokia5110 Ekranda Gösterim
Bu proje, Nucleo-F103RB Geliştirme Kartı ile DS1307-RTC modülü ve DHT11 Nem/Sıcaklık sensörü kullanılarak I2C, SPI ve 1-Wire haberleşme protokolleriyle entegre edilmiştir. Sonuç olarak, saat, tarih, nem ve sıcaklık değerleri 84x48 Grafik LCD üzerinde gösterilmiştir.


![ds1307](https://github.com/KOBASTAR-IME-2024/proje1_sw/assets/115595244/ba5bbc0b-73fe-4a46-aae0-f0b7a5ac87f0)




## PINOUT
### DS1307-RTC:
- PB8 I2C1_SCL
- PB9 I2C1_SDA
  
### DHT11:
* PB3 DHT11_SENS
  
### Nokia5110:
+ RST PB10
+ CE  PA8
+ DC  PB4
+ DIN PB15 SPI2_MOSI
+ CLK PB13 SPI2_SCK

![rtc-temp_bb](https://github.com/KOBASTAR-IME-2024/RTC-Temp_SW/assets/115595244/fb25a37b-61c2-47cf-87c8-2ed39165c9d3)
