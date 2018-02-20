/*
/*********************************************************
Get Cryoto currency data info from various crypto APIs:       
BlockCypher,CryptoWatch, Arkcoin                                                           

Modified from coinmarketcap.api written by Brian Lough                                       

 
This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/


#ifndef CryptoGetAPI_h
#define CryptoGetAPI_h

#include <Arduino.h>
#include <ArduinoJson.h>
#include <Client.h>

#define BLOCKCYPHER_HOST "api.blockcypher.com"
#define COINMARKETCAP_HOST "api.coinmarketcap.com"
#define CRYPTOWATCH_HOST "api.cryptowat.ch"
#define ARKMAIN_HOST "api.arkcoin.net"
#define ARKJAKE_HOST "104.238.132.186:4100"



struct BCResponse{
  String address;
  unsigned long total_received;
  unsigned long total_sent;
  unsigned long balance;
  unsigned long unconfirmed_balance;
  unsigned long final_balance;
  unsigned long n_tx;
  unsigned long unconfirmed_n_tx;
  unsigned long final_n_tx;

  String error;
};

struct CWResponse{
  //String result;
  float price;

  String error;
};

struct ARKResponse{
  bool success;
  unsigned long balance;
  unsigned long unconfirmedBalance;

  String error;
};


class CryptoGetAPI
{
  public:
    CryptoGetAPI (Client &client);
    String SendGetToAPI(String command, String host);
    BCResponse GetBlockCypherInfo(String coinID, String address);
	ARKResponse GetARKInfo(String coinID, String address);
	CWResponse GetCryptoWatchInfo(String coinID, String exchange);
    int Port = 443;

  private:
    Client *client;
};

#endif
