#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <ctime>

using namespace std;

const int N = 10, n = 9; // n*n的数独，保存方便N=n+1
 
int vis[N]; //判断i有没有出现过 
int maxAns; // 需要找到的答案数量 
int possibleNextSearchPoint[100], top; // 保存哪些位置可能填的数最少
int columnRes[N], rowRes[N], blockRes[N]; // 用(1<<i)这个位置表示i这个数有没有出现过 
int ans[11][N][N], totAns; // 答案数组，当前找到的答案数 

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

int valid_point(const int &x, const int &y) { //(x,y)这个位置有哪些数可以填 
	return rowRes[x] & columnRes[y] & blockRes[block_id(x, y)]; 
} 

int search(int a[][N], int x, int y) { // dfs搜索答案 
	
	int S = valid_point(x, y); // S表示哪些数可以填
	if (!S) return 0;
	
	int bx = (x - 1) / 3 * 3, by = (y - 1) / 3 * 3; // (x,y)所在块的左上元素是(bx+1,by+1)
	
	for(int v = 1; v <= n; v++) { //枚举当前位置填哪些数 
		if ((S >> v) & 1) { //v这个数可以填 
		
			a[x][y] = v;
			columnRes[y] ^= 1 << v;
			rowRes[x] ^= 1 << v;
			blockRes[block_id(x, y)] ^= 1 << v;
		
			int minPossibleNumber = N;
		
			for(int i = 1; i <= n; i++) { // 如果填了V后会导致某个位置不能填数，就不填v / 判断同一列 
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
			
			for(int i = 1; i <= n; i++) { // 如果填了V后会导致某个位置不能填数，就不填v / 判断同一行 
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
		
			for(int i = 1; i <= 3; i++) { // 如果填了V后会导致某个位置不能填数，就不填v / 判断同一大格 
				for(int j = 1; j <= 3; j++) {
					int tx = bx + i, ty = by + j; //判断当前哪个位置 
					
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
			
			if (minPossibleNumber == N) { // [可能填的数的数量]可能会发生改变的格子都被填满了，重新讨论  
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
			
			if (minPossibleNumber == N) { //所有位置都被填满了，即找到一组解 ，否则搜索下一个位置的数
			 
				for(int i = 1; i <= n; i++) {
					for(int j = 1; j <= n; j++) {
						ans[totAns][i][j] = a[i][j]; // 更新答案数组 
					}
				} 
				
				totAns++;
				if (totAns >= maxAns) {
					return 0; //已经找到足够多答案就退出
				} 

			} else {
				int p = rand() % top + 1;
				search(a, possibleNextSearchPoint[p] / N, possibleNextSearchPoint[p] % N);
				if (totAns >= maxAns){
					return 0; //已经找到足够多答案就退出
				}
			}
				
			failed:	// 如果填数直接失败就到这个位置 
				
			a[x][y] = 0; //还原 
			columnRes[y] ^= 1 << v;
			rowRes[x] ^= 1 << v;
			blockRes[block_id(x, y)] ^= 1 << v;
		}
	}
	
	return 0;
}

int solve_rect(int a[][N]) { //计算给出矩阵的答案，以及随机生成一组可能的数独 
	
	if (!check_valid_rect(a)) { // 如果本身就不合法就不再搜索 
		return -1;
	}
	
	memset(ans, 0, sizeof(ans));
	totAns = 0;
	
	for(int i = 1; i <= n; i++) {
		blockRes[i] = columnRes[i] = rowRes[i] = ((1 << 10) - 1) ^ 1; // 用(1<<i)这个位置表示i这个数有没有出现过 
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
	} //初始化哪些数已经出现过 
	
	int minPossibleNumber = N; // 每个位置有若干个可以填的数，贪心选择可能填的数最少的某个位置开始搜索 
	
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			if (!a[i][j]) {
				int k = bit_cnt(valid_point(i, j)); //这个位置可以填的数的数量 
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
