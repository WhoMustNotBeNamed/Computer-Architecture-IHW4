#include <iostream>
#include <vector>
#include <csignal>
#include <getopt.h>
#include <cstring>
#include <fstream>
#include <unistd.h>
#include <pthread.h>

pthread_t tid[2];
pthread_mutex_t mutex; // мьютекс, который будет использоваться для синхронизации потоков

struct Point { //структура точка, для обозначения координат на которых расположены садовники и объекты на поле сада
    int x;
    int y;

    Point(int x, int y) : x(x), y(y) {}

    explicit Point() : x(0), y(0) {}

    bool operator==(const Point &right) const {
        return x == right.x && y == right.y;
    }
};

struct FieldSize {
    int M;
    int N;

    FieldSize(int m, int n) : M(m), N(n) {}
};

enum direction { // направления, в которых садовники могут совершать движения
    UP,
    DOWN,
    LEFT,
    RIGHT
};

enum cell { // типы квадратов
    NOT_GARDENED, // неухоженный квадрат сада, но доступный для ухаживания
    GARDENED, // уже ухоженный квадрат сада
    ROCK, // камень
    POND, // пруд
    BEING_GARDENED // квадрат, за которым в данный момент ухаживает садовник
};

class Field { // поле сада
public:
    Field(FieldSize size) : size_(size) {
        field_.resize(size.M, std::vector<cell>(size.N, NOT_GARDENED));
    }

    void placeObstacles() { // создаем нужное количество препятствий на поле
        srand(time(nullptr));
        int amount = rand() % ((size_.N*size_.M)*10)/100 +
                                ((size_.N*size_.M)*20)/100; // количество объектов - случайное число от 10 до 30, так как размер поля 100, а требуется заполнить препятствиями от 10% до 30%
        for (int i = 0; i < amount; ++i) {
            int random_obstacle = rand() % 2; // случайное число 0 или 1, если 0 то камни, иначе - пруд
            cell new_cell; // новое препятствие
            if (random_obstacle == 0) {
                new_cell = ROCK;
            } else {
                new_cell = POND;
            }
            int random_x, random_y; // случайные координаты, в которых будет располагаться препятствие
            do {
                random_x = rand() % size_.M;
                random_y = rand() % size_.N;
            } while (field_[random_x][random_y] != NOT_GARDENED);
            Point new_location(random_x, random_y); // создаем точку с выбранными случайными координатами
            setCell(new_location, new_cell); // ставим препятствие в эту точку
        }
    }

    void garden(int step_duration, Point currentSquare) { // садовник ухаживает за квадратом
        pthread_mutex_lock(&mutex);
        if (getCell(currentSquare) == NOT_GARDENED) {
            setCell(currentSquare, BEING_GARDENED);
            pthread_mutex_unlock(&mutex);
            usleep(step_duration * 2);
            setCell(currentSquare, GARDENED);
        } else {
            pthread_mutex_unlock(&mutex);
            usleep(step_duration);
        }
    }

    void printField(std::ofstream &output) { // выводим поле в файл
        for (int i = size_.N - 1; i >= 0; --i) {
            for (int j = 0; j < size_.M; ++j) {
                Point current(j, i);
                pickColor(current, output);
            }
            output << std::endl;
        }
    }

    void printField(Point first_gardener_location, Point second_gardener_location) { // выводим поле в консоль
        for (int i = size_.N - 1; i >= 0; --i) {
            for (int j = 0; j < size_.M; ++j) {
                Point current(j, i);
                if (current == first_gardener_location && current == second_gardener_location) {
                    pickColor(current, "43");
                } else if (current == first_gardener_location) {
                    pickColor(current, "102");
                } else if (current == second_gardener_location) {
                    pickColor(current, "102");
                } else {
                    pickColor(current, "42");
                }
            }
            std::cout << std::endl;
        }
    }

    cell getCell(Point point) {
        return field_[point.x][point.y];
    }

    void setCell(Point point, cell value) {
        field_[point.x][point.y] = value;
    }

    FieldSize getSize() const {
        return size_;
    }

private:
    FieldSize size_;

    std::vector<std::vector<cell>> field_; // поле сада

    void pickColor(Point current,
                   std::ofstream &output) { // выводим квадрат в файл с фоном нужного цвета, в зависимости от того есть ли на нем садовники
        switch (getCell(current)) {
            case NOT_GARDENED:
                output << "\xF0\x9F\x8D\x82";
                break;
            case GARDENED:
                output << "  ";
                break;
            case ROCK:
                output << "\xF0\x9F\x8C\x91";
                break;
            case POND:
                output << "\xF0\x9F\x94\xB5";
                break;
            case BEING_GARDENED:
                output << "\xF0\x9F\x91\xB7";
                break;
        }
    }

    void pickColor(Point current, const std::string &color) { // выводим квадрат в консоль с фоном нужного цвета, в зависимости от того есть ли на нем садовники
        switch (getCell(current)) {
            case NOT_GARDENED:
                std::cout << "\033[" + color + "m\xF0\x9F\x8D\x82\033[m";
                break;
            case GARDENED:
                std::cout << "\033[" + color + "m  \033[m";
                break;
            case ROCK:
                std::cout << "\033[" + color + "m\xF0\x9F\x8C\x91\033[m";
                break;
            case POND:
                std::cout << "\033[" + color + "m\xF0\x9F\x94\xB5\033[m";
                break;
            case BEING_GARDENED:
                std::cout << "\033[" + color + "m\xF0\x9F\x91\xB7\033[m";
                break;
        }
    }
};
