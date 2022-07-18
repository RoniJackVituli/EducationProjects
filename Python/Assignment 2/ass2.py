# Roni Jack Vituli



#----------------------------------------- Question Number 2 -------------------------------------------------------------------
# a
def my_filter(b_F):
    """
    This function is high function it get function and return function.
    the function it get is boolean function.
    the fuction it return get a list and create new list and put elements from the list it recevied that perform the boolean function.
    :param b_F:
    :return new_list:
    """
    def new_list(listA):
        listB = []
        for i in range(len(listA)):
            if b_F(listA[i]):
                listB.append(listA[i])
        return listB
    return new_list

# b
def filtered_words(list_word,n):
    """
    this function get list of word and num, then create new list of word that length of the word bigger than num
    :param list_word:
    :param n:
    :return:
    """
    return my_filter(lambda x: len(x) > n)(list_word)

# c
def my_map(F):
    """
    This function is high function it get function and return function.
    the update funtion update the elemente on the list with the function my_map get.
    :param F:
    :return:
    """
    def update(lst):
        for i in range(len(lst)):
            lst[i] = F(lst[i])
        return lst
    return update

# d

def my_filter_and_map(lst,BF1,BF2):
    """
    this function get a list and two function.
    one function is boolean the second is function return some value.
    so function my_filter_and_map crete new list that put elements from the old list that preform the boolean function and update the old value to new values.
    :param lst:
    :param BF1:
    :param BF2:
    :return:
    """
    return my_map(BF2)(my_filter(BF1)(lst))


#----------------------------------------- Question Number 3 -------------------------------------------------------------------

def polynomial(factors):
    """
    This function calculate polynomial value at some point
    :param factors:
    :return:
    """
    def sum_of_polynomial(value):
        sum = 0
        j = 0
        for i in range(len(factors)-1,-1,-1):
            sum += factors[j]*(lambda value,sqr: value**sqr)(value,i)
            j += 1
        return sum

    return sum_of_polynomial


#----------------------------------------- Question Number 4 -------------------------------------------------------------------
import random

def code_cracker():
    """
    This function start the game of code cracker.
    :return:
    """
    points = 100
    correct_num = random.randrange(10000,100000)
    guess = 0;
    i = 1
    flag = True
    print("Welcome to the pin cracker game!")
    def yes_or_no(F,n):
        """
        get a function and number and check if is bigger or smaller depends on the lambda.
        :param F:
        :param n:
        :return:
        """
        if F(n):
            return 'YES'
        return 'NO'

    def print_msg_to_func(msg,F):
        """
        get msg clue and function.
        and print new message.
        :param msg:
        :param F:
        :return:
        """
        print(msg + str(F(correct_num)))

    def show_string_by_func(msg,f):
        """
        this function get msg and function and makes printing according to the clue he received
        :param msg:
        :param f:
        :return:
        """
        nonlocal demo
        if(demo == 0):
         return msg
        elif(f(demo)):
            demo = demo//10
            return show_string_by_func(msg+'X',f)
        demo = demo//10
        return show_string_by_func(msg+'-',f)

    def update_points(point):
        """
        this function update to points of the player.
        :param point:
        :return:
        """
        point -= 10
        print("Points lef:",point)
        return point

    def check_input(guess):
        if(guess == ''):
            return guess
        while (len(guess) != 5):
            guess = input('Please enter correct number with 5 digits: ')
        return guess

    def guessF(guess):
        nonlocal flag,points
        guess = input('guess or press ENTER for exit: ')
        if(guess == ''):
            print("\n\nbye bye!")
            print("Left Points: ",points)
            flag = False
            return
        guess = (int)(check_input(guess))
        if(guess == correct_num):
            print("\n\nyes, correct!")
            print("Left Points: ", points)
            flag = False
        elif(points == 0):
            print("\n\nbye bye!")
            print("Left Points: ", points)
            flag = False
        return 0

    def reverse(correct_num):
        """
        this function help for print right the X or - .
        :param correct_num:
        :return:
        """
        temp = correct_num
        digit = 0
        rev_num = 0
        while((lambda x: x != 0)(temp)):
            digit = temp%10
            rev_num = (rev_num * 10) + digit
            temp = temp//10
        return rev_num


    while points > 0 and flag:
        clue = random.randrange(1,7)
        print("clue #", i)
        if(clue == 1):
            check_num = (int)(check_input(input('Enter number to check if the code is bigger:')))
            if((lambda x: x == correct_num)(check_num)):
                print("\n\nyes, correct!")
                print("Left Points: ", points)
                flag = False
            else:
                print(yes_or_no(lambda x: x < correct_num,check_num))
                points = update_points(points)
                guess = guessF(guess)
        elif(clue == 2):
            check_num = (int)(check_input(input('Enter number to check if the code is smaller:')))
            if ((lambda x: x == correct_num)(check_num)):
                print("\n\nyes, correct!")
                print("Left Points: ", points)
                flag = False
            else:
                print(yes_or_no(lambda x: x > correct_num, check_num))
                points = update_points(points)
                guess = guessF(guess)
        elif(clue == 3):
            print_msg_to_func('sum: ',lambda x: x%10 + (x//10)%10 + (x//100)%10 + (x//1000)%10 + x//10000)
            points = update_points(points)
            guess = guessF(guess)
        elif(clue == 4):
            print_msg_to_func('sub: ',lambda x: (x//10000) - (x//1000)%10 - (x//100)%10 - (x//10)%10 - x%10)
            points = update_points(points)
            guess = guessF(guess)
        elif (clue == 5):
            demo = reverse(correct_num)
            print(show_string_by_func('odd digits: ',lambda x : x%2))
            points = update_points(points)
            guess = guessF(guess)
        elif (clue == 6):
            demo = reverse(correct_num)
            print(show_string_by_func('digits divided by 3: ', lambda x: (x%10)%3 == 0))
            points = update_points(points)
            guess = guessF(guess)
        i+=1
        print('\n\n')


#code_cracker() #start the Game.
