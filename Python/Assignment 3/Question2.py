# ---------------------LEVEL ONE-----------------------------
def make_vector(size, list):
    """
    This build new vector and return the function dispatch.
    :param size:
    :param list:
    :return: dispatch
    """
    if size < 0:
        size = 0
    def dispatch(index):
        """
        this function get a index a return the value.
        :param index:
        :return: size or list dependent of the index
        """
        if index == 0:
            return size
        if index == 1:
            return list
    return dispatch

def getitem_vector(vector,index):
    """
    get vector and index and return the value (size or values)
    :param vector:
    :param index:
    :return:
    """
    return vector(index)
# ---------------------LEVEL TWO-----------------------------
def size(vector):
    """
    return the size of the vector
    :param vector:
    :return:
    """
    return getitem_vector(vector,0)

def value(vector):
    """
    return the values on the vector
    :param vector:
    :return:
    """
    return getitem_vector(vector,1)

# ---------------------LEVEL THREE-----------------------------

def print_vector(vector):
    """
    print the vector.
    :param vector:
    """
    print("size = {0}; values = {1}".format(size(vector), value(vector)))

def value_at(vector, index):
    """
    the value_at get vector and index and return one value from the vector.
    and if the index is not correct he return string of None
    :param vector:
    :param index:
    """
    if index > size(vector) - 1 or index < 0:
        return "None"
    return value(vector)[index]

def reverse(vector):
    """
    get vector and return new vector with reverse elements of the vector he get
    :param vector:
    :return:
    """
    return make_vector(size(vector), value(vector)[::-1])

def norm1(vector):
    """
    get a vector and summarize the organs with absolute value
    :param vector:
    :return: sum
    """
    sum = 0
    for i in range (size(vector)):
        temp = value(vector)[i]
        if temp < 0:
            sum += temp*(-1)
        else:
            sum += temp
    return sum

def norm2(vector):
    """
    summarize the squares and return the sprt of the result
    :param vector:
    :return:
    """
    sum = 0
    for i in range(size(vector)):
        sum += (value(vector)[i])**2
    return (sum)**0.5

def insert(vector, new_ele):
    '''
    gets a new vector and a new value and adds it to the end of the vector
    :param vector:
    :param new_ele:
    :return:
    '''
    temp = list(value(vector))
    temp.append(new_ele)
    return make_vector(size(vector) + 1, tuple(temp))

def delete(vector,index):
    '''
    Gets a vector and index and deletes the value in the given index.
    :param vector:
    :param index:
    :return:
    '''
    temp = list(value(vector))
    for i in range(size(vector)):
        if i == index:
            temp.remove(temp[i])
    return make_vector(size(vector) - 1, tuple(temp))

def sort_vector(vector):
    '''
    Gets a vector and sorts it in ascending order
    :param vector:
    :return:
    '''
    temp = list(value(vector))
    temp.sort()
    return make_vector(size(vector), tuple(temp))


def add_vector(vec_one, vec_two):
    '''
    Gets two vectors and returns a new vector from the add of two vectors
    :param vec_one:
    :param vec_two:
    :return:
    '''
    small = size(vec_two) if size(vec_one) > size(vec_two) else size(vec_one)
    big = size(vec_one) if size(vec_one) > size(vec_two) else size(vec_two)
    new_vec = []
    for i in range(small):
        new_vec.append(value(vec_one)[i] + value(vec_two)[i])
    for i in range(small,big):
        new_vec.append((value(vec_one) if size(vec_one) > size(vec_two) else value(vec_two))[i])
    return make_vector(big, tuple(new_vec))


def mult_scalar(vector, scalar):
    '''
    Get vector and scalar returns a new vector with a scalar vector multiplication
    :param vector:
    :param scalar:
    :return:
    '''
    temp = []
    for i in range(size(vector)):
        temp.append(value(vector)[i]*scalar)
    return make_vector(size(vector), tuple(temp))
