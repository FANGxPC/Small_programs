
from numpy import *
import matplotlib.pyplot as plt

def eror(b,m,points):
    totalerr=0
    for i in range(0 , len(points)):
        x=points[i, 0]
        y=points[i, 1]

        totalerr += (y-(m*x +b))**2
    return totalerr/float(len(points))


def grad_desc(points, init_b , init_m , lr , num_iter):
    b = init_b
    m = init_m
    x = points[:, 0]
    y = points[:, 1]
    for i in range(num_iter):
        b, m = step_grad(b, m, array(points), lr)
        # Visualize every 100 iterations
        if i !=0 :
            plt.clf()
            plt.scatter(x, y, color='blue', label='Data Points')
            y_pred = m * x + b
            plt.plot(x, y_pred, color='red', label=f'Iteration {i}\nm={m:.2f}, b={b:.2f}')
            plt.xlabel('x')
            plt.ylabel('y')
            plt.title('Linear Regression Progression')
            plt.legend()
            plt.pause(0.001)
    plt.show()
    return [b, m]

def step_grad(init_b , init_m , points , lr):
    b_grad=0
    m_grad=0
    N = float(len(points))
    for  i in range(0, len(points)):
        x=points[i,0]
        y=points[i,1]

        b_grad+= -(2/N)*(y- ((init_m*x)+init_b))
        m_grad+= -(2/N)*x*(y- ((init_m*x)+init_b))

    new_b= init_b - ( lr*b_grad)
    new_m= init_m - ( lr*m_grad)
    return [new_b ,new_m]


def run():
    points=genfromtxt('sample.csv',delimiter=',', skip_header=1)

    lr =0.0001 # learning rate
    # y =mx + b
    inital_b=0
    inital_m=0

    num_iter= 10000
    
    print(f"Starting grading descent : b  = {inital_b} , m = {inital_m} err: {eror(inital_b,inital_m, points)}")


    [b,m]=grad_desc(points, inital_b,inital_m, lr, num_iter)

    print(f"Ending grading descent : b  = {b} , m = {m} err: {eror(b,m, points)}")





if __name__ =='__main__':
    run()