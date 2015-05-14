function [Q,R] = QR_GS(A)
% Descomposició QR per procés Gram-Schmidt
% [IN] A matriu mxn amb m >= n
% [OUT] Q matriu mxn ortogonal
% [OUT] R matriu nxn triangular superior
    [m,n] = size(A);
    Q = zeros(m,n);
    R = zeros(n);
    for j = 1:n
        R(j,j) = norm(A(:,j));
        Q(:,j) = A(:,j) / R(j,j); % normalitza
        R(j,j+1:n) = Q(:,j)'*A(:,j+1:n);
        A(:,j+1:n) = A(:,j+1:n) - Q(:,j)*R(j,j+1:n);
    endfor
    % comprovació Q'Q = Id
%    normaQ = norm(Q'*Q - eye(n), Inf);
%    fprintf("||QtQ - Id||inf = %e\n", normaQ);
endfunction
