class SafetyRequirements:
    def __init__(self):
        self._pass = False

    @property
    def isPass(self):
        return self._pass
    
    def reCheck(self, status):
        self._pass = status