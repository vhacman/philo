#!/usr/bin/env bash

# tester.sh
# Tester esteso per il progetto philosophers
# Durata minima di ogni test: 15s, fino a 35s per stress
# Usage: ./advanced_philo_tester.sh [-v]

# ----------------------------
# Configurazione colori
# ----------------------------
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
MAGENTA='\033[0;35m'
CYAN='\033[0;36m'
BOLD='\033[1m'
NC='\033[0m' # No Color

# ----------------------------
# Contatori
# ----------------------------
PASSED=0
FAILED=0
TOTAL=0

VERBOSE=0
TIME_MIN=15s

# ----------------------------
# Funzioni di utilità
# ----------------------------
print_header() {
    echo -e "${BLUE}${BOLD}=============================================="
    echo -e "   ADVANCED DINING PHILOSOPHERS TESTER        "
    echo -e "==============================================${NC}"
    echo
}

print_summary() {
    echo -e "${BLUE}${BOLD}=============================================="
    echo -e "               RIASSUNTO TEST                 "
    echo -e "==============================================${NC}"
    echo -e "Totale test eseguiti: $TOTAL"
    echo -e "${GREEN}✔ Passati: $PASSED${NC}"
    echo -e "${RED}✖ Falliti: $FAILED${NC}"
    if [ $FAILED -eq 0 ]; then
        echo -e "${GREEN}${BOLD}Tutti i test sono passati! 🎉${NC}"
    else
        echo -e "${RED}${BOLD}Alcuni test sono falliti. Controlla i dettagli sopra.${NC}"
    fi
    echo
}

run_test() {
    local params="$1"
    local expected="$2"
    local desc="$3"
    local timeout_dur="$4"

    TOTAL=$((TOTAL + 1))
    echo -e "${YELLOW}${BOLD}Test #$TOTAL${NC}: $desc"
    echo -e "  Parametri: ${CYAN}$params${NC}"
    echo -e "  Atteso:    ${MAGENTA}$expected${NC}"
    echo -n "  Esecuzione... "

    # esegue con timeout
    if [ "$VERBOSE" -eq 1 ]; then
        timeout "$timeout_dur" ./philo $params
        exit_code=$?
        output=$(timeout "$timeout_dur" ./philo $params 2>&1)
    else
        timeout "$timeout_dur" ./philo $params > /tmp/philo_out 2>&1
        exit_code=$?
        output=$(< /tmp/philo_out)
    fi

    # determina risultato
    if [ $exit_code -eq 124 ]; then
        result="SURVIVED"
    else
        if echo "$output" | grep -q "died"; then
            result="DIED"
        else
            result="SURVIVED"
        fi
    fi

    # confronto
    if [ "$result" = "$expected" ]; then
        echo -e "${GREEN}✓ PASSED${NC}"
        PASSED=$((PASSED + 1))
    else
        echo -e "${RED}✗ FAILED${NC}"
        echo -e "    Atteso: $expected, Ottenuto: $result"
        echo -e "    Ultime righe di output:"
        echo "$output" | tail -n5 | sed 's/^/      /'
        FAILED=$((FAILED + 1))
    fi
    echo
    rm -f /tmp/philo_out
}

# ----------------------------
# Parsing argomenti
# ----------------------------
while getopts "vh" opt; do
    case $opt in
        v) VERBOSE=1 ;;
        h)
            echo "Usage: $0 [-v]  # -v verbose"
            exit 0
            ;;
    esac
done

# ----------------------------
# Main
# ----------------------------
print_header

# Compilazione
echo -e "${CYAN}Compilazione dell'eseguibile 'philo'...${NC}"
make re > /dev/null 2>&1
if [ ! -x "./philo" ]; then
    echo -e "${RED}Errore: eseguibile 'philo' non trovato. Assicurati di aver compilato.${NC}"
    exit 1
fi
echo -e "${GREEN}Compilazione riuscita!${NC}"
echo

# ----------------------------
# Definizione test
# ----------------------------
# format: run_test "philos die eat sleep [meals]" EXPECTED DESCRIPTION TIMEOUT
# Survival tests (dovrebbero SURVIVE)
run_test "5 800 200 200"        SURVIVED "5 filosofi, timing confortevole"      "15s"
run_test "5 800 200 200 7"      SURVIVED "5 filosofi, 7 pasti ciascuno"         "20s"
run_test "4 1000 100 100"       SURVIVED "4 filosofi, timing larghissimo"       "15s"
run_test "6 900 300 300"        SURVIVED "6 filosofi (pari), mangiano e dormono" "15s"
run_test "7 900 300 300"        SURVIVED "7 filosofi (dispari), carico medio"    "15s"
run_test "10 1200 200 200"      SURVIVED "10 filosofi, stress leggero"            "20s"
run_test "2 500 100 100"        SURVIVED "2 filosofi, scenario triviale"         "15s"

# Edge/Stress survival
run_test "100 800 200 200"      SURVIVED "100 filosofi, stress test"            "30s"
run_test "101 800 200 200"      SURVIVED "101 filosofi (dispari), stress"       "30s"

# Death tests (dovrebbero DIED)
run_test "1 800 200 200"        DIED     "1 filosofo: non può prendere due forchette" "10s"
run_test "5 300 200 200"        DIED     "5 filosofi, die_time troppo basso"         "10s"
run_test "5 200 300 200"        DIED     "eat_time > die_time"                       "10s"
run_test "4 400 100 400"        DIED     "sleep_time troppo lungo vs die_time"       "10s"
run_test "8 350 150 150"        DIED     "8 filosofi, timing strettissimo"           "15s"

# ----------------------------
# Summary
# ----------------------------
print_summary
