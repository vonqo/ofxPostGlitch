//
//  CrBlueinvert.h
//  ofxPostGlitchExample
//
//  Created by Akira on 7/26/15.
//
//

#ifndef ofxPostGlitchExample_CrBlueinvert_h
#define ofxPostGlitchExample_CrBlueinvert_h

#include "ofMain.h"
#include "PGShaderConstants.h"

class CrBlueinvert : public ofShader
{
public:
    
    CrBlueinvert() : ofShader()
    {
        string vertexShader;
        string fragmentShader;
        
        if (ofIsGLProgrammableRenderer())
        {
            vertexShader = gl150VertShader;
            
            fragmentShader = GLSL150(
                                     uniform sampler2DRect image;
                                     uniform float rand;
                                     uniform int range;
                                     uniform float weight;
                                     
                                     in vec3 pos;
                                     
                                     out vec4 fragColor;
                                     
                                     void main (void)
                                     {
                                         float e = 2.718281828459045235360287471352;
                                         vec2 texCoord = vec2(pos.x , pos.y);
                                         vec4 col = texture(image,texCoord);
                                         
                                         vec3 k =   vec3(0.2,0.2,0.4);
                                         vec3 min = vec3(0.0,0.0,1.0);
                                         vec3 max = vec3(1.0,1.0,0.0);
                                         
                                         col.r = (1.0/(1.0+pow(e,(-k.r*((col.r*2.0)-1.0)*20.0)))*(max.r-min.r)+min.r);
                                         col.g = (1.0/(1.0+pow(e,(-k.g*((col.g*2.0)-1.0)*20.0)))*(max.g-min.g)+min.g);
                                         col.b = (1.0/(1.0+pow(e,(-k.b*((col.b*2.0)-1.0)*20.0)))*(max.b-min.b)+min.b);
                                         
                                         fragColor = col.rgba;
                                     }
                                     );
        }
        else
        {
            vertexShader = gl120VertShader;
            
            fragmentShader = GLSL120(
                                     uniform sampler2DRect image;
                                     uniform float rand;
                                     uniform int range;
                                     uniform float weight;
                                     
                                     varying vec3 pos;
                                     
                                     
                                     void main (void)
                                     {
                                         float e = 2.718281828459045235360287471352;
                                         vec2 texCoord = vec2(pos.x , pos.y);
                                         vec4 col = texture2DRect(image,texCoord);
                                         
                                         vec3 k =   vec3(0.2,0.2,0.4);
                                         vec3 min = vec3(0.0,0.0,1.0);
                                         vec3 max = vec3(1.0,1.0,0.0);
                                         
                                         col.r = (1.0/(1.0+pow(e,(-k.r*((col.r*2.0)-1.0)*20.0)))*(max.r-min.r)+min.r);
                                         col.g = (1.0/(1.0+pow(e,(-k.g*((col.g*2.0)-1.0)*20.0)))*(max.g-min.g)+min.g);
                                         col.b = (1.0/(1.0+pow(e,(-k.b*((col.b*2.0)-1.0)*20.0)))*(max.b-min.b)+min.b);
                                         
                                         gl_FragColor.rgba = col.rgba;
                                     }
                                     );
        }
        
        setupShaderFromSource(GL_VERTEX_SHADER, vertexShader);
        setupShaderFromSource(GL_FRAGMENT_SHADER, fragmentShader);
        bindDefaults();
        linkProgram();
    }
    
    ~CrBlueinvert() { unload(); }
};

#endif
