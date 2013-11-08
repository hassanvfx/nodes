//
//  FX3ShaderDemo.cpp
//  FX3Ctest
//
//  Created by hassanvfx on 04/10/12.
//  Copyright (c) 2012 hassanvfx. All rights reserved.
//

#include "FX3ShaderDemo.h"


char* FX3ShaderDemo::vertexShader()
{
    return SHADER_STRING
    (
     
     attribute mediump vec4 vertexPosition;
     attribute mediump vec4 vertexUV;
     varying mediump vec2 textureCoordinate;
     
     void main()
     {
         
         gl_Position = vertexPosition;
         textureCoordinate = vertexUV.xy;
     }
     );
    
}
  char* FX3ShaderDemo::fragmentShader()
  {
  
  return SHADER_STRING
  (
  
  precision highp int;
  precision highp float;
  varying  vec2 textureCoordinate;
  uniform sampler2D texture0;
  
  float add(  float a,  float b,  float mixed){
  
  return mix( a, a+b, mixed);
  }
  float sub(  float a,  float b,  float mixed){
  
  return mix( a, a-b, mixed);
  }
  float div(  float a,  float b,  float mixed){
  
  return mix( a, a/b, mixed);
  }
  float mult(  float a,  float b,  float mixed){
  
  return mix( a, a*b, mixed);
  }
  float invert(  float a){
  
  return 1.0-a;
  }
  float contrast (  float a,  float val,  float center ){
  
  return (a - 0.5) * val + 0.5;
  }
  float gamma (  float a,  float val ) {
  
  return pow( a , (1.0/val));
  }
  vec4 gamma4 (  vec4 a,  float val ) {
  
  return pow( a , vec4(1.0/val));
  }
  vec4 bright4 (  vec4 a,  float val ) {
  
  return a * vec4( val );
  }
  
  vec4 vignette( vec4 color, float radius, float softness, vec2 center, vec2 coords){
  
  float d = sqrt(pow( abs(center.x -coords.x),2.0) + pow( abs(center.y -coords.y),2.0));
  d=d> radius ? 1.0:d * 1.0/radius;
  d=pow( d , ( 1.0/softness)) ;
  d=1.0-d;
  d=clamp (d,0.0,1.0);
  vec4 result =vec4(d);
  result.w=color.w;
  color =color*result;
  return color;
  }
  
  vec4 soho( vec4 color){
  
  // vec4 vignette1 = texture2D(texture1, textureCoordinate);
  // color = clamp(gamma4( color, 0.5 + ( (1.0-knobMix)*.6)), 0.01, 1.0 );
  float r = color.r;
  float g = color.g;
  float b = color.b;
  float invert2 = 1.0-r;
  float gamma2 = gamma( invert2, 0.6);
  float contrast2 = contrast( r, 2.0, 0.75 );
  float add2 = r+g*.4;
  float add3 = add2 + b;
  float add1 = g+b* .523;
  float sub1 = add1- r*.165;
  float gamma1 = gamma( b, 1.4);
  float sub2 = gamma1- r*.215;
  float add8 = sub2+ gamma2* .17;
  float inside1 = add8 * g;
  float add5 =  sub1 + inside1* .237;
  float div1 = r;
  float invert1 = 1.0-(add3);
  float add4 = (div1 + invert1 * .223);
  float add6 = ( add4 + contrast2 * 0.5);
  float mult1 = mult(add5, contrast2, 0.1);
  vec4 color2 = vec4( add6, mult1, add8, color.a);
  
  return color2;
  }
  
  void main() {
  

      vec2 center =vec2(0.5);
      vec4 color = texture2D(texture0, textureCoordinate);
      color=  soho(color);
      color=clamp(color,0.0,1.0);
      color = vignette( color, 0.65, 0.9, center, textureCoordinate);
  

      gl_FragColor = color ;
  }
  
  );
  
  
  }

