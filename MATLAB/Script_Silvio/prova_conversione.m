function json_content = prova_conversione()

    trip = struct('meters', 50, 'starttime', '2018-01-07 07:30:00', 'secondslength', 120);

    stat = struct('numberacc', 2, 'worstacc', 5, 'numberbra', 1, 'worstbra', 3, 'numbercur', 8);

    evaluation = struct('pointstotal', 2, 'pointsacceleration', 5, 'pointsbraking', 1, 'pointssteering', 3, 'pointsspeed', 8);

    crash = struct('crashtime', '2018-01-07 07:30:00', 'intensity', 5, 'stationary', 0);

    content = struct('email', 'user@example.it', 'trip', trip, 'stat', stat, 'evaluation', evaluation, 'crash', crash);

    json_content = jsonencode(content);
end