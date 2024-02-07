#include <iostream>
#include <vector>

using namespace std;

void merge(vector<int> &vec, int left, int mid, int right)
{
    int arr1size = mid - left + 1;
    int arr2size = right - mid;

    vector<int> leftarr(arr1size), rightarr(arr2size);

    for (int i = 0; i < arr1size; i++)
        leftarr[i] = vec[left + i];
    for (int i = 0; i < arr2size; i++)
        rightarr[i] = vec[mid + i + 1];

    auto indexOfarr1 = 0, indexOfarr2 = 0;
    int indexOfMergedarr = left;

    while (indexOfarr1 < arr1size && indexOfarr2 < arr2size)
    {
        if (leftarr[indexOfarr1] <= rightarr[indexOfarr2])
        {
            vec[indexOfMergedarr] = leftarr[indexOfarr1];
            indexOfarr1++;
        }
        else
        {
            vec[indexOfMergedarr] = rightarr[indexOfarr2];
            indexOfarr2++;
        }
        indexOfMergedarr++;
    }

    while (indexOfarr1 < arr1size)
    {
        vec[indexOfMergedarr] = leftarr[indexOfarr1];
        indexOfarr1++;
        indexOfMergedarr++;
    }

    while (indexOfarr2 < arr2size)
    {
        vec[indexOfMergedarr] = rightarr[indexOfarr2];
        indexOfarr2++;
        indexOfMergedarr++;
    }
}

void mergeSort(vector<int> &vec, int begin, int end)
{
    if (begin >= end)
        return;

    int mid = begin + (end - begin) / 2;
    mergeSort(vec, begin, mid);
    mergeSort(vec, mid + 1, end);
    merge(vec, begin, mid, end);
}

// Function to find the missing number in a sorted array
int search(int vec[], int size)
{
    // Extreme cases
    if (vec[0] != 1)
        return 1;
    if (vec[size - 1] != (size + 1))
        return size + 1;

    // Binary search to find the missing number
    int a = 0, b = size - 1;
    int mid;

    while ((b - a) > 1)
    {
        mid = (a + b) / 2;

        // If the difference between element and index is not consistent,
        // adjust the search range accordingly
        if ((vec[a] - a) != (vec[mid] - mid))
            b = mid;
        else if ((vec[b] - b) != (vec[mid] - mid))
            a = mid;
    }

    // Return the missing number
    return (vec[a] + 1);
}

int main()
{
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    if (n <= 0)
    {
        cout << "Invalid number of elements. Exiting..." << endl;
        return -1;
    }

    vector<int> vec(n);
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++)
        cin >> vec[i];

    mergeSort(vec, 0, n - 1);

    cout << "Missing number: " << search(&vec[0], n) << endl;

    return 0;
}
