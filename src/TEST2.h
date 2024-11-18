#include <khaibao.h>
#include <WiFi.h>
// Cảm biến nhiệt độ
void xulycambien()
{
  analogReadResolution(12);
  int giatrinhietdo = analogRead(sensorpin);
  float analogReadMax = 4096.0;
  float mV = (giatrinhietdo / analogReadMax) * 5000.0;
  float nhietdo = mV / 10.0;
  Serial.println(nhietdo);
}
// Hiển thị màn hình làm việc của chế độ
void hienthi1()
{
  GLCD.ClearScreen();
  GLCD.SetFontColor(255);
  GLCD.CursorTo(0, 0);
  GLCD.print("Blinking");
}
void hienthi2()
{
  GLCD.ClearScreen();
  GLCD.SetFontColor(255);
  GLCD.CursorTo(0, 0);
  GLCD.print("Chasing");
}
void hienthi3()
{
  // GLCD.ClearScreen();
  // GLCD.SetFontColor(255);
  // GLCD.CursorTo(0, 0);
  // GLCD.print("Bouncing");
}
// Chế độ làm việc-----------------------------------------------------------------------------------
void MODE_1()
{
  digitalWrite(14, HIGH);
}
void MODE_2()
{
  digitalWrite(14, HIGH);
  delay(100);
  digitalWrite(14, LOW);
  delay(100);
}
void MODE_3()
{
  analogReadResolution(12);
  int giatrinhietdo = analogRead(sensorpin);
  float analogReadMax = 4096.0;
  float mV = (giatrinhietdo / analogReadMax) * 5000.0;
  float nhietdo = mV / 10.0;
  Serial.println(nhietdo);
  GLCD.SetFontColor(255);
  GLCD.FillRect(0, 0, 192, 64, 0);
  GLCD.CursorTo(0, 0);
  GLCD.print("Nhiet do la: ");
  GLCD.print(nhietdo);
}
// Hiển thị bản chế độ-------------------------------------------------------------------------------
void MODE1()
{
  // GLCD.ClearScreen();
  // GLCD.DrawBitmap(CKCPIXEL, 128, 0, 255);
  GLCD.SetFontColor(0);
  GLCD.CursorTo(0, 1);
  GLCD.print("-> Blink");
  GLCD.SetFontColor(255);
  GLCD.CursorTo(0, 3);
  GLCD.print("   Chase");
  GLCD.CursorTo(0, 5);
  GLCD.print("   Hien thi nhiet do");
}
void MODE2()
{
  // GLCD.ClearScreen();
  // GLCD.DrawBitmap(CKCPIXEL, 128, 0, 255);
  GLCD.SetFontColor(255);
  GLCD.CursorTo(0, 1);
  GLCD.print("   Blink");
  GLCD.SetFontColor(0);
  GLCD.CursorTo(0, 3);
  GLCD.print("-> Chase");
  GLCD.SetFontColor(255);
  GLCD.CursorTo(0, 5);
  GLCD.print("   Hien thi nhiet do");
}
void MODE3()
{
  // GLCD.ClearScreen();
  // GLCD.DrawBitmap(CKCPIXEL, 128, 0, 255);
  GLCD.CursorTo(0, 1);
  GLCD.print("   Blink");
  GLCD.CursorTo(0, 3);
  GLCD.print("   Chase");
  GLCD.SetFontColor(0);
  GLCD.CursorTo(0, 5);
  GLCD.print("-> Hien thi nhiet do");
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
void TEST()
{
  if (chedo != lastchedo) // Khi chế độ thay đổi
  {
    GLCD.ClearScreen();
    digitalWrite(14, LOW);
    if (chedo == 1)
    {
      switch (vitri)
      {
      case 1:
        GLCD.SetFontColor(255);
        MODE_1();
        break;

      case 2:
        GLCD.SetFontColor(255);
        MODE_2();
        break;

      case 3:
        GLCD.SetFontColor(255);
        MODE_3();
        break;
      }
    }
    if (chedo == 2)
    {
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
    delay(100);        // Tạm dừng sau khi cập nhật màn hình
    lastchedo = chedo; // Cập nhật giá trị lastchedo để tránh lặp lại việc in ra
  }
}
void TESTCODE()
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
    if (chedo == 1)
    {
      switch (vitri)
      {
      case 1:
        hienthi1();
        break;

      case 2:
        hienthi2();
        break;

      case 3:
        hienthi3();
        break;
      }
      while (vitri == 1)
      {
        MODE_1();
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
        MODE_2();
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
        MODE_3();
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
  if (thoigiandongbo - thoigiantruockhidongbo >= 100)
  {
    thoigiantruockhidongbo = thoigiandongbo;
    xulytinhieunut();
    SelectMode();
    TESTCODE();
    // xulycambien();
  }
}