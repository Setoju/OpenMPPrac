#include <iostream>
#include <cstdlib> // for rand() and srand()
#include <ctime>
#include <omp.h>

using namespace std;

const int ROWS = 10000;
const int COLS = 10000;

int matrix[ROWS][COLS];
long long row_sums[ROWS];

void init_matrix() {
    srand(time(NULL)); // it passes current time and since it changes every second it will generate different random numbers each time
    for (int i = 0; i < ROWS; ++i)
        for (int j = 0; j < COLS; ++j)
            matrix[i][j] = rand();
}

long long total_sum(int num_threads) {
    long long sum = 0;
    double start = omp_get_wtime();

#pragma omp parallel for reduction(+:sum) num_threads(num_threads)
    for (int i = 0; i < ROWS; ++i)
        for (int j = 0; j < COLS; ++j)
            sum += matrix[i][j];

    double end = omp_get_wtime();
    cout << "Total sum calculated in " << end - start << " seconds with " << num_threads << " threads.\n";
    return sum;
}

void min_row_sum(int num_threads, int& min_row_index, long long& min_sum) {
    double start = omp_get_wtime();

#pragma omp parallel for num_threads(num_threads)
    for (int i = 0; i < ROWS; ++i)
        for (int j = 0; j < COLS; ++j)
            row_sums[i] += matrix[i][j];

    min_sum = row_sums[0];
    min_row_index = 0;

    // Better approach but still no visible time improvements?   
#pragma omp parallel for num_threads(num_threads)
    for (int i = 0; i < ROWS; ++i) {
        long long local_min = row_sums[i];
        int local_index = i;
        if (local_min >= min_sum)
            continue;


#pragma omp critical
        {
            if (local_min < min_sum) {
                min_sum = local_min;
                min_row_index = local_index;
            }
        }
    }

    double end = omp_get_wtime();
    cout << "Min row sum found in " << end - start << " seconds with " << num_threads << " threads.\n";
}

int main() {
    init_matrix();

    omp_set_nested(1);
    int min_row_idx = -1;
    long long min_val = 0, total = 0;

#pragma omp parallel sections
    {
#pragma omp section
        {
            total = total_sum(8);
        }

#pragma omp section
        {
            min_row_sum(8, min_row_idx, min_val);
        }
    }

    /*total = total_sum(1);

    min_row_sum(1, min_row_idx, min_val);*/

    cout << "Total sum of matrix elements: " << total << endl;
    cout << "Row with minimum sum: " << min_row_idx << " (sum = " << min_val << ")\n";

    return 0;
}
