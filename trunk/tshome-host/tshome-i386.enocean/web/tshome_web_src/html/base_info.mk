include ../libs.mk
#目标信息
objs = $(base_obj) base_info.o 
basic_control = $(obj_path)/base_info.html

#开始编译
$(basic_control)	:	$(objs)
	$(TS_GCC) -Wall -o $(basic_control)  $(objs) $(imp_gateway) -I $(path_comm)  $(ts_db_lib) $(lib_cgic)
base_info.o :
	$(TS_GCC) -Wall -c $(html_path)/base_info.c $(imp_gateway)  -I $(path_comm) $(ts_db_lib) $(lib_cgic)
#清除
clean:
	rm -rf $(basic_control) base_info.o 
