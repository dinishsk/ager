"""
-----------------CHART------------------
The package for changeing the data in the
excel to Bar Graph.
----------AUTHOR INFORMATION------------
Name: DINISH S K
Mail ID: dinishsk02@gmail.com
----------------------------------------
"""


from openpyxl import load_workbook
import matplotlib.pyplot as plt
import numpy as np

class BarGraph():
    def __init__(self):
        ##Initialize the Chart
        self.fig, self.ax = plt.subplots()
        self.ax.set_xlabel('Location\n(Latitude, Longitude)')
        self.ax.set_ylabel('Nutrient Level\n(in mg/kg)')
        self.ax.set_title("NPK Values")
        self.ax.set_yticks(range(0,200,40))

    def update(self):
            try:
                wb = load_workbook("data/AGER.xlsx")    ##Load the Excel file
                l=[]
                for i in wb.worksheets[0].values:
                    l.append(list(i))
                xaxis=[]
                values=[[],[],[]]
                for i in l[1:]:
                    xaxis.append(f"{i[0]},{i[1]}")
                    values[0].append(i[2])
                    values[1].append(i[3])
                    values[2].append(i[4])
                
                width = 0.1
                x = np.arange(1,len(values[0])+1)
                self.ax.bar(x - width - 0.01, values[0], width, label="Nitrogen (101-150)")
                self.ax.bar(x , values[1], width, label="Phosphorous (11-20)")
                self.ax.bar(x + width + 0.01,values[2], width, label="Potassium (101-150)")
                
                self.ax.set_xticks(x)
                self.ax.set_xticklabels(xaxis)
                self.ax.legend()
                self.show()
            
            except Exception as e:
                print("File Not Found")
        

    def show(self):
        plt.show()

def main():
    b = BarGraph()
    b.update()

if __name__=="__main__":
    main()