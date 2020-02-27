import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

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
    #n = len(nums)
    #skew = (np.sum((nums-u)**3)/n)/((np.sum((nums-u)**2))/(n-1))**(3/2) 
    #kurt = (np.sum((nums-u)**4)/n)/((np.sum((nums-u)**2))/n)**2 - 3 
    return [skew,kurt]

def correlation(x,y,z):
    #global correlation_xy,correlation_xz,correlation_yz,correlation_mean
    correlation_xy = np.cov(x,y)[0,1]/np.sqrt(np.var(x) * np.var(y))
    correlation_xz = np.cov(x,z)[0,1]/np.sqrt(np.var(x) * np.var(z))
    correlation_yz = np.cov(y,z)[0,1]/np.sqrt(np.var(y) * np.var(z))
    correlation_mean = (correlation_xy+correlation_xz+correlation_yz)/3
    return [correlation_xy,correlation_xz,correlation_yz,correlation_mean]




