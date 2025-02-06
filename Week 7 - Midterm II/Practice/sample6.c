#include <stdio.h>

int main(){
    float num1, num2;

    scanf("%f %f", &num1, &num2);

    int count = 0, count1 = 0;
    unsigned char *one = (unsigned char*)&num1, *two = (unsigned char*)&num2;

    for(int i = 0; i < 4; i++){
        unsigned char byte1 = one[i], byte2 = two[i];
        for(int j = 0; j < 8; j++){
            int bit1 = (byte1 >> i) & 1, bit2 = (byte2 >> i) & 1;
            if (bit1 == bit2) count++;
        }
    }

    printf("Count - %d\n", count1);
}