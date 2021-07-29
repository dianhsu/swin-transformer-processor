
# 实验记录

## Matrix Multiply

| data type | FPGA Customized | Latency   | Frequency  | csynth_design elapsed time |
| --------- | --------------- | --------- | ---------- | -------------------------- |
| float     | default         | 0.188 ms  | 142.53 MHz | 8.93 seconds               |
| ap_fixed  | default         | 0.280 ms  | 313.28 MHz | 10.47 seconds              |
| ap_fixed  | optimized       | 95.680 us | 323.52 MHz | 164.75 seconds             |
| float     | optimized       | 0.105 ms  | 142.53 MHz | 144.72 seconds             |