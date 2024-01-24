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

vector<vector<int>> calcPower(vector<vector<int>> &base, int exp)
{
    // Initialize result matrix with zeros
    int size = base.size();
    vector<int> temp(size, 0);
    vector<vector<int>> res(size, temp);
    for (int i = 0; i < size; i++)
        res[i][i] = 1;

    if (exp == 0)
        return res;

    while (exp > 1)
    {
        // If exponent is odd, multiply result by base and decrement exponent
        if (exp % 2 == 1)
        {
            res = multiplyMatrices(base, res);
            exp--;
        }
        // Square the base and halve the exponent
        base = multiplyMatrices(base, base);
        exp /= 2;
    }

    return multiplyMatrices(base, res);
}

int main()
{
    int size, power;
    vector<vector<int>> vec;

    cout << "Enter Size of Matrix: ";
    cin >> size;
    if (size <= 0)
    {
        cout << "Invalid matrix size. Please enter a positive integer." << endl;
        return -1;
    }

    cout << "\nEnter Elements of 1st Matrix: \n";
    takeInput(vec, size, size);

    cout << "Enter power: ";
    cin >> power;
    if (power < 0)
    {
        cout << "Invalid power. Please enter a non-negative integer." << endl;
        return -1;
    }

    vector<vector<int>> res = calcPower(vec, power);
    cout << "\nPower of Matrix is: \n";
    printMatrix(res);
    return 0;
}
