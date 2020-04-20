import numpy as np
import xlrd


# Read an excel
def excel_to_matrix(path):
    table = xlrd.open_workbook(path).sheets()[0]
    row = table.nrows #Read the number of rows in excel.
    col = table.ncols #Read the number of columns in excel.
    datamatrix = np.zeros((row, col))  # Create a zero matrix with the same size as excel.
    for x in range(col):
        cols = np.matrix(table.col_values(x))
        datamatrix[:, x] = cols  # Collect data in excel into matrix.
    return datamatrix

def prediction(array):
    if (array[0] == np.max(array)):
        y = 0
    if (array[1] == np.max(array)):
        y = 1
    if (array[2] == np.max(array)):
        y = 2
    if (array[3] == np.max(array)):
        y = 3
    if (array[4] == np.max(array)):
        y = 4
    if (array[5] == np.max(array)):
        y = 5
    return y


# Read information of extracted key features of all samples. 
result = excel_to_matrix('./feature.xlsx')
# w is our weight martix which will be used to establish machine learning model.
# b is our bias martix which will also be used to establish machine learning model.
w = excel_to_matrix('./w.xlsx')
b = np.array([0.1545268, 0.11176813, -0.39776308, 0.07103815, -0.07802755, 0.13513086])

rows, cols = result.shape
number = rows//6
fea = result/(10^4)

### Forward
yF = 0
yB = 0
yL = 0
yR = 0
yU = 0
yD = 0
for i in range(number):
    y_pre = np.dot(w, fea[i]) + b
    ytest = prediction(y_pre)
    if ytest == 0:
        yF = yF + 1
    if ytest == 1:
        yB = yB + 1
    if ytest == 2:
        yL = yL + 1
    if ytest == 3:
        yR = yR + 1
    if ytest == 4:
        yU = yU + 1
    if ytest == 5:
        yD = yD + 1
print('Forward')
print('F= ', yF,'B= ', yB,'L= ', yL,'R= ', yR,'U= ', yU,'D= ', yD)

### Backward
yF = 0
yB = 0
yL = 0
yR = 0
yU = 0
yD = 0
for i in range(number):
    y_pre = np.dot(w, fea[i+number]) + b
    ytest = prediction(y_pre)
    if ytest == 0:
        yF = yF + 1
    if ytest == 1:
        yB = yB + 1
    if ytest == 2:
        yL = yL + 1
    if ytest == 3:
        yR = yR + 1
    if ytest == 4:
        yU = yU + 1
    if ytest == 5:
        yD = yD + 1
print('Backward')
print('F= ', yF,'B= ', yB,'L= ', yL,'R= ', yR,'U= ', yU,'D= ', yD)


### Left
yF = 0
yB = 0
yL = 0
yR = 0
yU = 0
yD = 0
for i in range(number):
    y_pre = np.dot(w, fea[i+number*2]) + b
    ytest = prediction(y_pre)
    if ytest == 0:
        yF = yF + 1
    if ytest == 1:
        yB = yB + 1
    if ytest == 2:
        yL = yL + 1
    if ytest == 3:
        yR = yR + 1
    if ytest == 4:
        yU = yU + 1
    if ytest == 5:
        yD = yD + 1
print('Left')
print('F= ', yF,'B= ', yB,'L= ', yL,'R= ', yR,'U= ', yU,'D= ', yD)


### Right
yF = 0
yB = 0
yL = 0
yR = 0
yU = 0
yD = 0
for i in range(number):
    y_pre = np.dot(w, fea[i+number*3]) + b
    ytest = prediction(y_pre)
    if ytest == 0:
        yF = yF + 1
    if ytest == 1:
        yB = yB + 1
    if ytest == 2:
        yL = yL + 1
    if ytest == 3:
        yR = yR + 1
    if ytest == 4:
        yU = yU + 1
    if ytest == 5:
        yD = yD + 1
print('Right')
print('F= ', yF,'B= ', yB,'L= ', yL,'R= ', yR,'U= ', yU,'D= ', yD)



### Up
yF = 0
yB = 0
yL = 0
yR = 0
yU = 0
yD = 0
for i in range(number):
    y_pre = np.dot(w, fea[i+number*4]) + b
    ytest = prediction(y_pre)
    if ytest == 0:
        yF = yF + 1
    if ytest == 1:
        yB = yB + 1
    if ytest == 2:
        yL = yL + 1
    if ytest == 3:
        yR = yR + 1
    if ytest == 4:
        yU = yU + 1
    if ytest == 5:
        yD = yD + 1
print('Up')
print('F= ', yF,'B= ', yB,'L= ', yL,'R= ', yR,'U= ', yU,'D= ', yD)


### Down
yF = 0
yB = 0
yL = 0
yR = 0
yU = 0
yD = 0
for i in range(number):
    y_pre = np.dot(w, fea[i+number*5]) + b
    ytest = prediction(y_pre)
    if ytest == 0:
        yF = yF + 1
    if ytest == 1:
        yB = yB + 1
    if ytest == 2:
        yL = yL + 1
    if ytest == 3:
        yR = yR + 1
    if ytest == 4:
        yU = yU + 1
    if ytest == 5:
        yD = yD + 1
print('Down')
print('F= ', yF,'B= ', yB,'L= ', yL,'R= ', yR,'U= ', yU,'D= ', yD)
