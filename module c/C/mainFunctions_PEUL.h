#pragma once
sParamEqua calcParamEquaBetweenTwoPos(sPos pos, sPos light);
int testTvalueFromParamEqua(sPos pos, sParamEqua paramEqua);
sPos* intersectLight_PEUL(sParamEqua paramEqua, double t, sPos *pos);
void* doesCollide_PEUL(sParam param, double t, sParamEqua paramEqua);
int isInTheShadow(sPos pos, sParam param);