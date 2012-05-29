<?php

/*
 * Functional test for get2() of ext_memcache.
 * @author Weijun Li
 * @copyright 2012, Zynga Game Network, Inc.
*/

print("==== Hello World\n");
print("0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789\n");
print("0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789\n");
print("0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789\n");
print("0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789\n");
print("0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789\n");
print("0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789\n");
print("0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789\n");
print("0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789\n");
print("0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789\n");
print("0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789\n");
printf("==== End Content\n");

function mc_add($mc, $key, $val, $flag, $timeout) {
  $result = $mc->add($key, $val, $flag, $timeout);
  echo "add() key: '$key' result '$result' val: '$val' flag '$flag' timeout '$timeout'\n";
  return $result;
}

$kvs = array('k1' => 'val_1', 'k2' => 'val_2', 'k3' => 'val_3', 'k4' => 'val_4', 'k5' => 'val_5');
$svs = array('127.0.0.1' => 11211, '127.0.0.2' => 11311, '333.0.0.3' => 11411, '333.0.0.4' => 11511, '333.0.0.5' => 11611);

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

// == get2()
$valRet = null;

//$result = $memcache->get($key, $flag);
//echo "get() result: '$result' \n";

$keyArray = array_keys($kvs);
$result = $memcache->get2($keyArray, $valRet, $flag, $cas);
$valDisp = print_r($valRet, true);
$casDisp = print_r($cas, true);
$resultDisp = print_r($result, true);
echo "get2() result: '$resultDisp' cas:'$casDisp' valRet: ['$valDisp']\n"; 

// == delete()
foreach($kvs as $k => $v) {
  $memcache->delete($k);
}

