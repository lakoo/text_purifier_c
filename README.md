# Text Purifier (0.9.3)

- [Introduction](#introduction)
- [Installation](#installation)
- [Example](#example)
- [License](#license)

## Introduction

This is a C library for purifying text from a list of words.  It supports UTF-8 string (wchar_t\*, char\*).

## Installation

```bash
git clone https://github.com/lakoo/text_purifier_c.git
cd text_purifier_c
./autogen.sh
./configure
make
make install
```

## Example

```C
##############
# example.c
##############

#include <locale.h>
#include <stdio.h>
#include <wchar.h>

#include <text_purifier_c.h>


#define UNUSED(x) UNUSED_##x __attribute__((__unused__))


void charExample()
{
    void* handle = text_purifier_init();

    const char* list[] = { "歧視言論", "粗口", "色情圖片" };
    const size_t size = sizeof(list) / sizeof(char*);

    for(size_t index = 0; index < size; ++index)
    {
        text_purifier_add(handle, list[index]);
    }

    const char strA[] = "這是歧視言論啊！";
    const char* str = text_purifier_purify2str(handle, strA, "河蟹");
    printf("1. %s -> %s\n", strA, str);
    text_purifier_free_str(handle, str);
    str = NULL;

    const char strB[] = "這裏有歧視言論、粗口用語、色情圖片等等。";

    str = text_purifier_purify2char(handle, strB, '*', 1);
    printf("2. %s -> %s\n", strB, str);
    text_purifier_free_str(handle, str);
    str = NULL;

    str = text_purifier_purify2char(handle, strB, '#', 0);
    printf("3. %s -> %s\n", strB, str);
    text_purifier_free_str(handle, str);
    str = NULL;

    text_purifier_destroy(handle);
    handle = NULL;
}

void wcharExample()
{
    void* handle = text_purifier_init();

    const wchar_t* list[] = { L"歧視言論", L"粗口", L"色情圖片" };
    const size_t size = sizeof(list) / sizeof(wchar_t*);

    text_purifier_add_wlist(handle, list, size);

    const wchar_t strA[] = L"這是歧視言論啊！";
    const wchar_t* str = text_purifier_wpurify2str(handle, strA, L"河蟹");
    wprintf(L"4. %ls -> %ls\n", strA, str);
    text_purifier_free_wstr(handle, str);
    str = NULL;

    const wchar_t strB[] = L"這裏有歧視言論、粗口用語、色情圖片等等。";

    str = text_purifier_wpurify2char(handle, strB, L'畢', 1);
    wprintf(L"5. %ls -> %ls\n", strB, str);
    text_purifier_free_wstr(handle, str);
    str = NULL;

    str = text_purifier_wpurify2char(handle, strB, L'禁', 0);
    wprintf(L"6. %ls -> %ls\n", strB, str);
    text_purifier_free_wstr(handle, str);
    str = NULL;

    text_purifier_destroy(handle);
    handle = NULL;
}

int main(int UNUSED(argc), char* UNUSED(argv[]))
{
    setlocale(LC_ALL, "C.UTF-8");

    printf("char\n");
    charExample();
    printf("\n");

    printf("wchar_t\n");
    wcharExample();

    return 0;
}
```

```bash
$ g++ -o example.o -std=c11 -c example.cpp
$ g++ -o example -ltextpurifier -Wl,-rpath,/usr/local/lib example.o
$ ./example
char
1. 這是歧視言論啊！ -> 這是河蟹啊！
2. 這裏有歧視言論、粗口用語、色情圖片等等。 -> 這裏有****、**用語、****等等。
3. 這裏有歧視言論、粗口用語、色情圖片等等。 -> 這裏有#、#用語、#等等。

wchar_t
4. 這是歧視言論啊！ -> 這是河蟹啊！
5. 這裏有歧視言論、粗口用語、色情圖片等等。 -> 這裏有畢畢畢畢、畢畢用語、畢畢畢畢等等。
6. 這裏有歧視言論、粗口用語、色情圖片等等。 -> 這裏有禁、禁用語、禁等等。
```

## License

This software is licensed under the [GNU Lesser GPL v3 license](https://www.gnu.org/copyleft/lgpl.html). © 2017 Lakoo Games Limited
