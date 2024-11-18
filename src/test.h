#include <openGLCD.h>
#include <EEPROM.h>

int vitri = 1;
int p_vitri = 1;
float nhietdo = 0;
float p_nhietdo = 0;
float volt = 0;
int digit = 0;
int dem = 0;

int Threshold; // nguong
// chi vao chuong trinh dieu khien tu dong
void nd1()
{
  GLCD.ClearScreen(); // xoa het man hinh
  GLCD.CursorTo(0, 0);
  GLCD.print("-> ON/OFF algorithm");
  GLCD.CursorTo(0, 1);
  GLCD.print("   Threshold");
  GLCD.CursorTo(0, 2);
  GLCD.print("   Temperature");
}
// chi vao chinh nguong dieu khien
void nd2()
{
  GLCD.ClearScreen(); // xoa het man hinh
  GLCD.CursorTo(0, 0);
  GLCD.print("   ON/OFF algorithm");
  GLCD.CursorTo(0, 1);
  GLCD.print("-> Threshold");
  GLCD.CursorTo(0, 2);
  GLCD.print("   Temperature");
}
// chi vao xem nhiet do hien tai
void nd3()
{
  GLCD.ClearScreen(); // xoa het man hinh
  GLCD.CursorTo(0, 0);
  GLCD.print("   ON/OFF algorithm");
  GLCD.CursorTo(0, 1);
  GLCD.print("   Threshold");
  GLCD.CursorTo(0, 2);
  GLCD.print("-> Temperature");
}
void Wellcome_nd1() // chay chuong trinh dieu khien tu dong
{
  GLCD.ClearScreen(); // xoa het man hinh
  GLCD.CursorTo(0, 0);
  GLCD.print("->  Controling ON/OFF algorithm");
}
void Wellcome_nd2() // chinh thong so nguong
{
  GLCD.ClearScreen(); // xoa het man hinh
  GLCD.CursorTo(0, 0);
  GLCD.print("->  Threshold...");
}
void Wellcome_nd3() // xem nhiet do hien tai
{
  GLCD.ClearScreen(); // xoa het man hinh
  GLCD.CursorTo(0, 0);
  GLCD.print("->  Temperature...");
}
void setup()
{
  // put your setup code here, to run once:
  // initialize EEPROM with predefined size
  EEPROM.begin(250);
  // quy dinh dia chi luu nguong la : 1
  // doc gia tri da luu
  Threshold = EEPROM.read(1);

  // Initialize the GLCD
  GLCD.Init();
  // Select the font for the default text area
  GLCD.SelectFont(System5x7);

  pinMode(34, INPUT); // cai 34 input UP
  pinMode(35, INPUT); // cai 35 input DOWN
  pinMode(39, INPUT); // cai 39 input BACK
  pinMode(13, INPUT); // cai 36 input ENTER

  /// pinMode(36,INPUT);  // cai 36 input doc cam bien
  pinMode(14, OUTPUT); // role kich quat

  digitalWrite(14, LOW);

  vitri = 1;
  p_vitri = 1;
  nd1();
}

void loop()
{
  // put your main code here, to run repeatedly:
  if (digitalRead(34) == 0) // kiem tra nhan nut
  {
    vitri--;
    if (vitri <= 0)
    {
      vitri = 3;
    }
    while (digitalRead(34) == 0) // thay bang delay(200)
    {
    }
  }
  if (digitalRead(35) == 0) // kiem tra nhan nut
  {
    vitri++;
    if (vitri > 3)
    {
      vitri = 1;
    }
    while (digitalRead(35) == 0)
    {
    }
  }
  if (p_vitri != vitri)
  {
    if (vitri == 1)
    {
      nd1();
    }
    else if (vitri == 2)
    {
      nd2();
    }
    else if (vitri == 3)
    {
      nd3();
    }
    p_vitri = vitri;
  }
  //----------------------------------------------------//
  if (digitalRead(13) == 0) // neu nhan enter
  {
    if (vitri == 1)
    { // chay 1 lan wellcome
      Wellcome_nd1();
      while (vitri == 1) // chay chuong trinh 1 lien tục va lap lai
      {

        if (digitalRead(39) == 0)
          break;
      }
    }
    else if (vitri == 2)
    {
      // chay 1 lan wellcome
      Wellcome_nd2();
      Threshold = EEPROM.read(1);
      GLCD.CursorTo(0, 1);
      GLCD.print(Threshold);
      GLCD.print(" C");
      while (vitri == 2) // chay chuong trinh 1 lien tục va lap lai
      {
        if (digitalRead(34) == 0) // kiem tra nhan nut
        {
          Threshold--;
          if (Threshold <= 0)
          {
            Threshold = 100;
          }
          GLCD.CursorTo(0, 1);
          GLCD.print("                   ");
          GLCD.CursorTo(0, 1);
          GLCD.print(Threshold);
          GLCD.print(" C");
          EEPROM.write(1, Threshold); // luu vao eeprom
          EEPROM.commit();
          while (digitalRead(34) == 0) // thay bang delay(200)
          {
          }
        }
        if (digitalRead(35) == 0) // kiem tra nhan nut
        {
          Threshold++;
          if (Threshold > 100)
          {
            Threshold = 0;
          }
          GLCD.CursorTo(0, 1);
          GLCD.print("                   ");
          GLCD.CursorTo(0, 1);
          GLCD.print(Threshold);
          GLCD.print(" C");
          EEPROM.write(1, Threshold); // luu vao eeprom
          EEPROM.commit();
          while (digitalRead(35) == 0) // thay bang delay(200)
          {
          }
        }

        if (digitalRead(39) == 0)
          break;
      }
    }
    else if (vitri == 3) // doc nhiet do hien tai
    {
      // chay 1 lan wellcome
      Wellcome_nd3();
      digit = analogRead(36);
      volt = ((float)(digit) * 3.30) / 4095.0; //(V)
      nhietdo = (volt * 1000.0) / 10.0;

      GLCD.CursorTo(0, 1);
      GLCD.print(nhietdo);
      GLCD.print(" C");
      while (vitri == 3) // chay chuong trinh 1 lien tục va lap lai
      {
        for (dem = 0; dem < 20; dem++)
        {
          digit = analogRead(36);
          volt = ((float)(digit) * 3.30) / 4095.0; //(V)
          nhietdo += (volt * 1000.0) / 10.0;
          delay(10);
        }
        nhietdo = nhietdo / 20.0;

        if (p_nhietdo != nhietdo)
        {
          GLCD.CursorTo(0, 1);
          GLCD.print("                   ");
          GLCD.CursorTo(0, 1);
          GLCD.print(nhietdo);
          GLCD.print(" C");
          p_nhietdo = nhietdo;
        }
        delay(100);
        if (digitalRead(39) == 0)
          break;
      }
    }

    // backup lai giao dien chon chuong trinh
    if (vitri == 1)
    {
      nd1();
    }
    else if (vitri == 2)
    {
      nd2();
    }
    else if (vitri == 3)
    {
      nd3();
    }
    // xoa het tin hieu
    digitalWrite(14, LOW);
    while (digitalRead(39) == 0)
      ; // chong doi nut
  }
}