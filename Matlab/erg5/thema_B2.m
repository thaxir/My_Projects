%thema_B2

clear all, clf;
ekf = '(x-1)*(x-2)*(x-5)'%'sin(x)'
p = extrema(ekf);

dp = eval(p)

domain = [min(dp)-1, 1+max(dp)];

ezplot(inline(ekf), domain); hold on
for i = 1:length(dp)
  plot(dp(i), feval(inline(ekf), dp(i)),'r*')
end
