fileID = fopen('C:\Users\lab\Documents\Visual Studio 2015\Projects\Akwizycja\Akwizycja\bin\Debug\test.txt','r');
formatSpec = '%f';
A = fscanf(fileID,formatSpec);
fclose(fileID);
plot(A);
axis([1 100 1.35 1.45]);
ylabel('[V]');
xlabel('[sample]');

