from math import atan2
from math import sin, cos

def gcd(x, y):
    while (y):
        x, y = y, x % y
    return x

class ComplexRI(object):
    def __init__(self, real, imag):
        self.real = real
        self.imag = imag
    @property
    def magnitude(self):
        return (self.real**2 + self.imag**2)**0.5

    @property
    def angle(self):
        return atan2(self.imag,self.real)

    def __repr__(self):
        return 'ComplexRI({0},{1})'.format(self.real, self.imag)

class ComplexMA(object):
    def __init__(self, magnitude, angle):
        self.magnitude = magnitude
        self.angle = angle

    @property
    def real(self):
        return self.magnitude * cos(self.angle)

    @property
    def imag(self):
        return self.magnitude * sin(self.angle)

    def __repr__(self):
        return 'ComplexMA({0},{1})'.format(self.magnitude, self.angle)

class Rational(object):
    def __init__(self, numer, denom):
        g = gcd(numer, denom)
        self.numer = numer//g
        self.denom = denom//g

    def __repr__(self):
        return 'Rational({0},{1})'.format(self.numer, self.denom)

class Exponential(object):
    def __init__(self, base, pow):
        self.base = base
        self.pow = pow

    def __repr__(self):
        return 'Exponential({0},{1})'.format(self.base, self.pow)

def type_tag(x):
    return type_tag.tags[type(x)]
type_tag.tags = {ComplexRI : 'com', ComplexMA: 'com', Rational: 'rat', Exponential: 'exp'}

def rational_to_complex(r):
    return ComplexRI(r.numer/r.denom, 0)

def exponential_to_rational(e):
    if(e.pow > 0):
        return Rational(e.base*pow(10,e.pow), 1)
    return Rational(e.base, pow(10,abs(e.pow)))

def exponential_to_complex(e):
    r = exponential_to_rational(e)
    return ComplexRI(r.numer/r.denom, 0)

coercions = {('rat','com'): rational_to_complex, ('exp', 'rat'): exponential_to_rational, ('exp','com'): exponential_to_complex}







def add_complex(comOne, comTwo):
    '''add between to complex numbers'''
    return ComplexRI(comOne.real + comTwo.real, comOne.imag + comTwo.imag)


def mul_complex(comOne, comTwo):
    '''add between to complex numbers'''
    return ComplexMA(comOne.magnitude * comTwo.magnitude, comOne.angle + comTwo.angle)

def add_rational(ratOne,ratTwo):
    '''add between to rantionals numbers'''
    nx ,ny = ratOne.numer, ratTwo.numer
    dx ,dy = ratOne.denom, ratTwo.denom
    rat = Rational(nx*dy + ny*dx, dx*dy)
    return ComplexRI(rat.numer/rat.denom, 0)

def mul_rational(ratOne,ratTwo):
    '''mul between to rantionals numbers'''
    c = ComplexRI((ratOne.numer*ratTwo.numer)/(ratOne.denom*ratTwo.denom), 0)
    return ComplexMA(c.magnitude, c.angle)


def add_rational_to_exponential(r, e):
    '''get rational and exponential numbers and return new Rational obj'''
    if(e.pow > 0):
       return Rational(r.numer + (e.base*r.denom)*(pow(10,e.pow)), r.denom)
    return Rational(r.numer*pow(10, abs(e.pow)) + e.base*r.denom, r.denom*pow(10, abs(e.pow)))


def add_exponential(e1, e2):
    """get two exponential and return new complexRI."""
    if(e1.pow < 0):
        rat =  add_rational_to_exponential(Rational(e1.base, pow(10,abs(e1.pow))), e2)
        return ComplexRI(rat.numer/rat.denom, 0)
    rat =  add_rational_to_exponential(Rational(e1.base, pow(10, e1.pow)), e2)
    return ComplexRI(rat.numer/rat.denom, 0)



def mul_exponential(e1, e2):
    """get two exponential number and return complexMA number. """
    exp = Exponential(e1.base*e2.base, e1.pow+e2.pow)
    c = exponential_to_complex(exp)
    return ComplexMA(c.magnitude, c.angle)


def coerce_apply(operator_name, x,y):
    tx, ty = type_tag(x), type_tag(y)
    if tx != ty:
        if(tx, ty) in coercions:
            tx, x = ty, coercions[(tx, ty)](x)
        elif(ty,tx) in coercions:
            ty, y = tx, coercions[(ty, tx)](y)
        else:
            return 'No coersion possible'
    key = (operator_name, tx)
    return coerce_apply.implementation[key](x,y)

coerce_apply.implementation = {('mul','com'): mul_complex,
                               ('add','com'): add_complex,
                               ('mul', 'rat'): mul_rational,
                               ('add', 'rat'): add_rational,
                               ('mul','exp'): mul_exponential,
                               ('add','exp'): add_exponential}

# print(coerce_apply('add', Exponential(2,-4), Rational(3,4)))
# print(coerce_apply('add', Exponential(2,-4), ComplexRI(3,4)))
# print(coerce_apply('add', Exponential(2,-4), Exponential(3,-5)))
# print(coerce_apply('mul', Exponential(2,-4), Exponential(3,-5)))
# print(coerce_apply('mul', Exponential(2,-4), ComplexMA(10,1)))
# print(coerce_apply('mul', Exponential(2,-4), ComplexRI(3,4)))
# print(coerce_apply('mul', Exponential(2,-4), Rational(1,3)))