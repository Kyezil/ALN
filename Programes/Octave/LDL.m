function [L,D] = LDL(A)
% Decomposició LDL' per matrius simètriques
% [IN] A una matriu simètrica nxn
% [OUT] L matriu triangular inferior nxn amb 1 a la diagonal
% [OUT] D una matriu diagonal
% LDL' = A
    [n,n] = size(A);
    for k = 1:n
        for r = 1:k-1
            A(k,k) -= A(k,r)^2*A(r,r);
        endfor
        for i = k+1:n
            for r = 1:k-1
                A(i,k) -= A(i,r)*A(r,r)*A(k,r);
            endfor
            A(i,k) /= A(k,k);
        endfor
    endfor
    L = tril(A,-1) + eye(n);
    D = diag(diag(A));
endfunction
