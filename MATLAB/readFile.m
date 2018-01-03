function var = readFile(filename, startRow, endRow)
delimiter = {'\t'};
if nargin<=2
    startRow = 1;
    endRow = inf;
end

formatSpec = '%f%f%f%f%f%f%f%f%[^\n\r]';
fileID = fopen(filename,'r');

data = textscan(fileID, formatSpec, endRow(1)-startRow(1)+1, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'HeaderLines', startRow(1)-1, 'ReturnOnError', false, 'EndOfLine', '\r\n');

for block = 2 : length(startRow)
    frewind(fileID);
    dataArrayBlock = textscan(fileID, formatSpec, endRow(block)-startRow(block)+1, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'HeaderLines', startRow(block)-1, 'ReturnOnError', false, 'EndOfLine', '\r\n');
    for col=1:length(data)
        data{col} = [data{col};dataArrayBlock{col}];
    end
end
fclose(fileID);
timestamp = data{:, 1};
acc_x = data{:, 2};
acc_y = data{:, 3};
acc_z = data{:, 4};
v = data{:, 5};
gy_x = data{:, 6};
gy_y = data{:, 7};
gy_z = data{:, 8};

dim = min([size(timestamp,1), size(acc_x,1), size(acc_y,1), size(acc_z,1), size(v,1), size(gy_x,1), size(gy_y,1), size(gy_z,1)]);
var = [timestamp(1:dim), acc_x(1:dim), acc_y(1:dim), acc_z(1:dim), v(1:dim), gy_x(1:dim), gy_y(1:dim), gy_z(1:dim)];