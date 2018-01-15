function filtered = ara_filter(unfiltered)
    n = size(unfiltered,2);
    w = 3; % window size 3, ovvero media il corrente con quello prima e quello dopo
    b = (1/w) * ones(1,w);
    a = 1;

    delay       = mean(grpdelay(b,a)); % serve per dei conti dopo
    filt_idxs   = delay *2+1:n; % filtra i dati, praticamente vanno spostati indietro per via del ritardo

    f = filter(b,a,unfiltered);

    filtered = f(:, filt_idxs);
end