import matplotlib.pyplot as plt
import numpy as np

# trace0.txt 파일을 로드 (경로 확인 필요)
trace = np.loadtxt('trace0.txt')

plt.figure(figsize=(15, 6))
plt.plot(trace, color='blue', linewidth=0.7, label='Power Trace')

# 1라운드 및 S-box 구간 집중 확대
plt.xlim(0, 3000) 

# 시각적 가이드 추가 (PPT 발표 시 매우 유용함)
plt.axvspan(1500, 2500, color='red', alpha=0.2, label='SubBytes (ROI)')

plt.title('AES 1st Round SPA Analysis (0 - 3000 Points)', fontsize=15)
plt.xlabel('Sample Points', fontsize=12)
plt.ylabel('Amplitude', fontsize=12)
plt.grid(True, which='both', linestyle='--', alpha=0.5)
plt.legend()

plt.show()
