// cl main.c /Zi /nologo

#include <stdio.h>
#include <stdlib.h>

#define GB (1024 * 1024 * 1024) // 1 gigabyte

/*
---------- Arena ----------
Hello, 0World!0000000000000
^       ^      ^
str     str2   offset
*/

typedef struct {
    unsigned char *data;
    size_t length;
    size_t offset;
} Arena;

Arena ArenaAlloc(size_t sz) {
    unsigned char *memory = malloc(sz);
    Arena arena = {
        .data = memory,
        .length = sz,
        .offset = 0
    };
    return arena;
}

void *ArenaPush(Arena *a, size_t sz) {
    if(a->offset+sz <= a->length) {
        void *p = &a->data[a->offset];
        a->offset += sz;
        memset(p, 0, sz);
        return p;
    }   
    printf("Game over, man. Game over!"); // Handle out of memory.
    return NULL;
}  

int main() {
  
    Arena arena = ArenaAlloc(GB);

    char *str = ArenaPush(&arena, 8 * sizeof(char));
    memcpy(str, "Hello, ", 7);
    str[7] = '\0';
    
    char *str2 = ArenaPush(&arena, 7 * sizeof(char));
    memcpy(str2, "World!", 6);
    str2[6] = '\0';
    
    printf("%s%s", str, str2);

    // output: Hello, World!

    return 0;
}