/*
char* FX3ShaderDemo::fragmentShader(){
    
    return SHADER_STRING
    (
     precision highp int;
     precision highp float;
     varying  vec2 textureCoordinate;
     uniform sampler2D texture0;
    // uniform sampler2D texture1;
     //uniform  float knobIntensity;
     //uniform  float knobMix;
     vec4 gamma4 (  vec4 a,  float val ) {
         
         return pow( a , vec4(1.0/val));
     }
     vec4 bright4 (  vec4 a,  float val ) {
         
         return a * vec4( val );
     }
     
     vec4 vignette( vec4 color, float radius, float softness, vec2 center, vec2 coords){
         
         float d = sqrt(pow( abs(center.x -coords.x),2.0) + pow( abs(center.y -coords.y),2.0));
         d=d> radius ? 1.0:d * 1.0/radius;
         d=pow( d , ( 1.0/softness)) ;
         d=1.0-d;
         d=clamp (d,0.0,1.0);
         vec4 result =vec4(d);
         result.w=color.w;
         color =color*result;
         return color;
     }
     void main() {
         
         float knobMixInverted = 0.5;
         vec4 color = texture2D(texture0, textureCoordinate);
         
        
       //  vec4 vignette1 = texture2D(texture1, textureCoordinate);
        // color = clamp(gamma4( color,0.6+ ( knobMixInverted*0.3) ), 0.01, 1.0 );
         float r = color.r;
         float g = color.g;
         float b = color.b;
         float rMask = (1.0-b) + ( r * 0.5 + g * 0.5);
         float gMask = (1.0-g) + ( r * 0.5 + b * 0.5);
         float bMask = (1.0-r) + ( b * 0.5 + g * 0.5);
         float rMask2 = 1.0 - ( rMask* gMask);
         float gMask2 = 1.0 - (bMask * rMask);
         float bMask2 = 1.0 - (bMask * gMask);
         float r2 = r-rMask2;
         float g2 = g-gMask2;
         float b2 = b-bMask2;
         float l =( r2 *.3 +g2 *.59 +b2 *.11 ) ;
         vec4 color2 = vec4 ( r2, l, g2, color.a);
         
         
         
        // vec2 center =vec2(0.5);
        // color2 = vignette( color2, 0.65, 0.9, center, textureCoordinate);
      
         
        // vec4 gamma14 = mix( color2 , gamma4( color2, (0.2) + (0.3*knobMixInverted ) ) ,vignette1.r);
        // vec4 bright2 = mix( gamma14 , bright4( gamma14, (0.1) + (0.3*knobMixInverted ) ) ,vignette1.g);
         gl_FragColor = color2 ;
     });
    
}*/

#pragma mark newPacks



char* FX3ShaderDemo::fragmentOverExposed(){
    
    return SHADER_STRING
    (
     
     precision highp int;
     precision highp float;
     varying  vec2 textureCoordinate;
     uniform sampler2D texture0;
     
     
     uniform sampler2D tex;
     
     void main()
     {
         
         vec4 color =  texture2D(texture0, textureCoordinate);
         vec3 gamma17 =  pow( color.rgb, vec3( 1.0 /1.311));
         
         vec3 gamma10 = pow( gamma17, vec3( 1.0 /0.7732 , 1.0 / 0.45, 1.0 / 0.2 ));
         
         vec3 gamma9 = pow( gamma17, vec3( 1.0 /0.8504 , 1.0 / 0.5624, 1.0 / 0.8 ));
         
         vec3 add3 = gamma10 + gamma9;
         
         add3.r = smoothstep( 0.295, 1.0,  add3.r );
         add3.g = smoothstep( 0.2518, 1.0,  add3.g );
         add3.b = smoothstep( 0.0093, 1.0,  add3.b );
         
         gl_FragColor =vec4(add3 ,1.0);

     }
     
     
     );
    
}



char* FX3ShaderDemo::fragmentSoftElegance(){
    
    return SHADER_STRING
    (
     
     precision highp int;
     precision highp float;
     varying  vec2 textureCoordinate;
     uniform sampler2D texture0;
     
     
     uniform sampler2D tex;
     
     void main()
     {
         
         vec4 color =  texture2D(texture0, textureCoordinate);
         vec3 gamma19 = pow( color.rgb, vec3(1.0 /1.2));
         
         vec3 gamma3 = pow( color.rgb, vec3(1.0 /0.8 , 1.0/ 0.52, 1.0/0.8));
         vec3 mult2 = gamma3 * vec3( 0.7168,1.0,0.8011);
         
         vec3 gamma1 = pow( color.rgb, vec3( 1.0 / 1.85 , 1.0 / 2.1, 1.0));
         vec3 mult1 = gamma1 * vec3( 0.9083 ,  0.8415 , 0.5673 );
         vec3 gamma2= pow( mult1, vec3( 1.0 / 0.3 ));
         
         
         vec3 add1= mult2 + gamma2;
         
         vec3 grayXfer = vec3(0.3, 0.59, 0.11);
         vec3 gray = vec3(dot(grayXfer, add1));
         vec3 sat1 = mix( gray, add1 , 0.63);
         
         
         gl_FragColor =vec4(sat1 ,1.0);
     }
     
     
     );
    
}



