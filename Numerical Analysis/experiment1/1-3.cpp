#include <cstdio>
#include <ctime>
#include <cstdlib>

using namespace std;

const float one_float = 1.0;
const double one_double = 1.0;

int main()
{
    float harmonic_float = 0.0, tmp;
    int n = 0;
    while (true)
    {
        tmp = harmonic_float;
        ++n;
        harmonic_float += one_float / n;
        if (harmonic_float == tmp)
            break;
    }
    double used_time = clock() / (double) CLOCKS_PER_SEC;

    printf("When n = %d, the harmonic series recorded in float does not change.\n", n);
    printf("Now the harmonic series is equal to %.8f.\n", harmonic_float);
    printf("The calculation took %.3lfs.\n\n", used_time);

    double harmonic_double = 0.0;           // 计算用double存储的结果
    for(int i = 1; i <= n; ++i)
        harmonic_double += one_double / i;

    printf("When n = %d, the harmonic series recorded in double is equal to %.14lf.\n", n, harmonic_double);
    printf("The absolute error when recorded in float is %.10lf.\n", harmonic_float - harmonic_double);                           // 绝对误差
    printf("The relative error when recorded in float is %.10lf.\n", (harmonic_float - harmonic_double) / harmonic_double);       // 相对误差

    system("pause");
    
    return 0;
}