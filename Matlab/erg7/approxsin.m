function error = approxsin( n, k )

x = pi*(cos(((2*[1:n]-1)/(2*(n)))*pi)+1);
y = cos(x);

pp = polyfit(x,y,k);
pv = polyval(pp, x);

error = norm(y-pv, 2)

ezplot('cos(x)',[0, 2*pi]);
hold on 
xx = linspace(0, 2*pi, 1000);
yy = polyval(pp,xx);
plot(xx,yy, 'r')
hold off

end

