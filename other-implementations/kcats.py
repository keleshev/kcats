

def parse(s): return s.split(' ')

def is_number(s): 
    try: float(s)
    except ValueError: return False
    return True

def num(s):
    if s.isdigit(): return int(s)
    if is_number(s): return float(s)
    raise ValueError

class Stack:
    _d = []
    def __str__(self):
       #return str(list(reversed(self._d)))
        return str(self._d).replace(',', '')
    def clear(self):
        self._d = []
    def read(self):
        return self._d[-1]
    def push(self, val):
        self._d.append(val)
    def pop(self):
        return self._d.pop()
    def duplicate(self):
        self.push(self.read())
    def apply(self, f, arity):
        args = []
        for i in range(arity):
            args.append(self.pop())
        self.push(apply(f, list(reversed(args))))

    def evaluate_token(self, t):
        if is_number(t): self.push(num(t))
       #elif is_string(t): self.push(t)
        elif t=='#': print self.pop()
        elif t=='$': self.duplicate()
        elif t=='+': self.apply(lambda x,y: x+y, 2)
        elif t=='-': self.apply(lambda x,y: x-y, 2)
        elif t=='*': self.apply(lambda x,y: x*y, 2)
        elif t=='/': self.apply(lambda x,y: float(x)/y, 2)
        elif t=='!': self.apply(lambda x: num(not(x)), 1)
        elif t=='^': self.apply(lambda x,y: x**y, 2)
        else: self.push(t)
       #else: print t+'?'



def kcats():
    s = Stack()
    while True:
        print s
        input = raw_input('kcats> ')
        if input.startswith(':'):
            if input == ':q': break
            if input == ':c': s.clear() 
        else:
            tokens = parse(input)
            for t in tokens:
                s.evaluate_token(t)
        
kcats()



