#include <iostream>
using namespace std;

/* ===================== 1.7 ХРЕСТИКИ-НУЛИКИ ===================== */

class TicTacToe {
    char board[3][3];
    char player;

public:
    TicTacToe() {
        player = 'X';
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                board[i][j] = '.';
    }

    void print() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++)
                cout << board[i][j] << " ";
            cout << endl;
        }
    }

    bool move(int x, int y) {
        x--;
        y--;

        if (x < 0 || x > 2 || y < 0 || y > 2) return false;
        if (board[x][y] != '.') return false;

        board[x][y] = player;
        player = (player == 'X') ? 'O' : 'X';
        return true;
    }

    bool checkWin() {
        for (int i = 0; i < 3; i++)
            if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != '.')
                return true;

        for (int i = 0; i < 3; i++)
            if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != '.')
                return true;

        if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != '.')
            return true;

        if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != '.')
            return true;

        return false;
    }
    bool isDraw() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '.')
                    return false;
            }
        }
        return true;
    }

    char getPlayer() {
        return player;
    }
    
};

/* ===================== 2.7 ВЕКТОР ===================== */

class Vec3 {
    double v[3];
    int state;
    static int count;

public:
    Vec3() {
        v[0] = v[1] = v[2] = 0;
        state = 0;
        count++;
    }

    Vec3(double val) {
        v[0] = v[1] = v[2] = val;
        state = 0;
        count++;
    }

    Vec3(double* arr) {
        if (arr == nullptr) {
            v[0] = v[1] = v[2] = 0;
            state = -1;
        }
        else {
            for (int i = 0; i < 3; i++)
                v[i] = arr[i];
            state = 0;
        }
        count++;
    }

    ~Vec3() {
        count--;
        cout << "Vec destroyed, state = " << state << endl;
    }

    void set(int i, double val = 0) {
        if (i >= 0 && i < 3) v[i] = val;
        else state = -1;
    }

    double get(int i) {
        if (i >= 0 && i < 3) return v[i];
        state = -1;
        return 0;
    }

    void print() {
        cout << "[" << v[0] << ", " << v[1] << ", " << v[2] << "] state=" << state << endl;
    }

    Vec3 add(Vec3& b) {
        Vec3 res;
        for (int i = 0; i < 3; i++)
            res.v[i] = v[i] + b.v[i];
        return res;
    }

    Vec3 sub(Vec3& b) {
        Vec3 res;
        for (int i = 0; i < 3; i++)
            res.v[i] = v[i] - b.v[i];
        return res;
    }

    Vec3 cross(Vec3& b) {
        Vec3 res;
        res.v[0] = v[1] * b.v[2] - v[2] * b.v[1];
        res.v[1] = v[2] * b.v[0] - v[0] * b.v[2];
        res.v[2] = v[0] * b.v[1] - v[1] * b.v[0];
        return res;
    }

    Vec3 div(short k) {
        Vec3 res;
        if (k == 0) {
            res.state = -2;
            cout << "Division by zero!\n";
            return *this;
        }
        for (int i = 0; i < 3; i++)
            res.v[i] = v[i] / k;
        return res;
    }

    bool less(Vec3& b) {
        return v[0] < b.v[0] && v[1] < b.v[1] && v[2] < b.v[2];
    }

    static int getCount() { return count; }
};

int Vec3::count = 0;

int main() {

    int choice;

    do {
        cout << "\n===== MENU =====\n";
        cout << "1 - Tic Tac Toe\n";
        cout << "2 - Vector\n";
        cout << "0 - Exit\n";
        cout << "Choose: ";
        cin >> choice;

        switch (choice) {

        case 1: {
            TicTacToe game;
            int x, y;

            while (true) {
                game.print();
                cout << "Enter move (1-3 1-3): ";
                cin >> x >> y;

                if (!game.move(x, y)) {
                    cout << "Invalid move!\n";
                    continue;
                }

                if (game.checkWin()) {
                    game.print();
                    cout << "WIN!\n";
                    break;
                }
                else if (game.isDraw()) {
                    game.print();
                    cout << "DRAW!\n";
                    break;
                }
            }
            break;
        }

        case 2: {
            double arr[3];
            cout << "Enter 3 values: ";
            for (int i = 0; i < 3; i++)
                cin >> arr[i];

            Vec3 v1(arr);
            Vec3 v2(2.0);

            cout << "v1: "; v1.print();
            cout << "v2: "; v2.print();

            Vec3 v3 = v1.add(v2);
            cout << "Add: "; v3.print();

            Vec3 v4 = v1.sub(v2);
            cout << "Sub: "; v4.print();

            Vec3 v5 = v1.cross(v2);
            cout << "Cross: "; v5.print();

            Vec3 v6 = v1.div(2);
            cout << "Div: "; v6.print();

            cout << "Objects: " << Vec3::getCount() << endl;

            break;
        }

        case 0:
            cout << "Exit...\n";
            break;

        default:
            cout << "Wrong choice!\n";
        }

    } while (choice != 0);

    return 0;
}