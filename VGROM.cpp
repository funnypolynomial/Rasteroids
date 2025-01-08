#include <Arduino.h>
#include "VGROM.h"

namespace VGROM {

#define LABEL_org 0x08A4
static const uint16_t ROM[] PROGMEM =
{
// Omitted: Test Pattern
// Omitted: Bank Error

#define LABEL_Credits 0x08A4
  0xA080, 0x0190, //     CUR     scale=00(/512)           x=400     y=128
  0x7000, 0x0000, //     VEC     scale=07(/4)   bri=0     x=0       y=0      
  0xF573,         //     SVEC    scale=00(/512) bri=7     x=3       y=-1     
  0xF173,         //     SVEC    scale=00(/512) bri=7     x=3       y=1      
  0xF178,         //     SVEC    scale=02(/128) bri=7     x=0       y=1      
  0xF177,         //     SVEC    scale=00(/512) bri=7     x=-3      y=1      
  0xF577,         //     SVEC    scale=00(/512) bri=7     x=-3      y=-1     
  0xF578,         //     SVEC    scale=02(/128) bri=7     x=0       y=-1     
  0x3180, 0x0200, //     VEC     scale=03(/64)  bri=0     x=512     y=384    
  0xF875,         //     SVEC    scale=01(/256) bri=7     x=-1      y=0      
  0xFD70,         //     SVEC    scale=01(/256) bri=7     x=0       y=-1     
  0xF871,         //     SVEC    scale=01(/256) bri=7     x=1       y=0      
  0xFD02,         //     SVEC    scale=01(/256) bri=0     x=2       y=-1     
  0xCB2E,         //     JSR     $0E5C               // 
  0xCB63,         //     JSR     $0EC6               // 
  0xCB56,         //     JSR     $0EAC               // 
  0xCB63,         //     JSR     $0EC6               // 
  0xCB2C,         //     JSR     $0E58               // 
  0xCA78,         //     JSR     $0CF0               // 
  0xCB02,         //     JSR     $0E04               // 
  0xCA78,         //     JSR     $0CF0               // 
  0xCAF3,         //     JSR     $0DE6               // 
  0xCABA,         //     JSR     $0D74               // 
  0xCB2C,         //     JSR     $0E58               // 
  0xCABA,         //     JSR     $0D74               // 
  0xCAD8,         //     JSR     $0DB0               // 
  0xEA8D,         //     JMP     $0D1A               // 
#define LABEL_Ship_Explosion 0x08E0
  0xFFC6,         //     SVEC    scale=01(/256) bri=12    x=-2      y=-3     
  0xFEC1,         //     SVEC    scale=01(/256) bri=12    x=1       y=-2     
  0xF1C3,         //     SVEC    scale=00(/512) bri=12    x=3       y=1      
  0xF1CD,         //     SVEC    scale=02(/128) bri=12    x=-1      y=1      
  0xF1C7,         //     SVEC    scale=00(/512) bri=12    x=-3      y=1      
  0xFDC1,         //     SVEC    scale=01(/256) bri=12    x=1       y=-1     
#define LABEL_Ship_explosion_pieces_velocity 0x08EC
  0x1ED8, // (-40,  30)
  0xEC32, // ( 50, -20)
  0xC400, // (  0, -60)
  0x143C, // ( 60,  20)
  0x460A, // ( 10,  70)
  0xD8D8, // (-40, -40)
#define LABEL_Shrapnel_Patterns_Jump_table_for_4 0x08F8
  0xC8D0,         //     JSR     $09A0               // 
  0xC8B5,         //     JSR     $096A               // 
  0xC896,         //     JSR     $092C               // 
  0xC880,         //     JSR     $0900               // 
#define LABEL_Shrapnel_pattern1 0x0900
  0xF80D,         //     SVEC    scale=03(/64)  bri=0     x=-1      y=0      
  0xF878,         //     SVEC    scale=03(/64)  bri=7     x=0       y=0      
  0xFD0D,         //     SVEC    scale=03(/64)  bri=0     x=-1      y=-1     
  0xF878,         //     SVEC    scale=03(/64)  bri=7     x=0       y=0      
  0xFD09,         //     SVEC    scale=03(/64)  bri=0     x=1       y=-1     
  0xF878,         //     SVEC    scale=03(/64)  bri=7     x=0       y=0      
  0xF10B,         //     SVEC    scale=02(/128) bri=0     x=3       y=1      
  0xF878,         //     SVEC    scale=03(/64)  bri=7     x=0       y=0      
  0xF50A,         //     SVEC    scale=02(/128) bri=0     x=2       y=-1     
  0xF878,         //     SVEC    scale=03(/64)  bri=7     x=0       y=0      
  0xF908,         //     SVEC    scale=03(/64)  bri=0     x=0       y=1      
  0xF878,         //     SVEC    scale=03(/64)  bri=7     x=0       y=0      
  0xF309,         //     SVEC    scale=02(/128) bri=0     x=1       y=3      
  0xF878,         //     SVEC    scale=03(/64)  bri=7     x=0       y=0      
  0xF30D,         //     SVEC    scale=02(/128) bri=0     x=-1      y=3      
  0xF878,         //     SVEC    scale=03(/64)  bri=7     x=0       y=0      
  0x5480, 0x0600, //     VEC     scale=05(/16)  bri=0     x=-512    y=-128   
  0xF878,         //     SVEC    scale=03(/64)  bri=7     x=0       y=0      
  0xF10F,         //     SVEC    scale=02(/128) bri=0     x=-3      y=1      
  0xF878,         //     SVEC    scale=03(/64)  bri=7     x=0       y=0      
  0xD000,         //     RTS                         
#define LABEL_Shrapnel_pattern2 0x092C
  0x3000, 0x0780, //     VEC     scale=03(/64)  bri=0     x=-896    y=0      
  0xF878,         //     SVEC    scale=03(/64)  bri=7     x=0       y=0      
  0x3780, 0x0780, //     VEC     scale=03(/64)  bri=0     x=-896    y=-896   
  0xF878,         //     SVEC    scale=03(/64)  bri=7     x=0       y=0      
  0x3780, 0x0380, //     VEC     scale=03(/64)  bri=0     x=896     y=-896   
  0xF878,         //     SVEC    scale=03(/64)  bri=7     x=0       y=0      
  0x40E0, 0x02A0, //     VEC     scale=04(/32)  bri=0     x=672     y=224    
  0xF878,         //     SVEC    scale=03(/64)  bri=7     x=0       y=0      
  0x35C0, 0x0380, //     VEC     scale=03(/64)  bri=0     x=896     y=-448   
  0xF878,         //     SVEC    scale=03(/64)  bri=7     x=0       y=0      
  0x3380, 0x0000, //     VEC     scale=03(/64)  bri=0     x=0       y=896    
  0xF878,         //     SVEC    scale=03(/64)  bri=7     x=0       y=0      
  0x42A0, 0x00E0, //     VEC     scale=04(/32)  bri=0     x=224     y=672    
  0xF878,         //     SVEC    scale=03(/64)  bri=7     x=0       y=0      
  0x42A0, 0x04E0, //     VEC     scale=04(/32)  bri=0     x=-224    y=672    
  0xF878,         //     SVEC    scale=03(/64)  bri=7     x=0       y=0      
  0x44E0, 0x0780, //     VEC     scale=04(/32)  bri=0     x=-896    y=-224   
  0xF878,         //     SVEC    scale=03(/64)  bri=7     x=0       y=0      
  0x40E0, 0x06A0, //     VEC     scale=04(/32)  bri=0     x=-672    y=224    
  0xF878,         //     SVEC    scale=03(/64)  bri=7     x=0       y=0      
  0xD000,         //     RTS                         
#define LABEL_Shrapnel_pattern3 0x096A
  0xF807,         //     SVEC    scale=01(/256) bri=0     x=-3      y=0      
  0xF878,         //     SVEC    scale=03(/64)  bri=7     x=0       y=0      
  0xFF07,         //     SVEC    scale=01(/256) bri=0     x=-3      y=-3     
  0xF878,         //     SVEC    scale=03(/64)  bri=7     x=0       y=0      
  0xFF03,         //     SVEC    scale=01(/256) bri=0     x=3       y=-3     
  0xF878,         //     SVEC    scale=03(/64)  bri=7     x=0       y=0      
  0x40C0, 0x0240, //     VEC     scale=04(/32)  bri=0     x=576     y=192    
  0xF878,         //     SVEC    scale=03(/64)  bri=7     x=0       y=0      
  0x3580, 0x0300, //     VEC     scale=03(/64)  bri=0     x=768     y=-384   
  0xF878,         //     SVEC    scale=03(/64)  bri=7     x=0       y=0      
  0xFB00,         //     SVEC    scale=01(/256) bri=0     x=0       y=3      
  0xF878,         //     SVEC    scale=03(/64)  bri=7     x=0       y=0      
  0x4240, 0x00C0, //     VEC     scale=04(/32)  bri=0     x=192     y=576    
  0xF878,         //     SVEC    scale=03(/64)  bri=7     x=0       y=0      
  0x4240, 0x04C0, //     VEC     scale=04(/32)  bri=0     x=-192    y=576    
  0xF878,         //     SVEC    scale=03(/64)  bri=7     x=0       y=0      
  0x44C0, 0x0700, //     VEC     scale=04(/32)  bri=0     x=-768    y=-192   
  0xF878,         //     SVEC    scale=03(/64)  bri=7     x=0       y=0      
  0x40C0, 0x0640, //     VEC     scale=04(/32)  bri=0     x=-576    y=192    
  0xF878,         //     SVEC    scale=03(/64)  bri=7     x=0       y=0      
  0xD000,         //     RTS                         
#define LABEL_Shrapnel_pattern4 0x09A0
  0x3000, 0x0680, //     VEC     scale=03(/64)  bri=0     x=-640    y=0      
  0xF878,         //     SVEC    scale=03(/64)  bri=7     x=0       y=0      
  0x3680, 0x0680, //     VEC     scale=03(/64)  bri=0     x=-640    y=-640   
  0xF878,         //     SVEC    scale=03(/64)  bri=7     x=0       y=0      
  0x3680, 0x0280, //     VEC     scale=03(/64)  bri=0     x=640     y=-640   
  0xF878,         //     SVEC    scale=03(/64)  bri=7     x=0       y=0      
  0x3140, 0x03C0, //     VEC     scale=03(/64)  bri=0     x=960     y=320    
  0xF878,         //     SVEC    scale=03(/64)  bri=7     x=0       y=0      
  0x3540, 0x0280, //     VEC     scale=03(/64)  bri=0     x=640     y=-320   
  0xF878,         //     SVEC    scale=03(/64)  bri=7     x=0       y=0      
  0x3280, 0x0000, //     VEC     scale=03(/64)  bri=0     x=0       y=640    
  0xF878,         //     SVEC    scale=03(/64)  bri=7     x=0       y=0      
  0x33C0, 0x0140, //     VEC     scale=03(/64)  bri=0     x=320     y=960    
  0xF878,         //     SVEC    scale=03(/64)  bri=7     x=0       y=0      
  0x33C0, 0x0540, //     VEC     scale=03(/64)  bri=0     x=-320    y=960    
  0xF878,         //     SVEC    scale=03(/64)  bri=7     x=0       y=0      
  0x44A0, 0x0680, //     VEC     scale=04(/32)  bri=0     x=-640    y=-160   
  0xF878,         //     SVEC    scale=03(/64)  bri=7     x=0       y=0      
  0x3140, 0x07C0, //     VEC     scale=03(/64)  bri=0     x=-960    y=320    
  0xF878,         //     SVEC    scale=03(/64)  bri=7     x=0       y=0      
  0xD000,         //     RTS                         
#define LABEL_Rock_Patterns_Jump_table_for_4 0x09DE
  0xC8F3,         //     JSR     $09E6               // 
  0xC8FF,         //     JSR     $09FE               // 
  0xC90D,         //     JSR     $0A1A               // 
  0xC91A,         //     JSR     $0A34               // 
#define LABEL_Rock_Pattern1 0x09E6
  0xF908,         //     SVEC    scale=03(/64)  bri=0     x=0       y=1      
  0xF979,         //     SVEC    scale=03(/64)  bri=7     x=1       y=1      
  0xFD79,         //     SVEC    scale=03(/64)  bri=7     x=1       y=-1     
  0xF67D,         //     SVEC    scale=02(/128) bri=7     x=-1      y=-2     
  0xF679,         //     SVEC    scale=02(/128) bri=7     x=1       y=-2     
  0xF68F,         //     SVEC    scale=02(/128) bri=8     x=-3      y=-2     
  0xF08F,         //     SVEC    scale=02(/128) bri=8     x=-3      y=0      
  0xF97D,         //     SVEC    scale=03(/64)  bri=7     x=-1      y=1      
  0xFA78,         //     SVEC    scale=03(/64)  bri=7     x=0       y=2      
  0xF979,         //     SVEC    scale=03(/64)  bri=7     x=1       y=1      
  0xFD79,         //     SVEC    scale=03(/64)  bri=7     x=1       y=-1     
  0xD000,         //     RTS                         
#define LABEL_Rock_Pattern2 0x09FE
  0xF10A,         //     SVEC    scale=02(/128) bri=0     x=2       y=1      
  0xF17A,         //     SVEC    scale=02(/128) bri=7     x=2       y=1      
  0xF97D,         //     SVEC    scale=03(/64)  bri=7     x=-1      y=1      
  0xF57E,         //     SVEC    scale=02(/128) bri=7     x=-2      y=-1     
  0xF17E,         //     SVEC    scale=02(/128) bri=7     x=-2      y=1      
  0xFD7D,         //     SVEC    scale=03(/64)  bri=7     x=-1      y=-1     
  0xF679,         //     SVEC    scale=02(/128) bri=7     x=1       y=-2     
  0xF67D,         //     SVEC    scale=02(/128) bri=7     x=-1      y=-2     
  0xFD79,         //     SVEC    scale=03(/64)  bri=7     x=1       y=-1     
  0xF179,         //     SVEC    scale=02(/128) bri=7     x=1       y=1      
  0xF58B,         //     SVEC    scale=02(/128) bri=8     x=3       y=-1     
  0xF38A,         //     SVEC    scale=02(/128) bri=8     x=2       y=3      
  0xF97D,         //     SVEC    scale=03(/64)  bri=7     x=-1      y=1      
  0xD000,         //     RTS                         
#define LABEL_Rock_Pattern3 0x0A1A
  0xF80D,         //     SVEC    scale=03(/64)  bri=0     x=-1      y=0      
  0xF57E,         //     SVEC    scale=02(/128) bri=7     x=-2      y=-1     
  0xF77A,         //     SVEC    scale=02(/128) bri=7     x=2       y=-3     
  0xF37A,         //     SVEC    scale=02(/128) bri=7     x=2       y=3      
  0xF778,         //     SVEC    scale=02(/128) bri=7     x=0       y=-3     
  0xF879,         //     SVEC    scale=03(/64)  bri=7     x=1       y=0      
  0xF37A,         //     SVEC    scale=02(/128) bri=7     x=2       y=3      
  0xF978,         //     SVEC    scale=03(/64)  bri=7     x=0       y=1      
  0xF37E,         //     SVEC    scale=02(/128) bri=7     x=-2      y=3      
  0xF07F,         //     SVEC    scale=02(/128) bri=7     x=-3      y=0      
  0xF77F,         //     SVEC    scale=02(/128) bri=7     x=-3      y=-3     
  0xF57A,         //     SVEC    scale=02(/128) bri=7     x=2       y=-1     
  0xD000,         //     RTS                         
#define LABEL_Rock_Pattern4 0x0A34
  0xF009,         //     SVEC    scale=02(/128) bri=0     x=1       y=0      
  0xF17B,         //     SVEC    scale=02(/128) bri=7     x=3       y=1      
  0xF168,         //     SVEC    scale=02(/128) bri=6     x=0       y=1      
  0xF27F,         //     SVEC    scale=02(/128) bri=7     x=-3      y=2      
  0xF07F,         //     SVEC    scale=02(/128) bri=7     x=-3      y=0      
  0xF669,         //     SVEC    scale=02(/128) bri=6     x=1       y=-2     
  0xF07F,         //     SVEC    scale=02(/128) bri=7     x=-3      y=0      
  0xF778,         //     SVEC    scale=02(/128) bri=7     x=0       y=-3     
  0xF77A,         //     SVEC    scale=02(/128) bri=7     x=2       y=-3     
  0xF17B,         //     SVEC    scale=02(/128) bri=7     x=3       y=1      
  0xF569,         //     SVEC    scale=02(/128) bri=6     x=1       y=-1     
  0xF969,         //     SVEC    scale=03(/64)  bri=6     x=1       y=1      
  0xF27F,         //     SVEC    scale=02(/128) bri=7     x=-3      y=2      
  0xD000,         //     RTS                         
#define LABEL_UFO_Jump_table_for_1 0x0A50
  0xC929,         //     JSR     $0A52               // 
//
  0xF10E,         //     SVEC    scale=02(/128) bri=0     x=-2      y=1      
  0xF8CA,         //     SVEC    scale=03(/64)  bri=12    x=2       y=0      
  0xF60B,         //     SVEC    scale=02(/128) bri=0     x=3       y=-2     
  0x6000, 0xD680, //     VEC     scale=06(/8)   bri=13    x=-640    y=0      
  0xF6DB,         //     SVEC    scale=02(/128) bri=13    x=3       y=-2     
  0xF8CA,         //     SVEC    scale=03(/64)  bri=12    x=2       y=0      
  0xF2DB,         //     SVEC    scale=02(/128) bri=13    x=3       y=2      
  0xF2DF,         //     SVEC    scale=02(/128) bri=13    x=-3      y=2      
  0xF2CD,         //     SVEC    scale=02(/128) bri=12    x=-1      y=2      
  0xF8CD,         //     SVEC    scale=03(/64)  bri=12    x=-1      y=0      
  0xF6CD,         //     SVEC    scale=02(/128) bri=12    x=-1      y=-2     
  0xF6DF,         //     SVEC    scale=02(/128) bri=13    x=-3      y=-2     
  0xD000,         //     RTS                         
#define LABEL_Player_Ships_Table 0x0A6E
  0x5290, // ShipDir0
  0x52A8, // ShipDir4
  0x52CC, // ShipDir8
  0x52F0, // ShipDir12
  0x5314, // ShipDir16
  0x5336, // ShipDir20
  0x535A, // ShipDir24
  0x537E, // ShipDir28
  0x53A2, // ShipDir32
  0x53C6, // ShipDir36
  0x53EA, // ShipDir40
  0x540E, // ShipDir44
  0x5432, // ShipDir48
  0x5456, // ShipDir52
  0x547A, // ShipDir56
  0x549E, // ShipDir60
  0x54C2, // ShipDir64
//ShipDir0:
  0xF60F,         //     SVEC    scale=02(/128) bri=0     x=-3      y=-2     
  0xFAC8,         //     SVEC    scale=03(/64)  bri=12    x=0       y=2      
  0xF9BD,         //     SVEC    scale=03(/64)  bri=11    x=-1      y=1      
  0x6500, 0xC300, //     VEC     scale=06(/8)   bri=12    x=768     y=-256   
  0x6500, 0xC700, //     VEC     scale=06(/8)   bri=12    x=-768    y=-256   
  0xF9B9,         //     SVEC    scale=03(/64)  bri=11    x=1       y=1      
  0xD000,         //     RTS                         
//ThrustDir0:  
  0xF9CE,         //     SVEC    scale=03(/64)  bri=12    x=-2      y=1      
  0xF9CA,         //     SVEC    scale=03(/64)  bri=12    x=2       y=1      
  0xD000,         //     RTS                         

//ShipDir4:
  0x4640, 0x06C0, //     VEC     scale=04(/32)  bri=0     x=-704    y=-576   
  0x5200, 0xC430, //     VEC     scale=05(/16)  bri=12    x=-48     y=512    
  0x41C0, 0xC620, //     VEC     scale=04(/32)  bri=12    x=-544    y=448    
  0x64B0, 0xC318, //     VEC     scale=06(/8)   bri=12    x=792     y=-176   
  0x6548, 0xC6E0, //     VEC     scale=06(/8)   bri=12    x=-736    y=-328   
  0x4220, 0xC1C0, //     VEC     scale=04(/32)  bri=12    x=448     y=544    
  0xD000,         //     RTS                         
//ThrustDir4:  
  0x50D0, 0xC610, //     VEC     scale=05(/16)  bri=12    x=-528    y=208    
  0x4260, 0xC3C0, //     VEC     scale=04(/32)  bri=12    x=960     y=608    
  0xD000,         //     RTS                         

//ShipDir8:  
  0x4680, 0x0680, //     VEC     scale=04(/32)  bri=0     x=-640    y=-640   
  0x43E0, 0xC4C0, //     VEC     scale=04(/32)  bri=12    x=-192    y=992    
  0x41A0, 0xC660, //     VEC     scale=04(/32)  bri=12    x=-608    y=416    
  0x6468, 0xC320, //     VEC     scale=06(/8)   bri=12    x=800     y=-104   
  0x6590, 0xC6C0, //     VEC     scale=06(/8)   bri=12    x=-704    y=-400   
  0x4260, 0xC1A0, //     VEC     scale=04(/32)  bri=12    x=416     y=608    
  0xD000,         //     RTS                         
//ThrustDir8:
  0x5090, 0xC630, //     VEC     scale=05(/16)  bri=12    x=-560    y=144    
  0x42C0, 0xC380, //     VEC     scale=04(/32)  bri=12    x=896     y=704    
  0xD000,         //     RTS                         

//ShipDir12:
  0x46C0, 0x0640, //     VEC     scale=04(/32)  bri=0     x=-576    y=-704   
  0x43E0, 0xC520, //     VEC     scale=04(/32)  bri=12    x=-288    y=992    
  0x4160, 0xC680, //     VEC     scale=04(/32)  bri=12    x=-640    y=352    
  0x6418, 0xC328, //     VEC     scale=06(/8)   bri=12    x=808     y=-24    
  0x65D0, 0xC698, //     VEC     scale=06(/8)   bri=12    x=-664    y=-464   
  0x4280, 0xC160, //     VEC     scale=04(/32)  bri=12    x=352     y=640    
  0xD000,         //     RTS                         
//ThrustDir12:
  0x5060, 0xC630, //     VEC     scale=05(/16)  bri=12    x=-560    y=96     
  0x4320, 0xC340, //     VEC     scale=04(/32)  bri=12    x=832     y=800    
  0xD000,         //     RTS                         

//ShipDir16:
  0xF70E,         //     SVEC    scale=02(/128) bri=0     x=-2      y=-3     
  0x43C0, 0xC580, //     VEC     scale=04(/32)  bri=12    x=-384    y=960    
  0x4120, 0xC6A0, //     VEC     scale=04(/32)  bri=12    x=-672    y=288    
  0x6038, 0xC328, //     VEC     scale=06(/8)   bri=12    x=808     y=56     
  0x6610, 0xC660, //     VEC     scale=06(/8)   bri=12    x=-608    y=-528   
  0x42A0, 0xC120, //     VEC     scale=04(/32)  bri=12    x=288     y=672    
  0xD000,         //     RTS                         
//ThrustDir16:
  0x5030, 0xC640, //     VEC     scale=05(/16)  bri=12    x=-576    y=48     
  0x4360, 0xC2E0, //     VEC     scale=04(/32)  bri=12    x=736     y=864    
  0xD000,         //     RTS                         

//ShipDir20:  
  0x4720, 0x05C0, //     VEC     scale=04(/32)  bri=0     x=-448    y=-800   
  0x4380, 0xC5E0, //     VEC     scale=04(/32)  bri=12    x=-480    y=896    
  0x40E0, 0xC6C0, //     VEC     scale=04(/32)  bri=12    x=-704    y=224    
  0x6088, 0xC320, //     VEC     scale=06(/8)   bri=12    x=800     y=136    
  0x6648, 0xC630, //     VEC     scale=06(/8)   bri=12    x=-560    y=-584   
  0x42C0, 0xC0E0, //     VEC     scale=04(/32)  bri=12    x=224     y=704    
  0xD000,         //     RTS                         
//ThrustDir20:
  0x5410, 0xC640, //     VEC     scale=05(/16)  bri=12    x=-576    y=-16    
  0x43A0, 0xC2A0, //     VEC     scale=04(/32)  bri=12    x=672     y=928    
  0xD000,         //     RTS                         

//ShipDir24:  
  0x4760, 0x0560, //     VEC     scale=04(/32)  bri=0     x=-352    y=-864   
  0x4360, 0xC640, //     VEC     scale=04(/32)  bri=12    x=-576    y=864    
  0x4080, 0xC6C0, //     VEC     scale=04(/32)  bri=12    x=-704    y=128    
  0x60D8, 0xC310, //     VEC     scale=06(/8)   bri=12    x=784     y=216    
  0x6680, 0xC5F0, //     VEC     scale=06(/8)   bri=12    x=-496    y=-640   
  0x42C0, 0xC080, //     VEC     scale=04(/32)  bri=12    x=128     y=704    
  0xD000,         //     RTS                         
//ThrustDir24:
  0x5440, 0xC630, //     VEC     scale=05(/16)  bri=12    x=-560    y=-64    
  0x43E0, 0xC240, //     VEC     scale=04(/32)  bri=12    x=576     y=992    
  0xD000,         //     RTS                         

//ShipDir28:  
  0x4780, 0x0500, //     VEC     scale=04(/32)  bri=0     x=-256    y=-896   
  0x4320, 0xC680, //     VEC     scale=04(/32)  bri=12    x=-640    y=800    
  0x4040, 0xC6E0, //     VEC     scale=04(/32)  bri=12    x=-736    y=64     
  0x6120, 0xC2F8, //     VEC     scale=06(/8)   bri=12    x=760     y=288    
  0x66B0, 0xC5B0, //     VEC     scale=06(/8)   bri=12    x=-432    y=-688   
  0x42E0, 0xC040, //     VEC     scale=04(/32)  bri=12    x=64      y=736    
  0xD000,         //     RTS                         
//ThrustDir28:
  0x5480, 0xC630, //     VEC     scale=05(/16)  bri=12    x=-560    y=-128   
  0x5210, 0xC0F0, //     VEC     scale=05(/16)  bri=12    x=240     y=528    
  0xD000,         //     RTS                         

//ShipDir32:  
  0x4780, 0x04C0, //     VEC     scale=04(/32)  bri=0     x=-192    y=-896   
  0x42E0, 0xC6E0, //     VEC     scale=04(/32)  bri=12    x=-736    y=736    
  0x4000, 0xC6E0, //     VEC     scale=04(/32)  bri=12    x=-736    y=0      
  0x6168, 0xC2D8, //     VEC     scale=06(/8)   bri=12    x=728     y=360    
  0x66D8, 0xC568, //     VEC     scale=06(/8)   bri=12    x=-360    y=-728   
  0x42E0, 0xC000, //     VEC     scale=04(/32)  bri=12    x=0       y=736    
  0xD000,         //     RTS                         
//ThrustDir32:
  0x54B0, 0xC620, //     VEC     scale=05(/16)  bri=12    x=-544    y=-176   
  0x5220, 0xC0B0, //     VEC     scale=05(/16)  bri=12    x=176     y=544    
  0xD000,         //     RTS                         

//ShipDir36:  
  0x47A0, 0x0460, //     VEC     scale=04(/32)  bri=0     x=-96     y=-928   
  0x4280, 0xC720, //     VEC     scale=04(/32)  bri=12    x=-800    y=640    
  0x4440, 0xC6E0, //     VEC     scale=04(/32)  bri=12    x=-736    y=-64    
  0x61B0, 0xC2B0, //     VEC     scale=06(/8)   bri=12    x=688     y=432    
  0x66F8, 0xC520, //     VEC     scale=06(/8)   bri=12    x=-288    y=-760   
  0x42E0, 0xC440, //     VEC     scale=04(/32)  bri=12    x=-64     y=736    
  0xD000,         //     RTS                         
//ThrustDir36:
  0x54F0, 0xC610, //     VEC     scale=05(/16)  bri=12    x=-528    y=-240   
  0x5230, 0xC080, //     VEC     scale=05(/16)  bri=12    x=128     y=560    
  0xD000,         //     RTS                         

//ShipDir40:  
  0x47A0, 0x0000, //     VEC     scale=04(/32)  bri=0     x=0       y=-928   
  0x4240, 0xC760, //     VEC     scale=04(/32)  bri=12    x=-864    y=576    
  0x4480, 0xC6C0, //     VEC     scale=04(/32)  bri=12    x=-704    y=-128   
  0x61F0, 0xC280, //     VEC     scale=06(/8)   bri=12    x=640     y=496    
  0x6710, 0xC4D8, //     VEC     scale=06(/8)   bri=12    x=-216    y=-784   
  0x42C0, 0xC480, //     VEC     scale=04(/32)  bri=12    x=-128    y=704    
  0xD000,         //     RTS                         
//ThrustDir40:
  0x4640, 0xC7E0, //     VEC     scale=04(/32)  bri=12    x=-992    y=-576   
  0x5230, 0xC040, //     VEC     scale=05(/16)  bri=12    x=64      y=560    
  0xD000,         //     RTS                         

//ShipDir44: 
  0x47A0, 0x0060, //     VEC     scale=04(/32)  bri=0     x=96      y=-928   
  0x41E0, 0xC780, //     VEC     scale=04(/32)  bri=12    x=-896    y=480    
  0x44E0, 0xC6C0, //     VEC     scale=04(/32)  bri=12    x=-704    y=-224   
  0x6230, 0xC248, //     VEC     scale=06(/8)   bri=12    x=584     y=560    
  0x6720, 0xC488, //     VEC     scale=06(/8)   bri=12    x=-136    y=-800   
  0x42C0, 0xC4E0, //     VEC     scale=04(/32)  bri=12    x=-224    y=704    
  0xD000,         //     RTS                         
//ThrustDir44:
  0x46A0, 0xC7A0, //     VEC     scale=04(/32)  bri=12    x=-928    y=-672   
  0x5240, 0xC010, //     VEC     scale=05(/16)  bri=12    x=16      y=576    
  0xD000,         //     RTS                         

//ShipDir48:  
  0x4780, 0x00C0, //     VEC     scale=04(/32)  bri=0     x=192     y=-896   
  0x4180, 0xC7C0, //     VEC     scale=04(/32)  bri=12    x=-960    y=384    
  0x4520, 0xC6A0, //     VEC     scale=04(/32)  bri=12    x=-672    y=-288   
  0x6260, 0xC210, //     VEC     scale=06(/8)   bri=12    x=528     y=608    
  0x6728, 0xC438, //     VEC     scale=06(/8)   bri=12    x=-56     y=-808   
  0x42A0, 0xC520, //     VEC     scale=04(/32)  bri=12    x=-288    y=672    
  0xD000,         //     RTS                         
//ThrustDir48:
  0x46E0, 0xC760, //     VEC     scale=04(/32)  bri=12    x=-864    y=-736   
  0x5240, 0xC430, //     VEC     scale=05(/16)  bri=12    x=-48     y=576    
  0xD000,         //     RTS                         

//ShipDir52:
  0x4780, 0x0100, //     VEC     scale=04(/32)  bri=0     x=256     y=-896   
  0x4120, 0xC7E0, //     VEC     scale=04(/32)  bri=12    x=-992    y=288    
  0x4560, 0xC680, //     VEC     scale=04(/32)  bri=12    x=-640    y=-352   
  0x6298, 0xC1D0, //     VEC     scale=06(/8)   bri=12    x=464     y=664    
  0x6728, 0xC018, //     VEC     scale=06(/8)   bri=12    x=24      y=-808   
  0x4280, 0xC560, //     VEC     scale=04(/32)  bri=12    x=-352    y=640    
  0xD000,         //     RTS                         
//ThrustDir52:
  0x4740, 0xC720, //     VEC     scale=04(/32)  bri=12    x=-800    y=-832   
  0x5230, 0xC460, //     VEC     scale=05(/16)  bri=12    x=-96     y=560    
  0xD000,         //     RTS                         

//ShipDir56:
  0x4760, 0x0160, //     VEC     scale=04(/32)  bri=0     x=352     y=-864   
  0x40C0, 0xC7E0, //     VEC     scale=04(/32)  bri=12    x=-992    y=192    
  0x45A0, 0xC660, //     VEC     scale=04(/32)  bri=12    x=-608    y=-416   
  0x62C0, 0xC190, //     VEC     scale=06(/8)   bri=12    x=400     y=704    
  0x6720, 0xC068, //     VEC     scale=06(/8)   bri=12    x=104     y=-800   
  0x4260, 0xC5A0, //     VEC     scale=04(/32)  bri=12    x=-416    y=608    
  0xD000,         //     RTS                         
//ThrustDir56:
  0x4780, 0xC6C0, //     VEC     scale=04(/32)  bri=12    x=-704    y=-896   
  0x5230, 0xC490, //     VEC     scale=05(/16)  bri=12    x=-144    y=560    
  0xD000,         //     RTS                         

//ShipDir60:  
  0x4720, 0x01C0, //     VEC     scale=04(/32)  bri=0     x=448     y=-800   
  0x5030, 0xC600, //     VEC     scale=05(/16)  bri=12    x=-512    y=48     
  0x45C0, 0xC620, //     VEC     scale=04(/32)  bri=12    x=-544    y=-448   
  0x62E0, 0xC148, //     VEC     scale=06(/8)   bri=12    x=328     y=736    
  0x6718, 0xC0B0, //     VEC     scale=06(/8)   bri=12    x=176     y=-792   
  0x4220, 0xC5C0, //     VEC     scale=04(/32)  bri=12    x=-448    y=544    
  0xD000,         //     RTS                         
//ThrustDir60:
  0x47C0, 0xC660, //     VEC     scale=04(/32)  bri=12    x=-608    y=-960   
  0x5210, 0xC4D0, //     VEC     scale=05(/16)  bri=12    x=-208    y=528    
  0xD000,         //     RTS                         

//ShipDir64:
  0xF70A,         //     SVEC    scale=02(/128) bri=0     x=2       y=-3     
  0xF8CE,         //     SVEC    scale=03(/64)  bri=12    x=-2      y=0      
  0xFDCD,         //     SVEC    scale=03(/64)  bri=12    x=-1      y=-1     
  0x6300, 0xC100, //     VEC     scale=06(/8)   bri=12    x=256     y=768    
  0x6700, 0xC100, //     VEC     scale=06(/8)   bri=12    x=256     y=-768   
  0xF9CD,         //     SVEC    scale=03(/64)  bri=12    x=-1      y=1      
//ThrustDir64:
  0xD000,         //     RTS                         
  0xFECD,         //     SVEC    scale=03(/64)  bri=12    x=-1      y=-2     
  0xFACD,         //     SVEC    scale=03(/64)  bri=12    x=-1      y=2      
  0xD000,         //     RTS                         

#define LABEL_Lives 0x0CDA
  0xF70E,         //     SVEC    scale=02(/128) bri=0     x=-2      y=-3     
  0xF87A,         //     SVEC    scale=03(/64)  bri=7     x=2       y=0      
  0xFD79,         //     SVEC    scale=03(/64)  bri=7     x=1       y=-1     
  0x6300, 0x7500, //     VEC     scale=06(/8)   bri=7     x=-256    y=768    
  0x6700, 0x7500, //     VEC     scale=06(/8)   bri=7     x=-256    y=-768   
  0xF979,         //     SVEC    scale=03(/64)  bri=7     x=1       y=1      
  0x60C0, 0x0280, //     VEC     scale=06(/8)   bri=0     x=640     y=192    
  0xD09F,         //     RTS                         

#define LABEL_Characters 0x0CF0
// "A"
  0xFA70,         //     SVEC    scale=01(/256) bri=7     x=0       y=2      
  0xF272,         //     SVEC    scale=00(/512) bri=7     x=2       y=2      
  0xF672,         //     SVEC    scale=00(/512) bri=7     x=2       y=-2     
  0xFE70,         //     SVEC    scale=01(/256) bri=7     x=0       y=-2     
  0xF906,         //     SVEC    scale=01(/256) bri=0     x=-2      y=1      
  0xF872,         //     SVEC    scale=01(/256) bri=7     x=2       y=0      
  0xF602,         //     SVEC    scale=00(/512) bri=0     x=2       y=-2     
  0xD000,         //     RTS                         

// "B"
  0xFB70,         //     SVEC    scale=01(/256) bri=7     x=0       y=3      
  0xF073,         //     SVEC    scale=00(/512) bri=7     x=3       y=0      
  0xF571,         //     SVEC    scale=00(/512) bri=7     x=1       y=-1     
  0xF570,         //     SVEC    scale=00(/512) bri=7     x=0       y=-1     
  0xF575,         //     SVEC    scale=00(/512) bri=7     x=-1      y=-1     
  0xF077,         //     SVEC    scale=00(/512) bri=7     x=-3      y=0      
  0xF003,         //     SVEC    scale=00(/512) bri=0     x=3       y=0      
  0xF571,         //     SVEC    scale=00(/512) bri=7     x=1       y=-1     
  0xF570,         //     SVEC    scale=00(/512) bri=7     x=0       y=-1     
  0xF575,         //     SVEC    scale=00(/512) bri=7     x=-1      y=-1     
  0xF077,         //     SVEC    scale=00(/512) bri=7     x=-3      y=0      
  0xF803,         //     SVEC    scale=01(/256) bri=0     x=3       y=0      
  0xD000,         //     RTS                         

// "C"
  0xFB70,         //     SVEC    scale=01(/256) bri=7     x=0       y=3      
  0xF872,         //     SVEC    scale=01(/256) bri=7     x=2       y=0      
  0xFF06,         //     SVEC    scale=01(/256) bri=0     x=-2      y=-3     
  0xF872,         //     SVEC    scale=01(/256) bri=7     x=2       y=0      
  0xF002,         //     SVEC    scale=00(/512) bri=0     x=2       y=0      
  0xD000,         //     RTS                         
  
// "D"
  0xFB70,         //     SVEC    scale=01(/256) bri=7     x=0       y=3      
  0xF072,         //     SVEC    scale=00(/512) bri=7     x=2       y=0      
  0xF672,         //     SVEC    scale=00(/512) bri=7     x=2       y=-2     
  0xF670,         //     SVEC    scale=00(/512) bri=7     x=0       y=-2     
  0xF676,         //     SVEC    scale=00(/512) bri=7     x=-2      y=-2     
  0xF076,         //     SVEC    scale=00(/512) bri=7     x=-2      y=0      
  0xF803,         //     SVEC    scale=01(/256) bri=0     x=3       y=0      
  0xD000,         //     RTS                         

// "E"
  0xFB70,         //     SVEC    scale=01(/256) bri=7     x=0       y=3      
  0xF872,         //     SVEC    scale=01(/256) bri=7     x=2       y=0      
  0xF705,         //     SVEC    scale=00(/512) bri=0     x=-1      y=-3     
  0xF077,         //     SVEC    scale=00(/512) bri=7     x=-3      y=0      
  0xF700,         //     SVEC    scale=00(/512) bri=0     x=0       y=-3     
  0xF872,         //     SVEC    scale=01(/256) bri=7     x=2       y=0      
  0xF002,         //     SVEC    scale=00(/512) bri=0     x=2       y=0      
  0xD000,         //     RTS                         

// "F"
  0xFB70,         //     SVEC    scale=01(/256) bri=7     x=0       y=3      
  0xF872,         //     SVEC    scale=01(/256) bri=7     x=2       y=0      
  0xF705,         //     SVEC    scale=00(/512) bri=0     x=-1      y=-3     
  0xF077,         //     SVEC    scale=00(/512) bri=7     x=-3      y=0      
  0xF700,         //     SVEC    scale=00(/512) bri=0     x=0       y=-3     
  0xF803,         //     SVEC    scale=01(/256) bri=0     x=3       y=0      
  0xD000,         //     RTS                         

// "G"
  0xFB70,         //     SVEC    scale=01(/256) bri=7     x=0       y=3      
  0xF872,         //     SVEC    scale=01(/256) bri=7     x=2       y=0      
  0xF670,         //     SVEC    scale=00(/512) bri=7     x=0       y=-2     
  0xF606,         //     SVEC    scale=00(/512) bri=0     x=-2      y=-2     
  0xF072,         //     SVEC    scale=00(/512) bri=7     x=2       y=0      
  0xF670,         //     SVEC    scale=00(/512) bri=7     x=0       y=-2     
  0xF876,         //     SVEC    scale=01(/256) bri=7     x=-2      y=0      
  0xF803,         //     SVEC    scale=01(/256) bri=0     x=3       y=0      
  0xD000,         //     RTS                         

// "H"
  0xFB70,         //     SVEC    scale=01(/256) bri=7     x=0       y=3      
  0xF700,         //     SVEC    scale=00(/512) bri=0     x=0       y=-3     
  0xF872,         //     SVEC    scale=01(/256) bri=7     x=2       y=0      
  0xF300,         //     SVEC    scale=00(/512) bri=0     x=0       y=3      
  0xFF70,         //     SVEC    scale=01(/256) bri=7     x=0       y=-3     
  0xF002,         //     SVEC    scale=00(/512) bri=0     x=2       y=0      
  0xD000,         //     RTS                         

// "I"
  0xF872,         //     SVEC    scale=01(/256) bri=7     x=2       y=0      
  0xF006,         //     SVEC    scale=00(/512) bri=0     x=-2      y=0      
  0xFB70,         //     SVEC    scale=01(/256) bri=7     x=0       y=3      
  0xF002,         //     SVEC    scale=00(/512) bri=0     x=2       y=0      
  0xF876,         //     SVEC    scale=01(/256) bri=7     x=-2      y=0      
  0xFF03,         //     SVEC    scale=01(/256) bri=0     x=3       y=-3     
  0xD000,         //     RTS                         

// "J"
  0xF200,         //     SVEC    scale=00(/512) bri=0     x=0       y=2      
  0xF672,         //     SVEC    scale=00(/512) bri=7     x=2       y=-2     
  0xF072,         //     SVEC    scale=00(/512) bri=7     x=2       y=0      
  0xFB70,         //     SVEC    scale=01(/256) bri=7     x=0       y=3      
  0xFF01,         //     SVEC    scale=01(/256) bri=0     x=1       y=-3     
  0xD000,         //     RTS                         

// "K"
  0xFB70,         //     SVEC    scale=01(/256) bri=7     x=0       y=3      
  0xF003,         //     SVEC    scale=00(/512) bri=0     x=3       y=0      
  0xF777,         //     SVEC    scale=00(/512) bri=7     x=-3      y=-3     
  0xF773,         //     SVEC    scale=00(/512) bri=7     x=3       y=-3     
  0xF003,         //     SVEC    scale=00(/512) bri=0     x=3       y=0      
  0xD000,         //     RTS                         

// "L"
  0xFB00,         //     SVEC    scale=01(/256) bri=0     x=0       y=3      
  0xFF70,         //     SVEC    scale=01(/256) bri=7     x=0       y=-3     
  0xF872,         //     SVEC    scale=01(/256) bri=7     x=2       y=0      
  0xF002,         //     SVEC    scale=00(/512) bri=0     x=2       y=0      
  0xD000,         //     RTS                         

// "M"
  0xFB70,         //     SVEC    scale=01(/256) bri=7     x=0       y=3      
  0xF672,         //     SVEC    scale=00(/512) bri=7     x=2       y=-2     
  0xF272,         //     SVEC    scale=00(/512) bri=7     x=2       y=2      
  0xFF70,         //     SVEC    scale=01(/256) bri=7     x=0       y=-3     
  0xF002,         //     SVEC    scale=00(/512) bri=0     x=2       y=0      
  0xD000,         //     RTS                         

// "N"
  0xFB70,         //     SVEC    scale=01(/256) bri=7     x=0       y=3      
  0xFF72,         //     SVEC    scale=01(/256) bri=7     x=2       y=-3     
  0xFB70,         //     SVEC    scale=01(/256) bri=7     x=0       y=3      
  0xFF01,         //     SVEC    scale=01(/256) bri=0     x=1       y=-3     
  0xD000,         //     RTS                         

// "O"
  0xFB70,         //     SVEC    scale=01(/256) bri=7     x=0       y=3      
  0xF872,         //     SVEC    scale=01(/256) bri=7     x=2       y=0      
  0xFF70,         //     SVEC    scale=01(/256) bri=7     x=0       y=-3     
  0xF876,         //     SVEC    scale=01(/256) bri=7     x=-2      y=0      
  0xF803,         //     SVEC    scale=01(/256) bri=0     x=3       y=0      
  0xD000,         //     RTS                         

// "P"
  0xFB70,         //     SVEC    scale=01(/256) bri=7     x=0       y=3      
  0xF872,         //     SVEC    scale=01(/256) bri=7     x=2       y=0      
  0xF770,         //     SVEC    scale=00(/512) bri=7     x=0       y=-3     
  0xF876,         //     SVEC    scale=01(/256) bri=7     x=-2      y=0      
  0xF703,         //     SVEC    scale=00(/512) bri=0     x=3       y=-3     
  0xF003,         //     SVEC    scale=00(/512) bri=0     x=3       y=0      
  0xD000,         //     RTS                         

// "Q"
  0xFB70,         //     SVEC    scale=01(/256) bri=7     x=0       y=3      
  0xF872,         //     SVEC    scale=01(/256) bri=7     x=2       y=0      
  0xFE70,         //     SVEC    scale=01(/256) bri=7     x=0       y=-2     
  0xF676,         //     SVEC    scale=00(/512) bri=7     x=-2      y=-2     
  0xF076,         //     SVEC    scale=00(/512) bri=7     x=-2      y=0      
  0xF202,         //     SVEC    scale=00(/512) bri=0     x=2       y=2      
  0xF672,         //     SVEC    scale=00(/512) bri=7     x=2       y=-2     
  0xF002,         //     SVEC    scale=00(/512) bri=0     x=2       y=0      
  0xD000,         //     RTS                         

// "R"
  0xFB70,         //     SVEC    scale=01(/256) bri=7     x=0       y=3      
  0xF872,         //     SVEC    scale=01(/256) bri=7     x=2       y=0      
  0xF770,         //     SVEC    scale=00(/512) bri=7     x=0       y=-3     
  0xF876,         //     SVEC    scale=01(/256) bri=7     x=-2      y=0      
  0xF001,         //     SVEC    scale=00(/512) bri=0     x=1       y=0      
  0xF773,         //     SVEC    scale=00(/512) bri=7     x=3       y=-3     
  0xF002,         //     SVEC    scale=00(/512) bri=0     x=2       y=0      
  0xD000,         //     RTS                         

// "S"
  0xF872,         //     SVEC    scale=01(/256) bri=7     x=2       y=0      
  0xF370,         //     SVEC    scale=00(/512) bri=7     x=0       y=3      
  0xF876,         //     SVEC    scale=01(/256) bri=7     x=-2      y=0      
  0xF370,         //     SVEC    scale=00(/512) bri=7     x=0       y=3      
  0xF872,         //     SVEC    scale=01(/256) bri=7     x=2       y=0      
  0xFF01,         //     SVEC    scale=01(/256) bri=0     x=1       y=-3     
  0xD000,         //     RTS                         

// "T"
  0xF002,         //     SVEC    scale=00(/512) bri=0     x=2       y=0      
  0xFB70,         //     SVEC    scale=01(/256) bri=7     x=0       y=3      
  0xF006,         //     SVEC    scale=00(/512) bri=0     x=-2      y=0      
  0xF872,         //     SVEC    scale=01(/256) bri=7     x=2       y=0      
  0xFF01,         //     SVEC    scale=01(/256) bri=0     x=1       y=-3     
  0xD000,         //     RTS                         

// "U"
  0xFB00,         //     SVEC    scale=01(/256) bri=0     x=0       y=3      
  0xFF70,         //     SVEC    scale=01(/256) bri=7     x=0       y=-3     
  0xF872,         //     SVEC    scale=01(/256) bri=7     x=2       y=0      
  0xFB70,         //     SVEC    scale=01(/256) bri=7     x=0       y=3      
  0xFF01,         //     SVEC    scale=01(/256) bri=0     x=1       y=-3     
  0xD000,         //     RTS                         

// "V"
  0xFB00,         //     SVEC    scale=01(/256) bri=0     x=0       y=3      
  0xFF71,         //     SVEC    scale=01(/256) bri=7     x=1       y=-3     
  0xFB71,         //     SVEC    scale=01(/256) bri=7     x=1       y=3      
  0xFF01,         //     SVEC    scale=01(/256) bri=0     x=1       y=-3     
  0xD000,         //     RTS                         

// "W"
  0xFB00,         //     SVEC    scale=01(/256) bri=0     x=0       y=3      
  0xFF70,         //     SVEC    scale=01(/256) bri=7     x=0       y=-3     
  0xF272,         //     SVEC    scale=00(/512) bri=7     x=2       y=2      
  0xF672,         //     SVEC    scale=00(/512) bri=7     x=2       y=-2     
  0xFB70,         //     SVEC    scale=01(/256) bri=7     x=0       y=3      
  0xFF01,         //     SVEC    scale=01(/256) bri=0     x=1       y=-3     
  0xD000,         //     RTS                         
  
// "X"
  0xFB72,         //     SVEC    scale=01(/256) bri=7     x=2       y=3      
  0xF806,         //     SVEC    scale=01(/256) bri=0     x=-2      y=0      
  0xFF72,         //     SVEC    scale=01(/256) bri=7     x=2       y=-3     
  0xF002,         //     SVEC    scale=00(/512) bri=0     x=2       y=0      
  0xD000,         //     RTS                         

// "Y"
  0xF002,         //     SVEC    scale=00(/512) bri=0     x=2       y=0      
  0xFA70,         //     SVEC    scale=01(/256) bri=7     x=0       y=2      
  0xF276,         //     SVEC    scale=00(/512) bri=7     x=-2      y=2      
  0xF802,         //     SVEC    scale=01(/256) bri=0     x=2       y=0      
  0xF676,         //     SVEC    scale=00(/512) bri=7     x=-2      y=-2     
  0xFE02,         //     SVEC    scale=01(/256) bri=0     x=2       y=-2     
  0xD000,         //     RTS                         

// "Z"
  0xFB00,         //     SVEC    scale=01(/256) bri=0     x=0       y=3      
  0xF872,         //     SVEC    scale=01(/256) bri=7     x=2       y=0      
  0xFF76,         //     SVEC    scale=01(/256) bri=7     x=-2      y=-3     
  0xF872,         //     SVEC    scale=01(/256) bri=7     x=2       y=0      
  0xF002,         //     SVEC    scale=00(/512) bri=0     x=2       y=0      
  0xD000,         //     RTS                         

// SPACE
  0xF803,         //     SVEC    scale=01(/256) bri=0     x=3       y=0      
  0xD000,         //     RTS                         

// "1"
  0xF002,         //     SVEC    scale=00(/512) bri=0     x=2       y=0      
  0xFB70,         //     SVEC    scale=01(/256) bri=7     x=0       y=3      
  0xFF02,         //     SVEC    scale=01(/256) bri=0     x=2       y=-3     
  0xD000,         //     RTS                         

// "2"
  0xFB00,         //     SVEC    scale=01(/256) bri=0     x=0       y=3      
  0xF872,         //     SVEC    scale=01(/256) bri=7     x=2       y=0      
  0xF770,         //     SVEC    scale=00(/512) bri=7     x=0       y=-3     
  0xF876,         //     SVEC    scale=01(/256) bri=7     x=-2      y=0      
  0xF770,         //     SVEC    scale=00(/512) bri=7     x=0       y=-3     
  0xF872,         //     SVEC    scale=01(/256) bri=7     x=2       y=0      
  0xF002,         //     SVEC    scale=00(/512) bri=0     x=2       y=0      
  0xD000,         //     RTS                         
  
// "3"
  0xF872,         //     SVEC    scale=01(/256) bri=7     x=2       y=0      
  0xFB70,         //     SVEC    scale=01(/256) bri=7     x=0       y=3      
  0xF876,         //     SVEC    scale=01(/256) bri=7     x=-2      y=0      
  0xF700,         //     SVEC    scale=00(/512) bri=0     x=0       y=-3     
  0xF872,         //     SVEC    scale=01(/256) bri=7     x=2       y=0      
  0xF702,         //     SVEC    scale=00(/512) bri=0     x=2       y=-3     
  0xD000,         //     RTS                         
  
// "4"
  0xFB00,         //     SVEC    scale=01(/256) bri=0     x=0       y=3      
  0xF770,         //     SVEC    scale=00(/512) bri=7     x=0       y=-3     
  0xF872,         //     SVEC    scale=01(/256) bri=7     x=2       y=0      
  0xF300,         //     SVEC    scale=00(/512) bri=0     x=0       y=3      
  0xFF70,         //     SVEC    scale=01(/256) bri=7     x=0       y=-3     
  0xF002,         //     SVEC    scale=00(/512) bri=0     x=2       y=0      
  0xD000,         //     RTS                         

// "5"
  0xF872,         //     SVEC    scale=01(/256) bri=7     x=2       y=0      
  0xF370,         //     SVEC    scale=00(/512) bri=7     x=0       y=3      
  0xF876,         //     SVEC    scale=01(/256) bri=7     x=-2      y=0      
  0xF370,         //     SVEC    scale=00(/512) bri=7     x=0       y=3      
  0xF872,         //     SVEC    scale=01(/256) bri=7     x=2       y=0      
  0xFF01,         //     SVEC    scale=01(/256) bri=0     x=1       y=-3     
  0xD000,         //     RTS                         

// "6"
  0xF300,         //     SVEC    scale=00(/512) bri=0     x=0       y=3      
  0xF872,         //     SVEC    scale=01(/256) bri=7     x=2       y=0      
  0xF770,         //     SVEC    scale=00(/512) bri=7     x=0       y=-3     
  0xF876,         //     SVEC    scale=01(/256) bri=7     x=-2      y=0      
  0xFB70,         //     SVEC    scale=01(/256) bri=7     x=0       y=3      
  0xFF03,         //     SVEC    scale=01(/256) bri=0     x=3       y=-3     
  0xD000,         //     RTS                         

// "7"
  0xFB00,         //     SVEC    scale=01(/256) bri=0     x=0       y=3      
  0xF872,         //     SVEC    scale=01(/256) bri=7     x=2       y=0      
  0xFF70,         //     SVEC    scale=01(/256) bri=7     x=0       y=-3     
  0xF002,         //     SVEC    scale=00(/512) bri=0     x=2       y=0      
  0xD000,         //     RTS                         

// "8"
  0xF872,         //     SVEC    scale=01(/256) bri=7     x=2       y=0      
  0xFB70,         //     SVEC    scale=01(/256) bri=7     x=0       y=3      
  0xF876,         //     SVEC    scale=01(/256) bri=7     x=-2      y=0      
  0xFF70,         //     SVEC    scale=01(/256) bri=7     x=0       y=-3     
  0xF300,         //     SVEC    scale=00(/512) bri=0     x=0       y=3      
  0xF872,         //     SVEC    scale=01(/256) bri=7     x=2       y=0      
  0xF702,         //     SVEC    scale=00(/512) bri=0     x=2       y=-3     
  0xD000,         //     RTS                         

// "9"
  0xF802,         //     SVEC    scale=01(/256) bri=0     x=2       y=0      
  0xFB70,         //     SVEC    scale=01(/256) bri=7     x=0       y=3      
  0xF876,         //     SVEC    scale=01(/256) bri=7     x=-2      y=0      
  0xF770,         //     SVEC    scale=00(/512) bri=7     x=0       y=-3     
  0xF872,         //     SVEC    scale=01(/256) bri=7     x=2       y=0      
  0xF702,         //     SVEC    scale=00(/512) bri=0     x=2       y=-3     
  0xD000,         //     RTS                         

#define LABEL_Cross_reference_table_for_character_data 0x0ED4
  0xCB2C,         //     JSR     $0E58               // SPACE 1
  0xCADD,         //     JSR     $0DBA               // O and 0 ... same pattern
  0xCB2E,         //     JSR     $0E5C               // 1
  0xCB32,         //     JSR     $0E64               // 2
  0xCB3A,         //     JSR     $0E74               // 3
  0xCB41,         //     JSR     $0E82               // 4
  0xCB48,         //     JSR     $0E90               // 5
  0xCB4F,         //     JSR     $0E9E               // 6
  0xCB56,         //     JSR     $0EAC               // 7 2
  0xCB5B,         //     JSR     $0EB6               // 8 3
  0xCB63,         //     JSR     $0EC6               // 9 4
  0xCA78,         //     JSR     $0CF0               // A 5
  0xCA80,         //     JSR     $0D00               // B 6
  0xCA8D,         //     JSR     $0D1A               // C 7
  0xCA93,         //     JSR     $0D26               // D 8
  0xCA9B,         //     JSR     $0D36               // E 9
  0xCAA3,         //     JSR     $0D46               // F 10
  0xCAAA,         //     JSR     $0D54               // G 11
  0xCAB3,         //     JSR     $0D66               // H 12
  0xCABA,         //     JSR     $0D74               // I 13
  0xCAC1,         //     JSR     $0D82               // J 14
  0xCAC7,         //     JSR     $0D8E               // K 15
  0xCACD,         //     JSR     $0D9A               // L 16
  0xCAD2,         //     JSR     $0DA4               // M 17
  0xCAD8,         //     JSR     $0DB0               // N 18
  0xCADD,         //     JSR     $0DBA               // O 19
  0xCAE3,         //     JSR     $0DC6               // P 20
  0xCAEA,         //     JSR     $0DD4               // Q 21
  0xCAF3,         //     JSR     $0DE6               // R 22
  0xCAFB,         //     JSR     $0DF6               // S 23
  0xCB02,         //     JSR     $0E04               // T 24
  0xCB08,         //     JSR     $0E10               // U 25
  0xCB0E,         //     JSR     $0E1C               // V 26
  0xCB13,         //     JSR     $0E26               // W 27
  0xCB1A,         //     JSR     $0E34               // X 28
  0xCB1F,         //     JSR     $0E3E               // Y 29
  0xCB26,         //     JSR     $0E4C               // Z 30
};

const uint16_t* Base()
{
  return ROM;
}

uint16_t AddrToOffset(uint16_t addr)
{
  // convert a ROM address to an type
  return (2*(addr - VGROM::BaseAddress) + VGROM::BaseAddress - LABEL_org)/2;
}

uint16_t Credits()
{
  return (LABEL_Credits - LABEL_org)/sizeof(uint16_t);
}

uint16_t Saucer()
{
  return (LABEL_UFO_Jump_table_for_1 - LABEL_org)/sizeof(uint16_t);
}

uint16_t Rock(uint8_t index)
{
  return (LABEL_Rock_Patterns_Jump_table_for_4 - LABEL_org)/sizeof(uint16_t) + (index % 4);
}

uint16_t Lives()
{
  return (LABEL_Lives - LABEL_org)/sizeof(uint16_t);
}

uint16_t Shrapnel(uint8_t index)
{
  return (LABEL_Shrapnel_Patterns_Jump_table_for_4 - LABEL_org)/sizeof(uint16_t) + (index % 4);
}


uint16_t Char(uint8_t index)
{
    return (LABEL_Cross_reference_table_for_character_data - LABEL_org)/sizeof(uint16_t) + index;
}
}
