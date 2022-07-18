def isSequence(obj):
    return type(obj) in [str, list, tuple, range,]

def make_sequence(seq=None):
    try:
        if(isSequence(seq)):
            def filter1(func = None):
                '''
                Accepts a function as a single argument and returns filtered values using a tuple
                :param func:
                :return:
                '''
                try:
                    if func != None:
                        new_filter = filter(func, seq)
                        return tuple(new_filter)
                    else:
                        raise TypeError(": No filter function")
                except TypeError as e:
                    print(str(TypeError) + str(e))
                    return tuple(seq)

            def filter_iterator(func = None):
                '''
                A circular iterator function that returns filtered values by promoting next or by promoting in the reverse direction
                :param func:
                :return:
                '''
                try:
                    if(func != None):
                        new_seq = tuple(filter(func, seq))
                        index = 0
                    else:
                        raise TypeError(": No filter function")
                except TypeError as e:
                    print(str(TypeError)+str(e))
                    return seq

                def next():
                    nonlocal index
                    try:
                        if index >= 0 and index < len(new_seq):
                            ele = new_seq[index]
                            index += 1
                        else:
                            raise IndexError(": tuple index out of range")
                        return ele
                    except IndexError as e:
                        print(str(IndexError) + str(e))

                def reverse():
                    nonlocal index
                    try:
                        if index >= 0 and index < len(new_seq):
                            ele = new_seq[index]
                            index -= 1
                            return ele
                        else:
                           raise IndexError(": Index error")
                    except IndexError as e:
                        print(str(IndexError) + str(e))
                return {'next': next, 'reverse': reverse}

            def reverse():
                '''
                Returns the reverse list
                :return:
                '''
                return tuple(seq[::-1])

            def extend(new_seq):
                '''
                Threads a new list and an existing list
                :param new_seq:
                :return:
                '''
                nonlocal seq
                seq += new_seq

            return {'filter': filter1, 'filter_iterator': filter_iterator, 'reverse': reverse, 'extend': extend}
        raise TypeError(": no sequence argument")
    except TypeError as e:
       print(str(TypeError) + str(e))


# s1 = make_sequence()
# s1 = make_sequence(200)
# s1 = make_sequence((1, 2, 3, 4, 5))
# print(s1['filter']())
# p1=s1['filter_iterator']()
# p1 = s1['filter_iterator'](lambda x: x<4)
# for _ in range(6):
#     print(p1['next']())
# p1=s1['filter_iterator'](lambda x: x>1)

# print(p1['next']())
# print(p1['next']())
# print(p1['next']())
# print()
# for _ in range(6):
#     print(p1['reverse']())