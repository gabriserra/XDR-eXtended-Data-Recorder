%Takes in input the accx parameter that represents the frontal G
%Evolution over time.
%Return a nx4 matrix where each rows represents a sudden braking
%columns={time interval (sample),acc intensity, acc/interval,starting sample}
function [ output ] = Sudden_Braking_checker(accx)
    if(size(accx,1) == 1)
        accx=accx';
    end
    
    peaks = find(accx > 0.8);                       
    brakings=zeros(size(peaks,1),4);
    brakings(:,4) = peaks;
    output=zeros(size(peaks,1),4);
    j=1;
    
    for i=1:1:size(peaks,1)                                                 %for each peaks compute intensity and time interval
        ends=find(accx(peaks(i,1):size(accx,1)) < 0);
        brakings(i,1) = ends(1,1)-1;                                        %interval (in samples)
        brakings(i,2) = accx(peaks(i,1)) - accx(brakings(i,4)+ brakings(i,1),1);               %intensity
        brakings(i,3) = brakings(i,2)/brakings(i,1)*100;                    %G/(ms*10)*1000    
    end

    for i=1:1:size(peaks,1)-1                                               %check consequent brakins 
        if(brakings(i+1,4) - brakings(i,4) < 5)             
            selected = max(brakings(i+1,3),brakings(i+1,3));                %choose the maximum wrt G/s 
            output(j,:)=brakings(find (brakings(:,3) == selected) ,:) ;
        else
            output(j,:)=brakings(i,:);
        end
        j=j+1;
       
    end
    output(j,:)=brakings(i+1,:);
    output=unique(output,'rows');                                           %remove duplicates

end

