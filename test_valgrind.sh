#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
CYAN='\033[0;36m'
YELLOW='\033[0;33m'
RESET='\033[0m'

BINARY="./cub3D"
VALID_MAP="map/valid_map/intra.cub"
INVALID_DIR="map/invalid_map"
PASS=0
FAIL=0

run_valgrind()
{
	local map="$1"
	local expect_error="$2"
	local name
	name=$(basename "$map")

	local output
	output=$(valgrind \
		--leak-check=full \
		--show-leak-kinds=all \
		--track-fds=yes \
		--error-exitcode=42 \
		"$BINARY" "$map" 2>&1)

	local exit_code=$?
	local has_leak=0
	local has_fd_leak=0

	echo "$output" | grep -q "definitely lost: [^0]" && has_leak=1
	echo "$output" | grep -q "indirectly lost: [^0]" && has_leak=1
	echo "$output" | grep -q "possibly lost: [^0]" && has_leak=1
	echo "$output" | grep -q "still reachable: [^0]" && has_leak=1
	echo "$output" | grep -q "Open file descriptor" && has_fd_leak=1

	if [ "$expect_error" = "1" ]; then
		if echo "$output" | grep -qE "ERROR SUMMARY: 0 errors" && \
		   [ "$has_leak" -eq 0 ] && [ "$has_fd_leak" -eq 0 ]; then
			echo -e "  ${GREEN}[OK]${RESET}  $name"
			PASS=$((PASS + 1))
		else
			echo -e "  ${RED}[KO]${RESET}  $name"
			[ "$has_leak" -eq 1 ] && echo -e "         ${RED}→ memory leak detecte${RESET}"
			[ "$has_fd_leak" -eq 1 ] && echo -e "         ${RED}→ fd leak detecte${RESET}"
			FAIL=$((FAIL + 1))
		fi
	else
		if echo "$output" | grep -qE "ERROR SUMMARY: 0 errors" && \
		   [ "$has_leak" -eq 0 ] && [ "$has_fd_leak" -eq 0 ]; then
			echo -e "  ${GREEN}[OK]${RESET}  $name"
			PASS=$((PASS + 1))
		else
			echo -e "  ${RED}[KO]${RESET}  $name"
			[ "$has_leak" -eq 1 ] && echo -e "         ${RED}→ memory leak detecte${RESET}"
			[ "$has_fd_leak" -eq 1 ] && echo -e "         ${RED}→ fd leak detecte${RESET}"
			FAIL=$((FAIL + 1))
		fi
	fi
}

echo -e "${CYAN}========================================${RESET}"
echo -e "${CYAN}   cub3D - Tests Valgrind${RESET}"
echo -e "${CYAN}========================================${RESET}"

echo -e "\n${YELLOW}>>> Compilation...${RESET}"
make re > /dev/null 2>&1
if [ $? -ne 0 ]; then
	echo -e "${RED}Compilation echouee, arret.${RESET}"
	exit 1
fi
echo -e "${GREEN}Compilation OK${RESET}"

echo -e "\n${YELLOW}>>> Cartes invalides (doivent quitter proprement sans leak) :${RESET}"
for map in "$INVALID_DIR"/*.cub; do
	run_valgrind "$map" 1
done

echo -e "\n${YELLOW}>>> Carte valide (lancement 2 secondes, verification leak a la fermeture) :${RESET}"
timeout 2 valgrind \
	--leak-check=full \
	--show-leak-kinds=all \
	--track-fds=yes \
	"$BINARY" "$VALID_MAP" > /tmp/valgrind_valid.log 2>&1
output=$(cat /tmp/valgrind_valid.log)
has_leak=0
has_fd_leak=0
echo "$output" | grep -q "definitely lost: [^0]" && has_leak=1
echo "$output" | grep -q "indirectly lost: [^0]" && has_leak=1
echo "$output" | grep -q "possibly lost: [^0]" && has_leak=1
echo "$output" | grep -q "Open file descriptor" && has_fd_leak=1
name=$(basename "$VALID_MAP")
if [ "$has_leak" -eq 0 ] && [ "$has_fd_leak" -eq 0 ]; then
	echo -e "  ${GREEN}[OK]${RESET}  $name"
	PASS=$((PASS + 1))
else
	echo -e "  ${RED}[KO]${RESET}  $name"
	[ "$has_leak" -eq 1 ] && echo -e "         ${RED}→ memory leak detecte${RESET}"
	[ "$has_fd_leak" -eq 1 ] && echo -e "         ${RED}→ fd leak detecte${RESET}"
	FAIL=$((FAIL + 1))
fi

echo -e "\n${CYAN}========================================${RESET}"
echo -e "  Resultats : ${GREEN}$PASS OK${RESET} / ${RED}$FAIL KO${RESET}"
echo -e "${CYAN}========================================${RESET}\n"
