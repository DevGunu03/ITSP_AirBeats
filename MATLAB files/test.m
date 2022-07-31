load mpuCali.mat sensorCalibration;

plot(sensorCalibration)
%legend("ax","ay","az")

%% 

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
for c = 2:size(sensorCalibration, 1)
    reading = sensorCalibration(c, :);
    q = fuse(reading(5:7)*9.81, reading(2:4)*(pi/180), reading(8:10));
<<<<<<< HEAD
    g = [0 0 9.81];
    qg = quaternion([0 g]);
    g_ = q*qg*q.conj;
    [r, g_x, g_y, g_z] = parts(g_)
    set(pp, Orientation = q, Position = pos);
=======
    set(pp, Orientation = quaternion(0, 0, 0, 1), Position = pos);
>>>>>>> 6003d8a7dd059fb03b1363e2de146fbc8a1afef2
    drawnow;
end

mag_array = [];

for c = 1:size(sensorCalibration, 1)
    mag_field_mag = sqrt(sensorCalibration(c,8)^2 + sensorCalibration(c,9)^2 + sensorCalibration(c,10)^2);
    mag_array = [mag_array; mag_field_mag]
end