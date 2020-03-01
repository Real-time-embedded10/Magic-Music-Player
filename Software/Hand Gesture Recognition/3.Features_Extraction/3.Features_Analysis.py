import pandas as pd
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

def feature_set(nums):
    #global mean, median, var, std, diff
    mean = np.mean(nums)
    median = np.median(nums)
    var = np.var(nums,ddof = 1)
    std = np.std(nums,ddof = 1)
    diff = np.max(nums) - np.min(nums)
    return [mean,median,var,std,diff]

def skewness_and_kurtosis(nums):
    #global skew,kurt
    s = pd.Series(nums)
    skew = 100*s.skew()
    kurt = 100*s.kurt()
    # n = len(nums)
    # skew = (np.sum((nums-u)**3)/n)/((np.sum((nums-u)**2))/(n-1))**(3/2)
    # kurt = (np.sum((nums-u)**4)/n)/((np.sum((nums-u)**2))/n)**2 - 3
    return [skew,kurt]

def correlation(x,y,z):
    #global correlation_xy,correlation_xz,correlation_yz,correlation_mean
    correlation_xy = np.cov(x,y)[0,1]/np.sqrt(np.var(x) * np.var(y)) * 100
    correlation_xz = np.cov(x,z)[0,1]/np.sqrt(np.var(x) * np.var(z)) * 100
    correlation_yz = np.cov(y,z)[0,1]/np.sqrt(np.var(y) * np.var(z)) * 100
    correlation_mean = (correlation_xy+correlation_xz+correlation_yz)/3
    return [correlation_xy,correlation_xz,correlation_yz,correlation_mean]


result = excel_to_matrix('./sample.xlsx')
rows, cols = result.shape
print(rows, cols)
number = rows//31
feature = np.zeros((number, 50), dtype='uint16')

for i in range(number):
    sample = []
    sample = result[(1*(i+1)-1):(30*(i+1)-1), :]
    print(i)
    mean_ax, median_ax, var_ax, std_ax, diff_ax = feature_set(sample[:, 0])
    mean_ay, median_ay, var_ay, std_ay, diff_ay = feature_set(sample[:, 1])
    mean_az, median_az, var_az, std_az, diff_az = feature_set(sample[:, 2])
    mean_gx, median_gx, var_gx, std_gx, diff_gx = feature_set(sample[:, 3])
    mean_gy, median_gy, var_gy, std_gy, diff_gy = feature_set(sample[:, 4])
    mean_gz, median_gz, var_gz, std_gz, diff_gz = feature_set(sample[:, 5])
    skew_ax, kurt_ax = skewness_and_kurtosis(sample[:, 0])
    skew_ay, kurt_ay = skewness_and_kurtosis(sample[:, 1])
    skew_az, kurt_az = skewness_and_kurtosis(sample[:, 2])
    skew_gx, kurt_gx = skewness_and_kurtosis(sample[:, 3])
    skew_gy, kurt_gy = skewness_and_kurtosis(sample[:, 4])
    skew_gz, kurt_gz = skewness_and_kurtosis(sample[:, 5])
    correlation_xy_a, correlation_xz_a, correlation_yz_a, correlation_mean_a = correlation(sample[:, 0], sample[:, 1],
                                                                                           sample[:, 2])
    correlation_xy_g, correlation_xz_g, correlation_yz_g, correlation_mean_g = correlation(sample[:, 3], sample[:, 4],
                                                                                           sample[:, 5])
    feature[i] = [mean_ax, median_ax, var_ax, std_ax, diff_ax,
                        mean_ay, median_ay, var_ay, std_ay, diff_ay,
                        mean_az, median_az, var_az, std_az, diff_az,
                        mean_gx, median_gx, var_gx, std_gx, diff_gx,
                        mean_gy, median_gy, var_gy, std_gy, diff_gy,
                        mean_gz, median_gz, var_gz, std_gz, diff_gz,
                        skew_ax, kurt_ax, skew_ay, kurt_ay, skew_az, kurt_az,
                        skew_gx, kurt_gx, skew_gy, kurt_gy, skew_gz, kurt_gz,
                        correlation_xy_a, correlation_xz_a, correlation_yz_a, correlation_mean_a,
                        correlation_xy_g, correlation_xz_g, correlation_yz_g, correlation_mean_g]

x = np.real(feature)
save(x,'./feature.xlsx')



