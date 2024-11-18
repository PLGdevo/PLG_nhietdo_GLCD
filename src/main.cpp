#include <khaibao.h>

// xử lý cảm biến
void xulycambien()
{
  int giatrinhietdo = analogRead(sensorpin);
  float analogReadMax = 4096.0;
  float mV = (giatrinhietdo / analogReadMax) * 5000.0;
  nhietdo = mV / 10.0;
}
// Chế độ làm việc-----------------------------------------------------------------------------------
void MODE_1()
{
}
void MODE_2()
{
}
void MODE_3()
{
}

// Hiển thị bản chế độ-------------------------------------------------------------------------------
void MODE1()
{
  GLCD.SetFontColor(0);
  GLCD.CursorTo(0, 1);
  GLCD.print("-> Setting WiFi");
  GLCD.SetFontColor(255);
  GLCD.CursorTo(0, 3);
  GLCD.print("   Setting Threshold");
  GLCD.CursorTo(0, 5);
  GLCD.print("   ON/OFF algorithm");
}
void MODE2()
{
  GLCD.SetFontColor(255);
  GLCD.CursorTo(0, 1);
  GLCD.print("   Setting WiFi");
  GLCD.SetFontColor(0);
  GLCD.CursorTo(0, 3);
  GLCD.print("-> Setting Threshold");
  GLCD.SetFontColor(255);
  GLCD.CursorTo(0, 5);
  GLCD.print("   ON/OFF algorithm");
}
void MODE3()
{
  GLCD.CursorTo(0, 1);
  GLCD.print("   Setting WiFi");
  GLCD.CursorTo(0, 3);
  GLCD.print("   Setting Threshold");
  GLCD.SetFontColor(0);
  GLCD.CursorTo(0, 5);
  GLCD.print("-> ON/OFF algorithm");
}

// Hiển thị màn hình làm việc của chế độ
void hienthi1()
{
  GLCD.ClearScreen();
  GLCD.SetFontColor(255);
  GLCD.CursorTo(0, 0);
  GLCD.print("Comming Soon ");
  digitalWrite(14, HIGH);
}
void hienthi2()
{
  GLCD.ClearScreen();
  GLCD.SetFontColor(255);
  GLCD.CursorTo(3, 0);
  GLCD.print("SETTING LIMIT TEMP");
}
void hienthi3()
{
  GLCD.SetFontColor(255);
  GLCD.FillRect(0, 0, 192, 64, 0);
  GLCD.CursorTo(7, 0);
  GLCD.print("ON/OFF algorithm");
}

