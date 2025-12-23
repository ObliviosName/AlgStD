#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1024
#define COLOR_DOUBLE "\033[1;32m"   // Зелёный цвет для double
#define COLOR_RESET  "\033[0m"      // Сброс цвета

// Проверка, является ли слово ключевым словом double
int is_double_keyword(const char* word) {
    return strcmp(word, "double") == 0;
}

// Обработка строки: вывод с подсветкой слова double
void process_line(const char* line) {
    char word[MAX_LINE_LENGTH];
    int in_comment = 0;   // Флаг однострочного комментария //
    int in_string = 0;   // Флаг строки в кавычках
    int i = 0;

    while (line[i] != '\0') {

        // начало однострочного комментария //
        if (!in_string && line[i] == '/' && line[i + 1] == '/') {
            in_comment = 1;
        }

        // переключение состояния строки
        if (!in_comment && line[i] == '\"') {
            in_string = !in_string;
            putchar(line[i]);
            i++;
            continue;
        }

        // если не в комментарии и не в строке – ищем слова
        if (!in_comment && !in_string && (isalpha((unsigned char)line[i]) || line[i] == '_')) {
            int j = 0;
            // собираем слово: буквы, цифры, подчёркивания
            while (isalnum((unsigned char)line[i]) || line[i] == '_') {
                word[j++] = line[i++];
            }
            word[j] = '\0';

            if (is_double_keyword(word)) {
                printf("%s%s%s", COLOR_DOUBLE, word, COLOR_RESET);
            }
            else {
                printf("%s", word);
            }
        }
        else {
            // обычный символ
            putchar(line[i]);
            i++;
        }

        // конец комментария — при переходе на новую строку
        if (in_comment && line[i] == '\n') {
            in_comment = 0;
        }
    }
}

int lab1_main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Использование: %s <имя_файла>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE* file = fopen(argv[1], "r");
    if (!file) {
        perror("Ошибка открытия файла");
        return EXIT_FAILURE;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        process_line(line);
    }

    fclose(file);
    return EXIT_SUCCESS;
}
