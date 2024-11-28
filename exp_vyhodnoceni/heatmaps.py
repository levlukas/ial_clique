import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

file_path = "..//experiment.csv"
try:
    data = pd.read_csv(file_path, on_bad_lines='skip')
except Exception as e:
    print("Error reading CSV:", e)
    exit()

data.replace('na', np.nan, inplace=True)

def compute_mean(cell):
    if isinstance(cell, str) and ',' in cell:
        values = [float(x) for x in cell.split(',')]
        return np.mean(values)
    try:
        return float(cell)  
    except ValueError:
        return np.nan

data['bruteforce'] = data['bruteforce'].apply(compute_mean)
data['backtracking'] = data['backtracking'].apply(compute_mean)

data['size'] = pd.to_numeric(data['size'], errors='coerce')
data['density'] = pd.to_numeric(data['density'], errors='coerce')

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

fig, axes = plt.subplots(1, 2, figsize=(18, 8))

sns.heatmap(bruteforce_pivot, ax=axes[0], cmap="viridis", annot=True, fmt=".2f")
axes[0].set_title("hrubá síla")
axes[0].set_xlabel("hustota hran v matici sousednosti")
axes[0].set_ylabel("n")

sns.heatmap(backtracking_pivot, ax=axes[1], cmap="viridis", annot=True, fmt=".2f")
axes[1].set_title("zpětné vyhledávání")
axes[1].set_xlabel("hustota hran v matici sousednosti")
axes[1].set_ylabel("n")

plt.tight_layout()
plt.show()
