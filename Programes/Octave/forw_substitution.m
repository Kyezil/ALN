function [X] = forw_substitution(L,B)
    % Resol un sistema triangular inferior amb substitució enrere LX=B
    % [IN] L és triangular superior nxn
    % [IN] B són els termes independents  nxk (k = # de sistemes)
    % [OUT] x és la solució del sistema
    [n,n] = size(L);
    [n,k] = size(B);
    X = zeros(n,k);
    X(1,:) = B(1,:)/L(1,1);
    for i=2:n
        if (L(i,i) == 0) error('Matriu singular!'); end;
        X(i,:) = (B(i,:) - L(i,1:i-1)*X(1:i-1,:))/L(i,i);
    endfor
endfunction
