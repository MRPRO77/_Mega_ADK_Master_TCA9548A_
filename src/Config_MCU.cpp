/************************************************************************************************************

                                      configurações Mega ADK
************************************************************************************************************/

                                   /* Arquivos de Bibliotecas */

 // ========================================================================================================
// --- Bibliotecas Auxiliares --- //

#include <Adafruit_GFX.h>
#include <Adafruit_BusIO_Register.h>
#include <TCA9548A.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_SSD1306.h>
#include <U8glib-HAL.h> 


/**********************************************************************************************************/
                                        /* Arquivos de inclusão */


#include "Config_mcu.h"




// ========================================================================================================
//                                   --- Definições e Objetos ---
 

#define ledpin_MEGA_ADK    13                  // numero do pino onde o LED Verde supervisionamento do funcionamento do codigo

#define slaveAdress     0x07                   // ESP32

#define i2clcd       0
#define i2cOled      1
#define i2cESP32     2


#define OLED_RESET   3

U8GLIB_ST7920_128X64_1X u8g( 6,  //E
                             5,  //R/W
                             4,  //RS
                             7); //RST


TCA9548A I2CMux;                                     // Address can be passed into the constructor
#define usalcd       I2CMux.openChannel(i2clcd)
#define usaOled     I2CMux.openChannel(i2cOled)
#define usaESP32   I2CMux.openChannel(i2cESP32)

LiquidCrystal_I2C lcd(0x27,20,4);                   // set the LCD address to 0x27 for a 16 chars and 2 line display
Adafruit_SSD1306 display(OLED_RESET);               // configura tela de Oled


 


void Config_mcu()
{
     
                                                    Wire.begin(); 
                                            Serial.begin(115200);
                                              I2CMux.begin(Wire);               // Wire instance is passed to the library

                       display.begin(SSD1306_SWITCHCAPVCC, 0x3C);               // initialize with the I2C addr 0x3C (for the 128x64)
                                                     delay(3000);
                                          display.clearDisplay();

                                                          usalcd;
                                                      lcd.init();
                                                     lcd.clear(); 
                                                 lcd.backlight();               
                                          I2CMux.closeChannel(0);

                                                          usalcd;
                                                     lcd.clear(); 
                                              lcd.setCursor(2,1);
                                   lcd.print("MRPRO TECNOLOGIA");
                                                      delay(200);
                                          I2CMux.closeChannel(0);   


                                                         usaOled;
                       display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
                                          display.clearDisplay();
                                          I2CMux.closeChannel(1);          
 
                                                         usaOled;
                                          display.clearDisplay(); 
                                     display.setTextColor(WHITE);
                                         display.setCursor(25,1);
                                display.println("Loja Saravati");
                                     display.setTextColor(WHITE);
                                        display.setCursor(25,15);
                                display.println("Mestre Felipe");
                                                     delay(2000);
                                               display.display();
                                          I2CMux.closeChannel(1);

                                               disp_graph_init();

 
                                                        usaESP32;
                                                      delay(100);
                                          I2CMux.closeChannel(2);                                               
                                               

                               pinMode (ledpin_MEGA_ADK, OUTPUT);                // configura o pino do LED 13 como saida
                               digitalWrite(ledpin_MEGA_ADK,LOW);  


                             

}

// ======================================================================================================
// --- Função para desenho de strings ---
void draw() 
{
  
  u8g.setFont(u8g_font_unifont);
 
  u8g.drawStr( 0, 25, "MRPRO TECNOLOGIA");
  
} //end draw


// ======================================================================================================
// --- Função de inicialização do Display ---
void disp_graph_init()
{
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     //branco
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         //máxima intensidade
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }

    u8g.firstPage();  
  do {
                        draw();
     } while( u8g.nextPage() );
  
                    delay(100);

} //end disp_graph_init

// ======================================================================================================
// --- Função de Supervisionamento do programa ---

void Supervisionamento()
{

  //Acende o LED durante 1 segundo
  digitalWrite(ledpin_MEGA_ADK, HIGH);
  delay(1000);

  //Apaga o LED durante 1 segundo
  digitalWrite(ledpin_MEGA_ADK, LOW);
  delay(1000);

    
}


  
  