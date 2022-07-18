from datetime import date
from datetime import time
from datetime import datetime
#------------------------------ Date Class ------------------------------
class Date(object):
    def __init__(self, day = datetime.now().strftime("%d") , month = datetime.now().strftime("%m") , year = datetime.now().strftime("%Y") ):
        self.day = day
        self.month = month
        self.year = year

    def __str__(self):
        return "{:02d}/{:02d}/{:04d}".format(int(self.day), int(self.month), int(self.year))

#------------------------------ Temperature Class ------------------------------
class Temperature(object):
    def __init__(self, tempe , day = datetime.now().strftime("%d") , month = datetime.now().strftime("%m") , year = datetime.now().strftime("%Y")):
        self.tempe = tempe
        self.date = Date(day,month,year)

    def compareTemp(self, obj):
        return self if self.tempe > obj.tempe else obj

    def __str__(self):
        if(self.tempe > 0):
            return "+{0}°C:{1}".format(float(self.tempe), self.date)
        return "{0}°C:{1}".format(float(self.tempe), self.date)

#------------------------------ Location Class ------------------------------
class Location(object):
    """create location obj"""
    def __init__(self, location):
        self.location = location
        self.listTempe = []

    def printLocation(self):
        """print the location obj"""
        if not self.listTempe:
           print(self.location)
           print('no temperature measurements available')
        else:
            print(self.location)
            for i in self.listTempe:
                print(i, end=' ')
            print('\n')

    def addTemp(self, *args):
        for i in args:
            self.listTempe.append(i)

    def getAverage(self):
        """clac the avg of temp"""
        sum = 0
        if(not self.listTempe):
            return sum
        else:
            for i in self.listTempe:
                sum += i.tempe
            return sum/len(self.listTempe)

    def getMaxTemp(self):
        """return the max temp"""
        max = self.listTempe[0]
        for i in self.listTempe:
            if i.tempe > max.tempe:
                max = i
        return max

    def compareLocation(self, obj):
        """compare between to location where was the max temp."""
        return self if self.getAverage() >= obj.getAverage() else obj


# d1 = Date(1,2,2020)
# d2 = Date()
# print(d1, '-', d2)
# t1 = Temperature(-12,1,2,20)
# t2 = Temperature(0)
# t3 = Temperature(32,20,8,2020)
# print(t1,',',t2,',',t3)
# print(t1.compareTemp(t3))
# loc1 = Location('London')
# loc1.printLocation()
# loc1.addTemp(Temperature(9),Temperature(7,1,12,2020),Temperature(23,21,8,2020),Temperature(16,4,5,2020))
# loc1.printLocation()
# print(loc1.getAverage())
# print(loc1.getMaxTemp())
# loc2 = Location('Berlin')
# loc2.addTemp(Temperature(6),Temperature(28,12,8,2020),Temperature(3,1,12,2020),Temperature(-3,2,1,2020))
# loc2.printLocation()
# loc2.getAverage()
# loc2.compareLocation(loc1).printLocation()