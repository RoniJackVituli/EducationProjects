from datetime import date
from datetime import time
from datetime import datetime

def make_class(attrs, base=None):
    """Return a new class (a dispatch dictionary) with given class attributes"""
    #print(attrs)
    # Getter: class attribute (looks in this class, then base)
    def get(name):
        if name in attrs:
            return attrs[name]
        elif base:
            return base['get'](name)

    # Setter: class attribute (always sets in this class)
    def set(name, value):
        attrs[name] = value

    # Return a new initialized objec'aaa': 5.5t instance (a dispatch dictionary)
    def new(*args):
        # instance attributes (hides encapsulating function's attrs)
        attrs = {}

        # Getter: instance attribute (looks in object, then class (binds self if callable))
        def get(name):
            if name in attrs:
                return attrs[name]
            else:
                value = cls['get'](name)
                if callable(value): #check if value are function , if is funtion return lambda function.
                    return lambda *args: value(obj, *args)
                else:
                    return value #else value are var static or none

        # Setter: instance attribute (always sets in object)
        def set(name, value):
            attrs[name] = value

        # instance dictionary
        obj = { 'get': get, 'set': set }

        # calls constructor if present
        init = get('__init__')
        if init:
            init(*args)

        return obj

    # class dictionary
    cls = { 'get': get, 'set': set, 'new': new }
    return cls

def make_date_class():
    """Return the date class."""
    def __init__(self, day = datetime.now().strftime("%d") , month = datetime.now().strftime("%m") , year = datetime.now().strftime("%Y") ):
        self['set']('day', day) #self.day = day
        self['set']('month', month) #self.month = month
        self['set']('year', year) #self.year = year

    def str(self):
        return "{:02d}/{:02d}/{:04d}".format(int(self['get']('day')), int(self['get']('month')), int(self['get']('year')))

    # locals() returns a dictionary of local variables
    return make_class(locals())

def make_temperature_class():
    def __init__(self, tempe , day = datetime.now().strftime("%d") , month = datetime.now().strftime("%m") ,year = datetime.now().strftime("%Y")):
        self['set']('tempe',tempe) #self.tempe = tempe
        self['set']('date', make_date_class()['new'](day,month,year))  #self.date = Date(day,month,year)

    def compareTemp(self, obj):
        return self if self['get']('tempe') > obj['get']('tempe') else obj

    def str(self):
        if(self['get']('tempe') > 0):
            return "+{0}°C:{1}".format(float(self['get']('tempe')), self['get']('date')['get']('str')())
        return "{0}°C:{1}".format(float(self['get']('tempe')), self['get']('date')['get']('str')())

    return make_class(locals())

def make_location_class():
    def __init__(self, location):
        self['set']('location',location)
        self['set']('listTempe', [])

    def printLocation(self):
        if not self['get']('listTempe'):
            print(self['get']('location'))
            print('no temperature measurements available')
        else:
            print(self['get']('location'))
            for i in self['get']('listTempe'):
                print(i['get']('str')() , end=' ')
            print('\n')

    def addTemp(self,*args):
        for i in args:
            self['get']('listTempe').append(i)

    def getAverage(self):
        sum = 0
        if (not self['get']('listTempe')):
            return sum
        else:
            for i in self['get']('listTempe'):
                sum += i['get']('tempe')
            return sum / len(self['get']('listTempe'))

    def getMaxTemp(self):
        max = self['get']('listTempe')[0]
        for i in self['get']('listTempe'):
            if i['get']('tempe') > max['get']('tempe'):
                max = i
        return max

    def compareLocation(self, obj):
        return self if self['get']('getAverage')() >= obj['get']('getAverage')() else obj

    return make_class(locals())


Date = make_date_class()
Temperature = make_temperature_class()
Location = make_location_class()

#
#
# d1 = Date['new'](1,2,2020)
# d2 = Date['new']()
# print(d1['get'])
# print(d2['get'])
# t1 = Temperature['new'](-12,1,2,2020)
# t2 = Temperature['new'](0)
# t3 = Temperature['new'](32,20,8,2020)
# print(t1['get']('str')(),',',t2['get']('str')(),',',t3['get']('str')())
# print(t1['get']('compareTemp')(t3)['get']('str')())
# loc1=Location['new']('London')
# loc1['get']('printLocation')()
# loc1['get']('addTemp')(Temperature['new'](9),Temperature['new'](7,1,12,2020),Temperature['new'](23 ,21,8,2020),Temperature['new'](16,4,5,2020))
# loc1['get']('printLocation')()
# print(loc1['get']('getAverage')())
# print(loc1['get']('getMaxTemp')()['get']('str')())
# loc2 = Location['new']('Berlin')
# loc2['get']('addTemp')(Temperature['new'](6),Temperature['new'](28,12,8,2020),Temperature['new'](3 ,1,12,2020),Temperature['new'](-3,2,1,2020))
# loc2['get']('printLocation')()
# print(loc2['get']('getAverage')())
# loc2['get']('compareLocation')(loc1)['get']('printLocation')()