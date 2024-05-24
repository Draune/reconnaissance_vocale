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
model.add(tf.keras.layers.MaxPooling2D((2, 2)))
model.add(tf.keras.layers.Flatten())

model.summary()


predictions = model.predict(matrice_test)


# Afficher les prédictions
print(predictions)

# python result
# 7.32693    8.30145   13.1740465 14.148566

# arduino result
# 7.33    8.30    13.17   14.15 