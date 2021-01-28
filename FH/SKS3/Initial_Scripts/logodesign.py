import turtle

'''
def rectangle(side):
    for i in [1,2]:
        turtle.forward(side)
        turtle.left(-90)
        turtle.forward(side/4)
        turtle.left(-90)

for i in range(1,9):
    rectangle(100)
    turtle.left(-45)
'''
wn = turtle.Screen()
wn.bgcolor("black")
t = turtle.Turtle()
t.shape("turtle")
t.color("white")

t.penup()
size=20
for i in range(30):
    t.stamp()
    size = size + 3
    t.forward(size)
    t.right(24)
