//
//  Outline.h
//  ofxPostGlitchExample
//
//  Created by Akira on 7/27/15.
//
//

#ifndef ofxPostGlitchExample_Outline_h
#define ofxPostGlitchExample_Outline_h

#include "ofMain.h"
#include "PGShaderConstants.h"

class Outline : public ofShader
{
public:
    
    Outline() : ofShader()
    {
        string vertexShader;
        string fragmentShader;
        
        if (ofIsGLProgrammableRenderer())
        {
            vertexShader = gl150VertShader;
            
            fragmentShader = GLSL150(
                                     /*
                                      MAX-MINフィルタという手法を使ったエッジ検出の例です。
                                      周辺ピクセルの最大値と最小値を取り、その差を輝度として出力しています。
                                      */
                                     
                                     uniform sampler2DRect image;
                                     uniform float weight;
                                     in vec3 pos;
                                     
                                     out vec4 fragColor;
                                     
                                     void main (void)
                                     {
                                         int step = 3;
                                         vec4 cols[9];/*自分の周辺のピクセルの色情報*/
                                         vec2 texCoord = vec2(pos.x,pos.y);/*自分の色情報*/
                                         
                                         /*周辺の色情報をピックアップして、RGBの平均値(グレースケール)をR要素に代入する*/
                                         for (int i = 0;i < step;i++){
                                             for (int j = 0;j < step;j++){
                                                 cols[i*step+j] = texture(image,vec2((pos.x+float(j)-2.0), (pos.y+float(i)-2.0)));
                                                 cols[i*step+j].r = (cols[i*step+j].r + cols[i*step+j].g + cols[i*step+j].b) / 3.0;
                                             }
                                         }
                                         
                                         /*取得した色の中で、輝度の最大値と最小値をピックアップする*/
                                         float mn = 1.0;
                                         float mx = 0.0;
                                         for (int i = 0;i < step*step;i++){
                                             mn = min(cols[i].r,mn);
                                             mx = max(cols[i].r,mx);
                                         }
                                         
                                         /*最大・最小の差を計算して出力する*/
                                         float dst = abs(mx-mn);
                                         fragColor.a = 1.0;
                                         fragColor.rgb = vec3(dst,dst,dst);
                                     }
                                     );
   
        }
        else
        {
            vertexShader = gl120VertShader;
            
            fragmentShader = GLSL120(
                                     /*
                                      MAX-MINフィルタという手法を使ったエッジ検出の例です。
                                      周辺ピクセルの最大値と最小値を取り、その差を輝度として出力しています。
                                      */
                                     
                                     uniform sampler2DRect image;
                                     uniform float weight;
                                     varying vec3 pos;
                                     
                                     void main (void)
                                     {
                                         int step = 3;
                                         vec4 cols[9];/*自分の周辺のピクセルの色情報*/
                                         vec2 texCoord = vec2(pos.x,pos.y);/*自分の色情報*/
                                         
                                         /*周辺の色情報をピックアップして、RGBの平均値(グレースケール)をR要素に代入する*/
                                         for (int i = 0;i < step;i++){
                                             for (int j = 0;j < step;j++){
                                                 cols[i*step+j] = texture2DRect(image,vec2((pos.x+float(j)-2.0), (pos.y+float(i)-2.0)));
                                                 cols[i*step+j].r = (cols[i*step+j].r + cols[i*step+j].g + cols[i*step+j].b) / 3.0;
                                             }
                                         }
                                         
                                         /*取得した色の中で、輝度の最大値と最小値をピックアップする*/
                                         float mn = 1.0;
                                         float mx = 0.0;
                                         for (int i = 0;i < step*step;i++){
                                             mn = min(cols[i].r,mn);
                                             mx = max(cols[i].r,mx);
                                         }
                                         
                                         /*最大・最小の差を計算して出力する*/
                                         float dst = abs(mx-mn);
                                         gl_FragColor.a = 1.0;
                                         gl_FragColor.rgb = vec3(dst,dst,dst);
                                     }
                                     );
        }
        
        setupShaderFromSource(GL_VERTEX_SHADER, vertexShader);
        setupShaderFromSource(GL_FRAGMENT_SHADER, fragmentShader);
        bindDefaults();
        linkProgram();
    }
    
    ~Outline() { unload(); }
};

#endif
