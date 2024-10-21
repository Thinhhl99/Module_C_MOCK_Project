#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#pragma warning (disable:4996)
#define MAXN 10001
int components[MAXN][MAXN], adj[MAXN][MAXN];
int componentCounts[MAXN], arr_nguy[MAXN], arr_k_cach[MAXN];
bool visited[MAXN];
int dd[1000], tt = 0;
int dem = 1, dem2 = 99999999;
int n, m, value_nguy, u, v;
int a[MAXN][MAXN];
int b[MAXN];
int c[MAXN];

typedef struct num_n {
	int data;
} num_n;

void dfs(int u1, int* count, int componentIndex) {
	visited[u1] = true;
	components[componentIndex][(*count)++] = u1; // Luu dinh vao phan lien thong con lai
	for (int v = 1; v <= n; v++) {
		if (adj[u1 - 1][v - 1] && !visited[v]) {
			dfs(v, count, componentIndex);
		}
	}
}

void duongDiNganNhat(int i) {
	dd[i] = 1;

	if (i == v) {
		tt = 1;
		if (dem < dem2) {
			for (int j = 0; j < dem; j++)
				c[j] = b[j];//c[j] la mang chua duong di qa cac dinh && duong ngan nhat
			dem2 = dem;
		}
	}
	else {
		for (int j = 0; j < n; j++) {
			if (adj[i][j] != 0 && dd[j] == 0) {
				b[dem++] = j;
				duongDiNganNhat(j);
				dem--;
				dd[j] = 0;
			}
		}
	}
}

int induongdi() {
	int count = 0;
	//printf("\nDuong di ngan ngat la: ");
	for (int i = 0; i < dem2; i++) {
		//printf("%d ", c[i]+1);
		count++;
	}
	//printf("\nDinh %d do thuoc F%d",c[0], count-1);
	if (count - 1 == 0) {
		return count - 1;
	}
	else if (count - 1 == 1) {
		return count - 1;
	}
	else if (count - 1 == 2) {
		return count - 1;
	}
	else {
		return 3;
	}
}

int process_arr_nguy(int* p) {
	int temp = p[0];
	for (int i = 1; i < value_nguy; i++) {
		if (temp > p[i]) {
			temp = p[i];
		}
	}
	if (temp < 4) {
		if (temp == 0) {
			return 10;
		}
		else if (temp == 1) {
			return 5;
		}
		else if (temp == 2) {
			return 3;
		}
		else {
			return 1;
		}
	}
	else {
		return 4;
	}
}

void sort_arr(int* p, int n) {
	// bubble sort
	for (int i = 0; i < n - 1; i++) {
		for (int j = n - 1; j > i; j--) {
			if (p[j] > p[j - 1]) {
				int temp = p[j];
				p[j] = p[j - 1];
				p[j - 1] = temp;
			}
		}
	}
}

int main() {
	printf("Nhap so n: ");
	scanf("%d", &n);
	num_n *group;
	group = (num_n*)malloc(n * sizeof(num_n));
	memset(visited, false, sizeof(visited));
	memset(adj, 0, sizeof(adj));

	printf("Nhap so luong phan tu cua mang a: ");
	scanf("%d", &m);
	printf("Nhap cac phan tu mang a:\n");
	for (int i = 1; i <= m; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		adj[x - 1][y - 1] = 1;
		adj[y - 1][x - 1] = 1;
	}

	printf("So luong phan tu cua mang b: ");
	scanf("%d", &value_nguy);
	printf("Nhap cac phan tu mang b:\n");
	for (int i = 0; i < value_nguy; i++) {
		scanf("%d", &arr_nguy[i]);
	}

	for (int k = 1; k <= n; k++) {
		u = k - 1;
		for (int i = 0; i < value_nguy; i++) {
			v = arr_nguy[i] - 1;
			b[0] = u;
			duongDiNganNhat(u);
			if (tt) {
				arr_k_cach[i] = induongdi();

			}
			else {
				arr_k_cach[i] = 4;
			}
			tt = 0;
			dem = 1;
			dem2 = 99999999;
			memset(dd, 0, sizeof(dd));
			memset(b, 0, sizeof(b));
			memset(c, 0, sizeof(c));
		}
		//k:1->n; xet tung dinh va gan gia tri muc do nguy hiem cho dinh do
		if (process_arr_nguy(arr_k_cach) == 4) {
			group[k - 1].data = 0;
			//printf("\nMuc do nguy hiem Dinh %d la %d",k, 0);
		}
		else {//
			group[k - 1].data = process_arr_nguy(arr_k_cach);
			//printf("\nMuc do nguy hiem Dinh %d la %d",k,process_arr_nguy(arr_k_cach));
		}
		//printf("\nMuc do nguy hiem Dinh %d la F%d",k,process_arr_nguy(arr_k_cach));
	}
	//------------------------------------------------------------------------------------------------------------//
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		if (!visited[i]) {
			int count = 0;
			dfs(i, &count, cnt);
			componentCounts[cnt] = count; // Luu so luong dinh vao thanh phan lien thong
			cnt++;
		}
	}
	int covidSeverity[MAXN];
	for (int i = 0; i < cnt; i++) {
		int sum = 0;//printf("\nConnected component %d has %d vertices: ", i + 1, componentCounts[i]);
		for (int j = 0; j < componentCounts[i]; j++) {
			for (int k = 0; k < n; k++) {
				if (components[i][j] == k + 1) { //
					sum += group[k].data;
				}
			}
		}
		// Muc do nguy hiem cua tung nhom 
		covidSeverity[i] = sum;
	}
	sort_arr(covidSeverity, cnt);
	printf("covidSeverity(n,a): [");
	for (int i = 0; i < cnt; i++) {
		if (i == cnt - 1) {
			printf("%d]", covidSeverity[i]);
		}
		else {
			printf("%d, ", covidSeverity[i]);
		}
	}
	return 0;
}
