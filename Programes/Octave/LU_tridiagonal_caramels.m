function [L,U] = LU_tridiagonal_caramels(A)
% Descomposició LU d'una matriu tridiagonal amb caramels
% [IN] A una matriu tridiagonal quadrada nxn amb caramels als extrems de
%        la diagonal secundaria
% [OUT] L una matriu bidiagonal inferior amb 1s a la diagonal principal
%        i la última fila plena
% [OUT] U una matriu bidiagonal superior amb la última columna plena
% LU = A  n >= 3
    [n n] = size(A);
    a = diag(A); % alpha
    b = diag(A,-1); % beta
    c = diag(A,1);
    d = zeros(1,n-1);
    e = zeros(n-1,1);
    % alpha(1) = a(1);
    d(1) = A(end,1)/a(1);
    e(1) = A(1,end);
    for j = 2:n-2
        b(j-1) /= a(j-1);
        a(j) -= b(j-1)*c(j-1);
        d(j) = -d(j-1)*c(j-1)/a(j);
        e(j) = -b(j-1)*e(j-1);
    endfor
    b(n-2) /= a(n-2);
    a(n-1) -= b(n-2)*c(n-2);
    d(n-1) = (b(n-1)-d(n-2)*c(n-2))/a(n-1);
    e(n-1) = c(n-1) - b(n-2)*e(n-2);
    a(n) -= d*e;
    L = eye(n) + diag(b, -1);
    L(n,1:n-1) = d;
    U = diag(a) + diag(c,1);
    U(1:n-1,end) = e;
endfunction

function [X] = solve_tridiagonal_caramels(L,U,B)
% Resol un sistema AX = B donada la descomposició LU de A tridiagonal caramels
% [IN] L una matriu bidiagonal inferior amb 1s a la diagonal i última fila
% [IN] U una matriu bidiagonal superior amb última columna
% [IN] B terme independent del sistema
% [OUT] X solució del sistema
    [n m] = size(B);
    b = diag(L,-1)(1:end-1);
    d = L(end,1:end-1);
    X = zeros(n,m);
    % LX = B
    X(1,:) = B(1,:);
    for k = 2:n-1
        X(k,:) = B(k,:) - b(k-1).*X(k-1,:);
    endfor
    X(n,:) = B(n,:) - d*X(1:end-1,:);
    disp(X);
    % UX = Y
    a = diag(U);
    c = diag(U,1)(1:end-1);
    e = U(1:end-1,end);
    X(n,:) = X(n,:)/a(n);
    X(n-1,:) = (X(n-1,:) - e(n-1)*X(n,:))/a(n-1);
    for k = n-2:-1:1
        X(k,:) = (X(k,:) - c(k)*X(k+1,:) - e(k)*X(n,:))/a(k);
    endfor
endfunction
