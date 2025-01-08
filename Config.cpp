#include <Arduino.h>
#include "BTN.h"
#include "RTC.h"
#include "SparseXL.h"
#include "Game.h"
#include "Data.h"
#include "Config.h"

namespace Config {

  void Button(int x, int y, const uint8_t* pData, const word* palette)
  {
    // draw the given button with top-left at (x, y), using palette
    LCD_BEGIN_FILL(x, y, Data::ButtonSize, Data::ButtonSize);
    while (true)
    {
      uint8_t data = pgm_read_byte_near(pData++);
      if (data)
        LCD_FILL_COLOUR(data >> 2, pgm_read_word_near(palette + (data & 0x03)));
      else
        break;
    }
  }

  void Text(int16_t x, int16_t y, uint8_t idx)
  {
    // just 3 chars from above array, starting at idx
    for (uint8_t ch = 0; ch < 3; ch++, idx++)
    {
      LCD_BEGIN_FILL(x, y, 8, 8);
      for (uint8_t row = 0; row < 8; row++)
      {
        uint8_t data = pgm_read_byte_near(Data::Font() + 8*idx + row);
        uint8_t mask = 0x80;
        for (uint8_t col = 0; col < 8; col++, mask >>= 1)
        {
          LCD_FILL_BYTE(1, (data & mask) ? 0xFF : 0x00);
        }
      }
      x += 8;
    }
  }

  constexpr int ButtonTop = 5;
  constexpr int ButtonSetLeft = 200;
  constexpr int ButtonAdjLeft = 250;
  byte BottomY = ButtonTop + Data::ButtonSize;

  enum Btn { NoBtn, SetBtn, AdjBtn, OutsideBtn };

  Btn GetButtonPressed(bool touch)
  {
    // returns button pressed, or NoBtn/OutsideBtn
    // a touch on the graphical button, or a hard-key press
    if (touch)
    {
      int x, y;
      if (LCD_GET_TOUCH(x, y))
      {
        if (ButtonSetLeft <= x && x < ButtonSetLeft + Data::ButtonSize && y < BottomY)
          return SetBtn;
        else if (ButtonAdjLeft <= x && x < ButtonAdjLeft + Data::ButtonSize && y < BottomY)
          return AdjBtn;
        else if (y >= BottomY)
          // clicked outside config area
          return OutsideBtn;
      }
    }
    else
    {
      if (btn1Set.CheckButtonPress())
        return SetBtn;
      else if (btn2Adj.CheckButtonPress())
        return AdjBtn;
    }
    return NoBtn;
  }

  bool GetButtonUp(Btn btn, bool touch)
  {
    // returns true if the button is still pressed
    // touching anywhere, or the hard-key released
    if (touch)
    {
      int x, y;
      return !LCD_GET_TOUCH(x, y);
    }
    else
    {
      if (btn == SetBtn)
        return !btn1Set.IsDown();
      else if (btn == AdjBtn)
        return !btn2Adj.IsDown();
    }
    return false;
  }

  void SetTime(bool touch)
  {
    // set the RTC's time
#ifdef ENABLE_TIME_SCORE
    rtc.ReadTime();
    uint8_t hour24 = rtc.m_Hour24 % 24, minute = rtc.m_Minute % 60;
    int16_t TimeY, LivesY, LabelY;
    Game::GetElementPixelPositions(TimeY, LivesY);
    LabelY = max(TimeY + 1, ButtonTop + Data::ButtonSize + 2);
    BottomY = max(LabelY + 8 + 4, LivesY);
    // Clear to line
    LCD_FILL_BYTE(LCD_BEGIN_FILL(0, 0, LCD_WIDTH, BottomY), 0x00);
    // Hz line above asteroids area
    LCD_FILL_BYTE(LCD_BEGIN_FILL(0, BottomY, LCD_WIDTH, 1), 0xFF);
    // Fixed labels
    if (touch)
    {
      Text(ButtonSetLeft + (Data::ButtonSize - 3 * 8) / 2, LabelY, 0);   // "SET"
      Text(ButtonAdjLeft + (Data::ButtonSize - 3 * 8) / 2, LabelY, 3);   // "ADJ"
    }
    
    bool update = true;
    bool blink = false;
    bool save = false;
    Btn btnDown = NoBtn;
    uint8_t mask = 0x01;
    unsigned long idleMS, blinkMS;
    idleMS = blinkMS = millis();
    while (true)
    {
      if (btnDown == NoBtn)
      {
        btnDown = GetButtonPressed(touch);
        if (btnDown == SetBtn)
        {
          if (mask == 0x01)   // blinking hour->blinking minute
            mask = 0x02;
          else
            mask = 0x03;    // none blinking 2nd press of Set is being held
        }
        else if (btnDown == AdjBtn)
        {
          if (mask == 0x01)   // blinkng hour
          {
            hour24++;
            hour24 %= 24;
          }
          else
          {
            minute++;
            minute %= 60;
          }
        }
        else if (btnDown == OutsideBtn)
          // clicked outside config area, bail
          break;
        if (btnDown != NoBtn)
        {
          update = true;
          blink = false;
          idleMS = blinkMS = millis();
        }
      }
      else
      {
        // button is still down?
        if (GetButtonUp(btnDown, touch))
        {
          btnDown = NoBtn;
          if (mask == 0x03)   // done
          {
            save = true;
            break;
          }
        }
        update = (btnDown == NoBtn);
      }
      unsigned long nowMS = millis();
      if ((nowMS - blinkMS) > 500UL)
      {
        blink = !blink;
        update = true;
        blinkMS = millis();
      }
      if ((nowMS - idleMS) > 30000L)
        break;

      if (update)
      {
        Game::PaintConfigTime(hour24, minute, blink ? mask : 0x03);
        if (touch)
        {
          Button(ButtonSetLeft, ButtonTop, Data::ButtonImage(btnDown == SetBtn), Data::ButtonPalette(true));
          Button(ButtonAdjLeft, ButtonTop, Data::ButtonImage(btnDown == AdjBtn), Data::ButtonPalette(false));
        }
        update = false;
      }
    }
    if (save)
    {
      rtc.m_Hour24 = hour24;
      rtc.m_Minute = minute;
      rtc.WriteTime();
    }
#endif
  }

}
