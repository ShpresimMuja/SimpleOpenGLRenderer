#pragma once

inline void initialiseMat4(float * mat4[4][4])
{

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            *mat4[i][j] = 0.0f;

        }

    }


}


