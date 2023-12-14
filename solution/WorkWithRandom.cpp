#include <iostream>
#include <pthread.h>
#include <unistd.h>

// Функция для работы в случайном режиме
void WorkWithRandom() {
    // Генерация случайных размеров поля (M и N от 2 до 20)
    int M = std::rand() % 19 + 2; 
    int N = std::rand() % 19 + 2;

    FieldSize field_size(M, N);
    Field my_field(field_size); // создаем поле
    my_field.placeObstacles(); // расставляем препятствия

    // Генерация случайных скоростей для садовников (от 1 до 10)
    double speed_first = std::rand() % 10 + 1; 
    double speed_second = std::rand() % 10 + 1;

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
        std::cout << "\033[2J\033[1;1H"; // Очистка экрана в консоли
        my_field.printField(first_gardener.current_location, second_gardener.current_location);
        usleep(std::min(step_duration_first, step_duration_second));
    }

    // Ожидание завершения работы садовников
    pthread_join(tid[0], nullptr);
    pthread_join(tid[1], nullptr);
}
