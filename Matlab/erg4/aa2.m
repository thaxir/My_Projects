diary atksirof.txt
diary on
clc;clear  all;

x = [1  2];

y = fun1_B1(x);

plot([0, 1],[0,2],'b', [0 y(1)], [0, y(2)],'r')
title('OMADA B1','FontSize',14);
xlabel('x axonas');
ylabel('y axonas');
