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

tf.keras.backend.set_floatx('float32')
model = training_model.create_model(1,[3],1,[4],2,0.005)

model.summary()

log_dir = "./logs/fit/"+"final" + datetime.datetime.now().strftime("%Y%m%d-%H%M%S")
tensorboard_callback = tf.keras.callbacks.TensorBoard(log_dir=log_dir, histogram_freq=1)

model.fit(training.training_inputs,training.training_outputs,epochs=50,validation_data=(test.test_inputs,test.test_outputs),callbacks=[tensorboard_callback])

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