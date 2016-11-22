clear all
clc

% Declare the number of the bits you wish to transmit , Set 60000 for 64-QAM
%bits = 100000;

% Declare the range of Signal to Noise Ratio (SNR)
%SNR = 1:1:10;

% Energy/bit
Eb = 1;
mean = 0;
% var(aX) = a^2var(X)
var = 1/sqrt(2);

% Number of bits the channel remains stable
% T = 10;
% Q = bits/T;

%Give modulation scheme
M=input('Enter the modulation type[1 for BPSK,2 for QPSK,8 for 8-PSK]: ');

%Give as input the SNR
SNR = input('enter SNR values between square bracket, like [1 2 3] ');


%Give as input the # of bits
bits = input('Put number of bits? ');


if M==8  %in case 8PSK
      %kanw ta bits pollaplasio to 3 gia na parei se periptwsh pou dn diaireitai 
       bits=bits+rem((3-rem(bits,3)),3);
end


for n = 1:length(SNR)
  % Create the AWGN - Convert in Db -- /bits/2 -> QPSK , bits/4 -> 16-QAM , bits/6 -> 64-QAM
  noise = var*10^(-SNR(n)/20)*[randn(1,bits) + j*randn(1,bits)] + mean;
    
  switch M   
        
    case 1
            % AWGN case
            for i = 1:bits
                if rand < 0.5
                    s(i) = 1;
                    % The received signal
                    y(i) = Eb*s(i) + noise(i);
                else
                    s(i) = -1;
                    % The received signal
                    y(i) = Eb*s(i) + noise(i);
                end
            end


            Error = 0 ;

            %Decision device taking hard decision and deciding error
            for k=1:bits                 
                     if ((y(k)>0 && s(k)==0)||(y(k)<0 && s(k)==1))
                         Error=Error+1;
                     end
            end

            Error=Error/bits;             %Calculate error/bit
            m(n)=Error;
            
            % Constellations
            scatterplot(y);
        
       case 2  %QPSK #################################
            si=2*(round(rand(1,bits))-0.5);                      %In-phase symbol generation
            sq=2*(round(rand(1,bits))-0.5);                      %Quadrature symbol generation                
            s=si+j*sq;                                        %Adding the two parallel symbol streams
            r=s+noise;                                          %Received signal
            si_=sign(real(r));                                %In-phase demodulation
            sq_=sign(imag(r));                                %Quadrature demodulation
            ber1=(bits - sum(si==si_))/ bits;                          
            ber2=(bits - sum(sq==sq_))/ bits;                      
            ber(n)= (ber1 + ber2)/2;                         %Overall BER
            
            scatterplot(r);
            
            
       case 8        % 8PSK #################################################
           
            %Constellation Mapper
           map=[1.414 0.707;0.707 1.414;-0.707 1.414;-1.414 0.707;-1.414 -0.707;-0.707 -1.414;0.707 -1.414;1.414 -0.707];
  
           Error=0;
             
           x=rand(1,bits)>=0.5;
           
           %kanw 3s sthles kai gray code
            x1=reshape(x,3,bits/3)';
            %g=bin2gray(x1,'psk',8);
            
            b=bin2dec(num2str(x1,'%-1d'))';
            
            s=map(b(:)+1,1)+j*map(b(:)+1,2);
            n1=noise(1:3:end);  %den  vrika kalytero tropo na kanw tous pinakes s kai n isous :/
            s=s+n1(:);
            
        
            scatterplot(s);
    end
    
    
   

  
end

if M == 1
    semilogy(SNR, m, 'r','linewidth',2),grid on,hold on;
    BER=(1/2)*erfc(sqrt(SNR));
    semilogy(SNR,BER,'k','linewidth',2);
    xlabel('SNR (dB)')
    ylabel('BER')
    legend('simulation','theoretical')
elseif M ==2
    semilogy(SNR, ber,'o-')                      
    xlabel('SNR (dB)')
    ylabel('BER')   
    grid on 
else
   BER = berawgn(SNR, 'psk', 8, 'nondiff');
   semilogy(SNR, BER,'o-')                      
    xlabel('SNR (dB)')
    ylabel('BER')   
    grid on 
end

