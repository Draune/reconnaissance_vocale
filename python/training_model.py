from tensorflow.keras.optimizers import Adam
from tensorflow.keras.callbacks import LearningRateScheduler
import tensorflow as tf
import numpy as np
import datetime
import random
import filters
import activation_functions

tf.keras.backend.set_floatx('float32')

def create_model(nb_filters,num_filters,nb_dense_layer,nb_neurones,activation_function,learning_rate):
    model = tf.keras.Sequential()
    model.add(tf.keras.layers.Input(shape=(13, 48, 1)))

    
    if (nb_filters > 0):
        combined_kernels = []
        if (nb_filters == 1):
            combined_kernels = filters.filters[num_filters[0]]
        elif (nb_filters == 2):
            combined_kernels = np.concatenate([filters.filters[num_filters[0]],filters.filters[num_filters[1]]], axis=-1)
        else:
            combined_kernels = np.concatenate([filters.filters[num_filters[0]],filters.filters[num_filters[1]],filters.filters[num_filters[2]]], axis=-1)
        conv_layer = tf.keras.layers.Conv2D(nb_filters, (3, 3), activation='linear')
        conv_layer.build((None, 13, 48, 1))  # Construire la couche pour initialiser les poids
        conv_layer.set_weights([combined_kernels,np.zeros(1)])
        model.add(conv_layer)
    model.add(tf.keras.layers.MaxPooling2D((2, 2)))
    model.add(tf.keras.layers.Flatten())

    for i in range(0,nb_dense_layer):
        model.add(tf.keras.layers.Dense(nb_neurones[i], activation=activation_functions.activation_funcs[activation_function]))
    model.add(tf.keras.layers.Dense(1, activation='sigmoid'))
    
    model.compile(optimizer=Adam(learning_rate=learning_rate), loss='binary_crossentropy', metrics=['accuracy'])
    return model