char* FX3ShaderDemo::fragmentHolga(){
    
    return SHADER_STRING
    (
     
     precision highp int;
     precision highp float;
     varying  vec2 textureCoordinate;
     uniform sampler2D texture0;
     
     
     uniform sampler2D tex;
     
     void main()
    {
        
        vec4 color =  texture2D(texture0, textureCoordinate);
        vec3 grayXfer = vec3(0.3, 0.59, 0.11);
        vec3 gray = vec3(dot(grayXfer, color.rgb));
        vec3 sat1 = mix( gray, color.rgb , 1.5);
        
        
        vec3 sat3 = gray;
        vec3 add6 = sat3*0.4 + sat1*1.2;
        
        
        vec3 gamma22 = pow( add6, vec3(1.0 /0.82 ));
        vec3 gray2 = vec3(dot(grayXfer, gamma22));
        vec3 sat4 = mix( gray2, gamma22 , 1.5);
        
        sat4. r = smoothstep( 0.125, 1.0 ,sat4.r);
        sat4. g = smoothstep( 0.0636, 1.0 ,sat4.g);
        sat4. b = smoothstep( 0.0023, 1.0 ,sat4.b);
        
        gl_FragColor =vec4(sat4 ,1.0);
    }

     
     );
    
}

#pragma mark old packs


char* FX3ShaderDemo::fragmentSoho(){

    return SHADER_STRING
    (
     
     precision highp int;
     precision highp float;
     varying  vec2 textureCoordinate;
     uniform sampler2D texture0;
     
     float add(  float a,  float b,  float mixed){
         
         return mix( a, a+b, mixed);
     }
     float sub(  float a,  float b,  float mixed){
         
         return mix( a, a-b, mixed);
     }
     float div(  float a,  float b,  float mixed){
         
         return mix( a, a/b, mixed);
     }
     float mult(  float a,  float b,  float mixed){
         
         return mix( a, a*b, mixed);
     }
     float invert(  float a){
         
         return 1.0-a;
     }
     float contrast (  float a,  float val,  float center ){
         
         return (a - 0.5) * val + 0.5;
     }
     float gamma (  float a,  float val ) {
         
         return pow( a , (1.0/val));
     }
     vec4 gamma4 (  vec4 a,  float val ) {
         
         return pow( a , vec4(1.0/val));
     }
     vec4 bright4 (  vec4 a,  float val ) {
         
         return a * vec4( val );
     }
     
     vec4 vignette( vec4 color, float radius, float softness, vec2 center, vec2 coords){
         
         float d = sqrt(pow( abs(center.x -coords.x),2.0) + pow( abs(center.y -coords.y),2.0));
         d=d> radius ? 1.0:d * 1.0/radius;
         d=pow( d , ( 1.0/softness)) ;
         d=1.0-d;
         d=clamp (d,0.0,1.0);
         vec4 result =vec4(d);
         result.w=color.w;
         color =color*result;
         return color;
     }
     
     vec4 soho( vec4 color){
         
         // vec4 vignette1 = texture2D(texture1, textureCoordinate);
         // color = clamp(gamma4( color, 0.5 + ( (1.0-knobMix)*.6)), 0.01, 1.0 );
         float r = color.r;
         float g = color.g;
         float b = color.b;
         float invert2 = 1.0-r;
         float gamma2 = gamma( invert2, 0.6);
         float contrast2 = contrast( r, 2.0, 0.75 );
         float add2 = r+g*.4;
         float add3 = add2 + b;
         float add1 = g+b* .523;
         float sub1 = add1- r*.165;
         float gamma1 = gamma( b, 1.4);
         float sub2 = gamma1- r*.215;
         float add8 = sub2+ gamma2* .17;
         float inside1 = add8 * g;
         float add5 =  sub1 + inside1* .237;
         float div1 = r;
         float invert1 = 1.0-(add3);
         float add4 = (div1 + invert1 * .223);
         float add6 = ( add4 + contrast2 * 0.5);
         float mult1 = mult(add5, contrast2, 0.1);
         vec4 color2 = vec4( add6, mult1, add8, color.a);
         
         return color2;
     }
     
     void main() {
         
         
         vec2 center =vec2(0.5);
         vec4 color = texture2D(texture0, textureCoordinate);
         color=  soho(color);
         color=clamp(color,0.0,1.0);
         color = vignette( color, 0.65, 0.9, center, textureCoordinate);
         
         
         gl_FragColor = color ;
     }
     
     );
    
}




