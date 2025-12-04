#include <stdio.h>
#include <string.h>

// Book structure
struct Book {
    int id;
    int popularity;
    int lastAccessTime;  // To track least recently used
};

// Shelf structure
struct Shelf {
    struct Book books[100];
    int count;
    int capacity;
    int timeCounter;  // To track access order
};

// Initialize the shelf
void initShelf(struct Shelf *shelf, int capacity) {
    shelf->count = 0;
    shelf->capacity = capacity;
    shelf->timeCounter = 0;
}

// Find book by ID
int findBook(struct Shelf *shelf, int id) {
    for (int i = 0; i < shelf->count; i++) {
        if (shelf->books[i].id == id) {
            return i;
        }
    }
    return -1;  // Not found
}

// Find least recently accessed book
int findLRU(struct Shelf *shelf) {
    int lruIndex = 0;
    for (int i = 1; i < shelf->count; i++) {
        if (shelf->books[i].lastAccessTime < shelf->books[lruIndex].lastAccessTime) {
            lruIndex = i;
        }
    }
    return lruIndex;
}

// Add a book to the shelf
void addBook(struct Shelf *shelf, int id, int popularity) {
    int index = findBook(shelf, id);
    
    // Book already exists, update popularity
    if (index != -1) {
        shelf->books[index].popularity = popularity;
        shelf->books[index].lastAccessTime = shelf->timeCounter++;
        return;
    }
    
    // Shelf is full, remove LRU book
    if (shelf->count == shelf->capacity) {
        int lruIndex = findLRU(shelf);
        
        // Shift books to remove LRU
        for (int i = lruIndex; i < shelf->count - 1; i++) {
            shelf->books[i] = shelf->books[i + 1];
        }
        shelf->count--;
    }
    
    // Add new book
    shelf->books[shelf->count].id = id;
    shelf->books[shelf->count].popularity = popularity;
    shelf->books[shelf->count].lastAccessTime = shelf->timeCounter++;
    shelf->count++;
}

// Access a book
int accessBook(struct Shelf *shelf, int id) {
    int index = findBook(shelf, id);
    
    if (index == -1) {
        return -1;  // Book not found
    }
    
    // Update last access time
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
        } 
        else if (strcmp(operation, "ACCESS") == 0) {
            int id;
            scanf("%d", &id);
            int result = accessBook(&shelf, id);
            printf("%d\n", result);
        }
    }
    
    return 0;
}

/* 
Sample Input:
2 5
ADD 101 50
ADD 102 30
ACCESS 101
ADD 103 40
ACCESS 102

Expected Output:
50
-1
*/
