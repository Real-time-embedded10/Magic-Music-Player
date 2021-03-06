import numpy as np
import xlrd
from openpyxl import Workbook

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

# Save matrix as excel
def save(data,path):
    wb = Workbook()
    ws = wb.active
    [h, l] = data.shape
    for i in range(h):
        row = []
        for j in range(l):
            row.append(data[i,j])
        ws.append(row)
    wb.save(path)

# Read the original information obtain from sensor 
result = excel_to_matrix('./result.xlsx')
rows, cols = result.shape
print(rows, cols)

# for r in range(rows):
#     AX = result[r, 0]
#     AY = result[r, 1]
#     AZ = result[r, 2]
#     GX = result[r, 3]
#     GY = result[r, 4]
#     GZ = result[r, 5]
sample = np.zeros((rows, 1), dtype='int16')
for r in range(rows):
    if ((result[r, 0] > 700) or (result[r, 0] < -700)):
        sample[r, 0] = 1
    else:
        if ((result[r, 1] > 700) or (result[r, 1] < -700)):
            sample[r, 0] = 1
        else:
            if ((result[r, 2] > 2200) or (result[r, 2] < 700)):
                sample[r, 0] = 1
            else:
                if ((result[r, 3] > 700) or (result[r, 3] < -700)):
                    sample[r, 0] = 1
                else:
                    if ((result[r, 4] > 700) or (result[r, 4] < -700)):
                        sample[r, 0] = 1
                    else:
                        if ((result[r, 5] > 700) or (result[r, 5] < -700)):
                            sample[r, 0] = 1
                        else:
                            sample[r, 0] = 0
position = np.transpose(np.nonzero(sample))

# Identify whether the gesture is
rows2, cols2 = position.shape
position_judge = np.zeros((rows+1, 1), dtype='uint16')
for r in range(rows2):
    position_judge[0, 0] = 0
    position_judge[r+1, 0] = position[r, 0]  # the r itme of position_judge is equal to the (r-1) itme of postion.
positiontest = np.zeros((rows2, 1), dtype='uint16')
i = 0
for r in range(rows2-1):
    if (position[r, 0] - position_judge[r, 0] >= 20):
        if (position[r+1, 0] - position_judge[r+1, 0] <= 2):
            positiontest[i, 0] = position[r, 0]
            i = i + 1

# Hand Geasture Segmentation
positionmark = np.trim_zeros(positiontest)
rows3, cols3 = positionmark.shape
marknumber = rows3
samplenumber = 31 * marknumber
savesample = np.zeros((samplenumber, 6), dtype='int16')
for i in range(marknumber):
    for r in range(30):
        for c in range(6):
            savesample[(i * 31 + r), c] = result[(positionmark[i, 0] - 9 + r), c]

# Save the position information of gesture in './positionmark.txt'
x = np.real(positionmark)
save(x,'./positionmark.xlsx')

# Save segmented result in './savesample.txt'
y = np.real(savesample)
save(y,'./savesample.xlsx')
