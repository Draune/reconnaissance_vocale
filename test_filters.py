from tensorflow.keras.optimizers import Adam
from tensorflow.keras.callbacks import LearningRateScheduler
import tensorflow as tf
import numpy as np
import datetime
import training_model

import filters
import activation_functions

import test
import training

IS_BIASED = True


# Enable 32-bit floating-point precision
tf.keras.backend.set_floatx('float32')

for i in range (0, filters.nb_filters ) :
    model = training_model.create_model(1,[i],1,[30],1,0.005)

    # Résumé du modèle
    #model.summary()

    #log_dir = "/home/louis/Documents/ece_traitement_numerique_signal/projet/logs/fit/" + datetime.datetime.now().strftime("%Y%m%d-%H%M%S")
    #tensorboard_callback = tf.keras.callbacks.TensorBoard(log_dir=log_dir, histogram_freq=1)

    model.fit(training.training_inputs,training.training_outputs,epochs=300,validation_data=(test.test_inputs,test.test_outputs))
    #,callbacks=[tensorboard_callback]

