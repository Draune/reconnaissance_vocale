import numpy as np

# pour ameliorer la netteté
laplacian_kernel = np.array([[0, -1, 0],
                             [-1, 4, -1],
                             [0, -1, 0]], dtype='float32').reshape((3, 3, 1, 1))

# pour flou
blur_kernel = np.array([[1/9, 1/9, 1/9],
                        [1/9, 1/9, 1/9],
                        [1/9, 1/9, 1/9]], dtype='float32').reshape((3, 3, 1, 1))

# pour lignes horizontales
sobel_x_kernel = np.array([[-1, -1, -1],
                           [2,  2,  2],
                           [-1, -1, -1]], dtype='float32').reshape((3, 3, 1, 1))

# pour lignes verticales
sobel_y_kernel = np.array([[-1, 2, -1],
                           [-1, 2, -1],
                           [-1, 2, -1]], dtype='float32').reshape((3, 3, 1, 1))

# tableau de filtres
nb_filters = 4
filters = [laplacian_kernel,blur_kernel,sobel_x_kernel,sobel_y_kernel]