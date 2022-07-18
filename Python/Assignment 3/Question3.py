# --------------Conventional Interface, Pipline-------------------
from functools import reduce
from operator import add

def avg_grades(courses):
    '''
    get list courses and return for eatch courses the average of grades
    :param courses:
    :return:
    '''
    return tuple(map(lambda x: (x[0], reduce(add,x[1])/len(x[1])) ,courses))

def add_factors(courses, factor):
    '''
    The function returns the list of courses with the updated grades after the factor.
    :param courses:
    :param factor:
    :return:
    '''
    name_of_courses = tuple(map(lambda name: name[0], factor))
    return tuple(map(lambda x: (x[0], x[1] + factor[name_of_courses.index(x[0])][1]) if x[0] in name_of_courses else x, courses))

def total_average(courses,credits):
    '''
    The function returns the overall average of all courses
    :param courses:
    :param credits:
    :return:
    '''
    name_of_courses = tuple(map(lambda x: x[0],credits))
    return sum(map(lambda x: x[1]*credits[name_of_courses.index(x[0])][1] if x[0] in name_of_courses else x[1], courses))/ sum(map(lambda x: x[1],credits))

