﻿# Пример вывода на экран LCD бегущей строки

Для 1986ВЕ93 необходимо подключаться к Jtag_A, поскольку один из выводов Jtag_B конфликтует с одним из сигналов LCD. Поэтому в MDR32F9Qx_config.h файле, скопированном из библиотеки в локальный прокт должно быть выставлено USE_JtagA. Без этого экран не работает. Либо можно закомментировать оба определения USE_JtagA и USE_JtagB.