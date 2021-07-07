#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

const int N = 100;

double H[N][N], L[N][N];
double x[N], b[N], ans[N], r[N], dx[N];

void split_line()
{
    for(int i = 1; i <= 20; ++i)
        printf("-");
    puts("");
}

void Cholesky(int n) // Cholesky分解
{
    for(int i = 1; i <= n; ++i)
    {
        for(int j = 1; j <= i; ++j)
            L[i][j] = H[i][j];
        for(int j = i + 1; j <= n; ++j)
            L[i][j] = 0;
    }
    for(int i = 1; i <= n; ++i)
    {
        for(int j = 1; j < i; ++j)
            L[i][i] -= L[i][j] * L[i][j];
        L[i][i] = sqrt(L[i][i]);
        for(int j = i + 1; j <= n; ++j)
        {
            for(int k = 1; k < i; ++k)
                L[j][i] -= L[j][k] * L[i][k];
            L[j][i] /= L[i][i];
        }
    }
}

void Gauss(double a[][N], double x[], int n) // 用高斯消元解 A*ans=x
{
    double b[N][N];
    for(int i = 1; i <= n; ++i)
    {
        for(int j = 1; j <= n; ++j)
            b[i][j] = a[i][j];
        b[i][n + 1] = x[i];
    }
    for(int i = 1; i <= n; ++i)
    {
        for(int j = 1; j <= n; ++j)
        {
            if (i == j) continue;
            for(int k = n + 1; k >= i; --k)
                b[j][k] -= b[j][i] / b[i][i] * b[i][k];
        }
    }
    for(int i = 1; i <= n; ++i)
        ans[i] = b[i][n + 1] / b[i][i];
}

void work(int n, double delta)
{
    cout << "n=" << n << ", delta=" << delta << endl;

    for(int i = 1; i <= n; ++i)           // 生成H矩阵，x向量，b=Hx向量
        for(int j = 1; j <= n; ++j)
            H[i][j] = 1.0 / (i + j - 1);
    for(int i = 1; i <= n; ++i)
        x[i] = 1 + delta;
    for(int i= 1; i <= n; ++i)
    {
        b[i] = 0;
        for(int j = 1; j <= n; ++j)
            b[i] += H[i][j] * x[j];
    }

    Cholesky(n);                           // 用Cholesky分解计算x*
    Gauss(L, b, n);                        // 解出L^T x
    for(int i = 1; i <= n; ++i)
        for(int j = i + 1; j <= n; ++j)
            swap(L[i][j], L[j][i]);
    Gauss(L, ans, n);                     // 解出 x

    double mx = 0; // 计算残差的范数
    for(int i = 1; i <= n; ++i) 
    {
        r[i] = b[i];
        for(int j = 1; j <= n; ++j)
            r[i] -= H[i][j] * ans[j];
        mx = max(mx, abs(r[i]));
    }
    cout << "||r||_inf=" << mx << endl;

    mx = 0; // 计算误差的范数
    for(int i = 1; i <= n; ++i)
    {
        dx[i] = ans[i] - x[i];
        mx = max(mx, dx[i]);
    }
    cout << "||dx||_inf=" << mx << endl;


    split_line();
}

int main()
{
    split_line();
    work(10, 0);
    work(10, 1e-7);
    work(8, 0);
    work(12, 0);
    system("pause");
    return 0;
}