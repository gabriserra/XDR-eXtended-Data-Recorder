function json_content = computeLossPackets(filename)
    fprintf('%s\n', filename);
    unfilled = readFile(filename);
    diff = zeros(size(unfilled,1), 4);
    duration = unfilled(size(unfilled,1),1) - unfilled(1,1);
    % timestamp = computeDate(unfilled, erase(erase(filename,'.csv'),'../../server/log/log_'));
    % timestamp = timestamp(2:end,:);
    
    for i = 2 : size(unfilled,1)
        diff(i,1) = unfilled(i,2) - unfilled(i-1,2);
        diff(i,2) = unfilled(i,1) - unfilled(i-1,1);
        diff(i,3) = unfilled(i-1,1);
        diff(i,4) = unfilled(i,1);
    end
    
    diff = diff(2:end,:);
    
    MAX = max(diff(:,2));
    MIN = min(diff(:,2));
    MEAN = mean(diff(:,2));
        
    figure;
    plot(diff(:,2));
    % plot(timestamp, diff(:,2));
    
    fprintf('\nTIME RECORDED: \t%f \n\nMAX: \t%d \nMIN: \t%d \nMEAN: \t%f \n\n', duration, MAX, MIN, MEAN);
    
    loss = diff(diff(:,1) > 1,:);
    names = [string('TIME RECORDED'); string('MAX'); string('MIN'); string('MEAN');];
    stats = [names [duration; MAX; MIN; MEAN]];
    
    if (~isempty(loss))
        filled = filler(unfilled);
        % timestamp = computeDate(filled, erase(erase(filename,'.csv'),'../../server/log/log_'));
        % timestamp = timestamp(2:end,:);
        diff = zeros(size(filled,1), 4);

        for i = 2 : size(filled,1)
            diff(i,1) = filled(i,2) - filled(i-1,2);
            diff(i,2) = filled(i,1) - filled(i-1,1);
            diff(i,3) = filled(i-1,1);
            diff(i,4) = filled(i,1);
        end

        diff = diff(2:end,:);

        figure;
        plot(diff(:,2));
        % plot(timestamp, diff(:,2));
        
        SUM = sum(loss,1);
        MAX = max(loss(:,1));
        MIN = min(loss(:,1));
        MEAN = mean(loss(:,1));
        fprintf('PACKET LOST: \t%d \nTIME LOST: \t%d \nPERC. LOST: \t%f \n\n', SUM(1), SUM(2), SUM(2)/duration*100);
        fprintf('MAX CONS. PACKET LOST: \t%d \nMIN CONS. PACKET LOST: \t%d \nAVE CONS. PACKET LOST: \t%f \n\n',  MAX, MIN, MEAN);
        names = [string('PACKET LOST'); string('TIME LOST'); string('PERC. LOST'); string('MAX CONS. PACKET LOST'); string('MIN CONS. PACKET LOST'); string('MEAN CONS. PACKET LOST')];
        stats = [stats; names [SUM(1); SUM(2); SUM(2)/duration*100; MAX; MIN; MEAN]];
    end
    
    json_content = prova_conversione();
    json_content = sprintf('%s%s', 'content=',json_content);
    
    fileID = fopen('./tmp.txt', 'w');
    fprintf(fileID, '%s', json_content);
    fclose(fileID);
end