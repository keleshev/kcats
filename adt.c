


Stack-new();

Stack-push(10);

int poped = Stack-pop(); 


void Stack-add() {
    Stack-push(Stack-pop() + Stack-pop());
}

#define Stack-infix(op) Stack-push(Stack-pop() #op Stack-pop())