char* FX3ShaderDemo::fragmentCine(){
    
    return SHADER_STRING
    (
     precision highp int;
     precision highp float;
     varying  vec2 textureCoordinate;
     uniform sampler2D texture0;
     // uniform sampler2D texture1;
     //uniform  float knobIntensity;
     //uniform  float knobMix;
     vec4 gamma4 (  vec4 a,  float val ) {
         
         return pow( a , vec4(1.0/val));
     }
     vec4 bright4 (  vec4 a,  float val ) {
         
         return a * vec4( val );
     }
     
     vec4 vignette( vec4 color, float radius, float softness, vec2 center, vec2 coords){
         
         float d = sqrt(pow( abs(center.x -coords.x),2.0) + pow( abs(center.y -coords.y),2.0));
         d=d> radius ? 1.0:d * 1.0/radius;
         d=pow( d , ( 1.0/softness)) ;
         d=1.0-d;
         d=clamp (d,0.0,1.0);
         vec4 result =vec4(d);
         result.w=color.w;
         color =color*result;
         return color;
     }
     void main() {
         
         float knobMixInverted = 0.5;
         vec4 color = texture2D(texture0, textureCoordinate);
         
         
         //  vec4 vignette1 = texture2D(texture1, textureCoordinate);
         // color = clamp(gamma4( color,0.6+ ( knobMixInverted*0.3) ), 0.01, 1.0 );
         float r = color.r;
         float g = color.g;
         float b = color.b;
         float rMask = (1.0-b) + ( r * 0.5 + g * 0.5);
         float gMask = (1.0-g) + ( r * 0.5 + b * 0.5);
         float bMask = (1.0-r) + ( b * 0.5 + g * 0.5);
         float rMask2 = 1.0 - ( rMask* gMask);
         float gMask2 = 1.0 - (bMask * rMask);
         float bMask2 = 1.0 - (bMask * gMask);
         float r2 = r-rMask2;
         float g2 = g-gMask2;
         float b2 = b-bMask2;
         float l =( r2 *.3 +g2 *.59 +b2 *.11 ) ;
         vec4 color2 = vec4 ( r2, l, g2, color.a);
         
         
         
         // vec2 center =vec2(0.5);
         // color2 = vignette( color2, 0.65, 0.9, center, textureCoordinate);
         
         
         // vec4 gamma14 = mix( color2 , gamma4( color2, (0.2) + (0.3*knobMixInverted ) ) ,vignette1.r);
         // vec4 bright2 = mix( gamma14 , bright4( gamma14, (0.1) + (0.3*knobMixInverted ) ) ,vignette1.g);
         gl_FragColor = color2 ;
     });
    
    
    
}


char* FX3ShaderDemo::fragmentNone(){
    
    return SHADER_STRING
    (
     precision highp int;
     precision highp float;
     varying  vec2 textureCoordinate;
     uniform sampler2D texture0;
     
     void main() {
         
     
         vec4 color = texture2D(texture0, textureCoordinate);
         gl_FragColor = texture2D(texture0, textureCoordinate) ;
     });
    
    
    
}

#pragma mark converters




char* FX3ShaderDemo::fragmentRGBtoYUV(){
    
    return SHADER_STRING
    (
     
     precision highp int;
     precision highp float;
     varying  vec2 textureCoordinate;
     uniform sampler2D texture0;
     
   
     vec3 RGB2YUV ( vec3 color){
     
         vec3 yuv = mat3      ( 0.2123,    -0.09991,  0.615,
                               0.7152, -0.33609 ,   -.55861,
                               0.0722,    0.436,  -0.05639
                               )*color;
         
         
         
         
         return yuv;
     }
     
     
     vec3 YUV2RGB ( vec3 color){
         
     
         vec3 rgb = mat3(
                         1.0, 1.0,     1.0,
                         0.0, -.21482, 2.12798,
                         1.28033,  -0.38059, 0.0
                         )*color;
         
         return rgb;
     }
     
 
     
     void main() {
         
         
         vec4 color = texture2D(texture0, textureCoordinate);
         vec3 YUV = RGB2YUV( color.rgb);
         
         gl_FragColor = vec4( YUV,1.0) ;
     }
     
     );
    
}





