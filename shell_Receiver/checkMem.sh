#!/bin/sh

echo "Check Memory usage of a process.";
echo "Please put c for continue.";

read cont;

index=1;
while [ ${cont} = "c" ]
do
    echo "receiver count = ${index}" >> memUsage.txt;
    grep VmSize /proc/$1/status >> memUsage.txt;
    grep VmRSS /proc/$1/status >> memUsage.txt;
    grep VmLck /proc/$1/status >> memUsage.txt;
    echo "Please put c for continue.";
    read cont;
    index=`expr "${index}" "+" "1"`;
done
