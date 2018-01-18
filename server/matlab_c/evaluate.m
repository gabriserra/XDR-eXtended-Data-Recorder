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

    if (acc ~= 0)
        slope = -100 / (sum(acc) * (weights(3,1) - weights(1,1)));
        evaluation(1) = 100 + slope * (acc' * weights(:,1) - sum(acc) * weights(1,1));
    else
        evaluation(1) = 100;
    end
    
    if (brake ~= 0)
        slope = -100 / (sum(brake) * weights(3,2) - sum(brake) * weights(1,2));
        evaluation(2) = 100 + slope * (brake' * weights(:,2) - sum(brake) * weights(1,2));
    else
        evaluation(2) = 100;
    end
    
    if (turns ~= 0)
        slope = -100 / (sum(turns) * weights(3,3) - sum(turns) * weights(1,3));
        evaluation(3) = 100 + slope * (turns' * weights(:,3) - sum(turns) * weights(1,3));
    else
        evaluation(3) = 100;
    end
    
    for i = 1 : size(evaluation, 1) - 1
        evaluation(size(evaluation, 1)) = evaluation(size(evaluation, 1)) + evaluation(i) * evaluation_weights(i);
    end
    evaluation
    evaluation = round(evaluation);
end