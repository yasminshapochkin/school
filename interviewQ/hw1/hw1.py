import numpy as np

def hw1():
    board = np.array([[0,1,2,0],
             [3,0,0,0],
             [0,0,1,0],
             [0,4,0,0]])

    
    board_evelable = np.array([
             [0,1,1,0],
             [1,0,0,0],
             [0,0,1,0],
             [0,1,0,0]])
    size = 2
    numbersRow = np.array([[1,1,1,1],
                          [1,1,1,1],
                          [1,1,1,1],
                          [1,1,1,1]])
    
    numbersCol = np.array([[1,1,1,1],
                          [1,1,1,1],
                          [1,1,1,1],
                          [1,1,1,1]])
    
    for i in range(size*size):
        for j in range(size*size):
            if (board[i][j] != 0):
                numbersRow[i][board[i][j]-1] = 0
                numbersCol[j][board[i][j]-1] = 0


    for i in range(size*size):
        for j in range(size*size):
            if board[i][j] == 0:
                ii = numbersRow[i] + numbersCol[j]
                for k in range(size*size):
                    if (ii[k] == 2):
                        numbersRow[i][k] = 0
                        numbersCol[j][k] = 0
                        board[i][j] = k + 1
                        
    print(board)


if __name__ == '__main__':
    hw1()    


