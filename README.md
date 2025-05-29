# Parallel Matrix Computation using OpenMP

This project demonstrates parallel computation on a large matrix using OpenMP in C++. The program performs two main tasks:

1. **Calculates the total sum of all elements in a 10,000 x 10,000 matrix.**
2. **Finds the row with the minimum sum.**

Both tasks can be executed using a configurable number of threads.

---

## Features

- **Matrix Initialization:** Generates a large matrix with random integers using `rand()`.
- **Parallel Sum Calculation:** Computes the total sum of matrix elements using OpenMP with reduction.
- **Parallel Row Minimum:** Identifies the row with the minimum sum, with an option to parallelize using OpenMP.
- **Execution Time Measurement:** Uses `omp_get_wtime()` to measure performance.
