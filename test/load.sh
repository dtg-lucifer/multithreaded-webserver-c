#!/bin/bash

# Server address and port
HOST="localhost"
PORT=8998
ENDPOINT="/"
TOTAL_REQUESTS=100

echo "Starting load test on http://${HOST}:${PORT}${ENDPOINT}"
echo ""

for ((i = 1; i <= TOTAL_REQUESTS; i++)); do
  START=$(date +%s%3N)  # milliseconds
  RESPONSE=$(curl -s -o /dev/null -w "%{http_code}" http://$HOST:$PORT$ENDPOINT)
  END=$(date +%s%3N)

  TIME_TAKEN=$((END - START))

  echo "Request $i: status $RESPONSE - ${TIME_TAKEN}ms"
done
