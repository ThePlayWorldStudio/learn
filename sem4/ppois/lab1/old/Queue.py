class Queue:
    def __init__(self):
        self.queue = []

    def addNewVisitor(self, Visitor):
        self.queue.append(Visitor)

    def delVisitor(self):
        self.queue.pop(len(self.queue)-1)

    def getFirst(self):
        return self.queue[len(self.queue)-1]
    
    def getId(self):
        return self.queue[len(self.queue)-1].getId