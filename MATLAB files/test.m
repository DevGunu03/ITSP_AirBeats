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
    g = [0 0 9.81];
    qg = quaternion([0 g]);
    g_ = q*qg*q.conj;
    [r, g_x, g_y, g_z] = parts(g_)
    set(pp, Orientation = q, Position = pos);
    drawnow;
end
