load mpuCali.mat sensorCalibration;

pp = poseplot;
xlabel("North-x (m)");
ylabel("East-y (m)");
zlabel("Down-z (m)");

%Initialise filter
Fs = 10;
decim = 1;
fuse = ahrsfilter("SampleRate", 10, "DecimationFactor", decim);

%Create orientation matrix
pos = [0 0 0];
for c = 1:size(sensorCalibration, 1)
    reading = sensorCalibration(c, :);
    q = fuse(reading(5:7)*9.81, reading(2:4)*(pi/180), reading(8:10));
    set(pp, Orientation = q, Position = pos);
    drawnow;
end
