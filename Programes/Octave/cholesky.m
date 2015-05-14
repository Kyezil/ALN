function [L] = cholesky(A)
    % Factorització de Cholesky per matrius simètriques definides positives
    % [IN] A una matriu nxn simètrica definida positiva
    % [OUT] L una matriu triangular inferior nxn
    % LL' = A
    [n n] = size(A);
    for k = 1:n
        A(k,k) = sqrt(A(k,k));
        A(k+1:n,k) = A(k+1:n,k)/A(k,k);
        for j = k+1:n
            A(j:n, j) = A(j:n, j)-A(j,k)*A(j:n,k);
        endfor
    endfor
    L = tril(A);
endfunction
