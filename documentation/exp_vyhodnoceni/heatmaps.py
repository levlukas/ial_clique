import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

# Load the data with error handling
file_path = "..//experiment.csv"  # Replace with your file path
try:
    data = pd.read_csv(file_path, on_bad_lines='skip')  # Skip problematic rows
except Exception as e:
    print("Error reading CSV:", e)
    exit()

# Replace 'na' with NaN for easier handling
data.replace('na', np.nan, inplace=True)

# Function to compute the mean for cells with multiple values
def compute_mean(cell):
    if isinstance(cell, str) and ',' in cell:  # Check for multiple values
        values = [float(x) for x in cell.split(',')]
        return np.mean(values)
    try:
        return float(cell)  # Convert single value to float
    except ValueError:
        return np.nan  # Handle non-numeric cases

# Apply the compute_mean function to relevant columns
data['bruteforce'] = data['bruteforce'].apply(compute_mean)
data['backtracking'] = data['backtracking'].apply(compute_mean)

# Convert size and density to numeric for pivoting (if necessary)
data['size'] = pd.to_numeric(data['size'], errors='coerce')
data['density'] = pd.to_numeric(data['density'], errors='coerce')

# Create pivot tables for heatmaps
bruteforce_pivot = data.pivot_table(
    index='size',
    columns='density',
    values='bruteforce',
    aggfunc='mean'
)

backtracking_pivot = data.pivot_table(
    index='size',
    columns='density',
    values='backtracking',
    aggfunc='mean'
)

# Plotting the heatmaps
fig, axes = plt.subplots(1, 2, figsize=(18, 8))

# Bruteforce heatmap
sns.heatmap(bruteforce_pivot, ax=axes[0], cmap="viridis", annot=True, fmt=".2f")
axes[0].set_title("hrubá síla")
axes[0].set_xlabel("hustota hran v matici sousednosti")
axes[0].set_ylabel("n")

# Backtracking heatmap
sns.heatmap(backtracking_pivot, ax=axes[1], cmap="viridis", annot=True, fmt=".2f")
axes[1].set_title("zpětné vyhledávání")
axes[1].set_xlabel("hustota hran v matici sousednosti")
axes[1].set_ylabel("n")

# Show the plots
plt.tight_layout()
plt.show()
