#include <iostream>
#include <vector>

using namespace std;

// Function to find a local minima in a given range of the vector
int local_minima(vector<int> &vec, int low, int high, int n)
{
    int mid = low + (high - low) / 2;

    // Check if the middle element is a local minima
    if ((mid == 0 || vec[mid - 1] > vec[mid]) && (mid == n - 1 || vec[mid + 1] > vec[mid]))
        return mid;

    // If the element to the left of the middle is smaller, search in the left half
    else if (mid > 0 && vec[mid - 1] < vec[mid])
        return local_minima(vec, low, mid - 1, n);

    // Else search in the right half
    return local_minima(vec, mid + 1, high, n);
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

    int minima_index = local_minima(vec, 0, n - 1, n);
    cout << "Local minima is " << vec[minima_index] << " and its index is " << minima_index << endl;

    return 0;
}
