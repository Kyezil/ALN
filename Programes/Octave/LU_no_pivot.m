function [L,A] = LU_no_pivot(A)
% Factorització LU d'una matriu quadrada A via eliminació
% Gaussiana sense pivotatge
% [IN] A una matriu nxn
% [OUT] L una matriu nxn triangular inferior amb 1s a la diagonal
% [OUT] U una matriu nxn triangular superior
% LU = A
    [n,n] = size(A);
    L = eye(n);
    for k=1:n
        if (A(k,k) == 0) error('Cal pivotar!'); end;
        L(k+1:n, k) = A(k+1:n,k)/A(k,k);
        A(k+1:n,:) = A(k+1:n,:) - L(k+1:n,k)*A(k,:);
    endfor
endfunction
