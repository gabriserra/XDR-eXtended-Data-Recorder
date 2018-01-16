function processData(filename, email)
    raw = readFile(filename);
    if (size(raw,1) > 100)
        date = erase(erase(filename,'.csv'),'../log/log_');
        start_time = datetime(date,'InputFormat','uuuu-MM-dd_HH-mm-ss');
        duration = round((raw(size(raw,1),1) - raw(1,1)) / 1000);
        unfiltered = filler(raw);
        filtered = raw;

        for i = 3 : 5
            filtered(:,i) = denoise(raw(:,i));
        end

        filtered = filler(filtered);

        [acc, brake, turns, dynamic_crashes, static_crashes] = mainChecker(filtered, unfiltered);

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
        [c_acc, c_brake, c_turns] = classifyRisk(acc, brake, turns);

        weights = [0.2 0.2 0.2; 0.3 0.3 0.3; 0.5 0.5 0.5];

        evaluation_weights = [1/3 1/3 1/3];

        evaluation = evaluate(c_acc, c_brake, c_turns, weights, evaluation_weights);

        content = createJsonStructure(email, start_time, duration, acc, brake, turns, dynamic_crashes, static_crashes, evaluation);

        json_content = sprintf('%s%s', 'content=',jsonencode(content));

        fileID = fopen('./.tmp.txt', 'w');
        fprintf(fileID, '%s', json_content);
        fclose(fileID);
    end
end