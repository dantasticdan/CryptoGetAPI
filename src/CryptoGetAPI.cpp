#include "CryptoGetAPI.h"

CryptoGetAPI::CryptoGetAPI(Client &client)	{
  this->client = &client;
}

String CryptoGetAPI::SendGetToAPI(String command, String host) {
  String body="";
  body.reserve(700);
  bool finishedHeaders = false;
  bool currentLineIsBlank = true;
	long now;
	bool avail;
	const char * APIHost = host.c_str();

	//if (client->connect(ARKMAIN_HOST, Port)) {
	if (client->connect(APIHost, Port)) {
		//Serial.println(".... connected to block cypher server " + host);  
		String a="";
		char c;
		int ch_count=0;
		client->println("GET " + command + " HTTP/1.1");
    client->println("Host: " + host);
		client->println(F("User-Agent: arduino/1.0.0"));
		client->println();
		now=millis();
		avail=false;
		while (millis()-now<1500) {
			while (client->available()) {
				char c = client->read();
				//Serial.write(c);		

        if(!finishedHeaders){
          if (currentLineIsBlank && c == '\n') {
            finishedHeaders = true;
          }
        } else {
          body=body+c;
          ch_count++;
        }

        if (c == '\n') {
          currentLineIsBlank = true;
        }else if (c != '\r') {
          currentLineIsBlank = false;
        }
				avail=true;
			}
			if (avail) {
				 //Serial.println("Body:");  
				 //Serial.println(body);		
				 //Serial.println("END");		
				break;
			}
		}
	}

  return body;
}

BCResponse CryptoGetAPI::GetBlockCypherInfo(String coinId, String address) {
  // https://api.blockcypher.com/v1/btc/main/addrs/1KZfLsoF6MMzeGCZKrgjohNW2gx2NJ7ixK/balance
    String command="/v1/" + coinId + "/main/addrs/" + address + "/balance";

  //Serial.println(command); 
  String response = SendGetToAPI(command, BLOCKCYPHER_HOST);
  BCResponse responseObject = BCResponse();
  DynamicJsonBuffer jsonBuffer;

   // Parse JSON object
  JsonObject& root = jsonBuffer.parseObject(response);
  if (!root.success()) {
    responseObject.error = "Failed to parse JSON";
	return responseObject;
  } 
  else {
	responseObject.address = root["address"].as<String>();
    responseObject.total_received = root["total_received"].as<unsigned long>();
	responseObject.total_sent = root["total_sent"].as<unsigned long>();
	responseObject.balance = root["balance"].as<unsigned long>();
	responseObject.unconfirmed_balance = root["unconfirmed_balance"].as<unsigned long>();
	responseObject.final_balance = root["final_balance"].as<unsigned long>();
	responseObject.n_tx = root["n_tx"].as<unsigned long>();
	responseObject.unconfirmed_n_tx = root["unconfirmed_n_tx"].as<unsigned long>();
	responseObject.final_n_tx = root["final_n_tx"].as<unsigned long>();
	return responseObject;
  }

}

ARKResponse CryptoGetAPI::GetARKInfo(String coinId, String address) {
  //https://api.arkcoin.net/api/accounts/getBalance?address=AG3iujyBLTYr4ohj7z1qvpAPRUeJD4wWuA
  //http://104.238.132.186:4100/api/accounts/getBalance?address=JSBCwrMocFtxwgC71gHwufZS4zZeX2naUt

  String command="/api/accounts/getBalance?address=" + address;
	
  Serial.println(command); 
  String response = SendGetToAPI(command, ARKMAIN_HOST);
  ARKResponse responseObject = ARKResponse();
  DynamicJsonBuffer jsonBuffer;

   // Parse JSON object
  JsonObject& root = jsonBuffer.parseObject(response);
  if (!root.success()) {
    responseObject.error = "Failed to parse JSON";
	return responseObject;
  } 
  else {
	responseObject.success = root["success"].as<bool>();
    responseObject.balance = root["balance"].as<unsigned long>();
	responseObject.unconfirmedBalance = root["unconfirmedBalance"].as<unsigned long>();

	return responseObject;
  }
  
}

CWResponse CryptoGetAPI::GetCryptoWatchInfo(String coinId, String exchange) {
  //https://api.cryptowat.ch/markets/gdax/btcusd/price

  String command="/markets/" + exchange + "/btcusd/price";
  //Serial.println(command); 
  String response = SendGetToAPI(command, CRYPTOWATCH_HOST);
  CWResponse responseObject = CWResponse();
  DynamicJsonBuffer jsonBuffer;

   // Parse JSON object
  JsonObject& root = jsonBuffer.parseObject(response);
  if (!root.success()) {
    responseObject.error = "Failed to parse JSON";
	return responseObject;
  } 
  else {
	//responseObject.result = root["result"].as<String>();
	responseObject.price = root["result"]["price"].as<float>();

	return responseObject;
  }
  
}


