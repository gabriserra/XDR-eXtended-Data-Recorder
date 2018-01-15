function content = prova_conversione()
    trip_fields = ['meters' 'starttime' 'secondslength'];
    trip = struct(trip_fields(1), 50, trip_fields(2), '2018-01-07 07:30:00', trip_fields(3), 120);
    
    stat_fields = ['numberacc' 'worstacc' 'numberbra' 'worstbra' 'numbercur'];
    stat = struct(stat_fields(1), 2, stat_fields(2), 5, stat_fields(3), 1, stat_fields(4), 3, stat_fields(5), 8);
    
    evaluation_fields = ['pointstotal' 'pointsacceleration' 'pointsbraking' 'pointssteering' 'pointsspeed'];
    evaluation = struct(evaluation_fields(1), 2, evaluation_fields(2), 5, evaluation_fields(3), 1, evaluation_fields(4), 3, evaluation_fields(5), 8);
    
    crash_fields = ['crashtime' 'intensity' 'stationary'];
    crash = struct(crash_fields(1), '2018-01-07 07:30:00', crash_fields(2), 5, crash_fields(3), 0);
    
    content_fields = ['email' 'trip' 'stat' 'evaluation' 'crash'];
    content = struct(content_fields(1), 'user@example.it', content_fields(2), trip, content_fields(3), stat, content_fields(4), evaluation, content_fields(5), crash);
end