import csv


class Parser:

    def csvParser(self, filename):
        self.data = []
        with open(filename,'r') as csvfile:
            csvreader = csv.reader(csvfile, delimiter=',')
            count = 0
            for row in csvreader:
                if count == 0:
                    self.attributeNames = row[:-1]
                else:
                    self.data.append([int(i) for i in row])
                count += 1

        self.attributes = range(len(self.attributeNames))
        self.trainingIndex = list(range(len(self.data)))

        self.target_attribute=[]
        for row in self.data:
            self.target_attribute.append(row[-1])

        return self

