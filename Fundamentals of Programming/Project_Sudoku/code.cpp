#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <ctime>

using namespace std;

const int N = 10, n = 9; // n*n�����������淽��N=n+1
 
int vis[N]; //�ж�i��û�г��ֹ� 
int maxAns; // ��Ҫ�ҵ��Ĵ����� 
int possibleNextSearchPoint[100], top; // ������Щλ�ÿ������������
int columnRes[N], rowRes[N], blockRes[N]; // ��(1<<i)���λ�ñ�ʾi�������û�г��ֹ� 
int ans[11][N][N], totAns; // �����飬��ǰ�ҵ��Ĵ��� 

bool check_valid_rect(int a[][N]) { //check if a[][] is a valid rect
 
	for(int i = 1; i <= n; i++) {
		
		memset(vis, 0, sizeof(vis));
		for(int j = 1; j <= n; j++) { //row check
			if (!vis[a[i][j]]) {
				vis[a[i][j]] = 1;
			} else {
				if (a[i][j]) {
					return false;
				}
			}
		}
			
		memset(vis, 0, sizeof(vis));
		for(int j = 1; j <= n; j++) { //column check
			if (!vis[a[j][i]]) {
				vis[a[j][i]] = 1;
			} else {
				if (a[j][i]) {
					return false;
				}
			}
		}
	}
	
	for(int x0 = 0; x0 < n; x0 += 3) {
		for(int y0 = 0; y0 < n; y0 += 3) { // block check
		  
			memset(vis, 0, sizeof(vis));
			for(int i = 1; i <= 3; i++) {
				for(int j = 1; j <= 3; j++) {
					
					if (!vis[a[x0 + i][y0 + j]]) {
						vis[a[x0 + i][y0 + j]] = 1;
					} else {
						if (a[x0 + i][y0 + j]) {
							return false;
						} 
					} 
					
				}
			}
		} 
		
	}
	
	return true;
	
}

int block_id(const int x, const int y) { //get the id of the block of (x,y)
	return (x - 1) / 3 * 3 + (y - 1) / 3 + 1;
}

int bit_cnt(unsigned int x) { //get the number of 1 in the binary system of x
	int ret = 0;
	while (x) {
		ret += x & 1;
		x >>= 1;
	}
	return ret;
}

int valid_point(const int &x, const int &y) { //(x,y)���λ������Щ�������� 
	return rowRes[x] & columnRes[y] & blockRes[block_id(x, y)]; 
} 

