#include <stdio.h>

#define MAX_SIZE 100

int main() {
    int n;
    printf("Enter the size of the matrix (n x n): ");
    scanf("%d", &n);

    double matrix[MAX_SIZE][MAX_SIZE];

    printf("Enter the elements of the matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%lf", &matrix[i][j]);
        }
    }

    // Perform row reduction to echelon form
    int rank = 0;
    for (int i = 0; i < n; i++)
    {
        int nonZeroRow = -1;

        // Find the first non-zero element in the current row
        for (int j = 0; j < n; j++)
        {
            if (matrix[i][j] != 0)
            {
                nonZeroRow = i;
                break;
            }
        }

        // If a non-zero element was found, increment the rank
        if (nonZeroRow != -1)
        {
            rank++;

            // Divide the current row by the first non-zero element
            double pivot = matrix[nonZeroRow][nonZeroRow];
            for (int j = 0; j < n; j++)
            {
                matrix[i][j] /= pivot;
            }

            // Eliminate non-zero elements in the current column
            for (int k = 0; k < n; k++)
            {
                if (k != i && matrix[k][nonZeroRow] != 0)
                {
                    double factor = matrix[k][nonZeroRow];
                    for (int j = 0; j < n; j++)
                    {
                        matrix[k][j] -= factor * matrix[i][j];
                    }
                }
            }
        }
    }

    printf("Rank of the matrix is: %d\n", rank);

    return 0;
}
