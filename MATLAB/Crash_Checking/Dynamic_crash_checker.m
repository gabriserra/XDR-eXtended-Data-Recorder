function [crash] = Dynamic_crash_checker(accx)
    peaks = find(accx < -0.5 & accx > -1.2 );
   

    crash=0;
    found=0;
    j=1;
    i=1
    while (i < size(peaks,1)-1)
        if(found == 0)
            crash(j,1) = peaks(i,1);
            j=j+1;
            found = 1;
        end
        
        if(found == 1 && abs(crash(j-1,1)-peaks(i,1)) > 10)
            found = 0;
            i = i-1;
        end
        i=i+1;
    end
  

    for i=1:1:size(crash,1)  
        
        ends=find(abs(accx(crash(i,1):size(accx,1))) < 0.3);
        crash(i,1)
        crash(i,2)=ends(1,1);
        
    end
   % crash;
    %filtering
    to_remove = find(crash(:,2)>15);
    crash(to_remove,:)=[];
     to_remove = find(abs(crash(:,2)) < 4)  
     crash(to_remove,:)=[];
                     
end
    



