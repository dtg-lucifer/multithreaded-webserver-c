#!/bin/bash

HOST="localhost"
PORT=8998
ENDPOINT="/"
TOTAL_REQUESTS=5000
CONCURRENT=10

echo "Starting concurrent load test..."

for ((i = 1; i <= TOTAL_REQUESTS; i++)); do
  (
    START=$(date +%s%3N)
    RESPONSE=$(curl -s -o /dev/null -w "%{http_code}" http://$HOST:$PORT$ENDPOINT)
    END=$(date +%s%3N)
    TIME_TAKEN=$((END - START))
    echo "Request $i: status $RESPONSE - ${TIME_TAKEN}ms"
  ) &

  if (( i % CONCURRENT == 0 )); then
    wait
  fi
done

wait
