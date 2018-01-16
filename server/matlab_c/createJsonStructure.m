function content = createJsonStructure(email, start_time, duration, acc, brake, turns, dynamic_crashes, static_crashes, evaluation)
    if (acc == 0)
        acc = ones(1,2);
    end
    if (brake == 0)
        brake = ones(1,2);
    end
    if (turns == 0)
        turns = ones(1,2);
    end
    if (dynamic_crashes == 0)
        static_crashes = ones(1,2);
    end
    if (static_crashes == 0)
        static_crashes = ones(1,2);
    end

    trip = struct('meters', 0, 'starttime', start_time, 'secondslength', duration);
    
    stat = struct('numberacc', size(acc,1), 'worstacc', max(acc(:,2)), 'numberbra', size(brake,1), 'worstbra', max(brake(:,2)), 'numbercur', size(turns, 1), 'worstcur', max(turns(:,2)));

    evaluation = struct('pointstotal', evaluation(4), 'pointsacceleration', evaluation(1), 'pointsbraking', evaluation(2), 'pointssteering', evaluation(3), 'pointsspeed', -1);

    index = 1;
    if (static_crashes ~= 0)
        for i = 1 : size(static_crashes,1)
            crash(i) = struct('crashtime', start_time + milliseconds(static_crashes(i,1)), 'intensity', static_crashes(i,2), 'stationary', 1);
            index = index + 1;
        end
    else
        static_crashes = -ones(1,2);
        crash(index) = struct('crashtime', static_crashes(1), 'intensity', static_crashes(2), 'stationary', 1);
    end
    
    if (dynamic_crashes ~= 0)
        for i = 1 : size(dynamic_crashes,1)
            crash(index) = struct('crashtime', start_time + milliseconds(dynamic_crashes(i,1)), 'intensity', dynamic_crashes(i,2), 'stationary', 0);
            index = index + 1;
        end
    else
        dynamic_crashes = -ones(1,2);
        crash(index) = struct('crashtime', dynamic_crashes(1), 'intensity', dynamic_crashes(2), 'stationary', 0);
    end
    content = struct('email', email, 'trip', trip, 'stat', stat, 'evaluation', evaluation, 'crash', crash);
end