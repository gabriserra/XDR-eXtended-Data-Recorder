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
    static_crashes = Static_crash_checker(n_datain(:,3))
    dynamic_crashes = Dynamic_crash_checker(accx);

    
    %remove static crashes from dynamic crashes
    for i=1:1:size(static_crashes,1)
        dynamic_crashes(find(dynamic_crashes(:,1) == static_crashes(i,4)),:)=[];
    end
end


