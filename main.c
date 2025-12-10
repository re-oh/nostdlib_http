#include "headers/com.h"
#include "headers/sys.h"
#include "headers/str.h"

int main(args_t args) {
    print(strfrom("Hello from MiniC!\n"));

    return 0;
}

ENTRY_POINT(main)