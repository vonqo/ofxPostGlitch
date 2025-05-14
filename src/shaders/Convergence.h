//
//  Convergence.h
//  ofxPostGlitchExample
//
//  Created by Akira on 7/26/15.
//
//

#ifndef ofxPostGlitchExample_Convergence_h
#define ofxPostGlitchExample_Convergence_h

#include "ofMain.h"
#include "PGShaderConstants.h"

class Convergence : public ofShader
{
public:
    
    Convergence() : ofShader()
    {
        string vertexShader;
        string fragmentShader;
        
        if (ofIsGLProgrammableRenderer())
        {
            vertexShader = gl150VertShader;
            
            fragmentShader = GLSL150(
                                     uniform sampler2DRect image;
                                     uniform float rand;
                                     uniform float weight;
                                     
                                     in vec3 pos;
                                     
                                     out vec4 fragColor;
                                     
                                     void main (void)
                                     {
                                         vec2 texCoord = vec2(pos.x , pos.y);
                                         
                                         vec4 col = texture(image,texCoord);
                                         vec4 col_r = texture(image,texCoord + vec2(-45.0*rand*weight,0));
                                         vec4 col_l = texture(image,texCoord + vec2( 45.0*rand*weight,0));
                                         vec4 col_g = texture(image,texCoord + vec2(-12.5*rand*weight,0));
                                         
                                         
                                         col.b = col.b + col_r.b*max(1.0,sin(pos.y*1.2)*2.5)*rand;
                                         col.r = col.r + col_l.r*max(1.0,sin(pos.y*1.2)*2.5)*rand;
                                         col.g = col.g + col_g.g*max(1.0,sin(pos.y*1.2)*2.5)*rand;
                                         
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
                                     uniform float weight;
                                     
                                     varying vec3 pos;
                                     
                                     void main (void)
                                     {
                                         vec2 texCoord = vec2(pos.x , pos.y);
                                         
                                         vec4 col = texture2DRect(image,texCoord);
                                         vec4 col_r = texture2DRect(image,texCoord + vec2(-45.0*rand*weight,0));
                                         vec4 col_l = texture2DRect(image,texCoord + vec2( 45.0*rand*weight,0));
                                         vec4 col_g = texture2DRect(image,texCoord + vec2(-12.5*rand*weight,0));
                                         
                                         
                                         col.b = col.b + col_r.b*max(1.0,sin(pos.y*1.2)*2.5)*rand;
                                         col.r = col.r + col_l.r*max(1.0,sin(pos.y*1.2)*2.5)*rand;
                                         col.g = col.g + col_g.g*max(1.0,sin(pos.y*1.2)*2.5)*rand;
                                         
                                         gl_FragColor.rgba = col.rgba;
                                     }
                                     );
        }
        
        setupShaderFromSource(GL_VERTEX_SHADER, vertexShader);
        setupShaderFromSource(GL_FRAGMENT_SHADER, fragmentShader);
        bindDefaults();
        linkProgram();
    }
    
    ~Convergence() { unload(); }
};

#endif
