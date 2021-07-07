#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <windows.h>

using namespace std;

const double eps = 1e-6;

struct matrix
{
    int n;
    double m[100][100];

    matrix(int nn = 0){n = nn; for(int i = 0; i < 100; ++i) for(int j = 0; j < 100; ++j) m[i][j] = 0;}
} Q;

double v[100], w[100];

matrix operator * (matrix A, matrix B)  // 矩阵乘法
{
    matrix C(A.n);
    for(int i = 1; i <= A.n; ++i)
        for(int j = 1; j <= A.n; ++j)
            for(int k = 1; k <= A.n; ++k)
                C.m[i][j] += A.m[i][k] * B.m[k][j];
    return C;
}

matrix householder(int n, double *w)  // 用w向量构造householder矩阵
{
    matrix A(n);
    for(int i = 1; i <= n; ++i)
    {
        for(int j = 1; j <= n; ++j)
            A.m[i][j] -= 2 * w[i] * w[j];
        A.m[i][i] += 1;
    }
    return A;
}

pair<matrix, matrix> QR_decomposition(matrix A)  // 计算A矩阵的QR分解
{
    int n = A.n;
    matrix Q(n);
    for(int i = 1; i <= n; ++i) Q.m[i][i] = 1;

    for(int i = 1; i <= n; ++i)
    {
        double sig = 0;
        for(int j = i; j <= n; ++j)
            sig += A.m[j][i] * A.m[j][i];
        sig = sqrt(sig);
        if (A.m[i][i] < 0) sig = -sig;
        if (fabs(sig - A.m[i][i]) < eps) continue;

        for(int j = 1; j < i; ++j) v[j] = 0;
        for(int j = i; j <= n; ++j) v[j] = A.m[j][i];
        v[i] += sig;
        double beta = 0;
        for(int j = i; j <= n; ++j) beta += v[j] * v[j];
        
        for(int j = 1; j <= n; ++j) w[j] = v[j] / sqrt(beta);
        matrix H = householder(n, w);

        Q = Q * H;
        A = H * A;
    }

    return make_pair(Q, A);
}

matrix QR_iteration(matrix A)  // QR迭代,A_{k+1}=RQ
{
    pair<matrix, matrix> QR;
    QR = QR_decomposition(A);
    return QR.second * QR.first;
}

matrix tridiagonal(matrix A)  // 用householder变换将A转化为三对角矩阵
{
    for(int i = 1; i <= A.n - 2; ++i)
    {
        for(int j = 1; j <= A.n; ++j) w[j] = 0;
        double s = 0, sign = 1;
        for(int j = i + 1; j <= A.n; ++j)
            s += A.m[i][j] * A.m[i][j];
        s = sqrt(s);
        if (fabs(s) < eps) continue;
        if (A.m[i][i + 1] < 0) sign = -1;
        w[i+1] = sqrt(0.5 * (1 + fabs(A.m[i][i+1]) / s));
        for(int j = i + 2; j <= A.n; ++j)
            w[j] = (A.m[i][j] / (2 * s * w[i+1])) * sign;
        matrix H = householder(A.n, w);
        A = H * A * H;
    }
    return A;
}

void solve(matrix A)  // 计算矩阵A的特征值
{
    printf("eigenvalue: \n");
    A = tridiagonal(A);
    while (A.n > 1)
    {
        if (fabs(A.m[A.n][A.n - 1]) < eps)
        {
            printf("%.4lf, ", A.m[A.n][A.n]);
            A.n--;
            continue;
        }
        double tmp = A.m[A.n][A.n];
        for(int i = 1; i <= A.n; ++i) A.m[i][i] -= tmp;
        A = QR_iteration(A);
        for(int i = 1; i <= A.n; ++i) A.m[i][i] += tmp;
    }
    printf("%.4lf\n", A.m[1][1]);
}

int main()
{
    matrix A(4);
    A.m[1][1] = 0.5; A.m[1][2] = 0.5; A.m[1][3] = 0.5; A.m[1][4] = 0.5;
    A.m[2][1] = 0.5; A.m[2][2] = 0.5; A.m[2][3] = -0.5; A.m[2][4] = -0.5;
    A.m[3][1] = 0.5; A.m[3][2] = -0.5; A.m[3][3] = 0.5; A.m[3][4] = -0.5;
    A.m[4][1] = 0.5; A.m[4][2] = -0.5; A.m[4][3] = -0.5; A.m[4][4] = 0.5;
    
    solve(A);
    system("pause");

    return 0;
}