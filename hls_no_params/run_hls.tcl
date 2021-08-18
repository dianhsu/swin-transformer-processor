# 设置项目名称
open_project stp
# 设置顶层函数名称（要在代码中找得到这个顶层函数名）
set_top project_top

# 添加代码文件
add_files config.h
add_files controller.h
add_files data_selection_and_arrangement.h
add_files functions.h
add_files linear.h
add_files matrix_multiply.h
add_files partition_merge.h
add_files residual_attention.h
add_files residual_feed_forward.h
add_files main.cpp
add_files main.h

# 添加TestBench文件，用于 c sim。
add_files -tb main_tb.cpp

# 设置 solution 的目标是 vivado
open_solution "solution" -flow_target vivado

# 设置芯片型号，这个是ZCU102的芯片
set_part {xczu9eg-ffvb1156-2-e}

create_clock -period 10 -name default

#csim_design
csynth_design

exit