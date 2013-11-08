//
//  FX3GeoUtils.h
//  FX3C
//
//  Created by hassan vfx on 26/07/12.
//  Copyright (c) 2012 hassanvfx. All rights reserved.
//

#ifndef FX3C_FX3GeoUtils_h
#define FX3C_FX3GeoUtils_h


#include <math.h>
struct FX3Size
{
    
    float width;
    float height;
    
    FX3Size();
    FX3Size( float, float);
    ~FX3Size();
};



typedef float mat4[16];
// Pre-calculated value of PI / 180.
#define kPI180   0.017453

// Pre-calculated value of 180 / PI.
#define k180PI  57.295780

// Converts degrees to radians.
#define degreesToRadians(x) (x * kPI180)

// Converts radians to degrees.
#define radiansToDegrees(x) (x * k180PI)

class FX3Matrix {
    
    
public:
    
    static void multiply(mat4 m1, mat4 m2, mat4 result)
    {
        // Fisrt Column
        result[0] = m1[0]*m2[0] + m1[4]*m2[1] + m1[8]*m2[2] + m1[12]*m2[3];
        result[1] = m1[1]*m2[0] + m1[5]*m2[1] + m1[9]*m2[2] + m1[13]*m2[3];
        result[2] = m1[2]*m2[0] + m1[6]*m2[1] + m1[10]*m2[2] + m1[14]*m2[3];
        result[3] = m1[3]*m2[0] + m1[7]*m2[1] + m1[11]*m2[2] + m1[15]*m2[3];
        
        // Second Column
        result[4] = m1[0]*m2[4] + m1[4]*m2[5] + m1[8]*m2[6] + m1[12]*m2[7];
        result[5] = m1[1]*m2[4] + m1[5]*m2[5] + m1[9]*m2[6] + m1[13]*m2[7];
        result[6] = m1[2]*m2[4] + m1[6]*m2[5] + m1[10]*m2[6] + m1[14]*m2[7];
        result[7] = m1[3]*m2[4] + m1[7]*m2[5] + m1[11]*m2[6] + m1[15]*m2[7];
        
        // Third Column
        result[8] = m1[0]*m2[8] + m1[4]*m2[9] + m1[8]*m2[10] + m1[12]*m2[11];
        result[9] = m1[1]*m2[8] + m1[5]*m2[9] + m1[9]*m2[10] + m1[13]*m2[11];
        result[10] = m1[2]*m2[8] + m1[6]*m2[9] + m1[10]*m2[10] + m1[14]*m2[11];
        result[11] = m1[3]*m2[8] + m1[7]*m2[9] + m1[11]*m2[10] + m1[15]*m2[11];
        
        // Fourth Column
        result[12] = m1[0]*m2[12] + m1[4]*m2[13] + m1[8]*m2[14] + m1[12]*m2[15];
        result[13] = m1[1]*m2[12] + m1[5]*m2[13] + m1[9]*m2[14] + m1[13]*m2[15];
        result[14] = m1[2]*m2[12] + m1[6]*m2[13] + m1[10]*m2[14] + m1[14]*m2[15];
        result[15] = m1[3]*m2[12] + m1[7]*m2[13] + m1[11]*m2[14] + m1[15]*m2[15];
    }
    
    
    static void identity(mat4 m)
    {
        m[0] = m[5] = m[10] = m[15] = 1.0;
        m[1] = m[2] = m[3] = m[4] = 0.0;
        m[6] = m[7] = m[8] = m[9] = 0.0;
        m[11] = m[12] = m[13] = m[14] = 0.0;
    }
    
    static void translate(float x, float y, float z, mat4 matrix)
    {
        FX3Matrix::identity(matrix);
        
        // Translate slots.
        matrix[12] = x;
        matrix[13] = y;
        matrix[14] = z;
    }
    
    static void scale(float sx, float sy, float sz, mat4 matrix)
    {
        FX3Matrix::identity(matrix);
        
        // Scale slots.
        matrix[0] = sx;
        matrix[5] = sy;
        matrix[10] = sz;
    }
    
