#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>     /* for _O_TEXT and _O_BINARY */
#include <io.h>      /* for _setmode() */
#include "md5.h"

void print_hash(uint8_t* p) {
    for (unsigned int i = 0; i < 16; ++i) {
        printf("%02x", p[i]);
    }
    printf("\n");
}

const char* basename(const char* argv0)
{
    const char* p1 = argv0 - 1, * p2 = argv0;
    for (const char* p = argv0; 1; p++)
    {
        const char c = *p;
        if (c == '\0' || c == '\\' || c == '/' || c == ':')
        {
            p1 = p2;
            p2 = p;
            if (c == '\0')
            {
                break;
            }
        }
    }
    return p1 + 1;
}

int main(int argc, char* argv[]) {
    uint8_t result[16];
    if (argc > 1) {
        const char* g = argv[1];
        if (!strcmp(g, "/?") || !strcmp(g, "-h") || !strcmp(g, "--help"))
        {
            const char* bname = basename(argv[0]);
            fprintf(stderr,
                "%s {[targetString1] [targetString2] ... [targetStringN]}\r\n"
                "\tExample:\r\n"
                "\t\t%s \"The quick brown fox jumps over the lazy dog\"\r\n"
                "\t\t%s < \"c:\\windows\\explorer.exe\"\r\n"
                "\t\ttype \"c:\\Windows\\System32\\drivers\\gmreadme.txt\" | %s"
                , bname, bname, bname, bname);
            exit(1);
        }
        for (int i = 1; i < argc; ++i) {
            md5String(argv[i], result);
            print_hash(result);
        }
    }
    else {
        // FILE* fp = fopen("d:\\target.file", "r");
        // FILE* fp = fopen("d:\\target.file", "rb");
        if (-1 == _setmode(_fileno(stdin), O_BINARY))
        {
            fprintf(stderr, "\"_setmode(_fileno(stdin), O_BINARY)\" failed.");
            abort(); // exit(3);
        }
        md5File(stdin, result);
        print_hash(result);
    }
    return 0;
}
