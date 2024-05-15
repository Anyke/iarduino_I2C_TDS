//	Библиотека для работы с Trema модулем TDS/EC-метр, I2C-flash для Arduino: https://iarduino.ru/shop/Sensory-Datchiki/solemer-tds-ec-flash-i2c.html
//  Версия: 1.3.1
//  Последнюю версию библиотеки Вы можете скачать по ссылке: https://iarduino.ru/file/556.html
//  Подробное описание функций бибилиотеки доступно по ссылке: https://wiki.iarduino.ru/page/TDS-EC-i2c/
//  Библиотека является собственностью интернет магазина iarduino.ru и может свободно использоваться и распространяться!
//  При публикации устройств или скетчей с использованием данной библиотеки, как целиком, так и её частей,
//  в том числе и в некоммерческих целях, просим Вас опубликовать ссылку: http://iarduino.ru
//  Автор библиотеки: Панькин Павел.
//  Если у Вас возникли технические вопросы, напишите нам: shop@iarduino.ru

#ifndef iarduino_I2C_TDS_h																						//
#define iarduino_I2C_TDS_h																						//
																												//
#if defined(ARDUINO) && (ARDUINO >= 100)																		//
#include		<Arduino.h>																						//
#else																											//
#include		<WProgram.h>																					//
#endif																											//
																												//
#include	"iarduino_I2C_TDS_I2C.h"																			//	Подключаем библиотеку выбора реализации шины I2C.
																												//
#if defined(TwoWire_h) || defined(__ARDUINO_WIRE_IMPLEMENTATION__) || defined(__AVR_ATmega328__) || defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1284P__) || defined(__AVR_ATmega2560__) || defined(ESP8266) || defined(ESP32) || defined(ARDUINO_ARCH_RP2040) || defined(RENESAS_CORTEX_M4) // Если подключена библиотека Wire или платы её поддерживают...
#include	<Wire.h>																							//	Разрешаем использовать библиотеку Wire в данной библиотеке.
#endif																											//
#if defined( iarduino_I2C_Software_h )																			//	Если библиотека iarduino_I2C_Software подключена в скетче...
#include	<iarduino_I2C_Software.h>																			//	Разрешаем использовать библиотеку iarduino_I2C_Software в данной библиотеке.
#endif																											//
																												//
