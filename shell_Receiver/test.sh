#!/bin/bash


port1=$ALTIBASE_PORT_NO;
ROOT=$ALTIBASE_HOME;
replPort=$ALTIBASE_REPLICATION_PORT_NO;

export REPLICATION_PORT_NO=${replPort};


# remove old db
CMD="rm -rf db*";
$CMD;

# PORT확인
echo "Receiver port = ${port1}";
echo "Root = ${ROOT}";
# isql settings
ADMIN1="${ALTIBASE_HOME}/bin/isql -silent -u sys -p manager -s 127.0.0.1"

# receiver를 위한 server를 start한다.
CMD="server kill";
$CMD;
CMD="destroydb -n mydb";
$CMD;
CMD="createdb -M 10";
$CMD;
CMD="server start";
$CMD;


echo "=================================================================";
echo "Altibase for back-up is ready";
echo "If you want to start one more server, please put 'c'.";
echo "=================================================================";

read cont;

index=1;

while [ ${cont} = "c" ]
do
# port를 정한다.
    portNo=`expr "${index}" "*" "1000" "+" "30084"`;
    replPortNo=`expr "${portNo}" + "1"`;
    echo "index  = ${index}";
    echo "portNo = ${portNo}";

    CMD="mkdir db${index}";
    $CMD;
    CMD="ln -s ${ROOT}/bin db${index}/bin";
    $CMD;
    CMD="ln -s ${ROOT}/msg db${index}/msg";
    $CMD;
    CMD="ln -s ${ROOT}/dlib db${index}/dlib";
    $CMD;
    CMD="mkdir db${index}/conf";
    $CMD;
    CMD="cp -f $ALTIBASE_HOME/conf/altibase.properties db${index}/conf";
    $CMD;
    CMD="cp -f $ALTIBASE_HOME/conf/license             db${index}/conf";
    $CMD;
    CMD="mkdir db${index}/dbs";
    $CMD;
    CMD="mkdir db${index}/logs";
    $CMD;
    CMD="mkdir db${index}/trc";
    $CMD;
    CMD="mkdir db${index}/arch_logs";   
    $CMD;


    export ALTIBASE_HOME="${PWD}/db${index}";
    export ALTIBASE_PORT_NO="${portNo}";
    export ALTIBASE_REPLICATION_PORT_NO="${replPortNo}";

    echo "=-=-=-=-=-=-Test.sh-=-=-=-=-=-=";
    echo "ALTIBASE_HOME = ${ALTIBASE_HOME}";
    echo "ALTIBASE_PORT_NO = ${ALTIBASE_PORT_NO}";
    echo "ALTIBASE_REPLICATION_PORT_NO = ${ALTIBASE_REPLICATION_PORT_NO}";

    CMD="server kill";
    $CMD;
    CMD="destroydb -n mydb";
    $CMD;
    CMD="createdb -M 10";
    $CMD;
    CMD="server start";
    $CMD;

    echo "=================================================================";
    echo "Altibase is ready.";
    echo "If you want to start one more server, please put 'c'.";
    echo "=================================================================";

    read cont;

    index=`expr $index + 1`
done
