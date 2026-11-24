#!/bin/bash

if [ $# -ne 2 ]; then
  echo "Error: Two arguments required (directory and search string)"
  exit 1
fi

if [ ! -d "$1" ]; then
  echo "Error: $1 is not a valid directory"
  exit 1
fi

shopt -s nullglob

file_cnt=0
match_cnt=0

search_dir() {
  local dir="$1"
  local search_term="$2"

  echo "$dir"
  echo "$search_term"

  for item in "$dir"/*; do
    if [ -d "$item" ]; then
      # It's a directory - recurse into it
      search_dir "$item" "$search_term"
    elif [ -f "$item" ]; then
      # It's a file - process it
      ((file_cnt++))

      while IFS= read -r line || [ -n "$line" ]; do
        if [[ "$line" == *"$search_term"* ]]; then
          ((match_cnt++))
        fi
      done <"$item"
    fi
  done
}

search_dir "$1" "$2"

echo "The number of files are $file_cnt and the number of matching lines are $match_cnt"
