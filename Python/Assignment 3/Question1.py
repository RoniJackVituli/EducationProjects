#--------------------------------------- Data abstraction, Immutable data --------------------------------------------------------------------

#------Level 0---------
def make_rectangle(x,y,leghth,width):
    '''
    create immutable type
    :param x:
    :param y:
    :param leghth:
    :param width:
    :return:
    '''
    def dispatch(index):
        if index == 0:
            return x
        if index == 1:
            return y
        if index == 2:
            return leghth
        if index == 3:
            return width
    return dispatch

#----------------LEVEL ONE---------------------
def getitem_rec(rectangle,i):
    '''
    get rec and index and return value
    :param rectangle:
    :param i:
    :return:
    '''
    return rectangle(i)

def x(rectangle):
    '''
    return the x point with getitem_rec
    :param rectangle:
    :return:
    '''
    return getitem_rec(rectangle,0)
def y(rectangle):
    '''
    return y point whit getitem_rec
    :param rectangle:
    :return:
    '''
    return getitem_rec(rectangle,1)
def length(rectangle):
    '''
    return length whit getitem_rec
    :param rectangle:
    :return:
    '''
    return getitem_rec(rectangle,2)
def width(rectangle):
    '''
    return width whit getitem_rec
    :param rectangle:
    :return:
     '''
    return getitem_rec(rectangle,3)

#-------------LEVEL THREE----------------------


def diagonal(rectangle):
    '''
    calculate the diagonal on the rectangle is get
    :param rectangle:
    :return:
    '''
    return ((length(rectangle))**2 + (width(rectangle))**2)**0.5

def print_rectangle(rectangle):
    '''
    print all the data of rectangle
    :param rectangle:
    :return:
    '''
    print("Rectangle: point = ({0},{1}); size = {2}x{3}".format(x(rectangle), y(rectangle), length(rectangle), width(rectangle)))

def center(rectangle):
    '''
    return the center point of the rectangle
    :param rectangle:
    :return:
    '''
    return (x(rectangle) + length(rectangle)/2, y(rectangle) + width(rectangle)/2)

def distance(rec_one,rec_two):
    '''
    return the distance between two rectangles
    :param rec_one:
    :param rec_two:
    :return:
    '''
    return ((center(rec_one)[0] - center(rec_two)[0])**2 + (center(rec_one)[1] - center(rec_two)[1])**2)**0.5

def move(rectangle, deltaX, deltaY):
    '''
    moves the rectangle in the hinge system
    :param rectangle:
    :param deltaX:
    :param deltaY:
    :return:
    '''
    return make_rectangle(x(rectangle) + deltaX, y(rectangle) + deltaY, length(rectangle), width(rectangle))

def resize(rectangle, resize):
    '''
    change the width and length depending on the factor
    :param rectangle:
    :param resize:
    :return:
    '''
    return make_rectangle(x(rectangle), y(rectangle), length(rectangle)*resize, width(rectangle)*resize)

def average_rectangle(rec_one, rec_two):
    '''
    receives two rectangles and returns the average rectangle between the two rectangles
    :param rec_one:
    :param rec_two:
    :return:
    '''
    return make_rectangle((x(rec_one) + x(rec_two))/2, (y(rec_one) + y(rec_two))/2, (length(rec_one) + length(rec_two))/2, (width(rec_one) + width(rec_two))/2)


