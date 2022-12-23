#include <iostream>
#include <string>
#include <nlohmann/json.hpp> // Include the nlohmann/json header file
#include "minecraft/commands/command.h" // Include the Minecraft Command header file
#include "minecraft/commands/command_origin.h" // Include the Minecraft CommandOrigin header file
#include "minecraft/commands/command_output.h" // Include the Minecraft CommandOutput header file
#include "minecraft/player/player.h" // Include the Minecraft Player header file

using namespace std;
using json = nlohmann::json; // Use the namespace alias

// Define the command callback function
void statsCommand(CommandOrigin const& origin, CommandOutput& output, std::vectorstd::string const& args) {
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
json responseJson = json::parse(response);
json stats = responseJson["player"]["stats"][gamemode];
int coins = stats["coins"];
int kills = stats["kills"];

// Create a message string containing the target player's stats for the specified gamemode
string message = "Coins: " + to_string(coins) + "\nKills: " + to_string(kills);

// Send the message to the player in chat
output.sendMessage(message);
}

int main() {
// Register the command and specify the callback function to be called when the command is issued
CommandRegistry::addCommand("stats", "Displays the stats of a player for a specific gamemode", 2, 2, (CommandPermissionLevel)4, (CommandFlag)4, (CommandFlag)4, statsCommand);

// TODO: Call the statsCommand function when the command is issued
}
