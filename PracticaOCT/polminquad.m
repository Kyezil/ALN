1;
function take_the_tour(x,y)
    figure;
    min = norm(x,-Inf);
    max = norm(x,Inf);
    sep = abs(max - min);
    axis([min - 0.1*sep, max + 0.1*sep]);
    X = linspace(min,max);
    n = length(x);
    for m = 0:n-1
        plot(x,y,'@'); % els punts
        p = polminquad(x,y,m);
        hold on;
        Ym = polyval(fliplr(p),X);
        plot(X, Ym, 'r');
        if m > 0
            plot(X, Y', ':r');
        endif
        Y = Ym';
        wait = input("Press Enter...");
        hold off;
    endfor
endfunction

function [coeff, norm2_res] = polminquad(x,y,m)
    n = length(x);
    m = m+1; % dimensió 0 és 1 equació
    if (1 <= m && m <= n)
        % Volem trobar p de grau m tal que p(xi) = yi (millor)
        % Imposem-ho com Aa = y  | a els coeff del polinomi
        A = fliplr(vander(x .* ones(1,n)))(:,1:m); % A is NxM
        [Q,R] = decompQR_GS(A);
        % resolució del sistema
        coeff = (R\(Q'*y'))';
        norm2_res = norm(A*coeff' - y');
    else
        disp("m fora de rang");
    endif
endfunction

function [Q,R] = decompQR_GS(A)
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
    normaQ = norm(Q'*Q - eye(n), Inf);
    fprintf("||QtQ - Id||inf = %e\n", normaQ);
endfunction