#define			DEF_CHIP_ID_FLASH		0x3C																	//	ID линейки чипов - константа для всех чипов серии Flash (позволяет идентифицировать принадлежность чипа к серии).
#define			DEF_CHIP_ID_METRO		0xC3																	//	ID линейки чипов - константа для всех чипов серии Metro (позволяет идентифицировать принадлежность чипа к серии).
#define			DEF_MODEL_TDS			0x19																	//	Идентификатор модели - константа.
//				Адреса регистров модуля:																		//
#define			REG_FLAGS_0				0x00																	//	Адрес регистра флагов управления для чтения.
#define			REG_BITS_0				0x01																	//	Адрес регистра битов  управления для чтения и записи.
#define			REG_FLAGS_1				0x02																	//	Адрес регистра флагов управления для чтения.
#define			REG_BITS_1				0x03																	//	Адрес регистра битов  управления для чтения и записи.
#define			REG_MODEL				0x04																	//	Адрес регистра содержащего номер типа модуля.
#define			REG_VERSION				0x05																	//	Адрес регистра содержащего версию прошивки.
#define			REG_ADDRESS				0x06																	//	Адрес регистра содержащего текущий адрес модуля на шине I2C. Если адрес указан с флагом IF-PIN-ADDRES то адрес установится (и запишется в регистр) только при наличии 1 на входе PIN_ADDRES.
#define			REG_CHIP_ID				0x07																	//	Адрес регистра содержащего ID линейки чипов «Flash». По данному ID можно определить принадлежность чипа к линейки «Flash».
#define			REG_TDS_FREQUENCY_L		0x08																	//	Адрес регистра содержащего чатоту смены полярности от 50 Гц до 4 кГц (младший байт).
#define			REG_TDS_FREQUENCY_H		0x09																	//	Адрес регистра содержащего чатоту смены полярности от 50 Гц до 4 кГц (старший байт).
#define			REG_TDS_KNOWN_TDS		0x0A																	//	Адрес регистра получающего известное количество растворенных в воде примесей «TDS» в ppm = мг/л (два байта).
#define			REG_TDS_KNOWN_TDS_1		0x0C																	//	Адрес регистра содержащего значение которое копируется в «REG_TDS_KNOWN_TDS» при запуске 1 стадии калибровки вызванной нажатием кнопки (два байта).
#define			REG_TDS_KNOWN_TDS_2		0x0E																	//	Адрес регистра содержащего значение которое копируется в «REG_TDS_KNOWN_TDS» при запуске 2 стадии калибровки вызванной нажатием кнопки (два байта).
#define			REG_TDS_CALIBRATION		0x10																	//	Адрес регистра содержащего биты запуска калибровки датчика и определения температурного коэффициента жидкости.
#define			REG_TDS_Ka				0x11																	//	Адрес регистра содержащего множитель степенной функции «Ka» в десятых долях (три байта).
#define			REG_TDS_Kb				0x14																	//	Адрес регистра содержащего модуль степени функции «Kb» в тысчяных долях (два байта).
#define			REG_TDS_Kt				0x16																	//	Адрес регистра содержащего температурный коэффициент жидкости «Kt» в десятитысячных долях (два байта).
#define			REG_TDS_Kp				0x18																	//	Адрес регистра содержащего коэффициент пересчёта «Kp» для перевода EC (мкСм/см) в TDS (ppm) в сотых долях.
#define			REG_TDS_t				0x19																	//	Адрес регистра получающего температуру жидкости «t» в °С *4. (1 значение регистра = 0.25°С).
#define			REG_TDS_T				0x1A																	//	Адрес регистра содержащего опорную температуру  «T» в °С *4. (1 значение регистра = 0.25°С).
#define			REG_TDS_Ro				0x1B																	//	Адрес регистра содержащего общее измеренное сопротивление в Ом (три байта).
#define			REG_TDS_Vout			0x1E																	//	Адрес регистра содержащего напряжение на выходе ОУ в десятитысчяных долях В (два байта).
#define			REG_TDS_S				0x20																	//	Адрес регистра содержащего удельную электропроводность «S» в мкСм/см измеренную при текущей температуре t°C (два байта).
#define			REG_TDS_EC				0x22																	//	Адрес регистра содержащего удельную электропроводность «EC» в мкСм/см приведённую к опорной температуре T°С (два байта).
#define			REG_TDS_TDS				0x24																	//	Адрес регистра содержащего количество растворенных в воде примесей «TDS» в ppm = мг/л (два байта).
//				Позиция битов и флагов:																			//
#define			TDS_FLG_STATUS_2		0x80																	//	Флаг  регистра REG_TDS_CALIBRATION информирует о выполнении 2 стадии калибровки.
#define			TDS_FLG_STATUS_1		0x40																	//	Флаг  регистра REG_TDS_CALIBRATION информирует о выполнении 1 стадии калибровки.
#define			TDS_BIT_CALC_ERR		0x10																	//	Бит   регистра REG_TDS_CALIBRATION указывает на ошибку последней калибровки.
#define			TDS_BIT_CALC_2			0x02																	//	Бит   регистра REG_TDS_CALIBRATION указывает модулю выполнить 2 стадию калибровки.
#define			TDS_BIT_CALC_1			0x01																	//	Бит   регистра REG_TDS_CALIBRATION указывает модулю выполнить 1 стадию калибровки.
#define			TDS_BITS_CALC_INFO		0x0C																	//	Биты  регистра REG_TDS_CALIBRATION для ввода информации о ходе калибровки.
#define			TDS_CODE_CALC_SAVE		0x24																	//	Код   разрешения записи калибровочных данных.
																												//
