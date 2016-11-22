diary atksirof
diary on
clc;
clear;
clf;


n = 100;
x = 0:0.1:2*pi;

for i = 1:length(x)
    y(i) = fun1(n, x(i));
end

plot(x, y, 'r');
title('Askhsh A1');
ylabel('sinx taylor');
xlabel('x');
diary off
