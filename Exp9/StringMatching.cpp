#include <iostream>
#include <string>

#define b 256
#define q 101 // Prime number for hash function

using namespace std;

void NaiveSearch(string &pat, string &text)
{
    int lenp = pat.length(), lent = text.length();
    int i, j;

    for (i = 0; i <= lent - lenp; i++)
    {
        for (j = 0; j < lenp; j++)
            if (text[i + j] != pat[j])
                break;

        if (j == lenp)
            cout << "Pattern found at index " << i << endl;
    }
}

void RabinKarpSearch(string &pat, string &text)
{
    int lenp = pat.length(), lent = text.length();
    int i, j, p, t;
    p = t = 0; // hash value for text

    int h = 1;
    // Precompute (b^(lenp-1)) % q
    for (i = 0; i < lenp - 1; i++)
        h = (h * b) % q;

    for (i = 0; i < lenp; i++)
    {
        p = (b * p + pat[i]) % q;
        t = (b * t + text[i]) % q;
    }

    for (i = 0; i <= lent - lenp; i++)
    {
        // Check if the hash values match
        if (p == t)
        {
            // Check for characters one by one
            for (j = 0; j < lenp; j++)
            {
                if (text[i + j] != pat[j])
                    break;
            }
            if (j == lenp)
                cout << "Pattern found at index " << i << endl;
        }

        // Calculate hash value for next window of text
        if (i < lent - lenp)
        {
            t = (b * (t - text[i] * h) + text[i + lenp]) % q;

            // Ensure t is non-negative
            if (t < 0)
                t = (t + q);
        }
    }
}

int main()
{
    string text, pat;
    int choice;

    while (true)
    {
        cout << "\nEnter the text: ";
        getline(cin, text);
        cout << "Enter the pattern: ";
        getline(cin, pat);

        cout << "\nChoose search algorithm:" << endl;
        cout << "1. Naive Search" << endl;
        cout << "2. Rabin-Karp Search" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;

        switch (choice)
        {
        case 1:
            NaiveSearch(pat, text);
            break;

        case 2:
            RabinKarpSearch(pat, text);
            break;

        case 3:
            exit(0);

        default:
            cout << "Invalid choice." << endl;
        }

        cin.ignore(); // Clear the input buffer
    }

    return 0;
}