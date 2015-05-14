function [L,U,P,Q] = LU_pivot_total(A)
% Factorització LU d'una matriu quadrada A via eliminació
% Gaussina amb pivotatge total (element més gran)
% [IN] A una matriu nxn
% [OUT] L una matriu nxn triangular inferior amb 1s a la diagonal
% [OUT] U una matriu nxn triangular superior
% [OUT] P,Q matrius de permutació (ortonormal)
% LU = PAQ
    [n,n] = size(A);
    P = Q = eye(n);
    for k=1:n
        % pivotatge
        [pivots row] = max(abs(A(k:n,k:n))); %max per columnes
        [pivots col] = max(pivots); %max per max de columnes
        row = row(col)+k-1;
        col = col+k-1;
        if row ~= k % si cal pivotar files
            % canviar files en A
            temp = A(k,:);
            A(k,:) = A(row,:);
            A(row,:) = temp;
            % canviar files en P
            temp = P(k,:);
            P(k,:) = P(row,:);
            P(row,:) = temp;
        endif
        if col ~= k % si cal pivotar columnes
            % canviar columnes en A
            temp = A(:,col);
            A(:,col) = A(:,k);
            A(:,k) = temp;
            % canviar columnes en Q
            temp = Q(:,k);
            Q(:,k) = Q(:,col);
            Q(:,col) = temp;

        endif
        % descomposició
        A(k+1:n, k) = A(k+1:n,k)/A(k,k);
        A(k+1:n,k+1:n) = A(k+1:n,k+1:n) - A(k+1:n,k)*A(k,k+1:n);
    endfor
    % obté L, U de la matriu A
    L = tril(A,-1) + eye(n);
    U = triu(A);
endfunction
