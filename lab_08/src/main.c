#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define     __TEST__

#ifdef __TEST__
static uint64_t
asmstrlen(const char *str) {
    int len = -1;

    __asm__(
        "mov $0, %%al\n\t"
        "mov %1, %%rdi\n\t"
        "mov $-1, %%ecx\n\t"
        "repne scasb\n\t"
        "mov $-2, %%eax\n\t"
        "sub %%ecx, %%eax\n\t"
        "mov %%eax, %0"
        : "=r"(len)
        : "r"(str)
        : "%eax", "%ecx", "%rdi", "%al"
    );

    return len;
}

static void
testAsmstrlen() {
    const char *test_str = "Test string YEP :)";

    puts("__STRLEN__");
    puts("--------------------");
    printf("asmstrlen result: %llu\nstrlen result: %lu\n", asmstrlen(test_str), strlen(test_str));
}

void
strcopy(char *dest, char *src, int len);

static void
testAsmstrcopy() {
    char src[] = "qwertyuiopasdfghjklzxcvbnm";
    char dst[] = "111222333444555";
    size_t len;

    puts("__INIT__");
    puts("--------------------");
    printf("Sources for test: src - %s, dst - %s\n", src, dst);
    len = 5;
    strcopy(dst, src, len);
    printf("Different Source and Destination. Result: %s\nSymbols copied: %zu\n", dst, len);
    puts("--------------------");

    puts("__TESTS__");
    puts("--------------------");
    printf("Source for test: %s\n", src);
    len = 10;
    strcopy(src + 2, src, len);
    printf("Destination is Source + 2. Result: %s\nSymbols copied: %zu\n", src, len);
    puts("--------------------");
    printf("Source for test: %s\n", src);
    len = 10;
    strcopy(src, src + 3, len);
    printf("Source is Destination + 3. Result: %s\nSymbols copied: %zu\n", src, len);
    puts("--------------------");
    printf("Source for test: %s\n", src);
    len = 10;
    strcopy(src, src, len);
    printf("Source is Destination. Result: %s\nSymbols copied: %zu\n", src, len);
}
#endif  // __TEST__

int
main(void) {
#ifdef __TEST__
    puts("--------------------");
    testAsmstrlen();
    puts("--------------------");
    testAsmstrcopy();
    puts("--------------------");
#endif  // __TEST__

    return 0;
}