char* FX3ShaderDemo::fragmentRGBtoRGBY(){
    
    return SHADER_STRING
    (
     
     precision highp int;
     precision highp float;
     varying  vec2 textureCoordinate;
     uniform sampler2D texture0;
     
     
     vec3 RGB2YUV ( vec3 color){
         
         vec3 yuv = mat3      ( 0.2123,    -0.09991,  0.615,
                               0.7152, -0.33609 ,   -.55861,
                               0.0722,    0.436,  -0.05639
                               )*color;
         
         
         
         
         return yuv;
     }
     
     
     vec3 YUV2RGB ( vec3 color){
         
         
         vec3 rgb = mat3(
                         1.0, 1.0,     1.0,
                         0.0, -.21482, 2.12798,
                         1.28033,  -0.38059, 0.0
                         )*color;
         
         return rgb;
     }
     
     
     
     void main() {
         
         
         vec4 color = texture2D(texture0, textureCoordinate);
         vec3 YUV = RGB2YUV( color.rgb);
         color.a= YUV.x;
         
         gl_FragColor = color ;
     }
     
     );
    
}



char* FX3ShaderDemo::fragmentRGBtoHSV(){
    
    return SHADER_STRING
    (
     
     precision highp int;
     precision highp float;
     varying  vec2 textureCoordinate;
     uniform sampler2D texture0;
     
     /*
      ** Hue, saturation, luminance
      */
     
     vec3 RGBToHSL(vec3 color)
    {
        vec3 hsl; // init to 0 to avoid warnings ? (and reverse if + remove first part)
        
        float fmin = min(min(color.r, color.g), color.b);    //Min. value of RGB
        float fmax = max(max(color.r, color.g), color.b);    //Max. value of RGB
        float delta = fmax - fmin;             //Delta RGB value
        
        hsl.z = (fmax + fmin) / 2.0; // Luminance
        
        if (delta == 0.0)		//This is a gray, no chroma...
        {
            hsl.x = 0.0;	// Hue
            hsl.y = 0.0;	// Saturation
        }
        else                                    //Chromatic data...
        {
            if (hsl.z < 0.5)
                hsl.y = delta / (fmax + fmin); // Saturation
            else
                hsl.y = delta / (2.0 - fmax - fmin); // Saturation
            
            float deltaR = (((fmax - color.r) / 6.0) + (delta / 2.0)) / delta;
            float deltaG = (((fmax - color.g) / 6.0) + (delta / 2.0)) / delta;
            float deltaB = (((fmax - color.b) / 6.0) + (delta / 2.0)) / delta;
            
            if (color.r == fmax )
                hsl.x = deltaB - deltaG; // Hue
            else if (color.g == fmax)
                hsl.x = (1.0 / 3.0) + deltaR - deltaB; // Hue
            else if (color.b == fmax)
                hsl.x = (2.0 / 3.0) + deltaG - deltaR; // Hue
            
            if (hsl.x < 0.0)
                hsl.x += 1.0; // Hue
            else if (hsl.x > 1.0)
                hsl.x -= 1.0; // Hue
        }
        
        return hsl;
    }
     
     float HueToRGB(float f1, float f2, float hue)
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
     
     vec3 HSLToRGB(vec3 hsl)
    {
        vec3 rgb;
        
        if (hsl.y == 0.0)
            rgb = vec3(hsl.z); // Luminance
        else
        {
            float f2;
            
            if (hsl.z < 0.5)
                f2 = hsl.z * (1.0 + hsl.y);
            else
                f2 = (hsl.z + hsl.y) - (hsl.y * hsl.z);
			
            float f1 = 2.0 * hsl.z - f2;
            
            rgb.r = HueToRGB(f1, f2, hsl.x + (1.0/3.0));
            rgb.g = HueToRGB(f1, f2, hsl.x);
            rgb.b= HueToRGB(f1, f2, hsl.x - (1.0/3.0));
        }
        
        return rgb;
    }
     
     
     void main() {
         
         
         vec4 color = texture2D(texture0, textureCoordinate);
         vec3 HSV = RGBToHSL( color.rgb);
 
         gl_FragColor = vec4( HSV,1.0) ;
     }
     
     );
    
}



char* FX3ShaderDemo::vertexScaleCenter()
{
    return SHADER_STRING
    (
     
     attribute mediump vec4 vertexPosition;
     attribute mediump vec4 vertexUV;
     varying mediump vec2 textureCoordinate;
     
     void main()
     {
         
         gl_Position = vertexPosition;
         textureCoordinate = (vertexUV.xy *vec2(0.6))+vec2(0.3);
     }
     );
}

