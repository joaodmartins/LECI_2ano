%% n = 12
fileID = fopen('dados_12.txt','r');
formatSpec = '%d %d';
sizeA = [2 Inf];
A = fscanf(fileID,formatSpec,sizeA);
B = A(1,:);
C = A(2,:);
subplot(2,1,1)
histogram('BinEdges',[0 B(1:20:end)],'BinCounts',C(1:20:end));
%bar(B,C,1,'b');
axis([0 5000 0 5e4]);
xticks(0:500:4500);
yticks(0:1e4:5e4);
title('Distribuicao dos tamanhos das tours para n = 12');
xlabel('Tamanho');
ylabel('Numero de tours');
fclose(fileID);

%% n = 15
%{
fileID = fopen('dados_15.txt','r');
formatSpec = '%d %d';
sizeA = [2 Inf];
A = fscanf(fileID,formatSpec,sizeA);
B = A(1,:);
C = A(2,:);
subplot(2,1,2)
bar(B,C,1,'b');
axis([0 6500 0 7e4]);
xticks(0:1000:6000);
yticks(0:1e4:7e4);
title('Distribuicao dos tamanhos das tours para n = 15');
xlabel('Tamanho');
ylabel('Numero de tours');
fclose('dados_15.txt');
%}

%% RANDOM
%% n = 12
%{
fileID = fopen('dados_rand_12.txt','r');
formatSpec = '%d %d';
sizeA = [2 Inf];
A = fscanf(fileID,formatSpec,sizeA);
B = A(1,:);
C = A(2,:);
subplot(2,1,2)
bar(B,C,1,'b');
axis([0 5000 0 5e4]);
xticks(0:500:4500);
yticks(0:1e4:5e4);
title('Distribuicao dos tamanhos das tours para n = 12');
xlabel('Tamanho');
ylabel('Numero de tours');
fclose('dados_rand_12.txt');
%}

%% n = 15
%{
fileID = fopen('dados_rand_15.txt','r');
formatSpec = '%d %d';
sizeA = [2 Inf];
A = fscanf(fileID,formatSpec,sizeA);
B = A(1,:);
C = A(2,:);
subplot(2,1,2)
bar(B,C,1,'b');
axis([0 6500 0 7e4]);
xticks(0:1000:6000);
yticks(0:1e4:7e4);
title('Distribuicao dos tamanhos das tours para n = 15');
xlabel('Tamanho');
ylabel('Numero de tours');
fclose('dados_rand_15.txt');
%}

%% n = 18
%{
fileID = fopen('dados_rand_18.txt','r');
formatSpec = '%d %d';
sizeA = [2 Inf];
A = fscanf(fileID,formatSpec,sizeA);
B = A(1,:);
C = A(2,:);
subplot(2,1,2)
bar(B,C,1,'b');
axis([0 7500 0 7e4]);
xticks(0:1000:7000);
yticks(0:1e4:7e4);
title('Distribuicao dos tamanhos das tours para n = 18');
xlabel('Tamanho');
ylabel('Numero de tours');
fclose('dados_rand_18.txt');
%}