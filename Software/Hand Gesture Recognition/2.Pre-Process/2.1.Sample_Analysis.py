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
sample = np.zeros((rows, 2), dtype='uint16')
i = 0
for r in range(rows):
    if ((result[r, 0] > 50) or (result[r, 0] < -50)):
        sample[i, 0] = r
        sample[i, 1] = 1
        i = i + 1
    else:
        if ((result[r, 1] > 50) or (result[r, 1] < -50)):
            sample[i, 0] = r
            sample[i, 1] = 2
            i = i + 1
        else:
            if ((result[r, 2] > 200) or (result[r, 2] < 100)):
                sample[i, 0] = r
                sample[i, 1] = 3
                i = i + 1
            else:
                if ((result[r, 3] > 50) or (result[r, 3] < -50)):
                    sample[i, 0] = r
                    sample[i, 1] = 4
                    i = i + 1
                else:
                    if ((result[r, 4] > 50) or (result[r, 4] < -50)):
                        sample[i, 0] = r
                        sample[i, 1] = 5
                        i = i + 1
                    else:
                        if ((result[r, 5] > 50) or (result[r, 5] < -50)):
                            sample[i, 0] = r
                            sample[i, 1] = 6
                            i = i + 1

x = np.real(sample)
save(x,'./sampleanalysis.xlsx')
