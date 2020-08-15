from NaiveBayes import BagOfWords, naiveBayes, Stem

'''Please adjust the directories according to your own file'''

source_directory = '/Users/selindinc/Desktop/CS436-MachineLearning/assignments/hw2/train/'
stop_words_directory = '/Users/selindinc/Desktop/CS436-MachineLearning/assignments/hw2/stop_words'


def main():


    s= Stem()
    bag_spam, bag_ham = s.stemmer()

    model = naiveBayes(bag_spam,bag_ham)

    test_bag_array=s.test_stemmer()
    correct=0
    false=0

    for s in test_bag_array:
        label=s.type
        which_label=model.classification(s,1)

        if which_label==label:
            correct+=1
        else:
            false+=1

    print('Accuracy: %',(correct/(correct+false)*100))




if __name__ == '__main__':
    main()
