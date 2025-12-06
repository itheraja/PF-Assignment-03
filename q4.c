#include <stdio.h>
#include <string.h>

struct Book {
    int id;
    int popularity;
    int lastAccessTime;
};

struct Shelf {
    struct Book books[100];
    int count;
    int capacity;
    int timeCounter;
};

void initShelf(struct Shelf *shelf, int capacity) {
    shelf->count = 0;
    shelf->capacity = capacity;
    shelf->timeCounter = 0;
}

int findBook(struct Shelf *shelf, int id) {
    for (int i = 0; i < shelf->count; i++) {
        if (shelf->books[i].id == id) {
            return i;
        }
    }
    return -1;
}

int findLRU(struct Shelf *shelf) {
    int lruIndex = 0;
    for (int i = 1; i < shelf->count; i++) {
        if (shelf->books[i].lastAccessTime < shelf->books[lruIndex].lastAccessTime) {
            lruIndex = i;
        }
    }
    return lruIndex;
}

void addBook(struct Shelf *shelf, int id, int popularity) {
    int index = findBook(shelf, id);

    if (index != -1) {
        shelf->books[index].popularity = popularity;
        shelf->books[index].lastAccessTime = shelf->timeCounter++;
        return;
    }

    if (shelf->count == shelf->capacity) {
        int lruIndex = findLRU(shelf);
        for (int i = lruIndex; i < shelf->count - 1; i++) {
            shelf->books[i] = shelf->books[i + 1];
        }
        shelf->count--;
    }

    shelf->books[shelf->count].id = id;
    shelf->books[shelf->count].popularity = popularity;
    shelf->books[shelf->count].lastAccessTime = shelf->timeCounter++;
    shelf->count++;
}

int accessBook(struct Shelf *shelf, int id) {
    int index = findBook(shelf, id);

    if (index == -1) {
        return -1;
    }

    shelf->books[index].lastAccessTime = shelf->timeCounter++;
    return shelf->books[index].popularity;
}

int main() {
    struct Shelf shelf;
    int capacity, Q;

    printf("Enter capacity and number of operations: ");
    scanf("%d %d", &capacity, &Q);

    initShelf(&shelf, capacity);

    for (int i = 0; i < Q; i++) {
        char operation[10];
        scanf("%s", operation);

        if (strcmp(operation, "ADD") == 0) {
            int id, popularity;
            scanf("%d %d", &id, &popularity);
            addBook(&shelf, id, popularity);
        } else if (strcmp(operation, "ACCESS") == 0) {
            int id;
            scanf("%d", &id);
            printf("%d\n", accessBook(&shelf, id));
        }
    }

    return 0;
}
