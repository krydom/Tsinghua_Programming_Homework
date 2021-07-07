#include <cstdio>
#include <algorithm>
#include <cstdlib>

using namespace std;

struct matrix
{
    int n;
    double m[100][100];
} A, B;

double now[100], nxt[100];

void power(matrix A)
{
    double tmp = 1, lambda = 0;
    now[1] = 1;                             // 初始化向量为(1,0,0,...)
    for(int i = 2; i <= A.n; ++i)
        now[i] = 0;
    while (abs(lambda - tmp) >= 1e-5)
    {
        tmp = lambda;
        for(int i = 1; i <= A.n; ++i)
        {
            nxt[i] = 0;
            for(int j = 1; j <= A.n; ++j)
                nxt[i] += A.m[i][j] * now[j];  // 计算 Ax
        }
        lambda = 0;
        for(int i = 1; i <= A.n; ++i)
            if (abs(lambda) < abs(nxt[i]))
                lambda = nxt[i];               // 找到新的特征值
        for(int i = 1; i <= A.n; ++i)          // 标准化向量
            now[i] = nxt[i] / lambda;
    }
    printf("lambda1 = %.6lf\nx1 = (", lambda);
    for(int i = 1; i < A.n; ++i)
        printf("%.6lf, ", now[i]);
    printf("%.6lf)\n", now[A.n]);
    puts("");
}

int main()
{
    A.n = 3;
    A.m[1][1] = 5; A.m[1][2] = -4; A.m[1][3] = 1;
    A.m[2][1] = -4; A.m[2][2] = 6; A.m[2][3] = -4;
    A.m[3][1] = 1; A.m[3][2] = -4; A.m[3][3] = 7;
    power(A);

    B.n = 4;
    B.m[1][1] = 25; B.m[1][2] = -41; B.m[1][3] = 10; B.m[1][4] = -6;
    B.m[2][1] = -41; B.m[2][2] = 68; B.m[2][3] = -17; B.m[2][4] = 10;
    B.m[3][1] = 10; B.m[3][2] = -17; B.m[3][3] = 5; B.m[3][4] = -3;
    B.m[4][1] = -6; B.m[4][2] = 10; B.m[4][3] = -3; B.m[4][4] = 2;
    power(B);

    system("pause");

    return 0;
}