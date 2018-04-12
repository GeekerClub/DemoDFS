#!/bin/bash

PRINT_GREEN='\033[40;32m'

echo -e $PRINT_GREEN"Install toft component ..."$PRINT_GREEN
git clone https://github.com/GeekerClub/toft

echo ""
echo ""

echo -e $PRINT_GREEN"Install thirdparty component ..."$PRINT_GREEN
git clone https://github.com/GeekerClub/thirdparty
echo ""
echo ""


echo -e $PRINT_GREEN"Install trident component ..."$PRINT_GREEN
git clone https://github.com/GeekerClub/trident
