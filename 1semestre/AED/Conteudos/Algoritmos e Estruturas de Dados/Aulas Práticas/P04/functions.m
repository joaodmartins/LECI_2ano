A = load("data1.txt");
figure
F=1;plot(A(F:6:end,1),A(F:6:end,3))
hold on
F=2;plot(A(F:6:end,1),A(F:6:end,3),'r-+')
F=3;plot(A(F:6:end,1),A(F:6:end,3),'g-*')
F=4;plot(A(F:6:end,1),A(F:6:end,3),'c-o')
F=5;plot(A(F:6:end,1),A(F:6:end,3),'k:')
F=6;plot(A(F:6:end,1),A(F:6:end,3),'y-^')
legend('f1','f2','f3','f4','f5','f6')
title('Valor função')

% Tempos
figure 
F=1;plot(A(F:6:end,1),A(F:6:end,4))
hold on
F=2;plot(A(F:6:end,1),A(F:6:end,4),'r-+')
F=3;plot(A(F:6:end,1),A(F:6:end,4),'g-*')
F=4;plot(A(F:6:end,1),A(F:6:end,4),'c-o')
F=5;plot(A(F:6:end,1),A(F:6:end,4),'k:')
F=6;plot(A(F:6:end,1),A(F:6:end,4),'y-^')
legend('f1','f2','f3','f4','f5','f6')
title('Valor função')

% Tempos logscale
figure 
F=1;loglog(A(F:6:end,1),A(F:6:end,4))
hold on
F=2;loglog(A(F:6:end,1),A(F:6:end,4),'r-+')
F=3;loglog(A(F:6:end,1),A(F:6:end,4),'g-*')
F=4;loglog(A(F:6:end,1),A(F:6:end,4),'c-o')
F=5;loglog(A(F:6:end,1),A(F:6:end,4),'k:')
F=6;loglog(A(F:6:end,1),A(F:6:end,4),'y-^')
legend('f1','f2','f3','f4','f5','f6')
title('Valor função')


