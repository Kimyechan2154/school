import numpy as np
import matplotlib.pyplot as plt

# 1. 텍스트 파일에서 전력 데이터 읽어오기 (절대 경로 적용)
trace = np.loadtxt(r"C:\Users\kimye\OneDrive\Desktop\학교\PEPSI\PEPSI_DPA과제\DPA_main\DPA_main\trace0.txt")

# 2. 파형 시각화 (SPA)
plt.figure(figsize=(15, 5))
plt.plot(trace, linewidth=0.5, color='blue')
plt.title('SPA - Trace 0 Power Consumption')
plt.xlabel('Point Index (0 ~ 14863)')
plt.ylabel('Power Value')
plt.grid(True)
plt.show()
