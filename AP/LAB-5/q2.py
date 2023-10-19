class Vehicle:
    def __init__(self, own=" ", id=0, man=" "):
        self.own = own
        self.id = id
        self.man = man

    def inp(self):
        self.own = input("Enter name of vehicle owner: ")
        self.id = int(input("Enter vehicle registration id: "))
        self.man = input("Enter name of the manufacturer: ")


class Passenger(Vehicle):
    def __init__(self, count=0):
        super().__init__()
        self.count = count

    def passcount(self):
        self.count = int(input("Enter number of passengers in the vehicle: "))

    def disp(car):
        for i in car:
            print(f"Owner name : {i.own}")
            print(f"Vehicle id : {i.id}")
            print(f"Name of manufacturer : {i.man}")
            print(f"No. of passengers in the vehicle : {i.count}")
            print()

def main():
    e = []
    k = int(input("no. of cars = "))
    for i in range(k):
        p = Passenger()
        p.inp()
        p.passcount()
        e.append(p)

    Passenger.disp(e)


main()
