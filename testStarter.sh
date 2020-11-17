#!/bin/sh
chmod +x bin/CPP_HokusBlokus_Starter
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
"$DIR/bin/CPP_HokusBlokus_Starter" "$@" "--verbose"