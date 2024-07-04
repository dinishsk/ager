"""
---------------LOCATION------------------
The package for Live location tracking,
marking a value in the map.
NOTE: Update the Live Location before
      adding the marking the value in
      the map.
----------AUTHOR INFORMATION------------
Name: DINISH S K
Mail ID: dinishsk02@gmail.com
----------------------------------------
"""

from folium import Map, Marker

class Location(Map):
    def __init__(self):
        super().__init__(zoom_start=10)
        self.livelocation = Marker(location = [0, 0], popup="Live Location").add_to(self)
        self.updateMap()

    ##Change the Live Location in the Map
    def changeLiveLocation(self,lat,long):
        self.livelocation.location=[lat,long]
        self.updateMap()

    ##Add the Soil Nutrition data in the map
    def addData(self,popup_html):
        Marker(location=self.livelocation.location, popup=popup_html).add_to(self)
        self.updateMap()

    ##For generating the POP
    def generatePopup_html(self,names,values):
        popup_html = ""
        for i in range(len(names)):
            popup_html+=f'<b>{names[i]}:<b> {values[i]}<br>'
        return popup_html
    
    ##Update the Map HTML
    def updateMap(self):
        self.fit_bounds([self.livelocation.location])
        self.save("data/live_location.html")

def main():
    ##For Tesing
    l = Location()
    l.changeLiveLocation(72,84)
    l.addData(l.generatePopup_html(["Nitrogen","Phosporous", "Potassium"],[1,2,3]))
    l.changeLiveLocation(72,84.1)

if __name__=="__main__":
    main()