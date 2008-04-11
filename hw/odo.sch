v 20050820 1
C 11900 74600 1 0 0 crystal-1.sym
{
T 12050 74900 5 10 1 1 0 0 1
refdes=ZQ1
T 11800 74300 5 10 1 1 0 0 1
value=14.7456MHz
T 11900 74600 5 10 0 0 0 0 1
footprint=crystal
}
C 10600 74500 1 0 0 capacitor-1.sym
{
T 10800 75000 5 10 1 1 0 0 1
refdes=C1
T 11200 74800 5 10 1 1 0 0 1
value=22
T 10600 74500 5 10 0 0 0 0 1
footprint=0603
}
C 13000 74500 1 0 0 capacitor-1.sym
{
T 13200 75000 5 10 1 1 0 0 1
refdes=C2
T 13600 74800 5 10 1 1 0 0 1
value=22
T 13000 74500 5 10 0 0 0 0 1
footprint=0603
}
C 10100 74800 1 270 0 gnd-1.sym
N 11900 74700 11500 74700 4
N 10400 74700 10600 74700 4
C 14300 74800 1 90 1 gnd-1.sym
N 14000 74700 13900 74700 4
N 13000 74700 12600 74700 4
N 12800 74700 12800 75600 4
N 12800 75600 13300 75600 4
N 13300 75800 11600 75800 4
N 11600 75800 11600 74700 4
C 7400 81300 1 0 0 capacitor-1.sym
{
T 7650 81850 5 10 1 1 0 0 1
refdes=C3
T 8050 81750 5 10 1 1 0 0 1
value=0.22
T 7400 81300 5 10 0 0 0 0 1
footprint=0603
}
C 10600 81300 1 0 0 capacitor-1.sym
{
T 10550 81600 5 10 1 1 0 0 1
refdes=C5
T 11200 81200 5 10 1 1 0 0 1
value=0.22
T 10600 81300 5 10 0 0 0 0 1
footprint=0603
}
C 10600 80500 1 0 0 capacitor-1.sym
{
T 10550 80800 5 10 1 1 0 0 1
refdes=C6
T 11200 80400 5 10 1 1 0 0 1
value=0.22
T 10600 80500 5 10 0 0 0 0 1
footprint=0603
}
C 7400 80500 1 0 0 capacitor-1.sym
{
T 7350 80900 5 10 1 1 0 0 1
refdes=C4
T 8000 80800 5 10 1 1 0 0 1
value=0.22
T 7400 80500 5 10 0 0 0 0 1
footprint=0603
}
N 10400 80700 10600 80700 4
N 10400 81500 10600 81500 4
N 8300 81500 8400 81500 4
N 7400 81500 7400 81100 4
N 7400 81100 8400 81100 4
N 8300 80700 8400 80700 4
N 7400 80700 7400 80300 4
N 7400 80300 8400 80300 4
C 10600 77300 1 0 0 capacitor-1.sym
{
T 10600 77650 5 10 1 1 0 0 1
refdes=C7
T 11200 77200 5 10 1 1 0 0 1
value=0.22
T 10600 77300 5 10 0 0 0 0 1
footprint=0603
}
N 10400 77500 10600 77500 4
N 11500 78100 11500 77500 4
C 10400 76900 1 0 0 gnd-1.sym
N 10500 77200 10500 77500 4
N 10400 78100 11800 78100 4
{
T 11800 78100 5 10 1 1 0 0 1
netname=+5V
}
C 6600 75400 1 0 0 adm202.sym
{
T 10100 81900 5 10 1 1 0 6 1
refdes=U2
T 6600 75400 5 10 0 0 0 0 1
footprint=SO16
T 6600 75400 5 10 0 0 0 0 1
value=ADM202[AJ]R
}
C 12100 80600 1 90 0 gnd-1.sym
N 11800 80700 11500 80700 4
N 11500 81500 11800 81500 4
{
T 11850 81500 5 10 1 1 0 0 1
netname=+5V
}
N 13300 79700 10400 79700 4
N 10400 79700 10400 79900 4
N 10400 79500 13300 79500 4
N 16000 76700 16000 76400 4
C 16200 75100 1 90 0 capacitor-1.sym
{
T 16500 75850 5 10 1 1 180 0 1
refdes=C8
T 16600 75300 5 10 1 1 180 0 1
value=0.22
T 16200 75100 5 10 0 0 90 0 1
footprint=0603
}
C 16100 74500 1 0 1 gnd-1.sym
N 16000 76700 15900 76700 4
N 15900 76400 16600 76400 4
{
T 16700 76400 5 10 1 1 0 0 1
netname=+5V
}
N 16000 76400 16000 76000 4
N 16000 75100 16000 74800 4
N 13300 76000 12600 76000 4
{
T 12200 75900 5 10 1 1 0 0 1
netname=SCK
}
N 13300 76200 12600 76200 4
{
T 12100 76100 5 10 1 1 0 0 1
netname=MISO
}
N 13300 76400 12600 76400 4
{
T 12100 76300 5 10 1 1 0 0 1
netname=MOSI
}
N 15900 77500 16400 77500 4
{
T 16500 77400 5 10 1 1 0 0 1
netname=~RESET
}
N 15900 77700 17400 77700 4
C 23350 76200 1 0 1 opamp-1.sym
{
T 22650 76800 5 10 1 1 0 6 1
refdes=U3.1
T 22650 76300 5 10 1 1 0 6 1
device=AD712
}
C 20400 76000 1 0 1 opamp-1.sym
{
T 19700 76600 5 10 1 1 0 6 1
refdes=U3.2
}
C 17600 78250 1 0 1 bat54c.sym
{
T 17048 79218 5 12 1 1 180 2 1
refdes=D1
}
N 16600 79000 16400 79000 4
N 16400 79000 16400 77700 4
N 16700 78500 16700 78400 4
N 17800 78400 17800 79000 4
N 17800 79000 17100 79000 4
N 16700 78400 18200 78400 4
{
T 18250 78400 5 10 1 1 0 2 1
netname=+5V
}
C 18300 77800 1 180 0 resistor-2.sym
{
T 17950 78050 5 10 1 1 180 0 1
refdes=R1
T 18050 77500 5 10 1 1 180 0 1
value=330k
T 18300 77800 5 10 0 0 90 0 1
footprint=0603
}
C 19800 75550 1 0 0 gnd-1.sym
N 19900 75850 19900 76000 4
N 19900 76800 19900 77000 4
{
T 20100 77100 5 10 1 1 0 6 1
netname=+12V
}
C 23950 76900 1 180 1 resistor-2.sym
{
T 24300 77150 5 10 1 1 180 6 1
refdes=R2
T 24200 76600 5 10 1 1 180 6 1
value=330k
T 23950 76900 5 10 0 0 90 2 1
footprint=0603
}
C 22850 75350 1 180 1 resistor-2.sym
{
T 23200 75600 5 10 1 1 180 6 1
refdes=R3
T 23100 75050 5 10 1 1 180 6 1
value=330k
T 22850 75350 5 10 0 0 90 2 1
footprint=0603
}
N 23950 76800 23350 76800 4
N 23750 75250 23750 76800 4
N 22550 75250 22850 75250 4
{
T 22500 75150 5 10 1 1 0 6 1
netname=+5V
}
N 24850 76800 25250 76800 4
{
T 25850 76750 5 10 1 1 0 6 1
netname=INPUT
}
C 20950 76700 1 180 1 resistor-2.sym
{
T 21300 76950 5 10 1 1 180 6 1
refdes=R3
T 21350 76400 5 10 1 1 180 6 1
value=1k
T 20950 76700 5 10 0 0 90 2 1
footprint=0603
}
C 19900 77800 1 180 0 resistor-2.sym
{
T 19550 78050 5 10 1 1 180 0 1
refdes=R3
T 19650 77500 5 10 1 1 180 0 1
value=10k
T 19900 77800 5 10 0 0 90 0 1
footprint=0603
}
N 18300 77700 19000 77700 4
N 18800 77700 18800 76400 4
N 18800 76400 19400 76400 4
N 19900 77700 20500 77700 4
N 20500 77700 20500 76600 4
N 21850 76600 22350 76600 4
N 20400 76200 20400 75750 4
{
T 20300 75500 5 10 1 1 0 0 1
netname=+5V
}
C 14900 81700 1 0 0 DB9-1.sym
{
T 15100 84900 5 10 1 1 0 0 1
refdes=CONN1
T 15000 81400 5 10 1 1 0 0 1
value=DB9-M
}
C 18200 81700 1 0 0 DB9-1.sym
{
T 18400 84900 5 10 1 1 0 0 1
refdes=CONN2
T 18300 81450 5 10 1 1 0 0 1
value=DB9-F
}
C 16400 81550 1 0 1 gnd-1.sym
C 19600 81400 1 0 1 gnd-1.sym
N 19500 81700 19500 82000 4
N 19500 82000 19400 82000 4
N 16300 81850 16300 82000 4
N 16300 82000 16100 82000 4
C 19600 79850 1 0 0 lm7805-1.sym
{
T 21000 80850 5 10 1 1 0 6 1
refdes=U3
}
C 20500 78750 1 0 1 gnd-1.sym
N 20400 79050 20400 79850 4
N 19600 80450 18450 80450 4
{
T 18400 80500 5 10 1 1 0 0 1
netname=+12V
}
N 21200 80450 22500 80450 4
{
T 22100 80500 5 10 1 1 0 0 1
netname=+5V
}
C 21700 79250 1 90 0 capacitor-1.sym
{
T 21900 80050 5 10 1 1 180 0 1
refdes=C10
T 21900 79400 5 10 1 1 180 0 1
value=1.0
}
C 19300 79250 1 90 0 capacitor-1.sym
{
T 19500 80050 5 10 1 1 180 0 1
refdes=C9
T 19500 79400 5 10 1 1 180 0 1
value=1.0
}
N 20400 79150 19100 79150 4
N 19100 79150 19100 79250 4
N 20400 79150 21500 79150 4
N 21500 79150 21500 79250 4
N 21500 80150 21500 80450 4
N 19100 80150 19100 80450 4
T 21105 78050 8 10 1 1 0 0 1
description=This input circuit is just a hint
T 21105 77800 8 10 1 1 0 0 1
description=it is probably not needed at all
T 21105 77500 8 10 1 1 0 0 1
description=the only necessary parts are D1 and R1
T 7155 85900 8 10 1 1 0 0 1
description=stribog the attitude determination platform: auxiliary odometer counter
T 7155 85400 8 10 1 1 0 0 1
comment=Copyright (C) 2008 Ineiev <ineiev@users.sourceforge.net>
T 7155 85000 8 10 1 1 0 0 1
documentation=This program is free software; you can redistribute it and/or modify
T 7155 84800 8 10 1 1 0 0 1
documentation=it under the terms of the GNU General Public License as published by
T 7155 84600 8 10 1 1 0 0 1
documentation=the Free Software Foundation; either version 3 of the License, or
T 7155 84400 8 10 1 1 0 0 1
documentation=(at your option) any later version.
T 7155 84100 8 10 1 1 0 0 1
documentation=This program is distributed in the hope that it will be useful,
T 7155 83900 8 10 1 1 0 0 1
documentation=but WITHOUT ANY WARRANTY; without even the implied warranty of
T 7155 83700 8 10 1 1 0 0 1
documentation=MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
T 7155 83500 8 10 1 1 0 0 1
documentation=GNU General Public License for more details.
T 7155 83200 8 10 1 1 0 0 1
documentation=You should have received a copy of the GNU General Public License
T 7155 83000 8 10 1 1 0 0 1
documentation=along with this program. If not, see <http://www.gnu.org/licenses/>.
T 7155 82500 8 10 1 1 0 0 1
description=revision date: 11IV2008
N 22000 76600 22000 76000 4
N 22000 76000 23350 76000 4
N 23350 76000 23350 76400 4
N 20400 76600 20950 76600 4
N 16100 83800 17100 83800 4
N 17100 83800 17100 85350 4
N 17100 85350 19900 85350 4
N 19900 85350 19900 83800 4
N 19900 83800 19400 83800 4
T 17900 82555 8 10 1 1 90 0 1
description=to GPS (NMEA)
T 14700 82555 8 10 1 1 90 0 1
description=mixed output
N 19400 83200 19850 83200 4
{
T 19950 83150 5 10 1 1 0 0 1
netname=NMEA
}
N 8400 79500 8150 79500 4
{
T 7550 79450 5 10 1 1 0 0 1
netname=NMEA
}
N 8400 79900 7800 79900 4
{
T 7250 79850 5 10 1 1 0 0 1
netname=output
}
N 16100 83200 16600 83200 4
{
T 16700 83150 5 10 1 1 0 0 1
netname=output
}
C 13300 75400 1 0 0 ATmega8-1.sym
{
T 15600 80000 5 10 1 1 0 6 1
refdes=U1
}
