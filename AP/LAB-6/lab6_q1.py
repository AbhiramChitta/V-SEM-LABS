import sqlite3


# CRUD
def ID(conn):
    cursor = conn.execute("SELECT * FROM STUDENT ORDER BY ID DESC LIMIT 1")
    last_record = cursor.fetchone()
    _id = 1000 if last_record == None else int(last_record[0])
    _id += 12
    print(_id)
    return _id


def create(_id, name, branch, grade, rank):
    conn.execute("INSERT INTO STUDENT VALUES(?,?,?,?,?)", (_id, name, branch, grade, rank))
    conn.commit()
    read(_id)


def read(_id):
    if _id == 0:
        cursor = conn.execute("SELECT * FROM STUDENT")
        print("(REGNO, NAME,  BRANCH, GRADE, MARKS)")
        for row in cursor:
            print(row)
    else:
        cursor = conn.execute("SELECT * FROM STUDENT WHERE ID = ?", (_id,))
        print(cursor.fetchone())


def update(_id, field, new_val):
    conn.execute("UPDATE STUDENT SET " + field + " = ? WHERE ID = ?", (new_val, _id))
    read(_id)
    conn.commit()


def delete(_id):
    if _id == 0:
        conn.execute("DELETE FROM STUDENT;")
    else:
        conn.execute("DELETE FROM STUDENT WHERE ID = ?;", (_id,))
        read(0)
    conn.commit()


def displayBranch(branch):
    cursor = conn.execute("SELECT * FROM STUDENT WHERE BRANCH = ?", (branch,))
    for row in cursor:
        print(row)


def displayMarks():
    cursor = conn.execute("SELECT * FROM STUDENT ORDER BY MARKS DESC")
    print("(REGNO, NAME,  BRANCH, GRADE, MARKS)")
    for row in cursor:
        print(row)


conn = sqlite3.connect('test.db')
print("Opened database successfully")

conn.execute('''CREATE TABLE IF NOT EXISTS STUDENT (
                ID INT PRIMARY KEY  NOT NULL,
                NAME TEXT NOT NULL,
                BRANCH TEXT NOT NULL,
                GRADE TEXT,
                MARKS INT
                );''')

conn.execute('''CREATE TABLE IF NOT EXISTS ATTENDANCE (
                ID INT NOT NULL,
                DATE TEXT NOT NULL,
                CLASS TEXT NOT NULL
                );''')

print("Table created")

print('''Enter
1> To create a new student
2> To read student's data
3> To Update a student's data
4> To Delete student's data.
5> To Display students by branch.
6> To display students by marks.
0> To exit\n
''')
opt = 1
while (opt != 0):
    opt = int(input("Enter Option: "))
    if opt == 1:
        print("Enter student details: ")
        _id = int(ID(conn))
        name = input("Enter name: ")
        branch = input("Enter branch: ")
        grade = input("Enter grade: ")
        rank = int(input("Enter rank: "))
        create(_id, name, branch, grade, rank)

    if opt == 2:
        print("Reading student details: ")
        _id = int(input("Enter id: (Enter 0 to read all students) "))
        read(_id)

    if opt == 3:
        print("Updating student details: ")
        _id = int(input("Enter id: "))
        field = input("Enter field to update: ")
        new_val = input("Enter new value: ")
        update(_id, field, new_val)

    if opt == 4:
        print("Deleting student details: ")
        _id = int(input("Enter id:  (Enter 0 to delete all students) "))
        delete(_id)

    if opt == 5:
        print("Get Students by Branch: ")
        branch = (input("Enter Branch: "))
        displayBranch(branch)

    if opt == 6:
        print("Sorted by Marks: ")
        displayMarks()



conn.commit()
conn.close()