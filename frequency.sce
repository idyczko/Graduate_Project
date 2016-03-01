clear;
File = mgetl("frequency.txt");
Vector = evstr(File);
len= size(Vector);
frequency = len(2)/20;
time_stamp = 10000/frequency;
