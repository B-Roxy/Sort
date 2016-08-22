#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>
#include <iomanip>
#include <memory>

using namespace std;

const int countData = 7;
const int countSort = 3; 

enum Sortings {
	ChoiceSort,
	BubbleSort,
	ShakerSort
};

struct StatSorting{
	float time;
	int countCompare;	// ñðàâíåíèÿ
	int countSwap;		// ïåðåñòàíîâêè
};

struct Statistics {
	string name;
	StatSorting dataSorting[countData];
} dataStatSorting[countSort];

/* ñîðòèðîâêà âûáîðîì
1) èùåì ìèíèìàëüíûé âî âñåì ìàññèâå ñ òåêóùåãî ïîëîæåíèÿ è äî êîíöà ìàññèâà, 
2) ïåðåñòàâëÿåì ìèíèìàëüíûé ñ òåêóùèì ÷ëåíîì ìàññàèâà
*/
void ChoiceSorting(int *arr, int size, int indx) {
	int min, c;
	clock_t start;
	int countSwap = 0;
	int countCompare = 0;

	start = clock();
	for (int i = 0; i < size - 1; i++) {
		min = i;
		for (int j = i + 1; j < size; j++) {
			if (arr[j] < arr[min]) {
				min = j;
				countCompare++;
			}
		}
		if (i != min) {
			c = arr[i];
			arr[i] = arr[min];
			arr[min] = c;
			countSwap++;
		}
	}
	dataStatSorting[ChoiceSort].name = "ChoiceSort";
	dataStatSorting[ChoiceSort].dataSorting[indx].time = (clock() - start) / (float)CLK_TCK;
	dataStatSorting[ChoiceSort].dataSorting[indx].countCompare = countCompare;
	dataStatSorting[ChoiceSort].dataSorting[indx].countSwap = countSwap;
}

/* ñîðòèðîâêà ïóçûðüêîì
*/
void BubbleSorting(int *arr, int size, int indx) {
	clock_t start;
	int countSwap = 0;
	int countCompare = 0;
	bool check = true;

	start = clock();
	while (check) {
		check = false;
		for (int i = 0; i < size - 1; i++) {
			if (arr[i] > arr[i + 1]) {
				int c = arr[i];
				arr[i] = arr[i+1];
				arr[i+1] = c;
				check = true;
				countSwap++;
			}
			countCompare++;
		}
		size--; // ñäâèãàåì ïðàâóþ ãðàíèöó, ò.ê. ñàìûé áîëüøîé ýë-ò áóäåò ñäâèíóò âïðàâî
	} 
	dataStatSorting[BubbleSort].name = "BubbleSort";
	dataStatSorting[BubbleSort].dataSorting[indx].time = (clock() - start) / (float)CLK_TCK;
	dataStatSorting[BubbleSort].dataSorting[indx].countCompare = countCompare;
	dataStatSorting[BubbleSort].dataSorting[indx].countSwap = countSwap;
}

void ReverseData(int *arr, int size) {
	for (int i = 0, j = size - 1; i < j; i++, j--) {
		int c = arr[j];
		arr[j] = arr[i];
		arr[i] = c;
	}
}
/* ��������� ����������
   1) ��������� ����� ������� �� ������ �������, ������� ������ ������� �� 1 �������
   2) ���� ������� � ���������, ����� ��������� �� ����� �������, ������� ����� ������� �� 1 �������
   3) ��������� ���������� �.1 � �.2 �� ��� ���, ���� ����, ��� ���������� ��� ���� ������� �� ��������
*/
void ShakerSorting(int *arr, int size, int indx) {
	clock_t start;
	int countSwap = 0;
	int countCompare = 0;
	bool check = true, isRight = true;
	int a = 0, b = size;

	start = clock();
	while (a < b && check) {
		check = false;
		if (isRight) {
			for (int i = a; i < b - 1; i++) {
				if (arr[i] > arr[i + 1]){
					int c = arr[i];
					arr[i] = arr[i+1];
					arr[i+1] = c;
					check = true;
				}
			}
			b--;
		}
		else {
			for (int i = b - 1; i > a; i--) {
				if (arr[i] < arr[i - 1]) {
					int c = arr[i];
					arr[i] = arr[i-1];
					arr[i-1] = c;
					check = true;
				}
			}
			a++;
		}
		isRight = !isRight;
	}
	dataStatSorting[ShakerSort].name = "ShakerSort";
	dataStatSorting[ShakerSort].dataSorting[indx].time = (clock() - start) / (float)CLK_TCK;
	dataStatSorting[ShakerSort].dataSorting[indx].countCompare = countCompare;
	dataStatSorting[ShakerSort].dataSorting[indx].countSwap = countSwap;
}

void PrintData(int size) {
	// âûâîä ðåçóëüòàòîâ
	cout << size << endl;
	cout << "Sort\t\tdata1\tdata2\tdata3\tdata4\tdata5\tdata6\tdata7	\n";
	for (int i = 0; i < countSort; i++) {
		cout << dataStatSorting[i].name << "\t";
		for (int j = 0; j < countData; j++) {
			cout << setw(8) << left << dataStatSorting[i].dataSorting[j].time;
		}
		cout << endl;
	}
	cout << endl << endl;
}

void main() {
	int *arr, *tmpArr; 
	const int countSizes = 6;
	int sizes[] = {1000, 5000, 10000, 50000, 100000, 150000};
	
	srand(800000);
	for (int i = 0; i < countSizes; i++) {
		arr = new int[sizes[i]];
		tmpArr = new int[sizes[i]];
		for (int j = 0; j < sizes[i]; j++) {
			arr[j] = rand() % sizes[i];
		}
		for (int j = 0; j < countData; j++) {
			// äàííûå:
			//0 - ñëó÷àéíû è íåîòñîðòèðîâàííû
			//1 - îòñîðòèðîâàííûå ïî âîçðàñòàíèþ
			//2 - îòñîðòèðîâàííûå ïî óáûâàíèþ
			//3 - ïî âîçðàñòàíèþ, çà èñêëþ÷åíèåì ýëåìåíòà ñ èíäåêñîì  (size/4)
			//4 - ïî âîçðàñòàíèþ, çà èñêëþ÷åíèåì ýëåìåíòà ñ èíäåêñîì  3*(size/4)
			//5 - ïî óáûâàíèþ, çà èñêëþ÷åíèåì èíäåêñîâ ìàññèâîâ (size/4)
			//6 - ïî óáûâàíèþ, çà èñêëþ÷åíèåì èíäåêñîâ ìàññèâîâ 3*(size/4) 
			if (j == 2 || j == 5 || j == 6)
				ReverseData(arr, sizes[i]);
			if (j == 3 || j == 5)
				arr[sizes[i] / 4] = 3 * sizes[i] / 4;
			if (j == 4 || j == 6)
				arr[(sizes[i] / 4) * 3] = sizes[i] / 4;
			memcpy(tmpArr, arr, sizeof(int) * sizes[i]);
			ChoiceSorting(arr, sizes[i], j);
			memcpy(arr, tmpArr, sizeof(int) * sizes[i]);
			BubbleSorting(arr, sizes[i], j);
			memcpy(arr, tmpArr, sizeof(int) * sizes[i]);
			ShakerSorting(arr, sizes[i], j);
		}
		delete[] arr;
		delete[] tmpArr;
		PrintData(sizes[i]);
	}
}
