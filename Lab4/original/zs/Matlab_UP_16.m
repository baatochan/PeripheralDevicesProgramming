

fileID = fopen('C:\Users\lab\Desktop\zs\WindowsFormsApplication4\WindowsFormsApplication4\bin\Debuglapszo.txt','r');
formatSpec = '%f';
A = fscanf(fileID,formatSpec);
fclose(fileID);
%axis([0 100*32 -5 5]); %100 * 1024 - czas * probki
t= 1:1:2048;
figure(1);
plot(A);
ylabel('Amplituda');
xlabel('Czas [ms]');

