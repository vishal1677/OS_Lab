#!/bin/sh

if [$# -ne 2 ]; then
  echo "You didnt entered 2 values"
  exit 1
fi 

num1=$1
num2=$2

sum_bc=$(echo "$1 +$2" | bc)
sum_expr=$(expr $num1+$num2)

echo "Sum bc $sum_bc"
echo "Sum expr $sum_expr"


