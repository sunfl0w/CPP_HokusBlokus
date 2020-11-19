#!/bin/sh
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
chmod +x "$DIR/bin/CPP_HokusBlokus_Starter"
"$DIR/bin/CPP_HokusBlokus_Starter" "$@" "--verbose"