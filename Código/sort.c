#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define MAX_SIZE 2000005

void bubbleSort(int arr[], int n, long long *swaps)
{
  int temp;
  *swaps = 0;
  for (int i = 0; i < n - 1; i++)
  {
    for (int j = 0; j < n - i - 1; j++)
    {
      if (arr[j] > arr[j + 1])
      {
        temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
        (*swaps)++;
      }
    }
  }
}

void selectionSort(int arr[], int n, long long *swaps)
{
  int minIndex, temp;
  *swaps = 0;
  for (int i = 0; i < n - 1; i++)
  {
    minIndex = i;
    for (int j = i + 1; j < n; j++)
    {
      if (arr[j] < arr[minIndex])
      {
        minIndex = j;
      }
    }
    if (minIndex != i)
    {
      temp = arr[minIndex];
      arr[minIndex] = arr[i];
      arr[i] = temp;
      (*swaps)++;
    }
  }
}

void insertionSort(int arr[], int n, long long *swaps)
{
  int key, j;
  *swaps = 0;
  for (int i = 1; i < n; i++)
  {
    key = arr[i];
    j = i - 1;
    while (j >= 0 && arr[j] > key)
    {
      arr[j + 1] = arr[j];
      (*swaps)++;
      j = j - 1;
    }
    arr[j + 1] = key;
  }
}

void bucketSort(int arr[], int n, long long *swaps)
{
  int i, j, k, range, numberOfBuckets;
  int max = arr[0];
  *swaps = 0;

  for (i = 1; i < n; i++)
  {
    if (arr[i] > max)
    {
      max = arr[i];
    }
  }

  numberOfBuckets = ceil(sqrt(n));
  if (numberOfBuckets == 0)
  {
    numberOfBuckets = 1;
  }

  range = (max + 1) / numberOfBuckets;
  if (range == 0)
  {
    range = 1;
  }

  int **buckets = (int **)malloc(sizeof(int *) * numberOfBuckets);
  int *bucketSizes = (int *)calloc(numberOfBuckets, sizeof(int));

  for (i = 0; i < numberOfBuckets; i++)
  {
    buckets[i] = (int *)malloc(sizeof(int) * (n + 1));
    bucketSizes[i] = 0;
  }

  for (i = 0; i < n; i++)
  {
    j = arr[i] / range;
    if (j >= numberOfBuckets)
    {
      j = numberOfBuckets - 1; // Clamp to the last bucket
    }
    buckets[j][bucketSizes[j]++] = arr[i];
  }

  k = 0;
  long long localSwaps;
  for (i = 0; i < numberOfBuckets; i++)
  {
    insertionSort(buckets[i], bucketSizes[i], &localSwaps);
    *swaps += localSwaps;
    for (j = 0; j < bucketSizes[i]; j++)
    {
      arr[k++] = buckets[i][j];
    }
  }

  for (i = 0; i < numberOfBuckets; i++)
  {
    free(buckets[i]);
  }
  free(buckets);
  free(bucketSizes);
}

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    printf("Usage: %s <sort_algorithm>\n", argv[0]);
    printf("sort_algorithm: bubble, selection, insertion, or bucket\n");
    return 1;
  }

  int arr[MAX_SIZE];
  int n = 0;
  long long swaps;

  while (scanf("%d", &arr[n]) != EOF)
  {
    n++;
  }

  clock_t start_time = clock();

  if (strcmp(argv[1], "bubble") == 0)
  {
    bubbleSort(arr, n, &swaps);
  }
  else if (strcmp(argv[1], "selection") == 0)
  {
    selectionSort(arr, n, &swaps);
  }
  else if (strcmp(argv[1], "insertion") == 0)
  {
    insertionSort(arr, n, &swaps);
  }
  else if (strcmp(argv[1], "bucket") == 0)
  {
    bucketSort(arr, n, &swaps);
  }
  else
  {
    printf("Invalid sort algorithm. Choose 'bubble', 'selection', 'insertion', or 'bucket'.\n");
    return 1;
  }

  clock_t end_time = clock();
  double time_spent = (double)(end_time - start_time) * 1000.0 / CLOCKS_PER_SEC;

  printf("%lld %f\n", swaps, time_spent);

  return 0;
}
