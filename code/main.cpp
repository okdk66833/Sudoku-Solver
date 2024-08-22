#include <cstdio>
#include <windows.h>

int board[10][10];
int displayPath[81][2], voidCount, lvl = 1;

void scan() {
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            scanf("%d", &board[i][j]);
        }
    }
}

bool is_valid(int x, int y, int value) {
    if (board[x][y] != 0) return false;

    for (int tmp = 1; tmp <= 9; tmp++)
        if (value == board[x][tmp] || value == board[tmp][y]) return false;

    int x_s = (x - 1) / 3 * 3 + 1;
    int y_s = 3 * ((y + 2) / 3 - 1) + 1;
    for (int ch_x = x_s; ch_x < x_s + 3; ch_x++)
        for (int ch_y = y_s; ch_y < y_s + 3; ch_y++)
            if (ch_x != x && ch_y != y && value == board[ch_x][ch_y]) return false;
    return true;
}

bool find(int& x, int& y) {
    for (x = 1; x <= 9; x++) {
        for (y = 1; y <= 9; y++) {
            if (board[x][y] == 0) {
                return true;
            }
        }
    }
    return false;
}

bool solve() {
    int x, y;
    if (!find(x, y)) return true;
    for (int cand = 1; cand <= 9; cand++) {
        if (is_valid(x, y, cand)) {
            board[x][y] = cand;
            if (solve()) return true;
            board[x][y] = 0;
        }
    }
    return false;
}

void print() {
    printf("\n┌─────┬─────┬─────┐\n");
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            printf("%c%d", ((j == 1 || j == 4 || j == 7) ? '|' : ' '), board[i][j]);
            if (j == 9) printf("│");
        }
        if (i == 3 || i == 6)
            printf("\n├─────┼─────┼─────┤");
        printf("\n");
    }
    printf("└─────┴─────┴─────┘");
}

void display_menu() {
    system("cls");
    printf("┌───────────────┐\n");
    printf("│ SuDoKu Solver │\n");
    printf("└───────────────┘\n");

    if (lvl == 1) {
        printf("\n1단계\n빈자리를 0으로 표시한 스도쿠 퍼즐을 입력하세요.\n\n");
        scan();
    }
    else if (lvl == 2) {
        printf("\n2단계\n스도쿠를 푸는 중 입니다...\n");
        solve();
    }
    else if (lvl == 3) {
        printf("\n완료!\n");
        print();
    }
}

int main() {
    for (lvl = 1; lvl <= 3; lvl++) {
        display_menu();
        if (lvl != 2)getchar();
    }
    getchar();
    getchar();
}
