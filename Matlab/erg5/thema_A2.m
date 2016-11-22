%thema_A2

clear all, clf;
fun=inline('exp((2-x)^2)')
dfun = inline(diff(sym('exp((2-x)^2)')))
d2fun = inline(diff(diff(sym('exp((2-x)^2)'))))

ezplot(fun, [0, 4]); hold on

xold = 0
fxold = dfun(xold)
 
error = 100
while error > 1e-5
   xnew = xold - fxold/d2fun(xold)
   fxnew = dfun(xnew)
   error = abs(xnew-xold);
   
   xold = xnew;
   fxold = fxnew;
   plot(xold, fun(xold), 'm*')
    
end

