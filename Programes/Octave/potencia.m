function [vap,vep] = potencia0(A, z0, tol)
    % Mètode de la potència per calcular vap dominant v0
    % [IN] A matriu nxn amb vap dominant > 2n vap dominant
    % [IN] z0 vector inicial (z0)_0 != 0 nx1
    % [IN] tol tolerància en la solució  real
    % [OUT] vap valor propi dominant real
    % [OUT] vec vector propi de vap el valor propi dominant nx1
    n = size(A,1);
    z = vap = zeros(n,1);
    do
        vap_ant = vap;
        z = A*z0;
        vap = z ./ z0;
        z0 = z;
    until (norm(vap-vap_ant,Inf) <= tol)
    vep = z/norm(z);
    vap = mean(vap);
endfunction

function [vap,vep] = potencia1(A, z0, tol)
    % Mètode de la potència per calcular vap dominant v1
    % [IN] A matriu nxn amb vap dominant > 2n vap dominant
    % [IN] z0 vector inicial (z0)_0 != 0 nx1
    % [IN] tol tolerància en la solució  real
    % [OUT] vap valor propi dominant
    % [OUT] vec vector propi de vap el valor propi dominant nx1
    n = size(A,1);
    z = ones(n,1);
    vap = zeros(n,1);
    do
        vap_ant = vap;
        y = z/norm(z);
        z = A*y;
        vap = z ./ y;
    until (norm(vap-vap_ant,Inf) <= tol)
    vep = z/norm(z);
    vap = mean(vap);
endfunction

function [vap,vep] = potencia_rayleigh(A, z0, tol)
    % Mètode de la potència per calcular vap dominant amb coef de Rayleigh
    % [IN] A matriu simètrica nxn amb vap dominant > 2n vap dominant
    % [IN] z0 vector inicial (z0)_0 != 0 nx1
    % [IN] tol tolerància en la solució  real
    % [OUT] vap valor propi dominant
    % [OUT] vec vector propi de vap el valor propi dominant nx1
    n = size(A,1);
    z = ones(n,1);
    vap = 0;
    do
        vap_ant = vap;
        y = z/norm(z); %k
        z = A*y; %k+1
        vap = y'*z;
    until (norm(vap-vap_ant,Inf) <= tol)
    vep = z/norm(z);
endfunction
