diary atksirof.txt
diary on
clear all;
clc;

a = 1;
b = -1e8;
c = 1;

[a1 a2] =  syn1(a, b, c);

x = [-10: 0.1: 10];
y = a*x.*x+b*x+c;

plot(x , y , 'r');
title('parabolh');
xlabel('x');
ylabel('ax2+bx+c=0');
title('A2 askhsh');


