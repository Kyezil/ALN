% PER COMPROVAR EL RADI ESPECTRAL rho = max(abs(eig(B)));
function [x dx k] = SOR(A,b,x0,w,tol,maxit)
    % Mètode iteratiu de sobrerelaxació per resoldre Ax=b
    % [IN] A matriu amb diagonal != 0    nxn
    % [IN] b vector terme independent    nx1
    % [IN] x0 primera aproximació        nx1
    % [IN] w paramètre de sobrerelaxació real
    % [IN] tol tolerància en la solució  real
    % [IN] maxit màxim d'iteraciosn      enter
    % [OUT] x solució del sistema        nx1
    % [OUT] dx mesura de l'error         real
    % [OUT] k iteració on s'ha parat  enter
    % P = 1/w(D + wL) i B = inv(D + wL) rho(B) < 1
    n = length(b);
    x = x0;
    for k = 1:maxit
        for i = 1:n
            x(i) += w*((b(i) - A(i,1:n)*x(1:n))/A(i,i));
        endfor
        dx = abs(x - x0);
        err = norm(dx);
        relerr = err/(norm(x)+eps);
        x0 = x;
        if ((err < tol) || (relerr < tol)) break; endif
    endfor
endfunction

function [x dx k] = SOR2(A,b,x0,w,tol,maxit)
    % Mètode iteratiu de sobrerelaxació per resoldre Ax=b
    % [IN] A matriu amb diagonal != 0    nxn
    % [IN] b vector terme independent    nx1
    % [IN] x0 primera aproximació        nx1
    % [IN] w paramètre de sobrerelaxació real
    % [IN] tol tolerància en la solució  real
    % [IN] maxit màxim d'iteraciosn      enter
    % [OUT] x solució del sistema        nx1
    % [OUT] dx mesura de l'error         real
    % [OUT] k iteració on s'ha parat  enter
    % P = 1/w(D + wL) i B = inv(D + wL) rho(B) < 1
    n = length(b);
    D = diag(diag(A));
    L = tril(A);
    U = triu(A);
    B = (D+w*L)\((1-w)*D - w*U);
    % optimal w śi A és tridiagonal per blocs
    % w = 2/(1+sqrt(1-max(abs(eig(B))^2)));
    c = w*(D+w*L)\b;
    x = x0;
    for k = 1:maxit
        x = B*x0 + c;
        dx = abs(x - x0);
        err = norm(dx);
        relerr = err/(norm(x)+eps);
        x0 = x;
        if ((err < tol) || (relerr < tol)) break; endif
    endfor
endfunction
