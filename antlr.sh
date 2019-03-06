#!/bin/bash
export ANTLRDIR=./antlr
CLASSPATH="$ANTLRDIR/antlr-4.7.2-complete.jar:." \
	 exec java -jar $ANTLRDIR/antlr-4.7.2-complete.jar "$@"

# antlr.sh -visitor -no-listener -Dlanguage=Cpp <file>