fileID = fopen('C:\Users\lab\Documents\Visual Studio 2015\Projects\Akwizycja\Akwizycja\bin\Debug\test2.txt','r');
formatSpec = '%f';
A = fscanf(fileID,formatSpec);
fclose(fileID);
plot(A);
axis([1 5 1.35 1.45]);
ylabel('[V]');
xlabel('[sample]');

