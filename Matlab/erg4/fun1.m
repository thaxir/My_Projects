function [ a ] = fun1( n, x )

a = 0;
l = 0;
for k = 1:2:n
    if mod(l, 2) == 0
        a = a + ((x ^ k) / factorial(k));
        l = l + 1;
    elseif ( mod(l, 2))
        a = a - ((x ^ k) / factorial(k));
        l = l + 1;
    end
        
        
        



end

