n1 = int(input("Enter the first number : "))
opr = input("Select opration :  ");
n2 = int(input("Enter second number : "))
if opr == "+":
    print(n1 + n2)
elif opr == "-":
    print(n1 - n2)
elif opr == "*":
    print(n1 * n2)
elif opr == "/":
    print(n1 / n2)
else:
    print("invalid Value")
