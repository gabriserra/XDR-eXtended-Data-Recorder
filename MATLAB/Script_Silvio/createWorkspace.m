function createWorkspace()
    path = '../../server/log/';
    folder = dir(strcat(path,'*'));
    for sub_folder = folder'
        if(~strcmp(sub_folder.name,'..')==1)
            sub_folder_path = strcat(path,sub_folder.name,'/');
            files = dir(strcat(sub_folder_path,'*'));
            for file = files'
                if(~strcmp(file.name,'..')==1 && ~strcmp(file.name,'.')==1)
                    if(contains(file.name,'log') == 1)
                        filename = erase(strrep(file.name, '-','_'),'.csv');
                        cmd = [filename '=readFile(strcat(sub_folder_path,file.name));'];
                        eval(cmd);

                        if ~exist('dataset.mat','file')
                            save('dataset.mat',filename);
                        else
                            save('dataset.mat',filename,'-append');
                        end
                    end
                end
            end
        end
    end