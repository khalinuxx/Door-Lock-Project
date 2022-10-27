#include <Keypad.h>
#include <LiquidCrystal.h>

#define dooropen 10
#define doorclose 9


#define Password_Lenght 7 //taille du mot de passe + 1 

#define rs A0
#define en A1
#define d4 A2
#define d5 A3
#define d6 A4
#define d7 A5
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


char Data[Password_Lenght];
char Master[Password_Lenght] = "123456"; //variable t7ot fyh  password
byte data_count = 0, master_count = 0;
bool Pass_is_good;
char customKey; // variable t7ot fyh chnoww ktebt f clavier

const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
bool door = true; 

byte rowPins[ROWS] = {2,3,4,5}; //connect ll les ligne mta3 clavier
byte colPins[COLS] = {6,7,8}; //connect ll les colonnes mta3 clavier

Keypad customKeypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS); //inisialisation ll classe ta3 clavier

void setup()
{

  pinMode(dooropen,OUTPUT);
  pinMode(doorclose,OUTPUT);
 
    
   lcd.begin(16, 2);
   lcd.setCursor(1,0);
   lcd.print(" Welcome ING1 ");
  
  delay(500);
  
   lcd.setCursor(0,1);
   lcd.print(" Arduino Door");
 
  
    delay(500);
      digitalWrite(doorclose,HIGH);
      digitalWrite(dooropen,LOW);
      lcd.clear();
  

}

void loop()
{
  if (door == 0)
  {
    digitalWrite(doorclose,LOW);
      digitalWrite(dooropen,HIGH);
    customKey = customKeypad.getKey();

    if (customKey == '#') // si vous cliker # la port va fermé

    {
      lcd.clear();
      lcd.print(" Door is close");
       digitalWrite(doorclose,HIGH);
      digitalWrite(dooropen,LOW);
      delay(1500);
      door = 1;
     
    }
  }

  else Open();
  
}

//fonction hedhy ma3mpila bech tfassa5 m variable data l'mot de passe ba3d me tektebha 
void clearData()
{
  while (data_count != 0)
  { 
    Data[data_count--] = 0; 
  }
  return;
}





void Open()
{
      //lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" Enter Password");
  
  customKey = customKeypad.getKey();
  if (customKey!= NO_KEY) // condition bech t'verify si famma click 3le clavier ou nn
  {
    Data[data_count] = customKey; // enregirement du mot de passe dans le variable data
     // move cursor to show each new char
    lcd.setCursor(data_count, 1);
    lcd.print("*"); // chaque click 3le lclavier bch todhher * f afficheur
   
    data_count++; // incrementation ll variable data bch y9ayyed chiffre jdyd
  }

  if (data_count == Password_Lenght - 1) // ken wsol taille mta3 l'mot de passe ly tekteb 9ad taille ta3 mot de passe ta3 l'port yabda yaaml f verification te3o
  {
    if (!strcmp(Data, Master)) // ken mot de passe s7y7 beb bch yet7all w yetkteb port ouvert
    {
     
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("  Door is Open");
      door = 0;
      digitalWrite(doorclose,LOW);
      digitalWrite(dooropen,HIGH);
    }
    else  // ken mot de passe s7y7 beb bch yet7all w yetkteb port ouvert
    {
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("  Wrong Password");
      digitalWrite(doorclose,HIGH);
      digitalWrite(dooropen,LOW);
      delay(1000);
      door = 1;
      lcd.clear();
      
    }
    clearData();
  }
}
