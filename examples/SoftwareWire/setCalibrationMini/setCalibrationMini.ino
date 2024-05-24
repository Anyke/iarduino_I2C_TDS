// ПРИМЕР КАЛИБРОВКИ МОДУЛЯ:                                 // * Строки со звёздочкой являются необязательными.
// Требуется установить библиотеку <iarduino_I2C_Software.h> //   https://iarduino.ru/file/627.html
                                                             //
// TDS/EC-метр с щупом (Trema-модуль) Flash-I2C:             //   https://iarduino.ru/shop/Sensory-Datchiki/bamper-s-9-datchikami-liniy-s-shagom-7mm-flash-i2c.html
// Информация о подключении модулей к шине I2C:              //   https://wiki.iarduino.ru/page/i2c_connection/
// Информация о модуле и описание библиотеки:                //   https://wiki.iarduino.ru/page/TDS-EC-i2c/
                                                             //
// Данный пример короче чем setCalibrationBig                //
// так как в этом коде функция getCalibration()              //
// вызывается без параметра.                                 //
                                                             //
#include <iarduino_I2C_Software.h>                           //   Подключаем библиотеку для работы с программной шиной I2C, до подключения библиотеки iarduino_I2C_TDS.
SoftTwoWire sWire(3,4);                                      //   Создаём объект программной шины I2C указав выводы которым будет назначена роль линий: SDA, SCL.
                                                             //
#include <iarduino_I2C_TDS.h>                                //   Подключаем библиотеку для работы с TDS/EC-метром I2C-flash.
iarduino_I2C_TDS tds(0x09);                                  //   Объявляем объект tds  для работы с функциями и методами библиотеки iarduino_I2C_TDS, указывая адрес модуля на шине I2C.
                                                             //   Если объявить объект без указания адреса (iarduino_I2C_TDS tds;), то адрес будет найден автоматически.
float val_t = 25.0;                                          //   Температура калибровочных жидкостей.
                                                             //
void setup(){                                                //
     delay(500);                                             // * Ждём завершение переходных процессов связанных с подачей питания.
     Serial.begin(9600);                                     //   Инициируем работу с шиной UART для передачи данных в монитор последовательного порта на скорости 9600 бит/сек.
     tds.begin(&sWire);                                      //   Инициируем работу с TDS/EC-метром, указав ссылку на объект для работы с шиной I2C на которой находится модуль (по умолчанию &Wire).
     tds.set_t(val_t);                                       //   Указываем температуру жидкости в °С.
     Serial.print("ОПУСТИТЕ ДАТЧИК В 1 РАСТВОР");            //
     Serial.print(" (500 ppm). \r\n");                       //
     delay(60000);                                           //   Ждём 1 минуту.
     Serial.print("КАЛИБРОВКА...\r\n");                      //
     tds.setCalibration(1, 500);                             //   Выполняем 1 стадию калибровки указав известную концентрацию 1 раствора (в примере 500ppm ).
     while(tds.getCalibration()==1){delay(500);}             //   Ждём завершения 1 стадии калибровки...
     Serial.print("СПОЛОСНИТЕ ДАТЧИК.\r\n");                 //
     delay(30000);                                           //   Ждём 30 секунд.
     Serial.print("ОПУСТИТЕ ДАТЧИК В 2 РАСТВОР");            //
     Serial.print(" (1500 ppm). \r\n");                      //
     delay(60000);                                           //   Ждём 1 минуту.
     Serial.print("КАЛИБРОВКА...\r\n");                      //
     tds.setCalibration(2, 1500);                            //   Выполняем 2 стадию калибровки указав известную концентрацию 2 раствора (в примере 1500ppm ).
     while(tds.getCalibration()==2){delay(500);}             //   Ждём завершения 2 стадии калибровки...
     Serial.print("КАЛИБРОВКА ВЫПОЛНЕНА ");                  //
     bool f = tds.getCalibration();                          //   Получаем результат калибровки.
     Serial.print((f==3)?"С ОШИБКОЙ":"УСПЕШНО");             //
     Serial.print("\r\n-------------------\r\n");            //
}                                                            //
                                                             //
void loop(){                                                 //
     Serial.print("TDS=");                                   //
     Serial.print(tds.getTDS() );                            //   Выводим количество растворённых твёрдых веществ в жидкости.
     Serial.print("мг/л, EC=");                              //
     Serial.print(tds.getEC() );                             //   Выводим удельную электропроводность приведённую к опорной температуре.
     Serial.print("мСм/см.\r\n");                            //
     delay(1000);                                            //
}                                                            //