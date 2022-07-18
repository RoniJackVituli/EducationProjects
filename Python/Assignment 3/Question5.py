def make_sequence(seq):

    def filter1(func = None):
        '''
        Accepts a function as a single argument and returns filtered values using a tuple
        :param func:
        :return:
        '''
        if func != None:
            new_filter = filter(func, seq)
            return tuple(new_filter)
        return tuple(seq)

    def filter_iterator(func = None):
        '''
        A circular iterator function that returns filtered values by promoting next or by promoting in the reverse direction
        :param func:
        :return:
        '''
        if(func != None):
            new_seq = tuple(filter(func, seq))
            index = 0
        else:
            return tuple(seq)
        def next():
            nonlocal index
            if index >= 0 and index < len(new_seq):
                ele = new_seq[index]
                index += 1
            else:
                index = 0
                ele = new_seq[index]
                index += 1
            return ele

        def reverse():
            nonlocal index
            index -= 1
            if index >= 0 and index < len(new_seq):
                ele = new_seq[index]
            else:
                index = len(new_seq) - 1
                ele = new_seq[index]
            return ele

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

