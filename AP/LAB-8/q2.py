from tkinter import *

calc = Tk()
calc.geometry("300x300")
calc.title("Calculator")
calcLabel = Label(calc, text="CALC", bg='White',font=("Times New Roman", 30, 'normal'))
calcLabel.pack(side=TOP)
calc.config(background='black')

textin = StringVar()
operator = ""


def select(number):  # lambda:clickbut(1)
    global operator
    operator = operator+str(number)
    textin.set(operator)


def equals():
    global operator
    add = str(eval(operator))
    textin.set(add)
    operator = ''


def clear():
    textin.set('')


metext = Entry(calc, font=("Courier New", 20, 'bold'), textvar=textin, width=20, bd=5, bg='white')
metext.pack()

button1 = Button(calc, bg='white', font =("Times New Roman", 25, 'bold'), command=lambda: select(1), text="1")
button1.place(x=40, y=100)

button2 = Button(calc, bg='white', font =("Times New Roman", 25, 'bold'), command=lambda: select(2), text="2")
button2.place(x=40, y=150)

button3 = Button(calc, bg='white', font =("Times New Roman", 25, 'bold'), command=lambda: select(3), text="3")
button3.place(x=40, y=200)

button4 = Button(calc, bg='white', font =("Times New Roman", 25, 'bold'), command=lambda: select(4), text="4")
button4.place(x=80, y=100)

button5 = Button(calc, bg='white', font =("Times New Roman", 25, 'bold'), command=lambda: select(5), text="5")
button5.place(x=80, y=150)

button6 = Button(calc, bg='white', font =("Times New Roman", 25, 'bold'), command=lambda: select(6), text="6")
button6.place(x=80, y=200)

button7 = Button(calc, bg='white', font =("Times New Roman", 25, 'bold'), command=lambda: select(7), text="7")
button7.place(x=120, y=100)

button8 = Button(calc, bg='white', font =("Times New Roman", 25, 'bold'), command=lambda: select(8), text="8")
button8.place(x=120, y=150)

button9 = Button(calc, bg='white', font =("Times New Roman", 25, 'bold'), command=lambda: select(9), text="9")
button9.place(x=120, y=200)

button0 = Button(calc, bg='white', font =("Times New Roman", 25, 'bold'), command=lambda: select(0), text="0")
button0.place(x=40, y=250)

buttondot = Button(calc, bg='white', font =("Courier New", 20, 'bold'), command=lambda: select("."), text=".")
buttondot.place(x=80, y=250)

buttonadd = Button(calc, bg='white', text="+", font =("Courier New", 20, 'bold'), command=lambda: select("+"))
buttonadd.place(x=160, y=100)

buttonsub = Button(calc, bg='white', text="-", font =("Courier New", 20, 'bold'), command=lambda: select("-"))
buttonsub.place(x=160, y=150)

buttonmul = Button(calc, bg='white', text="*", font =("Courier New", 20, 'bold'), command=lambda: select("*"))
buttonmul.place(x=160, y=200)

buttondiv = Button(calc, bg='white', text="/", font =("Courier New", 20, 'bold'), command=lambda: select("/"))
buttondiv.place(x=160, y=250)

buttonmod = Button(calc, bg='white', font =("Courier New", 20, 'bold'), command=lambda: select("%"), text="%")
buttonmod.place(x=120, y=250)

buttonclear = Button(calc, bg='white', font =("Courier New", 20, 'bold'), text="CE", command=clear)
buttonclear.place(x=200, y=250)

buttonequal = Button(calc, bg='white', font =("Courier New", 20, 'bold'), command=equals, text="=")
buttonequal.place(x=200, y=196)
calc.mainloop()
