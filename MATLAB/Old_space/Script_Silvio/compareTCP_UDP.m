set(0,'DefaultFigureVisible','off');

[AV_TCP_S, MAX_TCP_S, MIN_TCP_S, LOSS_TCP_S] = computeRate('../../server/log/log_2018-01-12_14-50-27.csv');
[AV_UDP_S, MAX_UDP_S, MIN_UDP_S, LOSS_UDP_S] = computeRate('../../server/log/log_2018-01-12_15-12-34.csv');
[AV_UDP_X, MAX_UDP_X, MIN_UDP_X, LOSS_UDP_X] = computeRate('../../server/log/log_2018-01-12_15-18-56.csv');
[AV_TCP_X, MAX_TCP_X, MIN_TCP_X, LOSS_TCP_X] = computeRate('../../server/log/log_2018-01-12_15-25-36.csv');
[AV_TCP_A, MAX_TCP_A, MIN_TCP_A, LOSS_TCP_A] = computeRate('../../server/log/log_2018-01-12_15-28-57.csv');
[AV_UDP_A, MAX_UDP_A, MIN_UDP_A, LOSS_UDP_A] = computeRate('../../server/log/log_2018-01-12_15-34-02.csv');

AVERAGE_UDP = [AV_UDP_S; AV_UDP_X; AV_UDP_A];
AVERAGE_TCP = [AV_TCP_S; AV_TCP_X; AV_TCP_A];

MAX_UDP = [MAX_UDP_S; MAX_UDP_X; MAX_UDP_A];
MAX_TCP = [MAX_TCP_S; MAX_TCP_X; MAX_TCP_A];

MIN_UDP = [MIN_UDP_S; MIN_UDP_X; MIN_UDP_A];
MIN_TCP = [MIN_TCP_S; MIN_TCP_X; MIN_TCP_A];

STATS_1_UDP = [LOSS_UDP_S(size(LOSS_UDP_S,1) - 1,1:3); LOSS_UDP_X(size(LOSS_UDP_X,1) - 1,1:3); LOSS_UDP_A(size(LOSS_UDP_A,1) - 1,1:3)];
STATS_2_UDP = [LOSS_UDP_S(size(LOSS_UDP_S,1),:); LOSS_UDP_X(size(LOSS_UDP_X,1),:); LOSS_UDP_A(size(LOSS_UDP_A,1),:)];

if ~isempty(LOSS_TCP_S) && ~isempty(LOSS_TCP_X) && ~isempty(LOSS_TCP_A)
    STATS_1_TCP = [LOSS_TCP_S(size(LOSS_TCP_S,1) - 1,1:3); LOSS_TCP_X(size(LOSS_TCP_X,1) - 1,1:3); LOSS_TCP_A(size(LOSS_TCP_A,1) - 1,1:3)];
    STATS_2_TCP = [LOSS_TCP_S(size(LOSS_TCP_S,1),:); LOSS_TCP_X(size(LOSS_TCP_X,1),:); LOSS_TCP_A(size(LOSS_TCP_A,1),:)];
end

set(0,'DefaultFigureVisible','on');

str1 = [string('MEDIA TEMPO DI TRASMISSIONE'); string('MAX TEMPO DI TRASMISSIONE'); string('MIN TEMPO DI TRASMISSIONE'); string('MAX PERSI CONS.'); string('MIN PERSI CONS.'); string('MEDIA PERSI CONS.'); string('TOT. PACCHETTI PERSI'); string('TOT. TEMPO PERSO'); string('TOTALE REGISTRATO'); string('PERCENTUALE PERSA')];

names = [string(''); string('SILVIO'); string('XDR'); string('ANDREA');];

UDP = [str1'; AVERAGE_UDP MAX_UDP MIN_UDP STATS_1_UDP STATS_2_UDP];

UDP = [names UDP];

str2 = [string('MEDIA TEMPO DI TRASMISSIONE'); string('MAX TEMPO DI TRASMISSIONE'); string('MIN TEMPO DI TRASMISSIONE')];

if ~isempty(LOSS_TCP_S) && ~isempty(LOSS_TCP_X) && ~isempty(LOSS_TCP_A)
    TCP = [str2'; AVERAGE_TCP MAX_TCP MIN_TCP STATS_1_TCP STATS_2_TCP];
else
    TCP = [str2'; AVERAGE_TCP MAX_TCP MIN_TCP];
end

TCP = [names TCP];

clear AV_TCP_S MAX_TCP_S MIN_TCP_S LOSS_TCP_S AV_UDP_S MAX_UDP_S MIN_UDP_S LOSS_UDP_S AV_UDP_X MAX_UDP_X MIN_UDP_X LOSS_UDP_X AV_TCP_X MAX_TCP_X MIN_TCP_X LOSS_TCP_X AV_TCP_A MAX_TCP_A MIN_TCP_A LOSS_TCP_A AV_UDP_A MAX_UDP_A MIN_UDP_A LOSS_UDP_A