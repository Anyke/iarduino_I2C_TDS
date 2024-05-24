// ПРИМЕР НАСТРОЙКИ МОДУЛЯ:                                  // * Строки со звёздочкой являются необязательными.
// Требуется установить библиотеку <iarduino_I2C_Software.h> //   https://iarduino.ru/file/627.html
                                                             //
// TDS/EC-метр с щупом (Trema-модуль) Flash-I2C:             //   https://iarduino.ru/shop/Sensory-Datchiki/bamper-s-9-datchikami-liniy-s-shagom-7mm-flash-i2c.html
// Информация о подключении модулей к шине I2C:              //   https://wiki.iarduino.ru/page/i2c_connection/
// Информация о модуле и описание библиотеки:                //   https://wiki.iarduino.ru/page/TDS-EC-i2c/
                                                             //
#include <iarduino_I2C_Software.h>                           //   Подключаем библиотеку для работы с программной шиной I2C, до подключения библиотеки iarduino_I2C_TDS.
SoftTwoWire sWire(3,4);                                      //   Создаём объект программной шины I2C указав выводы которым будет назначена роль линий: SDA, SCL.
                                                             //
#include <iarduino_I2C_TDS.h>                                //   Подключаем библиотеку для работы с TDS/EC-метром I2C-flash.
iarduino_I2C_TDS tds(0x09);                                  //   Объявляем объект tds  для работы с функциями и методами библиотеки iarduino_I2C_TDS, указывая адрес модуля на шине I2C.
                                                             //   Если объявить объект без указания адреса (iarduino_I2C_TDS tds;), то адрес будет найден автоматически.
void setup(){                                                //
     delay(500);                                             // * Ждём завершение переходных процессов связанных с подачей питания.
     tds.begin(&sWire);                                      //   Инициируем работу с TDS/EC-метром, указав ссылку на объект для работы с шиной I2C на которой находится модуль (по умолчанию &Wire).
     tds.setFrequency(  2000);                               //   Устанавливаем частоту переменного тока для измерений от 50 до 5000 Гц. Значение сохраняется в энергонезависимую память.
     tds.setKnownTDS (1, 500);                               //   Устанавливаем концентрацию 1 раствора для калибровки модуля с кнопки.  Значение сохраняется в энергонезависимую память.
     tds.setKnownTDS (2,1500);                               //   Устанавливаем концентрацию 2 раствора для калибровки модуля с кнопки.  Значение сохраняется в энергонезависимую память.
     tds.setKt       (  0.02);                               //   Устанавливаем температурный коэффициент жидкости от 0,0000 до 6,5535.
     tds.setKp       (  0.50);                               //   Устанавливаем коэффициент пересчёта от 0,01 до 2,55.
     tds.set_T       ( 25.00);                               //   Устанавливаем опорную температуру жидкости от 0,00 до 63,75 °С.
}                                                            //
                                                             //
void loop(){}                                                //