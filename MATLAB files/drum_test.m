clear;

[y1,fs1] = audioread("Drums/Closed-HiHat.wav");
[y2,fs2] = audioread("Drums/Hand-clap.wav");
[y3,fs3] = audioread("Drums/Kick-drum-1_1.wav");
for i = 1:10
    sound(y3(1105:4608, :), fs3);
    pause(0.25)
    sound(y2(1105:5000, :), fs2);
    pause(0.25)
    sound(y3, fs3);
    pause(0.17)
    sound(y3, fs3);
    pause(0.17)
    sound(y3, fs3);
    pause(0.17)
    sound(y2(1105:5000, :), fs2);
    pause(0.25)
end