clear;
close all;

files = dir("planets/*");

%check if any files are in this directory
if isempty(files)
    error("No files found in 'Data/'");
end

%gather filenames of all .dat files present
for i = 1:length(files)
    filenames{i} = convertCharsToStrings(files(i).name);
end

hold on
for i = 3:size(files(:,1))
    data = readmatrix("planets/" + filenames(i));
    plot(data(:,2), data(:,3));
end
legend(filenames(3:end), 'Location','bestoutside');
