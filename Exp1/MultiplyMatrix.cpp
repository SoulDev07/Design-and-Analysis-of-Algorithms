#include <iostream>
#include <vector>
using namespace std;

// Function to take input for a matrix
void takeInput(vector<vector<int>> &vec, int r, int c)
{
    int n;
    for (int i = 0; i < r; i++)
    {
        vector<int> temp(c);
        cout << "\nRow " << i + 1 << ": " << endl;
        for (int j = 0; j < c; j++)
            cin >> temp[j];
        vec.push_back(temp);
    }
}

// Function to print a matrix
void printMatrix(vector<vector<int>> &vec)
{
    for (vector<int> &row : vec)
    {
        for (int val : row)
            cout << val << "\t";
        cout << endl;
    }
}

// Function to multiply two matrices
vector<vector<int>> multiplyMatrices(vector<vector<int>> &arr1, vector<vector<int>> &arr2)
{
    int r1 = arr1.size();
    int c1 = arr1[0].size();
    int c2 = arr2[0].size();

    vector<int> temp(c2, 0);
    vector<vector<int>> res(r1, temp);

    for (int i = 0; i < r1; i++)
        for (int j = 0; j < c2; j++)
            for (int k = 0; k < c1; k++)
                res[i][j] += arr1[i][k] * arr2[k][j];

    return res;
}

int main()
{
    int r1, c1, r2, c2;
    vector<vector<int>> arr1, arr2;

    // Matrix 1
    cout << "Enter No. of Row and Columns of Matrix 1: ";
    cin >> r1 >> c1;
    cout << "\nEnter Elements of 1st Matrix: \n";
    takeInput(arr1, r1, c1);

    // Matrix 2
    cout << "Enter No. of Row and Columns of Matrix 2: ";
    cin >> r2 >> c2;
    cout << "\nEnter Elements of 2nd Matrix: \n";
    takeInput(arr2, r2, c2);

    // Check if both matrix can be multiplied
    if (c1 != r2)
    {
        cout << "\nMatrix cannot be multiplied!";
        return -1;
    }

    vector<vector<int>> res = multiplyMatrices(arr1, arr2);
    cout << "\nMultiplication of Matrix is: \n";
    printMatrix(res);

    return 0;
}
