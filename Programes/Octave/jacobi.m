% PER COMPROVAR EL RADI ESPECTRAL rho = max(abs(eig(B)));
function [x dx k] = jacobi(A,b,x0,tol,maxit)
    % Mètode iteratiu de Jacobi per resoldre Ax=b
    % [IN] A matriu amb diagonal != 0    nxn
    % [IN] b vector terme independent    nx1
    % [IN] x0 primera aproximació        nx1
    % [IN] tol tolerància en la solució  real
    % [IN] maxit màxim d'iteraciosn      enter
    % [OUT] x solució del sistema        nx1
    % [OUT] dx mesura de l'error         real
    % [OUT] k iteració on s'ha parat  enter
    % condició radi espectral de (D\(A-D)) < 1
    n = length(b);
    x = x0;
    for k = 1:maxit
        for r = 1:n
            x(r) = (b(r) - A(r, [1:r-1,r+1:n])*x0([1:r-1,r+1:n]))/A(r,r);
        endfor
        dx = abs(x - x0);
        err = norm(dx);
        relerr = err/(norm(x)+eps);
        x0 = x;
        if ((err < tol) || (relerr < tol)) break; endif
    endfor
endfunction

function [x dx k] = jacobi2(A,b,x0,tol,maxit)
    % Mètode iteratiu de Jacobi per resoldre Ax=b
    % [IN] A matriu amb diagonal != 0    nxn
    % [IN] b vector terme independent    nx1
    % [IN] x0 primera aproximació        nx1
    % [IN] tol tolerància en la solució  real
    % [IN] maxit màxim d'iteraciosn      enter
    % [OUT] x solució del sistema        nx1
    % [OUT] dx mesura de l'error         real
    % [OUT] k iteració on s'ha parat  enter
    % condició radi espectral de (D\(A-D)) < 1
    n = length(b);
    P = diag(diag(A));
    B = P\(A-P);
    c = P\b;
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
