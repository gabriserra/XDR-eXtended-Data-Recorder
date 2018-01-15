function [suddens, turns, static_crashes, dynamic_crashes] = main_checker(datain,n_datain)
    
    %check input size
    if(size(datain,2) ~= 5)                                                 
        fprintf('input does not match');
    end
    samples = size(datain,1);
    
    %remove signal noise
%     samples
%     for i=3:1:5
%         
%         datain(:,i) = denoise(datain(:,i));
%     end
%     
%     %fill signal with missing packets
%     datain = filler(datain);                                              

    %auxiliary variables
    accx = datain(:,3);                                                    
    accy = datain(:,4);
    giroz = datain(:,5);
    
    %Sudden acceleration/braking
    suddens = sudden_checker(accx)
    
    %turns
    turns = Turn_Checker(accx,accy,giroz)
    
    %Crashes
    static_crashes = Static_crash_checker(n_datain(:,3))
    dynamic_crashes = Dynamic_crash_checker(accx);

    %remove suddens from turns
    proximity_margin = 100;
        if(turns ~= 0)
            for i=1:1:size(turns,1)
                upper = turns(i,1)+turns(i,2)+ proximity_margin;
                lower = turns(i,1)- proximity_margin;
                to_remove = find(suddens(:,1) < upper & suddens(:,1) > lower);
                suddens(to_remove,:) = [];
            end
        end
    
    
    %remove static crashes from suddens
    proximity_margin = 100;
        
        for i=1:1:size(suddens,1)
            upper = suddens(i,1)+ proximity_margin;
            lower = suddens(i,1)- proximity_margin;
            to_remove = find(static_crashes(:,1) < upper & static_crashes(:,1) > lower);
            static_crashes(to_remove,:) = [];
        end
    
    %remove detected suddens,turns and statics crashes near to dynamic crashes
    proximity_margin = 25;
        
        for i=1:1:size(dynamic_crashes,1)
            upper = dynamic_crashes(i,1)+ proximity_margin;
            lower = dynamic_crashes(i,1)- proximity_margin;
            to_remove = find(suddens(:,1) < upper & suddens(:,1) > lower);
            suddens(to_remove,:) = [];
            to_remove = find(turns(:,1) < upper & turns(:,1) > lower);
            turns(to_remove,:) = [];
            upper = dynamic_crashes(i,1)+ proximity_margin*2;
            lower = dynamic_crashes(i,1)- proximity_margin*2;
            to_remove = find(static_crashes(:,1) < upper & static_crashes(:,1) > lower);
            static_crashes(to_remove,:) = [];
        end
    
    
end


