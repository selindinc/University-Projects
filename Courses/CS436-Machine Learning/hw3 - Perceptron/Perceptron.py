from __future__ import print_function
from nltk.stem.porter import *
import os, re
from collections import \
    Counter  # A counter is a container that stores elements as dictionary keys, and their counts are stored as dictionary values.

'''Please adjust the directories according to your own file'''
source_directory = '/Users/selindinc/Desktop/CS436-MachineLearning/assignments/hw3/train/'

stop_words_directory = '/Users/selindinc/Desktop/CS436-MachineLearning/assignments/hw3/'

test_directory = '/Users/selindinc/Desktop/CS436-MachineLearning/assignments/hw3/test/'

'''#############################################################################################'''

stop_flag = 0
'''please turn flag 0 to remove the stop words from the data'''


class BagOfWords:
    def __init__(self):
        self.num_docs = 0  # number of how many times a word appeared in a document
        self.total_word_num = 0
        self.frequency = Counter()
        self.type = 0

    def bag(self, num_docs, frequency, type):
        self.num_docs = num_docs
        self.frequency = frequency
        self.total_word_num = sum(frequency.values())
        self.type = type
        return self


class Stem:
    counter = Counter()

    def __init__(self):
        self.stemmed_words_ham = []
        self.stemmed_words_spam = []
        self.spam_doc_count = 0
        self.ham_doc_count = 0
        self.stop_words = []
        self.test_doc_count = 0
        self.bag_test_array = []
        self.weight = Counter()
        self.bags_array = []

    def setStopWords(self, path):
        with open(path, 'rb+') as file:
            if stop_flag == 0:
                self.stop_words = file.read().decode('latin-1').strip()
            else:
                self.stop_words = []
        return self.stop_words

    def test_stemmer(self):

        stemmer = PorterStemmer()
        self.setStopWords(stop_words_directory + 'stop_words.txt')
        for label in ['spam/', 'ham/']:
            for filename in os.listdir(test_directory + label):
                path = label + filename
                with open(test_directory + path, 'rb+') as f:
                    wordss = re.findall(r'\w[a-z]+', f.read().decode('latin-1').lower())

                    test_words = []
                    test_words.extend(wordss)
                    stemmed_test_words = []
                    counter = Counter()
                    for w in test_words:
                        if w not in self.stop_words:
                            words = stemmer.stem(w)
                            stemmed_test_words.append(words)
                            self.test_doc_count += 1

                    for w2 in stemmed_test_words:
                        counter[w2] += 1
                    if label == "spam/":
                        bag_test = BagOfWords().bag(self.test_doc_count, counter, 0)
                    if label == "ham/":
                        bag_test = BagOfWords().bag(self.test_doc_count, counter, 1)
                    self.bag_test_array.append(bag_test)

        return self.bag_test_array

    def stemmer(self):
        stemmer = PorterStemmer()

        self.setStopWords(stop_words_directory + 'stop_words.txt')

        for label in ['spam/', 'ham/']:

            for filename in os.listdir(source_directory + label):
                path = label + filename
                with open(source_directory + path, 'rb+') as f:
                    words = re.findall(r'\w[a-z]+', f.read().decode('latin-1').lower())

                    for word in words:
                        if word not in self.stop_words:
                            if label == 'ham/':
                                self.stemmed_words_ham.append(stemmer.stem(word))
                                self.ham_doc_count += 1

                            if label == 'spam/':
                                self.stemmed_words_spam.append(stemmer.stem(word))
                                self.spam_doc_count += 1

        spam_counter = Counter()
        for word1 in self.stemmed_words_spam:
            spam_counter[word1] += 1
        bag_spam = BagOfWords().bag(self.spam_doc_count, spam_counter, 0)
        ham_counter = Counter()
        for word in self.stemmed_words_ham:
            ham_counter[word] += 1
        bag_ham = BagOfWords().bag(self.ham_doc_count, ham_counter, 1)
        self.weight = ham_counter + spam_counter

        return bag_spam, bag_ham, self.weight

    def UltimateBags(self):  # puts every texts in a bag and then cretaes an array that contains that bags
        stemmer = PorterStemmer()

        self.setStopWords(stop_words_directory + 'stop_words.txt')

        for label in ['spam/', 'ham/']:
            for filename in os.listdir(source_directory + label):
                path = label + filename
                with open(source_directory + path, 'rb+') as f:
                    words = re.findall(r'\w[a-z]+', f.read().decode('latin-1').lower())

                    stemmed_words = []
                    stemmed_words_count = Counter()

                    for word in words:
                        if word not in self.stop_words:
                            stemmed_words.append(stemmer.stem(word))

                    for w in stemmed_words:
                        stemmed_words_count[w] += 1

                    if label == 'ham/':
                        bag = BagOfWords().bag(1, stemmed_words_count, 1)
                        self.bags_array.append(bag)
                    else:

                        bag = BagOfWords().bag(1, stemmed_words_count, 0)
                        self.bags_array.append(bag)

        return self.bags_array


class PerceptronAlgorithm:

    def BagClassReturn(self, bag, weight):  # spam=0 ham=1 #finds the class of the bag
        sum_of_weights = 0
        for word, freq in bag.frequency.items():
            sum_of_weights = sum_of_weights + freq * weight[word]
        if sum_of_weights <= 0:
            return 0  # spam
        else:
            return 1  # ham

    def perceptron(self, weight, learning_rate, bag_array, num_of_iter):

        for bag in bag_array:
            for i in range(0, num_of_iter):
                class_return = self.BagClassReturn(bag, weight)

                delta_class = bag.type - class_return  # new sign check -1 or 1

                for word, freq in bag.frequency.items():
                    weight[word] = weight[word] + learning_rate * delta_class * freq  # calclulate delta weight
