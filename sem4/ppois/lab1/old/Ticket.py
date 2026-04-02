# from src.consts import ROLLER_COASTER, FERRIS_WHEEL, CAROUSEL

class Ticket:
    
    def __init__(self, type):
        self._type = type
        match type:
            case "rollcoaster":
                self._price = 9 #ROLLER_COASTER
            case "carousel":
                self._price = 5 #CAROUSEL
            case "ferris":
                self._price = 7 #FERRIS_WHEEL
            case _:
                self._price = -1

    @property
    def getPrice(self):
        return self._price
    
    @property
    def getType(self):
        return self._type
    
    
