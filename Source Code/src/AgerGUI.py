"""
-------------------GUI------------------
The package for Creating the ControlGUI,
can also be modified.
----------AUTHOR INFORMATION------------
Name: DINISH S K
Mail ID: dinishsk02@gmail.com
----------------------------------------
"""

from tkinter import Tk, Frame, Button
from tkinter import RIDGE, DISABLED, NORMAL, BOTH

class GUI(Tk):
    def __init__(self,serial=None):
        super().__init__()
        self.serial = serial
        self.title("Controller")
        self.frame = Frame(self, bg="#f0f0f0")  ##Frame Creation
        self.frame.pack(pady=10)
        self.setupButtons()  ##SettingUpButtons
        self.gridManagement()  ##SetupLayout

    def setupButtons(self): ##Creation of Buttons
        ##Colour Schemes
        button_bg = "#4caf50"  # Green
        button_fg = "white"    # White
        button_active_bg = "#388e3c"  # Dark green
        button_font = ("Arial", 12)   # Font size 12
        ##Forward Button
        self.f_b = Button(self.frame, text = "Forward", width = 10, height = 10, font = button_font, bg = button_bg, fg = button_fg, activebackground = button_active_bg, bd = 0, relief = RIDGE)
        self.f_b.grid(row = 0, column = 1, padx = 5, pady = 5, sticky = "ew")
        self.f_b.bind("<ButtonPress>", self.forward)
        ##Reverse Button
        self.b_b = Button(self.frame, text = "Backward", width = 10, height = 10, font = button_font, bg = button_bg, fg = button_fg, activebackground = button_active_bg, bd = 0, relief = RIDGE)
        self.b_b.grid(row = 2, column = 1, padx = 5, pady = 5, sticky = "ew")
        self.b_b.bind("<ButtonPress>", self.backward)
        ##Left Button
        self.l_b = Button(self.frame, text = "Left", width = 10, height = 10, font = button_font, bg = button_bg, fg = button_fg, activebackground = button_active_bg, bd = 0, relief = RIDGE)
        self.l_b.grid(row = 1, column = 0, padx = 5, pady = 5, sticky = "ew")
        self.l_b.bind("<ButtonPress>", self.left)
        ##Right Button
        self.r_b = Button(self.frame, text = "Right", width = 10, height = 10, font = button_font, bg = button_bg, fg = button_fg, activebackground = button_active_bg, bd = 0, relief = RIDGE)
        self.r_b.grid(row = 1, column = 2, padx = 5, pady = 5, sticky = "ew")
        self.r_b.bind("<ButtonPress>", self.right)
        ##Get Data Button
        self.g_b = Button(self.frame, text = "Get Data", width = 10, height = 10, font = button_font, bg = "#e91e63", fg = button_fg, activebackground = button_active_bg, bd = 0, relief = RIDGE)
        self.g_b.grid(row = 1, column = 1, padx = 5, pady = 5, sticky = "ew")
        self.g_b.bind("<ButtonPress>", self.getData)
    
    def forward(self,event=None):
        if self.f_b["state"]==NORMAL:   
            print("Forward")
            if(self.serial!=None):
                print("Serial Not connected")
                self.serial.write('w'.encode())

    def backward(self,event=None):
        if self.b_b["state"]==NORMAL:
            print("Backward")
            if(self.serial!=None):
                print("Serial Not connected")
                self.serial.write('s'.encode())

    def left(self, event=None):
        if self.l_b["state"]==NORMAL:
            print("Left")
            if(self.serial!=None):
                print("Serial Not connected")
                self.serial.write('a'.encode())

    def right(self, event=None):
        if self.r_b["state"]==NORMAL:
            print("Right")
            if(self.serial!=None):
                print("Serial Not connected")
                self.serial.write('d'.encode())
    
    def getData(self,event=None):
        if self.g_b["state"]==NORMAL:
            print("Get the Data")
            if(self.serial!=None):
                print("Serial Not connected")
                self.serial.write('l'.encode())
            self.disableButtons()

    def disableButtons(self,event=None):
        for button in [self.f_b, self.b_b, self.l_b, self.r_b, self.g_b]:
            button.config(state=DISABLED)
    
    def enableButtons(self,event=None):
        for button in [self.f_b, self.b_b, self.l_b, self.r_b, self.g_b]:
            button.config(state=NORMAL)
    
    def gridManagement(self):
        self.frame.grid_columnconfigure((0, 1, 2), weight=1)  # columns 0, 1, and 2
        self.frame.grid_rowconfigure((0, 2), weight=1)       # rows 0 and 2
        self.frame.grid_rowconfigure(1, weight=1)           # row 1
        self.frame.pack(fill=BOTH, expand=True)

    def run(self):
        self.mainloop()

def main():
    ##For Testing
    g = GUI()
    g.run()

if __name__=="__main__":
    main()