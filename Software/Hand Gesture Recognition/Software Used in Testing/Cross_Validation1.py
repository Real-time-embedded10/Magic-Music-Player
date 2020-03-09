from sklearn import svm
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

# Combine two vectors
def createset (array1,array2):
    array = np.vstack((array1,array2))
    return array

# Select training samples randomly
def datatest(x,a):
    arr = np.arange(180)
    np.random.shuffle(arr)
    randomarray = np.random.permutation(180)
    xtest = np.zeros((20,21))
    xtrain = np.zeros((160,21))
    for i in range(20):
        for j in range(21):
            xtest[i,j] = x[randomarray[i]+a,j]
    for i in range (160):
        for j in range (21):
            xtrain[i,j] = x[randomarray[i+20]+a,j]
    return xtest, xtrain


result = excel_to_matrix('./feature.xlsx')
x = np.real(result)
#F = Forward, B = Backward, L = Left, R = Right, U = Up, D = Down
xtestF, xtrainF = datatest(x,0)
xtestB, xtrainB = datatest(x,180)
xtestL, xtrainL = datatest(x,360)
xtestR, xtrainR = datatest(x,540)
xtestU, xtrainU = datatest(x,720)
xtestD, xtrainD = datatest(x,900)

xtest = createset (xtestF,xtestB)
xtest = createset (xtest,xtestL)
xtest = createset (xtest,xtestR)
xtest = createset (xtest,xtestU)
xtest = createset (xtest,xtestD)

xtrain = createset (xtrainF,xtrainB)
xtrain = createset (xtrain,xtrainL)
xtrain = createset (xtrain,xtrainR)
xtrain = createset (xtrain,xtrainU)
xtrain = createset (xtrain,xtrainD)
y = [0] * 160 + [1] * 160 + [2] * 160 + [3] * 160 + [4] * 160 + [5] * 160

clf = svm.SVC(C=1.0, cache_size=200, class_weight=None,
    decision_function_shape='ovo', kernel='linear',
    max_iter=-1, probability=False, random_state=None, shrinking=True,
    tol=0.001, verbose=False)

clf.fit(xtrain,y)

###F
yF = 0
yB = 0
yL = 0
yR = 0
yU = 0
yD = 0
for i in range(20):
    ytest = clf.predict([np.real(xtest[i,:])])
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

###B
yF = 0
yB = 0
yL = 0
yR = 0
yU = 0
yD = 0
for i in range(20):
    ytest = clf.predict([np.real(xtest[i+20,:])])
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


###L
yF = 0
yB = 0
yL = 0
yR = 0
yU = 0
yD = 0
for i in range(20):
    ytest = clf.predict([np.real(xtest[i+40,:])])
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


###R
yF = 0
yB = 0
yL = 0
yR = 0
yU = 0
yD = 0
for i in range(20):
    ytest = clf.predict([np.real(xtest[i+60,:])])
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



###U
yF = 0
yB = 0
yL = 0
yR = 0
yU = 0
yD = 0
for i in range(20):
    ytest = clf.predict([np.real(xtest[i+80,:])])
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


###D
yF = 0
yB = 0
yL = 0
yR = 0
yU = 0
yD = 0
for i in range(20):
    ytest = clf.predict([np.real(xtest[i+100,:])])
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

