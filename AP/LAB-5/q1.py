class Employee:
    def __init__(self, id=0, name=" ", sal=" ", dept=" "):
        self.id = id
        self.name = name
        self.sal = sal
        self.dept = dept

    def inp(self):
        self.id = int(input("Enter id: "))
        self.name = input("Enter name: ")
        self.sal = input("Enter salary: ")
        self.dept = input("Enter department name: ")


def main():
    n = int(input("Enter the number of tuples: "))
    e = []  # Create an empty list to store employee objects
    for i in range(n):
        f = Employee()  # Create a new Employee object for each tuple
        f.inp()  # Call the inp() method to input data
        e.append(f)  # Add the Employee object to the list
    k=int(input("Enter the id which is to be searched: "))
    # Display the stored employee data
    for i, emp in enumerate(e):
        if emp.id == k:
            print(f"Employee {i + 1}:")
            print(f"ID: {emp.id}")
            print(f"Name: {emp.name}")
            print(f"Salary: {emp.sal}")
            print(f"Department: {emp.dept}")
            print()


if __name__ == "__main__":
    main()
