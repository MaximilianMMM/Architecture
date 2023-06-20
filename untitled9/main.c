#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 50

typedef struct {
    char name[MAX_NAME_LENGTH];
} Architect;

typedef struct {
    char name[MAX_NAME_LENGTH];
    Architect architect;
} Monument;

void createFile() {
    FILE *file = fopen("monuments.dat", "wb");
    if (file == NULL) {
        printf("Помилка при створенні файлу.\n");
        return;
    }
    fclose(file);
    printf("Файл створено успішно.\n");
}

void openFile() {
    FILE *file = fopen("monuments.dat", "rb");
    if (file == NULL) {
        printf("Файлу з такою назвою не існує.\n");
        return;
    }
    fclose(file);
    printf("Файл відкрито успішно.\n");
}

void closeFile() {
    FILE *file = fopen("monuments.dat", "rb");
    if (file == NULL) {
        printf("Файлу з такою назвою не існує.\n");
        return;
    }
    fclose(file);
    printf("Файл закрито успішно.\n");
}

void viewFileContent() {
    FILE *file = fopen("monuments.dat", "rb");
    if (file == NULL) {
        printf("Файлу з такою назвою не існує.\n");
        return;
    }

    Monument monument;
    while (fread(&monument, sizeof(Monument), 1, file)) {
        printf("Пам'ятка: %s\n", monument.name);
        printf("Архітектор: %s\n", monument.architect.name);
        printf("--------------------\n");
    }

    fclose(file);
}

void addMonument() {
    FILE *file = fopen("monuments.dat", "ab");
    if (file == NULL) {
        printf("Файлу з такою назвою не існує.\n");
        return;
    }

    Monument monument;
    printf("Введіть назву пам'ятки: ");
    fgets(monument.name, MAX_NAME_LENGTH, stdin);
    monument.name[strlen(monument.name) - 1] = '\0'; // Видаляємо символ нового рядка

    printf("Введіть ім'я архітектора: ");
    fgets(monument.architect.name, MAX_NAME_LENGTH, stdin);
    monument.architect.name[strlen(monument.architect.name) - 1] = '\0'; // Видаляємо символ нового рядка

    fwrite(&monument, sizeof(Monument), 1, file);
    fclose(file);
    printf("Пам'ятку додано успішно.\n");
}

void searchByArchitect() {
    char searchName[MAX_NAME_LENGTH];
    printf("Введіть ім'я архітектора: ");
    fgets(searchName, MAX_NAME_LENGTH, stdin);
    searchName[strlen(searchName) - 1] = '\0'; // Видаляємо символ нового рядка

    FILE *file = fopen("monuments.dat", "rb");
    if (file == NULL) {
        printf("Файлу з такою назвою не існує.\n");
        return;
    }

    Monument monument;
    int found = 0;
    while (fread(&monument, sizeof(Monument), 1, file)) {
        if (strcmp(monument.architect.name, searchName) == 0) {
            printf("Пам'ятка: %s\n", monument.name);
            printf("Архітектор: %s\n", monument.architect.name);
            printf("--------------------\n");
            found = 1;
        }
    }

    fclose(file);

    if (!found) {
        printf("Пам'ятки з архітектором %s не знайдено.\n", searchName);
    }
}

int main() {
    int choice;
    while (1) {
        printf("\nМеню:\n");
        printf("1. Створити файл\n");
        printf("2. Відкрити файл\n");
        printf("3. Закрити файл\n");
        printf("4. Переглянути вміст файлу\n");
        printf("5. Додати пам'ятку архітектури\n");
        printf("6. Пошук пам'яток за архітектором\n");
        printf("7. Вийти з програми\n");
        printf("Оберіть дію: ");
        scanf("%d", &choice);
        getchar(); // Очищуємо буфер введення

        switch (choice) {
            case 1:
                createFile();
                break;
            case 2:
                openFile();
                break;
            case 3:
                closeFile();
                break;
            case 4:
                viewFileContent();
                break;
            case 5:
                addMonument();
                break;
            case 6:
                searchByArchitect();
                break;
            case 7:
                printf("До побачення!\n");
                return 0;
            default:
                printf("Невірний вибір. Спробуйте ще раз.\n");
        }
    }

    return 0;
}
