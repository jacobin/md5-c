#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>     /* for _O_TEXT and _O_BINARY */

#include "md5.h"

void print_hash(uint8_t* p) {
    for (unsigned int i = 0; i < 16; ++i) {
        printf("%02x", p[i]);
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    const char* p1 = argv[0] - 1, * p2 = argv[0];
    for (char* p = argv[0]; 1; p++)
    {
        const char c = *p;
        if (c == '\0' || c == '\\' || c == '/' || c == ':')
        {
            p1 = p2;
            p2 = p;
        }
        if (c == '\0')
        {
            break;
        }
    }

    uint8_t result[16];
    if (argc > 1) {
        const char* g = argv[1];
        if (strcmp(g, "/?") || strcmp(g, "-h") || strcmp(g, "--help"))
        {
            fprintf(stderr, "%s [targetString]\r\n"
                "\tExample:\r\n"
                "\t\tmd5 \"The quick brown fox jumps over the lazy dog\"\r\n"
                "\t\tmd5 < \"c:\\windows\\explorer.exe\"\r\n"
                "\t\ttype \"c:\\Windows\\System32\\drivers\\gmreadme.txt\" | md5"
                , p1 + 1);
            exit(1);
        }
        for (int i = 1; i < argc; ++i) {
            md5String(argv[i], result);
            print_hash(result);
        }
    }
    else {
        // FILE* fp = fopen("d:\\a.bat", "r");
        // FILE* fp = fopen("d:\\a.bat", "rb");
        _setmode(_fileno(stdin), O_BINARY);
        md5File(stdin, result);
        print_hash(result);
    }
    return 0;
}
