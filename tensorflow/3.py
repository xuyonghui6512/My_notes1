# -*- coding: utf-8 -*-

import numpy as np
import sklearn.preprocessing as prep
import tensorflow as tf
from tensorflow.examples.tutorials.mnist import input_data
 
# Xavier prameters initialization method
def xavier_init(fan_in, fan_out, constant = 1): # fan_in and fan_out are the number of the input and output nodes number.
    low = -constant * np.sqrt(6.0 / (fan_in + fan_out))
    high = constant * np.sqrt(6.0 / (fan_in + fan_out))
    return tf.random_uniform( [fan_in,fan_out], # shape 
                      minval = low, maxval = high, # value range
                      dtype = tf.float32) # value type
 
class AdditiveGaussianNoiseAutoencoder(object):
    # Parameters:
    def __init__(self, n_input, n_hidden, transfer_function = tf.nn.softplus, # tf.nn.softplus(x) = np.log(np.exp(x)+1) 
                 optimizer = tf.train.AdamOptimizer(learning_rate = 0.001), scale = 0.1):
        self.n_input = n_input #input layer nodes number
        self.n_hidden = n_hidden # hidden layer nodes
        self.transfer = transfer_function # activate function from input to hidden
        self.scale = tf.placeholder(tf.float32) # Placeholder: noise level to be input
        self.training_scale = scale # noise level      
        network_weights = self._initialize_weights() # initialize weights by using Xaiver parameters initialization
        self.weights = network_weights
 
        # define the Net structure
        self.x = tf.placeholder(tf.float32, [None, self.n_input])
        self.hidden = self.transfer(tf.add( tf.matmul(self.x + scale * tf.random_normal((n_input,)), self.weights['w1']), self.weights['b1']))
        self.reconstruction = tf.add( tf.matmul(self.hidden, self.weights['w2']), self.weights['b2'] )     
 
        # define the loss
        self.cost = 0.5 * tf.reduce_sum(tf.pow(tf.subtract(self.reconstruction,self.x), 2.0))
#        self.cost = 0.5 * tf.reduce_sum(tf.pow((self.reconstruction-self.x), 2.0))
        self.optimizer = optimizer.minimize(self.cost)
 
        # Session
        init = tf.global_variables_initializer()
        self.sess = tf.Session()
        self.sess.run(init)
 
    def _initialize_weights(self):
        all_weights = dict()
        all_weights['w1'] = tf.Variable(xavier_init(self.n_input, self.n_hidden))
        all_weights['b1'] = tf.Variable(tf.zeros([self.n_hidden], dtype = tf.float32))
        all_weights['w2'] = tf.Variable(tf.zeros([self.n_hidden,self.n_input], dtype = tf.float32))
        all_weights['b2'] = tf.Variable(tf.zeros([self.n_input], dtype = tf.float32))
        return all_weights       
 
 
    # only few results
    def partial_fit(self,X):
        cost,opt = self.sess.run( (self.cost, self.optimizer), feed_dict = {self.x: X, self.scale: self.training_scale} )
        return cost
 
    # all the results    
    def clac_total_cost(self,X):
        return self.sess.run(self.cost, feed_dict = {self.x: X, self.scale: self.training_scale})
 
    # hiiden layer feature
    def transform(self,X):
        return self.sess.run(self.hidden, feed_dict = {self.x: X, self.scale: self.training_scale})
 
    # from hidden layer to reconstruction layer
    def generate(self, hidden = None):
        if hidden is None:
            hidden = np.random.normal(size = self.weights['b1'])
        return self.sess.run(self.reconstruction, feed_dict = {self.hidden: hidden})
 
    # define the Net: input = input layer output = output layer
    def reconstruct(self, X):
        return self.sess.run(self.reconstruction, feed_dict = {self.x: X, self.scale: self.training_scale})
 
    # define the weights show method 
    def getWeights(self):
        return self.sess.run(self.weights['w1'])
 
    # define the bias show method
    def getBiases(self):
        return self.sess.run(self.weights['b1'])
 
# read the data
mnist = input_data.read_data_sets('MNIST_data', one_hot = True)
 
# preprocess the training data and test data, note that the test data processing method depends on the training data
def standard_scale(X_train, X_test):
    preprocessor = prep.StandardScaler().fit(X_train)
    X_train = preprocessor.transform(X_train)
    X_test = preprocessor.transform(X_test)
    return X_train, X_test
 
# define the traing data batch with some random type(sample without put back)
def get_random_block_from_data(data, batch_size):
    start_index = np.random.randint(0, (len(data)-batch_size))
    return data[start_index:(start_index+batch_size)]
 
# standard_scale the training data    
X_train, X_test = standard_scale(mnist.train.images, mnist.test.images)
 
n_samples = int(mnist.train.num_examples) # the number of the samples
training_epochs = 20 # the loop number 
batch_size = 128 # define the traning batch_size
display_step = 1 # every epoch
 
autoencoder = AdditiveGaussianNoiseAutoencoder(n_input = 784, 
                                               n_hidden = 200,
                                               transfer_function = tf.nn.softplus,
                                               optimizer = tf.train.AdadeltaOptimizer(learning_rate = 0.1),
                                               scale = 0.01)
 
for epoch in range(training_epochs):
    avg_cost = 0
    total_batch = int(n_samples / batch_size) # the number of the batch for each epoch
    for i in range(total_batch):        
        batch_xs = get_random_block_from_data(X_train, batch_size) # batch data 
 
        cost = autoencoder.partial_fit(batch_xs) # save every batch cost
#        print("The %04d batch cost is:" %(i), cost)
        avg_cost += cost / n_samples * batch_size # Note that just output each batch cost
 
    if epoch % display_step == 0:
        print("Epoch:", '%04d' %(epoch+1), "cost=", "{:.9f}".format(avg_cost))
 
# print all the cost on the Test data        
print("Total cost:", str(autoencoder.clac_total_cost(X_test)))
