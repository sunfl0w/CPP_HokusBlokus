#include "blokusClient.hpp"
#include "scMessageType.hpp"

using namespace boost::program_options;

namespace HokusBlokus::Blokus::Client {
    BlokusClient::BlokusClient(AI::Logic *logic) {
        this->logic = logic;
    }

    void BlokusClient::Start(int argc, char *argv[]) {
        std::cout << "Parsing arguments.\n";

        options_description optionsDesribtion("C++ client");
        optionsDesribtion.add_options()("host,h", value<std::string>()->default_value("localhost"), "Host")("port,p", value<unsigned short>()->default_value(13050), "Port")("reservation,r", value<std::string>()->default_value(""), "ReservationCode")("verbose,v", "Verbosity");

        variables_map varibaleMap;
        store(command_line_parser(argc, argv).options(optionsDesribtion).run(), varibaleMap);

        std::string hostname = "localhost";
        unsigned short hostPort = 13050;
        std::string reservationCode;

        if (varibaleMap.count("host")) {
            hostname = varibaleMap["host"].as<std::string>();
        }
        if (varibaleMap.count("port")) {
            hostPort = varibaleMap["port"].as<unsigned short>();
        }
        if (varibaleMap.count("reservation")) {
            reservationCode = varibaleMap["reservation"].as<std::string>();
        }
        if (varibaleMap.count("verbose")) {
            verboseOutputEnabled = true;
        }

        std::cout << "Parsing complete. Arguments are:\n";
        std::cout << "HostName: " + hostname + "\n";
        std::cout << "HostPort: " + std::to_string(hostPort) + "\n";
        std::cout << "ReservationCode: " + reservationCode + "\n";

        if (reservationCode.size() == 0) {
            std::cout << "Starting a connection.\n";
            StartConnection("127.0.0.1", hostPort);
        } else {
            std::cout << "Starting a reserved connection.\n";
            StartReservedConnection(hostname, hostPort, reservationCode);
        }
    }

    void BlokusClient::ClientLoop() {
        while (!gameOver) {
            if (verboseOutputEnabled) {
                std::cout << "Listening.\n";
            }

            std::string inputStream = tcpClient.ReadMessage();

            std::vector<HokusBlokus::Blokus::Communication::SC_Message> messages = scMessageConverter.SplitInputMessagesIntoValidSC_Messages(inputStream);
            for (HokusBlokus::Blokus::Communication::SC_Message message : messages) {
                if (verboseOutputEnabled) {
                    std::cout << "RECV: " <<message.GetContent() + "\n";
                }
            }
            std::vector<HokusBlokus::Blokus::Communication::SC_Message> responses = HandleIncomingMessagesAndGenerateRespones(messages);
            for (HokusBlokus::Blokus::Communication::SC_Message response : responses) {
                if (verboseOutputEnabled) {
                    std::cout << "SEND: " << response.GetContent() + "\n";
                }
                tcpClient.SendMessage(response.GetContent());
            }
        }
    }

    void BlokusClient::Shutdown() {
        tcpClient.SendMessage(scMessageConverter.CreateProtocolEndMessage().GetContent());
    }

    std::vector<HokusBlokus::Blokus::Communication::SC_Message> BlokusClient::HandleIncomingMessagesAndGenerateRespones(const std::vector<HokusBlokus::Blokus::Communication::SC_Message> &incomingMessages) {
        std::vector<HokusBlokus::Blokus::Communication::SC_Message> responseMessages;
        for (HokusBlokus::Blokus::Communication::SC_Message message : incomingMessages) {
            if (message.GetMessageType() == HokusBlokus::Blokus::Communication::SC_MessageType::Joined) {
                std::string roomId = scMessageConverter.GetRoomIDFromJoinedMessage(message);
                roomID = roomId;
            } else if (message.GetMessageType() == HokusBlokus::Blokus::Communication::SC_MessageType::Welcome) {
                ownPlayerID = scMessageConverter.GetPlayerIDFromWelcomeMessage(message);
            } else if (message.GetMessageType() == HokusBlokus::Blokus::Communication::SC_MessageType::GameState) {
                currentGameState = scMessageConverter.GetGameStateFromGameStateMessage(message);
            } else if (message.GetMessageType() == HokusBlokus::Blokus::Communication::SC_MessageType::MoveRequest) {
                if (!gameOver) {
                    HokusBlokus::Blokus::Move nextMove = GetNextMove(currentGameState, ownPlayerID);
                    responseMessages.push_back(scMessageConverter.CreateMoveMessage(nextMove, roomID));   
                }
            } else if (message.GetMessageType() == HokusBlokus::Blokus::Communication::SC_MessageType::Left) {
                gameOver = true;
            } else if (message.GetMessageType() == HokusBlokus::Blokus::Communication::SC_MessageType::Result) {
                logic->OnGameEnd(scMessageConverter.GetIDOfWinningPlayerFromResultMessage(message));
                gameOver = true;
            } else if (message.GetMessageType() == HokusBlokus::Blokus::Communication::SC_MessageType::Error) {
                gameOver = true;
            } else if (message.GetMessageType() == HokusBlokus::Blokus::Communication::SC_MessageType::ProtocolEnd) {
                gameOver = true;
            } else if (message.GetMessageType() == HokusBlokus::Blokus::Communication::SC_MessageType::Undefined) {
                gameOver = true;
            }
        }
        return responseMessages;
    }

    HokusBlokus::Blokus::Move BlokusClient::GetNextMove(HokusBlokus::Blokus::GameState currentGameState, int ownPlayerID) {
        return logic->GetNextMove(currentGameState, ownPlayerColor);
    }

    void BlokusClient::StartConnection(const std::string &address, const unsigned short &port) {
        tcpClient.ConnectWithIP(address, port);
        tcpClient.SendMessage("<protocol>");
        tcpClient.SendMessage(scMessageConverter.CreateJoinRequestMessage().GetContent());
        ClientLoop();
        Shutdown();
        std::cout << "Disconnected. Bye.\n";
    }

    void BlokusClient::StartReservedConnection(const std::string &hostname, const unsigned short &port, const std::string &reservationCode) {
        if (hostname == "localhost") {
            tcpClient.ConnectWithIP("127.0.0.1", port);
        } else {
            tcpClient.ConnectWithIP(tcpClient.ResolveHostnameToIPAddress(hostname), port);
        }
        tcpClient.SendMessage("<protocol>");
        tcpClient.SendMessage(scMessageConverter.CreateJoinReservedRequestMessage(reservationCode).GetContent());
        ClientLoop();
        Shutdown();
        std::cout << "Disconnected. Bye.\n";
    }
}  // namespace Client