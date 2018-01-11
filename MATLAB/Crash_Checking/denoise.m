function filtered = denoise(unfiltered)
    rho = 10;
    mu = 0.5;
 
    l = length(unfiltered);
    
    filtered = zeros(l,1);
    u = zeros(l,1);
    y = zeros(l,1);
    
    eigD = abs(fftn([-1;1],[l 1])).^2;

    for k = 1 : 100
        filtered = real(ifft(fft(mu * unfiltered + rho * Dt(u) - Dt(y)) ./ (mu + rho * eigD)));
        v = D(filtered) + (1/rho) * y;
        u = max(abs(v) - 1/rho, 0) .* sign(v);
        y = y - rho * (u - D(filtered));
    end

%     figure;
%     plot(unfiltered);
%     axis([1 l min(min(unfiltered),min(filtered)) max(max(unfiltered),max(filtered))]);
%     title('Filter');
%     hold on
%     plot(filtered,'r');
end

function y = D(x)
    y = [diff(x); x(1)-x(end)];
end

function y = Dt(x)
    y = [x(end)-x(1); -diff(x)];
end