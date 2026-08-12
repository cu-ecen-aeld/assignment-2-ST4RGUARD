#!/bin/bash

if [ $# -ne 2 ]; then
  echo "Error: Two arguments required (path/to/file and write term)"
  exit 1
fi

shopt -s nullglob

writefile() {

  local writefile="$1"
  local writestr="$2"

  local dir
  dir=$(dirname "$writefile")

  if mkdir -p "$dir" && printf '%s\n' "$writestr" >"$writefile"; then
    echo "Successfully wrote to $writefile"
  else
    echo "Error: Failed to create directory or write to file '$writefile'" >&2
    exit 1
  fi

}

writefile "$1" "$2"
