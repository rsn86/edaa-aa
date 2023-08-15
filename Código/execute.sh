#!/bin/bash

THIS=$(basename $(readlink -nf $0))
THIS_PATH=$(dirname $(readlink -nf $0))

SORT_PROGRAM="${THIS_PATH}/sort"

DATA_DIR="${THIS_PATH}/../Dados"

RESULTS_DIR="${THIS_PATH}/../Resultados"
mkdir -p "${RESULTS_DIR}"

DATA_SUBDIRS=(Aleatórios Decrescentes Ordenados ParcialmenteOrdenados)

ALGORITHMS=(bubble selection insertion bucket)

for ALGORITHM in "${ALGORITHMS[@]}"; do
    RESULTS_FILE="${RESULTS_DIR}/${ALGORITHM}.txt"
    [[ -f "${RESULTS_FILE}" ]] && mv "${RESULTS_FILE}" "${RESULTS_FILE}_$(date +%Y%m%d%H%M%S)"
    for SUBDIR in "${DATA_SUBDIRS[@]}"; do
        for FILE in "${DATA_DIR%/}/${SUBDIR}"/*.txt; do
            echo "${SUBDIR%/}/$(basename "${FILE}")" | tee -a "${RESULTS_FILE}"
            $SORT_PROGRAM $ALGORITHM < "${FILE}"  | tee -a "${RESULTS_FILE}"
        done
    done
done

