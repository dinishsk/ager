from src.AgerGUI import GUI
from src.Location import Location
from src.Excel import Excel
from src.Chart import BarGraph

import serial
from threading import Thread

## For reading the data from serial
def read_serial(ser,g,l,e):
    while ser!=None:
        try:
            if ser.in_waiting:
                received_data = ser.readline().decode().strip()
                print("Received data:", received_data)
        
                if received_data[0] == 'g':
                    received_data = received_data.split(",")
                    l.changeLiveLocation(float(received_data[1]),float(received_data[2]))
                
                if received_data[0]=='n':
                    received_data = received_data.split(",")
                    data=[]
                    data.extend(l.livelocation.location)
                    data.append(float(received_data[1]))
                    data.append(float(received_data[2]))
                    data.append(float(received_data[3]))
                    e.addData(data)
                    html = l.generatePopup_html(["Nitrogen","Phosphorous","Potassium"],data[2:])
                    l.addData(html)
                
                if received_data=='k':
                    g.enableButtons()

        except Exception:
            print("Exception")

def main():
    opt = int(input("1. Control\n2. Generate Chart\nEnter the Option(1,2): "))

    if(opt == 1):
        ser=None
        try:
            SERIAL_PORT = 'COM6'
            BAUD_RATE = 9600
            ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
        except Exception as e:
            print("Serial Not Available....!")

        g = GUI(ser)
        l = Location()
        e = Excel(["Latitude","Longitude","Nitrogen","Phosphorous","Potassium"])

        read_thread = Thread(target=read_serial, args=(ser,g,l,e))    ##Thread for Reading
        read_thread.daemon = True
        ##read_thread.start()
        g.run()

    elif(opt == 2):
        c = BarGraph()
        c.update()

if __name__=="__main__":
    main()
