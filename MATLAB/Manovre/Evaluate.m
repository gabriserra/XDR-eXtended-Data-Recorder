%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%   Takes in input:
%           - 4 row vectors representing the discrete class
%             distributions of differents detected maneuvres.
%           - maneuvres weights (4,3)
%           - driving time 
%           - weights associated to each index (1,4)
%   
%   Return a column vector (1,5) containing the evaluation index of single
%   maneuvres and an overall index. 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [ index ] = Evaluate( suddens, brakings, turns, dynamic_crashes, weights, driving_time, evaluation_weights)
    index = zeros(1,5);
    if(size(weights,1) ~= 4 || size(weights,2) ~= 3)
        fprintf('Something wrong with the weights matrix');
    end 
    
    index(1,1) = compute_index(suddens,weights(:,1),driving_time);
    
    index(1,2) = compute_index(brakings,weights(:,1),driving_time);
    
    index(1,3) = compute_index(turns,weights(:,2),driving_time);
    
    index(1,4) = compute_index(dynamic_crashes,weights(:,3),driving_time);
    
    for i=1:1:4
        index(1,5) = index(1,5) + index(1,i) * evaluation_weights(1,i);
    end

end

function [index] = compute_index(distribution, weights, driving_time)
    if(size(distribution,1) == 3)
        distribution = distribution'; 
    end
    if(size(weights,2) == 3)
        weights = weights';
    end
    
    index =  distribution(:,1) * weights(:,1)'/driving_time;
end 


