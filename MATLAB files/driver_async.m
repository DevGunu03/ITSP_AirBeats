clear;

%Initialise filter
Fs = 5;
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

% Initialise sounds and threshold values
load_drums;
global checkDrum;
checkDrum = 21;

% Define BlueTooth object. The exact name is required
esp32 = bluetooth("Shobhit_ESP32", 1);
flush(esp32);
esp32.configureTerminator("CR");
esp32.UserData = zeros(1, 5);
configureCallback(esp32, "terminator", @collectData);

%Start the actual data collection
esp32.writeline("hello");

function collectData(src, evt)
    global fuse;
    global pp;
    global pos;
    global checkDrum;
    global y1;
    global y2;
    global y3;
    global fs1;
    global fs2;
    global fs3;

    data = src.readline();
    sensorDataNew = cell2mat(arrayfun(@str2num,transpose(split(data)),'uni',0));
    q = fuse(sensorDataNew(5:7)*(-9.81), sensorDataNew(2:4)*(pi/180), sensorDataNew(8:10));
    qprev = quaternion(src.UserData(2:5));
    time = sensorDataNew(1);
    prevTime = src.UserData(1);
    changeQuat = compact(q - qprev)*1000/(time - prevTime);

    %Check if drum is hit
        if checkDrum >= 20
            checkDrum = 0;
            if changeQuat(3) > 10
                sound(y2, fs2);
                disp("Played sound 2");
                pause(0.2);
            elseif changeQuat(3) < -10
                disp("played sound 3");
                sound(y3, fs3);
                pause(0.2);
            else
                checkDrum  = 20;
            end
        else
            checkDrum = checkDrum  +1;
        end

    set(pp, Orientation = q, Position = pos);
    drawnow;
    src.UserData = [sensorDataNew(1), compact(q)] ;
end
