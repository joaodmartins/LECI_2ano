plot(n3, r3)

N = [n3 0*n3+1];

C = pinv(N)*r3;

r3_est = N*C;
figure; plot(n3,r3, n3, r3_est, 'r:')