// Hàm xử lý nút down và up--------------------------------------------------------------------------
void xulytinhieunut()
{
  unsigned thoigian = millis();
  if (thoigian - thoigiantruockhibamnut >= thoigianbamnut)
  {
    thoigiantruockhibamnut = thoigian;
    int len = digitalRead(nutup);
    int xuong = digitalRead(nutdown);
    if (len == LOW)
    {
      vitri--;
      if (vitri <= 0)
      {
        vitri = 3;
      }
    }
    if (xuong == LOW)
    {
      vitri++;
      if (vitri > 3)
      {
        vitri = 1;
      }
    }
    if (vitri != lastvitri)
    {
      if (vitri == 1)
      {
        MODE1();
      }
      if (vitri == 2)
      {
        MODE2();
      }
      if (vitri == 3)
      {
        MODE3();
      }
      lastvitri = vitri;
    }
  }

  //---------------------------------------------------------------------
}
// Xử lý nút enter và forward-------------------------------------------------------------------------
void SelectMode()
{
  int enter = digitalRead(nutenter);
  if (enter != lastenter)
  {
    if (enter == 0)
    {
      chedo = 1;
    }
  }
  int back = digitalRead(nutforward);
  if (back != lastback)
  {
    if (back == 0)
    {
      chedo = 2;
    }
  }
  delay(50);
  lastenter = enter;
  lastback = back;
}
// xử lý các lệnh------------------------------------------------------------------------------------
void program()
{
  if (lastchedo != chedo)
  {
    if (chedo == 2)
    {
      GLCD.ClearScreen();
      GLCD.SetFontColor(255);
      digitalWrite(14, LOW);
      vitri = lastvitri; // Quay lại vị trí trước đó
      if (vitri == 1)
      {
        MODE1();
      }
      else if (vitri == 2)
      {
        MODE2();
      }
      else if (vitri == 3)
      {
        MODE3();
      }
    }
    // xử lý các chế độ khi ấn enter---------------------------------------------
    if (chedo == 1)
    {
      switch (vitri)
      {
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////
      case 1:
        hienthi1();
        // GLCD.CursorTo(13, 0);
        // GLCD.print(nhietdo);
        // GLCD.print(" C");
        // while (vitri == 1)
        // {
        //   float tongNhietdo = 0;
        //   for (i = 0; i < 1000; i++)
        //   {
        //     xulycambien();
        //     tongNhietdo += nhietdo;
        //   }
        //   delay(10);
        //   nhietdo = tongNhietdo / 1000.0;
        //   // Chỉ cập nhật GLCD nếu nhiệt độ thay đổi
        //   if (lastnhietdo != nhietdo)
        //   {
        //     GLCD.CursorTo(13, 0);
        //     GLCD.print("           ");
        //     GLCD.CursorTo(13, 0);
        //     GLCD.print(nhietdo);
        //     GLCD.print(" C");
        //     lastnhietdo = nhietdo;
        //   }
        //   delay(500);
        if (digitalRead(13) == LOW)
        {
          break;
        }
        // }
        break;
        /////////////////////////////////////////////////////////////////////////////////////////////////////////
      case 2: // xử lý mode 2
        hienthi2();
        Thresholdmax = EEPROM.read(2);
        Thresholdmin = EEPROM.read(3);
        GLCD.CursorTo(0, 2);
        GLCD.print("  LIMIT MAX TEMP: ");
        GLCD.CursorTo(18, 2);
        GLCD.print(Thresholdmax);
        GLCD.print(" °C");
        GLCD.CursorTo(0, 4);
        GLCD.print("  LIMIT MIN TEMP: ");
        GLCD.CursorTo(18, 4);
        GLCD.print(Thresholdmin);
        GLCD.print(" °C");
        Serial.println(vitri);
        while (vitri == 2)
        {
          unsigned thoigian = millis();
          if (thoigian - thoigiantruockhibamnut >= thoigianbamnut)
          {
            thoigiantruockhibamnut = thoigian;
            int len = digitalRead(nutup);
            int xuong = digitalRead(nutdown);
            int enter = digitalRead(nutenter);
            if (enter == LOW)
            {
              mode = !mode;
              delay(80);
            } // chế độ điều chỉnh Max
            if (mode == 0)
            {
              GLCD.CursorTo(0, 2);
              GLCD.print("<>");
              GLCD.CursorTo(0, 4);
              GLCD.print("  ");
              if (len == LOW)
              {
                Thresholdmax--;
                if (Thresholdmax <= 0)
                {
                  Thresholdmax = 100;
                }
              }
              if (xuong == LOW)
              {
                Thresholdmax++;
                if (Thresholdmax > 100)
                {
                  Thresholdmax = 0;
                }
              }
              if (Thresholdmax != lastThresholdmax)
              {
                EEPROM.write(2, Thresholdmax);
                EEPROM.commit();
                GLCD.CursorTo(18, 2);
                GLCD.print("                 ");
                GLCD.CursorTo(18, 2);
                GLCD.print(Thresholdmax);
                GLCD.print(" °C");
                lastThresholdmax = Thresholdmax;
              }
            }

            // chế độ điều chỉnh Min
            if (mode == 1)
            {
              GLCD.CursorTo(0, 4);
              GLCD.print("<>");
              GLCD.CursorTo(0, 2);
              GLCD.print("  ");

              if (len == LOW)
              {
                Thresholdmin--;
                if (Thresholdmin <= 0)
                {
                  Thresholdmin = 100;
                }
              }
              if (xuong == LOW)
              {
                Thresholdmin++;
                if (Thresholdmin > 100)
                {
                  Thresholdmin = 0;
                }
              }
              if (Thresholdmin != lastThresholmin)
              {
                EEPROM.write(3, Thresholdmin);
                EEPROM.commit();
                GLCD.CursorTo(18, 4);
                GLCD.print("         "); // Xóa giá trị cũ
                GLCD.CursorTo(18, 4);
                GLCD.print(Thresholdmin);
                GLCD.print(" °C");
                lastThresholmin = Thresholdmin;
              }
            }
          }
          delay(100); // Tránh việc xử lý quá nhanh gây ra hiện tượng nhấp nháy
          if (digitalRead(13) == 0)
          {
            break; // Thoát khỏi vòng lặp khi nhấn nút thoát
          }
        }
        break;
      case 3:
        hienthi3();
        delay(500);
        GLCD.ClearScreen();
        GLCD.SetFontColor(255);
        GLCD.FillRect(0, 0, 192, 64, 0);
        Thresholdmax = EEPROM.read(2);
        GLCD.CursorTo(0, 0);
        GLCD.print("Temperature");
        GLCD.CursorTo(0, 2);
        GLCD.print("LIMIT MAX TEMP: ");
        GLCD.print(Thresholdmax);
        GLCD.print(" °C");
        GLCD.CursorTo(0, 4);
        GLCD.print("LIMIT MIN TEMP: ");
        GLCD.print(Thresholdmin);
        GLCD.print(" °C");
        GLCD.CursorTo(0, 6);
        GLCD.print("Status: OFF  ");

        while (vitri == 3)
        {
          float tongNhietdo = 0;
          for (i = 0; i < 1000; i++)
          {
            xulycambien();
            tongNhietdo += nhietdo;
          }
          delay(500);
          nhietdo = tongNhietdo / 1000.0;
          // Chỉ cập nhật GLCD nếu nhiệt độ thay đổi
          if (lastnhietdo != nhietdo)
          {
            GLCD.CursorTo(13, 0);
            GLCD.print("           ");
            GLCD.CursorTo(13, 0);
            GLCD.print(nhietdo);
            GLCD.print(" °C");
            lastnhietdo = nhietdo;
          }
          if ((nhietdo < Thresholdmax) && (nhietdo > Thresholdmin))
          {

            digitalWrite(14, HIGH);
            GLCD.CursorTo(0, 6);
            GLCD.print("Status: ON  ");
          }
          else
          {
            digitalWrite(14, LOW);
            GLCD.CursorTo(0, 6);
            GLCD.print("Status: OFF  ");
          }
          delay(100);
          if (digitalRead(13) == 0)
          {
            break;
          }
        }
        break;
        ///////////////////////////////////////////////////////////////////////////////////////////
      }
      // Xử lý back--------------------------------------------------------------
      while (vitri == 1)
      {
        if (digitalRead(13) == 0)
        {
          break;
          GLCD.ClearScreen();
          GLCD.SetFontColor(255);
          digitalWrite(14, LOW);
          vitri = lastvitri; // Quay lại vị trí trước đó
        }
      }
      while (vitri == 2)
      {
        if (digitalRead(13) == 0)
        {
          break;
          GLCD.ClearScreen();
          GLCD.SetFontColor(255);
          digitalWrite(14, LOW);
          vitri = lastvitri; // Quay lại vị trí trước đó
        }
      }
      while (vitri == 3)
      {
        if (digitalRead(13) == 0)
        {
          break;
          GLCD.ClearScreen();
          GLCD.SetFontColor(255);
          digitalWrite(14, LOW);
          vitri = lastvitri; // Quay lại vị trí trước đó
        }
      }
    }
  }
  delay(10);         // Tạm dừng sau khi cập nhật màn hình
  lastchedo = chedo; // Cập nhật giá trị lastchedo để tránh lặp lại việc in ra
}
// Set up VDK và GLCD--------------------------------------------------------------------------------
void setup()
{
  Serial.begin(9600);
  EEPROM.begin(250);
  Thresholdmax = EEPROM.read(2);
  Thresholdmin = EEPROM.read(3);
  pinMode(34, INPUT);
  pinMode(35, INPUT);
  // pinMode(36, INPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);
  pinMode(39, INPUT); // cảm biến

  pinMode(14, OUTPUT);
  digitalWrite(14, LOW);

  GLCD.Init();
  GLCD.SelectFont(System5x7);
  // GLCD.DrawBitmap(openGLCDh128x64, 64, 0, 255);
  GLCD.CursorTo(0, 0);
  GLCD.print("Practical");
  GLCD.CursorTo(0, 1);
  GLCD.print("Control");
  GLCD.CursorTo(0, 2);
  GLCD.print("Club");
  GLCD.DrawBitmap(CKCPIXEL, 128, 0, 255);

  delay(2000);
  GLCD.ClearScreen();
  vitri = 1;
  lastvitri = 1;
  chedo = 2;
  MODE1();
}
// Hàm chính------------------------------------------------------------------------------------------
void loop()
{
  unsigned long thoigiandongbo = millis();
  if (thoigiandongbo - thoigiantruockhidongbo >= 10)
  {
    thoigiantruockhidongbo = thoigiandongbo;
    xulytinhieunut();
    SelectMode();
    program();
  }
}