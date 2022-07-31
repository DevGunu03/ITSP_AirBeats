clear;

<<<<<<< HEAD
[y1,fs1] = audioread("Drums/Closed-HiHat.wav");
[y2,fs2] = audioread("Drums/Hand-clap.wav");
[y3,fs3] = audioread("Drums/Kick-drum-1_1.wav");
=======
[y1,fs1]=audioread("Closed-HiHat.wav");
[y2, fs2] = audioread("Hand-clap.wav");
[y3,fs3] = audioread("Kick-drum-1_1.wav");
>>>>>>> 6003d8a7dd059fb03b1363e2de146fbc8a1afef2
for i = 1:10
    sound(y3(1105:4608, :), fs3);
    pause(0.25)
    sound(y2(1105:5000, :), fs2);
    pause(0.25)
    sound(y3, fs3);
    pause(0.25)
    sound(y3, fs3);
    pause(0.25)
    sound(y3, fs3);
    pause(0.25)
    sound(y2(1105:5000, :), fs2);
    pause(0.25)
end