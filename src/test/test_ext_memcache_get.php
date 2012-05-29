<?php

/*
 * Functional test for get() of ext_memcache.
 * @author Weijun Li
 * @copyright 2012, Zynga Game Network, Inc.
*/

function mc_add($mc, $key, $val, $flag, $timeout) {
  $result = $mc->add($key, $val, $flag, $timeout);
  echo "add() key: '$key' result '$result' val: '$val' flag '$flag' timeout '$timeout'\n";
  return $result;
}

$failures = 0;

$kvs = array('k1' => 'val_1', 'k2' => 'val_2', 'k3' => 'val_3', 'k4' => 'val_4', 'k5' => 'val_5');
$svs = array('127.0.0.1' => 11211);

$memcache = new Memcache();
foreach($svs as $ip => $port) {
  $memcache->addServer($ip, $port);
  printf("added server ip=%s port=%s\n", $ip, $port);
}

foreach($svs as $ip => $port) {
  $status = $memcache->getServerStatus($ip, $port);
  printf("status=%s ip=%s port=%s\n", $status, $ip, $port);
}

// add()
$timeout = 1209600;
$cas = 0;
$flag = 0;

foreach($kvs as $k => $v) {
  $result = mc_add($memcache, $k, $v, $flag, $timeout);
}

echo "[1] Call get() with one key\n";
$retResult = null;
$retVal = null;
$retFlags = null;
$retCas = null;

$retVal = $memcache->get('k1', $retFlags, $retCas);
if( $retVal != $kvs['k1'] ) {
  $failures++;
  echo "Failed with invalid retVal=$retVal\n";
}

if( !$retCas ) {
  $failures++;
  echo "Failed with invalid retCas=$retCas\n";
} 

echo "[2] Call get() with multiple good keys\n";
$retResult = null;
$retVal = null;
$retFlags = null;
$retCas = null;

$retVal = $memcache->get(array('k1', 'k3'), $retFlags, $retCas);
$retValDump = print_r($retVal, true);
$retFlagsDump = print_r($retFlags, true);
$retCasDump = print_r($retCas, true);
if( count($retVal) != 2 || $retVal['k1'] != $kvs['k1'] || $retVal['k3'] != $kvs['k3'] ) {
  $failures++;
  echo "Failed with invalid retVal=$retValDump\n";
}

if( count($retCas) != 2 || !$retCas['k1'] || !$retCas['k3'] ) {
  $failures++;
  echo "Failed with invalid retCas=$retCasDump\n";
}

if( count($retFlags) != 2 ) {
  $failures++;
  echo "Failed with invalid retFlags=$retFlagsDump\n";}

echo "[3] Call get() with multiple bad keys\n";
$retResult = null;
$retVal = null;
$retFlags = null;
$retCas = null;

$retVal = $memcache->get(array('k1', 'k10'), $retFlags, $retCas);
$retValDump = print_r($retVal, true);
$retFlagsDump = print_r($retFlags, true);
$retCasDump = print_r($retCas, true);
if( count($retVal) != 1 || $retVal['k1'] != $kvs['k1'] ) {
  $failures++;
  echo "Failed with invalid retVal=$retValDump\n";
}

if( count($retCas) != 1 || !$retCas['k1'] ) {
  $failures++;
  echo "Failed with invalid retCas=$retCasDump\n";
}

if( count($retFlags) != 1 ) {
  $failures++;
  echo "Failed with invalid retFlags=$retFlagsDump\n";}


// == delete()
foreach($kvs as $k => $v) {
  $memcache->delete($k);
}

if( $failures != 0 ) {
  echo "**** ERROR failures=$failures\n";
}
else {
  echo "SUCCESS!\n";
}

