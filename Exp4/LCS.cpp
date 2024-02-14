#include <iostream>
#include <vector>
using namespace std;

string lcs(string &s1, string &s2)
{
    int m = s1.length(), n = s2.length();

    // Matrix of Size s1 + 1 x s2 + 1
    vector<vector<int>> L(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (s1[i - 1] == s2[j - 1])
                // Diagonal + 1
                L[i][j] = L[i - 1][j - 1] + 1;
            else
                // Max of previous row/column cell value
                L[i][j] = max(L[i - 1][j], L[i][j - 1]);
        }
    }

    // Last cell has length of string
    int index = L[m][n];

    string result(index, '\0');

    int i = m, j = n;
    while (i > 0 && j > 0)
    {
        // Part of LCS
        if (s1[i - 1] == s2[j - 1])
        {
            result[index - 1] = s1[i - 1];
            i--;
            j--;
            index--;
        }
        // Go in direction of larger value
        else if (L[i - 1][j] > L[i][j - 1])
            i--;
        else
            j--;
    }

    return result;
}

int main()
{
    string s1, s2, result;
    cout << "Enter String 1: ";
    cin >> s1;
    cout << "Enter String 2: ";
    cin >> s2;

    result = lcs(s1, s2);
    cout << "\nLCS of " << s1 << " and " << s2 << " is " << result;
    return 0;
}
