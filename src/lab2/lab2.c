#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>

void shell_sort(int* array, int size);
void sliyn_sort(int* array, int size);
int load(int* array, int dl, const char* filename);

int lab2_main(void){
	int meth;
	int dl;
	int zp;
	srand(time(0));

	printf("Insert len of array:\n");
	scanf("%d", &dl);

	int *ar1 = (int *)malloc(dl*sizeof(int));

	printf("Choose method:\n 1.Insertion \n 2.Random \n 3.File \n");
	scanf("%d", &zp);

	if (zp == 1) {
		//ввод
		printf("Insert %d numbers:\n", dl);
		for (int i = 0; i < dl; i++) {
			scanf("%d", &ar1[i]);
		}

		printf("Choose method:\n 1.Shell \n 2.Sliyn \n");
		scanf("%d", &meth);

		if (meth == 1) {
			shell_sort(ar1, dl);
		}
		else if (meth == 2) {
			sliyn_sort(ar1, dl);
		}
	}
	if (zp == 2) {
		//рандом
		for (int i = 0; i < dl; i++) {
			ar1[i] = -100 + rand() % (100 +100 + 1);
			}
		
		printf("Your random numbers\n");
		for (int i = 0; i < dl; i++) {
			printf("%d ", ar1[i]);
		}

		printf("\n");
		printf("Choose method:\n 1.Shell \n 2.Sliyn \n");
		scanf("%d", &meth);

		if (meth == 1) {
			shell_sort(ar1, dl);
		}
		else if (meth == 2) {
			sliyn_sort(ar1, dl);
		}

		}
	if (zp == 3) {
		//файл
		char filename[100];
		printf("Enter filename: ");
		scanf("%s", filename);

		int loaded = load(ar1, dl, filename);
		if (loaded <= 0) {
			free(ar1);
			return 1;
		}
		dl = loaded; 
		printf("numbers from file:\n");
		for (int i = 0; i < dl; i++) {
			printf("%d ", ar1[i]);
		}
		printf("\n");
		printf("Choose method:\n 1.Shell \n 2.Sliyn \n");
		scanf("%d", &meth);

		if (meth == 1) {
			shell_sort(ar1, dl);
		}
		else if (meth == 2) {
			sliyn_sort(ar1, dl);
		}
		printf("\n");

		}


		//демонстрация финала 
		for (int i = 0; i < dl; i++) {
			printf("%d ", ar1[i]);
		}

		printf("\n");

		free(ar1);

}
void shell_sort(int* array, int size) {
	for (int s = size / 2; s > 0; s /= 2) {
		for (int i = s; i < size; ++i) {
			for (int j = i - s; j >= 0 && array[j] > array[j + s]; j -= s) {
				int temp = array[j];
				array[j] = array[j + s];
				array[j + s] = temp;
			}
		}
	}
}

void merge(int* array, int left, int mid, int right) {
	int n1 = mid - left + 1;
	int n2 = right - mid;

	int* L = (int*)malloc(n1 * sizeof(int));
	int* R = (int*)malloc(n2 * sizeof(int));

	for (int i = 0; i < n1; i++)
		L[i] = array[left + i];
	for (int j = 0; j < n2; j++)
		R[j] = array[mid + 1 + j];

	int i = 0, j = 0, k = left;
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			array[k] = L[i];
			i++;
		}
		else {
			array[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1) {
		array[k] = L[i];
		i++;
		k++;
	}

	while (j < n2) {
		array[k] = R[j];
		j++;
		k++;
	}

	free(L);
	free(R);
}

void merge_sort_recursive(int* array, int left, int right) {
	if (left < right) {
		int mid = left + (right - left) / 2;

		merge_sort_recursive(array, left, mid);
		merge_sort_recursive(array, mid + 1, right);

		merge(array, left, mid, right);
	}
}

void sliyn_sort(int* array, int size) {
	merge_sort_recursive(array, 0, size - 1);
}

int load(int* array, int dl, const char* filename) {
	FILE* fpin = fopen(filename, "r");
	if (!fpin) {
		printf("Error '%s'\n", filename);
		return -1;
	}

	int count = 0;
	while (count < dl && fscanf(fpin, "%d", &array[count]) == 1) {
		count++;
	}

	fclose(fpin);

	if (count < dl) {
		printf(" only %d numbers (expected %d)\n", count, dl);
	}

	return count; 
}