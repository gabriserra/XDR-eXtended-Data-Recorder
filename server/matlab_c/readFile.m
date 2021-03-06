function [var, del] = readFile(filename)
delimiter = {'\t'};
startRow = 1;
endRow = inf;

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

if size(data,2) == 8
    timestamp = data{:, 1};
    acc_x = data{:, 2};
    acc_y = data{:, 3};
    acc_z = data{:, 4};
    v = data{:, 5};
    gy_x = data{:, 6};
    gy_y = data{:, 7};
    gy_z = data{:, 8};
    
    index = find(timestamp > 10000);

    timestamp = removerows(timestamp,'ind',index);
    acc_x = removerows(acc_x,'ind',index);
    acc_y = removerows(acc_y,'ind',index);
    acc_z = removerows(acc_z,'ind',index);
    gy_x = removerows(gy_x,'ind',index);
    gy_y = removerows(gy_y,'ind',index);
    gy_z = removerows(gy_z,'ind',index);

    dim = min([size(timestamp,1), size(acc_x,1), size(acc_y,1), size(acc_z,1), size(v,1), size(gy_x,1), size(gy_y,1), size(gy_z,1)]);
    var = [timestamp(1:dim), acc_x(1:dim), acc_y(1:dim), acc_z(1:dim), v(1:dim), gy_x(1:dim), gy_y(1:dim), gy_z(1:dim)];
    [index, ~] = find(isnan(var));
    var = removerows(var,'ind',index);
else
    if size(data,2) == 4
        timestamp = data{:, 1};
        acc_x = data{:, 2};
        acc_y = data{:, 3};
        gy_z = data{:, 4};

        index = find(timestamp > 1000000);

        timestamp = removerows(timestamp,'ind',index);
        acc_x = removerows(acc_x,'ind',index);
        acc_y = removerows(acc_y,'ind',index);
        gy_z = removerows(gy_z,'ind',index);

        del = index;

        dim = min([size(timestamp,1), size(acc_x,1), size(acc_y,1), size(gy_z,1)]);
        var = [timestamp(1:dim), acc_x(1:dim), acc_y(1:dim), gy_z(1:dim)];
        [index, ~] = find(isnan(var));
        var = removerows(var,'ind',index);
    else
        timestamp = data{:, 1};
        seq_num = data{:,2};
        acc_x = data{:, 3};
        acc_y = data{:, 4};
        gy_z = data{:, 5};

        index = find(seq_num > 1000000);

        timestamp = removerows(timestamp,'ind',index);
        seq_num = removerows(seq_num,'ind',index);
        acc_x = removerows(acc_x,'ind',index);
        acc_y = removerows(acc_y,'ind',index);
        gy_z = removerows(gy_z,'ind',index);

        del = index;

        dim = min([size(timestamp,1), size(seq_num,1), size(acc_x,1), size(acc_y,1), size(gy_z,1)]);
        var = [timestamp(1:dim), seq_num(1:dim), acc_x(1:dim), acc_y(1:dim), gy_z(1:dim)];
        [index, ~] = find(isnan(var));
        var = removerows(var,'ind',index);
    end
end