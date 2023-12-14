#include <iostream>
#include <array>
#include <csignal>
#include <getopt.h>
#include <cstring>
#include <fstream>
#include <unistd.h>
//#include "Field.cpp"
#include "Gardener.cpp"

int main(int argc, char *argv[]) {
    // Запрашиваем размеры поля у пользователя
    int M, N;
    std::cout << "Введите размеры поля M x N (два положительных целых числа, разделенные пробелом):" << std::endl;
    std::cin >> M >> N;

    FieldSize field_size(M, N);
    Field my_field(field_size); // создаем поле
    my_field.placeObstacles(); // расставляем препятствия

    double speed_first, speed_second; // скорости первого и второго садовников

    std::cout << "Введите скорости (квадратов в секунду), с которыми будут работать садовники (2 положительных рациональных числа, разделенные пробелом):" << std::endl;
    std::cin >> speed_first >> speed_second;

    int step_duration_first = 1000000 / speed_first; // длительность шага соответствующего садовника
    int step_duration_second = 1000000 / speed_second;

    Gardener first_gardener(Point(0, N - 1), Point(0, 0),
                            RIGHT, DOWN, LEFT,
                            &my_field, step_duration_first); // создаем садовников
    Gardener second_gardener(Point(M - 1, 0), Point(0, 0),
                             UP, LEFT, DOWN,
                             &my_field, step_duration_second);

    pthread_create(&(tid[0]), nullptr, startGardening, &first_gardener); // запускаем садовников в разных потоках
    pthread_create(&(tid[1]), nullptr, startGardening, &second_gardener);

    while (!first_gardener.haveFinished || !second_gardener.haveFinished) {
        my_field.printField(first_gardener.current_location, second_gardener.current_location);
        std::cout << "\033[2J\033[1;1H";
        //std::cout << std::endl;
        usleep(std::min(step_duration_first, step_duration_second));
    }

    pthread_join(tid[0], nullptr);
    pthread_join(tid[1], nullptr);

    return 0;
}
