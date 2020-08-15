from __future__ import print_function
from nltk.stem.porter import *
import os, re
from math import log
from collections import \
    Counter  # A counter is a container that stores elements as dictionary keys, and their counts are stored as dictionary values.

'''Please adjust the directories according to your own file'''
source_directory = '/Users/selindinc/Desktop/CS436-MachineLearning/assignments/hw2/train/'

stop_words_directory = '/Users/selindinc/Desktop/CS436-MachineLearning/assignments/hw2/'

test_directory = '/Users/selindinc/Desktop/CS436-MachineLearning/assignments/hw2/test/'

'''#############################################################################################'''

stop_flag = 0 # please turn flag 0 to remove the stop words from the data


class BagOfWords:
    def __init__(self):
        self.num_docs = 0  # number of how many times a word appeared in a document
        self.total_word_num = 0
        self.frequency = Counter()
        self.type = ''

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
        self.stemmed_words = []
        self.spam_doc_count = 0
        self.ham_doc_count = 0
        self.stop_words = []
        self.test_doc_count = 0
        self.bag_test_array = []

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

                    bag_test = BagOfWords().bag(self.test_doc_count, counter, label)
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

                            else:
                                self.stemmed_words_spam.append(stemmer.stem(word))
                                self.spam_doc_count += 1

        spam_counter = Counter()
        for word in self.stemmed_words_spam:
            spam_counter[word] += 1
        bag_spam = BagOfWords().bag(self.spam_doc_count, spam_counter, 'spam/')
        ham_counter = Counter()
        for word in self.stemmed_words_ham:
            ham_counter[word] += 1
        bag_ham = BagOfWords().bag(self.ham_doc_count, ham_counter, 'ham/')

        return bag_spam, bag_ham


class naiveBayes():
    bags = {}  # bag of words dictionary
    uniqueWords = Counter()

    def __init__(self, bag_spam, bag_ham):

        self.uniqueWords = bag_ham.frequency + bag_spam.frequency
        self.num_docs = bag_ham.num_docs + bag_spam.num_docs  # number of how many times a word appeared in a document
        self.stop_words = []  # stop words array
        self.bags = {}  # bag of words dictionary
        self.bags['spam/'] = bag_spam
        self.bags['ham/'] = bag_ham


    def classification(self, test_bag, k=1):
        s=Stem()
        stop_words=s.setStopWords(stop_words_directory + 'stop_words.txt')
        best_class = ''
        best_posterior = (-2) ** 25

        for label, bag in self.bags.items():
            prior = log(bag.num_docs / self.num_docs)
            denominator = bag.num_docs + k * len(self.uniqueWords)
            likelihood = 0
            for word, count in test_bag.frequency.items():
                if word not in stop_words:
                    numerator = bag.frequency.get(word, 0) + k
                    likelihood += count * log(numerator / denominator)
            posterior = prior + likelihood
            if posterior > best_posterior:
                best_posterior = posterior
                best_class = label
        return best_class
