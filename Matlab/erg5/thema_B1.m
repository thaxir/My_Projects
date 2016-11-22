%thema_B1

clear all, clf;
fun=inline('sin(2*x)-x^2+1')

ezplot(fun, [0, 2]); hold on

xn = 0, xnp1 = 1
fxn = fun(xn), fxnp1 = fun(xnp1)

plot(xn, fxn, xnp1, fxnp1, 'g*') 

error = 100
while error > 1e-5
   xnp2 = xnp1 - fxnp1*(xnp1-xn)/(fxnp1-fxn)
   fxnp2 = fun(xnp2)
   
   error = abs(xnp2-xnp1);
   
   xn = xnp1;
   fxn = fxnp1;
   xnp1 = xnp2;
   fxnp1= fxnp2;
   
   plot(xnp2, fxnp2, 'g*')
    
end
