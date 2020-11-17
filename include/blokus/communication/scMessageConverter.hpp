#pragma once

#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include "color.hpp"
#include "gameState.hpp"
#include "move.hpp"
#include "moveType.hpp"
#include "piece.hpp"
#include "pieceShape.hpp"
#include "pugixml.hpp"
#include "scMessage.hpp"
#include "vec2i.hpp"
#include "xmlStringWriter.hpp"
#include "logger.hpp"

namespace HokusBlokus::Blokus::Communication {
    /**
     * @brief This class works on and with messages from the SC-Server.
     *
     */
    class SC_MessageConverter {
    private:
        /**
         * @brief Removes all protocol messages from the message received from the SC-Server.
         *
         * @param inputStream The message received from the SC-Server.
         * @return A vector of SC_Messages that represent possible protocol messages.
         */
        std::vector<SC_Message> FilterProtocolMessages(std::string &inputStream);

    public:
        /**
         * @brief Constructs a new SC_MessageConverter.
         *
         */
        SC_MessageConverter();

        /**
         * @brief Splits the incoming messages into SC_Messages.
         *
         * @param inputStream The message received from the SC-Server.
         * @return A vector of SC_Messages.
         */
        std::vector<SC_Message> SplitInputMessagesIntoValidSC_Messages(std::string inputStream);

        /**
         * @brief Creates a protocol SC_Message.
         *
         * @return A protocol SC_Message.
         */
        SC_Message CreateProtocolMessage();

        /**
         * @brief Creates a protocol end SC_Message.
         *
         * @return A protocol end SC_Message.
         */
        SC_Message CreateProtocolEndMessage();

        /**
         * @brief Creates a join request SC_Message.
         *
         * @return A join request SC_Message.
         */
        SC_Message CreateJoinRequestMessage();

        /**
         * @brief Creates a join reserved SC_Message.
         *
         * @param reservationCode The reservation code.
         * @return A join reserved SC_Message.
         */
        SC_Message CreateJoinReservedRequestMessage(const std::string &reservationCode);

        /**
         * @brief Create a move SCMessage.
         *
         * @param move The move.
         * @param roomID The room ID.
         * @return A move SCMessage.
         */
        SC_Message CreateMoveMessage(const HokusBlokus::Blokus::Move &move, const std::string &roomID);

        /**
         * @brief Gets the Player ID from welcome SC_Messages.
         *
         * @param message The welcome SC_Message.
         * @return Player ID in the welcome SC_Message.
         */
        int GetPlayerIDFromWelcomeMessage(const SC_Message &message);

        /**
         * @brief Gets the room ID from joined SC_Messages.
         *
         * @param message The joined SC_Message.
         * @return The room ID.
         */
        std::string GetRoomIDFromJoinedMessage(const SC_Message &message);

        /**
         * @brief Gets the GameState from gameState SC_Messages.
         *
         * @param message The gameState SC_Message.
         * @return The GameState.
         */
        HokusBlokus::Blokus::GameState GetGameStateFromGameStateMessage(const SC_Message &message);

        /**
         * @brief Gets the ID of the Player that won the game from result SC_Messages.
         *
         * @param message The result SC_Message.
         * @return The ID of the Player that won the game.
         */
        int GetIDOfWinningPlayerFromResultMessage(const SC_Message &message);
    };
}  // namespace HokusBlokus::Blokus::Communication