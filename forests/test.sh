#!/bin/bash

executable=$1
source_path=$2

for f in $source_path/*.in; 
do 
  echo -n "Test $f ";
  ./$executable <$f >out 2>err
  diff -w -q ${f%in}out out
  if [ "$?" -eq "1" ]
  then
      echo "nie działa.";
  else
      diff -w -q ${f%in}err err
      if [ "$?" -eq "1" ]
      then
        echo "nie działa.";
      else
        echo "działa.";
      fi;
  fi; 
done
rm out
rm err


