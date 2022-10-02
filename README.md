#Laufzeit Prognose
Hallo,
Hier einmal ein Walkthrough von meinem Batterie Laufzeit-Prognose Problem.

Zu erst einmal die Frage wo kann ich Status Werte meiner Batterie auslesen?

Das Durchsuchen von meinem /sys/class/ Verzeichnisses gibt die Info:
```
$ ls -al /sys/class/power_supply/BAT0/
drwxr-xr-x 4 root root    0  2. Okt 17:49 .
drwxr-xr-x 3 root root    0  2. Okt 17:49 ..
-rw-r--r-- 1 root root 4096  2. Okt 19:23 alarm
-r--r--r-- 1 root root 4096  2. Okt 17:58 capacity
-r--r--r-- 1 root root 4096  2. Okt 19:23 capacity_level
-rw-r--r-- 1 root root 4096  2. Okt 19:23 charge_control_end_threshold
-rw-r--r-- 1 root root 4096  2. Okt 19:23 charge_control_start_threshold
-rw-r--r-- 1 root root 4096  2. Okt 19:23 charge_start_threshold
-rw-r--r-- 1 root root 4096  2. Okt 19:23 charge_stop_threshold
-r--r--r-- 1 root root 4096  2. Okt 17:58 cycle_count
lrwxrwxrwx 1 root root    0  2. Okt 19:23 device -> ../../../PNP0C0A:00
-r--r--r-- 1 root root 4096  2. Okt 17:50 energy_full
-r--r--r-- 1 root root 4096  2. Okt 17:58 energy_full_design
-r--r--r-- 1 root root 4096  2. Okt 17:50 energy_now
drwxr-xr-x 3 root root    0  2. Okt 17:49 hwmon2
-r--r--r-- 1 root root 4096  2. Okt 17:58 manufacturer
-r--r--r-- 1 root root 4096  2. Okt 17:58 model_name
drwxr-xr-x 2 root root    0  2. Okt 19:23 power
-r--r--r-- 1 root root 4096  2. Okt 17:58 power_now
-r--r--r-- 1 root root 4096  2. Okt 17:58 present
-r--r--r-- 1 root root 4096  2. Okt 17:58 serial_number
-r--r--r-- 1 root root 4096  2. Okt 17:50 status
lrwxrwxrwx 1 root root    0  2. Okt 17:49 subsystem -> ../../../../../../../../../class/power_supply
-r--r--r-- 1 root root 4096  2. Okt 17:58 technology
-r--r--r-- 1 root root 4096  2. Okt 17:50 type
-rw-r--r-- 1 root root 4096  2. Okt 17:49 uevent
-r--r--r-- 1 root root 4096  2. Okt 17:58 voltage_min_design
-r--r--r-- 1 root root 4096  2. Okt 17:58 voltage_now
```
Die Dateien `energy_now` und `energy_full` sind hier Wichtig.
```
$ cat /sys/class/power_supply/BAT0/energy_now
27990000
$ cat /sys/class/power_supply/BAT0/energy_full
45000000
```
Über einen cronjob habe ich dann Minütlich meinen Ladestand tracken lassen.
```
 * * * * * /usr/bin/cat "/sys/class/power_supply/BAT0/energy_now" >> /home/janosch/BatLog_Ascii
```
Die Daten sind in `BatLog_Ascii` und `Graph.png` aufgetragen.
Zur erstellung der Abbildung wurde das Skript `Daten.gnuplot` verwendet.

Zur verkleinerung von Speicherplatz verwendet mein Programm allerding diese art der Speicherung von Daten. Ich habe ein weiteres Programm geschrieben. Welches den Ladestand ausließt und anschließend die Daten (Binär) in die Datei `BatLog_Bin` schreibt. Die Einzelnen Datenpunkte werden in 4-Byte Blöcken direkt Binär in die Date geschrieben.
Entsprechend kann der Inhalt mit `od -t d4 BatLog_Bin` Ausgelesen werden.
```
$ od -t d4 BatLog_Bin
0000000     4870000     4950000     5450000     5950000
0000020     6430000     6920000     7410000     7910000
0000040     8390000     8890000     9380000     9880000
0000060    10360000    10860000    11350000    11840000
0000100    12330000    12830000    13320000    13790000
0000120    14270000    14740000    15190000    15620000
0000140    16060000    16460000    16870000    17270000
0000160    17650000    18030000    18390000    18750000
0000200    19100000    19440000    19760000    20090000
0000220    20390000    20690000    20990000    21280000
0000240    21560000    21820000    22080000    22340000
0000260    22590000    22830000    23060000    23280000
0000300    23500000    23720000    23920000    24130000
0000320    24320000    24510000    24690000    24870000
0000340    25040000    25200000    25370000    25520000
0000360    25660000    25810000    25950000    26080000
0000400    26210000    26340000    26450000    26570000
0000420    26680000    26790000    26890000    27000000
0000440    27090000    27190000    27280000    27370000
0000460    27450000    27540000    27620000    27700000
0000500    27770000    27990000    27990000    27990000
0000520    27990000    27990000    27990000    27990000
*
0000640
```
Wie zusehen, scheint der Inhalt mit denen aus der Encodierten Datei übereinzustimmen.
Quellcode ist in dem Ordner `./ExpandBatteryDataFile` zusehen.
Hier sind nur die Datenpunkte des Letzten Statuses, also die Daten seit dem Aufladen.


