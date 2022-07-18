def make_warehouse(courese_dict, credits_dict, types):
    '''
    get 3 arguments:
    1- Dictionary of courses with their average
    2- Dictionary of courses with their credits
    3- Dictionary of course lists by types.
    and returns dispatch dictionary
    :param courese_dict:
    :param credits_dict:
    :param types:
    '''
    def min_credits():
        '''
        Returns a grade in the course with the lowest credits
        :return:
        '''
        courses = courese_dict.items()
        mini_value_with_key = min(credits_dict, key=credits_dict.get)
        for k, v in courses:
            if k == mini_value_with_key:
                return v

    def max_credits():
        '''
        Returns a grade in the course with the highest credits
        :return:
        '''
        courses = courese_dict.items()
        mini_value_with_key = max(credits_dict, key=credits_dict.get)
        for k, v in courses:
            if k == mini_value_with_key:
                return v

    def max_courses(key):
        '''
        Returns the highest grade in the type of course
        :param key:
        :return:
        '''
        keys = types[key]
        max = courese_dict[keys[0]]
        for i in keys:
            if (max < courese_dict[i]):
                max = courese_dict[i]
        return max

    def min_courses(key):
        '''
        Returns the lowest grade in the type of course
        :param key:
        :return:
        '''
        keys = types[key]
        min = courese_dict[keys[0]]
        for i in keys:
            if (min > courese_dict[i]):
                min = courese_dict[i]
        return min

    def avg_course(key):
        '''
        Returns the grade point average in the type of course
        :param key:
        :return:
        '''
        keys = types[key]
        sum = 0
        count = 0
        for i in keys:
            sum += courese_dict[i]
            count += 1
        return sum / count

    def add_course(name_course, grade, key):
        '''
        Adds a new course!
        :param name_course:
        :param grade:
        :param key:
        :return:
        '''
        types[key] += tuple(name_course)
        courese_dict[name_course] = grade

    return {'min_credits': min_credits, 'max_credits': max_credits, 'avg_course': avg_course, 'min_course': min_courses,
            'max_course': max_courses, 'add_course': add_course}

