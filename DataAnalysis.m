clear;
close all;

sun_data = readmatrix("Sun");
earth_data = readmatrix("Mercury");

%figure();
plot(earth_data(:,2), earth_data(:,3));
%title("Earth");
hold on

%figure();
plot(sun_data(:,2), sun_data(:,3));
%title("Sun");