#include <iostream>

using namespace std;
int total_count = 0;
int middle_value = 0;

void roll_dice(int dice, string result = "", int min_value = 1) {
    if (dice == 0) {
        int suma = 0;
        for (int i = 0; i < result.length(); i++)
            suma += result[i] -'0';
        if (suma == middle_value)
            total_count++;
    } else {
        for (int i = min_value; i <= 6; i++)
            roll_dice(dice - 1, result + to_string(i), i);
    }
}

int main() {
    int lim = 35;
    for (int number_dice = 2; number_dice <= lim; number_dice++) {
        total_count = 0;
        middle_value = ((7 * number_dice) + (number_dice % 2)) / 2;
        roll_dice(number_dice);
        cout << number_dice << "," << total_count << endl;
    }
    return 0;
}