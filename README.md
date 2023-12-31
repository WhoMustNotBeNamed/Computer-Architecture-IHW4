# Индивидуальное домашнее задание №4
## Евсюков Александр  <br/> Группа БПИ224  <br/> Вариант 21
## _Условие:_ 
Задача о нелюдимых садовниках. Имеется пустой участок земли (двумерный массив размером M ×N) и план сада, разбитого на
отдельные квадраты. От 10 до 30 процентов (задается случайно)
площади сада заняты прудами или камнями. То есть недоступны
для ухаживания. Эти квадраты располагаются на плане произвольным (случайным) образом. Ухаживание за садом выполняют два
садовника, которые не хотят встречаться друг другом (то есть, одновременно появляться в одном и том же квадрате). Первый садовник начинает работу с верхнего левого угла сада и перемещается
слева направо, сделав ряд, он спускается вниз и идет в обратном
направлении, пропуская обработанные участки. Второй садовник
начинает работу с нижнего правого угла сада и перемещается снизу
вверх, сделав ряд, он перемещается влево и также идет в обратную
сторону. Если садовник видит, что участок сада уже обработан другим садовником или является необрабатываемым, он идет дальше.
Если по пути какой-то участок занят другим садовником, то садовник ожидает когда участок освободится, чтобы пройти дальше на
доступный ему необработанный участок. Садовники должны работать одновременно со скоростями, определяемыми как параметры задачи. Прохождение через любой квадрат занимает некоторое время, которое задается константой, меньшей чем времена
обработки и принимается за единицу времени. Создать многопоточное приложение, моделирующее работу садовников. Каждый садовник — это отдельный поток.

## _Решение:_
_Модель параллельных вычислений:_

Имеется трёхпоточная программа, где первый и второй потоки имитируют работу садовников, а третий является основным, контролирующим. В основном потоке выполняются следующие действия: создание объектов для представления сада и садовников, ввод параметров программы, запуск первого и второго потоков, вывод сада на экран или в файл при обнаружении изменений в саде и завершение работы первых и вторых потоков. Для обеспечения согласованных действий между потоками используется мьютекс. Этот мьютекс запрещает двум потокам изменять состояние квадрата поля сада (из "необработанный" в "находится под обработкой") и одновременно считывать состояние квадрата, который может быть необработанным. Таким образом, обеспечивается выполнение требования, согласно которому, если один садовник обрабатывает квадрат, второй садовник ожидает завершения обработки этого квадрата первым садовником, прежде чем приступить к этому квадрату. Такой способ взаимодействия больше всего поход на модель "Управляющий и рабочие". 

_Обобщенный алгоритм:_ 

Есть класс Gardener, который моделирует деятельность садовника. Также имеется класс Field, представляющий сущность поля сада. Сначала создается объект поля field класса Field, затем, с использованием метода placeObstacles, случайные ячейки поля заполняются камнями или прудами в количестве от 10% до 30%. Затем создаются объекты first_gardener и second_gardener класса Gardener, представляющие первого и второго садовников. У них установлены соответствующие скорости, точки старта и направления движения. Далее создаются два потока, выполняющих функцию startGardening, с объектами садовников в качестве аргументов. Функция startGardening вызывает метод move у переданного садовника, пока флаг haveFinished садовника не станет положительным, что сигнализирует о завершении обхода всего поля.

В методе move сначала вызывается метод garden у объекта field, передавая длительность шага по квадрату и текущую локацию садовника. В методе garden устанавливается мьютекс, затем проверяется состояние квадрата. Если он необработанный, меняется на "находится под обработкой", мьютекс снимается, происходит задержка потока на двукратное время длительности шага, после чего состояние квадрата изменяется на "обработан". В случае необрабатываемого квадрата мьютекс разблокируется, и поток засыпает на время шага. Затем возвращаемся в метод move, где проверяется, является ли текущий квадрат конечным. Если да, устанавливается флаг haveFinished в true и выход из метода, иначе продолжается выполнение метода.

