#pragma once

#include "Float3.h"

bool CheckBallHit( Float3 center1, float radius1, Float3 center2, float radius2 );
bool CheckBoxHit3D( Float3 box_pos1, Float3 box_size1, Float3 box_pos2, Float3 box_size2 );
