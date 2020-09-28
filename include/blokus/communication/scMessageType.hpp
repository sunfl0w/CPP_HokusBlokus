#pragma once

namespace HokusBlokus::Blokus::Communication {
    /**
     * @brief This enum class lists all possible message types when communicating to the SC-Server.
     *
     */
    enum class SC_MessageType {
        Protocol,
        ProtocolEnd,
        Welcome,
        JoinRequest,
        JoinRequestPrepared,
        Joined,
        GameState,
        Move,
        MoveRequest,
        Left,
        Result,
        Error,
        Undefined,
    };
}  // namespace HokusBlokus::Blokus::Communication