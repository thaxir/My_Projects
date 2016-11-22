function [ iter , lim ] =  syn1_B2( a )


xlabel ('n')
ylabel ('a_{n+1} = 1+ 1/a_n')
title ('OMADA B2','FontSize',14)

aold = a;
anew = 1+ 1/aold;
iter = 1;
plot([0 1], [aold anew],'*r'); hold on;
while (abs(anew-aold) > 1e-5)
    aold = anew;
    anew = 1+ 1/aold;
    iter = iter+1;
    plot([iter], [anew],'*g')
end

lim = anew;

