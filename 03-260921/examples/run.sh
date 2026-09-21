#!/usr/bin/env bash
set -euo pipefail

# ./run.sh [число пачек по 1024 объекта] [число повторений]
batches=${1:-500000}
repeats=${2:-3}
if [[ $# -gt 2 || ! $batches =~ ^[1-9][0-9]*$ || ${#batches} -gt 7 ]] ||
   (( batches > 1000000 )) || [[ ! $repeats =~ ^[1-9]$ ]]; then
    printf 'Usage: %s [batches: 1..1000000] [repeats: 1..9]\n' "$0" >&2
    exit 2
fi

script_dir=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)
cc=${CC:-cc}
java=${JAVA:-java}
javac=${JAVAC:-javac}
for tool in "$cc" "$java" "$javac" /usr/bin/time; do
    command -v "$tool" >/dev/null || { printf 'Not found: %s\n' "$tool" >&2; exit 1; }
done

export LC_ALL=C
# Некоторые приложения macOS наследуют MallocNanoZone=0. Для обычной политики
# malloc убираем это переопределение только из окружения данного скрипта.
unset MallocNanoZone
build_dir=$(mktemp -d "${TMPDIR:-/tmp}/allocation-demo.XXXXXX")
trap 'rm -rf -- "$build_dir"' EXIT

printf 'Building examples (outside time)...\n'
"$cc" -O3 -std=c11 -Wall -Wextra -Werror \
    -fno-builtin-malloc -fno-builtin-free \
    "$script_dir/malloc_free.c" -o "$build_dir/malloc_free"
"$javac" -d "$build_dir" "$script_dir/ManagedAllocation.java"
"$java" -version
printf '\nObjects per measurement: %s; repetitions: %s\n' "$((batches * 1024))" "$repeats"
printf 'elapsed_ms: workload after warmup. time real/user/sys: whole process in seconds.\n'

java_flags=(-Xms128m -Xmx128m -XX:+UseSerialGC -XX:+AlwaysPreTouch
            -XX:-DoEscapeAnalysis -Xbatch)
expected_checksum=''

run_timed() {
    local label=$1
    local round=$2
    shift 2
    local log="$build_dir/$label-$round.log"
    local checksum real
    printf '\n--- %s, run %s/%s ---\n' "$label" "$round" "$repeats"
    # -p одинаково работает у внешнего time в Linux и macOS.
    /usr/bin/time -p "$@" 2>&1 | tee "$log"
    checksum=$(sed -n 's/.* checksum=\([0-9][0-9]*\).*/\1/p' "$log")
    if [[ -z $checksum || ( -n $expected_checksum && $checksum != "$expected_checksum" ) ]]; then
        printf 'Checksum missing or different between runs.\n' >&2
        exit 1
    fi
    expected_checksum=$checksum
    real=$(awk '$1 == "real" {print $2}' "$log")
    if [[ ! $real =~ ^[0-9]+([.][0-9]+)?$ ]]; then
        printf 'Could not parse exactly one real time from /usr/bin/time.\n' >&2
        exit 1
    fi
    printf '%s\n' "$real" >> "$build_dir/$label.seconds"
}

for (( round=1; round<=repeats; ++round )); do
    if (( round % 2 )); then
        run_timed C "$round" "$build_dir/malloc_free" "$batches"
        run_timed Java "$round" "$java" "${java_flags[@]}" -cp "$build_dir" ManagedAllocation "$batches"
    else
        run_timed Java "$round" "$java" "${java_flags[@]}" -cp "$build_dir" ManagedAllocation "$batches"
        run_timed C "$round" "$build_dir/malloc_free" "$batches"
    fi
done

median() {
    sort -n "$1" | awk '{v[NR]=$1} END {
        if (NR % 2) print v[(NR+1)/2]; else print (v[NR/2]+v[NR/2+1])/2
    }'
}
c_seconds=$(median "$build_dir/C.seconds")
java_seconds=$(median "$build_dir/Java.seconds")
awk -v c="$c_seconds" -v j="$java_seconds" 'BEGIN {
    printf "\nMedian whole-process real: C %.2f s; Java %.2f s\n", c, j;
    if (j > 0) printf "C / Java time ratio: %.2fx (>1 means Java took less time)\n", c/j;
}'
