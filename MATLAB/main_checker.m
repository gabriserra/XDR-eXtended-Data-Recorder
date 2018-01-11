function [suddens, turns, static_crashes, dynamic_crashes] = main_checker(datain,n_datain)
    
    %check input size
    if(size(datain,2) ~= 5)                                                 
        fprintf("input does not match");
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
    static_crashes = Static_crash_checker(accx)
    dynamic_crashes =Dynamic_crash_checker(accx);
    
    
end

