load matlabSignal.txt

[n,p] = size(matlabSignal);

t = 1:n;
t = t/n;

figure(1)
plot(t,matlabSignal), 
xlabel('Czas[s]'), ylabel('Napiecie[V]')
title('Przebieg sygnalu sinus')

load matlabSignal1012322637.txt

[n1,p1] = size(matlabSignal1012322637);

t1 = 1:n1;
t1 = t1/n1;

figure(2)
plot(t1,matlabSignal1012322637), 
xlabel('Czas[s]'), ylabel('Napiecie[V]')
title('Przebieg sygnalu trojkat')

load matlabSignal299323962.txt

[n1,p1] = size(matlabSignal299323962);

t1 = 1:n1;
t1 = t1/n1;

figure(3)
plot(t1,matlabSignal299323962), 
xlabel('Czas[s]'), ylabel('Napiecie[V]')
title('Przebieg sygnalu prostokat')