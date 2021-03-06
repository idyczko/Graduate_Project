xdel(winsid());
clear;
File = mgetl("frequency_double_measurement.txt");
Vector = evstr(File);
len= size(Vector);
frequency = len(2)/20;
time_stamp = 10000/frequency;

File = mgetl("Experiment_2_top.txt");
Vector = evstr(File);
Vector=Vector(131:length(Vector));
time_axis = 0:time_stamp/10000:length(Vector)*time_stamp/10000/2;
f = linspace(0,frequency,length(time_axis)); 
n = length(time_axis);
top=Vector(1:2:length(Vector));
bottom=Vector(2:2:length(Vector));
plot(time_axis(1:length(top)),top, 'b');
a=gca(); 
a.font_size=3;
xgrid(1, 1, 7);
mtlb_axis([0,5,-80,80]);
title("Wykres sygnału górnego akcelerometru", "fontsize",5);
xlabel("Czas [s]", "fontsize",5);
ylabel("Przyśpieszenie [m/s^2]", "fontsize",5);

figure;
plot(time_axis(1:length(bottom)),bottom, 'r');

title("Wykres sygnału dolnego akcelerometru", "fontsize",5);
a=gca(); 
a.font_size=3;
xgrid(1, 1, 7);
mtlb_axis([0,5,-80,90]);
xlabel("Czas [s]", "fontsize",5);
ylabel("Przyśpieszenie [m/s^2]", "fontsize",5);

figure;
X=fft(top)./(length(top)/2);
plot(f(1:n/2),abs(X(1:n/2)), 'b');
a=gca(); 
a.font_size=3;
xgrid(1, 1, 7);
title("Charakterystyka częstotliwościowa sygnału", "fontsize",5);
xlabel("Częstotliwość [Hz]", "fontsize",5);
ylabel("Moduł widma", "fontsize",5);

figure;
hz = iir(8,'lp','butt',6/frequency,[]);
[hzm,fr]=frmag(hz,256);
fr2 = fr.*frequency;
plot(f(1:n/2),abs(X(1:n/2)),fr2,hzm);
a=gca(); 
a.font_size=3;
xgrid(1, 1, 7);
title("Charakterystyka częstotliwościowa sygnału oraz filtra", "fontsize",5);
xlabel("Częstotliwość [Hz]", "fontsize",5);
ylabel("Moduł widma", "fontsize",5);

figure;
y = flts(top,hz);
Y = fft(y)./(length(top)/2);
plot(f(1:n/2),abs(Y(1:n/2)));
a=gca(); 
a.font_size=3;
xgrid(1, 1, 7);
xlabel("Częstotliwość [Hz]", "fontsize",5);
ylabel("Moduł widma", "fontsize",5);
title("Charakterystyka częstotliwościowa przefiltrowanego sygnału", "fontsize",5);

figure;
plot(time_axis(1:length(y)), y);
a=gca(); 
a.font_size=3;
xgrid(1, 1, 7);
mtlb_axis([0,5,-80,80]);
xlabel("Czas [s]", "fontsize",5);
ylabel("Przyśpieszenie [m/s^2]", "fontsize",5);
title("Wykres przefiltrowanego sygnału górnego akcelerometru", "fontsize",5);


figure;
plot(time_axis, sin(time_axis));

