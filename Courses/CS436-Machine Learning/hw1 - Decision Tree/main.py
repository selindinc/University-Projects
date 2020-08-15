import decisionTree
import sys

#directory = "dataset 1/"
#comment out above if you want to use the 2nd dataset

directory="data_sets2/"


def main():


    train_set = directory + str(sys.argv[1])
    validation_set = directory + str(sys.argv[2])
    test_set = directory + str(sys.argv[3])
    to_print = sys.argv[4]
    heuristic = sys.argv[5]

    if (heuristic == "InformationGain"):
        dT = decisionTree.DTree(train_set, "InformationGain")

    elif (heuristic == "VarianceImpurity"):
        dT = decisionTree.DTree(train_set, "VarianceImpurity")

    else:
        print("Please type arguments again!")


    if to_print == "yes":
        print("Decision Tree :")
        dT.displayTree(dT.root, 0, dT.attributeNames)

    print("")
    # print accuracy of train_set
    acc = decisionTree.Accuracy(train_set)
    acc.calcAccuracy(dT.root)
    print ("Accuracy of test_set:",acc.calcAccuracy(dT.root)* 100,"%")

    # print accuracy of validation_set
    accuracy = decisionTree.Accuracy(validation_set)
    accuracy.calcAccuracy(dT.root)
    print("Accuracy of validation_set:", accuracy.calcAccuracy(dT.root) * 100, "%")

    # print accuracy of test_set
    accuracy = decisionTree.Accuracy(test_set)
    accuracy.calcAccuracy(dT.root)
    print("Accuracy of test_set:", accuracy.calcAccuracy(dT.root) * 100, "%")

if __name__ == '__main__':
    main()
