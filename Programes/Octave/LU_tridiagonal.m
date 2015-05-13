function [L,U] = LU_tridiagonal(A)
% Descomposició LU d'una matriu tridiagonal
% [IN] A una matriu tridiagonal quadrada nxn
% [OUT] L una matriu bidiagonal inferior amb 1s a la diagonal principal
% [OUT] U una matriu bidiagonal superior
% LU = A   2n mult i n sumes
    [n n] = size(A);
    a = diag(A,-1); % l
    b = diag(A); % v
    c = diag(A,1); % c
    % v1 = b1;
    for k = 2:n
        a(k-1) = a(k-1) / b(k-1);
        b(k) = b(k) - a(k-1)*c(k-1);
    endfor
    L = eye(n) + diag(a, -1);
    U = diag(b) + diag(c,1);
endfunction

function [X] = solve_tridiagonal(L,U, B)
% Resol un sistema Ax = b donada la descomposició LU de A tridiagonal
% [IN] L una matriu bidiagonal inferior amb 1s a la diagonal
% [IN] U una matriu bidiagonal superior
% [IN] B terme independent del sistema
% [OUT] X solució del sistema
    [n m] = size(B);
    % Ly = b es pot guardar tot sobre b
    l = diag(L,-1);
    X = zeros(n,m);
    X(1,:) = B(1,:);
    for k = 2:n
        X(k,:) = B(k,:) - l(k-1).*X(k-1,:);
    endfor

    % Ux = y
    v = diag(U);
    c = diag(U,1);
    disp(n);
    X(n,:) = X(n,:) / v(n,:);
    for k = n-1:-1:1
        X(k,:) = (X(k,:) - c(k).*X(k+1,:))/v(k,:);
    endfor
endfunction
