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

for i in range (0, activation_functions.nb_activation_func ) :
    model = training_model.create_model(1,[3],1,[30],i,0.005)

    # Résumé du modèle
    #model.summary()

    log_dir = "./logs/fit/"+str(i)+"func" + datetime.datetime.now().strftime("%Y%m%d-%H%M%S")
    tensorboard_callback = tf.keras.callbacks.TensorBoard(log_dir=log_dir, histogram_freq=1)

    model.fit(training.training_inputs,training.training_outputs,epochs=30,validation_data=(test.test_inputs,test.test_outputs),callbacks=[tensorboard_callback])
    
