#include <CryptoGetAPI.h>

/*******************************************************************
 *  An example of getting data info from various crypto APIs       *
 *                                                                 *
 *  Modified from coinmarketcap.api Written by Brian Lough                                         *
 *******************************************************************/

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

//------- Install From Library Manager -------
#include <ArduinoJson.h>


//------- Replace the following! ------
char ssid[] = "";       // your network SSID (name)
char password[] = "";  // your network key

WiFiClientSecure client;
CryptoGetAPI api(client);

unsigned long api_mtbs = 30000; //mean time between api requests
unsigned long api_due_time = 0;

void setup() {

  Serial.begin(115200);

  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);
}

void GetAddressData(String coinID, String address) {
  Serial.println("---------------------------------");
  //Serial.println("Getting ticker data for " + ticker);

  if (coinID == "ark") {
    ARKResponse response = api.GetARKInfo(coinID, address);
    if (response.error == "") {
      Serial.print("Success: ");
      Serial.println(response.success);
      Serial.print("Balance: ");
      Serial.println(response.balance);
      Serial.print("Unconfirmed Balance: ");
      Serial.println(response.unconfirmedBalance);
  
    } else {
      Serial.print("Error getting data: ");
      Serial.println(response.error);
    }
    Serial.println("---------------------------------");
    
  }
  else {
    BCResponse response = api.GetBlockCypherInfo(coinID, address);
    if (response.error == "") {
      Serial.print("Coin: ");
      Serial.println(coinID);
      Serial.print("Address: ");
      Serial.println(response.address);
      Serial.print("Total Received: ");
      Serial.println(response.total_received);
      Serial.print("Total Sent: ");
      Serial.println(response.total_sent);
      Serial.print("Balance: ");
      Serial.println(response.balance);
      Serial.print("Unconfirmed Balance: ");
      Serial.println(response.unconfirmed_balance);
      Serial.print("Final Balance: ");
      Serial.println(response.final_balance);
      Serial.print("Num Tx: ");
      Serial.println(response.n_tx);
      Serial.print("Unconfirmed Tx: ");
      Serial.println(response.unconfirmed_n_tx);
      Serial.print("Final Num Tx: ");
      Serial.println(response.final_n_tx);
  
    } else {
      Serial.print("Error getting data: ");
      Serial.println(response.error);
    }
    Serial.println("---------------------------------");
  }
}

void GetCryptowatchData(String coinID, String exchange) {
  Serial.println("---------------------------------");
 
   CWResponse response = api.GetCryptoWatchInfo(coinID, exchange);
    if (response.error == "") {
      Serial.print("Trading Pair: ");
      Serial.println(coinID);
      Serial.print("Exchange: ");
      Serial.println(exchange);
      Serial.print("Result: ");
      Serial.println(response.price);
     } else {
      Serial.print("Error getting data: ");
      Serial.println(response.error);
    }
    Serial.println("---------------------------------");
}
  

void loop() {
  unsigned long timeNow = millis();
  if ((timeNow > api_due_time))  {
    //GetAddressData("btc","1KZfLsoF6MMzeGCZKrgjohNW2gx2NJ7ixK");
    GetAddressData("eth","0x07e8c5dc3749ec300b73a460147f366476a2a319");
    //GetAddressData("ark","AG3iujyBLTYr4ohj7z1qvpAPRUeJD4wWuA");
    //GetAddressData("doge","DBkjjjmMRQkyZ4hxRonnmqNssGxWwf7byn");
    //GetAddressData("dash","");
    //GetAddressData("ltc","");
    //GetCryptowatchData("btcusd","gdax");
    
    api_due_time = timeNow + api_mtbs;
  }
}
