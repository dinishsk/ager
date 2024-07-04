"""
-----------------EXCEL------------------
The package for entering the data in the
excel and store for further use.
----------AUTHOR INFORMATION------------
Name: DINISH S K
Mail ID: dinishsk02@gmail.com
----------------------------------------
"""

from openpyxl import Workbook

class Excel(Workbook):
    def __init__(self,columns):
        super().__init__()      ##Initialize the WorkBook
        self.ws = self.active   ##Take the Active WorkSheet
        self.ws.append(columns)  ##Add the Column Names
        self.updateSheet()    ##Update the xlsx
    
    ##Add data to the Sheet
    def addData(self,data=[]):
        self.ws.append(data)
        self.updateSheet()    ##Update the xlsx

    ##For Updating the Xlsx
    def updateSheet(self):
        self.save("data/AGER.xlsx")

def main():
    ##For Testing
    e= Excel([1,2,3])
    e.addData(["a","b","c"])

if __name__=="__main__":
    main()