int search(int a[][N], int x, int y) { // dfs������ 
	
	int S = valid_point(x, y); // S��ʾ��Щ��������
	if (!S) return 0;
	
	int bx = (x - 1) / 3 * 3, by = (y - 1) / 3 * 3; // (x,y)���ڿ������Ԫ����(bx+1,by+1)
	
	for(int v = 1; v <= n; v++) { //ö�ٵ�ǰλ������Щ�� 
		if ((S >> v) & 1) { //v����������� 
		
			a[x][y] = v;
			columnRes[y] ^= 1 << v;
			rowRes[x] ^= 1 << v;
			blockRes[block_id(x, y)] ^= 1 << v;
		
			int minPossibleNumber = N;
		
			for(int i = 1; i <= n; i++) { // �������V��ᵼ��ĳ��λ�ò����������Ͳ���v / �ж�ͬһ�� 
				if (!a[i][y]) {
					if (!valid_point(i, y)) goto failed;  
					int k = bit_cnt(valid_point(i, y));
					if (minPossibleNumber > k) {
						minPossibleNumber = k;
						possibleNextSearchPoint[top = 1] = i * N + y;
					} else {
						if (minPossibleNumber == k) {
							possibleNextSearchPoint[++top] = i * N + y;
						}
					}
				} 
			} 
			
			for(int i = 1; i <= n; i++) { // �������V��ᵼ��ĳ��λ�ò����������Ͳ���v / �ж�ͬһ�� 
				if (!a[x][i]) {
					if (!valid_point(x, i)) goto failed; 
					int k = bit_cnt(valid_point(x, i));
					if (minPossibleNumber > k) {
						minPossibleNumber = k;
						possibleNextSearchPoint[top = 1] = x * N + i;
					} else {
						if (minPossibleNumber == k) {
							possibleNextSearchPoint[++top] = x * N + i;
						}
					}
				} 
			}
		
			for(int i = 1; i <= 3; i++) { // �������V��ᵼ��ĳ��λ�ò����������Ͳ���v / �ж�ͬһ��� 
				for(int j = 1; j <= 3; j++) {
					int tx = bx + i, ty = by + j; //�жϵ�ǰ�ĸ�λ�� 
					
					if (!a[tx][ty]) {
						if(!valid_point(tx, ty)) goto failed;
						int k = bit_cnt(valid_point(tx, ty));
						if (minPossibleNumber > k) {
							minPossibleNumber = k;
							possibleNextSearchPoint[top = 1] = tx * N + ty;
						} else {
							if (minPossibleNumber == k) {
								possibleNextSearchPoint[++top] = tx * N + ty;
							}
						}
					}
					
				}
			}
			
			if (minPossibleNumber == N) { // [���������������]���ܻᷢ���ı�ĸ��Ӷ��������ˣ���������  
				for(int i = 1; i <= n; i++) {
					for(int j = 1; j <= n; j++) {
						
						if (!a[i][j]) {
							int k = bit_cnt(valid_point(i, j));
							if (k < minPossibleNumber){
								minPossibleNumber = k;
								possibleNextSearchPoint[top = 1] = i * N + j;
							} else if (k == minPossibleNumber) {
								possibleNextSearchPoint[++top] = i * N + j;
							} 
						}
						
					}
				}
			}
			
			if (minPossibleNumber == N) { //����λ�ö��������ˣ����ҵ�һ��� ������������һ��λ�õ���
			 
				for(int i = 1; i <= n; i++) {
					for(int j = 1; j <= n; j++) {
						ans[totAns][i][j] = a[i][j]; // ���´����� 
					}
				} 
				
				totAns++;
				if (totAns >= maxAns) {
					return 0; //�Ѿ��ҵ��㹻��𰸾��˳�
				} 

			} else {
				int p = rand() % top + 1;
				search(a, possibleNextSearchPoint[p] / N, possibleNextSearchPoint[p] % N);
				if (totAns >= maxAns){
					return 0; //�Ѿ��ҵ��㹻��𰸾��˳�
				}
			}
				
			failed:	// �������ֱ��ʧ�ܾ͵����λ�� 
				
			a[x][y] = 0; //��ԭ 
			columnRes[y] ^= 1 << v;
			rowRes[x] ^= 1 << v;
			blockRes[block_id(x, y)] ^= 1 << v;
		}
	}
	
	return 0;
}

int solve_rect(int a[][N]) { //�����������Ĵ𰸣��Լ��������һ����ܵ����� 
	
	if (!check_valid_rect(a)) { // �������Ͳ��Ϸ��Ͳ������� 
		return -1;
	}
	
	memset(ans, 0, sizeof(ans));
	totAns = 0;
	
	for(int i = 1; i <= n; i++) {
		blockRes[i] = columnRes[i] = rowRes[i] = ((1 << 10) - 1) ^ 1; // ��(1<<i)���λ�ñ�ʾi�������û�г��ֹ� 
	}
	
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++) {
			if (a[i][j]) {
				int k = a[i][j];
				columnRes[j] ^= (1 << k);
				rowRes[i] ^= (1 << k);
				blockRes[block_id(i, j)] ^= (1 << k);
			}
		}
	} //��ʼ����Щ���Ѿ����ֹ� 
	
	int minPossibleNumber = N; // ÿ��λ�������ɸ������������̰��ѡ�������������ٵ�ĳ��λ�ÿ�ʼ���� 
	
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			if (!a[i][j]) {
				int k = bit_cnt(valid_point(i, j)); //���λ�ÿ�������������� 
				if (k < minPossibleNumber){
					minPossibleNumber = k;
					possibleNextSearchPoint[top = 1] = i * N + j;
				}
				else if (k == minPossibleNumber) {
					possibleNextSearchPoint[++top] = i * N + j;
				} 
			}
		}
	}
	
	int p = rand() % top + 1;
	search(a, possibleNextSearchPoint[p] / N, possibleNextSearchPoint[p] % N);
	
	return totAns;
	
}

int main() {
	
	int T;
	scanf("%d", &T);
	while (T--)
	{
		
	
	int randomSeed = time(0);
	srand(randomSeed);
	
		int sudokuMatrix[N][N];
		char c;
		maxAns = 2;
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= n; j++) {
				do {
					c=getchar();
				}
				while (!(c >= '0' && c <= '9'));
				sudokuMatrix[i][j] = c - '0';
				
			}
		}
			
		maxAns = 1; //stop after finding 2 solutions 
		int s = solve_rect(sudokuMatrix);
		
			for(int i = 1; i <= n; i++, cout << endl) {
				for(int j = 1; j <= n; j++) {
					cout << ans[0][i][j];
				}
			}

	
}
	return 0;
	
}
