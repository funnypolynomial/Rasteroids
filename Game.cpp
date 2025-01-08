#include <Arduino.h>
#include "BTN.h"
#include "RTC.h"
#include "Game.h"
#include "SparseXL.h"
#include "DVG.h"
#include "VGROM.h"
#include "Objects.h"
#include "Bullets.h"
#include "Rocks.h"
#include "Config.h"
#include "Data.h"
#include "Saucer.h"

#ifdef DEBUG_STACK_CHECK
extern uint16_t stackHeadroom;
#endif

namespace Game
{
  constexpr int16_t LivesBeamY = DVG::beamHeight - 140;
  constexpr int16_t TimeBeamX =  120;
  constexpr int16_t TimeBeamY =  DVG::beamHeight - 80;
  constexpr int8_t  TimeScale = DVG::Mul4Scale;
  constexpr int8_t  TimePercent = 75;
  uint16_t animationStep = 0;

  void I2A(uint8_t i, char*& pBuff, char leading)
  {
    // convert i to 2-digit string at pBuff, using leading for the leading 0
    if (i < 10)
      *pBuff++ = leading;
    else
      *pBuff++ = '0' + i / 10;
    *pBuff++ = '0' + i % 10;
  }

  void DrawAtari()
  {
    // Draw "(C) 1979 ATARI INC"
#ifdef ENABLE_ATARI
#if ENABLE_ATARI == 1
    // lower and centred
    // bypass the DVG and blat to screen, covers asteroids etc
    // Much faster then rendering a lot of tiny lines. Introduces a little blink though, because after the main paint
    int width, height;
    const uint32_t* pData = Data::Atari(width, height);
    LCD_BEGIN_FILL((LCD_WIDTH - width)/2, LCD_HEIGHT - 2*height, width, height);
    uint32_t data = pgm_read_dword(pData++);
    int w = width;
    while (data)
    {
      uint32_t mask = 0b10000000000000000000000000000000UL;
      while (mask && w--)
      {
        LCD_FILL_BYTE(1, (data & mask) ? 0xFF : 0x00);
        mask >>= 1;
      }
      if (w <= 0)
        w = width;
      data = pgm_read_dword(pData++);
    }
#elif ENABLE_COPYRIGHT == 0
    // a little lower. but slightly off-centre as per original?
    DVG::Cursor(400, 40, DVG::UnityScale);
    DVG::Run(VGROM::Credits());
#endif
#endif
  }

  void GetElementPixelPositions(int16_t& TimeY, int16_t& LivesY)
  {
    TimeY  = DVG::ScaleY(TimeBeamY) + 1;
    LivesY = DVG::ScaleY(LivesBeamY) + 5;
  }

  void PaintConfigTime(uint8_t hour24, uint8_t min, uint8_t mask)
  {
    // paint just the time, mask is 0b000000HM, if the bit is set the value is shown, otherwise blank
    // clears screen down to the bottom of the text
    int16_t TimeY, LivesY;
    GetElementPixelPositions(TimeY, LivesY);
    SparseXL::Clear(0);
    DVG::Cursor(TimeBeamX, TimeBeamY, TimeScale);
    char buff[5];
    char* pBuff = buff;
    memset(buff, ' ', 4);
    if (mask & 0x02)
      I2A(hour24, pBuff, '0');
    else
      pBuff += 2;
    if (mask & 0x01)
      I2A(min, pBuff, '0');
    else
      pBuff += 2;
    *pBuff = 0;
    DVG::Text(buff, TimePercent);
    byte* pRowStart = NULL;
    SparseXL::Paint(0, 0, 0, TimeY, LCD_WIDTH/2, pRowStart, RGB(255, 255, 255));
  }

  void DrawScore()
  {
    // draw 4-digit score. position and scale tweaked from original
    
#ifdef DEBUG_STACK_CHECK
    // report stack headroom in score
    char strBuffer[5];
    char* pStr = strBuffer;
    I2A(stackHeadroom / 100, pStr, ' ');
    I2A(stackHeadroom % 100, pStr, '0');
    *pStr = 0;
    DVG::Cursor(TimeBeamX, TimeBeamY, TimeScale);
    DVG::Text(strBuffer, TimePercent);
    return;
#endif    

#ifdef ENABLE_SCORE
    DVG::Cursor(TimeBeamX, TimeBeamY, TimeScale);
    char buff[5];
    char* pBuff = buff;
#ifdef ENABLE_TIME_SCORE
    rtc.ReadTime();
#ifdef ENABLE_TIME_24HOUR
    I2A(rtc.m_Hour24, pBuff, '0');
#else
    byte hour = rtc.m_Hour24;
    if (hour > 12)
      hour -= 12;
    else if (hour == 0)
      hour = 12;
    I2A(hour, pBuff, ' ');
#endif
    I2A(rtc.m_Minute, pBuff, '0');
#else
    I2A(OPTION_SCORE / 100, pBuff, ' ');
    I2A(OPTION_SCORE % 100, pBuff, '0');
#endif
    * pBuff = 0;
    DVG::Text(buff, TimePercent);
#endif
  }

