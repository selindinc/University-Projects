import Node
import CSVParser
import math


class DTree:

    def __init__(self, filename, heuristic):

        csvParser = CSVParser.Parser.csvParser(self, filename)

        self.heuristic = heuristic

        self.attributeNames = csvParser.attributeNames
        self.data = csvParser.data
        self.attributes = csvParser.attributes
        self.trainingIndex = csvParser.trainingIndex
        self.target_attribute = csvParser.target_attribute

        self.root = self.ID3(self.trainingIndex, self.target_attribute, self.attributes, self.heuristic)

    def Entropy(self, trainingIndex, target_attribute):

        k = len(trainingIndex)
        onesCount = 0
        zerosCount = 0

        for i in range(len(trainingIndex)):
            if target_attribute[i] == 1:
                onesCount += 1
            elif target_attribute[i] == 0:
                zerosCount += 1

        if (onesCount == 0 or zerosCount == 0 or k == 0):
            return 0

        probOnes = 1.0 * onesCount / k
        probZeros = 1.0 * zerosCount / k

        entropy = -(probOnes * math.log(probOnes, 2) + probZeros * math.log(probZeros, 2))

        return entropy

    def InformationGain(self, trainingIndex, target_attribute, Entropy, attribute):

        rows = len(trainingIndex)

        subTree = self.split(trainingIndex, target_attribute, attribute)
        EntropyVal0 = self.Entropy(subTree[0][0], subTree[0][1])
        EntropyVal1 = self.Entropy(subTree[1][0], subTree[1][1])

        probVal0 = 1.0 * len(subTree[0][0]) / rows
        probVal1 = 1 - probVal0

        infoGain = Entropy - probVal0 * EntropyVal0 - probVal1 * EntropyVal1
        return infoGain

    def VarianceImpurity(self, trainingIndex, target_attribute):

        k = len(trainingIndex)
        k0 = 0
        k1 = 0
        for i in range(len(trainingIndex)):
            if target_attribute[i] == 1:
                k1 += 1
            elif target_attribute[i] == 0:
                k0 += 1
        if (k0 == 0 or k1 == 0 or k == 0):
            return 0

        ones = 1.0 * k1 / k
        zeros = 1.0 * k0 / k
        vI = ones * zeros  # variance impurity

        return vI

    def VarianceImpurityGain(self, trainingIndex, target_attribute, varianceImpurity, attributes):

        rows = len(trainingIndex)

        subTree = self.split(trainingIndex, target_attribute, attributes)
        varianceImpurityVal0 = self.VarianceImpurity(subTree[0][0], subTree[0][1])
        varianceImpurityVal1 = self.VarianceImpurity(subTree[1][0], subTree[1][1])

        probVal0 = 1.0 * len(subTree[0][0]) / rows
        probVal1 = 1 - probVal0

        Gain = varianceImpurity - probVal0 * varianceImpurityVal0 - probVal1 * varianceImpurityVal1

        return Gain

    def chooseBestAttribute(self, trainingIndex, target_attribute, Attributes, varianceImpurity, entropy, heuristic):
        maxGain = -1
        bestAttribute = -1

        for attribute in Attributes:
            if (heuristic == "InformationGain"):
                gain = self.InformationGain(trainingIndex, target_attribute, entropy, attribute)
                if gain > maxGain:
                    maxGain = gain
                    bestAttribute = attribute
            else:
                gain = self.VarianceImpurityGain(trainingIndex, target_attribute, varianceImpurity, attribute)
                if gain > maxGain:
                    maxGain = gain
                    bestAttribute = attribute

        return bestAttribute

    def split(self, trainingIndex, target_attribute, attribute):

        training_V0 = []
        training_V1 = []
        target_V0 = []
        target_V1 = []
        for i in range(len(trainingIndex)):
            if self.data[trainingIndex[i]][attribute] == 0:
                training_V0.append(trainingIndex[i])
                target_V0.append(target_attribute[i])
            else:
                training_V1.append(trainingIndex[i])
                target_V1.append(target_attribute[i])

        return [(training_V0, target_V0), (training_V1, target_V1)]

    def ID3(self, trainingValues, target_attribute, Attributes, heuristic):

        if len(trainingValues) == 0:
            return None

        Entropy = self.Entropy(trainingValues, target_attribute)
        varianceImpurity = self.VarianceImpurity(trainingValues, target_attribute)

        root = Node.Node(-1)
        countOne = 0
        countZero = 0

        for i in range(len(target_attribute)):
            if target_attribute[i] == 1:
                countOne += 1
            else:
                countZero += 0

        if (countOne > countZero):
            root.label = 1
        else:
            root.label = 0

        if Entropy == 0 or len(Attributes) == 0:
            return root

        else:

            if (heuristic == "InformationGain"):
                bestAttribute = self.chooseBestAttribute(trainingValues, target_attribute, Attributes, Entropy,
                                                         varianceImpurity, heuristic)

                root = self.grow_tree(bestAttribute, root, Attributes, target_attribute, trainingValues, heuristic)
                return root

            if (heuristic == "VarianceImpurity"):
                bestAttribute = self.chooseBestAttribute(trainingValues, target_attribute, Attributes, varianceImpurity,
                                                         Entropy, heuristic)

                root = self.grow_tree(bestAttribute, root, Attributes, target_attribute, trainingValues, heuristic)
                return root

    def grow_tree(self, bestAttribute, root, Attributes, target_attribute, trainingIndex, heuristic):

        if bestAttribute == -1:
            return root
        root.val = bestAttribute
        nextAttributesForSplitTree = []
        for attribute in Attributes:
            if attribute != bestAttribute:
                nextAttributesForSplitTree.append(attribute)
        Attributes = nextAttributesForSplitTree
        subTree = self.split(trainingIndex, target_attribute, bestAttribute)
        root.left = self.ID3(subTree[0][0], subTree[0][1], Attributes, heuristic)
        root.right = self.ID3(subTree[1][0], subTree[1][1], Attributes, heuristic)

        return root

    def displayTree(self, root, level, attributeNames):

        s = ""

        if (root == None):
            print("")
            return

        if root.left == None and root.right == None:
            s += str(root.label)
            print(s, end='')
            return

        print("")
        for i in range(0, level):
            s += "| "

        if root.left != None:
            if root.left.left == None and root.left.right == None:
                s += attributeNames[root.val] + "= 0 :"
            else:
                s += str(attributeNames[root.val]) + "= 0 :"

        print(s, end='')

        self.displayTree(root.left, level + 1, attributeNames)

        s = ""

        print("")
        for i in range(0, level):
            s += "| "

        if root.right != None:
            if root.right.left == None and root.right.right == None:
                s += attributeNames[root.val] + "= 1 :"
            else:
                s += attributeNames[root.val] + "= 1 :"

        print(s, end='')
        self.displayTree(root.right, level + 1, attributeNames)


class Accuracy:

    def __init__(self, filename):

        csvParser = CSVParser.Parser.csvParser(self, filename)
        self.target_attribute = csvParser.target_attribute
        self.data = csvParser.data

    def calcAccuracy(self, root):

        countAccurates = 0
        i = 0

        if (root == None):
            return 0
        while i < len(self.data):
            if self.traverse_tree(root, self.data[i]) == self.target_attribute[i]:
                countAccurates += 1
            i += 1
        self.accuracy = 1.0 * countAccurates / len(self.data)
        return self.accuracy

    def traverse_tree(self, root, data):

        if root != None:

            if root.val == -1:
                return root.label
            if data[root.val] == 0:
                return self.traverse_tree(root.left, data)
            else:
                return self.traverse_tree(root.right, data)
