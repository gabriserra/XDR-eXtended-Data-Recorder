%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%   Takes in input:
%           - 4 row vectors representing the discrete class
%             distributions of differents detected maneuvres.
%           - maneuvres weights (4,3)
%           - driving time 
%           - weights associated to each evaluation (1,4)
%   
%   Return a column vector (1,5) containing the evaluation evaluation of single
%   maneuvres and an overall evaluation. 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function evaluation = evaluate(acc, brake, turns, weights, evaluation_weights)
    evaluation = zeros(4,1);
    if (sum(acc, 1) ~= 0)
        evaluation(1) = 100 - 400 * (acc' * weights(:,1) / sum(acc) - 0.2);
    else
        evaluation(1) = 100;
    end
    
    if (sum(brake, 1) ~= 0)
        evaluation(2) = 100 - 400 * (brake' * weights(:,2) / sum(brake) - 0.2);
    else
        evaluation(2) = 100;
    end
    
    if (sum(turns, 1) ~= 0)
        evaluation(3) = 100 - 400 * (turns' * weights(:,3) / sum(turns) - 0.2);
    else
        evaluation(3) = 100;
    end
    
    for i = 1 : size(evaluation, 1) - 1
        evaluation(size(evaluation, 1)) = evaluation(size(evaluation, 1)) + evaluation(i) * evaluation_weights(i);
    end
    evaluation = round(evaluation);
end