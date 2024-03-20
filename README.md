# proje1_sw

## Zaman ve Çevresel Değerlerin Takibi: RTC-DS1307 ve DHT11 ile Nokia5110 Ekranda Gösterim
Bu proje, Nucleo-F103RB Geliştirme Kartı ile DS1307-RTC modülü ve DHT11 Nem/Sıcaklık sensörü kullanılarak I2C, SPI ve 1-Wire haberleşme protokolleriyle entegre edilmiştir. Sonuç olarak, saat, tarih, nem ve sıcaklık değerleri 84x48 Grafik LCD üzerinde gösterilmiştir.


![ds1307](https://github.com/KOBASTAR-IME-2024/Proje_1/assets/115595244/ba90ad19-dae5-430f-be0a-cd9840695d22)



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
+ DIN SPI2_MOSI
+ CLK SPI2_SCK
