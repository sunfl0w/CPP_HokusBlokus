#include "scMessageConverter.hpp"

using namespace HokusBlokus::Blokus;
using namespace HokusBlokus::Util;

namespace HokusBlokus::Blokus::Communication {
    SC_MessageConverter::SC_MessageConverter() {}

    std::vector<SC_Message> SC_MessageConverter::FilterProtocolMessages(std::string &inputStream) {
        std::vector<SC_Message> protocolMessages;

        // Removing non xml-compliant messages. Duhhh!
        std::size_t protocolPos = inputStream.find("<protocol>");
        if (protocolPos != std::string::npos) {
            std::string protocolMessage = inputStream.substr(protocolPos, 10);
            inputStream.erase(protocolPos, 10);
            protocolMessages.push_back(SC_Message(protocolMessage, SC_MessageType::Protocol));
        }

        std::size_t protocolEndPos = inputStream.find("</protocol>");
        if (protocolEndPos != std::string::npos) {
            std::string protocolEndMessage = inputStream.substr(protocolEndPos, 11);
            inputStream.erase(protocolEndPos, 11);
            protocolMessages.push_back(SC_Message(protocolEndMessage, SC_MessageType::ProtocolEnd));
        }

        return protocolMessages;
    }

    std::vector<SC_Message> SC_MessageConverter::SplitInputMessagesIntoValidSC_Messages(std::string inputStream) {
        std::vector<SC_Message> messages;

        std::vector<SC_Message> protocolMessages = FilterProtocolMessages(inputStream);
        messages.insert(std::end(messages), std::begin(protocolMessages), std::end(protocolMessages));

        // Wrapping xml-compliant messages for easy parsing
        inputStream.insert(0, "<SC_Message>");
        inputStream.append("</SC_Message>");

        pugi::xml_document scMessageDoc;
        scMessageDoc.load_string(inputStream.data());
        for (pugi::xml_node scMessageNode : scMessageDoc.children()) {
            for (pugi::xml_node childNode : scMessageNode.children()) {
                SC_MessageType scMessageType = SC_MessageType::Undefined;

                std::string childNodeName(childNode.name());

                if (childNodeName == "join") {
                    scMessageType = SC_MessageType::JoinRequest;
                } else if (childNodeName == "joinPrepared") {
                    scMessageType = SC_MessageType::JoinRequestPrepared;
                } else if (childNodeName == "joined") {
                    scMessageType = SC_MessageType::Joined;
                } else if (childNodeName == "left") {
                    scMessageType = SC_MessageType::Left;
                } else if (childNodeName == "room") {
                    std::string classAttributeValue = childNode.child("data").attribute("class").value();
                    if (classAttributeValue == "welcomeMessage") {
                        scMessageType = SC_MessageType::Welcome;
                    } else if (classAttributeValue == "memento") {
                        scMessageType = SC_MessageType::GameState;
                    } else if (classAttributeValue == "sc.framework.plugins.protocol.MoveRequest") {
                        scMessageType = SC_MessageType::MoveRequest;
                    } else if (classAttributeValue == "result") {
                        scMessageType = SC_MessageType::Result;
                    } else if (classAttributeValue == "error") {
                        scMessageType = SC_MessageType::Error;
                    }
                }
                Util::XMLStringWriter xmlStringWriter;
                childNode.print(xmlStringWriter, " ", pugi::format_default);
                messages.push_back(SC_Message(xmlStringWriter.stringData, scMessageType));
            }
        }

        return messages;
    }

    SC_Message SC_MessageConverter::CreateProtocolMessage() {
        return SC_Message("<protocol>", SC_MessageType::Protocol);
    }

    SC_Message SC_MessageConverter::CreateProtocolEndMessage() {
        return SC_Message("</protocol>", SC_MessageType::ProtocolEnd);
    }

    SC_Message SC_MessageConverter::CreateJoinRequestMessage() {
        return SC_Message("<join gameType=\"swc_2021_blokus\" />", SC_MessageType::JoinRequest);
    }

    SC_Message SC_MessageConverter::CreateJoinReservedRequestMessage(const std::string &reservationCode) {
        return SC_Message("<joinPrepared reservationCode=\"" + reservationCode + "\" />", SC_MessageType::JoinRequestPrepared);
    }

