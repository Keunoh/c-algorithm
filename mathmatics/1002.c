#include <stdio.h>
#include <math.h>

int main(void) {
    int t, x1, y1, r1, x2, y2, r2, result;
    double distance, subtract;
    scanf("%d", &t);

    while (t--) {
        scanf("%d %d %d %d %d %d", &x1, &y1, &r1, &x2, &y2, &r2);
        distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
        subtract = r1 > r2 ? r1 - r2 : r2 - r1;

        if (distance == 0 && r1 == r2) {
            result = -1;
        } 
        else if (distance < r1 + r2 && (subtract < distance)) {
            result = 2;
        }
        else if (distance == r1 + r2 || distance == subtract) {
            result = 1;
        }
        else {
            result = 0;
        }

        printf("%d\n", result);
        
    }
}