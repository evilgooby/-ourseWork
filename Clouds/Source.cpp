#include <iostream>
#include <cstdlib>
#include <ctime>

const int BOARD_SIZE = 8;

// Структура для представления облака
struct Cloud {
    int width;
    int height;
    Cloud() : width(0), height(0) {} // Конструктор по умолчанию
    Cloud(int w, int h) : width(w), height(h) {}
};
// Структура для представления игровой доски
struct Board {
    char grid[BOARD_SIZE][BOARD_SIZE];
    Cloud clouds[4]; // Два облака размером 2x2 и два облака размером 3x2
    int rowCounts[BOARD_SIZE];
    int colCounts[BOARD_SIZE];
    int remainingCloudCells; // Количество оставшихся клеток с облаками

    // Конструктор для инициализации доски
    Board() : remainingCloudCells(0) {
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                grid[i][j] = '.';
            }
            rowCounts[i] = 0;
            colCounts[i] = 0;
        }
        // Инициализация облаков
        clouds[0] = Cloud(2, 2);
        clouds[1] = Cloud(2, 2);
        clouds[2] = Cloud(3, 2);
        clouds[3] = Cloud(3, 2);

        // Размещение облаков на доске
        placeClouds();
    }

    // Отображение текущего состояния доски
    void display() {
        // Выводим номера столбцов
        std::cout << "   ";
        for (int j = 0; j < BOARD_SIZE; ++j) {
            std::cout << j << ' ';
        }
        std::cout << std::endl;

        for (int i = 0; i < BOARD_SIZE; ++i) {
            // Выводим номер строки
            std::cout << i << " |";
            for (int j = 0; j < BOARD_SIZE; ++j) {
                std::cout << grid[i][j] << ' ';
            }
            // Выводим количество занятых клеток в строке
            std::cout << "| " << rowCounts[i] << std::endl;
        }

        // Выводим подчеркивание
        for (int j = 0; j < BOARD_SIZE * 2 + 5; ++j) {
            std::cout << '-';
        }
        std::cout << std::endl;

        // Выводим количество занятых клеток в столбцах
        std::cout << "   ";
        for (int j = 0; j < BOARD_SIZE; ++j) {
            std::cout << colCounts[j] << ' ';
        }
        std::cout << std::endl << std::endl;
    }

    // Рекурсивная функция для отгадывания облаков
    void guessCloudsRecursive() {
       

        int guessX, guessY;
        std::cin >> guessX;

        if (guessX == -1) {
            std::cout << "Игра завершена. Спасибо за игру!" << std::endl;
            return; // Пользователь завершил ввод
        }

        std::cin >> guessY;

        if (guessX >= 0 && guessX < BOARD_SIZE && guessY >= 0 && guessY < BOARD_SIZE) {
            std::cout << "Эта клетка " << (grid[guessX][guessY] == 'C' ? "занята" : "свободна") << ". Попробуйте еще раз." << std::endl;

            // Проверяем, угадано ли облако в текущей клетке
            if (grid[guessX][guessY] == 'C') {
                std::cout << "Вы угадали клетку с облаком!" << std::endl;
                remainingCloudCells--;

                // Проверяем, остались ли еще неугаданные клетки с облаками
                if (remainingCloudCells == 0) {
                    std::cout << "Поздравляем! Вы угадали все клетки с облаками. Игра завершена." << std::endl;
                    return;
                }
            }

            // Рекурсивный вызов для следующей попытки
            guessCloudsRecursive();
        }
        else {
            std::cout << "Некорректные координаты. Попробуйте еще раз." << std::endl;

            // Рекурсивный вызов для текущей попытки
            guessCloudsRecursive();
        }
    }

    // Проверка, можно ли разместить облако в указанной позиции
    bool canPlaceCloud(int x, int y, const Cloud& cloud) {
        // Проверка, не касается ли облако другого облака краями
        for (int i = x - 1; i < x + cloud.width + 1; ++i) {
            for (int j = y - 1; j < y + cloud.height + 1; ++j) {
                if (i >= 0 && i < BOARD_SIZE && j >= 0 && j < BOARD_SIZE) {
                    if (grid[i][j] == 'C') {
                        return false; // Облако касается другого облака
                    }
                }
            }
        }
        return true;
    }

    // Размещение облака в указанной позиции
    void placeCloud(int x, int y, const Cloud& cloud) {
        for (int i = x; i < x + cloud.width; ++i) {
            for (int j = y; j < y + cloud.height; ++j) {
                grid[i][j] = 'C';
                // Обновляем количество занятых клеток в строке и столбце
                rowCounts[i]++;
                colCounts[j]++;
                remainingCloudCells++;
            }
        }
    }

    // Генерация случайных координат для размещения облака
    void generateCloudPosition(int& x, int& y) {
        x = rand() % (BOARD_SIZE - 1);
        y = rand() % (BOARD_SIZE - 1);
    }

    // Размещение облаков на доске
    void placeClouds() {
        for (int i = 0; i < 4; ++i) {
            int x, y;
            do {
                generateCloudPosition(x, y);
            } while (!canPlaceCloud(x, y, clouds[i]));

            placeCloud(x, y, clouds[i]);
        }
    }
};

int main() {
    setlocale(LC_ALL, "rus");
    // Инициализация генератора случайных чисел
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Создание игровой доски
    Board gameBoard;

    // Отображение текущего состояния доски
    gameBoard.display();

    std::cout << "Отгадайте, где находятся облака." << std::endl;
    std::cout << "Введите координаты клетки (x y) или -1 чтобы закончить: ";

    // Пользователь отгадывает облака рекурсивным методом
    gameBoard.guessCloudsRecursive();

    return 0;
}
