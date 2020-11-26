#include <stdio.h>

int main(void)
{
    int volume, weight, length;
    length=9;
    volume=length*length*length;
    weight = (volume + 165)/166;
    printf("Volume (cubic inches): %d\n", volume);
    printf("Dimensional weight (pounds) : %d\n", weight);

    return 0;
}
