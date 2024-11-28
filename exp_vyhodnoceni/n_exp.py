import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import linregress
from scipy.optimize import curve_fit
from scipy.interpolate import CubicSpline

# Fit parabola (quadratic) to log-log bruteforce data
def quadratic(x, a, b, c):
    return a * x**2 + b * x + c

# Load the Excel file and the 'srovnavaci graf' sheet
file_path = 'data.xlsx'
data = pd.read_excel(file_path, sheet_name='srovnavaci graf')

# Clean the data: Convert 'na' to NaN in both 'bruteforce' and 'backtracking' and drop rows with NaN values
data['bruteforce'] = pd.to_numeric(data['bruteforce'], errors='coerce')
data['backtracking'] = pd.to_numeric(data['backtracking'], errors='coerce')

# Remove rows with NaN or non-positive values for bruteforce or backtracking
data_cleaned = data[(data['bruteforce'] > 0) | (data['backtracking'] > 0)]

# Check if the cleaned data contains any rows
if data_cleaned.empty:
    print("No valid data left after cleaning. Please check your dataset.")
else:
    # Plotting setup
    fig, axs = plt.subplots()
    fig.figsize = (10, 10)

    # Linear plot (bruteforce and backtracking vs. size)
    axs.scatter(data_cleaned['size'], data_cleaned['bruteforce'], label='hrubá síla', color='skyblue', alpha=1, marker='+')
    axs.scatter(data_cleaned['size'], data_cleaned['backtracking'], label='zpětné vyhledávání', color='orange', alpha=1, marker='+')
    axs.set_xlabel('n')
    axs.set_ylabel('čas')

    # spline
    # x1 = data_cleaned[data_cleaned['bruteforce'].notna()]['size'].sort_values()
    # y1 = data_cleaned[data_cleaned['bruteforce'].notna()]['bruteforce'].sort_values()
    # x2 = data_cleaned[data_cleaned['backtracking'].notna()]['size'].sort_values()
    # y2 = data_cleaned[data_cleaned['backtracking'].notna()]['backtracking'].sort_values()
    # cs1 = CubicSpline(x1, y1)
    # cs2 = CubicSpline(x2, y2)
    # axs.plot(x1, cs1(x1), color='skyblue', linestyle='--')
    # axs.plot(x2, cs2(x2), color='orange', linestyle='--')

    axs.legend()

    plt.show()
    plt.close()

    # second plot
    fig, axs = plt.subplots()
    fig.figsize = (10, 10)

    # Log-log plot (log scale for y-axis)
    axs.scatter(data_cleaned['size'], data_cleaned['bruteforce'], label='hrubá síla, log', color='skyblue', alpha=1, marker='x')
    axs.scatter(data_cleaned['size'], data_cleaned['backtracking'], label='zpětné vyhledávání, log', color='orange', alpha=1, marker='x')
    axs.set_xlabel('log(n)')
    axs.set_ylabel('čas, log')
    axs.set_yscale('log')
    axs.set_xscale('log')

    log_bruteforce = np.log(data_cleaned['bruteforce'])
    log_backtracking = np.log(data_cleaned['backtracking'])

    # Linear fit for bruteforce and backtracking
    slope_bf, intercept_bf, _, _, _ = linregress(np.log(data_cleaned[data_cleaned['bruteforce'].notna()]['size']), 2 * np.log(data_cleaned[data_cleaned['bruteforce'].notna()]['bruteforce']))
    slope_bt, intercept_bt, _, _, _ = linregress(np.log(data_cleaned[data_cleaned['backtracking'].notna()]['size']), np.log(data_cleaned[data_cleaned['backtracking'].notna()]['backtracking']))

    # Add the linear fits to the log-log plot
    x_vals_bf = np.linspace(20.4, 30, 100)
    x_vals_bt = np.linspace(78, data_cleaned['size'].max(), 100)
    y_vals_bf = np.exp(slope_bf * np.log(x_vals_bf) + intercept_bf)
    y_vals_bt = np.exp(slope_bt * np.log(x_vals_bt) + intercept_bt)

    axs.plot(x_vals_bf, y_vals_bf, color='blue', linestyle='--')
    axs.plot(x_vals_bt, y_vals_bt, color='red', linestyle='--')

    axs.legend()

    plt.show()
    plt.close()


    # Output the slopes of the fitted curves in the log-log scale
    print(f'Slope of Bruteforce in log-log scale: {slope_bf:.2f}')
    print(f'Slope of Backtracking in log-log scale: {slope_bt:.2f}')
