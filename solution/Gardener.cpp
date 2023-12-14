#include <iostream>
#include <csignal>
#include <getopt.h>
#include <cstring>
#include <fstream>
#include <unistd.h>
#include <pthread.h>
#include "Field.cpp"

class Gardener {
public:
    Point current_location; // текущее местоположение садовника
    bool haveFinished = false; // флаг, который сигнализирует о том, что садовник достиг финального квадрата

    void move() { // садовник делает ход
        (*field).garden(step_duration, current_location);
        if (current_location == ending_point) { // если обошли все квадраты, то останавливаемся
            haveFinished = true;
            return;
        }
        if (!checkIfTheWayIsBlocked()) { // если подошли к краю, то идем в другое направление
            moveInDirection(current_direction);
        } else {
            moveInDirection(direction_when_blocked);
            if (current_direction == first_direction) { // меняем стороны в которые идут садовники на противоположные
                current_direction = second_direction;
            } else {
                current_direction = first_direction;
            }
        }
    }

    Gardener(Point starting_point, Point ending_point, direction first_direction,
             direction direction_when_blocked, direction second_direction,
             Field *field, int step_duration) {
        this->current_location = starting_point;
        this->ending_point = ending_point;
        this->first_direction = first_direction;
        this->second_direction = second_direction;
        this->current_direction = first_direction;
        this->direction_when_blocked = direction_when_blocked;
        this->field = field;
        this->step_duration = step_duration;
    }

private:
    Point ending_point; // точка, в которой садовник окажется, когда обойдет все квадраты
    direction first_direction; // сначала идем в этом направлении
    direction second_direction; // когда дошли до края и развернулись, идем в этом направлении, потом меняем обратно
    direction current_direction; // текущее направление
    direction direction_when_blocked; // идем в этом направлении, когда подошли к краю
    Field *field; // указатель на поле сада
    int step_duration; // длительность того, сколько занимает прохождение по необрабатываемому квадрату, обрабатывание квадрата x2 от step_duration

    bool checkIfTheWayIsBlocked() { // проверяем, подошли ли к краю
        int current_x = current_location.x;
        int current_y = current_location.y;

        if (current_direction == RIGHT && current_x == field->getSize().M - 1 ||
            current_direction == UP && current_y == field->getSize().N - 1 ||
            current_direction == LEFT && current_x == 0 ||
            current_direction == DOWN && current_y == 0) {
            return true;
        }

        return false;
    }

    void moveInDirection(direction direction) { // двигаемся в нужном направлении
        int new_x = current_location.x;
        int new_y = current_location.y;

        switch (direction) {
            case UP:
                new_y += 1;
                break;
            case DOWN:
                new_y -= 1;
                break;
            case LEFT:
                new_x -= 1;
                break;
            case RIGHT:
                new_x += 1;
                break;
        }

        pthread_mutex_lock(&mutex);
        while ((*field).getCell(Point(new_x, new_y)) == BEING_GARDENED) {
            printf(""); // ждем, пока освободится, чтобы пройти
        }
        pthread_mutex_unlock(&mutex);

        current_location.x = new_x;
        current_location.y = new_y;
    }
};

static void *startGardening(void *arg) { // запускаем садовника
    while (!(*(Gardener *) arg).haveFinished) {
        (*(Gardener *) arg).move();
    }
    return nullptr;
}
