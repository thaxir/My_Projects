# Makefile. If you change it, remember than in makefiles multiple spaces
# ARE NOT EQUIVALENT to tabs. The line after a rule starts with a tab!

#Add any executable you want to be created here.
EXECUTABLES	= sobel_orig
EXECUTABLES1 	= loop_interchange
EXECUTABLES2	= loop_unrolling
EXECUTABLES3	= loop_unrolling_grammh_107
EXECUTABLES4	= function_inlining_1
EXECUTABLES5	= loop_unrolling_grammh_125_v1 
EXECUTABLES6	= loop_unrolling_grammh_108
EXECUTABLES7	= loop_unrolling_grammh_108_kata_4
EXECUTABLES8	= loop_fusion_vrogxou_107_me_125
EXECUTABLES9	= code_motion_v2
EXECUTABLES10	= code_motion_v1
EXECUTABLES11	= common_sub_elimination_v1
EXECUTABLES12	= common_sub_elimination_v2
EXECUTABLES13	= str_reduction_v1
EXECUTABLES14	= str_reduction_v3
EXECUTABLES15	= function_inlining_v2
EXECUTABLES16	= teliko

#This is the compiler to use
CC = icc

#These are the flags passed to the compiler. Change accordingly
CFLAGS = -Wall -fast

#These are the flags passed to the linker. Nothing in our case
LDFLAGS = -lm


# make all will create all executables
all: $(EXECUTABLES) $(EXECUTABLES1) $(EXECUTABLES2) $(EXECUTABLES3) $(EXECUTABLES4) $(EXECUTABLES5) $(EXECUTABLES6) $(EXECUTABLES7) $(EXECUTABLES8) $(EXECUTABLES9) $(EXECUTABLES10) $(EXECUTABLES11) $(EXECUTABLES12) $(EXECUTABLES13) $(EXECUTABLES14) $(EXECUTABLES15) $(EXECUTABLES16) $(EXECUTABLES17)
 

# This is the rule to create any executable from the corresponding .c 
# file with the same name.
%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

# make clean will remove all executables, jpg files and the 
# output of previous executions.
clean:
	rm -f $(EXECUTABLES) $(EXECUTABLES1) $(EXECUTABLES2) $(EXECUTABLES3) $(EXECUTABLES4) $(EXECUTABLES5) $(EXECUTABLES6) $(EXECUTABLES7) $(EXECUTABLES8) $(EXECUTABLES9) $(EXECUTABLES10) $(EXECUTABLES11) $(EXECUTABLES12) $(EXECUTABLES13) $(EXECUTABLES14) $(EXECUTABLES15) $(EXECUTABLES16) $(EXECUTABLES17) *.jpg output_sobel.grey

# make image will create the output_sobel.jpg from the output_sobel.grey. 
# Remember to change this rule if you change the name of the output file.
image: output_sobel.grey
	convert -depth 8 -size 4096x4096 GRAY:output_sobel.grey output_sobel.jpg 

