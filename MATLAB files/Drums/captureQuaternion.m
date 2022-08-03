%Average the value of q over 50 readings

qArray = zeros(50, 4);

for i = 1:50
    qArray(i, :) = compact(esp32.UserData);
end

qAvg = sum(qArray, 1)/50;

save configQ.mat qAvg qArray
clear qAvg qArray i;
