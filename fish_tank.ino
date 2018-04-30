#include <Bridge.h>
#include <Temboo.h>
#include "TembooAccount.h" 
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


const String CLIENT_ID = "288996482834-5r0dg46brof0i6rnnvho1381i5ofu6kj.apps.googleusercontent.com";
const String CLIENT_SECRET = "gXaP6AQ809azXjouyzWUYyH8";
const String REFRESH_TOKEN = "1/CR2yWVg1746UNCwLCAOUC2tBSaqZrKb5nC-1LSeRD7g";
const String SPREADSHEET_ID = "1MNrCrgZkke4hXsGkWn9MmOmN3OhaDVqvEW_kVSkLCt4";
const unsigned long RUN_INTERVAL_MILLIS = 60000; // how often to run the Choreo (in milliseconds)
unsigned long lastRun = (unsigned long)-60000;


void setup() {
  lcd.begin(16, 2);
  lcd.print("Initializing the");
  lcd.setCursor(0,1);
  lcd.print("bridge...");
  Bridge.begin();
  lcd.clear();
  lcd.print("Done");

 
}

void loop()
{
  temperatureSensor();
}

void temperatureSensor(){
   int myvar = 123456;
  
  String now = "meh";
    TembooChoreo AppendValuesChoreo;  
    AppendValuesChoreo.begin();   
    AppendValuesChoreo.setAccountName(TEMBOO_ACCOUNT);
    AppendValuesChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    AppendValuesChoreo.setAppKey(TEMBOO_APP_KEY);   
    AppendValuesChoreo.setChoreo("/Library/Google/Sheets/AppendValues");   
    AppendValuesChoreo.addInput("ClientID", CLIENT_ID);
    AppendValuesChoreo.addInput("ClientSecret", CLIENT_SECRET);
    AppendValuesChoreo.addInput("RefreshToken", REFRESH_TOKEN);
    AppendValuesChoreo.addInput("SpreadsheetID", SPREADSHEET_ID);
    String rowData = "[[\"" + String("Meh") + "\"]]";
    AppendValuesChoreo.addInput("Values", rowData);
    unsigned int returnCode = AppendValuesChoreo.run();  
    if (returnCode == 0) {
      lcd.clear();
      lcd.print("Success!");
      lcd.setCursor(0,1);
      lcd.print("Appended " + rowData);
      lcd.print("");
    } else {
        while (AppendValuesChoreo.available()) {
        char c = AppendValuesChoreo.read();
        lcd.print(c);
      }
    }
    AppendValuesChoreo.close();
  }




