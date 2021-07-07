#include <cstdio>
#include <algorithm>
#include <cstdlib>

using namespace std;

const int N = 110;

double accurate[N], jac[N], gs[N], sor[N], b[N], a[N][N];
int cnt_Jac, cnt_GS, cnt_SOR;

void Jacobi(double a[][N], double x[], int n) // 雅克比迭代法
{
    cnt_Jac = 0;
    for(int i = 1; i <= n; ++i) jac[i] = 0;
    double tmp[N], mx;
    do
    {
        ++cnt_Jac;

        for(int i = 1; i <= n; ++i) tmp[i] = jac[i], jac[i] = x[i];
        for(int i = 1; i <= n; ++i)
        {
            for(int j = 1; j <= n; ++j)
            {
                if (i == j) continue;
                jac[i] -= a[i][j] * tmp[j];
            }
            jac[i] /= a[i][i];
        }
        
        mx = 0;
        for(int i = 1; i <= n; ++i)
            mx = max(mx, abs(jac[i] - tmp[i]));
    } while (mx > 1e-3);

    mx = 0;
    for(int i = 1; i <= n; ++i)
        mx = max(mx, abs(jac[i] - accurate[i]));
        
    printf("Jacobi: %4d  %.10lf\n", cnt_Jac, mx);
}

void GS(double a[][N], double x[], int n) //G-S迭代法
{
    cnt_GS = 0;
    for(int i = 1; i <= n; ++i) gs[i] = 0;
    double tmp[N], mx;
    do
    {
        ++cnt_GS;

        for(int i = 1; i <= n; ++i) tmp[i] = gs[i];
        for(int i = 1; i <= n; ++i)
        {
            gs[i] = x[i];
            for(int j = 1; j <= n; ++j)
            {
                if (i == j) continue;
                gs[i] -= a[i][j] * gs[j];
            }
            gs[i] /= a[i][i];
        }
        
        mx = 0;
        for(int i = 1; i <= n; ++i)
            mx = max(mx, abs(gs[i] - tmp[i]));
    } while (mx > 1e-3);

    for(int i = 1; i <= n; ++i)
        mx = max(mx, abs(gs[i] - accurate[i]));
    printf("GS:     %4d  %.10lf\n", cnt_GS, mx);
}

void SOR(double a[][N], double x[], int n, double w) // SOR迭代法
{
    cnt_SOR = 0;
    for(int i = 1; i <= n; ++i) sor[i] = 0;
    double tmp[N], mx;
    do
    {
        ++cnt_SOR;

        for(int i = 1; i <= n; ++i) tmp[i] = sor[i];
        for(int i = 1; i <= n; ++i)
        {
            sor[i] = x[i];
            for(int j = 1; j <= n; ++j)
            {
                if (i == j) continue;
                sor[i] -= a[i][j] * sor[j];
            }
            sor[i] /= a[i][i];
            sor[i] = w * sor[i] + (1-w) * tmp[i];
        }
        
        mx = 0;
        for(int i = 1; i <= n; ++i)
            mx = max(mx, abs(sor[i] - tmp[i]));
    } while (mx > 1e-3);

    mx = 0;
    for(int i = 1; i <= n; ++i)
        mx = max(mx, abs(sor[i] - accurate[i]));
    printf("SOR:    %4d  %.10lf\n", cnt_SOR, mx);
}

void Gauss(double a[][N], double x[], int n) // 用高斯消元计算精确解
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
        accurate[i] = b[i][n + 1] / b[i][i];
}

void work(double e)
{
    printf("epsilon = %.4lf\n", e);
    int n = 100;
    double h = 1.0 / n;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
        {
            a[i][j] = 0;
            if (i == j) a[i][j] = -2 * e - h;
            if (i == j - 1) a[i][j] = e + h;
            if (i == j + 1) a[i][j] = e;
        }
    for(int i = 1; i <= n; ++i)
        b[i] = i != n ? 0.5*h*h : 0.5*h*h-e-h;
    Gauss(a, b, n);
    Jacobi(a, b, n);
    GS(a, b, n);
    SOR(a, b, n, 0.9);
    SOR(a, b, n, 1.1);
    puts("");
}

int main()
{
    work(1);
    work(0.1);
    work(0.01);
    work(0.0001);
    system("pause");
    return 0;
}