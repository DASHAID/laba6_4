/*Реализуйте клеточный автомат Джона Конвея на замкнутой плоскости по 
классическим правилам. Продемонстрируйте работу клеточного автомата 
на примере «сорняка» («паразита») (фигуры, которая при столкновении с 
некоторыми фигурами дублируются) и на развитии колоний клеток, 
сгенерированных в случайном порядке. Реализовать работу графического 
отображения клеточного автомата можно таким образом, чтобы живые 
клетки изображались единицами, а мёртвые – нулями, либо живые – нулями, 
а мёртвые пробелами, либо другим возможным вариантом. Каждое новое 
поколение выводится на очищенное окно консоли через некоторый 
промежуток времени. Таким образом, получается непрерывная анимация.
*/ 

#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <iomanip>
#include <vector>

using namespace std;

//f для мертвых клеток
void _dead(vector<vector<int>>&life, vector<vector<int>>& lifeTwo, int i, int j, int M, int N) {
	int k = 0;

	//проверка соседних клеток
	for (int x=0;x<8;x++){
		if (x == 0) {
			if (i - 1 == -1 || j + 1 == N)continue;
			if (lifeTwo[i - 1][j + 1] == 1)k++;
		}
		if (x == 1) {
			if (i - 1 == -1||j-1==-1)continue;
			if (lifeTwo[i - 1][j - 1] == 1)k++;
		}
		if (x == 2) {
			if (i - 1 == -1)continue;
			if (lifeTwo[i - 1][j] == 1)k++;
		}
		if (x == 3) {
			if (j - 1 == -1)continue;
			if (lifeTwo[i][j - 1] == 1)k++;
		}
		if (x == 4) {
			if (i + 1 == M || j - 1 == -1)continue;
			if (lifeTwo[i + 1][j - 1] == 1)k++;
		}
		if (x == 5) {
			if (i + 1 == M)continue;
			if (lifeTwo[i + 1][j] == 1)k++;
		}
		if (x == 6) {
			if (i + 1 == M || j + 1 == N)continue;
			if (lifeTwo[i + 1][j + 1] == 1)k++;
		}
		if (x == 7) {
			if (j + 1 == N)continue;
			if (lifeTwo[i][j + 1] == 1)k++;
		}
	}
	//если клеток достаточно, она оживает
	if (k == 3)
		life[i][j]=1;
}

//f для живых клеток
void _live(vector<vector<int>> &life, vector<vector<int>>& lifeTwo, int i, int j, int M, int N) {
	int k = 0;
	
	//проверка соседних клеток
	for (int x = 0; x < 8; x++) {
		if (x == 0) {
			if (i - 1 == -1 || j - 1 == -1)continue;
			if (lifeTwo[i - 1][j - 1] == 1)k++;
		}
		if (x == 1) {
			if (i - 1 == -1)continue;
			if (lifeTwo[i - 1][j] == 1)k++;
		}
		if (x == 2) {
			if (i - 1 == -1 || j + 1 == N) continue;
			if (lifeTwo[i - 1][j + 1] == 1)k++;
		}
		if (x == 3) {
			if (j - 1 == -1)continue;
			if (lifeTwo[i][j - 1] == 1)k++;
		}
		if (x == 4) {
			if (i + 1 == M || j - 1 == -1)continue;
			if (lifeTwo[i + 1][j - 1] == 1)k++;
		}
		if (x == 5) {
			if (i + 1 == M)continue;
			if (lifeTwo[i + 1][j] == 1)k++;
		}
		if (x == 6) {
			if (i + 1 == M || j + 1 == N)continue;
			if (lifeTwo[i + 1][j + 1] == 1)k++;
		}
		if (x == 7) {
			if (j + 1 == N)continue;
			if (lifeTwo[i][j + 1] == 1)k++;
		}
	}

	//если клеток недостаточно или слишком много, она погибает
	if (k<=1||k>3)
		life[i][j]= 0;
	
}


int main()
{//определим начальную жизнь-
	srand(time(NULL));
	int M,N,j,i,y = 0;
	string agree;
	cout << "Size of place?" << endl;
	cout << "Height:" << endl;
	cin >> M;
	cout << "Weight:" << endl;
	cin >> N;

	vector < vector <int>> life(M);
	vector < vector <int>> lifeTwo(M);

	cout << "Do you want see a random life?(Yes/No)" << endl;
	cin >> agree;
	if (agree == "Yes") {
		for (i = 0; i < M; i++) {
			life[i].resize(N);
			for (j = 0; j < N; j++)
				life[i][j] = rand() % 2;

		}
	}
	//для показа паразита
	if (agree == "No") {
		cout << "Do you want see a life with parasites?(Yes/No)" << endl;
		cin >> agree;
		if (agree == "Yes") {
			for (i = 0; i < M; i++) {
				life[i].resize(N);
				for (j = 0; j < N; j++)
					life[i][j] = 0;

			}
			for (y = 0; y < 3; y++) {
				life[M-4][4 +y]=life[M-2][4+y] = 1;
				life[M - 4+1][4+y] = 1;
				
			}
			
		}
		if (agree == "No") {
			cout << "The End..";
			exit(0);
		}
	}
	//бесконечная анимация до esc
	while (1) {
		//изначальное поле для дальнейшего сравнивания
		for (int koordX = 0; koordX < M; koordX++) {
			lifeTwo[koordX].resize(N);
			for (int koordY = 0; koordY < N; koordY++)
				lifeTwo[koordX][koordY] = life[koordX][koordY];
		}
		//вывод поколений 
		system("cls");
		for (i = 0; i < M; ++i)
		{
			for (j = 0; j < N; ++j)
				cout << setw(2) << life[i][j];
			cout << endl;
		}
		Sleep(350);

		if (_kbhit() && (_getch() == 27))
		{
			cout << "Break done" << endl;
			break;
		}
		
		for (i = 0; i < M; i++)
			for (j = 0; j < N;j++) {
				if (life[i][j] == 1)_live(life,lifeTwo,i,j,M,N);
				if (life[i][j] == 0)_dead(life, lifeTwo, i, j, M, N);
			}
		
	}
	return(0);
}