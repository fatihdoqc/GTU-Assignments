
import numpy as np
import time


# Generate a random 30x40 matrix
A = np.random.rand(30, 40) + 1j * np.random.rand(30, 40)

start_time = time.time()

# Compute the pseudo-inverse of the matrix
A_pseudo_inverse = np.linalg.pinv(A)


end_time = time.time()

elapsed_time = (end_time - start_time) * 1000

print(elapsed_time)
print("Original matrix (A):")
print(A)
print("\nPseudo-inverse of A:")
print(A_pseudo_inverse)