%Takes in input the accx parameter that represents the frontal G
%Evolution over time.
%Return a nx4 matrix where each rows represents a sudden braking
%columns={time interval (sample),acc intensity, acc/interval,starting sample}
function [ output ] = Crash_checker(accx)
    if(size(accx,1) == 1)
        accx=accx';
    end
    
    peaks = find(abs(accx) > 0.5) ;                     
    brakings=zeros(size(peaks,1),4);
    directions= zeros(size(peaks,1),1);
    for i=1:1:size(peaks,1)
        if(accx(peaks(i,1),1) > 0)
            directions(i,1) = 1;
        else
            directions(i,1) =- 1;
        end
    end
    [peaks directions]
%     size(peaks,1)
%     size(brakings,1)
    brakings(:,4) = peaks;
    output=zeros(size(peaks,1),4);
    j=1;
    
    for i=1:1:size(peaks,1)                                                 %for each peaks compute intensity and time interval
        if(directions(i,1) > 0)
            ends=find(accx(peaks(i,1):size(accx,1)) < 0);
        else
            ends=find(accx(peaks(i,1):size(accx,1)) > 0);
        end
        brakings(i,1) = ends(1,1)-1;                                        %interval (in samples)
        brakings(i,2) = accx(peaks(i,1)) - accx(brakings(i,4)+ brakings(i,1),1);               %intensity
        brakings(i,3) = brakings(i,2)/brakings(i,1)*100;                    %G/(ms*10)*1000    
    end
    i=1;
    brakings
    while(i< size(peaks,1)-1)   
        selected = brakings(i,3)
        i=i+1
        brakings(i,4)
        find (brakings(:,3) == selected)   %%la find in caso di due elementi uguali mi prende il 739 anziche il 738
        output(j,:)=brakings(find (brakings(:,3) == selected) ,:) ;%check consequent brakins
        j = j+1;
        while(brakings(i+1,4) - brakings(i,4) < 10)  
            i=i+1;
        end
       
    end
    
    if(isempty(i))
        output(1,:)=brakings(1,:);
    else
        output(j,:)=brakings(i+1,:);
    end
    output = unique(output,'rows');                                           %remove duplicates
    output = sortrows(output,4);
    output = output(any(output,2),:);
end

