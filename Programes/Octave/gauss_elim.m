function [x] = gauss_elim(A, B)
    % Es pot eliminació gaussiana sense pivotatge:
    %   <=> els determinants principals són != 0
    % Per resoldre AX = B
    [n,n] = size(A);
    [n,k] = size(B);
    x = zeros(n,k);
    for i=1:n-1
        if (A(i,i) == 0) error('Pivot nul!'); end;
        m = -A(i+1:n,i)/A(i,i);
        A(i+1:n,:) = A(i+1:n,:) + m*A(i,:);
        B(i+1:n,:) = B(i+1:n,:) + m*B(i,:);
    endfor

    % substitució enrere
    x = back_substitution(A,B);
endfunction