class iarduino_I2C_TDS{																							//
	public:																										//
	/**	Конструктор класса **/																					//
		iarduino_I2C_TDS						(uint8_t address=0){											//	Конструктор класса														(Параметр: адрес модуля на шине I2C, если не указан (=0), то адрес будет определён).
													if(address>0x7F){ address>>=1; }							//	Корректируем адрес, если он указан с учётом бита RW.
							valAddrTemp			=	address;													//	Сохраняем переданный адрес модуля.
							selI2C				=	new iarduino_I2C_Select;									//	Переопределяем указатель selI2C на объект производного класса iarduino_I2C_Select.
		}																										//
	/**	Пользовательские функции **/																			//
		#if defined(TwoWire_h) || defined(__ARDUINO_WIRE_IMPLEMENTATION__)										//
		bool		begin					(TwoWire* i=&Wire ){ selI2C->begin(i); return _begin(); }			//	Определяем функцию инициализации модуля								(Параметр:  объект для работы с аппаратной шиной I2C).
		#endif																									//
		#if defined(iarduino_I2C_Software_h)																	//
		bool		begin					(SoftTwoWire* i   ){ selI2C->begin(i); return _begin(); }			//	Определяем функцию инициализации модуля								(Параметр:  объект для работы с программной шиной I2C).
		#endif																									//
		bool				reset				(void				);											//	Объявляем  функцию перезагрузки модуля									(Параметр:  отсутствует).
		bool				changeAddress		(uint8_t			);											//	Объявляем  функцию смены адреса модуля на шине I2C						(Параметр:  новый адрес модуля).
		uint8_t				getAddress			(void				){ return valAddr;	}						//	Определяем функцию возвращающую текущий адрес модуля на шине I2C		(Параметр:  отсутствует).
		uint8_t				getVersion			(void				){ return valVers;	}						//	Определяем функцию возвращающую текущую версию прошивки модуля			(Параметр:  отсутствует).
		bool				getPullI2C			(void				);											//	Объявляем  функцию возвращающую флаг наличия подтяжки шины I2C			(Параметр:  отсутствует).
		bool				setPullI2C			(bool=true			);											//	Объявляем  функцию установки    подтяжки шины I2C						(Параметр:  флаг подтяжки).
		uint16_t			getFrequency		(void				);											//	Объявляем  функцию получения    частоты переменного тока для измерений	(Параметр:  отсутствует).
		bool				setFrequency		(uint16_t			);											//	Объявляем  функцию установки    частоты переменного тока для измерений	(Параметр:  частота от 50 до 5000Гц).
		bool				setCalibration		(uint8_t, uint16_t	);											//	Объявляем  функцию запуска      калибровки модуля						(Параметры: стадия 1 или 2, концентрация калибровочной жидкости от 0 до 10000ppm).
		uint8_t				getCalibration		(uint8_t* info		);											//	Объявляем  функцию получения    текущей стадии калибровки модуля		(Параметр:  ссылка на получение дополнительной информации о калибровке).
		uint8_t				getCalibration		(void				){ uint8_t i; return getCalibration(&i); }	//	Определяем функцию получения    текущей стадии калибровки модуля		(Параметр:  отсутствует).
		uint16_t			getKnownTDS			(uint8_t			);											//	Объявляем  функцию получения    концентрации для калибр модуля с кнопки	(Параметр:  стадия 1 или 2).
		bool				setKnownTDS			(uint8_t, uint16_t	);											//	Объявляем  функцию установки    концентрации для калибр модуля с кнопки	(Параметр:  стадия 1 или 2, концентрация калибровочной жидкости от 0 до 10000ppm).
		float				getKa				(void				);											//	Объявляем  функцию получения    множителя степенной функции				(Параметр:  отсутствует).
		bool				setKa				(float				);											//	Объявляем  функцию установки    множителя степенной функции				(Параметр:  значение множителя от 0,1 до 1'677'721,5).
		float				getKb				(void				);											//	Объявляем  функцию получения    степени   степенной функции				(Параметр:  отсутствует).
		bool				setKb				(float				);											//	Объявляем  функцию установки    степени   степенной функции				(Параметр:  значение степени от -0,01 до -65,535).
		float				getKt				(void				);											//	Объявляем  функцию получения    температурного коэффициента жидкости	(Параметр:  отсутствует).
		bool				setKt				(float				);											//	Объявляем  функцию установки    температурного коэффициента жидкости	(Параметр:  температурный коэффициент от 0 до 6,5535).
		float				getKp				(void				);											//	Объявляем  функцию получения    коэффициента пересчёта					(Параметр:  отсутствует).
		bool				setKp				(float				);											//	Объявляем  функцию установки    коэффициента пересчёта					(Параметр:  коэффициент пересчёта от 0,01 до 2,55).
		bool				set_t				(float				);											//	Объявляем  функцию установки    реальной   температуры жидкости			(Параметр:  температура от 0 до 63,75 °С).
		float				get_T				(void				);											//	Объявляем  функцию получения    опорной    температуры жидкости			(Параметр:  отсутствует).
		bool				set_T				(float				);											//	Объявляем  функцию установки    опорной    температуры жидкости			(Параметр:  температура от 0 до 63,75 °С).
		uint32_t			getRo				(void				);											//	Объявляем  функцию получения    общего измеренного сопротивления		(Параметр:  отсутствует).
		float				getVout				(void				);											//	Объявляем  функцию получения    напряжения на выходе первого ОУ			(Параметр:  отсутствует).
		float				get_S				(void				);											//	Объявляем  функцию получения    измеренной  удельной электропроводности	(Параметр:  отсутствует).
		float				getEC				(void				);											//	Объявляем  функцию получения    приведённой удельной электропроводности	(Параметр:  отсутствует).
		uint16_t			getTDS				(void				);											//	Объявляем  функцию получения    количества растворённых твёрдых веществ	(Параметр:  отсутствует).
	private:																									//
	/**	Внутренние переменные **/																				//
		iarduino_I2C_VirtualSelect* selI2C;																		//	Объявляем  указатель  на  объект полиморфного класса iarduino_I2C_VirtualSelect, но в конструкторе текущего класса этому указателю будет присвоена ссылка на производный класс iarduino_I2C_Select.
		uint8_t				valAddrTemp			=	0;															//	Определяем переменную для хранения адреса модуля на шине I2C который был указан, но не был проверен.
		uint8_t				valAddr				=	0;															//	Определяем переменную для хранения адреса модуля на шине I2C.
		uint8_t				valVers				=	0;															//	Определяем переменную для хранения версии прошивки модуля.
		uint8_t				data[4];																			//	Объявляем  массив     для хранения получаемых/передаваемых данных.
	/**	Внутренние функции **/																					//
		bool				_begin				(void							);								//	Объявляем  функцию инициализации модуля									(Параметр:  отсутствует).
		bool				_readBytes			(uint8_t, uint8_t				);								//	Объявляем  функцию чтения данных в  массив  data						(Параметры: номер первого регистра, количество байт).
		bool				_writeBytes			(uint8_t, uint8_t, uint8_t=0	);								//	Объявляем  функцию записи данных из массива data						(Параметры: номер первого регистра, количество байт, номер первого элемента массива data).
};																												//
																												//
#endif																											//