function  myfun(n )
n = 10;
t = linspace(0, 2*pi, n);
x = (sin(t)).^3;
y = (cos(t)).^3;

shmeia = [0 x 0 ; 0 y 0];
nn= size(shmeia,2);
pp=spline(t , shmeia);
yy=ppval(pp,linspace(0,2*pi,1001));
plot(yy(2,:),yy(2,:), '-b', x,y,'*r')

end

