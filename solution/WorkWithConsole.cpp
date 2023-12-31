#include <iostream>
#include <pthread.h>
#include <unistd.h>

void WorkWithConsole() {
    // Запрос размеров поля у пользователя
    int M, N;
    std::cout << "Введите размеры поля M x N (два положительных целых числа, разделенные пробелом):" << std::endl;
    std::cin >> M >> N;

    // Создание и настройка поля
    FieldSize field_size(M, N);
    Field my_field(field_size); // создаем поле
    my_field.placeObstacles(); // расставляем препятствия

    // Запрос скоростей работы садовников
    double speed_first, speed_second; // скорости первого и второго садовников
    std::cout << "Введите скорости (квадратов в секунду), с которыми будут работать садовники (2 положительных рациональных числа, разделенные пробелом):" << std::endl;
    std::cin >> speed_first >> speed_second;

    // Расчет длительности шага для каждого садовника
    int step_duration_first = 1000000 / speed_first; // длительность шага соответствующего садовника
    int step_duration_second = 1000000 / speed_second;

    // Создание садовников
    Gardener first_gardener(Point(0, N - 1), Point(0, 0),
                            RIGHT, DOWN, LEFT,
                            &my_field, step_duration_first);
    Gardener second_gardener(Point(M - 1, 0), Point(0, 0),
                             UP, LEFT, DOWN,
                             &my_field, step_duration_second);

    // Запуск садовников в разных потоках
    pthread_create(&(tid[0]), nullptr, startGardening, &first_gardener);
    pthread_create(&(tid[1]), nullptr, startGardening, &second_gardener);

    // Сохранение в файл по желанию пользователя
    std::string outputFileRandom= "";
    std::cout << "Если желаете сохранить результат в файл, введите его название (например 'output.txt'). В противном случае введите N" << std::endl;
    std::cin >> outputFileRandom;
    std::ofstream out_stream; 
    if (outputFileRandom != "N") {
        out_stream.open(outputFileRandom); 
    }

    // Основной цикл до завершения работы садовников
    while (!first_gardener.haveFinished || !second_gardener.haveFinished) {
        std::cout << "\033[2J\033[1;1H"; // Очистка экрана (для красивого вывода)
        if (outputFileRandom != "N") {  // Сохранение в файл, если пользователь согласен
            my_field.printField(out_stream); 
            out_stream << std::endl;
        }
        my_field.printField(first_gardener.current_location, second_gardener.current_location);
        usleep(std::min(step_duration_first, step_duration_second));
    }

    if (outputFileRandom != "N") {
        out_stream.close();
    }

    // Ожидание завершения работы садовников
    pthread_join(tid[0], nullptr);
    pthread_join(tid[1], nullptr);
}