  void DrawLives()
  {
#ifdef ENABLE_LIVES
    // draw <lives> ships. position and scale tweaked from original
    DVG::Cursor(160, LivesBeamY, DVG::Div2Scale);
    for (int l = 0; l < OPTION_LIVES; l++)
      DVG::Run(VGROM::Lives(), 80);
#endif
  }

  void AnimationStep()
  {
    // advance all the objects
    animationStep++;
    Rocks::AnimationStep();
    Saucer::AnimationStep();
    Bullets::AnimationStep();
  }

  static const char Splash1[] PROGMEM = "RASTEROIDS";
  static const char Splash2[] PROGMEM = "MEW            MMXXV";
  void Splash()
  {
    // show splash screen -- lines of text, saucer and rocks move across screen
    // half-scale objects on large LCD to not overflow the sparse pool
    Rocks::Splash(Objects::maxY/6, Objects::maxY/6);
    Saucer::Splash(5*Objects::maxY/6);
    animationStep = 1; // bypass  fire/jink logic etc
    bool exists = true;
    do
    {
      exists = Saucer::Exists();
      SparseXL::Clear(0);
      DVG::Cursor(DVG::beamWidth/4, DVG::beamHeight/2, 2);
      DVG::Text(Splash1, 100, true);
      DVG::Cursor(DVG::beamWidth/4, DVG::beamHeight/2 - 50, 1);
      DVG::Text(Splash2, 100, true);
      Rocks::Draw();
      Saucer::Draw();
      Rocks::AnimationStep();
      Saucer::AnimationStep();
      byte* pRowStart = NULL;
      SparseXL::Paint(0, 0, 0, LCD_HEIGHT, LCD_WIDTH, pRowStart, RGB(255, 255, 255));
    } while (exists);
    delay(2000);
  }

  void Init()
  {
    // initialise all the objects
    animationStep = 0;
    Bullets::Init();
    Rocks::InitWave();
    Saucer::Init();
  }

  void Randomize(unsigned long ms)
  {
    // set the seed from the RTC, if present, or the ms count, if non-zero
    unsigned long seed = 0;
#ifdef RTC_I2C_ADDRESS
    (void)ms;
    rtc.ReadTime(true);
    seed = ((unsigned long)rtc.m_Second << 16 | (unsigned long)rtc.m_Hour24 << 8 | (unsigned long)rtc.m_Minute) ^ 0xDEADBEAFUL;
#else
    if (ms)
      seed = ms ^ 0xDECAFBADUL;
#endif
    if (seed)
      Objects::RandomSeed(seed);
  }

  void CheckInteraction()
  {
    // check for a touch or button-press, and process
    int x, y;
    bool restart = false;
    if (btn1Set.CheckButtonPress())
      Config::SetTime(false);
    else if (btn2Adj.CheckButtonPress())
      restart = true; // Adj restarts
    else if (LCD_GET_TOUCH(x, y))
    {
      (void)x;
      if (y > DVG::ScaleY(LivesBeamY))
        restart = true; // touching the lower area restarts
      else
        Config::SetTime(true); // touching in the score area configures the time
    }

    if (restart)
    {
      // randomize based on time of click
      Randomize(millis());
      Init();
    }
  }

  void Draw()
  {
    // draw everything
    SparseXL::Clear(0);
    DrawAtari();        // 46ms
    DrawLives();         // 24ms
    DrawScore();          // 24ms
    Rocks::Draw();
    Saucer::Draw();
    Bullets::Draw();
    byte* pRowStart = NULL;
    SparseXL::Paint(0, 0, 0, LCD_HEIGHT, LCD_WIDTH, pRowStart, RGB(255, 255, 255));
    DrawAtari();
    if (SparseXL::full)
    {
      // sparse is full -- reset!
      Init();
    }
  }
}