char* FX3ShaderDemo::fragmentMagic(){
    
    return SHADER_STRING
    (
     
     precision highp int;
     precision highp float;
     varying  vec2 textureCoordinate;
     uniform sampler2D texture0;
     uniform float knobLut1D[256];
     
     vec3 RGBToHSL(vec3 color)
     {
         vec3 hsl; // init to 0 to avoid warnings ? (and reverse if + remove first part)
         
         float fmin = min(min(color.r, color.g), color.b);    //Min. value of RGB
         float fmax = max(max(color.r, color.g), color.b);    //Max. value of RGB
         float delta = fmax - fmin;             //Delta RGB value
         
         hsl.z = (fmax + fmin) / 2.0; // Luminance
         
         if (delta == 0.0)		//This is a gray, no chroma...
         {
             hsl.x = 0.0;	// Hue
             hsl.y = 0.0;	// Saturation
         }
         else                                    //Chromatic data...
         {
             if (hsl.z < 0.5)
                 hsl.y = delta / (fmax + fmin); // Saturation
             else
                 hsl.y = delta / (2.0 - fmax - fmin); // Saturation
             
             float deltaR = (((fmax - color.r) / 6.0) + (delta / 2.0)) / delta;
             float deltaG = (((fmax - color.g) / 6.0) + (delta / 2.0)) / delta;
             float deltaB = (((fmax - color.b) / 6.0) + (delta / 2.0)) / delta;
             
             if (color.r == fmax )
                 hsl.x = deltaB - deltaG; // Hue
             else if (color.g == fmax)
                 hsl.x = (1.0 / 3.0) + deltaR - deltaB; // Hue
             else if (color.b == fmax)
                 hsl.x = (2.0 / 3.0) + deltaG - deltaR; // Hue
             
             if (hsl.x < 0.0)
                 hsl.x += 1.0; // Hue
             else if (hsl.x > 1.0)
                 hsl.x -= 1.0; // Hue
         }
         
         return hsl;
     }
     
     float HueToRGB(float f1, float f2, float hue)
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
     
     vec3 HSLToRGB(vec3 hsl)
     {
         vec3 rgb;
         
         if (hsl.y == 0.0)
             rgb = vec3(hsl.z); // Luminance
         else
         {
             float f2;
             
             if (hsl.z < 0.5)
                 f2 = hsl.z * (1.0 + hsl.y);
             else
                 f2 = (hsl.z + hsl.y) - (hsl.y * hsl.z);
             
             float f1 = 2.0 * hsl.z - f2;
             
             rgb.r = HueToRGB(f1, f2, hsl.x + (1.0/3.0));
             rgb.g = HueToRGB(f1, f2, hsl.x);
             rgb.b= HueToRGB(f1, f2, hsl.x - (1.0/3.0));
         }
         
         return rgb;
     }
     
     float magicContrast( float x){
         
         float freq = 0.15;
         float amp  = 1.4;
         float scale =-.03;
         float center =0.5;
         
         float d =center-(abs(center-x));
         float dist = pow( d/freq ,2.0)/amp;
         float y= (sin(-dist)*scale)+x;
         
         return y;
     }
     
     void main() {
         
         //vec2 textureCoordinate =gl_TexCoord[0].xy;
         vec4 color = texture2D(texture0, textureCoordinate);
        // vec3 HSV = RGBToHSL( color.rgb);
        // HSV.b = magicContrast ( HSV.b);
        // vec3 RGB = HSLToRGB( HSV);
         
         gl_FragColor = vec4( RGB,1.0) ;
     }
     
     );
    
}

#pragma mark denoiser

