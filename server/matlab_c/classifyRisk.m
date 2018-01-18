function [c_acc, c_brake, c_turns] = classifyRisk(acc, brake, turns)
    c_acc = zeros(3, 1);
    c_brake = zeros(3, 1);
    c_turns = zeros(3, 1);
    
    acc_small_threshold = 0;
    acc_medium_threshold = 0.07;
    acc_large_threshold = 0.14;
    
    if(acc ~= 0)
        c_acc(1) = size(acc(acc(:,2) >= acc_small_threshold & acc(:,2) < acc_medium_threshold), 1);
        c_acc(2) = size(acc(acc(:,2) >= acc_medium_threshold & acc(:,2) < acc_large_threshold), 1);
        c_acc(3) = size(acc(acc(:,2) >= acc_large_threshold), 1);
    end
    
    brake_small_threshold = -acc_small_threshold;
    brake_medium_threshold = -acc_medium_threshold;
    brake_large_threshold = -acc_large_threshold;
    
    if(brake ~= 0)
        c_brake(1) = size(brake(brake(:,2) < brake_small_threshold & brake(:,2) >= brake_medium_threshold), 1);
        c_brake(2) = size(brake(brake(:,2) < brake_medium_threshold & brake(:,2) >= brake_large_threshold), 1);
        c_brake(3) = size(brake(brake(:,2) < brake_large_threshold), 1);
    end
   
    turns_small_threshold = 0;
    turns_medium_threshold = 0.05;
    turns_large_threshold = 0.1;
    
    if(turns ~= 0)
        c_turns(1) = size(turns(turns(:,2) >= turns_small_threshold & turns(:,2) < turns_medium_threshold), 1);
        c_turns(2) = size(turns(turns(:,2) >= turns_medium_threshold & turns(:,2) < turns_large_threshold), 1);
        c_turns(3) = size(turns(turns(:,2) >= turns_large_threshold), 1);
    end
end