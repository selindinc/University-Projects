from Perceptron import PerceptronAlgorithm, Stem

##################################################################################################
'''Please adjust the directories according to your own file'''

source_directory = '/Users/selindinc/Desktop/CS436-MachineLearning/assignments/hw3/train/'
stop_words_directory = '/Users/selindinc/Desktop/CS436-MachineLearning/assignments/hw3/stop_words'

##################################################################################################
num_of_iter = 10000
'''please adjust the number of iterations'''
learning_rate = 0.01
'''please adjust the learning rate'''


def Accuracy(ss):
    w = ss.weight

    model = PerceptronAlgorithm()

    test_bag_array = ss.test_stemmer()
    correct = 0
    false = 0

    for s in test_bag_array:
        label = s.type
        which_label = model.BagClassReturn(s, w)

        if which_label == label:
            correct += 1
        else:
            false += 1

    return print('Accuracy after', num_of_iter, 'iterations with ', learning_rate, 'learning rate : %',
                 (correct / (correct + false) * 100))


def main():
    p = PerceptronAlgorithm()
    ss = Stem()
    ss.stemmer()
    bag_array = ss.UltimateBags()

    p.perceptron(ss.weight, learning_rate, bag_array, num_of_iter)
    Accuracy(ss)


if __name__ == '__main__':
    main()
