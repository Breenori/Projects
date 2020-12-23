import tkinter as tk
from tkinter import Menu, Toplevel, Button, filedialog, Frame, LabelFrame, Canvas, PhotoImage

import turtle

# Add GUI functions

def openFile():
    pathFilename = filedialog.askopenfilename(initialdir = "/", \
                                              title = "Select file", \
                                              filetypes = (("jpeg files", "*.jpg"),("all files", "*.*")))

    print(pathFilename)

def doNothingButton():
    filewin = Toplevel(mainWindow)
    button = Button(filewin, text="Do nothing Button")
    button.pack()

def groupBoxes(text, side, mW):
    groupBoxFrame = LabelFrame(mW, text=text)
    groupBoxFrame.pack(side=side, expand="yes", fill="both")
    return groupBoxFrame


# Main Window / Master
mainWindow = tk.Tk()
mainWindow.title("My First GUI")

# Create Menu & Filemenu
menubar = Menu(mainWindow)

# Tearoff = nicht standardmäßig aufgeklappt.
filemenu = Menu(menubar, tearoff=0)

filemenu.add_command(label="Open file", command=openFile)
filemenu.add_command(label="Open new window", command=doNothingButton)
filemenu.add_separator()
filemenu.add_command(label="Exit", command=mainWindow.destroy)
menubar.add_cascade(label="File", menu=filemenu)

# Layout Management / Frames & LabelFrames
mainFrameTop = Frame(mainWindow)
mainFrameTop.pack(side="top", fill="both", expand="yes")

groupBoxFrame = groupBoxes("Button Options", "left", mainFrameTop)
btnFill = Button(groupBoxFrame, text="ButtonFill")
btnFill.pack(fill="x")

btnExpand = Button(groupBoxFrame, text="ButtonExpand")
btnExpand.pack(expand="yes")

btnSide = Button(groupBoxFrame, text="buttonSide")
btnSide.pack(side="right")

# CHoice option frame & grid methods for layout management
choiceOptionFrame = groupBoxes("Choice Options", "right", mainFrameTop)

btnColumn = Button(choiceOptionFrame, text="I am in column 3")
btnColumn.grid(column=3)

btnColumnSpan = Button(choiceOptionFrame, text="I have a columnspan of 3")
btnColumnSpan.grid(columnspan=3)

mainFrameBottom = Frame(mainWindow)
mainFrameBottom.pack(side="bottom", fill="both", expand="yes")

# Picture Viewer
pictureFrame = groupBoxes("Picture Viewer", "left", mainFrameBottom)

canvas = Canvas(pictureFrame, width=300, height=300)
canvas.pack()
img = PhotoImage(file=r"F:\Bilder\Anime\saber_mini.png")
canvas.create_image(20, 20, anchor='nw', image=img)

# Canvas Drawer
canvasFrame = groupBoxes("Canvas Drawer", "right", mainFrameBottom)

canvas = Canvas(canvasFrame, width=200, height=200)
canvas.pack()

def forward():
    t.forward(50)

def back():
    t.back(50)

def left():
    t.left(90)
    
def right():
    t.right(90)

t = turtle.RawTurtle(canvas)
t.shape("turtle")
t.pencolor("blue")

t.pendown()

Button(canvasFrame, text="Forward", command=forward).pack(side=tk.LEFT)
Button(canvasFrame, text="Back", command=back).pack(side=tk.LEFT)
Button(canvasFrame, text="Left", command=left).pack(side=tk.LEFT)
Button(canvasFrame, text="Right", command=right).pack(side=tk.LEFT)

# Configure Main Window
mainWindow.config(menu=menubar)

mainWindow.mainloop()