char* FX3ShaderDemo::vertexDenoiser()
{
    return SHADER_STRING
    (
     precision highp int;
     precision highp float;
     attribute vec4 vertexPosition;
     attribute vec4 vertexUV;
     
     uniform   float knobInputWidth;
     uniform   float knobInputHeight;
     
     varying   vec2 textureCoordinate;
     varying   vec2 oneStepLeftTextureCoordinate;
     varying   vec2 twoStepsLeftTextureCoordinate;
     varying   vec2 oneStepRightTextureCoordinate;
     varying   vec2 twoStepsRightTextureCoordinate;
     
     
     void main() {
         
         
         gl_Position = vertexPosition;
         textureCoordinate = vertexUV.xy;
         
       
         vec2 pix = vec2( 1.0/knobInputWidth  , 1.0/knobInputHeight);
         
         vec2 firstOffset = vec2(  pix.x*0.75, pix.y);
         vec2 secondOffset = vec2( pix.x*1.25,  pix.y*1.5);
         
        // textureCoordinate = textureCoordinate;
         oneStepLeftTextureCoordinate = textureCoordinate - firstOffset;
         twoStepsLeftTextureCoordinate = textureCoordinate - secondOffset;
         oneStepRightTextureCoordinate = textureCoordinate + firstOffset;
         twoStepsRightTextureCoordinate = textureCoordinate + secondOffset;
     }
     
     
     );
    
}
char* FX3ShaderDemo::fragmentDenoiser()
{
    
    return SHADER_STRING
    (
     precision highp int;
     precision highp float;
     
     
     uniform sampler2D texture0;
     varying  vec2 textureCoordinate;
     varying  vec2 oneStepLeftTextureCoordinate;
     varying  vec2 twoStepsLeftTextureCoordinate;
     varying  vec2 oneStepRightTextureCoordinate;
     varying  vec2 twoStepsRightTextureCoordinate;
     
     void main() {
         
         vec3 grayXfer = vec3(0.3, 0.59, 0.11);
         
         
         lowp vec4 sum = texture2D(texture0, textureCoordinate) * 0.2270270270;
         sum += texture2D(texture0, oneStepLeftTextureCoordinate) * 0.3162162162;
         sum += texture2D(texture0, oneStepRightTextureCoordinate) * 0.3162162162;
         sum += texture2D(texture0, twoStepsLeftTextureCoordinate) * 0.0702702703;
         sum += texture2D(texture0, twoStepsRightTextureCoordinate) * 0.0702702703;
         

         vec4 originalColor = texture2D( texture0, textureCoordinate);
         vec3 gray = vec3( dot(sum.rgb,grayXfer));
         float saturation =(1.0-(distance (gray,sum.rgb) /1.5));
         saturation =  clamp(pow(saturation,20.0),0.0,1.0);
         
         
         // float lum = 1.0-((sum.r +sum.g +sum.b) /3.0);
       /*  sum.r = mix( originalColor.r, sum.r, saturation*1.2);
         sum.g = mix( originalColor.g, sum.g, saturation);
         sum.b = mix( originalColor.b, sum.b, saturation*1.3);*/
         sum = mix( originalColor, sum, saturation);
         
         
         
         
         gl_FragColor = sum;
        //  gl_FragColor =vec4(saturation);
     }
     
     
     );
    
    
}


/*
char* FX3ShaderDemo::vertexDenoiser()
{
    return SHADER_STRING
    (
     precision highp int;
     precision highp float;
     attribute vec4 vertexPosition;
     attribute vec4 vertexUV;
     const  int GAUSSIAN_SAMPLES = 9;
     uniform  float knobInputWidth;
     uniform  float knobInputHeight;
     uniform  float knobIntensity;
     uniform  float knobVertical;
     uniform  float knobHorizontal;
    
     varying  vec2 textureCoordinate;
     varying  vec2 blurCoordinates[GAUSSIAN_SAMPLES];
     void main() {
         
         
         gl_Position = vertexPosition;
         textureCoordinate = vertexUV.xy;
         float texelWidthOffset = (1.0 / knobInputWidth) *knobVertical;
         float texelHeightOffset = (1.0 / knobInputHeight) *knobHorizontal;
         int multiplier = 0;
         vec2 blurStep;
         float aspect = knobInputHeight/ knobInputWidth;
         vec2 singleStepOffset = vec2(texelWidthOffset* knobIntensity, texelHeightOffset* (knobIntensity *aspect) ) ;
         for ( int i = 0;
              i < GAUSSIAN_SAMPLES;
              i++) {
             
             multiplier = (i - ((GAUSSIAN_SAMPLES - 1) / 2));
             blurStep = float(multiplier) * singleStepOffset;
             blurCoordinates[i] = textureCoordinate.xy + blurStep;
         }
     }

    
     );
    
}
char* FX3ShaderDemo::fragmentDenoiser()
{
    
    return SHADER_STRING
    (
     precision highp int;
     precision highp float;
     
     uniform sampler2D texture0;
     const  int GAUSSIAN_SAMPLES = 9;
     varying  vec2 textureCoordinate;
     varying  vec2 blurCoordinates[GAUSSIAN_SAMPLES];
     void main() {
         
         vec3 grayXfer = vec3(0.3, 0.59, 0.11);
         
         
         vec4 sum = vec4(0.0);
         sum += texture2D(texture0, blurCoordinates[0]) * 0.05;
         sum += texture2D(texture0, blurCoordinates[1]) * 0.09;
         sum += texture2D(texture0, blurCoordinates[2]) * 0.12;
         sum += texture2D(texture0, blurCoordinates[3]) * 0.15;
         sum += texture2D(texture0, blurCoordinates[4]) * 0.18;
         sum += texture2D(texture0, blurCoordinates[5]) * 0.15;
         sum += texture2D(texture0, blurCoordinates[6]) * 0.12;
         sum += texture2D(texture0, blurCoordinates[7]) * 0.09;
         sum += texture2D(texture0, blurCoordinates[8]) * 0.05;
         
         
         vec4 originalColor = texture2D( texture0, textureCoordinate);
         vec3 gray = vec3( dot(sum.rgb,grayXfer));
         float saturation =(1.0-(distance (gray,sum.rgb) /1.5));
         saturation =  clamp(pow(saturation,20.0),0.0,1.0);
         
         // float lum = 1.0-((sum.r +sum.g +sum.b) /3.0);
         sum.r = mix( originalColor.r, sum.r, saturation*1.2);
         sum.g = mix( originalColor.g, sum.g, saturation);
         sum.b = mix( originalColor.b, sum.b, saturation*1.3);
         //mix( originalColor, sum, saturation);
         gl_FragColor = sum;
        // gl_FragColor =vec4(saturation);
     }

     
     );
    
    
}
*/
#pragma mark sharpener