    static void rotateX(float degrees, mat4 matrix)
    {
        float radians = degreesToRadians(degrees);
        
        FX3Matrix::identity(matrix);
        
        // Rotate X formula.
        matrix[5] = cosf(radians);
        matrix[6] = -sinf(radians);
        matrix[9] = -matrix[6];
        matrix[10] = matrix[5];
    }
    
    static void rotateY(float degrees, mat4 matrix)
    {
        float radians = degreesToRadians(degrees);
        
        FX3Matrix::identity(matrix);
        
        // Rotate Y formula.
        matrix[0] = cosf(radians);
        matrix[2] = sinf(radians);
        matrix[8] = -matrix[2];
        matrix[10] = matrix[0];
        
        
    }
    
    static void rotateZ(float degrees, mat4 matrix)
    {
        float radians = degreesToRadians(degrees);
        
        FX3Matrix::identity(matrix);
        
        // Rotate Z formula.
        matrix[0] = cosf(radians);
        matrix[1] = sinf(radians);
        matrix[4] = -matrix[1];
        matrix[5] = matrix[0];
    }
    
    
    
   
    static void loadOrthoMatrix(mat4 matrix, float left, float right, float bottom, float top, float near, float far)
    {
        GLfloat r_l = right - left;
        GLfloat t_b = top - bottom;
        GLfloat f_n = far - near;
        GLfloat tx = - (right + left) / (right - left);
        GLfloat ty = - (top + bottom) / (top - bottom);
        GLfloat tz = - (far + near) / (far - near);
        
        matrix[0] = 2.0f / r_l;
        matrix[1] = 0.0f;
        matrix[2] = 0.0f;
        matrix[3] = tx;
        
        matrix[4] = 0.0f;
        matrix[5] = 2.0f / t_b;
        matrix[6] = 0.0f;
        matrix[7] = ty;
        
        matrix[8] = 0.0f;
        matrix[9] = 0.0f;
        matrix[10] = 2.0f / f_n;
        matrix[11] = tz;
        
        matrix[12] = 0.0f;
        matrix[13] = 0.0f;
        matrix[14] = 0.0f;
        matrix[15] = 1.0f;
    }
    
    
    
};



class FX3ColorUtils {
    
    
public:
    
    static float HueToRGB(float f1, float f2, float hue)
    {
        if (hue < 0.0)
            hue += 1.0;
        else if (hue > 1.0)
            hue -= 1.0;
        float res;
        if ((6.0 * hue) < 1.0)
            res = f1 + (f2 - f1) * 6.0 * hue;
        else if ((2.0 * hue) < 1.0)
            res = f2;
        else if ((3.0 * hue) < 2.0)
            res = f1 + (f2 - f1) * ((2.0 / 3.0) - hue) * 6.0;
        else
            res = f1;
        return res;
    }
    
    static void HSLToRGB(UInt8 *hsl_int)
    {
        
        float rgb[3];
        float hsl[3];
        
        hsl[0] = hsl_int[2]/255.0;
        hsl[1] = hsl_int[1]/255.0;
        hsl[2] = hsl_int[0]/255.0;
        
        if (hsl[1] == 0.0){
            rgb[0] = hsl[2]; // Luminance
            rgb[1] = hsl[2]; // Luminance
            rgb[2] = hsl[2]; // Luminance
        }
        else
        {
            float f2;
            
            if (hsl[2] < 0.5)
                f2 = hsl[2] * (1.0 + hsl[1]);
            else
                f2 = (hsl[2] + hsl[1]) - (hsl[1] * hsl[2]);
            
            float f1 = 2.0 * hsl[2] - f2;
            
            rgb[0] = HueToRGB(f1, f2, hsl[0] + (1.0/3.0));
            rgb[1] = HueToRGB(f1, f2, hsl[0]);
            rgb[2]=  HueToRGB(f1, f2, hsl[0] - (1.0/3.0));
        }
        
        hsl_int[2] =(UInt8) round(rgb[0]*255.0);
        hsl_int[1] =(UInt8) round(rgb[1]*255.0);
        hsl_int[0] =(UInt8) round(rgb[2]*255.0);
        
        
    }

    
};

#endif
