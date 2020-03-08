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
    if ((result[r, 0] > 750) or (result[r, 0] < -750)):
        sample[r, 0] = 1
    else:
        if ((result[r, 1] > 750) or (result[r, 1] < -750)):
            sample[r, 0] = 1
        else:
            if ((result[r, 2] > 2250) or (result[r, 2] < 750)):
                sample[r, 0] = 1
            else:
                if ((result[r, 3] > 750) or (result[r, 3] < -750)):
                    sample[r, 0] = 1
                else:
                    if ((result[r, 4] > 750) or (result[r, 4] < -750)):
                        sample[r, 0] = 1
                    else:
                        if ((result[r, 5] > 750) or (result[r, 5] < -750)):
                            sample[r, 0] = 1
                        else:
                            sample[r, 0] = 0

x = np.real(sample)
save(x,'./sampleanalysis.xlsx')