function  myinterp( n )
n = 100;
x = linspace(0, 2*pi, n);
y = cos(x);
ezplot('cos(x)',[0, 2*pi]);
hold on 
for ii = 1:n-1
 lx =[x(ii) x(ii+1)];
 ly = cos(lx);
 
 logy = log(ly);
 synt = polyfit(lx, logy, 1);

 a = exp(synt(2))
 b = synt(1)
 xplot = linspace(x(ii), x(ii+1), 100);
 yplot = a*exp(b*xplot);
 plot(xplot, yplot, '*r')  
end

end