    SC_Message SC_MessageConverter::CreateMoveMessage(const HokusBlokus::Blokus::Move &move, const std::string &roomID) {
        Logger::getInstance() << "Creating move\n";

        pugi::xml_document moveMessageDoc;

        pugi::xml_node roomNode = moveMessageDoc.append_child("room");
        roomNode.append_attribute("roomId").set_value(roomID.c_str());
        pugi::xml_node dataNode = roomNode.append_child("data");

        Logger::getInstance() << "CHECK1\n";

        if (move.GetMoveType() == MoveType::SetMove) {
            Logger::getInstance() << "Set move\n";

            dataNode.append_attribute("class").set_value("sc.plugin2021.SetMove");

            pugi::xml_node pieceNode = dataNode.append_child("piece");
            pieceNode.append_attribute("color").set_value(ColorToString(move.GetColor()).c_str());
            pieceNode.append_attribute("kind").set_value(PieceShapeToString(move.GetPieceShape()).c_str());
            Piece movedPiece = PieceManager::GetPiece(move.GetPieceShape());
            pieceNode.append_attribute("rotation").set_value(PieceRotationToString(movedPiece.GetPieceBitmaskComplements()[move.GetComplementNumber()].GetRotation()).c_str());
            if(movedPiece.GetPieceBitmaskComplements()[move.GetComplementNumber()].IsFlipped()) {
                pieceNode.append_attribute("isFlipped").set_value("true");
            } else {
                pieceNode.append_attribute("isFlipped").set_value("false");
            }

            pugi::xml_node destinationNode = pieceNode.append_child("position");
            destinationNode.append_attribute("x").set_value(move.GetDestination().x);
            destinationNode.append_attribute("y").set_value(move.GetDestination().x);
        } else if (move.GetMoveType() == MoveType::SkipMove) {
            Logger::getInstance() << "Skip move\n";

            pugi::xml_node dataNode = roomNode.append_child("data");
            dataNode.append_attribute("class").set_value("sc.plugin2021.SkipMove");
        } else {
            Logger::getInstance() << "It is not allowed to send pass moves. This should never happen anyways :C\n";
            exit(1);
        }

        Util::XMLStringWriter xmlStringWriter;
        moveMessageDoc.print(xmlStringWriter, " ", pugi::format_default);

        return SC_Message(xmlStringWriter.stringData, SC_MessageType::Move);
    }

    int SC_MessageConverter::GetPlayerIDFromWelcomeMessage(const SC_Message &message) {
        pugi::xml_document scMessageDoc;
        scMessageDoc.load_string(message.GetContent().data());
        std::string color(scMessageDoc.child("room").child("data").attribute("color").value());

        if (color == "one") {
            return 0;
        } else {
            return 1;
        }
    }

    std::string SC_MessageConverter::GetRoomIDFromJoinedMessage(const SC_Message &message) {
        pugi::xml_document scMessageDoc;
        scMessageDoc.load_string(message.GetContent().data());
        std::string roomID(scMessageDoc.child("joined").attribute("roomId").value());
        return roomID;
    }

