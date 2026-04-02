from src.Ticket import Ticket

class Visitor:
    def __init__(self, id, name, firstname, lastname, wallet):
        self.__id = id
        self.__name = name
        self.__firstname = firstname
        self.__lastname = lastname
        self.__wallet = wallet
        self._tickets = []

    @property
    def getNfl(self):
        return [self.__name, self.__firstname, self.__lastname]
    
    @property
    def getCurrency(self):
        return self.__wallet
    
    @property
    def getId(self):
        return self.__id
    
    def setName(name, self):
        self.__name = name

    def setFirstname(name, self):
        self.__firstname = name

    def setLastname(name, self):
        self.__lastname = name

    def getTicket(self, Ticket):
        if(Ticket.getPrice <= 0):
            return 0
        else:
            self._tickets.append(Ticket)

    def delTicket(self):
        self._tickets.pop(len(self._tickets)-1)

    def transaction(self, ticket):
        if ticket.getPrice > self.__wallet:
            print("no money")
            return 0
        elif ticket.getPrice < 0:
            print("ticket is not valid")
            return 0
        else:
            self.__wallet -= ticket.getPrice
            print("transaction successful")
            return 1
        