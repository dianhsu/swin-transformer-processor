open_project project_hls
set_top project_top
add_files cyclic_shift.h
add_files main.cpp
add_files main.h
add_files -tb main_tb.cpp

open_solution "solution_default" -flow_target vivado
set_part {xcvu19p-fsva3824-2-e}
create_clock -period 10 -name default

csim_design
csynth_design
#cosim_design
#export_design -format ip_catalog
exit