from src.transformInt import *
from src.binops import *
from src.ieee import *
from src.bcd5421 import *


if __name__ == "__main__":
    print(ieeeToFloat(divideIeee(floatToIeee(13.5), floatToIeee(.1))))
    print(floatToIeee(.1))
