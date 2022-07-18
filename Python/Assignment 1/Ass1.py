

# Assignment 1
# Name: Roni Jack Vituli

'''
Assignment #1
Roni Jack Vituli 
'''


#Question 1

def Xnor(a,b):
    '''
    Question 1
    a function that recives two parameters of the same type and apply xnor
    parameters - a and b
    Returns true or false 
    '''
    if a == b:
        return True
    return False

def Digit_len(num):
    '''
    a function to help us in the assignment
    '''
    count = 0
    while(num != 0):
        num //= 10
        count += 1
    return count


def even_or_odd(x):
    '''a function that helped us in question2'''
    if(x % 2 == 0):
        return "even"
    return "odd"


#Question 2

def Digits(num):
    '''
    Question 2
    Function does as in the instructions
    Parameters - num
    Return value as in the instructions
	'''
    if( num > 0 and Digit_len(num) < 6):
       len = Digit_len(num)
       print(len)
       sum = 0
       str = ""
       if (len == 1):
           sum = num
           str = "One"
       elif(len == 2):
           sum = num//10 + num%10
           str = "Two"
       elif(len == 3):
            sum = num//100 + num%10
            str = "Three"
       elif(len == 4):
            sum = (num//10)%10 + (num//100)%10
            str = "Four"
       elif(len == 5):
           sum = (num//100)%10
           str = "Five"
       print('{0} digits   - {1}'.format(str,even_or_odd(sum)))

    else:
        print("ERROR!")


#Question 3
def GoodOrder(num):
    '''
    Question 3 
    a boolean function that returns true if all the digits of the number are odd or even and false if not
    Parameters - num(the number given)
    Return value - true or false
'''
    if(num >= 0):
        if(num > 9):
            state = even_or_odd(num)
            num //= 10
            while(num != 0):
                new_state = even_or_odd(num)
                if (state != new_state):
                    return False
                num //= 10
        return True
    print('Bad Number')
    return False

#Question 4
def Figure(num):
    '''
   Question 4
    prints a triangle as orderd we checked for repetitiveness of a rule and based on that we built the function
    Parameters -num:chooses the size of the triangle
    no Return value.
    '''
    for i in range(0,num-1):
        for j in range(0, num*2+1):
            if i + j == num - 1 or j - i == num - 1:
                print(i+1, end = '')
            else:
                print(' ', end = '')

        print('')
    for i in range(num,0,-1):
        print(i , end = '')
    for i in range(2, num+1):
        print(i , end = '')

#Question 5
def max(num):

    '''
   Question 5
    help function for question 5 its a recursive function to return the max digit
    Parameters -num 
    Return value max digit from the given number
    '''
    
    if(Recu_len(num) == 1):
         return num
    digit = num % 10
    num //= 10
    if(digit > num%10):
        num //=10
        num = num*10 + digit
    return max(num)

def Recu_len(num):

    '''
    help function for question 5 a recursive function to check a length of a number
    '''
    
    if(num == 0):
        return 0
    return 1 + Recu_len(num//10)

def weight(num):
    return max(num) + Recu_len(num)

#Question number 6

def IsPrimary(num, i = 2):

    '''
    Question 6
    finds if a number is a prime number with recurssion
    Parameters - num. i is for checking all the numbers
    Return value - true or false
    '''
    
    if(num == i or num == 1):
        return True
    elif(num % i == 0):
        return False
    return IsPrimary(num, i+1)




#Question number 7
def reduce(num):

    '''
      Question 7
    reduces zeroes with recurssion
    Parameters - num
    Return value - the number without zeroes
    '''
    
    if(num == 0):
        return 0
    if(num > 0):
        if (num % 10 == 0):
            return reduce(num // 10)
        return num % 10 + reduce(num // 10) * 10
    else:
        if (num % 10 == 0):
            return reduce(num // 10)
        return (10 - num % 10)*(-1) - reduce((num // 10) + 1) * 10 * (-1)



#Question number 8

def Pascal(n,m):

    '''
	Question 8
    the answer was based on the pascal triangle where each element depends on two elemnts before him
	the function checks how much ways to choose m elements from a set with a size of n
    Parameters - n: size of set, m - number of elements
    Return value - how much ways to choose m elements from a set with a size of n
    '''
    
    if( m > n or n < 0 or m < 0):
        return -1

    if n == m or m == 0:
        return 1
    return Pascal(n-1, m-1) + Pascal(n-1, m)

