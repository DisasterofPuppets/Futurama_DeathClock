#include "bot_credentials.h"
#include <memory_constraints.h>
#include <twitch_irc_api.h> //this library needs the ArduinoWebsockets library to work, so be sure to add it. https://github.com/Links2004/arduinoWebSockets
#include <ESP8266WiFi.h>
#include <Servo.h>

// Based off https://github.com/noycebru/twitch-websockets-for-channel-point-robots

Servo myservo;
int sPin = 12; //Pin 6 on the ESP


//Twitch Api Instance
TwitchWebsocketIRC twitch_api;


const char* ssid = WIFI_SSID; //Enter SSID
const char* password = WIFI_PASS; //Enter Password


void setup() {

  myservo.attach(sPin, 600, 2300);
  myservo.write(180);


  Serial.begin(115200);
  // Connect to wifi
  WiFi.begin(ssid, password);

  // Check if connected to wifi
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("No WIFI");
    delay(2000);
  }

  Serial.println("Connected to Wifi.");
  delay(3000);


  //Connect to twitch via websockets
  twitch_api.connect_to_twitch_websocket();

  //Register generic callbacks
  twitch_api.onPrivMsg(onPrivMsgCallback);



  //Helper Functions
  /*
    A sub plan is returned on subs, resub, gift, etc. You can use the helper function to convert int value to string.
  */
  printf("%s\n", twitch_api.sub_type_to_string(0));
  printf("%s\n", twitch_api.sub_type_to_string(1000));
  printf("%s\n", twitch_api.sub_type_to_string(2000));
  printf("%s\n", twitch_api.sub_type_to_string(3000));
  /*
    Emotes are returned when people say them in chat or in messages when donating. You can use the function to get the image url of the icon.
    Sizes: IMG_SMALL, IMG_MEDIUM, IMG_LARGE
  */
  printf("Emote Image URL: %s\n", twitch_api.get_emote_image_url(301448586, TwitchWebsocketIRC::Emote_Image_Size::IMG_MEDIUM));
}

void loop()
{



  if (twitch_api.available())
  {
    twitch_api.poll();
  }



  ////////NEED TO PUT IN DELAY SO IT CAN'T BE TRIGGERED WHILE IN LOOP AGAIN

}

/* Generic Callback Functions */

void onPrivMsgCallback(PrivMsg data) {
  printf("\n---------------------------------------------------\n");
  int count = 0;
  printf("\n=PRIVMSG=\n");
  printf("\nBadges Info\n");
  

if (strstr(data.message, " is about to reveal their future") != NULL && (strcmp(data.display_name, "DrPuppetMaster") == 0)) {

    char scenepls[30] = {"/w drpuppetmaster !deathshow"};
    twitch_api.send_chat_message(scenepls);

    printf("Death Clock Triggered");

    delay(1000);//for sound
    myservo.write(0);
    delay(400);
    myservo.write(180);

  }
  
  while (data.badge_info[count].name != NULL) {
    printf("\t-Badge Name: %s Version: %i\n", data.badge_info[count].name, data.badge_info[count].version);
    count += 1;
  }
  count = 0;
  printf("\nBadges\n");
  while (data.badges[count].name != NULL) {
    printf("\t-Badge Name: %s Version: %i\n", data.badges[count].name, data.badges[count].version);
    count += 1;
  }
  count = 0;
  printf("\nEmote Chat Set\n");
  while (data.emotes[count].start_index_location != 0 && data.emotes[count].end_index_location != 0) {
    printf("\t-Emote Id: %i\n", data.emotes[count].emote.emote_id);
    printf("\t-Emote First Index: %i\n", data.emotes[count].start_index_location);
    printf("\t-Emote Second Index: %i\n", data.emotes[count].end_index_location);
    count += 1;
  }
  printf("Bits: %i\nColor: %s\nDisplay Name: %s\nId: %s\nMessage: %s\nMod: %i\nRoom Id: %i\nTmi Sent Ts: %s\nUser Id: %i\nChannel Name: %s\n",
         data.bits, data.color, data.display_name, data.id, data.message, data.mod, data.room_id, data.tmi_sent_ts, data.user_id, data.channel_name);
  printf("\n---------------------------------------------------\n");
}

 
 
