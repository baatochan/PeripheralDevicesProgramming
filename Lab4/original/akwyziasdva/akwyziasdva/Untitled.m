fileID = fopen('C:\Users\lab\Documents\data.txt','r');
formatSpec = '%f';
A = fscanf(fileID,formatSpec);
fclose(fileID);
plot(A);
axis([1 100 -4 4]);
ylabel('[V]');
xlabel('[nr probki]');

