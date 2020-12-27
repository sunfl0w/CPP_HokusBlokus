%module(directors="1") Blokus

 %{
    #define SWIG_FILE_WITH_INIT
    #include "vec2i.hpp"
    #include "logic.hpp"
    #include "benchmark.hpp"
    #include "scMessageType.hpp"
    #include "scMessage.hpp"
    #include "scMessageConverter.hpp"
    #include "blokusClient.hpp"
    #include "tcpClient.hpp"
    #include "boundingRect.hpp"
    #include "boundingRectOptimizer.hpp"
    #include "board.hpp"
    #include "color.hpp"
    #include "gameState.hpp"
    #include "maskType.hpp"
    #include "move.hpp"
    #include "moveType.hpp"
    #include "pieceRotation.hpp"
    #include "piece.hpp"
    #include "pieceBitmask.hpp"
    #include "pieceBitmaskComplement.hpp"
    #include "pieceManager.hpp"
    #include "pieceShape.hpp"
    #include "player.hpp"

    using namespace HokusBlokus::Util;
    using namespace HokusBlokus::Util::Logging;
    using namespace HokusBlokus::PBM;
    using namespace HokusBlokus::Blokus;
    using namespace HokusBlokus::Blokus::AI;
    using namespace HokusBlokus::Blokus::Benchmark;
    using namespace HokusBlokus::Blokus::Client;
    using namespace HokusBlokus::Blokus::Communication;
    using namespace HokusBlokus::Blokus::Optimization;
    %}

%feature("director") HokusBlokus::Blokus::AI::Logic;

%include <argcargv.i>

%apply (int ARGC, char **ARGV) { (int argc, char *argv[]) }

void HokusBlokus::Blokus::Client::BlokusClient::Start(int argc, char *argv[]);

%include <std_array.i>

%include "typemaps.i"
%include "std_string.i"
%include "std_array.i"
%include "std_pair.i"
%include "std_vector.i"
%include "include/blokus/ai/logic.hpp"
%include "include/blokus/benchmark/benchmark.hpp"
%include "include/blokus/client/blokusClient.hpp"
%include "include/blokus/client/tcpClient.hpp"
%include "include/blokus/communication/scMessage.hpp"
%include "include/blokus/communication/scMessageConverter.hpp"
%include "include/blokus/communication/scMessageType.hpp"
%include "include/blokus/optimization/boundingRect.hpp"
%include "include/blokus/optimization/boundingRectOptimizer.hpp"
%include "include/blokus/board.hpp"
%include "include/blokus/color.hpp"
%include "include/blokus/gameState.hpp"
%include "include/blokus/maskType.hpp"
%include "include/blokus/move.hpp"
%include "include/blokus/moveType.hpp"
%include "include/blokus/piece.hpp"
%include "include/blokus/pieceBitmask.hpp"
%include "include/blokus/pieceBitmaskComplement.hpp"
%include "include/blokus/pieceManager.hpp"
%include "include/blokus/pieceRotation.hpp"
%include "include/blokus/pieceShape.hpp"
%include "include/blokus/player.hpp"
%include "include/blokus/vec2i.hpp"

%template(SC_Message_Vector) std::vector<HokusBlokus::Blokus::Communication::SC_Message>;
%template(Move_Vector) std::vector<HokusBlokus::Blokus::Move>;
%template(Bitmask_Complement_Vector) std::vector<HokusBlokus::Blokus::PieceBitmaskComplement>;
%template(Int_Vector) std::vector<int>;