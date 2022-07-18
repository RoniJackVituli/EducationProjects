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

def add_complex(comOne, comTwo):
    return ComplexRI(comOne.real + comTwo.real, comOne.imag + comTwo.imag)
def mul_complex(comOne, comTwo):
    return ComplexMA(comOne.magnitude * comTwo.magnitude, comOne.angle + comTwo.angle)

def add_rational(ratOne,ratTwo):
    nx ,ny = ratOne.numer, ratTwo.numer
    dx ,dy = ratOne.denom, ratTwo.denom
    return Rational(nx*dy + ny*dx, dx*dy)
def mul_rational(ratOne,ratTwo):
    return Rational(ratOne.numer * ratTwo.numer, ratOne.denom * ratTwo.denom)



def add_complex_to_rational(z, r):
    return ComplexRI(z.real + r.numer/r.denom, z.imag)
def mul_complex_to_rational(z, r):
    return ComplexMA(z.magnitude * (r.numer/r.denom), z.angle)


def add_complex_to_exponential(z, e):
    return ComplexRI(z.real + (e.base*pow(10,e.pow)), z.imag)


def add_exponential(e1, e2):
    if(e1.pow < 0):
        return add_rational_to_exponential(Rational(e1.base, pow(10,abs(e1.pow))), e2)
    return add_rational_to_exponential(Rational(e1.base, pow(10, e1.pow)), e2)

def mul_exponential(e1, e2):
   return Exponential(e1.base*e2.base, e1.pow+e2.pow)

def add_rational_to_exponential(r, e):
   if(e.pow > 0):
       return Rational(r.numer + (e.base*r.denom)*(pow(10,e.pow)), r.denom)
   return Rational(r.numer*pow(10, abs(e.pow)) + e.base*r.denom, r.denom*pow(10, abs(e.pow)))

def mul_complex_to_exponential(z, e):
    return ComplexMA(z.magnitude*(e.base*pow(10,e.pow)), z.angle)

def mul_rational_to_exponential(r, e):
    if (e.pow > 0):
        return Rational(r.numer*(e.base*pow(10, e.pow), r.denom))
    return Rational(r.numer*e.base, r.denom*pow(10, abs(e.pow)))

def apply(operator_name , x , y):
    tags = (type_tag(x), type_tag(y))
    key = (operator_name, tags)
    return apply.implementation[key](x,y)
apply.implementation = {('add', ('com', 'com')): add_complex,
                        ('add', ('com', 'rat')): add_complex_to_rational,
                        ('add', ('rat', 'com')): lambda x, y: add_complex_to_rational(y,x),
                        ('add', ('rat', 'rat')): add_rational,
                        ('add', ('com', 'exp')): add_complex_to_exponential,
                        ('add', ('exp', 'com')): lambda x, y: add_complex_to_exponential(y,x),
                        ('add', ('rat', 'exp')): add_rational_to_exponential,
                        ('add', ('exp', 'rat')): lambda x, y: add_rational_to_exponential(y,x),
                        ('add', ('exp', 'exp')): add_exponential,
                        ('mul', ('com', 'com')): mul_complex,
                        ('mul', ('com', 'rat')): mul_complex_to_rational,
                        ('mul', ('rat', 'com')): lambda x, y: mul_complex_to_rational(y,x),
                        ('mul', ('rat', 'rat')): mul_rational,
                        ('mul', ('com', 'exp')): mul_complex_to_exponential,
                        ('mul', ('exp', 'com')): lambda x, y: mul_complex_to_exponential(y,x),
                        ('mul', ('rat', 'exp')): mul_rational_to_exponential,
                        ('mul', ('exp', 'rat')): lambda x, y:mul_rational_to_exponential(y,x),
                        ('mul', ('exp', 'exp')): mul_exponential}


# print(apply('add', Exponential(2,-4), Rational(3,4)))
# print(apply('add', Exponential(2,-4), ComplexRI(3,4)))
# print(apply('add', Exponential(2,-4), Exponential(3,-5)))
# print(apply('mul', Exponential(2,-4), Exponential(3,-5)))
# print(apply('mul', Exponential(2,-4), ComplexMA(10,1)))
# print(apply('mul', Exponential(2,-4), Rational(1,3)))

