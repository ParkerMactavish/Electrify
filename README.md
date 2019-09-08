---
title: 'Electrify'
---


Electrify
===
[TOC]

## Parameter
1. Resistor Map:
    
| Variable Name | Arduino Pin | CD4066 Pin | Resistor Value|
| --------      | --------    | --------   | ---|
| pResCon0      | pin4        | pin13      | 27.1 kOhm|
| pResCon1      | pin5        | pin5       | 9.7  kOhm|
| pResCon2      | pin6        | pin6       | 4.5  kOhm|
| pResCon3      | pin7        | pin12      | 2.6  kOhm|
| N/A           | NC          | NC         | 10.4 kOhm(Const)|

2. Resistor Level:

| Level | Pin State | Resistor Value | Voltage Value|
| ----- | --------- | -------------- | -------------|
| 1     | 0 0 0 0   | 53.8 kOhm      | 29 Vpp       |
| 2     | 0 1 1 1   | 37.1 kOhm      | 40 Vpp       |
| 3     | 1 0 0 0   | 27.1 kOhm      | 54 Vpp       |
| 4     | 1 0 1 0   | 22.6 kOhm      | 64 Vpp       |
| 5     | 1 0 1 1   | 20.1 kOhm      | 70 Vpp       |
| 6     | 1 1 0 0   | 17.5 kOhm      | 80 Vpp       |
| 7     | 1 1 0 1   | 14.9 kOhm      | 80+ Vpp      |
| 8     | 1 1 1 0   | 13.0 kOhm      | 80+ Vpp      |
