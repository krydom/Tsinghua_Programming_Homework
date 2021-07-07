#include <cstdio>
#include <cstdlib>

using namespace std;

const double eps = 1e-8;

double fun1(double x) { return x*x*x - x - 1; } // 第一个方程及其导数
double der1(double x) { return 3*x*x - 1; }

double fun2(double x) { return - x*x*x + 5*x; } // 第二个方程及其导数
double der2(double x) { return - 3*x*x + 5; }

void newton(int tmp, double x0) // 将书中伪代码翻译成 C++
{
    double s, x = x0, f, f0, lambda;
    f = tmp == 1 ? fun1(x) : fun2(x);
    while (abs(f) > eps || abs(x - x0) > eps)
    {
        s = tmp == 1 ? fun1(x0) / der1(x0) : fun2(x0) / der2(x0);
        x = x0 - s;
        f = tmp == 1 ? fun1(x) : fun2(x);
        f0 = tmp == 1 ? fun1(x0) : fun2(x0);
        lambda = 0.5;
        while (abs(f) >= abs(f0))
        {
            x = x0 - lambda * s;
            f = tmp == 1 ? fun1(x) : fun2(x);
            lambda /= 2; // *
        }
        x0 = x;
        printf("lambda: %.8lf, approximate solution: %.8lf\n", lambda * 2, x0);
        // 因为在 * 行 lambda 会多 /2，所以在输出时将其 *2
    }
    puts("");
}

int main()
{
    newton(1, 0.6);
    newton(2, 1.35);
    system("pause");
    return 0;
}