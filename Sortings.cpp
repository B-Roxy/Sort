#include <cstdlib>
#include <ctime>
//#include <cstdio>
#include <string>
#include <iostream>
#include <iomanip>
#include <memory>

using namespace std;

const int countData = 7;
const int countSort = 2; 

enum Sortings {
	ChoiceSort,
	BubbleSort
};

struct StatSorting{
	float time;
	int countCompare;	// сравнения
	int countSwap;		// перестановки
};

struct Statistics {
	string name;
	StatSorting dataSorting[countData];
} dataStatSorting[countSort];

/* сортировка выбором
1) ищем минимальный во всем массиве с текущего положения и до конца массива, 
2) переставляем минимальный с текущим членом массаива
*/
void ChoiceSorting(int *arr, int size, int indx) {
	int min, c;
	clock_t start, end;
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
	end = clock();
	dataStatSorting[ChoiceSort].name = "ChoiceSort";
	dataStatSorting[ChoiceSort].dataSorting[indx].time = (clock() - start) / (float)CLK_TCK;
	dataStatSorting[ChoiceSort].dataSorting[indx].countCompare = countCompare;
	dataStatSorting[ChoiceSort].dataSorting[indx].countSwap = countSwap;
}

/* сортировка пузырьком
*/
void BubbleSorting(int *arr, int size, int indx) {
	clock_t start, end;
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
		size--; // сдвигаем правую границу, т.к. самый большой эл-т будет сдвинут вправо
	} 
	end = clock();
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

void PrintData(int size) {
	// вывод результатов
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
			// данные:
			//0 - случайны и неотсортированны
			//1 - отсортированные по возрастанию
			//2 - отсортированные по убыванию
			//3 - по возрастанию, за исключением элемента с индексом  (size/4)
			//4 - по возрастанию, за исключением элемента с индексом  3*(size/4)
			//5 - по убыванию, за исключением индексов массивов (size/4)
			//6 - по убыванию, за исключением индексов массивов 3*(size/4) 
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
		}
		delete[] arr;
		delete[] tmpArr;
		PrintData(sizes[i]);
	}
}