Далее проверяется, может ли садовник двигаться в своем обычном направлении или уперся в край поля с помощью метода checkIfTheWayIsBlocked. Если может, координаты садовника меняются методом moveInDirection, который в зависимости от переданного направления ходит в него, предварительно проверив, не является ли квадрат перед ним занятым. Перед проверкой включается мьютекс, чтобы избежать изменений состояния квадрата другим садовником. Если квадрат занят, садовник ожидает, пока он освободится, после чего мьютекс разблокируется, и происходит изменение координат садовника. Если садовник не может двигаться в том же направлении, он совершает движение в бок с помощью метода moveInDirection, изменяя направление движения на противоположное.

Метод move завершается, и мы возвращаемся в startGardening, который в зависимости от флага haveFinished либо вызывает move снова, либо выходит из startGardening. Параллельно с этим в основном потоке через промежутки равные длительности шага, выводится в консоль или в файл поле сада, пока у обоих садовников флаг haveFinished не станет true. После этого потоки останавливаются, и программа завершается.

_3 режима работы программы_:
* запуск через командную строку с флагом -f для чтения данных из файла и запись в файл. Пример:
    ```
    ./Computer-Architecture-IHW4 -f input.txt output.txt
    ```
    `Примечание: `
    1. Для запуска необходимо перейти в папку с собранной программой по адресу `build/solution`. Например, у меня это выглядит так: `alex@DESKTOP-R68N48Q:~/Computer-Architecture-IHW4/build/solution$`. 
    2. Файлы, которые мы собираемся читать, должны также находится в этой директории `build/solution`. 

* запуск через командную строку с флагом -r для работы со случайными значениями. Пример:
    ```
    ./Computer-Architecture-IHW4 -r
    ```
    `Примечание: `
    1. Для запуска необходимо перейти в папку с собранной программой по адресу `build/solution`. Например, у меня это выглядит так: `alex@DESKTOP-R68N48Q:~/Computer-Architecture-IHW4/build/solution$`. 
    2. После запуска вам будет предложено сохранить данные в файл. Для этого необходимо ввести название файла (например `output.txt`) или ввести `N`. После создания файл также будет находится в директории `build/solution`.

* запуск через командную строку с флагом -с для работы с консолью, который также является режимом работы по умолчанию (стандартный запуск из среды разработки без использования терминала). Пример:
    ```
    ./Computer-Architecture-IHW4 -с
    ```
    `Примечание: `
    1. Для запуска необходимо перейти в папку с собранной программой по адресу `build/solution`. Например, у меня это выглядит так: `alex@DESKTOP-R68N48Q:~/Computer-Architecture-IHW4/build/solution$`. 
    2. После запуска вам будет предложено сохранить данные в файл. Для этого необходимо ввести название файла (например `output.txt`) или ввести `N`. После создания файл также будет находится в директории `build/solution`.

## _Пример работы программы:_
`Примечание`: на такой вывод меня вдохновил Легалов Александр Иванович с его генерацией илюстрации к задаче, сгенерированной Кандинским, а также опыт создания игры "Змейка" на первом курсе с помощью С#) ![Alt text](screenshots/kandinsky-download-1702721904045.png)
Инфонмацию об окрашивании консоли взял со статьи на хабр: https://habr.com/ru/companies/macloud/articles/558316/

_Пример:_
![Alt text](screenshots/image1.png)
![Alt text](screenshots/image6.png)
![Alt text](screenshots/image2.png)
![Alt text](screenshots/image3.png)
![Alt text](screenshots/image4.png)
![Alt text](screenshots/image5.png)



## _Текст программы:_
В качестве примера представлен файл `main.cpp` и `WorkWithConsole.cpp`. Остальные файлы вы можете найти в папке `solution`.

main:
``` cpp
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
```

WorkWithConsole.cpp
``` cpp
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
```
