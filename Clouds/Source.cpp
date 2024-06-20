#include <iostream>
#include <cstdlib>
#include <ctime>

const int BOARD_SIZE = 8;

struct Cloud {
    int width;
    int height;
    Cloud() : width(0), height(0) {}
    Cloud(int w, int h) : width(w), height(h) {}
};

struct Board {
    char grid[BOARD_SIZE][BOARD_SIZE];
    Cloud clouds[4];
    int rowCounts[BOARD_SIZE];
    int colCounts[BOARD_SIZE];
    int remainingCloudCells;


    Board() : remainingCloudCells(0) {
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                grid[i][j] = '.';
            }
            rowCounts[i] = 0;
            colCounts[i] = 0;
        }

        clouds[0] = Cloud(2, 2);
        clouds[1] = Cloud(2, 2);
        clouds[2] = Cloud(3, 2);
        clouds[3] = Cloud(3, 2);


        placeClouds();
    }


    void display() {

        std::cout << "   ";
        for (int j = 0; j < BOARD_SIZE; ++j) {
            std::cout << j << ' ';
        }
        std::cout << std::endl;

        for (int i = 0; i < BOARD_SIZE; ++i) {

            std::cout << i << " |";
            for (int j = 0; j < BOARD_SIZE; ++j) {
                std::cout << grid[i][j] << ' ';
            }

            std::cout << "| " << rowCounts[i] << std::endl;
        }


        for (int j = 0; j < BOARD_SIZE * 2 + 5; ++j) {
            std::cout << '-';
        }
        std::cout << std::endl;


        std::cout << "   ";
        for (int j = 0; j < BOARD_SIZE; ++j) {
            std::cout << colCounts[j] << ' ';
        }
        std::cout << std::endl << std::endl;
    }

    void guessCloudsRecursive() {
       

        int guessX, guessY;
        std::cin >> guessX;

        if (guessX == -1) {
            std::cout << "���� ���������. ������� �� ����!" << std::endl;
            return;
        }

        std::cin >> guessY;

        if (guessX >= 0 && guessX < BOARD_SIZE && guessY >= 0 && guessY < BOARD_SIZE) {
            std::cout << "��� ������ " << (grid[guessX][guessY] == 'C' ? "������" : "��������") << ". ���������� ��� ���." << std::endl;

            // ���������, ������� �� ������ � ������� ������
            if (grid[guessX][guessY] == 'C') {
                std::cout << "�� ������� ������ � �������!" << std::endl;
                remainingCloudCells--;

                // ���������, �������� �� ��� ����������� ������ � ��������
                if (remainingCloudCells == 0) {
                    std::cout << "�����������! �� ������� ��� ������ � ��������. ���� ���������." << std::endl;
                    return;
                }
            }

            // ����������� ����� ��� ��������� �������
            guessCloudsRecursive();
        }
        else {
            std::cout << "������������ ����������. ���������� ��� ���." << std::endl;

            // ����������� ����� ��� ������� �������
            guessCloudsRecursive();
        }
    }

    // ��������, ����� �� ���������� ������ � ��������� �������
    bool canPlaceCloud(int x, int y, const Cloud& cloud) {
        // ��������, �� �������� �� ������ ������� ������ ������
        for (int i = x - 1; i < x + cloud.width + 1; ++i) {
            for (int j = y - 1; j < y + cloud.height + 1; ++j) {
                if (i >= 0 && i < BOARD_SIZE && j >= 0 && j < BOARD_SIZE) {
                    if (grid[i][j] == 'C') {
                        return false; // ������ �������� ������� ������
                    }
                }
            }
        }
        return true;
    }

    // ���������� ������ � ��������� �������
    void placeCloud(int x, int y, const Cloud& cloud) {
        for (int i = x; i < x + cloud.width; ++i) {
            for (int j = y; j < y + cloud.height; ++j) {
                grid[i][j] = 'C';
                // ��������� ���������� ������� ������ � ������ � �������
                rowCounts[i]++;
                colCounts[j]++;
                remainingCloudCells++;
            }
        }
    }

    // ��������� ��������� ��������� ��� ���������� ������
    void generateCloudPosition(int& x, int& y) {
        x = rand() % (BOARD_SIZE - 1);
        y = rand() % (BOARD_SIZE - 1);
    }

    // ���������� ������� �� �����
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
    // ������������� ���������� ��������� �����
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // �������� ������� �����
    Board gameBoard;

    // ����������� �������� ��������� �����
    gameBoard.display();

    std::cout << "���������, ��� ��������� ������." << std::endl;
    std::cout << "������� ���������� ������ (x y) ��� -1 ����� ���������: ";

    // ������������ ���������� ������ ����������� �������
    gameBoard.guessCloudsRecursive();

    return 0;
}
