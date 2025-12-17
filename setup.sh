#!/bin/bash

# DSA Visual Library - Setup Script

echo "=================================================="
echo "  DSA Visual Library - Setup & Installation"
echo "=================================================="
echo ""

GREEN='\033[1;32m'
YELLOW='\033[1;33m'
RED='\033[1;31m'
CYAN='\033[1;36m'
NC='\033[0m'

echo -n "Checking for make... "
if command -v make &> /dev/null; then
    echo -e "${GREEN}✓ Found${NC}"
else
    echo -e "${RED}✗ Not found${NC}"
    echo "Please install make: sudo apt-get install build-essential"
    exit 1
fi

echo -n "Checking for gcc... "
if command -v gcc &> /dev/null; then
    echo -e "${GREEN}✓ Found${NC}"
    gcc --version | head -n 1
else
    echo -e "${RED}✗ Not found${NC}"
    echo "Please install gcc: sudo apt-get install build-essential"
    exit 1
fi

echo ""
echo -e "${CYAN}Building the library...${NC}"
echo ""

make clean

if make; then
    echo ""
    echo -e "${GREEN}=================================================="
    echo "  ✓ Build Successful!"
    echo -e "==================================================${NC}"
    echo ""
    echo "  Run interactive demo:"
    echo -e "     ${CYAN}./dsa_demo${NC}"
    echo ""
    exit 0
else
    echo ""
    echo -e "${RED}=================================================="
    echo "  ✗ Build Failed"
    echo -e "==================================================${NC}"
    echo ""
    echo "Please check the error messages above."
    exit 1
fi
