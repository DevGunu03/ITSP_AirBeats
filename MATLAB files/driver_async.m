clear;

%Initialise filter
Fs = 10;
decim = 1;
global fuse;
fuse = ahrsfilter("SampleRate", 10, "DecimationFactor", decim);

%Initialise pose plot
global pp;
pp = poseplot;
xlabel("North-x (m)");
ylabel("East-y (m)");
zlabel("Down-z (m)");
%xlim([-2.00 2.00]);
%ylim([-2.00 2.00]);
%zlim([-2.00 2.00]);
global pos;
pos = [0 0 0];

% Define BlueTooth object. The exact name is required
esp32 = bluetooth("Shobhit_ESP32", 1);
flush(esp32);
esp32.configureTerminator("CR");
esp32.UserData = quaternion(0, 0, 0, 0);
configureCallback(esp32, "terminator", @collectData);

%Start the actual data collection
esp32.writeline("hello");

function collectData(src, evt)
    global fuse;
    global pp;
    global pos;
    data = src.readline();
    sensorDataNew = cell2mat(arrayfun(@str2num,transpose(split(data)),'uni',0));
    q = fuse(sensorDataNew(5:7)*(-9.81), sensorDataNew(2:4)*(pi/180), sensorDataNew(8:10));
    set(pp, Orientation = q, Position = pos);
    drawnow
    src.UserData = sensorDataNew;
end
