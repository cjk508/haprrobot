
const char *note[63];
// octave 0
note[0] = "<<<<C";
note[1] = "<<<<D";
note[2] = "<<<<E";
note[3] = "<<<<F";
note[4] = "<<<<G";
note[5] = "<<<<A";
note[6] = "<<<<B";
// octave 1
note[7]  = "<<<C";
note[8]  = "<<<D";
note[9]  = "<<<E";
note[10] = "<<<F";
note[11] = "<<<G";
note[12] = "<<<A";
note[13] = "<<<B";
// octave 2
note[14] = "<<C";
note[15] = "<<D";
note[16] = "<<E";
note[17] = "<<F";
note[18] = "<<G";
note[19] = "<<A";
note[20] = "<<B";
// octave 3
note[21] = "<C";
note[22] = "<D";
note[23] = "<E";
note[24] = "<F";
note[25] = "<G";
note[26] = "<A";
note[27] = "<B";
// octave 4
note[28] = "C";
note[29] = "D";
note[30] = "E";
note[31] = "F";
note[32] = "G";
note[33] = "A";
note[34] = "B";
// octave 5
note[35] = ">C";
note[36] = ">D";
note[37] = ">E";
note[38] = ">F";
note[39] = ">G";
note[40] = ">A";
note[41] = ">B";
// octave 6
note[42] = ">>C";
note[43] = ">>D";
note[44] = ">>E";
note[45] = ">>F";
note[46] = ">>G";
note[47] = ">>A";
note[48] = ">>B";
// octave 7
note[49] = ">>>C";
note[50] = ">>>D";
note[51] = ">>>E";
note[52] = ">>>F";
note[53] = ">>>G";
note[54] = ">>>A";
note[55] = ">>>B";
// octave 8
note[56] = ">>>>C";
note[57] = ">>>>D";
note[58] = ">>>>E";
note[59] = ">>>>F";
note[60] = ">>>>G";
note[61] = ">>>>A";
note[62] = ">>>>B";


const char *volume[16];
volume[0] = "V0";
volume[1] = "V1";
volume[2] = "V2";
volume[3] = "V3";
volume[4] = "V4";
volume[5] = "V5";
volume[6] = "V6";
volume[7] = "V7";
volume[8] = "V8";
volume[9] = "V9";
volume[10] = "V10";
volume[11] = "V11";
volume[12] = "V12";
volume[13] = "V13";
volume[14] = "V14";
volume[15] = "V15";


SensorPair noteValuesLeft(SensorPair sensorValue);

SensorPair volumeValuesRight(SensorPair sensorValue);

void setNote();

void setVolume();
