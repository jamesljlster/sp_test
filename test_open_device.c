#include <stdio.h>
#include <stdlib.h>

#include <libserialport.h>

#define test(func)                                                  \
    {                                                               \
        int __retVal = func;                                        \
        if (__retVal < 0)                                           \
        {                                                           \
            fprintf(stderr, "%s(), %d: %s failed with error: %d\n", \
                    __FUNCTION__, __LINE__, #func, __retVal);       \
            return -1;                                              \
        }                                                           \
    }

int main(int argc, char* argv[])
{
    struct sp_port* sp = NULL;

    const char* devPath;
    int baud;

    // Check argument
    if (argc < 3)
    {
        printf("Usage: test_open_device <dev_path> <baudrate>\n");
        return -1;
    }

    devPath = argv[1];
    baud = atoi(argv[2]);

    printf("Summary:\n");
    printf("    Device Path: %s\n", devPath);
    printf("    Baudrate: %d\n", baud);

    // Get port
    test(sp_get_port_by_name(argv[1], &sp));

    // Open port
    test(sp_open(sp, SP_MODE_READ_WRITE));

    // Set serialport
    test(sp_set_baudrate(sp, baud));
    test(sp_set_bits(sp, 8));

    // Close port
    test(sp_close(sp));
    sp_free_port(sp);

    return 0;
}
