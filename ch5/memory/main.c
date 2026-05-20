#include <stdint.h>
#include <string.h>
#include <stdlib.h>

int fn1(int i)
{
    uint32_t f1[100];
    char *c = malloc(10);
    for (int j = 0; j < 100; j++) {
        f1[j] = 0;
    }
    if (i > 16)
        return 0;
    free(c);
    return 1 + fn1(i + 1);
}


void fn0(void)
{
    //volatile uint8_t f1;
    fn1(0);

}

extern int mpu_enable(void);

void main(void) {
    mpu_enable();

    fn0();

    while(1);;
}