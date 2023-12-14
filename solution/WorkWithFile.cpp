#include <iostream>
#include <fstream>
#include <cstring>
#include <pthread.h>
#include <unistd.h>

// Функция для работы с файлами
int WorkWithFile(const std::string& inputFileName, const std::string& outputFileName) {
    // Открытие потоков для входного и выходного файлов
    std::ifstream in_stream(inputFileName);
    std::ofstream out_stream(outputFileName);

    // Проверка успешного открытия входного файла
    if (!in_stream.is_open()) {
        std::cout << "Не удалось открыть файл: " << inputFileName << std::endl;
        return 1; // Возврат с кодом ошибки
    }

    int M, N;
    double speed_first, speed_second; // скорости первого и второго садовников

    // Чтение размеров поля и скоростей из файла
    in_stream >> M >> N;
    in_stream >> speed_first >> speed_second;

    FieldSize field_size(M, N);
    Field my_field(field_size); // создаем поле
    my_field.placeObstacles(); // расставляем препятствия

    int step_duration_first = 1000000 / speed_first; // длительность шага соответствующего садовника
    int step_duration_second = 1000000 / speed_second;

    // Создание и настройка садовников
    Gardener first_gardener(Point(0, N - 1), Point(0, 0),
                            RIGHT, DOWN, LEFT,
                            &my_field, step_duration_first);
    Gardener second_gardener(Point(M - 1, 0), Point(0, 0),
                             UP, LEFT, DOWN,
                             &my_field, step_duration_second);

    // Запуск садовников в разных потоках
    pthread_create(&(tid[0]), nullptr, startGardening, &first_gardener);
    pthread_create(&(tid[1]), nullptr, startGardening, &second_gardener);

    // Основной цикл до завершения работы садовников
    while (!first_gardener.haveFinished || !second_gardener.haveFinished) {
        my_field.printField(out_stream); // Запись в файл
        std::cout << "\033[2J\033[1;1H"; // Очистка экрана в консоли
        my_field.printField(first_gardener.current_location, second_gardener.current_location);
        out_stream << std::endl; // Разделитель для записи в файл
        usleep(std::min(step_duration_first, step_duration_second));
    }

    // Ожидание завершения работы садовников
    pthread_join(tid[0], nullptr);
    pthread_join(tid[1], nullptr);

    // Закрытие потоков файлов
    in_stream.close();
    out_stream.close();

    return 0;
}
