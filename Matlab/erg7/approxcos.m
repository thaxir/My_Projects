function error = approxcos( n, k )

x = linspace(0, 2*pi, n);
y = cos(x);

pp = polyfit(x,y,k);
pv = polyval(pp, x);

error = norm(y-pv, 1)

ezplot('cos(x)',[0, 2*pi]);
hold on 
xx = linspace(0, 2*pi, 1000);
yy = polyval(pp,xx);
plot(xx,yy, 'r')
hold off

end

