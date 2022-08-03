clear;

%Initialise filter
Fs = 20;
decim = 1;
global fuse;
fuse = ahrsfilter("SampleRate", Fs, "DecimationFactor", decim);

%Initialise pose plot
global pp;
pp = poseplot;
xlabel("North-x (m)");
ylabel("East-y (m)");
zlabel("Down-z (m)");
global pos;
pos = [0 0 0];

% Initialise sounds and threshold values
load drumsounds.mat;

% Define BlueTooth object. The exact name is required
esp32 = bluecd Airbwtooth("Shobhit_ESP32", 1);
flush(esp32);
esp32.configureTerminator("CR");
configureCallback(esp32, "terminator", @collectData);

%Start data collection
esp32.writeline("Hello");

function collectData(src, evt)
    global fuse;
    global pp;
    global pos;
    %global checkDrum;
    global y_KickD;
    global y_HiHat;
    global y_HandC;
    global f_KickD;
    global f_HiHat;
    global f_HandC;
    
    data = src.readline();
    sensorDataNew = cell2mat(arrayfun(@str2num,transpose(split(data)),'uni',0));
    q = fuse(sensorDataNew(5:7)*(-9.81), sensorDataNew(2:4)*(pi/180), sensorDataNew(8:10));
    set(pp, Orientation = q, Position = pos);
    drawnow
    src.UserData = q;  
    disp(q);
end
