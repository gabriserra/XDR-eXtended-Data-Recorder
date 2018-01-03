function createWorkspace()
    files = dir('../server/log/*');
    
    for file = files'
        if(contains(file.name,'log') == 1)
            filename = erase(strrep(file.name, '-','_'),'.csv');
            cmd = [filename '=readFile(strcat(''../server/log/'',file.name));'];
            eval(cmd);
        end
    end
    if ~exist('dataset.mat','file')
        save('dataset.mat',filename);
    else
        save('dataset.mat',filename,'-append');
    end
end