<?php

/*
 * Functional test for getl of ext_memcache.
 * @author Weijun Li
 * @copyright 2012, Zynga Game Network, Inc.  
*/

function mc_add($mc, $key, $val, $flag, $timeout) {
  $result = $mc->add($key, $val, $flag, $timeout);
  echo "add() key: '$key' result '$result' val: '$val' flag '$flag' timeout '$timeout'\n";
  return $result;
}

$memcache = new Memcache();
$memcache->addServer("10.34.175.217",11211);

$failures = 0;

// add()
$timeout = 1209600;
$cas = 0;

$val = "value1-hiphop";
$val_cas = "after cas";
$key = "hhfoo";

$val2 = "v2_zynga";
$key2 = "hhfoo_k2";
$flag = 0;


// == get2()
$valRet = null;

$cas = 0;

$result = mc_add($memcache, $key, $val, $flag, $timeout);

$result = $memcache->get($key, $flag);
echo "get($key, $flag) result: $result\n";

echo $result ? "OK\n" : "FAILED\n";
if( !$result ) $failures++;

////
$lockSeconds = 2;
$result = $memcache->getl($key, $lockSeconds, $flag);
echo "lock-- getl($key, $flag, $lockSeconds) result: $result\n";

echo $result ? "OK\n" : "FAILED\n";
if( !$result ) $failures++;

// get it right away should fail

echo "within lock... \n";
$result = $memcache->get($key, $flag);
echo "get($key, $flag) result: $result\n";
if( !$result ) $failures++;

echo "delete within lock...\n";
$result = $memcache->delete($key);
if( $result ) $failures++;
echo !$result ? "OK\n" : "Failed\n";

echo "set within lock...\n";
$result = $memcache->set($key, $val_cas);
if( !$result ) $failures++;
echo $result ? "OK\n" : "Failed\n";

echo "wait for $lockSeconds +1\n";
sleep($lockSeconds + 1);

// get it after expiration should work
echo "after lock \n";
$result = $memcache->get($key, $flag);
echo "get($key, $flag) result: $result\n";
if( $result != $val_cas ) $failures++;

echo "delete the key after expiration\n";
$result = $memcache->delete($key);
if( !$result ) $failures++;

if( $failures > 0 ) echo "Failed!! failures=$failures\n";
else echo "Succeeded!!\n";