    HokusBlokus::Blokus::GameState SC_MessageConverter::GetGameStateFromGameStateMessage(const SC_Message &message) {

        pugi::xml_document scMessageDoc;
        scMessageDoc.load_string(message.GetContent().data());
        pugi::xml_node roomNode = scMessageDoc.child("room");

        GameState gameState;

        //Read metadata from game state

        for (pugi::xml_attribute stateAttribute : roomNode.child("data").child("state").attributes()) {
            std::string stateAttributeName(stateAttribute.name());
            if (stateAttributeName == "currentColorIndex") {
                int currentColorID = std::stoi(stateAttribute.value());
                gameState.GetColorQueue().SetCurrentColor(IntToColor(currentColorID));
            } else if (stateAttributeName == "turn") {
                gameState.SetTurn(std::stoi(stateAttribute.value()));
            } else if (stateAttributeName == "startPiece") {
                std::string startPieceString = stateAttribute.value();
                gameState.SetStartingPieceShape(StringToPieceShape(startPieceString));
            }
        }

        //Read board positions

        std::bitset<484> blueSet = std::bitset<484>();
        std::bitset<484> yellowSet = std::bitset<484>();
        std::bitset<484> redSet = std::bitset<484>();
        std::bitset<484> greenSet = std::bitset<484>();

        for (pugi::xml_node fieldsNode : roomNode.child("data").child("state").child("board").children()) {
            for (pugi::xml_node fieldNode : fieldsNode.children("field")) {
                int x = 0;
                int y = 0;
                for (pugi::xml_attribute fieldAttribute : fieldNode.attributes()) {
                    std::string fieldAttributeName(fieldAttribute.name());
                    if (fieldAttributeName == "x") {
                        x = std::stoi(fieldAttribute.value());
                    } else if (fieldAttributeName == "y") {
                        y = std::stoi(fieldAttribute.value());
                    } else if (fieldAttributeName == "content") {
                        if (std::string(fieldAttribute.value()) == "BLUE") {
                            blueSet[(x + 1) * (y + 1) * 22] = true;
                        } else if (std::string(fieldAttribute.value()) == "YELLOW") {
                            yellowSet[(x + 1) * (y + 1) * 22] = true;
                        } else if (std::string(fieldAttribute.value()) == "RED") {
                            redSet[(x + 1) * (y + 1) * 22] = true;
                        } else {
                            greenSet[(x + 1) * (y + 1) * 22] = true;
                        }
                    }
                }
            }
        }

        //Read undeployed pieces

        gameState.GetBoard().SetBitmask(Color::BLUE, blueSet);
        gameState.GetBoard().SetBitmask(Color::YELLOW, yellowSet);
        gameState.GetBoard().SetBitmask(Color::RED, redSet);
        gameState.GetBoard().SetBitmask(Color::GREEN, greenSet);

        for (pugi::xml_node blueShapeNode : roomNode.child("data").child("state").child("blueShapes").children("shape")) {
            gameState.GetPlayerWithColor(Color::BLUE).AddUndeployedPieceShape(Color::BLUE, StringToPieceShape(blueShapeNode.child_value()));
        }

        for (pugi::xml_node yellowShapeNode : roomNode.child("data").child("state").child("yellowShapes").children("shape")) {
            gameState.GetPlayerWithColor(Color::YELLOW).AddUndeployedPieceShape(Color::YELLOW, StringToPieceShape(yellowShapeNode.child_value()));
        }

        for (pugi::xml_node redShapeNode : roomNode.child("data").child("state").child("redShapes").children("shape")) {
            gameState.GetPlayerWithColor(Color::RED).AddUndeployedPieceShape(Color::RED, StringToPieceShape(redShapeNode.child_value()));
        }

        for (pugi::xml_node greenShapeNode : roomNode.child("data").child("state").child("greenShapes").children("shape")) {
            gameState.GetPlayerWithColor(Color::GREEN).AddUndeployedPieceShape(Color::GREEN, StringToPieceShape(greenShapeNode.child_value()));
        }

        //Reding color move order

        for (pugi::xml_node colorNode : roomNode.child("data").child("state").child("orderedColors").children("color")) {
            std::vector<Color> colorsInGame = std::vector<Color>();
            if(std::string(colorNode.value()) == "BLUE") {
                colorsInGame.push_back(Color::BLUE);
            } else if(std::string(colorNode.value()) == "YELLOW") {
                colorsInGame.push_back(Color::YELLOW);
            } else if(std::string(colorNode.value()) == "RED") {
                colorsInGame.push_back(Color::RED);
            } else if(std::string(colorNode.value()) == "GREEN") {
                colorsInGame.push_back(Color::GREEN);
            }

            if(std::find(colorsInGame.begin(), colorsInGame.end(), Color::BLUE) == colorsInGame.end()) {
                gameState.GetColorQueue().RemoveColor(Color::BLUE);
            }

            if(std::find(colorsInGame.begin(), colorsInGame.end(), Color::YELLOW) == colorsInGame.end()) {
                gameState.GetColorQueue().RemoveColor(Color::YELLOW);
            }

            if(std::find(colorsInGame.begin(), colorsInGame.end(), Color::RED) == colorsInGame.end()) {
                gameState.GetColorQueue().RemoveColor(Color::RED);
            }

            if(std::find(colorsInGame.begin(), colorsInGame.end(), Color::GREEN) == colorsInGame.end()) {
                gameState.GetColorQueue().RemoveColor(Color::GREEN);
            }
        }

        //LastMove : TODO

        Vec2i lastMoveDestination = Vec2i(0,0);
        PieceShape lastMovePieceShape = PieceShape::MONOMINO;
        int lastMoveComplementNumber = 0;
        Color lastMoveColor = Color::BLUE;
        MoveType lastMoveType = MoveType::SkipMove;

        Move lastMove = Move(lastMoveDestination, lastMovePieceShape, lastMoveColor, lastMoveType, lastMoveComplementNumber);

        gameState.SetLastPerformedMove(lastMove);

        Logger::getInstance() << "Received game state----\n";
        Logger::getInstance() << gameState.Draw();
        Logger::getInstance() << "Received game state----\n";

        return gameState;
    }

    int SC_MessageConverter::GetIDOfWinningPlayerFromResultMessage(const SC_Message &message) {
        int idOfWinningPlayer;
        pugi::xml_document scMessageDoc;
        scMessageDoc.load_string(message.GetContent().data());
        pugi::xml_node roomNode = scMessageDoc.child("room");
        idOfWinningPlayer = std::stoi(roomNode.child("data").child("winner").child("color").value());
        return idOfWinningPlayer;
    }
}  // namespace HokusBlokus::Blokus::Communication