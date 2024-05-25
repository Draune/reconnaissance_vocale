from tensorflow.keras.optimizers import Adam
from tensorflow.keras.callbacks import LearningRateScheduler
import tensorflow as tf
import numpy as np
import datetime
import training_model

import filters
import activation_functions

import test3
import training3

tf.keras.backend.set_floatx('float32')
model = tf.keras.Sequential()
model.add(tf.keras.layers.Input(shape=(13, 60, 1)))
conv_layer = tf.keras.layers.Conv2D(1, (3, 3), activation='linear')
conv_layer.build((None, 13, 60, 1))  # Construire la couche pour initialiser les poids
conv_layer.set_weights([filters.filters[3],np.zeros(1)])
model.add(conv_layer)
model.add(tf.keras.layers.MaxPooling2D((2, 2)))
model.add(tf.keras.layers.Flatten())
model.add(tf.keras.layers.Dense(64, activation=activation_functions.activation_funcs[2]))
model.add(tf.keras.layers.Dense(4, activation='sigmoid'))

model.compile(optimizer=Adam(learning_rate=0.01), loss='binary_crossentropy', metrics=['accuracy'])

model.summary()

log_dir = "./logs/fit/"+"final3" + datetime.datetime.now().strftime("%Y%m%d-%H%M%S")
tensorboard_callback = tf.keras.callbacks.TensorBoard(log_dir=log_dir, histogram_freq=1)

model.fit(training3.training_inputs,training3.training_outputs,epochs=100,validation_data=(test3.test_inputs,test3.test_outputs),callbacks=[tensorboard_callback])

weights_biases = model.get_weights()

print('float weights[] = {', end="")
for l, (w, b) in enumerate(zip(weights_biases[::2], weights_biases[1::2])):
    print()
    for j in range(0, w.shape[1]):
        print('  ', end='')
        for i in range(0, w.shape[0]):
            print(w[i][j], end=', ')
        print()
print('};\n')