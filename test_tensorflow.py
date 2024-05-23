from tensorflow.keras.optimizers import Adam
from tensorflow.keras.callbacks import LearningRateScheduler
import tensorflow as tf
import numpy as np
import datetime
import random

import test
import training

is_max_pool = random.randint(0,1)


# Define if you want to use biases
IS_BIASED = True

# Enable 32-bit floating-point precision
tf.keras.backend.set_floatx('float32')

# Définir le modèle
model = tf.keras.Sequential()

model.add(tf.keras.layers.Input(shape=(13, 48, 1)))
model.add(tf.keras.layers.MaxPooling2D((2, 2)))
model.add(tf.keras.layers.Flatten())

# Couche dense

model.add(tf.keras.layers.Dense(30, activation='sigmoid'))

# Couche de sortie
model.add(tf.keras.layers.Dense(1, activation='sigmoid'))

# Compiler le modèle
model.compile(optimizer=Adam(learning_rate=0.005), loss='binary_crossentropy', metrics=['accuracy'])

# Résumé du modèle
model.summary()

log_dir = "/home/louis/Documents/ece_traitement_numerique_signal/projet/logs/fit/" + datetime.datetime.now().strftime("%Y%m%d-%H%M%S")
tensorboard_callback = tf.keras.callbacks.TensorBoard(log_dir=log_dir, histogram_freq=1)

model.fit(training.training_inputs,training.training_outputs,epochs=300,validation_data=(test.test_inputs,test.test_outputs),callbacks=[tensorboard_callback])