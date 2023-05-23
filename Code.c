#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Функция для вывода правил игры
void print_rules() {
    printf("\n%s\n", "\x1B[1;33;22mПРАВИЛА ИГРЫ\n\x1B[0;37;40m");
    printf("%s\n", "Загадан код, состоящий из нескольких цифр. Игрок по очереди отгадывает их без права на\nошибку."
    "При этом можно задавать следующие вопросы, получая ответы да/нет:");
    printf("%s\n", ">x - вопрос : Цифра больше х?\n<x - вопрос : Цифра меньше х?\n=x - вопрос : Цифра равна х?"
    "\n~x - вопрос : Цифра четная?\n!x - утверждение : попытка вести цифру х (если не верно, то проиграл)");
    printf("------------------------------------------------------------------------------------");
    printf("\n\x1B[1;33;22mСПИСОК КОМАНД:\n\x1B[0;37;40m");
    printf("\nhelp    - Вывести список команд\n");
    printf("play    - Начать игру\n");
    printf("restart - Начать игру сначала\n");
    printf("exit    - Выйти из игры\n");
    printf("------------------------------------------------------------------------------------\n");
}

// Функция для отображения заставки
void display_title(const int* guessedCode, int codeLength) {
    printf("------------------------------------------------------------------------------------\n");
    printf("                                                                        _____        \n");
    printf("| /  ___    ___       ___  ___   ___     _    _    _ _  _    _       __|_____|__         \n");
    printf("|/  |   |  |   |     |   |  |      /    / \\   |\\  /| | /    / \\     |-----------|    \n");
    printf("|\\  |   | _|___|_    |   |  |      \\   /___\\  | \\/ | |{    /___\\    | |?||?||?| |  "
    "\n", guessedCode[0], guessedCode[1], guessedCode[2]);
    printf("| \\ |___| |     |    |___|  |     __\\ /     \\ |    | | \\_ /     \\   |-----------|   \n");
    printf("                                                                    |___________|          \n");
    printf("------------------------------------------------------------------------------------\n");
}

// Основная функция
int main() {
    int codeLength = 3;         // Длина кодапо умолчанию 
    int secretCode[5];          // Максимальная длинна кода
    int guess;                  // Попытка игрока
    char sign;                  // Знак (> < =)
    char command[10];           // Команда игрока
    int countingNum;            // Отображаемая позиция отгадываемой цифры
    int guessedCode[5] = { -1, -1, -1, -1, -1 }; // Массив для хранения угаданных цифр

    display_title(secretCode, codeLength);
    printf("\nДобро пожаловать в игру 'Отгадай код от замка'!\n");
    print_rules();

    srand(time(NULL));          // Инициализация генератора случайных чисел

    while (1) {
        printf("\nВведите команду ('help' для списка команд): ");
        scanf("%s", command);

        if (strcmp(command, "help") == 0) {
            printf("\n\x1B[1;33;22mСПИСОК КОМАНД:\n\x1B[0;37;40m");
            printf(" help    - Вывести список команд\n");
            printf(" play    - Начать игру\n");
            printf(" restart - Начать игру сначала\n");
            printf(" exit - Выйти из игры\n");
        } else if (strcmp(command, "play") == 0) {
            printf("\x1B[1;33;22mИГРА НАЧАЛАСЬ!\n\x1B[0;37;40m");
            printf("Введите длину кода (от 3 до 5): ");
            scanf("%d", &codeLength);
        if (codeLength < 3 || codeLength > 5) {
            printf("Неправильная длина кода. Установлено значение по умолчанию (3).\n");
            codeLength = 3;
}
        // Генерируем загаданный код
        for (int i = 0; i < codeLength; i++) {
            secretCode[i] = rand() % 10;
            printf("%i ", secretCode[i]);
        }

         int position = 0; // Текущая позиция цифры для угадывания
        countingNum = 1;   // Цифра #(1,2,3 и тд.)

        while (position < codeLength) {
            printf("\n\x1B[1;33;22mЦифра #%i\x1B[0;37;40m", countingNum);
            printf("\nВведите знак (> < = ~ ! и цифру (0-9), или команду: ");
            scanf(" %s", command);

            if (strcmp(command, "help") == 0) {
                printf("\n\x1B[1;33;22mСПИСОК КОМАНД:\n\x1B[0;37;40m");
                printf("  help    - Вывести список команд\n");
                printf("  restart - Начать игру сначала\n");
                printf("  exit    - Выйти из игры\n");
                continue;
            } else if (strcmp(command, "restart") == 0) {
                printf("\x1B[1;33;22mИгра будет начата сначала.\n\x1B[0;37;40m\n");
                break;
            } else if (strcmp(command, "exit") == 0) {
                printf("\x1B[1;33;22mСпасибо за игру! До свидания!\\n\x1B[0;37;40m\n");
                return 0;
            }

            if (strlen(command) != 2 || strchr("><=!~", command[0]) == NULL || !isdigit(command[1])) {
                printf("Неправильный ввод. Введите знак (> < =) и цифру (0-9), или команду.\n");
                continue;
            }

            sign = command[0];          // символ
            guess = command[1] - '0';   // число

            if (guess < 0 || guess > 9) {
                printf("Неправильный ввод. Цифра должна быть от 0 до 9.\n");
                continue;
            }

            int success = 0;    // Флаг, указывающий, успешно ли угадана цифра

            if (sign == '>') {
                if (guess > secretCode[position]) {
                    printf("Цифра больше, чем загаданная.\n");
                } else {
                    printf("Цифра меньше, чем загаданная.\n");
                }
            } else if (sign == '<') {
                if (guess < secretCode[position]) {
                    printf("Цифра меньше, чем загаданная.\n");
} else {
printf("Цифра больше, чем загаданная.\n");
}
} else if (sign == '=') {
if (guess == secretCode[position]) {
printf("Цифра равна загаданной.\n");
} else {
printf("Цифра не равна загаданной.\n");
}
} else if (sign == '~') {
if (guess != 2) {
printf("После ~ должна быть 2!\n");
} else if (guess == 2 && secretCode[position] % 2 == 0) {
printf("Загаданное число четное.\n");
} else if (guess == 2 && secretCode[position] % 2 != 0) {
printf("Загаданное число нечетное.\n");
}
} else if (sign == '!') {
if (guess == secretCode[position]) {
success = 1;
countingNum++;
} else {
printf("Цифра не равна загаданной.\n");
printf("Вы не угадали, игра окончена!\nGAME OVER =(");
break;
}
} else {
printf("Неправильный знак. Используйте только > < = ~ или !.\n");
}
            if (success) {
                printf("Вы угадали цифру!\n");
                position++;
            }

// Обновляем интерфейс после каждой угаданной цифры
            printf("\n\x1B[1;33;22mЗамок:\n\x1B[0;37;40m");
            for (int i = 0; i < codeLength; i++) {
                if (guessedCode[i] != -1) {
                    printf("%i ", guessedCode[i]);
                } else {
                    printf("? ");
                }
            }

        }

        if (position == codeLength) {
            printf("\x1B[1;33;22mПоздравляю! Вы угадали код от замка!\x1B[0;37;40m\n");
        }
    } else if (strcmp(command, "restart") == 0) {
        printf("\x1B[1;33;22mИгра будет начата сначала.\n\x1B[0;37;40m\n");
    } else if (strcmp(command, "exit") == 0) {
        printf("\x1B[1;33;22mСпасибо за игру! До свидания!\n\x1B[0;37;40m\n");
        break;
    } else {
        printf("Неизвестная команда. Пожалуйста, введите правильную команду.\n");
    }
}

return 0;
}