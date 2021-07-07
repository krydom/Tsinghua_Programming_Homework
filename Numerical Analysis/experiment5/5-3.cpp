#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cmath>

using namespace std;

const double eps = 1e-6;
const int max_iteration = 1000;  // 最大迭代次数

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

        for(int j = 1; j <= n; ++j) w[j] = v[j] / sqrt(beta);  // 构造householder矩阵
        matrix H(n);
        for(int j = 1; j <= n; ++j)
        {
            H.m[j][j] += 1;
            for(int k = 1; k <= n; ++k)
                H.m[j][k] -= 2 * w[j] * w[k];
        }

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

void calculate(double a, double b, double c, double d)  // 计算2*2矩阵的特征值
{
    double e = - a - d;
    double f = a * d - b * c;
    double rea = (a + d) / 2.0; 
    double g = e * e - 4 * f;
    if (g >= 0)
    {
        double t1 = rea + sqrt(g) / 2.0, t2 = rea - sqrt(g) / 2.0;
        printf("%.4lf, %.4lf, ", t2, t1);
    }
    else if (fabs(rea) < eps)
    {
        printf("%.4lfi, -%.4lfi, ", sqrt(-g) / 2.0, sqrt(-g) / 2.0);
    }
    else
    {
        printf("%.4lf+%.4lfi, %.4lf-%.4lfi, ", rea, sqrt(-g) / 2.0, rea, sqrt(-g) / 2.0);
    }
}

bool eigenvalue(matrix A)  // 如果A是拟上三角矩阵，计算特征值并返回1，否则返回0
{
    for(int i = 1; i <= A.n; ++i) v[i] = 0;
    for(int i = 1; i < A.n; ++i)
    {
        if (fabs(A.m[i + 1][i]) >= eps) v[i] = 1;
        for(int j = i + 2; j <= A.n; ++i)
            if (fabs(A.m[j][i]) >= eps) return 0;
        if (v[i] && v[i - 1]) return 0;
    }
    for(int i = 1; i <= A.n; ++i)
        if (v[i])
        {
            calculate(A.m[i][i], A.m[i][i+1], A.m[i+1][i], A.m[i+1][i+1]);
            ++i;
        }
        else printf("%.5lf, ", A.m[i][i]);
    puts("");
    return 1;
}

void solve(matrix A)  // 计算矩阵A的特征值
{
    bool fl = 0;
    for(int i = max_iteration; i; --i)  // 有可能无法收敛，设置最大迭代次数
    {
        if (eigenvalue(A))
        {
            fl = 1;
            break;
        }
        A = QR_iteration(A);
    }
    if (!fl) puts("Iteration does not end!");
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