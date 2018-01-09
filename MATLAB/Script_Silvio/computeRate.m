function [AV, MAX, MIN] = computeRate(filename)
    % [var, d] = readFile('../server/log/log_2018-01-06_18-35-50.csv');
    unfilled = readFile(filename);
    
    unfilled(:,3) = denoise(unfilled(:,3));
    unfilled(:,4) = denoise(unfilled(:,4));
    unfilled(:,5) = denoise(unfilled(:,5));
    
    var = filler(unfilled);
    
    figure;
    plot(var(:,3));
    title('Questo');
    
    % t = filled(:,1)./1000;
    % unfiltered = filled(:,3);
    % filtered = mlptdenoise(unfiltered, t); 
    % plot(t,filtered)
    % hold on
    % plot(t,unfiltered)
    % legend('Original','Corrupted')
    %figure;
    %plot(filled(:,3));
    
    % var = filled;
    
     %fft(filled());
     
%     Fs = 50;            % Sampling frequency                    
%     T = 1/Fs;             % Sampling period       
%     L = 1500;             % Length of signal
%      
%     Y = fft(filled(:,3));
%     
%     P2 = abs(Y/L);
%     P1 = P2(1:L/2+1);
%     P1(2:end-1) = 2*P1(2:end-1);
%     
%     f = Fs*(0:(L/2))/L;
%     plot(f,P1) 
%     title('Single-Sided Amplitude Spectrum of X(t)')
%     xlabel('f (Hz)')
%     ylabel('|P1(f)|')
    
    % var = denoise(filled(:,3));
    %var = filterData(filled);
    %figure;
    %plot(var(:,3));
    
    % vel = iomega(var, 0.02, 3, 2);
    
    % figure;
    % plot(vel);

    diff = zeros(size(var,1), 1);
    counter = 0;

    for i = 2 : size(var,1)
        if(var(i,2) - var(i-1,2) == 1)
            diff(i) = var(i,1) - var(i-1,1);
        else
            diff(i) = 0;
            counter = counter + 1;
        end
    end

    AV = mean(diff(diff>0));
    
    MIN = min(diff(diff>0));
    
    MAX = max(diff(diff>0));

    figure;
    plot(diff);
end