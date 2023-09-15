clear;
close all;
PlanetsToLoad = ["Sun","Mercury","Venus","Earth","Moon"];
hold on
for i = 1:5
    data = readmatrix(PlanetsToLoad(i));
    plot(data(:,2), data(:,3));
end