char* FX3ShaderDemo::vertexSharpener()
{
    return SHADER_STRING
    (
     precision highp int;
     precision highp float;
     attribute vec4 vertexPosition;
     attribute vec4 vertexUV;
     
     uniform  float knobInputWidth;
     uniform  float knobInputHeight;
     uniform  float knobIntensity;
     
     varying vec2 textureCoordinate;
     varying vec2 leftTextureCoordinate;
     varying vec2 rightTextureCoordinate;
     varying vec2 topTextureCoordinate;
     varying vec2 bottomTextureCoordinate;
     
     varying float centerMultiplier;
     varying float edgeMultiplier;
     
     void main() {
         
         
         gl_Position = vertexPosition;
         float texelWidthOffset = (1.0 / knobInputWidth);
         float texelHeightOffset = (1.0 / knobInputHeight) ;
         
         mediump vec2 widthStep = vec2(texelWidthOffset, 0.0);
         mediump vec2 heightStep = vec2(0.0, texelHeightOffset);
         
         
         textureCoordinate          = vertexUV.xy;;
         leftTextureCoordinate      = textureCoordinate.xy - widthStep;
         rightTextureCoordinate     = textureCoordinate.xy + widthStep;
         topTextureCoordinate       = textureCoordinate.xy + heightStep;
         bottomTextureCoordinate    = textureCoordinate.xy - heightStep;
         
         centerMultiplier = 1.0 + 4.0 * knobIntensity;
         edgeMultiplier = knobIntensity;
     }
     
     
     );
    
}
char* FX3ShaderDemo::fragmentSharpener()
{
    
    return SHADER_STRING
    (
     precision highp float;
     
     varying highp vec2 textureCoordinate;
     varying highp vec2 leftTextureCoordinate;
     varying highp vec2 rightTextureCoordinate;
     varying highp vec2 topTextureCoordinate;
     varying highp vec2 bottomTextureCoordinate;
     
     varying highp float centerMultiplier;
     varying highp float edgeMultiplier;
     
     uniform sampler2D texture0;
     
     void main()
     {
         mediump vec3 textureColor          = texture2D(texture0, textureCoordinate).rgb;
         mediump vec3 leftTextureColor      = texture2D(texture0, leftTextureCoordinate).rgb;
         mediump vec3 rightTextureColor     = texture2D(texture0, rightTextureCoordinate).rgb;
         mediump vec3 topTextureColor       = texture2D(texture0, topTextureCoordinate).rgb;
         mediump vec3 bottomTextureColor    = texture2D(texture0, bottomTextureCoordinate).rgb;
         
         vec3 grayXfer = vec3(0.3, 0.59, 0.11);
         vec3 gray = vec3( dot(textureColor.rgb,grayXfer));
         float saturation =((distance (gray,textureColor.rgb) /1.5));
         saturation =  clamp(pow(saturation,1.0),0.0,1.0);
         
         vec4 sharpened = vec4((textureColor * centerMultiplier - (leftTextureColor * edgeMultiplier + rightTextureColor * edgeMultiplier + topTextureColor * edgeMultiplier + bottomTextureColor * edgeMultiplier)), texture2D(texture0, bottomTextureCoordinate).w);
         gl_FragColor = mix(vec4(textureColor,1.0),sharpened,saturation);
     }
     
     
     );
    
    
}
