function [acc, brake, turns, static_crashes, dynamic_crashes] = mainChecker(datain, n_datain)
    accx = datain(:,3);                                                    
    accy = datain(:,4);
    giroz = datain(:,5);
    
    acc_small_threshold = 0.03;
    brake_small_threshold = -0.03;
    
    % Sudden acceleration/braking
    [acc, brake] = accBrakeChecker(accx, acc_small_threshold, brake_small_threshold);
    
    % turn_search_threshold = 0.05;
    turn_search_threshold = 10;
    
    %turns
    turns = turnChecker(accx, accy, giroz, turn_search_threshold);
    
    static_crashes_search_threshold = 1.5;
    
    %Crashes
    static_crashes = staticCrashChecker(n_datain(:,3), static_crashes_search_threshold);
    
    dynamic_crashes_small_threshold = -0.15;
    dynamic_crashes_large_threshold = -0.5;
    
    dynamic_crashes = dynamicCrashChecker(accx, dynamic_crashes_small_threshold, dynamic_crashes_large_threshold);
    
    %remove turns and dynamics from static_crashes
    proximity_margin = 25;
        
    for i = 1 : size(static_crashes,1)
        upper = static_crashes(i,1) + proximity_margin;
        lower = static_crashes(i,1) - proximity_margin;
        if (turns ~= 0)
            turns = turns(turns(:,1) >= upper | turns(:,1) <= lower, :);
            if(isempty(turns))
                turns = 0;
            end
        end
        
        if (acc ~= 0)
            acc = acc(acc(:,1) >= upper | acc(:,1) <= lower, 1:2);
            if(isempty(acc))
                acc = 0;
            end
        end
        if (brake ~= 0)
            brake = brake(brake(:,1) >= upper | brake(:,1) <= lower, 1:2);
            if(isempty(brake))
                brake = 0;
            end
        end

        upper = static_crashes(i,1) + proximity_margin * 2;
        lower = static_crashes(i,1) - proximity_margin * 2;
        if (dynamic_crashes ~= 0)
            dynamic_crashes = dynamic_crashes(dynamic_crashes(:,1) >= upper | dynamic_crashes(:,1) <= lower, :);
            if(isempty(dynamic_crashes))
                dynamic_crashes = 0;
            end
        end
    end
        
    %remove detected suddens, turns and statics crashes near to dynamic crashes
    proximity_margin = 60;
        
    for i = 1 : size(dynamic_crashes,1)
        upper = dynamic_crashes(i,1) + proximity_margin;
        lower = dynamic_crashes(i,1) - proximity_margin;
        if(brake ~= 0)
            brake = brake(brake(:,1) >= upper | brake(:,1) <= dynamic_crashes(i,1) - 5, 1:2);
            if(isempty(brake))
                brake = 0;
            end
        end
        if(turns ~= 0)
            turns = turns(turns(:,1) >= upper | turns(:,1) <= lower, :);
            if(isempty(turns))
                turns = 0;
            end
        end
    end
end