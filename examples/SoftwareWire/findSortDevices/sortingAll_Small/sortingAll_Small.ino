// ДАННЫЙ ПРИМЕР СОРТИРУЕТ АДРЕСА МОДУЛЕЙ ЛИНЕЙКИ FLASH I2C.                // * Строки со звёздочкой являются необязательными.
// Требуется установить библиотеку <iarduino_I2C_Software.h>                //   https://iarduino.ru/file/627.html
// Требуется установить библиотеку <iarduino_I2C_Address.h>                 //   https://iarduino.ru/file/558.html
//                                                                          //
// Допускается нахождение на шине модулей Flash I2C с одинаковыми адресами. //
// Допускается нахождение на шине сторонних устройств I2C.                  //
//                                                                          //
// - Пример sortingAll_Small только сортирует устройства.                   //
// - Пример sortingAll_Big   сортирует устройства и выводит информацию о них//
                                                                            //
const uint8_t start = 0x20;                                                 //   Определяем первый адрес из списка создаваемых адресов для модулей Flash I2C.
                                                                            //
#include <iarduino_I2C_Software.h>                                          //   Подключаем библиотеку для работы с программной шиной I2C, до подключения библиотеки iarduino_I2C_Address.
SoftTwoWire sWire(3,4);                                                     //   Создаём объект программной шины I2C указав выводы которым будет назначена роль линий: SDA, SCL.
                                                                            //
#include <iarduino_I2C_Address.h>                                           //   Подключаем библиотеку для работы с адресами модулей линейки I2C-flash.
iarduino_I2C_SortAddress all;                                               //   Объявляем  объект (all) для сортировки адресов.
                                                                            //
void setup(){                                                               //
     delay(500);                                                            // * Ждём завершение переходных процессов связанных с подачей питания.
     Serial.begin(9600);                                                    //   Инициируем передачу данных в монитор последовательного порта на скорости 9600 бит/сек.
     while(!Serial){;}                                                      // * Ждём завершения инициализации шины UART.
                                                                            //
     Serial.println( F("-----------------") );                              // *
                                                                            //
//   Выполняем сортировку адресов:                                          //
     Serial.print( F("Сортировка... ") );                                   // *
     all.begin(&sWire); // &Wire, &Wire1, &Wire2 ...                        //   Функция begin() принимает ссылку на объект для работы с шиной I2C на которой требуется произвести сортировку адресов.
     if( all.sorting(start) ){ Serial.println( F("выполнено!"  ) ); }       //   Функция sorting() сортирует адреса всех устройств iarduino по порядку начиная с указанного адреса.
     else                    { Serial.println( F("не требуется") ); }       //   Функция sorting() возвращает true при успехе или false если возникла ошибка.
                                                                            //
}                                                                           //
                                                                            //
void loop(){                                                                //
}                                                                           //