%thema_A1

clear all, clf;
ekf = 'exp(2*x)'%'sin(x)'
n = 4
domain = [-1, 1];

derivatives = der(ekf, n);

ezplot(inline(ekf), domain); hold on
xplot= domain(1):(domain(2)-domain(1))/100:domain(2);

for i = 1:n
   plot (xplot, feval(inline(derivatives(i)), xplot),'r-','LineWidth',2*i)
end

