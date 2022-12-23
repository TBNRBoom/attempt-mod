#include <iostream>
#include <string>
#include <curl/curl.h> // Include the cURL library
#include "minecraft/commands/command.h" // Include the Minecraft Command header file
#include "minecraft/commands/command_origin.h" // Include the Minecraft CommandOrigin header file
#include "minecraft/commands/command_output.h" // Include the Minecraft CommandOutput header file
#include "minecraft/player/player.h" // Include the Minecraft Player header file

using namespace std;

// Define the command callback function
void statsCommand(CommandOrigin const& origin, CommandOutput& output, std::vector<std::string> const& args) {
  // Get the player who issued the command
  Player* player = origin.getEntity();

  // Get the player's API key
  string apiKey = player->getAPIKey();

  // Get the target player's name and gamemode from the command arguments
  string targetPlayerName = args[0];
  string gamemode = args[1];

  // Set up the cURL request to retrieve the target player's stats from the Plancke.io API
  CURL* curl = curl_easy_init();
  curl_easy_setopt(curl, CURLOPT_URL, "https://api.plancke.io/hypixel/player?key=" + apiKey + "&name=" + targetPlayerName);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, nullptr);

  // Send the request and store the response
  string response;
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
  curl_easy_perform(curl);
  curl_easy_cleanup(curl);

  // Parse the response to extract the target player's stats for the specified gamemode
  // TODO: Parse the response and extract the target player's stats for the specified gamemode

  // Send the target player's stats for the specified gamemode to the player in chat
  // TODO: Send the target player's stats for the specified gamemode to the player in chat
}