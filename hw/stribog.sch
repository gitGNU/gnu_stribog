v 20050820 1
C 41200 60900 1 0 0 lpc2138.sym
{
T 45750 65050 5 17 1 1 0 2 1
refdes=U1
T 41200 60900 5 10 0 0 0 0 1
footprint=QFP64
T 41200 60900 5 10 0 0 0 0 1
value=LPC2138
T 45200 63800 14 10 1 1 0 0 1
comment=can be replaced with LPC2134 or LPC2136
}
C 32100 62850 1 0 1 hmc1022.sym
{
T 31700 67750 5 10 1 1 0 6 1
refdes=U2
T 32100 63750 5 10 0 2 0 6 1
footprint=SO16
T 32100 62850 5 10 0 0 0 0 1
value=HMC1022
}
C 32850 57650 1 0 0 hmc1021.sym
{
T 33250 62550 5 10 1 1 0 0 1
refdes=U3
T 34850 59650 5 10 0 2 0 0 1
footprint=hmc1021z
T 32850 57650 5 10 0 0 0 0 1
value=HMC1021Z
}
C 52850 73100 1 0 0 header10-2.sym
{
T 53450 75200 5 10 1 1 0 0 1
refdes=J1
T 52850 73100 5 10 0 0 0 0 1
footprint=2.5mm_10pin_header
}
C 44700 70400 1 0 0 crystal-1.sym
{
T 44650 70700 5 10 1 1 0 0 1
refdes=ZQ1
T 45200 70700 5 10 1 1 0 0 1
value=14.7456MHz
T 44700 70400 5 10 0 0 0 0 1
footprint=crystal
}
N 45400 70500 45400 67900 4
N 45000 67900 45000 69900 4
N 45000 69900 44700 69900 4
N 44700 69900 44700 70500 4
C 45500 69900 1 0 0 capacitor-1.sym
{
T 45700 70400 5 10 1 1 0 0 1
refdes=C1
T 45700 69650 5 10 1 1 0 0 1
value=22
T 45500 69900 5 10 0 0 0 0 1
footprint=0603
}
C 43700 69900 1 0 0 capacitor-1.sym
{
T 43900 70400 5 10 1 1 0 0 1
refdes=C2
T 44300 70200 5 10 1 1 0 0 1
value=22
T 43700 69900 5 10 0 0 0 0 1
footprint=0603
}
N 44700 70100 44600 70100 4
N 45400 70100 45500 70100 4
C 46500 70650 1 180 0 gnd-1.sym
C 43300 70200 1 270 0 gnd-1.sym
N 46400 70100 46400 70350 4
N 43600 70100 43700 70100 4
C 45300 54000 1 0 0 adxl210.sym
{
T 46800 58700 5 10 1 1 0 0 1
refdes=U4
T 45800 56100 5 10 0 0 0 0 1
footprint=adxl210
T 45300 54000 5 10 0 0 0 0 1
value=ADXL210AE
}
C 47450 57200 1 0 0 capacitor-1.sym
{
T 47500 57550 5 10 1 1 0 0 1
refdes=C3
T 48050 57500 5 10 1 1 0 0 1
value=0.1
T 47450 57200 5 10 0 0 0 0 1
footprint=0603
}
C 48750 57300 1 90 0 gnd-1.sym
N 48450 57400 48350 57400 4
C 47400 56700 1 0 0 capacitor-1.sym
{
T 47450 56550 5 10 1 1 0 0 1
refdes=C4
T 48000 56600 5 10 1 1 0 0 1
value=0.1
T 47400 56700 5 10 0 0 0 0 1
footprint=0603
}
C 48700 56800 1 90 0 gnd-1.sym
N 48400 56900 48300 56900 4
N 47200 57400 47450 57400 4
{
T 47400 57400 5 10 0 0 0 0 1
netname=xfilt
}
N 47400 56900 47200 56900 4
{
T 48000 56900 5 10 0 0 0 0 1
netname=yfilt
}
C 44400 57800 1 0 0 resistor-2.sym
{
T 44600 58100 5 10 1 1 0 0 1
refdes=R1
T 44800 57600 5 10 1 1 0 0 1
value=1M
T 44400 57800 5 10 0 0 0 0 1
footprint=0603
}
N 45300 57900 45400 57900 4
C 44300 56300 1 0 0 gnd-1.sym
N 44400 56600 44400 57900 4
N 44400 56900 45400 56900 4
N 45400 57400 44400 57400 4
C 44000 58300 1 90 1 capacitor-1.sym
{
T 44000 58100 5 10 1 1 0 0 1
refdes=C5
T 44000 57600 5 10 1 1 180 6 1
value=0.1
T 44000 58300 5 10 0 0 0 0 1
footprint=0603
}
N 43800 58400 43800 58300 4
N 43800 57400 43800 56900 4
C 56000 74200 1 0 0 gnd-1.sym
T 53350 74900 9 9 1 0 0 4 1
GND
T 53750 74900 9 9 1 0 0 4 1
+12V
T 53750 74100 9 9 1 0 0 4 1
Tx0
T 53350 74500 9 9 1 0 0 4 1
Tx1
T 53350 74100 9 9 1 0 0 4 1
Rx0
T 53750 74500 9 9 1 0 0 4 1
Rx1
T 53750 73300 9 9 1 0 0 4 1
SCL
T 53750 73700 9 9 1 0 0 4 1
SDA
T 53350 73700 9 9 1 0 0 4 1
A
T 53350 73300 9 9 1 0 0 4 1
B
C 30900 63850 1 0 0 gnd-1.sym
C 30100 63850 1 0 0 gnd-1.sym
C 30500 63850 1 270 0 capacitor-1.sym
{
T 30800 63600 5 10 1 1 0 0 1
refdes=C6
T 31000 63350 5 10 1 1 0 0 1
value=0.1
T 30500 63850 5 10 0 0 0 0 1
footprint=0603
}
C 29700 63850 1 270 0 capacitor-1.sym
{
T 29550 63550 5 10 1 1 0 0 1
refdes=C7
T 30000 63550 5 10 1 1 0 0 1
value=0.1
T 29700 63850 5 10 0 0 0 0 1
footprint=0603
}
N 29900 62950 29900 62750 4
C 32750 59750 1 270 0 capacitor-1.sym
{
T 33150 59450 5 10 1 1 0 0 1
refdes=C8
T 33150 58950 5 10 1 1 0 0 1
value=0.1
T 32750 59750 5 10 0 0 0 0 1
footprint=0603
}
C 34350 59150 1 0 0 gnd-1.sym
C 32600 66050 1 90 1 gnd-1.sym
C 28000 65850 1 270 1 gnd-1.sym
N 32950 60250 32950 59750 4
N 34450 59750 34450 59450 4
N 32300 65950 32000 65950 4
N 28300 65950 28600 65950 4
N 30500 67750 29300 67750 4
N 30500 67750 30500 68500 4
{
T 30850 68550 5 10 1 1 0 6 1
netname=+5V
}
C 32550 60750 1 270 0 gnd-1.sym
N 32850 60650 32950 60650 4
N 34450 62550 34450 63250 4
{
T 34500 63300 5 10 1 1 0 0 1
netname=+5V
}
C 37350 61050 1 0 0 ina118.sym
{
T 37250 61000 5 10 1 1 0 0 1
refdes=U5
T 37350 61050 5 10 0 0 0 0 1
footprint=SO8
T 37350 61050 5 10 0 0 0 0 1
value=INA118UB
}
C 35300 61450 1 0 0 capacitor-1.sym
{
T 35350 61800 5 10 1 1 0 0 1
refdes=C11
T 35850 61350 5 10 1 1 0 0 1
value=2.2; 5%
T 35300 61450 5 10 0 0 0 0 1
footprint=0805
}
C 36800 62700 1 0 0 resistor-2.sym
{
T 37000 62950 5 10 1 1 0 0 1
refdes=R4
T 37400 62950 5 10 1 1 0 0 1
value=200k
T 36800 62700 5 10 0 0 0 0 1
footprint=0603
}
C 36650 62050 1 0 0 resistor-2.sym
{
T 36850 62350 5 10 1 1 0 0 1
refdes=R5
T 36700 61800 5 10 1 1 0 0 1
value=200k
T 36650 62050 5 10 0 0 0 0 1
footprint=0603
}
C 35200 60850 1 0 0 capacitor-1.sym
{
T 35250 61200 5 10 1 1 0 0 1
refdes=C12
T 35200 60650 5 10 1 1 0 0 1
value=2.2; 5%
T 35200 60850 5 10 0 0 0 0 1
footprint=0805
}
C 38150 60650 1 0 0 resistor-2.sym
{
T 38350 60950 5 10 1 1 0 0 1
refdes=R6
T 38550 60450 5 10 1 1 0 0 1
value=24
T 38150 60650 5 10 0 0 0 0 1
footprint=0603
}
N 35150 61050 35200 61050 4
N 35150 61650 35300 61650 4
N 36200 61650 37350 61650 4
N 36100 61050 36600 61050 4
N 36600 61250 37350 61250 4
C 37750 60300 1 0 0 gnd-1.sym
N 37850 60600 37850 61050 4
N 36600 61050 36600 62150 4
N 36650 62150 36600 62150 4
N 36400 62800 36400 61650 4
N 37700 62800 39800 62800 4
{
T 39350 62950 5 10 1 1 0 0 1
netname=OpRef
}
N 36800 62800 36400 62800 4
N 38050 61150 38050 60750 4
N 38050 60750 38150 60750 4
N 38050 61750 39150 61750 4
N 39150 61750 39150 60750 4
N 39150 60750 39050 60750 4
C 35550 66250 1 0 0 ina118.sym
{
T 35400 66200 5 10 1 1 0 0 1
refdes=U6
T 35550 66250 5 10 0 0 0 0 1
footprint=SO8
T 35550 66250 5 10 0 0 0 0 1
value=INA118UB
}
C 33200 66650 1 0 0 capacitor-1.sym
{
T 33150 67100 5 10 1 1 0 0 1
refdes=C13
T 33650 67100 5 10 1 1 0 0 1
value=2.2; 5%
T 33200 66650 5 10 0 0 0 0 1
footprint=0805
}
C 35000 67900 1 0 0 resistor-2.sym
{
T 35000 68200 5 10 1 1 0 0 1
refdes=R7
T 35400 68200 5 10 1 1 0 0 1
value=200k
T 35000 67900 5 10 0 0 0 0 1
footprint=0603
}
C 34850 67350 1 0 0 resistor-2.sym
{
T 35050 67650 5 10 1 1 0 0 1
refdes=R8
T 34900 67100 5 10 1 1 0 0 1
value=200k
T 34850 67350 5 10 0 0 0 0 1
footprint=0603
}
C 33050 66050 1 0 0 capacitor-1.sym
{
T 33100 66400 5 10 1 1 0 0 1
refdes=C14
T 33650 66350 5 10 1 1 0 0 1
value=2.2; 5%
T 33050 66050 5 10 0 0 0 0 1
footprint=0805
}
C 36450 65850 1 0 0 resistor-2.sym
{
T 36650 66150 5 10 1 1 0 0 1
refdes=R9
T 36850 65650 5 10 1 1 0 0 1
value=24
T 36450 65850 5 10 0 0 0 0 1
footprint=0603
}
N 34100 66850 35550 66850 4
N 33950 66250 34750 66250 4
N 34750 66450 35550 66450 4
C 35950 65300 1 0 0 gnd-1.sym
N 36050 65600 36050 66250 4
N 34750 66250 34750 67450 4
N 34850 67450 34750 67450 4
N 34550 68000 34550 66850 4
N 35900 67450 35750 67450 4
N 35000 68000 34550 68000 4
N 36250 66350 36250 65950 4
N 36250 65950 36450 65950 4
N 36250 66950 37450 66950 4
N 37450 66950 37450 65950 4
N 37450 65950 37350 65950 4
C 36050 69550 1 0 0 ina118.sym
{
T 35950 69500 5 10 1 1 0 0 1
refdes=U7
T 36050 69550 5 10 0 0 0 0 1
footprint=SO8
T 36050 69550 5 10 0 0 0 0 1
value=INA118UB
}
C 33600 69950 1 0 0 capacitor-1.sym
{
T 33550 70300 5 10 1 1 0 0 1
refdes=C15
T 34200 70300 5 10 1 1 0 0 1
value=2.2; 5%
T 33600 69950 5 10 0 0 0 0 1
footprint=0805
}
C 35400 71200 1 0 0 resistor-2.sym
{
T 35500 71500 5 10 1 1 0 0 1
refdes=R10
T 36050 71500 5 10 1 1 0 0 1
value=200k
T 35400 71200 5 10 0 0 0 0 1
footprint=0603
}
C 35350 70550 1 0 0 resistor-2.sym
{
T 35400 70850 5 10 1 1 0 0 1
refdes=R11
T 35350 70300 5 10 1 1 0 0 1
value=200k
T 35350 70550 5 10 0 0 0 0 1
footprint=0603
}
C 33000 69350 1 0 0 capacitor-1.sym
{
T 33000 69650 5 10 1 1 0 0 1
refdes=C16
T 33650 69650 5 10 1 1 0 0 1
value=2.2; 5%
T 33000 69350 5 10 0 0 0 0 1
footprint=0805
}
C 36950 69150 1 0 0 resistor-2.sym
{
T 37150 69450 5 10 1 1 0 0 1
refdes=R12
T 37350 68950 5 10 1 1 0 0 1
value=24
T 36950 69150 5 10 0 0 0 0 1
footprint=0603
}
N 33900 69550 35000 69550 4
C 36450 68600 1 0 0 gnd-1.sym
N 36550 68900 36550 69550 4
N 35350 70650 35250 70650 4
N 36400 70650 36250 70650 4
N 36750 69650 36750 69250 4
N 36750 69250 36950 69250 4
N 36750 70250 37950 70250 4
N 37950 70250 37950 69250 4
N 37950 69250 37850 69250 4
C 42850 72350 1 0 0 gnd-1.sym
N 42950 72850 42950 72650 4
C 41150 75100 1 90 1 capacitor-1.sym
{
T 40750 74800 5 10 1 1 0 6 1
refdes=C17
T 40450 74450 5 10 1 1 180 6 1
value=0.47
T 41150 75100 5 10 0 0 0 0 1
footprint=0603
}
C 37200 70600 1 0 0 capacitor-1.sym
{
T 37200 70600 5 10 1 1 0 0 1
refdes=C18
T 37800 70500 5 10 1 1 0 0 1
value=0.47
T 37200 70600 5 10 0 0 0 0 1
footprint=0603
}
C 36850 67300 1 0 0 capacitor-1.sym
{
T 36850 67650 5 10 1 1 0 0 1
refdes=C19
T 37450 67200 5 10 1 1 0 0 1
value=0.47
T 36850 67300 5 10 0 0 0 0 1
footprint=0603
}
N 37750 67500 38000 67500 4
C 38700 62100 1 0 0 capacitor-1.sym
{
T 38650 62450 5 10 1 1 0 0 1
refdes=C20
T 39300 62000 5 10 1 1 0 0 1
value=0.47
T 38700 62100 5 10 0 0 0 0 1
footprint=0603
}
N 39600 62300 39800 62300 4
N 37850 62300 38700 62300 4
N 37850 61850 37850 62300 4
N 37550 62150 37700 62150 4
N 36050 67050 36050 67500 4
N 36050 67500 36850 67500 4
N 36400 70450 36400 71300 4
N 36550 70800 37200 70800 4
N 36550 70350 36550 71000 4
{
T 36600 70950 5 10 1 1 0 0 1
netname=A+3.3V
}
N 37100 69950 38400 69950 4
N 38400 64200 38400 69950 4
N 38400 64200 41200 64200 4
N 41200 63800 38000 63800 4
N 38000 63800 38000 66650 4
N 38000 66650 36600 66650 4
N 38400 61450 40200 61450 4
C 55000 73400 1 0 0 capacitor-1.sym
{
T 55250 73950 5 10 1 1 0 0 1
refdes=C21
T 55650 73850 5 10 1 1 0 0 1
value=0.47
T 55000 73400 5 10 0 0 0 0 1
footprint=0603
}
C 58200 73400 1 0 0 capacitor-1.sym
{
T 58150 73700 5 10 1 1 0 0 1
refdes=C22
T 58800 73300 5 10 1 1 0 0 1
value=0.47
T 58200 73400 5 10 0 0 0 0 1
footprint=0603
}
C 58200 72600 1 0 0 capacitor-1.sym
{
T 58150 72900 5 10 1 1 0 0 1
refdes=C23
T 58800 72500 5 10 1 1 0 0 1
value=0.47
T 58200 72600 5 10 0 0 0 0 1
footprint=0603
}
C 27850 60700 1 0 0 irlml.sym
{
T 27900 61550 5 10 1 1 0 0 1
refdes=Q1
T 27300 60800 5 9 1 1 0 0 1
device=IRLML2402
T 27850 60700 5 10 0 0 0 6 1
footprint=SOT23
T 27850 60700 5 10 0 0 0 0 1
value=IRLML2402
T 27250 60600 14 6 1 1 0 0 1
comment=IRLML2803 fits, too
}
C 28350 60250 1 0 0 gnd-1.sym
N 28450 60550 28450 60700 4
N 55100 75500 54250 75500 4
N 54250 75500 54250 74900 4
N 55600 75500 57450 75500 4
{
T 57450 75550 5 10 1 1 0 0 1
netname=+12V
}
C 55000 72600 1 0 0 capacitor-1.sym
{
T 54950 73000 5 10 1 1 0 0 1
refdes=C24
T 55600 72900 5 10 1 1 0 0 1
value=0.47
T 55000 72600 5 10 0 0 0 0 1
footprint=0603
}
N 58000 72800 58200 72800 4
N 58000 73600 58200 73600 4
N 55900 73600 56000 73600 4
N 55000 73600 55000 73200 4
N 55000 73200 56000 73200 4
N 55900 72800 56000 72800 4
N 55000 72800 55000 72400 4
N 55000 72400 56000 72400 4
C 58200 69400 1 0 0 capacitor-1.sym
{
T 58200 69750 5 10 1 1 0 0 1
refdes=C25
T 58800 69300 5 10 1 1 0 0 1
value=0.47
T 58200 69400 5 10 0 0 0 0 1
footprint=0603
}
N 58000 69600 58200 69600 4
N 59100 70200 59100 69600 4
C 58000 69000 1 0 0 gnd-1.sym
N 58100 69300 58100 69600 4
N 58000 70200 59400 70200 4
{
T 59400 70200 5 10 1 1 0 0 1
netname=+5V
}
N 56000 72000 54450 72000 4
N 52550 71200 56000 71200 4
N 56000 71600 52750 71600 4
N 52750 71600 52750 74100 4
N 54550 74500 54550 70800 4
N 54550 70800 56000 70800 4
C 54200 67500 1 0 0 adm202.sym
{
T 57700 74000 5 10 1 1 0 6 1
refdes=U8
T 54200 67500 5 10 0 0 0 0 1
footprint=SO16
T 54200 67500 5 10 0 0 0 0 1
value=ADM202[AJ]R
}
C 54600 74750 1 0 0 bat54c.sym
{
T 55200 75700 5 12 1 1 0 0 1
refdes=D1
T 54600 74750 5 10 0 0 0 0 1
footprint=SOT23
T 54600 74750 5 10 0 0 0 0 1
value=BAT54C
}
N 36450 67500 36450 67200 4
{
T 36500 67150 5 10 1 1 0 0 1
netname=A+3.3V
}
N 38250 62300 38250 61950 4
{
T 38300 61950 5 10 1 1 0 0 1
netname=A+3.3V
}
N 42550 56900 42550 57400 4
N 42550 56900 44400 56900 4
N 42550 58300 42550 58400 4
C 59700 72700 1 90 0 gnd-1.sym
N 59400 72800 59100 72800 4
N 59100 73600 59400 73600 4
{
T 59450 73600 5 10 1 1 0 0 1
netname=+5V
}
C 49400 58300 1 0 0 3.3V-plus-1.sym
N 49600 58300 50300 58300 4
C 49800 58000 1 90 1 capacitor-1.sym
{
T 49750 57750 5 10 1 1 0 0 1
refdes=C26
T 49800 57400 5 10 1 1 180 6 1
value=0.47
T 49800 58000 5 10 0 0 0 0 1
footprint=0603
}
N 49600 58300 49600 58000 4
C 49500 56350 1 0 0 gnd-1.sym
C 52100 57600 1 0 0 gnd-1.sym
N 49600 57100 49600 56650 4
N 52100 58300 52200 58300 4
N 52400 67000 52000 67000 4
{
T 52400 67000 5 10 1 1 0 0 1
netname=A
}
C 50200 55400 1 0 0 lm74.sym
{
T 50600 60100 5 10 1 1 0 0 1
refdes=U9
T 50200 55400 5 10 0 0 0 0 1
footprint=SO8
T 50200 55400 5 10 0 0 0 0 1
value=LM74CIM-3
}
C 48700 71100 1 0 0 dac7612.sym
{
T 49100 75800 5 10 1 1 0 0 1
refdes=U10
T 48700 71100 5 10 0 0 0 0 1
footprint=SO8
T 48700 71100 5 10 0 0 0 0 1
value=DAC7612U
}
C 48900 68200 1 0 0 dac7612.sym
{
T 49300 72900 5 10 1 1 0 0 1
refdes=U11
T 48900 68200 5 10 0 0 0 0 1
footprint=SO8
T 48900 68200 5 10 0 0 0 0 1
value=DAC7612U
}
C 47500 58700 1 90 0 resistor-2.sym
{
T 47600 59200 5 10 1 1 0 0 1
refdes=R15
T 47600 58900 5 10 1 1 0 0 1
value=10k
T 47500 58700 5 10 0 0 0 0 1
footprint=0603
}
C 48700 58700 1 90 0 resistor-2.sym
{
T 48800 59200 5 10 1 1 0 0 1
refdes=R16
T 48800 58900 5 10 1 1 0 0 1
value=10k
T 48700 58700 5 10 0 0 0 0 1
footprint=0603
}
N 47400 58400 47400 58700 4
{
T 47400 57800 5 10 0 0 0 0 1
netname=xout
}
N 47400 59600 47400 60900 4
N 48600 59600 48600 60900 4
C 49100 70700 1 0 1 gnd-1.sym
C 48900 73100 1 0 1 gnd-1.sym
N 48800 73400 48800 74000 4
N 49000 71000 49000 71100 4
N 47000 72600 49000 72600 4
N 47400 72100 49000 72100 4
N 47400 75000 48800 75000 4
N 47000 75500 48800 75500 4
C 50900 70400 1 0 1 gnd-1.sym
C 50700 73100 1 0 1 gnd-1.sym
N 50600 74000 50600 73400 4
N 50800 71100 50800 70700 4
C 49150 69700 1 90 0 resistor-2.sym
{
T 49250 70200 5 10 1 1 0 0 1
refdes=R17
T 49250 69900 5 10 1 1 0 0 1
value=220k
T 49150 69700 5 10 0 0 0 0 1
footprint=0603
}
C 47500 69700 1 90 0 resistor-2.sym
{
T 47600 70200 5 10 1 1 0 0 1
refdes=R18
T 47600 69900 5 10 1 1 0 0 1
value=220k
T 47500 69700 5 10 0 0 0 0 1
footprint=0603
}
C 46700 69700 1 90 0 resistor-2.sym
{
T 46800 70200 5 10 1 1 0 0 1
refdes=R19
T 46800 69900 5 10 1 1 0 0 1
value=220k
T 46700 69700 5 10 0 0 0 0 1
footprint=0603
}
C 48300 69700 1 90 0 resistor-2.sym
{
T 48400 70200 5 10 1 1 0 0 1
refdes=R20
T 48400 69900 5 10 1 1 0 0 1
value=220k
T 48300 69700 5 10 0 0 0 0 1
footprint=0603
}
N 47400 69200 47400 69700 4
N 47400 70600 47400 75000 4
N 47000 70800 47000 75500 4
C 46000 74400 1 0 0 resistor-2.sym
{
T 46200 74700 5 10 1 1 0 0 1
refdes=R21
T 46400 74200 5 10 1 1 0 0 1
value=330k
T 46000 74400 5 10 0 0 0 0 1
footprint=0603
}
C 46000 72500 1 0 0 resistor-2.sym
{
T 46200 72800 5 10 1 1 0 0 1
refdes=R22
T 46400 72300 5 10 1 1 0 0 1
value=330k
T 46000 72500 5 10 0 0 0 0 1
footprint=0603
}
C 46000 73550 1 0 0 resistor-2.sym
{
T 46200 73850 5 10 1 1 0 0 1
refdes=R23
T 46400 73350 5 10 1 1 0 0 1
value=330k
T 46000 73550 5 10 0 0 0 0 1
footprint=0603
}
C 46000 71500 1 0 0 resistor-2.sym
{
T 46200 71800 5 10 1 1 0 0 1
refdes=R24
T 46400 71300 5 10 1 1 0 0 1
value=330k
T 46000 71500 5 10 0 0 0 0 1
footprint=0603
}
N 46900 71600 49000 71600 4
N 46900 74500 48800 74500 4
N 45800 74500 45800 71600 4
N 45800 71600 46000 71600 4
N 46000 73650 45800 73650 4
N 46000 72600 45800 72600 4
N 52100 58800 52200 58800 4
N 52100 59300 52200 59300 4
N 52200 57900 52200 59800 4
N 52200 59800 52100 59800 4
N 45300 74500 46000 74500 4
{
T 45300 74500 5 10 1 1 0 6 1
netname=+5V
}
C 42350 58300 1 270 0 capacitor-4.sym
{
T 42850 58050 5 10 1 1 0 0 1
refdes=C27
T 42700 57550 5 10 1 1 0 0 1
value=3.3; 10V
T 42350 58300 5 10 0 0 0 0 1
footprint=tanA
}
C 55900 75500 1 270 0 capacitor-4.sym
{
T 56400 75250 5 10 1 1 0 0 1
refdes=C28
T 56250 74750 5 10 1 1 0 0 1
value=10.0; 25V
T 55900 75500 5 10 0 0 0 0 1
footprint=tanC
}
C 40200 54000 1 0 0 ref195.sym
{
T 40600 58700 5 10 1 1 0 0 1
refdes=U12
T 40200 54000 5 10 0 0 0 0 1
footprint=SO8
T 40200 54000 5 10 0 0 0 0 1
value=REF195[EFG]S
}
C 37900 57800 1 270 0 capacitor-4.sym
{
T 38400 57550 5 10 1 1 0 0 1
refdes=C29
T 38250 57050 5 10 1 1 0 0 1
value=10.0; 25V
T 37900 57800 5 10 0 0 0 0 1
footprint=tanC
}
C 39600 57800 1 90 1 capacitor-1.sym
{
T 39600 57600 5 10 1 1 0 0 1
refdes=C30
T 39600 57100 5 10 1 1 180 6 1
value=0.1
T 39600 57800 5 10 0 0 0 0 1
footprint=0603
}
N 38100 56900 40300 56900 4
N 40300 57900 38100 57900 4
N 38100 57900 38100 57800 4
N 39400 57900 39400 58200 4
{
T 39400 58200 5 10 1 1 0 0 1
netname=+12V
}
C 39300 56400 1 0 0 gnd-1.sym
N 39400 56700 39400 56900 4
N 42100 58400 45400 58400 4
N 42550 58400 42550 58700 4
{
T 42400 58750 5 10 1 1 0 0 1
netname=A+5V
}
C 51600 71600 1 90 1 capacitor-1.sym
{
T 51550 71400 5 10 1 1 0 0 1
refdes=C31
T 51600 71000 5 10 1 1 180 6 1
value=0.47
T 51600 71600 5 10 0 0 0 0 1
footprint=0603
}
C 51600 74500 1 90 1 capacitor-1.sym
{
T 51550 74300 5 10 1 1 0 0 1
refdes=C32
T 51600 73900 5 10 1 1 180 6 1
value=0.47
T 51600 74500 5 10 0 0 0 0 1
footprint=0603
}
N 51400 70700 50800 70700 4
N 51400 73600 50600 73600 4
N 50600 74500 52000 74500 4
{
T 52000 74500 5 10 1 1 0 0 1
netname=+5V
}
N 50800 71600 52000 71600 4
{
T 52000 71600 5 10 1 1 0 0 1
netname=+5V
}
N 40100 56100 40100 57400 4
N 40100 57400 40300 57400 4
N 40100 56100 49200 56100 4
N 49200 56100 49200 60200 4
C 58200 70700 1 0 0 resistor-2.sym
{
T 58400 71000 5 10 1 1 0 0 1
refdes=R25
T 58600 70500 5 10 1 1 0 0 1
value=10k
T 58200 70700 5 10 0 0 0 0 1
footprint=0603
}
C 58200 71500 1 0 0 resistor-2.sym
{
T 58400 71800 5 10 1 1 0 0 1
refdes=R26
T 58600 71300 5 10 1 1 0 0 1
value=10k
T 58200 71500 5 10 0 0 0 0 1
footprint=0603
}
N 58000 70800 58200 70800 4
N 58000 71600 58200 71600 4
N 59100 70800 59600 70800 4
{
T 59400 70800 5 10 1 1 0 0 1
netname=Rx0
}
N 58000 71200 59600 71200 4
{
T 59350 71200 5 10 1 1 0 0 1
netname=Tx0
}
N 59100 71600 59600 71600 4
{
T 59400 71600 5 10 1 1 0 0 1
netname=Rx1
}
N 58000 72000 59600 72000 4
{
T 59350 72000 5 10 1 1 0 0 1
netname=Tx1
}
C 52300 66100 1 0 0 lp2980AIM5-5.sym
{
T 52700 70800 5 10 1 1 0 0 1
refdes=U13
T 52300 66100 5 10 0 0 0 0 1
footprint=lp2980
}
C 56400 67600 1 270 0 capacitor-4.sym
{
T 56900 67350 5 10 1 1 0 0 1
refdes=C33
T 56750 66850 5 10 1 1 0 0 1
value=10.0; 10V
T 56400 67600 5 10 0 0 0 0 1
footprint=tanA
}
C 54400 70500 1 270 0 capacitor-4.sym
{
T 54900 70150 5 10 1 1 0 0 1
refdes=C34
T 54750 69750 5 10 1 1 0 0 1
value=10.0; 10V
T 54400 70500 5 10 0 0 0 0 1
footprint=tanA
}
C 54500 69000 1 0 0 gnd-1.sym
C 56500 66250 1 0 0 gnd-1.sym
N 56600 66700 56600 66550 4
N 56600 67650 56600 67600 4
N 54200 70500 55000 70500 4
{
T 55100 70500 5 10 1 1 0 0 1
netname=+5V
}
N 56200 67650 57350 67650 4
C 54300 63250 1 0 0 lp2980AIM5-3.sym
{
T 54700 67950 5 10 1 1 0 0 1
refdes=U14
T 54300 63250 5 10 0 0 0 0 1
footprint=lp2980
}
N 54600 69300 54600 69600 4
N 54200 67650 54200 66650 4
N 54200 66650 54400 66650 4
N 53800 67650 54400 67650 4
{
T 53800 67650 5 10 1 1 0 6 1
netname=+12V
}
C 53700 66650 1 0 0 gnd-1.sym
N 53800 66950 53800 67150 4
N 53800 67150 54400 67150 4
N 52400 70500 52100 70500 4
{
T 52100 70500 5 10 1 1 0 6 1
netname=+12V
}
C 51900 69650 1 0 0 gnd-1.sym
N 52000 69950 52000 70000 4
N 52000 70000 52400 70000 4
N 49000 67900 49000 69500 4
N 49000 69500 52400 69500 4
C 57150 67650 1 0 0 3.3V-plus-1.sym
C 32300 65550 1 0 0 resistor-2.sym
{
T 32850 65800 5 10 1 1 0 0 1
refdes=R27
T 32800 65300 5 10 1 1 0 0 1
value=499; 0.1%
T 32300 65550 5 10 0 0 0 0 1
footprint=0.125W_resistor
T 32300 65550 5 10 0 1 0 0 1
comment=precise value is not important; stability is essential
}
N 28600 64850 27700 64850 4
{
T 27650 64850 5 10 1 1 0 6 1
netname=2.048V
}
N 32000 64850 32500 64850 4
{
T 32500 64850 5 10 1 1 0 0 1
netname=2.048V
}
C 27400 65750 1 180 1 resistor-2.sym
{
T 27500 66000 5 10 1 1 180 6 1
refdes=R28
T 27600 65450 5 10 1 1 180 6 1
value=499; 0.1%
T 27400 65750 5 10 0 0 180 6 1
footprint=0.125W_resistor
T 27400 65750 5 10 0 1 0 0 1
comment=precise value is not important; stability is essential
}
N 32950 61050 31650 61050 4
{
T 32100 61050 5 10 1 1 0 6 1
netname=2.048V
}
C 31800 61750 1 0 0 resistor-2.sym
{
T 31850 62000 5 10 1 1 0 0 1
refdes=R29
T 32200 61550 5 10 1 1 0 0 1
value=499; 0.1%
T 31800 61750 5 10 0 0 0 0 1
footprint=0.125W_resistor
T 31800 61750 5 10 0 1 0 0 1
comment=precise value is not important; stability is essential
}
N 27400 65650 27100 65650 4
{
T 27250 65900 5 10 1 1 180 0 1
netname=DAC1
}
N 31800 61850 31400 61850 4
{
T 31700 61850 5 10 1 1 0 6 1
netname=DAC0
}
N 33200 65650 33600 65650 4
{
T 33650 65650 5 10 1 1 0 0 1
netname=DAC2
}
N 50800 72100 51600 72100 4
{
T 51650 72150 5 10 1 1 0 0 1
netname=2.048V
}
N 50800 72600 51550 72600 4
{
T 51600 72600 5 10 1 1 0 0 1
netname=DAC0
}
N 50600 75000 51200 75000 4
{
T 51250 75050 5 10 1 1 0 0 1
netname=DAC1
}
N 50600 75500 51200 75500 4
{
T 51250 75550 5 10 1 1 0 0 1
netname=DAC2
}
N 44200 60900 44200 60600 4
{
T 44050 60400 5 10 1 1 0 0 1
netname=Tx0
}
N 45000 60900 45000 60700 4
{
T 44850 60500 5 10 1 1 0 0 1
netname=Rx0
}
N 52000 61400 52300 61400 4
{
T 52350 61350 5 10 1 1 0 0 1
netname=Tx1
}
N 52000 61800 52300 61800 4
{
T 52350 61750 5 10 1 1 0 0 1
netname=Rx1
}
C 29600 60750 1 0 0 irf7317.sym
{
T 30300 62200 5 10 1 1 0 0 1
refdes=Q2
T 30000 60450 5 9 1 1 0 0 1
device=IRF7317
T 29600 60750 5 10 0 0 0 0 1
value=IRF7317
}
C 29100 61550 1 270 0 gnd-1.sym
N 29600 61450 29400 61450 4
N 32950 58850 32950 58600 4
{
T 32850 58400 5 10 1 1 0 0 1
netname=SR
}
N 29600 60750 29600 59500 4
C 30350 59400 1 0 0 resistor-2.sym
{
T 30550 59700 5 10 1 1 0 0 1
refdes=R30
T 30750 59200 5 10 1 1 0 0 1
value=200
T 30350 59400 5 10 0 0 0 0 1
footprint=0603
}
N 29600 59500 30350 59500 4
C 29500 58200 1 0 0 gnd-1.sym
N 29600 58500 29600 58600 4
N 31250 59500 31500 59500 4
{
T 31500 59500 5 10 1 1 0 0 1
netname=+12V
}
C 28550 61900 1 90 0 resistor-2.sym
{
T 28650 62400 5 10 1 1 0 0 1
refdes=R31
T 28650 62100 5 10 1 1 0 0 1
value=10k
T 28550 61900 5 10 0 0 0 0 1
footprint=0603
}
N 28450 61700 28450 61900 4
N 29100 61050 29600 61050 4
{
T 28850 61100 5 10 1 1 0 0 1
netname=RESET
}
N 28450 63000 28450 62800 4
{
T 28450 63000 5 10 1 1 0 0 1
netname=+12V
}
N 29600 61750 28450 61750 4
N 27450 61200 27850 61200 4
{
T 27250 61250 5 10 1 1 0 0 1
netname=SET
}
N 40100 60600 39700 60600 4
{
T 39500 60750 5 10 1 1 0 0 1
netname=RESET
}
N 42500 60600 42100 60600 4
{
T 41800 60650 5 10 1 1 0 0 1
netname=SET
}
N 41200 67400 41200 68000 4
{
T 41600 68200 5 10 1 1 0 6 1
netname=2.048V
}
N 46200 67900 46200 68100 4
C 43800 69600 1 90 1 capacitor-1.sym
{
T 43100 69300 5 10 1 1 0 0 1
refdes=C36
T 43200 69050 5 10 1 1 180 6 1
value=0.1
T 43800 69600 5 10 0 0 0 0 1
footprint=0603
}
N 44600 67900 44600 68700 4
N 43600 69600 43600 70100 4
C 40700 65500 1 270 0 gnd-1.sym
N 41000 65400 41200 65400 4
C 41900 68700 1 0 0 coil-1.sym
{
T 42100 68900 5 10 1 1 0 0 1
refdes=L1
T 42250 68500 5 10 1 1 0 0 1
value=100uH
T 41900 68700 5 10 0 0 0 0 1
footprint=1210
}
N 42900 68700 44600 68700 4
N 43200 68700 43200 68450 4
{
T 43150 68200 5 10 1 1 0 0 1
netname=AVdd
}
N 41900 68700 41600 68700 4
C 41400 68700 1 0 0 3.3V-plus-1.sym
C 39800 65000 1 90 0 capacitor-4.sym
{
T 40100 65750 5 10 1 1 180 0 1
refdes=C37
T 40450 65250 5 10 1 1 180 0 1
value=3.3; 10V
T 39800 65000 5 10 0 0 0 0 1
footprint=tanA
}
N 39600 65900 41000 65900 4
N 41000 65900 41000 65400 4
N 39200 65000 41200 65000 4
{
T 39200 65000 5 10 1 1 0 6 1
netname=AVdd
}
C 46500 60450 1 0 0 gnd-1.sym
C 43700 60450 1 0 0 gnd-1.sym
C 49900 68250 1 180 0 gnd-1.sym
C 52450 64900 1 90 0 gnd-1.sym
N 52150 65000 52000 65000 4
N 49800 67900 49800 67950 4
N 46600 60750 46600 60900 4
N 43800 60750 43800 60900 4
C 53200 65400 1 90 1 capacitor-1.sym
{
T 53200 65200 5 10 1 1 0 0 1
refdes=C38
T 53200 64700 5 10 1 1 180 6 1
value=0.47
T 53200 65400 5 10 0 0 0 0 1
footprint=0603
}
N 53000 64500 53000 64300 4
N 52000 65400 53000 65400 4
C 46000 60250 1 90 1 capacitor-1.sym
{
T 46000 60050 5 10 1 1 0 0 1
refdes=C39
T 46000 59550 5 10 1 1 180 6 1
value=0.47
T 46000 60250 5 10 0 0 0 0 1
footprint=0603
}
N 45800 60250 45800 60900 4
C 45700 58900 1 0 0 gnd-1.sym
N 45800 59200 45800 59350 4
C 50500 68600 1 180 1 capacitor-1.sym
{
T 50500 68600 5 10 1 1 0 0 1
refdes=C40
T 51600 68550 5 10 1 1 0 6 1
value=0.47
T 50500 68600 5 10 0 0 90 0 1
footprint=0603
}
C 52800 65400 1 0 0 3.3V-plus-1.sym
N 49400 67900 49400 68400 4
C 51800 68300 1 90 0 gnd-1.sym
N 51500 68400 51400 68400 4
C 50000 68750 1 0 0 3.3V-plus-1.sym
N 50200 68400 50200 67900 4
C 46000 60400 1 0 0 3.3V-plus-1.sym
N 46200 60400 45800 60400 4
N 54250 73300 54250 72800 4
{
T 53850 72800 5 10 1 1 0 0 1
netname=SCL
}
N 52850 73700 52400 73700 4
{
T 52350 73750 5 10 1 1 0 0 1
netname=A
}
N 54250 73700 54650 73700 4
{
T 54650 73800 5 10 1 1 0 0 1
netname=SDA
}
N 52000 64600 52600 64600 4
{
T 52400 64650 5 10 1 1 0 0 1
netname=SDA
}
N 52000 63000 52600 63000 4
{
T 52500 63050 5 10 1 1 0 0 1
netname=SCL
}
C 42500 60500 1 0 0 resistor-2.sym
{
T 42550 60800 5 10 1 1 0 0 1
refdes=R32
T 43050 60300 5 10 1 1 0 0 1
value=100
T 42500 60500 5 10 0 0 0 0 1
footprint=0603
}
N 43400 60600 43400 60900 4
C 40100 60500 1 0 0 resistor-2.sym
{
T 40300 60800 5 10 1 1 0 0 1
refdes=R33
T 40500 60300 5 10 1 1 0 0 1
value=100
T 40100 60500 5 10 0 0 0 0 1
footprint=0603
}
N 41000 60600 41200 60600 4
C 38450 73900 1 270 0 capacitor-4.sym
{
T 38950 73650 5 10 1 1 0 0 1
refdes=C41
T 38800 73150 5 10 1 1 0 0 1
value=10.0; 10V
T 38450 73900 5 10 0 0 0 0 1
footprint=tanA
}
C 38550 72550 1 0 0 gnd-1.sym
N 38650 73000 38650 72850 4
N 38650 73950 38650 73900 4
C 36350 69550 1 0 0 lp2980AIM5-3.sym
{
T 36750 74250 5 10 1 1 0 0 1
refdes=U15
T 36350 69550 5 10 0 0 0 0 1
footprint=lp2980
}
N 36050 72950 36450 72950 4
{
T 35600 73000 5 10 1 1 0 0 1
netname=AmpOn
}
N 35850 73950 36450 73950 4
{
T 36100 74000 5 10 1 1 0 6 1
netname=+12V
}
C 36100 73550 1 270 0 gnd-1.sym
N 36400 73450 36450 73450 4
N 47400 58400 47200 58400 4
N 29900 62750 31100 62750 4
{
T 31100 62750 5 10 1 1 0 0 1
netname=SR
}
N 30700 62950 30700 62750 4
N 40200 61450 40200 63400 4
N 40200 63400 41200 63400 4
C 36600 58100 1 0 0 header10-2.sym
{
T 37200 60200 5 10 1 1 0 0 1
refdes=J3
T 36600 58100 5 10 0 0 0 0 1
footprint=2.5mm_10pin_header
}
N 36600 59900 36300 59900 4
{
T 36300 59900 5 10 1 1 0 6 1
netname=A+5V
}
N 36600 59500 36300 59500 4
N 38000 59500 38300 59500 4
C 38600 59400 1 90 0 gnd-1.sym
C 36000 59400 1 270 1 gnd-1.sym
C 38700 60000 1 180 1 resistor-2.sym
{
T 39000 60100 5 10 1 1 0 6 1
refdes=R34
T 39600 60100 5 10 1 1 0 6 1
value=10k
T 38700 60000 5 10 0 0 270 6 1
footprint=0603
}
N 45400 60900 45400 59900 4
N 38000 59900 38700 59900 4
T 37500 59900 9 9 1 0 0 4 1
Zout
T 37500 59100 9 9 1 0 0 4 1
Ty
T 37100 59100 9 9 1 0 0 4 1
Tx
T 37100 58700 9 9 1 0 0 4 1
Tz
T 37500 58700 9 9 1 0 0 4 1
wx
T 37100 58300 9 9 1 0 0 4 1
wy
T 37500 58300 9 9 1 0 0 4 1
wz
T 37100 59900 9 9 1 0 0 4 1
+5V
T 37100 59500 9 9 1 0 0 4 1
Gnd
T 37500 59500 9 9 1 0 0 4 1
Gnd
N 41200 62600 41000 62600 4
{
T 41050 62600 5 10 1 1 0 6 1
netname=wz
}
N 41200 62200 41000 62200 4
{
T 41050 62200 5 10 1 1 0 6 1
netname=wx
}
N 41200 61800 41000 61800 4
{
T 41050 61800 5 10 1 1 0 6 1
netname=wy
}
N 38000 58700 38400 58700 4
{
T 38400 58700 5 10 1 1 0 0 1
netname=wx
}
N 38000 58300 38400 58300 4
{
T 38400 58300 5 10 1 1 0 0 1
netname=wz
}
N 36600 58300 36200 58300 4
{
T 36200 58300 5 10 1 1 0 6 1
netname=wy
}
N 36600 58700 36200 58700 4
{
T 36000 58700 5 10 1 1 0 0 1
netname=Tx
}
N 36600 59100 36200 59100 4
{
T 36000 59100 5 10 1 1 0 0 1
netname=Tz
}
N 38000 59100 38400 59100 4
{
T 38400 59100 5 10 1 1 0 0 1
netname=Ty
}
C 48400 60300 1 90 1 capacitor-1.sym
{
T 47750 60100 5 10 1 1 0 0 1
refdes=C42
T 47700 59700 5 10 1 1 180 6 1
value=0.47
T 48400 60300 5 10 0 0 0 0 1
footprint=0603
}
C 48100 58900 1 0 0 gnd-1.sym
N 48200 59200 48200 59400 4
N 48200 60300 48200 60900 4
N 48200 60500 47900 60500 4
{
T 47900 60500 5 10 1 1 0 6 1
netname=Tz
}
C 40000 66800 1 0 1 capacitor-1.sym
{
T 39100 67350 5 10 1 1 0 0 1
refdes=C43
T 39700 67300 5 10 1 1 180 6 1
value=0.47
T 40000 66800 5 10 0 0 270 0 1
footprint=0603
}
C 38600 67100 1 270 0 gnd-1.sym
N 38900 67000 39100 67000 4
N 41200 67000 40000 67000 4
N 40600 67000 40600 67400 4
{
T 40450 67500 5 10 1 1 0 0 1
netname=Ty
}
C 53750 62000 1 0 0 capacitor-1.sym
{
T 54100 62400 5 10 1 1 0 6 1
refdes=C44
T 54350 62350 5 10 1 1 0 0 1
value=0.47
T 53750 62000 5 10 0 0 90 6 1
footprint=0603
}
N 53400 62600 53400 62200 4
{
T 53400 62600 5 10 1 1 0 0 1
netname=Tx
}
C 54850 63850 1 90 0 resistor-2.sym
{
T 54950 64350 5 10 1 1 0 0 1
refdes=R35
T 54950 64050 5 10 1 1 0 0 1
value=10k
T 54850 63850 5 10 0 0 0 0 1
footprint=0603
}
C 54550 65150 1 0 0 3.3V-plus-1.sym
N 54750 65150 54750 64750 4
N 54750 63850 54750 63600 4
{
T 54600 63400 5 10 1 1 0 0 1
netname=SDA
}
C 55650 63850 1 90 0 resistor-2.sym
{
T 55750 64350 5 10 1 1 0 0 1
refdes=R36
T 55750 64050 5 10 1 1 0 0 1
value=10k
T 55650 63850 5 10 0 0 0 0 1
footprint=0603
}
N 55550 63850 55550 63600 4
{
T 55400 63400 5 10 1 1 0 0 1
netname=SCL
}
N 54750 64750 55550 64750 4
N 48600 57900 48600 58700 4
N 48600 57900 47200 57900 4
N 52400 66600 52000 66600 4
{
T 52400 66600 5 10 1 1 0 0 1
netname=B
}
C 52900 64000 1 0 0 gnd-1.sym
N 50100 60400 50100 59300 4
N 50100 59300 50300 59300 4
N 49400 60900 49400 59800 4
N 50300 59800 49400 59800 4
N 52000 62600 52800 62600 4
N 52800 62600 52800 60600 4
N 52800 60600 49900 60600 4
N 49900 60600 49900 58800 4
N 49900 58800 50300 58800 4
N 52550 71200 52550 74500 4
N 52550 74500 52850 74500 4
N 52750 74100 52850 74100 4
N 54450 72000 54450 74100 4
N 54450 74100 54250 74100 4
N 52400 73300 52850 73300 4
{
T 52350 73350 5 10 1 1 0 0 1
netname=B
}
N 49200 60200 49000 60200 4
N 49000 60200 49000 60900 4
C 52350 74800 1 270 1 gnd-1.sym
N 52650 74900 52850 74900 4
N 56100 74500 56100 74600 4
C 55400 74450 1 0 0 gnd-1.sym
N 55500 74750 55500 75000 4
N 54250 74500 54550 74500 4
N 37700 61950 37700 62800 4
N 35900 67150 35900 68000 4
N 35400 71300 35000 71300 4
N 35000 69750 36050 69750 4
N 29900 63850 29900 64350 4
N 30200 64350 30200 64150 4
N 30700 64350 30700 63850 4
N 31000 64150 31000 64350 4
N 32000 66250 33050 66250 4
N 32000 66850 33200 66850 4
N 28600 66850 28100 66850 4
N 28100 66850 28100 69550 4
N 28100 69550 33000 69550 4
N 27900 70150 33600 70150 4
N 27900 70150 27900 66250 4
N 27900 66250 28600 66250 4
N 52000 62200 53750 62200 4
N 54650 62200 54900 62200 4
C 54050 58150 1 0 0 header10-2.sym
{
T 54650 60250 5 10 1 1 0 0 1
refdes=J4
T 54050 58150 5 10 0 0 0 0 1
footprint=2.5mm_10pin_header
}
N 47000 67900 47000 68400 4
C 46900 68400 1 0 0 testpt-1.sym
{
T 47200 68600 5 10 1 1 0 0 1
refdes=TP1
T 46900 68400 5 10 0 0 0 0 1
footprint=tp
}
C 55200 62100 1 90 0 gnd-1.sym
N 46900 73650 47400 73650 4
N 55550 58350 55900 58350 4
{
T 55950 58350 5 10 1 1 0 0 1
netname=+12V
}
N 54050 57900 54050 58750 4
N 54050 57900 55550 57900 4
N 55550 57900 55550 58750 4
C 56100 59850 1 90 0 gnd-1.sym
N 54050 60500 55500 60500 4
N 55500 59950 55800 59950 4
N 50100 60400 53000 60400 4
N 53000 60400 53000 63400 4
N 53000 63400 52000 63400 4
N 32300 65650 32000 65650 4
N 32950 61850 32700 61850 4
N 39600 59900 45400 59900 4
N 30700 60750 30700 62750 4
N 34500 70150 36050 70150 4
N 35250 70150 35250 70650 4
N 35000 69550 35000 71300 4
N 28600 65650 28300 65650 4
N 41200 60600 41200 61400 4
N 41200 63000 40800 63000 4
{
T 40300 63050 5 10 1 1 0 0 1
netname=AmpOn
}
C 40850 69550 1 0 0 tps76316.sym
{
T 41250 74250 5 10 1 1 0 0 1
refdes=U16
T 40850 69550 5 10 0 0 0 0 1
footprint=lp2980
}
C 42750 73750 1 270 0 capacitor-4.sym
{
T 43250 73500 5 10 1 1 0 0 1
refdes=C46
T 43100 73000 5 10 1 1 0 0 1
value=4.7; 6.3V
T 42750 73750 5 10 0 0 0 0 1
footprint=tanA
}
N 42750 73950 43450 73950 4
{
T 43550 73950 5 10 1 1 0 0 1
netname=OpRef
}
N 42950 73750 42950 73950 4
N 40950 73950 40950 74200 4
N 38250 73950 40950 73950 4
N 40950 72950 40650 72950 4
{
T 40250 73000 5 10 1 1 0 0 1
netname=AmpOn
}
C 40350 73550 1 270 0 gnd-1.sym
N 40650 73450 40950 73450 4
C 41050 75500 1 180 0 gnd-1.sym
N 40950 75200 40950 75100 4
N 54050 59550 54050 60500 4
N 55500 59550 55500 60500 4
N 52000 67400 52350 67400 4
{
T 52350 67450 5 10 1 1 0 0 1
netname=Rx0
}
N 39800 62300 39800 62900 4
N 35900 68000 38000 68000 4
{
T 37650 68300 5 10 1 1 0 0 1
netname=OpRef
}
N 38000 67500 38000 68200 4
N 38100 70800 38400 70800 4
N 36300 71300 38400 71300 4
{
T 37850 71500 5 10 1 1 0 0 1
netname=OpRef
}
N 38400 70800 38400 71450 4
C 35250 68800 1 0 0 capacitor-1.sym
{
T 35250 69100 5 10 1 1 0 0 1
refdes=C50
T 35850 68700 5 10 1 1 0 0 1
value=0.47
T 35250 68800 5 10 0 0 0 0 1
footprint=0603
}
C 34800 65400 1 0 0 capacitor-1.sym
{
T 34800 65700 5 10 1 1 0 0 1
refdes=C51
T 35400 65300 5 10 1 1 0 0 1
value=0.47
T 34800 65400 5 10 0 0 0 0 1
footprint=0603
}
C 36650 60400 1 0 0 capacitor-1.sym
{
T 36650 60700 5 10 1 1 0 0 1
refdes=C52
T 36550 60350 5 10 1 1 0 0 1
value=0.47
T 36650 60400 5 10 0 0 0 0 1
footprint=0603
}
N 37550 60600 37850 60600 4
N 36650 60600 36300 60600 4
{
T 35950 60650 5 10 1 1 0 0 1
netname=OpRef
}
N 35700 65600 36050 65600 4
N 34800 65600 34550 65600 4
{
T 34300 65400 5 10 1 1 0 0 1
netname=OpRef
}
N 36150 69000 36550 69000 4
N 35250 69000 34800 69000 4
{
T 34200 68950 5 10 1 1 0 0 1
netname=OpRef
}
C 43050 74300 1 90 0 resistor-2.sym
{
T 43450 75100 5 10 1 1 180 0 1
refdes=R37
T 43550 74600 5 10 1 1 180 0 1
value=4.7k
T 43050 74300 5 10 0 0 90 0 1
footprint=0603
}
N 42950 73950 42950 74300 4
C 43050 75600 1 180 0 gnd-1.sym
N 42950 75300 42950 75200 4
T 27905 74750 8 10 1 1 0 0 1
description=stribog the attitude determination platform: main board
T 27905 73950 8 10 1 1 0 0 1
comment=Copyright (C) 2005-2006 D.Ineiev <ineiev@yahoo.co.uk>
T 27905 73550 8 10 1 1 0 0 1
documentation=This program is free software; you can redistribute it and/or modify
T 27905 73350 8 10 1 1 0 0 1
documentation=it under the terms of the GNU General Public License as published by
T 27905 73150 8 10 1 1 0 0 1
documentation=the Free Software Foundation; either version 2 of the License, or
T 27905 72950 8 10 1 1 0 0 1
documentation=(at your option) any later version.
T 27905 72650 8 10 1 1 0 0 1
documentation=This program is distributed in the hope that it will be useful,
T 27905 72450 8 10 1 1 0 0 1
documentation=but WITHOUT ANY WARRANTY; without even the implied warranty of
T 27905 72250 8 10 1 1 0 0 1
documentation=MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
T 27905 72050 8 10 1 1 0 0 1
documentation=GNU General Public License for more details.
T 27905 71750 8 10 1 1 0 0 1
documentation=You should have received a copy of the GNU General Public License
T 27905 71550 8 10 1 1 0 0 1
documentation=along with this program; if not, write to the Free Software
T 27905 71350 8 10 1 1 0 0 1
documentation=Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
T 27905 74450 8 10 1 1 0 0 1
description=revision date: 24II2006
N 55450 58350 55550 58350 4
N 55550 58750 55450 58750 4
N 55500 59950 55450 59950 4
N 55500 59550 55450 59550 4
N 48200 70600 48200 71600 4
N 48600 67900 48600 69650 4
N 48600 69650 49050 69650 4
N 49050 69650 49050 69700 4
N 48600 70600 48600 74500 4
N 48600 70600 49050 70600 4
N 46900 72600 47000 72600 4
N 45800 67900 45800 69200 4
N 45800 69200 47400 69200 4
C 46300 68400 1 180 0 gnd-1.sym
N 46600 69400 46600 69700 4
N 46600 69400 44200 69400 4
N 44200 67900 44200 69400 4
N 46600 70600 46600 70800 4
N 46600 70800 47000 70800 4
N 46600 67900 46600 69000 4
N 46600 69000 48200 69000 4
N 48200 69000 48200 69700 4
N 38650 73950 38650 74150 4
{
T 38400 74250 5 10 1 1 0 0 1
netname=A+3.3V
}
N 49400 68400 50500 68400 4
N 50200 68400 50200 68750 4
C 39600 69500 1 90 0 resistor-2.sym
{
T 39700 70000 5 10 1 1 0 0 1
refdes=R38
T 39700 69700 5 10 1 1 0 0 1
value=220
T 39600 69500 5 10 0 0 0 0 1
footprint=0603
}
C 40600 69500 1 90 0 resistor-2.sym
{
T 40700 70000 5 10 1 1 0 0 1
refdes=R39
T 40700 69700 5 10 1 1 0 0 1
value=220
T 40600 69500 5 10 0 0 0 0 1
footprint=0603
}
N 47400 67900 47400 68200 4
{
T 47300 68300 5 10 1 1 0 0 1
netname=LED1
}
N 48200 67900 48200 68200 4
{
T 48000 68300 5 10 1 1 0 0 1
netname=LED0
}
N 39500 69500 39500 69100 4
{
T 39300 68850 5 10 1 1 0 0 1
netname=LED0
}
N 40500 69500 40500 69100 4
{
T 40350 68850 5 10 1 1 0 0 1
netname=LED1
}
C 38900 70000 1 270 1 led.sym
{
T 39298 70668 5 12 1 1 180 2 1
refdes=HL1
T 38900 70000 5 10 0 0 0 0 1
footprint=led0805
}
C 39900 70000 1 270 1 led.sym
{
T 40752 70632 5 12 1 1 0 2 1
refdes=HL2
T 39900 70000 5 10 0 0 0 0 1
footprint=led0805
}
N 40500 70400 40500 70500 4
N 39500 70400 39500 70500 4
C 39600 71500 1 180 0 gnd-1.sym
N 39500 71200 39500 71000 4
N 39500 71100 40500 71100 4
N 40500 71100 40500 71000 4
N 39400 57800 39400 57900 4
C 29400 59500 1 270 0 capacitor-1.sym
{
T 29800 59200 5 10 1 1 0 0 1
refdes=C35
T 29800 58800 5 10 1 1 0 0 1
value=2.2
T 29400 59500 5 10 0 0 270 0 1
footprint=0805
}
