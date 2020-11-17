#pragma once

#include <boost/asio.hpp>
#include <boost/program_options.hpp>
#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "color.hpp"
#include "gameState.hpp"
#include "logger.hpp"
#include "logic.hpp"
#include "move.hpp"
#include "scMessage.hpp"
#include "scMessageConverter.hpp"
#include "scMessageType.hpp"
#include "tcpClient.hpp"

namespace HokusBlokus::Blokus::Client {
	/**
     * @brief This client class manages everything basically. It connects to the SC-Server, receives and sends messages, etc.
     * 
     */
	class BlokusClient {
		/**
         * @brief The TCP_CLient of the Client.
         * 
         */
		Client::TCP_Client tcpClient;

		/**
         * @brief The MessageConverter of the Client.
         * 
         */
		HokusBlokus::Blokus::Communication::SC_MessageConverter scMessageConverter;

		/**
         * @brief The room ID of the Game the Client is in.
         * 
         */
		std::string roomID;

		/**
         * @brief The ID of the Player played by the Client.
         * 
         */
		int ownPlayerID;

		/**
         * @brief The last GameState received by the Client.
         * 
         */
		HokusBlokus::Blokus::GameState currentGameState;

		/**
         * @brief Is true if the game of Blokus is over, else it is false.
         * 
         */
		bool gameOver = false;

		/**
         * @brief A pointer to the Logic that implements behaviour of the AI.
         * 
         */
		HokusBlokus::Blokus::AI::Logic *logic;

		/**
         * @brief A simple options. If it is set to true, the Client will print alle messages it receives and sens to standard out.
         * 
         */
		bool verboseOutputEnabled = false;

	public:
		/**
         * @brief Constructs a new BlokusClient with a Logic.
         * 
         * @param logic The Logic that implements behaviour of the AI.
         */
		BlokusClient(HokusBlokus::Blokus::AI::Logic *logic);

		/**
         * @brief Starts the Client.
         * 
         * @param argc Number of console arguments.
         * @param argv Array of console Arguments.
         */
		void Start(int argc, char *argv[]);

	private:
		/**
         * @brief Generates Messages according to the Messages received. This method also call the GetNextMove() method of the Logic.
         * 
         * @param incomingMessages The messages send from the SC-Server.
         * @return A vector of Messages the Client wants to send to the SC-Server.
         */
		std::vector<HokusBlokus::Blokus::Communication::SC_Message> HandleIncomingMessagesAndGenerateRespones(const std::vector<HokusBlokus::Blokus::Communication::SC_Message> &incomingMessages);

		/**
         * @brief The ClientLoop is a loop that runs until the game of Blokus is over. In the loop things like messaging is handled.
         * 
         */
		void ClientLoop();

		/**
         * @brief Disconnects the Client from the SC-Server.
         * 
         */
		void Shutdown();

		/**
         * @brief Gets the next Move the Client should send to the SC_Server. This method calls GetNextMove() of the Logic.
         * 
         * @param currentGameState The current GameState to get the next Move for.
         * @param ownPlayerID The ID of the Player played by the Client.
         * @return The Move that should be send to the SC-Server.
         */
		HokusBlokus::Blokus::Move GetNextMove(HokusBlokus::Blokus::GameState currentGameState, int ownPlayerID);

		/**
         * @brief Starts a connection with the SC-Server.
         * 
         * @param address The address of the SC-Server.
         * @param port The port of the SC-Server.
         */
		void StartConnection(const std::string &address, const unsigned short &port);

		/**
         * @brief Starts a reserved connection with the SC-Server.
         * 
         * @param hostanme The address of the SC-Server.
         * @param port The port of the SC-Server.
         * @param reservationCode The reservation code.
         */
		void StartReservedConnection(const std::string &hostanme, const unsigned short &port, const std::string &reservationCode);
	};
}  // namespace HokusBlokus::Blokus::Client