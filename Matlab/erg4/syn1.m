function [ r1 r2 ] = syn1( a, b, c )

diakr = sqrt(b ^ 2 - 4 * a * c);
 r1 = (-b + diakr) / (2 * a);
 r2 = (-b - diakr) / (2 * a);



end

