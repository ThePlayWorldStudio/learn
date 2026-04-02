from src.Park import Park

isWork = True
type = ["rollcoaster", "carousel", "ferris"]

def printMenu():
    print("<==========|Menu|==========>")
    print("1. add new visitor")
    print("2. list visitors")
    print("3. del visitor")
    print("4. add attraction")
    print("5. list attractions")
    print("6. del attrraction")
    print("7. add visitor to queue")
    print("8. who is on attraction")
    print("9. end attraction")
    print("10. recheck attraction security")
    print("11. recheck attraction security")
    print("12. help")
    print("13. exit")

if __name__ == "__main__":
    printMenu()
    park = Park()
    while isWork:
        act = int(input())
        match act:
            case 1:
                park.createVisitor()

            case 2:
                park.listVisitors()

            case 3:
                if park.noVisitors:
                    print("no visitors")
                else: 
                    ib = int(input("id: "))
                    park.delVisitor(ib)

            case 4:
                park.createAttraction()

            case 5:
                park.listAttraction()

            case 6:
                if park.noAttractions:
                    print("no attractions")
                else: 
                    ib = int(input("id: "))
                    park.delAttraction(ib)

            case 7:
                ibv = int(input("visitor id: "))
                iba = int(input("attraction id: "))
                park.addVisitorToAttraction(ibv, iba)

            case 8:
                if park.noAttractions:
                    print("no attractions")
                else: 
                    ib = int(input("attraction id: "))
                    park.checkAttraction(ib)

            case 9:
                iba = int(input("attraction id: "))
                park.delVisitorFromAttraction(iba)

            case 10:
                iba = int(input("attraction id: "))
                park.checkAttractionSafety(iba)

            case 11:
                iba = int(input("attraction id: "))
                print("input status:")
                print("1. True")
                print("2. False")
                chicking = True
                while chicking:
                    pas = int(input())
                    match pas:
                        case 1:
                            pas = True
                            chicking = False
                        case 2:
                            pas = False
                            chicking = False
                        case _:
                            print("invalid message!")
                park.recheckAttractionSafety(iba, pas)

            case 12:
                printMenu()

            case 13:
                isWork = False

            case _:
                print("No command?")
                printMenu()
