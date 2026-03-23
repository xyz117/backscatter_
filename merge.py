import glob
import pandas as pd
files = glob.glob("./build/Release/backscatter_*.csv")
dfs = [pd.read_csv(f, header=None,skiprows=12) for f in files]
merged = pd.concat(dfs, ignore_index=True)

# 保存合并结果
merged.to_csv("energy_merged.csv", index=False)
print(f"Merged {len(files)} thread files into energy_merged.csv")