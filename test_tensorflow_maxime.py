from tensorflow.keras.optimizers import Adam
from tensorflow.keras.callbacks import LearningRateScheduler
import tensorflow as tf
import numpy as np
import datetime

import filters
import activation_functions

import test
import training

# Define if you want to use biases
IS_BIASED = True


# Enable 32-bit floating-point precision
tf.keras.backend.set_floatx('float32')



for i in range [2, 100] :#nombre de neurones par couches
    for j in range [0,activation_functions.nb_activation_func - 1] :
        for k in range [0, filters.nb_filters - 1] :
            for l in range [1,50] :# incremetation de 0.005 sec du learning rate
                for m in range [1,4] : #nombre de couches du réseau de neuronnes
                    for o in range [1,4] : #nombre de couches du réseau de neuronnes
                        for n in range [1,5] : #nombre de epoch
                            # Définir le modèle
                            model = tf.keras.Sequential()

                            # Couche de convolution 
                            laplacian_layer = tf.keras.layers.Conv2D(1, (3, 3), activation='linear', input_shape=(13, 48, 1), use_bias=False)
                            laplacian_layer.build((None, 13, 48, 1))  # Build the layer to initialize weights
                            laplacian_layer.set_weights([laplacian_kernel])
                            model.add(laplacian_layer)
                            model.add(tf.keras.layers.MaxPooling2D((2, 2))) #faire varier entre 1 et 3 pour la boucle for

                            model.add(tf.keras.layers.Flatten())

                            # Couche dense
                            model.add(tf.keras.layers.Dense(i, activation_functions.activation_funcs[j])) #entre 2 et 100

                            # Couche de sortie
                            model.add(tf.keras.layers.Dense(1, activation='sigmoid'))

                            # Compiler le modèle
                            model.compile(optimizer=Adam(learning_rate=0.005 * l), loss='binary_crossentropy', metrics=['accuracy'])

                            # Résumé du modèle
                            #model.summary()

                            #log_dir = "/home/louis/Documents/ece_traitement_numerique_signal/projet/logs/fit/" + datetime.datetime.now().strftime("%Y%m%d-%H%M%S")
                            #tensorboard_callback = tf.keras.callbacks.TensorBoard(log_dir=log_dir, histogram_freq=1)

                            model.fit(training.training_inputs,training.training_outputs,epochs=n,validation_data=(test.test_inputs,test.test_outputs))
                             #,callbacks=[tensorboard_callback]

        
     
        
        

   