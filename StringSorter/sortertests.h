#ifndef SORTERTESTS_H
#define SORTERTESTS_H

#include <iostream>
#include <fstream>
#include <string>
#include "sorter.h"
#include <cstdint>

// Функция фуззинга
extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    try {
        // Преобразуем данные в строку
        std::string input(reinterpret_cast<const char*>(data), size);
        RunProjectWithInput(input);  // Передаем данные в проект
    } catch (...) {
        // Ловим любые исключения для предотвращения крашей тестера
        std::cerr << "Exception caught!" << std::endl;
    }

    return 0;  // Успешное завершение
}

#endif // SORTERTESTS_H

