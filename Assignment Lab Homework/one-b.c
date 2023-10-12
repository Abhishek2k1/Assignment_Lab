#include <stdio.h>
#include <math.h>

#define MAX_SIZE 100
#define TOLERANCE 1e-6
#define MAX_ITERATIONS 1000

double matrix[MAX_SIZE][MAX_SIZE];
int n;

double matrixMultiply(double x)
{
    double result = 0.0;
    for (int i = 0; i < n; i++)
    {
        result += matrix[n - 1][i] * x; // Use the last row of the matrix for multiplication
    }
    return result;
}

int main()
{
    printf("Enter the size of the square matrix (n x n): ");
    scanf("%d", &n);

    printf("Enter the elements of the matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%lf", &matrix[i][j]);
        }
    }

    double lambda = 1.0; // Initial eigenvalue estimate
    double prevLambda = 0.0;
    double shift = 0.0; // Initial shift value

    for (int iteration = 0; iteration < MAX_ITERATIONS; iteration++)
    {
        // Apply a shift to the eigenvalue estimate
        double shiftedMatrixValue = matrixMultiply(lambda - shift);

        lambda = shiftedMatrixValue + shift;

        // Check for convergence
        if (iteration > 0 && fabs(lambda - prevLambda) < TOLERANCE)
        {
            break;
        }

        prevLambda = lambda;
    }

    printf("Highest eigenvalue: %lf\n", lambda);

    return 0;
}
