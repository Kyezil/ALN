function [L,U,P] = LU_pivot_parcial_esglaonat(A)
% Factorització LU d'una matriu quadrada A via eliminació
% Gaussina amb pivotatge parcial esglaonat per files (max respecte els altres)
% [IN] A una matriu nxn
% [OUT] L una matriu nxn triangular inferior amb 1s a la diagonal
% [OUT] U una matriu nxn triangular superior
% [OUT] P matriu de permutació (ortonormal)
% LU = PA
    [n,n] = size(A);
    P = eye(n);
    for k=1:n
        % pivotatge
        [pivot m] = max(abs(A(k:n,k)') ./ max(abs(A(k:n,k:n)'))); %troba pivot
        m = m+k-1; % arregla l'offset
        if m ~= k % si cal pivotar
            % canviar files en A
            temp = A(k,:);
            A(k,:) = A(m,:);
            A(m,:) = temp;
            % canviar files en P
            temp = P(k,:);
            P(k,:) = P(m,:);
            P(m,:) = temp;
        endif
        % descomposició
        A(k+1:n, k) = A(k+1:n,k)/A(k,k);
        A(k+1:n,k+1:n) = A(k+1:n,k+1:n) - A(k+1:n,k)*A(k,k+1:n);
    endfor
    % obté L, U de la matriu A
    L = tril(A,-1) + eye(n);
    U = triu(A);
endfunction
