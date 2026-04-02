class Binary:
    def __init__(self, num):
        self.bins = self._transform(num)
    
    def _transform(self, num):
        binp = [0]*32
        binp = self._transformBinP(num)
        if num < 0:
            return {"binp":binp, "binrev":binp, "bindop":binp}
        else:
            binrev = self._transformBinRev(binp)
            bindop = self._transformBinDop(binrev)
            return {"binp":binp, "binrev":binrev, "bindop":bindop}


    def __iadd__(self, other):
        sum = self.bins + other
        return 

    def __add__(self, other):
        sum = [0]*32
        i = 31
        car = 0
        while i >= 0:
            if car == 0:
                if self.bins["bindop"][i] != other.bins["bindop"][i]:
                    sum[i] = 1
                    car = 0
                else:
                    match self.bins["bindop"][i]:
                        case 0:
                            sum[i] = 0
                            car = 0
                        case 1:
                            sum[i] = 0
                            car = 1
            elif car == 1:
                if self.bins["bindop"][i] != other.bins["bindop"][i]:
                    sum[i] = 0
                    car = 1
                else:
                    match self.bins["bindop"][i]:
                        case 0:
                            sum[i] = 1
                            car = 1
                        case 1:
                            sum[i] = 1
                            car = 0
            i -= 1
        return sum 
