#include <iostream>
#include <array>
#include <csignal>
#include <getopt.h>
#include <cstring>
#include <fstream>
#include <unistd.h>
#include "Gardener.cpp"
#include "WorkWithFile.cpp"
#include "WorkWithConsole.cpp"
#include "WorkWithRandom.cpp"

int main(int argc, char *argv[]) {
    char option = 'c';  // По умолчанию выбран режим работы с консолью
    if (argc >= 2) {
        option = argv[1][1];  // Если передан аргумент, используем его как опцию
    }

    switch (option) {
        case 'f': {
            // Режим работы с файлами
            if (argc < 4) {
                std::cerr << "Недостаточно аргументов для -f. Использование: " << argv[0] << " -f <input_file> <output_file>" << std::endl;
                return 1;
            }

            // Извлекаем имена файлов из аргументов
            std::string inputFileName = argv[2];
            std::string outputFileName = argv[3];

            // Вызываем функцию для работы с файлами
            WorkWithFile(inputFileName, outputFileName);
            break;
        }
        case 'r':
            // Режим работы с случайными значениями
            WorkWithRandom();
            break;
        case 'c':
            // Режим работы с консолью (по умолчанию)
            WorkWithConsole();
            break;
        default:
            std::cerr << "Неизвестная опция: " << option << std::endl;
            return 1;
    }
    return 0;
}
