function [X] = back_substitution(U,B)
    % Resol un sistema triangular superior amb substitució enrere UX=B
    % [IN] U és triangular superior nxn
    % [IN] B són els termes independents  nxk (k = # de sistemes)
    % [OUT] x és la solució del sistema
    [n,n] = size(U);
    [n,k] = size(B);
    X = zeros(n,k);
    X(n,:) = B(n,:)/U(n,n);
    for i=n-1:-1:1
        if (U(i,i) == 0) error('Matriu singular!'); end;
        X(i,:) = (B(i,:) - U(i,i+1:n)*X(i+1:n,:))/U(i,i);
    endfor
endfunction
