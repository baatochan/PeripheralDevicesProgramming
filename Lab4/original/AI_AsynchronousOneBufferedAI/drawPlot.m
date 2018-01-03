load matlabSignal.txt

[n,p] = size(matlabSignal);

t = 1:n;
t = t/n;

plot(t,matlabSignal), 
xlabel('Czas[s]'), ylabel('Napiecie[V]')
title('Przebieg sygnalu')