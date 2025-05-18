#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
using namespace std;

const int SIZE = 9;
const int CELL_SIZE = 60;
vector<vector<int>> board = {
    {0, 0, 0, 2, 6, 0, 7, 0, 1},
    {6, 8, 0, 0, 7, 0, 0, 9, 0},
    {1, 9, 0, 0, 0, 4, 5, 0, 0},
    {8, 2, 0, 1, 0, 0, 0, 4, 0},
    {0, 0, 4, 6, 0, 2, 9, 0, 0},
    {0, 5, 0, 0, 0, 3, 0, 2, 8},
    {0, 0, 9, 3, 0, 0, 0, 7, 4},
    {0, 4, 0, 0, 5, 0, 0, 3, 6},
    {7, 0, 3, 0, 1, 8, 0, 0, 0}
};

vector<vector<int>> original = board; // keep track of locked cells

bool isSafe(vector<vector<int>>& mat, int row, int col, int num) {
    for(int i = 0; i < SIZE; i++) {
        if(mat[row][i] == num || mat[i][col] == num) return false;
    }
    int rowStart = row - row % 3, colStart = col - col % 3;
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(mat[i + rowStart][j + colStart] == num) return false;
    return true;
}

bool solveSudoku(vector<vector<int>>& mat, int row = 0, int col = 0) {
    if(row == SIZE - 1 && col == SIZE) return true;
    if(col == SIZE) {
        row++;
        col = 0;
    }
    if(mat[row][col] != 0)
        return solveSudoku(mat, row, col + 1);
    for(int num = 1; num <= SIZE; num++) {
        if(isSafe(mat, row, col, num)) {
            mat[row][col] = num;
            if(solveSudoku(mat, row, col + 1)) return true;
            mat[row][col] = 0;
        }
    }
    return false;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(CELL_SIZE * SIZE, CELL_SIZE * SIZE), "Sudoku Game");
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) return -1;

    int selectedRow = -1, selectedCol = -1;

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::MouseButtonPressed) {
                int x = event.mouseButton.x / CELL_SIZE;
                int y = event.mouseButton.y / CELL_SIZE;
                if(original[y][x] == 0) {
                    selectedCol = x;
                    selectedRow = y;
                }
            }

            if(event.type == sf::Event::KeyPressed && selectedRow != -1 && selectedCol != -1) {
                if(event.key.code >= sf::Keyboard::Num1 && event.key.code <= sf::Keyboard::Num9) {
                    int num = event.key.code - sf::Keyboard::Num0;
                    if(isSafe(board, selectedRow, selectedCol, num)) {
                        board[selectedRow][selectedCol] = num;
                    }
                }
                if(event.key.code == sf::Keyboard::Backspace) {
                    board[selectedRow][selectedCol] = 0;
                }
                if(event.key.code == sf::Keyboard::Enter) {
                    solveSudoku(board);
                }
            }
        }

        window.clear(sf::Color::White);

        // Draw grid
        for(int i = 0; i <= SIZE; i++) {
            sf::RectangleShape line(sf::Vector2f(CELL_SIZE * SIZE, (i % 3 == 0) ? 3 : 1));
            line.setPosition(0, i * CELL_SIZE);
            line.setFillColor(sf::Color::Black);
            window.draw(line);

            line.setSize(sf::Vector2f((i % 3 == 0) ? 3 : 1, CELL_SIZE * SIZE));
            line.setPosition(i * CELL_SIZE, 0);
            window.draw(line);
        }

        // Draw numbers
        for(int i = 0; i < SIZE; i++) {
            for(int j = 0; j < SIZE; j++) {
                if(board[i][j] != 0) {
                    sf::Text text;
                    text.setFont(font);
                    text.setString(to_string(board[i][j]));
                    text.setCharacterSize(30);
                    text.setFillColor((original[i][j] != 0) ? sf::Color::Black : sf::Color::Blue);
                    text.setPosition(j * CELL_SIZE + 20, i * CELL_SIZE + 10);
                    window.draw(text);
                }
            }
        }

        window.display();
    }

    return 0;
}
