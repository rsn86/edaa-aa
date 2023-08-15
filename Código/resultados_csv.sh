#!/bin/bash

THIS=$(basename $(readlink -nf $0))
THIS_PATH=$(dirname $(readlink -nf $0))

RESULTS_DIR="${THIS_PATH}/../Resultados"
CSV_FILE="${RESULTS_DIR%/}/resultados.csv"

[[ -f "${CSV_FILE}" ]] && mv "${CSV_FILE}" "${CSV_FILE}_$(date +%Y%m%d%H%M%S)"

printf "%s;%s;%s;%s;%s\n" "método" "cenário" "tamanho" "trocas" "tempo" | tee -a "${CSV_FILE}"

for file in bubble.txt bucket.txt insertion.txt selection.txt; do
    [[ ! -f "${RESULTS_DIR%/}/${file}" ]] && continue
    algo=$(basename "${file}" ".txt")
    awk -valgo="${algo}" -F'/' 'BEGIN{OFS=";"} /txt/{cenario=$1; tamanho=$2; gsub(/[^0-9]/,"", tamanho); getline; gsub(/ /,";"); gsub(/\./,","); print algo,cenario,tamanho,$0}' "${RESULTS_DIR%/}/${file}" | tee -a "${CSV_FILE}"
done

