#!/bin/bash
set -e # Terminate on error

echo '*** Setting up smt/ directory'
rm -rf ./smt/ && mkdir -p smt

echo '*** Generating SMT files with UCLID5'
uclid -g "smt/output" main.ucl

echo '*** Append (get-model) to each file'
ls smt | xargs -I {} bash -c 'echo "(get-model)" >> smt/{}'

echo '*** Running Z3'
ls smt | xargs -I {} bash -c 'echo "Checking {}" && z3 -T:120 ./smt/{}'
