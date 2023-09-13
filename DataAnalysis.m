clear;
close all;

sun_data = readmatrix("sun.txt");
earth_data = readmatrix("earth.txt");

figure();
plot(earth_data(:,2), earth_data(:,3));
title("Earth");

figure();
plot(sun_data(:,2), sun_data(:,3));
title("Sun");