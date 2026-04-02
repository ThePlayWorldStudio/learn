from src.Queue import Queue
from src.SafetyRequirements import SafetyRequirements as sr

class Attraction:
    def __init__(self, id, name, type, Safety): 
        self._id = id
        self.__name = name
        self._type = type
        self.__que = Queue()
        self.__isFull = False
        self._sr = Safety

    @property
    def isFull(self):
        return self.__isFull
    
    @property
    def getType(self):
        return self._type
    
    @property
    def getId(self):
        return self._id
    
    @property
    def getName(self):
        return self.__name
    
    @property
    def whoIsOn(self):
        if self.isFull==False:
            return -1
        return self.__que.getFirst.getId
    
    def newVisitor(self, visitor):
        self.__que.addNewVisitor(visitor)

    def next(self):
        self.__que.delVisitor()

    @property
    def isSafe(self):
        return self._sr.isPass

    def recheckAttractionSafety(self, ispass):
        self._sr.reCheck(ispass)
    