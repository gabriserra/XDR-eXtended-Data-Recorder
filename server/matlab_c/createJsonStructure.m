function content = createJsonStructure(email, start_time, duration, acc, brake, turns, dynamic_crashes, static_crashes, evaluation)
    map_slope = 50;
    
    content.email = email;

    trip = struct('starttime', start_time, 'secondslength', duration);
    content.trip = trip;
    if (acc ~= 0)
        size_acc = size(acc,1);
        max_acc = round(200*max(abs(acc(:,2))));
    else
        size_acc = 0;
        max_acc = 0;
    end
    
    if (brake ~= 0)
        size_brake = size(brake,1);
        max_brake = round(200*max(abs(brake(:,2))));
    else
        size_brake = 0;
        max_brake = 0;
    end
    
    if (turns ~= 0)
        size_turns = size(turns,1);
        max_turns = round(300*max(abs(turns(:,2))));
    else
        size_turns = 0;
        max_turns = 0;
    end

    stat = struct('numberacc', size_acc, 'worstacc', max_acc, 'numberbra', size_brake, 'worstbra', max_brake, 'numbercur', size_turns, 'worstcur', max_turns);
    content.stat = stat;

    ev = struct('pointstotal', evaluation(4), 'pointsacceleration', evaluation(1), 'pointsbraking', evaluation(2), 'pointssteering', evaluation(3));
    content.evaluation = ev;

    index = 1;
    if (static_crashes ~= 0)
        for i = 1 : size(static_crashes,1)
            crash(i) = struct('crashtime', start_time + milliseconds(static_crashes(i,1)), 'intensity', round(map_slope*abs(static_crashes(i,2))), 'stationary', 1);
            index = index + 1;
        end
    end
    
    if (dynamic_crashes ~= 0)
        for i = 1 : size(dynamic_crashes,1)
            crash(index) = struct('crashtime', start_time + milliseconds(dynamic_crashes(i,1)), 'intensity', round(map_slope*abs(dynamic_crashes(i,2))), 'stationary', 0);
            index = index + 1;
        end
    end
    
    if(exist('crash', 'var'))
        crash(index) = struct('crashtime', '', 'intensity', '', 'stationary', '');
        content.crash = crash;
    end
    
end