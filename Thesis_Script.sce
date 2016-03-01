clear;
File = mgetl("frequency.txt");
Vector = evstr(File);
len= size(Vector);
frequency = len(2)/20;
time_stamp = 10000/frequency;

File = mgetl("experiment_filtering.txt");
Vector = evstr(File);
time_axis = 0:time_stamp/10000:length(Vector)*time_stamp/10000/2;
f = linspace(0,frequency,length(time_axis)); 
n = length(time_axis);
signal_filtered=Vector(1:2:length(Vector));
signal_unfiltered=Vector(2:2:length(Vector));
plot(time_axis(1:length(signal_filtered)),signal_filtered, 'b');
a=gca(); 
a.font_size=3;
mtlb_axis([0,30,-27,27]);
xlabel("Czas [s]", "fontsize",5);
ylabel("Przyśpieszenie [m/s^2]", "fontsize",5);
title("Wykres sygnału przefiltrowanego", "fontsize",5);
xgrid(1, 1, 7);

figure;
plot(time_axis(1:length(signal_unfiltered)),signal_unfiltered, 'r');
a=gca(); 
a.font_size=3;
mtlb_axis([0,30,-27,27]);
xlabel("Czas [s]", "fontsize",5);
ylabel("Przyśpieszenie [m/s^2]", "fontsize",5);
title("Wykres sygnału nieprzefiltrowanego", "fontsize",5);
xgrid(1, 1, 7);

//figure;
//plot(time_axis(1:length(signal_filtered)),signal_filtered, 'b');
//plot(time_axis(1:length(signal_unfiltered)),signal_unfiltered, 'r');
//mtlb_axis([0,30,-27,27]);
//xlabel("Czas [s]", "fontsize",5);
//ylabel("Przyśpieszenie [m/s^2]", "fontsize",5);
//legend("Sygnał przefiltrowany","Sygnał rzeczywisty", "fontsize",5);
//title("Wykres obu sygnałów", "fontsize",5);
//xgrid(1, 1, 7);


figure;
X=fft(signal_filtered)./(length(signal_filtered)/2);
plot(f(1:n/2),abs(X(1:n/2)), 'b');
a=gca(); 
a.font_size=3;
xlabel("Częstotliwość [Hz]", "fontsize",5);
ylabel("Moduł widma", "fontsize",5);
title("Charakterystyka częstotliwościowa sygnału przefiltrowanego", "fontsize",5);
xgrid(1, 1, 7);

figure;
hz = iir(8,'lp','butt',12/frequency,[]);
[hzm,fr]=frmag(hz,256);
fr2 = fr.*frequency;
plot(f(1:n/2),abs(X(1:n/2)),fr2,hzm);
a=gca(); 
a.font_size=3;
xlabel("Częstotliwość [Hz]", "fontsize",5);
ylabel("Moduł widma", "fontsize",5);
title("Charakterystyka sygnału przefiltrowanego i filtru dolnoprzepustowego", "fontsize",5);
xgrid(1, 1, 7);

figure;
y = flts(signal_filtered,hz);
Y = fft(y)./(length(signal_filtered)/2);
plot(f(1:n/2),abs(Y(1:n/2)));
a=gca(); 
a.font_size=3;
xlabel("Częstotliwość [Hz]", "fontsize",5);
ylabel("Moduł widma", "fontsize",5);
title("Charakterystyka częstotliwościowa sygnału dwukrotnie przefiltrowanego", "fontsize",5);
xgrid(1, 1, 7);

figure;
plot(time_axis(1:length(y)), y);
a=gca(); 
a.font_size=3;
mtlb_axis([0,30,-27,27]);
xlabel("Czas [s]", "fontsize",5);
ylabel("Przyśpieszenie [m/s^2]", "fontsize",5);
title("Wykres sygnału podwójnie przefiltrowanego", "fontsize",5);
xgrid(1, 1, 7);


