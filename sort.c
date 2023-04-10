#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

// implements heap sort
// extraMemoryAllocated counts bytes of memory allocated
void heapify(int arr[], int size, int i)
{
	// largest is right child
	int temp;
	int max = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	// if left child is larger than root(parent)
	if (left < size && arr[left]> arr[max])
	{
		// set the max val to left val
		max = left;
	}
	// if right child larger than largest so far
	if (right < size && arr[right]>arr[max])
	{
		// set the max val to right val
		max = right;
	}

	// If largest is not root
	if (max != i)
	{
		// swap
		temp = arr[i];
		arr[i] = arr[max];
		arr[max] = temp;

		// recursively heapify the subtree
		heapify(arr, size, max);
	}
}
	
void heapSort(int arr[], int n)
{
	int temp;
	int x = n/2 -1;
	int y = n - 1;

	for (int i = x; i >= 0; i --)
	{
		heapify(arr, n, i);
	}

	for (int i = y; i >= 0; i -- )
	{
		temp = arr[0];
		arr[0] = arr[i];
		arr[i] = temp;

		heapify(arr, i, 0);
	}
}


// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void merge (int arr[], int l, int m, int r)
{
	int *temp, i, len, cout1, cout2, index;

	len = r - l + 1;
	temp = (int*)malloc(len*sizeof(int));

	cout1 = l;
	cout2 = m +1;

	index = 0;

	// copy array into temp array
	while((cout1 <= m)&&(cout2 <= r))
	{
		if (arr[cout1] < arr[cout2])
		{
			temp[index] = arr[cout1];
			cout1++;
			index++;
		}
		else
		{
			temp[index] = arr[cout2];
			index++;
			cout2++;
		}	
	}
		
	while (cout1 <= m)
	{
		temp[index] = arr[cout1];
		index++;
		cout1++;
	}

	while (cout2 <= r)
	{
		temp[index] = arr[cout2];
		index++;
		cout2++;
	}
	

	for (i = l; i <= r; i++)
	{
		arr[i] = temp[i-l];
	}

	free(temp);
}

void mergeSort(int pData[], int l, int r)
{
	if (l < r)
	{
		// find the middle point to divide the array into two halves
		int m = (l+r)/2;

		//call mergeSort for first half
		mergeSort(pData, l, m);

		// call mergeSort for second half
		mergeSort(pData, m+1, r);

		merge(pData, l, m, r);

		extraMemoryAllocated += sizeof(l) + sizeof(r);
	}
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	int i, n, *data;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i=0;i<dataSz;++i)
		{
			fscanf(inFile, "%d ",&n);
			data = *ppData + i;
			*data = n;
		}

		fclose(inFile);
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
		if(i >= dataSz)
		{
			printf("\n\n");
			return;
		}
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt", "input4.txt" };
	
	for (i=0;i<4;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Heap Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		heapSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}