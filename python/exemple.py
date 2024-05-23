from tensorflow.keras.optimizers import Adam
from tensorflow.keras.callbacks import LearningRateScheduler
import tensorflow as tf
import numpy as np


# Define if you want to use biases
IS_BIASED = True

# Enable 32-bit floating-point precision
tf.keras.backend.set_floatx('float32')

# Define the XOR gate inputs and outputs
inputs  = np.array([
    [ 0, 0, 0 ], 
    [ 0, 0, 1 ], 
    [ 0, 1, 0 ], 
    [ 0, 1, 1 ], 
    [ 1, 0, 0 ], 
    [ 1, 0, 1 ], 
    [ 1, 1, 0 ], 
    [ 1, 1, 1 ]
], dtype = np.float32)
outputs = np.array([[0], [1], [1], [0], [1], [0], [0], [1]], dtype = np.float32)
input_size = 3

# Create a simple convolutional neural network
model = tf.keras.Sequential([
    tf.keras.layers.Input(shape=(input_size,)), # Input layer (no bias) 
    tf.keras.layers.Dense(3, activation='sigmoid', use_bias=IS_BIASED), # Dense  3 units 
    tf.keras.layers.Dense(1, activation='sigmoid', use_bias=IS_BIASED)  # Output 1 unit 
])

# Compile the model
optimizer = Adam(learning_rate=0.031)
model.compile(optimizer=optimizer, loss='binary_crossentropy', metrics=['accuracy'])

# Train the model
model.fit(inputs, outputs, epochs=900, verbose=0)

# Evaluate the model on the training data
loss, accuracy = model.evaluate(inputs, outputs)
print(f"Model accuracy: {accuracy * 100:.2f}%")

# Predict XOR gate outputs
predictions = model.predict(inputs)
print("Predictions:")
for i in range(len(inputs)):
    print(f"Input: {inputs[i]}, Predicted Output: {predictions[i][0]:.7f}")

# Print biases and weights
# (IMPORTANT NOTE! they are printed as w[i][j] not w[j][i] | outputs * inputs)
print()
weights_biases = model.get_weights()

if IS_BIASED:
    print("#define _2_OPTIMIZE B00100000 // MULTIPLE_BIASES_PER_LAYER \n")
    print('float biases[] = {')
    for l, (w, b) in enumerate(zip(weights_biases[::2], weights_biases[1::2])):
        print('  ', end='')
        for j in range(0, w.shape[1]):
            print(b[j], end=', ')
        print()
    print('};\n')
else:
    print("#define _2_OPTIMIZE B01000000 // NO_BIAS \n")

print('float weights[] = {', end="")
for l, (w, b) in enumerate(zip(weights_biases[::2], weights_biases[1::2])):
    print()
    for j in range(0, w.shape[1]):
        print('  ', end='')
        for i in range(0, w.shape[0]):
            print(w[i][j], end=', ')
        print()
print('};\n')
