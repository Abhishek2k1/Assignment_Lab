#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void displayMatrix(double mat[100][100], int n)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void luDecomposition(double mat[100][100], int n)
{
    double lower[100][100] = {0};
    double upper[100][100] = {0};

    for (int i = 0; i < n; ++i)
    {
        lower[i][i] = 1;

        for (int k = i; k < n; ++k)
        {
            double sum = 0;
            for (int j = 0; j < i; ++j)
            {
                sum += (lower[i][j] * upper[j][k]);
            }
            upper[i][k] = mat[i][k] - sum;
        }

        for (int k = i; k < n; ++k)
        {
            double sum = 0;
            for (int j = 0; j < i; ++j)
            {
                sum += (lower[k][j] * upper[j][i]);
            }
            lower[k][i] = (mat[k][i] - sum) / upper[i][i];
        }
    }

    cout << "Lower Triangular Matrix (MatL):\n";
    displayMatrix(lower, n);
    cout << "Upper Triangular Matrix (MatU):\n";
    displayMatrix(upper, n);
}

int main()
{
    int N;
    cout << "Enter the size of the matrix (N): ";
    cin >> N;

    double Mat[100][100];

    srand(time(0)); // Seed for random number generation based on current time

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            Mat[i][j] = rand() % 10 + 1; // Random numbers from 1 to 10
        }
    }

    cout << "Original Matrix (Mat):\n";
    displayMatrix(Mat, N);

    luDecomposition(Mat, N);

    return 0;
}
