function [acc, brake, turns, static_crashes, dynamic_crashes] = processData(filename, email)
    raw = readFile(filename);
    if (size(raw,1) > 100)
        date = erase(erase(filename,'.csv'),'../log/log_');
        start_time = datetime(date,'InputFormat','uuuu-MM-dd_HH-mm-ss','Format', 'uuuu-MM-dd HH:mm:ss');
        duration = round((raw(size(raw,1),1) - raw(1,1)) / 1000);
        unfiltered = filler(raw);
        filtered = raw;

        for i = 3 : 5
            filtered(:,i) = denoise(raw(:,i));
        end

        filtered = filler(filtered);

        [acc, brake, turns, static_crashes, dynamic_crashes] = mainChecker(filtered, unfiltered);

        figure;
        plot(filtered(:,3));
        figure;
        plot(filtered(:,4));
        figure;
        plot(filtered(:,5));
        
        if (acc ~= 0)
            acc(:,1) = unfiltered(acc(:,1),1);
        end

        if (brake ~= 0)
            brake(:,1) = unfiltered(brake(:,1),1);
        end

        if (turns ~= 0)
            turns(:,1) = unfiltered(turns(:,1),1);
        end

        if (dynamic_crashes ~= 0)
            dynamic_crashes(:,1) = unfiltered(dynamic_crashes(:,1),1);
        end

        if (static_crashes ~= 0)
            static_crashes(:,1) = unfiltered(static_crashes(:,1),1);
        end
        [c_acc, c_brake, c_turns] = classifyRisk(acc, brake, turns)
        
        weights = [0.2 0.2 0.2; 0.35 0.35 0.35; 0.45 0.45 0.45];

        evaluation_weights = [1/3 1/3 1/3];

        evaluation = evaluate(c_acc, c_brake, c_turns, weights, evaluation_weights)

        content = createJsonStructure(email, start_time, duration, acc, brake, turns, dynamic_crashes, static_crashes, evaluation);

        json_content = sprintf('%s%s', 'content=',jsonencode(content));

        if exist('./.tmp.txt', 'file')
            delete('./.tmp.txt');
        end
        
        fileID = fopen('./.tmp.txt', 'w');
        fprintf(fileID, '%s', json_content);
        fclose(fileID);
    end
end