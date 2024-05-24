import numpy as np
import tensorflow as tf

sobel_y_kernel = np.array([[-0.5326495, 2.6255102,-0.49177617 ],
                      [-0.5265761, 2.643906, -0.44409272],
                      [-0.55045366, 2.625338, -0.47660905]], dtype='float32').reshape((3, 3, 1, 1))

matrice_test = np.array([[
        [0.1, 0.2, 0.3, 0.4, 0.5, 0.6],
        [0.7, 0.8, 0.9, 1.0, 1.1, 1.2],
        [1.3, 1.4, 1.5, 1.6, 1.7, 1.8],
        [1.9, 2.0, 2.1, 2.2, 2.3, 2.4],
        [2.5, 2.6, 2.7, 2.8, 2.9, 3.0],
        [3.1, 3.2, 3.3, 3.4, 3.5, 3.6]
    ]], dtype='float32')

model = tf.keras.Sequential()
model.add(tf.keras.layers.Input(shape=(6, 6, 1)))
conv_layer = tf.keras.layers.Conv2D(1, (3, 3), activation='linear')
conv_layer.build((None, 6, 6, 1))  # Construire la couche pour initialiser les poids
conv_layer.set_weights([sobel_y_kernel,np.zeros(1)])
model.add(conv_layer)
model.summary()


predictions = model.predict(matrice_test)

weights_biases = model.get_weights()

print('float weights[] = [', end="")
for l, (w, b) in enumerate(zip(weights_biases[::2], weights_biases[1::2])):
    print()
    for j in range(0, w.shape[1]):
        print('  ', end='')
        for i in range(0, w.shape[0]):
            print(w[i][j], end=', ')
        print()
print('];\n')

# Afficher les prédictions
print(predictions)

# python result

# 3.9161122   4.403372    4.890632    5.3778915
# 6.8396707   7.32693     7.81419     8.30145  
# 9.763229    10.250488   10.737749   11.225008 
# 12.686786   13.1740465  13.661307   14.148566 


# arduino result

# 3.92    4.40    4.89    5.38
# 6.84    7.33    7.81    8.30
# 9.76    10.25   10.74   11.23
# 12.69   13.17   13.66   14.15 