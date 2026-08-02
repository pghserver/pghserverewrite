#!/usr/bin/env bash
set -e
if [ "$PWD" != "$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd )" ]; then
    echo -e "\033[31mYou must run this script from its parent directory!\033[0m"
    exit 1
fi
echo -e "\033[34mBuilding PghServer...\033[0m"
cmake -S . -B build
cmake --build build
echo -e "\033[34mBuilt PghServer!\033[0m"