function [c_acc, c_brake, c_turns] = classifyRisk(acc, brake, turns)
    c_acc = zeros(3, 1);
    c_brake = zeros(3, 1);
    c_turns = zeros(3, 1);
    
    acc_small_threshold = 0.04;
    acc_medium_threshold = 0.2;
    acc_large_threshold = 0.4;
    
    if(acc ~= 0)
        c_acc(1) = size(acc(acc >= acc_small_threshold & acc < acc_medium_threshold), 1);
        c_acc(2) = size(acc(acc >= acc_medium_threshold & acc < acc_large_threshold), 1);
        c_acc(3) = size(acc(acc >= acc_large_threshold), 1);
    end
    
    brake_small_threshold = -0.1;
    brake_medium_threshold = -0.2;
    brake_large_threshold = -0.22;
    
    if(brake ~= 0)
        c_brake(1) = size(brake(brake >= brake_small_threshold & brake < brake_medium_threshold), 1);
        c_brake(2) = size(brake(brake >= brake_medium_threshold & brake < brake_large_threshold), 1);
        c_brake(3) = size(brake(brake >= brake_large_threshold), 1);
    end
   
    turns_small_threshold = 0.0014;
    turns_medium_threshold = 0.7;
    turns_large_threshold = 0.14;
    
    if(turns ~= 0)
        c_turns(1) = size(turns(turns >= turns_small_threshold & turns < turns_medium_threshold), 1);
        c_turns(2) = size(turns(turns >= turns_medium_threshold & turns < turns_large_threshold), 1);
        c_turns(3) = size(turns(turns >= turns_large_threshold), 1);
    end
    
%     static_crashes_small_threshold = 1.9;
%     static_crashes_medium_threshold = 1.95;
%     static_crashes_large_threshold = 1.99;
%     
%     if(~isempty(static_crashes))
%         c_static_crashes(1) = size(static_crashes(static_crashes >= static_crashes_small_threshold && static_crashes < static_crashes_medium_threshold));
%         c_static_crashes(2) = size(static_crashes(static_crashes >= static_crashes_medium_threshold && static_crashes < static_crashes_large_threshold));
%         c_static_crashes(3) = size(static_crashes(static_crashes >= static_crashes_large_threshold));
%     end
%     
%     dynamic_crashes_small_threshold = -0.1;
%     dynamic_crashes_medium_threshold = -0.5;
%     dynamic_crashes_large_threshold = -1;
%     
%     if(~isempty(dynamic_crashes))
%         c_dynamic_crashes(1) = size(dynamic_crashes(dynamic_crashes >= dynamic_crashes_small_threshold && dynamic_crashes < dynamic_crashes_medium_threshold));
%         c_dynamic_crashes(2) = size(dynamic_crashes(dynamic_crashes >= dynamic_crashes_medium_threshold && dynamic_crashes < dynamic_crashes_large_threshold));
%         c_dynamic_crashes(3) = size(dynamic_crashes(dynamic_crashes >= dynamic_crashes_large_threshold));
%     end
end