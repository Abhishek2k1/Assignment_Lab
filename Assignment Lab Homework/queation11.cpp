#include <iostream>
#include <cstring>

using namespace std;

// Function to compute the LPS (Longest Prefix Suffix) array
void computeLPSArray(const char *pattern, int M, int *lps)
{
    int len = 0; // Length of the previous longest prefix suffix
    lps[0] = 0;  // lps[0] is always 0

    int i = 1;
    while (i < M)
    {
        if (pattern[i] == pattern[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
            {
                len = lps[len - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// Function to perform pattern searching using KMP algorithm
void KMPSearch(const char *text, const char *pattern)
{
    int M = strlen(pattern); // Length of the pattern
    int N = strlen(text);    // Length of the text

    int lps[M]; // Array to hold the Longest Prefix Suffix values

    // Compute the LPS array
    computeLPSArray(pattern, M, lps);

    int i = 0; // Index for text[]
    int j = 0; // Index for pattern[]

    // Iterate through the text to find the pattern
    while (i < N)
    {
        if (pattern[j] == text[i])
        {
            j++;
            i++;
        }
        if (j == M)
        {
            cout << "Pattern found at index " << i - j << endl;
            j = lps[j - 1];
        }
        else if (i < N && pattern[j] != text[i])
        {
            if (j != 0)
            {
                j = lps[j - 1];
            }
            else
            {
                i++;
            }
        }
    }
}

int main()
{
    const int maxLen = 100;
    char text[maxLen];
    char pattern[maxLen];

    cout << "Enter the text: ";
    cin.getline(text, maxLen);

    cout << "Enter the pattern: ";
    cin.getline(pattern, maxLen);

    cout << "Text: " << text << endl;
    cout << "Pattern: " << pattern << endl;
    cout << "Pattern occurrences:" ;

    // Perform pattern search using KMP algorithm
    KMPSearch(text, pattern);

    return 0;
}
