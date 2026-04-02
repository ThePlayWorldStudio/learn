from src.Attraction import Attraction as at
from src.Visitor import Visitor as vis
from src.Ticket import Ticket as tik
from src.SafetyRequirements import SafetyRequirements as sr

class Park:
    def __init__(self):
        self._visitors = []
        self._attractions = []
        self.idcountv = 0
        self.idcounta = 0

    @property
    def noVisitors(self):
        return not self._visitors
    
    @property
    def noAttractions(self):
        return not self._attractions

    def createVisitor(self):
        name = input("введите имя: ")
        firstname = input("введите фамилию: ")
        lastname = input("введите отчество: ")
        wall = int(input("введите сумму кошелька: "))
        self._visitors.append(vis(self.idcountv, name, firstname, lastname, wall))
        self.idcountv += 1

    def listVisitors(self):
        for i in self._visitors:
            print(i.getId, i.getNfl, i.getCurrency)

    def delVisitor(self, id):
        self._visitors.pop(id)

    def createAttraction(self):
        name = input("введите имя: ")
        type = input("введите тип: ")
        self._attractions.append(at(self.idcounta, name, type, sr()))
        self.idcounta += 1

    def listAttraction(self):
        for i in self._attractions:
            print(i.getId, i.getName)

    def delAttraction(self, id):
        self._attractions.pop(id)

    def checkAttraction(self, id):
        ib = self._attractions[id].whoIsOn
        self.checkVisitor(ib)

    def addVisitorToAttraction(self, ibv, iba):
        if self.noAttractions or self.noVisitors:
            print("no visitors or attractions")
        else: 
            ticket = tik(self._attractions[iba].getType)
            if self._visitors[ibv].transaction(ticket):
                self._attractions[iba].newVisitor(self._visitors[ibv])
            else:
                print("something went wrong")

    def delVisitorFromAttraction(self, iba):
        self._attractions[iba].next()

    def checkVisitor(self, id):
        print(self._visitors[id].getId, self._visitors[id].getNfl, self._visitors[id].getCurrency)

    def checkAttractionSafety(self, iba):
        if self._attractions[iba].isSafe:
            print("attraction is safe")
        else:
            print("attraction is not safe")

    def recheckAttractionSafety(self, iba, pas):
        self._attractions[iba].recheckAttractionSafety(pas)
        

    @property
    def getVisitor(self, id):
        return(self._visitors[id])
    
    @property
    def getAttraction(self, id):
        return(self._attractions[id])