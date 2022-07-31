clear;

%table for sensor and quaternion data
sensorCalibrationshake = zeros(200, 10);

%Initialise filter
Fs = 10;
decim = 1;
fuse = ahrsfilter("SampleRate", 10, "DecimationFactor", decim);

% Calibration variables
caliCount = 0;
CaliTimeLimit = 20;

%Initialise pose plot
pp = poseplot;
xlabel("North-x (m)");
ylabel("East-y (m)");
zlabel("Down-z (m)");
%xlim([-2.00 2.00]);
%ylim([-2.00 2.00]);
%zlim([-2.00 2.00]);
pos = [0 0 0];

% Initialise sounds and threshold values
% [y1, fs1] = audioread("Closed-HiHat.wav");
% [y2, fs2] = audioread("Hand-clap.wav");
% [y3, fs3] = audioread("Kick-drum-1_1.wav");
% checkDrum = 21;

% Define BlueTooth object. The exact name is required
esp32 = bluetooth("Shobhit_ESP32", 1);
flush(esp32);
esp32.configureTerminator("CR");
collectVal = 1;
watchdog = 0;

% Receive calibration data
% esp32.writeline("hello");
% while(collectCali)
%     b = esp32.NumBytesAvailable;
%     pause(0.01);
%     if(b > 0)
%         dataC = esp32.readline();
%         sensorDataCali = cell2mat(arrayfun(@str2num,transpose(split(dataC)),'uni',0));
%         sensorCalibration = [sensorCalibration; sensorDataCali(1:10)];
%         caliCounter = caliCounter + 1;
%     else
%         b = 0;
%     end
% 
%     if(caliCounter >= 100)
%         break;
%     end
% 
%     pause(0.001);
% end

% Process and save calibration data
% flush(esp32);
% pause(2);
% save mpuCali.mat sensorCalibration;

%Start the actual data collection
esp32.writeline("hello");

i = 1;
qprev = quaternion(0, 0, 0, 0);
prevTime = 0;

while (collectVal)
    a = esp32.NumBytesAvailable;
    if(a > 0)
        data = esp32.readline();
        watchdog = 0;
        sensorDataNew = cell2mat(arrayfun(@str2num,transpose(split(data)),'uni',0));
        sensorCalibrationshake(caliCount+1, :) = sensorDataNew(1:10); 
        % Accel, Gyro, Magneto. Make quaternion
        q = fuse(sensorDataNew(5:7)*(-9.81), sensorDataNew(2:4)*(pi/180), sensorDataNew(8:10));
        time = sensorDataNew(1);

        %Check if drum is hit
%         if checkDrum >= 20
%             changeQuat = compact(q - qprev)*1000/(time - prevTime);
%             checkDrum = 0;
%             if changeQuat(3) > 15
%                 sound(y2, fs2);
%                 disp("Played sound 2");
%             elseif changeQuat(3) < -15
%                 disp("played sound 3");
%                 sound(y3, fs3);
%             else
%                 checkDrum  = 20;
%             end
%             disp(changeQuat);
%         else
%             checkDrum = checkDrum  +1;
%         end

        % Update poseplot
        set(pp, Orientation = q, Position = pos);
        drawnow

        % Update previous variables
%         qprev = q;
%         prevTime = time;

        caliCount = caliCount + 1;
    else
        watchdog = watchdog + 1;
    end

    if (watchdog > 50000)
        break;
    end

    if (caliCount >= CaliTimeLimit*Fs)
        break;
    end

    pause(0.001);

end

% cleanup
% save quat_data quat_arr;
disp("Exiting data collection loop. Clearing all variables now");
save('mpuCali.mat', 'sensorCalibrationshake', '-append', '-v6');
clear;