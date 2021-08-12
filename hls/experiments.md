
# 实验记录

## Matrix Multiply

| data type | FPGA Customized | Latency   | Frequency  | csynth_design elapsed time | Latency[^1] |
| --------- | --------------- | --------- | ---------- | -------------------------- | ----------- |
| float     | default         | 0.188 ms  | 142.53 MHz | 8.93 seconds               | ?           |
| ap_fixed  | default         | 0.280 ms  | 313.28 MHz | 10.47 seconds              | ?           |
| ap_fixed  | optimized       | 95.680 us | 323.52 MHz | 164.75 seconds             | 6.29 us     |
| float     | optimized       | 0.105 ms  | 142.53 MHz | 144.72 seconds             | 13.03 us    |

读入模型参数的耗时在模型优化前大概占 $50\%$，优化之后约占 $93.4\%$

[^1]: 不考虑模型的参数