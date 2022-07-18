def make_class(className, attrs, base=None):
    """Return a new class (a dispatch dictionary) with given class attributes"""
    #print(attrs)
    # Getter: class attribute (looks in this class, then base)
    def get(name):
        if name == 'name':
            return className
        elif name in attrs:
            return attrs[name]
        elif base:
            return base['get'](name)

    def class_path():
        """return the inheritance of objects """
        if base:
            return base['class_path']() + '::' + className
        return className

    # Setter: class attribute (always sets in this class)
    def set(name, value):
        attrs[name] = value

    # Return a new initialized objec'aaa': 5.5t instance (a dispatch dictionary)
    def new(*args):
        # instance attributes (hides encapsulating function's attrs)
        attrs = {}

        # Getter: instance attribute (looks in object, then class (binds self if callable))
        def get(name):
            if name in attrs:
                return attrs[name]
            else:
                value = cls['get'](name)
                if callable(value): #check if value are function , if is funtion return lambda function.
                    return lambda *args: value(obj, *args)
                else:
                    return value #else value are var static or none

        # Setter: instance attribute (always sets in object)
        def set(name, value):
            attrs[name] = value

        # instance dictionary
        obj = { 'get': get, 'set': set }

        # calls constructor if present
        init = get('__init__')
        if init:
            init(*args)

        return obj

    # class dictionary
    cls = { 'get': get, 'set': set, 'new': new, 'class_path': class_path}
    return cls

def make_account_class():
    return make_class('Account', {'interest' : 0.05})

def make_save_account_class():
    def init(self, owner):
        self['set']('owner',owner)
        self['set']('balance',0)

    return make_class('SaveAccount', {'__init__' : init, 'interest' : 0.03}, Account)


Account = make_account_class()
SaveAccount = make_save_account_class()

# print(Account['class_path']())
# print(SaveAccount['class_path']())