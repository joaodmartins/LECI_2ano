A = load("results.txt");

N = A(:,1);
V = A(:,2)
Fib = A(:,3);
T = A(:,4);

N1 = N(V==1);
T1 = T(V==1);

N2 = N(V==2);
T2 = T(V==2);

N3 = N(V==3);
T3 = T(V==3);

N4 = N(V==4);
T4 = T(V==4);

plot(N1,T1);
hold on
plot(N2,T2);
plot(N3,T3);
plot(N4,T4);


xlabel("N");
ylabel("t");
semilogy(N1,T1);