<?php

/**
 * Functional test cases for HipHop ext_igbinary
 * 
 * @author Weijun Li
 * @copyright 2012, Zynga Game Network, Inc.
 *
 */

$totalAsserts = 0;
$totalFailures = 0;
$failedCases = array();
$totalCases = 0;

function str2bin($bytestring) {
	$len = strlen($bytestring);
	$output = '';

	for ($i = 0; $i < $len; $i++) {
		$bin = decbin(ord($bytestring[$i]));
		$bin = str_pad($bin, 8, '0', STR_PAD_LEFT);
		$output .= $bin;
	}

	return $output;
}

function doSerializeUnserialize($variable) {
	$serialized = igbinary_serialize($variable);
	$unserialized = igbinary_unserialize($serialized);
}
	
function tassert1($val, $exp, $context) {
	global $totalAsserts, $totalFailures;
	$totalAsserts++;

	if( $val === $exp ) {
		echo "OK==$context\n";
	}
	else {
		$totalFailures++;
		echo "**** ERROR == for $context: val=$val exp=$exp\n";
		return false;
	}
	return true;
}

function tassert($val, $exp, $context, $compareEqual=true, $compareDump=true) {
	global $totalAsserts, $totalFailures;
	$totalAsserts++;

	$dumpVal = print_r($val, true);
	$dumpExp = print_r($exp, true);

	if( $compareEqual ) {
		if( $val == $exp ) {
			echo "OK==$context\n";
		}
		else {
			$totalFailures++;
			echo "**** ERROR == for $context:\n$dumpVal\n$dumpExp\n";
		}
	}

	if( $compareDump && $dumpVal !== $dumpExp ) {
		$totalFailures++;
		echo "**** ERROR Var dump differs for $context:\n$dumpVal\n$dumpExp\n";
		return false;
	}
	return true;
}

function assert_stats() {
	global $totalAsserts, $totalFailures, $failedCases, $totalCases;
	echo "++++++ totalCases=$totalCases totalAsserts=$totalAsserts totalFailures=$totalFailures\n";

	if( count($failedCases) > 0 ) {
		echo "#### Failed Cases ####\n";
		foreach($failedCases as $name) {
			echo "$name\n";
		}
		echo "#### End ####\n";
	}
}

function test($type, $variable, $test=true, $compareDump=true, $serStd=null, $funcVerify=null) {
	global $totalAsserts, $totalFailures;

	$serialized = igbinary_serialize($variable);
	$unserialized = igbinary_unserialize($serialized);

	//echo $type, "\n";
	//echo substr(bin2hex($serialized), 8), "\n";
	tassert($unserialized, $variable, $type, $test, $compareDump);
	//echo $unserialized === $variable ? 'OK' : 'ERROR';
	//echo "\n";

	if($serStd) {
		$totalAsserts++;
		$bin = substr(bin2hex($serialized), 8);
		if($serStd != $bin) {
			echo "**** ERROR Serialized bin differs from standard for $type\nserialized=$bin\nstandard  =$serStd\n";
			$totalFailures++;
		} else {
			echo "OK verified serialized bin2hex: $serStd\n";
		}
	}

	if( $funcVerify != null ) {
		$totalAsserts++;
		if( !call_user_func($funcVerify, $unserialized) ) {
			$dump = print_r($unserialized, false);
			echo "**** ERROR funcVerify() failed:\n" . $dump . "\n";
			$totalFailures++;
		}
		else {
	  echo "OK funcVerify()\n";
		}
	}
}

function testSer($type, $serializedHex, $funcVerify) {
	global $totalAsserts, $totalFailures;

	$serialized = pack('H*', $serializedHex);
	$unserialized = igbinary_unserialize($serialized);

	$totalAsserts++;
	if( !call_user_func($funcVerify, $unserialized) ) {
		$dump = print_r($unserialized, false);
		echo "**** ERROR funcVerify() for $type:\n$dump\n";
		$totalFailures++;
	}
	else {
		echo "OK funcVerify() for $type\n";
	}
}

function testForResult($context, $func, $expected) {
	global $totalAsserts, $totalFailures;
	
	$totalAsserts++;
	
	ob_start();
	call_user_func($func);
	$str = ob_get_clean();

	if( $str == $expected ) {
		echo "ResultTest $context OK\n";
	}
	else {
		$totalFailures++;
		echo "**** ResultTest $context failed\nresult=\n$str\nexpected=\n$expected\n";
	}
}

function testForResultFile($context, $func, $fileName) {
	testForResult($context, $func, file_get_contents($fileName));
}

abstract class TestCase {
	abstract public function getName();
	public function start() {
	}
	abstract public function run();
	public function end() {}
}

function runTest($clsName, $t) {
	global $totalAsserts, $totalFailures, $failedCases;

	echo "<== Testing $clsName\n";

	$t->start();

	$saveA = $totalAsserts;
	$saveF = $totalFailures;

	$t->run();

	$thisAsserts = $totalAsserts - $saveA;
	$thisFailures = $totalFailures - $saveF;

	if( $thisFailures > 0 ) {
		$failedCases[] = $t->getName();
	}

	printf("==> %s %s - [%s]. asserts=%d falures=%d\n",
	$clsName, $thisFailures > 0 ? "ERROR" : "OK",
	$t->getName(), $thisAsserts, $thisFailures);

	$t->end();
}

class Test_001 extends TestCase {
	public function getName() { return "basic 001"; }

	public function run() {

		$t1 = "This is for igbinary test!! 01234567890";

		$s1 = igbinary_serialize($t1);
		$t1_n = igbinary_unserialize($s1);

		tassert($t1_n, $t1, "string-igb");

		$book = new stdClass;
		$book->title = "Harry Potter and the Prisoner of Azkaban";
		$book->author = "J. K. Rowling";
		$book->publisher = "Arthur A. Levine Books";
		$book->amazon_link = "http://www.amazon.com/dp/0439136369/";
		$book->price = 9.98;
		$book->quantity = 101;

		$s = igbinary_serialize($book);
		$book_n = igbinary_unserialize($s);

		tassert($book->title, $book_n->title, "book title");
		tassert($book->price, $book_n->price, "book price");
		tassert($book->quantity, $book_n->quantity, "book quantity");
	}
}

class Test_002 extends TestCase {
	public function getName() { return "null"; }

	public function run() {
		test("null", null);
	}
}

class Test_003 extends TestCase {
	public function getName() { return "bool"; }

	public function run() {
		test('bool true',  true);
		test('bool false', false);
	}
}

class Test_004 extends TestCase {
	public function getName() { return "numbers"; }

	public function run() {
		test('zero: 0', 0);
		test('small: 1',  1);
		test('small: -1',  -1);
		test('medium: 1000', 1000);
		test('medium: -1000', -1000);
		test('large: 100000', 100000);
		test('large: -100000', -100000);
	}
}

class Test_005 extends TestCase {
	public function getName() { return "double"; }

	public function run() {
		test('double: 123.456', 123.456);
	}
}

class Test_006 extends TestCase {
	public function getName() { return "string"; }

	public function run() {
		test('empty: ""', "");
		test('string: "foobar"', "foobar");
	}
}

class Test_007 extends TestCase {
	public function getName() { return "array"; }

	public function run() {
		test('empty array: ', array());
		test('array(1, 2, 3)', array(1, 2, 3));
		test('array(array(1, 2, 3), arr...', array(array(1, 2, 3), array(4, 5, 6), array(7, 8, 9)));
	}
}

class Test_008 extends TestCase {
	public function getName() { return "array2"; }

	public function run() {
		test('array("foo", "foo", "foo")', array("foo", "foo", "foo"));
		test('array("one" => 1, "two" => 2))', array("one" => 1, "two" => 2));
		test('array("kek" => "lol", "lol" => "kek")', array("kek" => "lol", "lol" => "kek"));
		test('array("" => "empty")', array("" => "empty"));
	}
}

class Test_009 extends TestCase {
	public function getName() { return "array3_ref"; }

	public function run() {
		$a = array('foo');

		test('array($a, $a)', array($a, $a), true);
		test('array(&$a, &$a)', array(&$a, &$a), true);

		$a = array(null);
		$b = array(&$a);
		$a[0] = &$b;

		test('cyclic $a = array(&array(&$a))', $a, false);
	}
}

class Test_010 extends TestCase {
	public function getName() { return "array4"; }

	public function run() {
		$a = array(
      'a' => array(
	'b' => 'c',
        'd' => 'e'
        ),
      'f' => array(
	'g' => 'h'
	)
	);

	test('array', $a, false);
	}
}

class Obj {
	public $a;
	protected $b;
	private $c;

	function __construct($a, $b, $c) {
		$this->a = $a;
		$this->b = $b;
		$this->c = $c;
	}
}

class Test_012 extends TestCase {
	public function getName() { return "object"; }

	public function run() {
		$o = new Obj(1, 2, 3);

		test('object', $o, false, true, '17034f626a140311016106011104002a006206021106004f626a00630603');
	}
}

class Obj_13 {
	var $a;
	var $b;

	function __construct($a, $b) {
		$this->a = $a;
		$this->b = $b;
	}
}

class Test_013 extends TestCase {
	public function getName() { return "object"; }

	public function run() {
		$o = array(new Obj_13(1, 2), new Obj_13(3, 4));

		test('object', $o, false, true, '1402060017064f626a5f313314021101610601110162060206011a0014020e0106030e020604');
	}
}

class Obj_14 {
	var $a;
	var $b;

	function __construct($a, $b) {
		$this->a = $a;
		$this->b = $b;
	}
}

class Test_014 extends TestCase {
	public function getName() { return "object_ref"; }

	public function run() {
		$o = new Obj_14(1, 2);
		$a = array(&$o, &$o);

		test('object', $a, false, true, '140206002517064f626a5f31341402110161060111016206020601252201');
	}
}

class Obj_16 {
	public $a;
	protected $b;
	private $c;
	var $d;

	function __construct($a, $b, $c, $d) {
		$this->a = $a;
		$this->b = $b;
		$this->c = $c;
		$this->d = $d;
	}

	function __sleep() {
		return array('a', 'b', 'c');
	}

	public function getC() {
		return $this->c;
	}

	#       function __wakeup() {
	#               $this->d = $this->a + $this->b + $this->c;
	#       }
}

class Test_016 extends TestCase {
	public function getName() { return "object __sleep"; }

	public static function verifyUnserialized($obj) {
		return $obj->a == 1 && $obj->b == 2 && $obj->getC() == 3 && !isset($obj->d);
	}

	public function run() {
		$o = new Obj_16(1, 2, 3, 4);

		test('object', $o, false, false, '17064f626a5f3136140311016106011104002a006206021109004f626a5f313600630603', array('Test_016', 'verifyUnserialized'));
	}
}

class Obj_17 {
	var $a;
	var $b;

	function __construct($a, $b) {
		$this->a = $a;
		$this->b = $b;
	}

	function __wakeup() {
		$this->b = $this->a * 3;
	}
}

class Test_017 extends TestCase {
	public function getName() { return "object __wakeup"; }

	public static function verifyUnserialized($obj) {
		return $obj->a == 1 && $obj->b == 3;
	}

	public function run() {
		$o = new Obj_17(1, 2);
		test('object', $o, false, false, '17064f626a5f3137140211016106011101620602', array('Test_017', 'verifyUnserialized'));
	}
}

class Obj_18 {
	var $a;
	var $b;

	function __construct($a, $b) {
		$this->a = $a;
		$this->b = $b;
	}

	function __sleep() {
		return array('c');
	}

	#       function __wakeup() {
	#               $this->b = $this->a * 3;
	#       }
}

class Opj_18 {
	var $a;
	var $b;

	function __construct($a, $b) {
		$this->a = $a;
		$this->b = $b;
	}

	function __sleep() {
		return array(1);
	}

	#       function __wakeup() {
	#
	#       }
}

class Test_018 extends TestCase {
	public function getName() { return "object __wakeup"; }

	public static function verifyUnserialized($obj) {
		return !isset($obj->a) && !isset($obj->b);
	}

	public function run() {
		$o = new Obj_18(1, 2);
		$p = new Opj_18(1, 2);

		test('__sleep nonexisting', $o, false, false, '17064f626a5f3138140111016300', array('Test_018', 'verifyUnserialized'));
		test('__sleep wrong', $p, false, false, '17064f706a5f3138140100', array('Test_018', 'verifyUnserialized'));
	}
}

function __autoload($classname) {
	class Obj_19 {
		var $a;
		var $b;

		function __construct($a, $b) {
			$this->a = $a;
			$this->b = $b;
		}
	}
}

class Test_019 extends TestCase {
	public function getName() { return "__autoload class"; }

	public static function verifyUnserialized($obj) {
		return $obj->a==1 && $obj->b==2;
	}

	public function run() {

		testSer('autoload', '0000000217064f626a5f3139140211016106011101620602', array('Test_019', 'verifyUnserialized'));
	}
}

class Test_020 extends TestCase {
	public function getName() { return "__PHP_Incomplete_Class"; }

	public static function verifyUnserialized($obj) {
		return $obj->a==1 && $obj->b==2 && $obj->__PHP_Incomplete_Class_Name=='Obj_20';
	}

	public function run() {
		testSer('__PHP_Incomplete_Class', '0000000217064f626a5f3230140211016106011101620602', array('Test_020', 'verifyUnserialized'));

		/*
		 object(__PHP_Incomplete_Class)#1 (3) {
		 ["__PHP_Incomplete_Class_Name"]=>
		 string(6) "Obj_20"
		 ["a"]=>
		 int(1)
		 ["b"]=>
		 int(2)
		 }
		 */
	}
}

class Obj_21 implements Serializable {
	var $a;
	var $b;

	function __construct($a, $b) {
		$this->a = $a;
		$this->b = $b;
	}

	public function serialize() {
		return pack('NN', $this->a, $this->b);
	}

	public function unserialize($serialized) {
		$tmp = unpack('N*', $serialized);
		$this->__construct($tmp[1], $tmp[2]);
	}
}

class Test_021 extends TestCase {
	public function getName() { return "Serializable interface"; }

	public static function verifyUnserialized($obj) {
		return $obj->a==1 && $obj->b==2 && get_class($obj)=='Obj_21';
	}

	public function run() {
		$o = new Obj_21(1, 2);

		test('Serializable', $o, true, true, '17064f626a5f32311d080000000100000002', array('Test_021', 'verifyUnserialized'));
	}
}

function autoload_022($classname) {
	class Obj_22 {
		var $a;
		var $b;

		function __construct($a, $b) {
			$this->a = $a;
			$this->b = $b;
		}
	}
}

class Test_022 extends TestCase {
	public function getName() { return "unserialize_callback_func"; }

	public static function verifyUnserialized($obj) {
		return $obj->a==1 && $obj->b==2 && get_class($obj)=='Obj_22';
	}

	public function run() {
		$saveAutoload = ini_get('unserialize_callback_func');
		ini_set('unserialize_callback_func', 'autoload_022');
		 
		testSer('unserialize_callback_func', '0000000217064f626a5f3232140211016106011101620602', array('Test_022', 'verifyUnserialized'));

		ini_set('unserialize_callback_func', $saveAutoload);
	}
}

class Test_023 extends TestCase {
	public function getName() { return "resource"; }

	public static function verifyUnserialized($obj) {
		return $obj === null;
	}

	public function run() {
		$res = tmpfile();

		test('resource', $res, false, false, null, array('Test_023', 'verifyUnserialized'));

		fclose($res);
	}
}

class Obj_24 {
	public $a;
	protected $b;
	private $c;

	function __construct($a, $b, $c) {
		$this->a = $a;
		$this->b = $b;
		$this->c = $c;
	}

	public function getB() { return $this->b; }
	public function getC() { return $this->c; }
}

class Obj2_24 {
	public $aa;
	protected $bb;
	private $cc;
	private $obj;

	function __construct($a, $b, $c) {
		$this->a = $a;
		$this->b = $b;
		$this->c = $c;

		$this->obj = new Obj_24($a, $b, $c);
	}

	public function getObj() { return $this->obj; }
}

class Obj3_24 {
	private $objs;

	function __construct($a, $b, $c) {
		$this->objs = array();

		for ($i = $a; $i < $c; $i += $b) {
			$this->objs[] = new Obj_24($a, $i, $c);
		}
	}

	public function getObjs() { return $this->objs; }
}

class Obj4_24 {
	private $a;
	private $obj;

	function __construct($a) {
		$this->a = $a;
	}

	public function set($obj) {
		$this->obj = $obj;
	}

	public function getA() { return $this->a; }
	public function getObj() { return $this->obj; }
}

class Test_024 extends TestCase {
	public function getName() { return "objectrec"; }

	public static function verifyUnserialized2($obj) {
		return $obj->a==1 && $obj->b==2 && $obj->c==3
		&& ($obj->getObj()->a==1 && $obj->getObj()->getB()==2 && $obj->getObj()->getC()==3);
	}

	public static function verifyUnserialized3($obj) {
		$objs = $obj->getObjs();
		return count($objs) == 4 && get_class($objs[3]) == 'Obj_24';
	}

	public static function verifyUnserialized4($obj) {
		return $obj->getA()==100 && $obj == $obj->getObj();
	}

	public function run() {
		$o2 = new Obj2_24(1, 2, 3);
		test('objectrec', $o2, true, true, '17074f626a325f3234140711026161001105002a00626200110b004f626a325f323400636300110c004f626a325f3234006f626a17064f626a5f3234140311016106011104002a006206021109004f626a5f3234006306030e06060111016206021101630603',
		array('Test_024', 'verifyUnserialized2'));

		$o3 = new Obj3_24(0, 1, 4);
		test('objectrecarr', $o3, true, true, '17074f626a335f32341401110d004f626a335f3234006f626a731404060017064f626a5f3234140311016106001104002a006206001109004f626a5f32340063060406011a0214030e0306000e0406010e05060406021a0214030e0306000e0406020e05060406031a0214030e0306000e0406030e050604',
		array('Test_024', 'verifyUnserialized3'));

		$o4 = new Obj4_24(100);
		$o4->set($o4);
		test('objectselfrec', $o4, false, true, '17074f626a345f32341402110a004f626a345f323400610664110c004f626a345f3234006f626a2200',
		array('Test_024', 'verifyUnserialized4'));
	}
}

class Obj_25 {
	public $a;
	protected $b;
	private $c;
	var $d;

	function __construct($a, $b, $c, $d) {
		$this->a = $a;
		$this->b = $b;
		$this->c = $c;
		$this->d = $d;
	}

	function __sleep() {
		return array('a', 'b', 'c');
	}

	#       function __wakeup() {
	#               $this->d = $this->a + $this->b + $this->c;
	#       }

	public function getB() { return $this->b; }
	public function getC() { return $this->c; }
}

class Test_025 extends TestCase {
	public function getName() { return "object array"; }

	public static function verifyUnserialized($obj) {
		return count($obj)==3 && get_class($obj[1])=='Obj_25'
		&& $obj[0]->a=='aa' && $obj[0]->getB()=='bb' && $obj[1]->getC()=='gg'
		&& $obj[1]->a=='ee'
		&& $obj[2]->a==1 && !isset($obj[2]->d)
		;
	}

	public function run() {
		$array = array(
		new Obj_25("aa", "bb", "cc", "dd"),
		new Obj_25("ee", "ff", "gg", "hh"),
		new Obj_25(1, 2, 3, 4),
		);

		test('array', $array, false, false, '1403060017064f626a5f32351403110161110261611104002a0062110262621109004f626a5f323500631102636306011a0014030e01110265650e03110266660e051102676706021a0014030e0106010e0306020e050603',
		array('Test_025', 'verifyUnserialized'));
	}
}

// wli-TODO serialization differs, skipped writing test
class Test_026 extends TestCase {
	public function getName() { return "array"; }

	public static function verifyUnserialized($obj) {
		return true;
	}

	function run1() {
		$a = array(
		'a' => array(
		'b' => 'c',
		'd' => 'e'
		),
		);

		$a['f'] = &$a;

		test('array', $a, false, true, '2514021101611402110162110163110164110165110166250100');
		//	2514021101611402110162110163110164110165110166250100
		//	140211016114021101621101631101641101651101662514020e0001010e05250102
	}

	function run2() {
		$a = array("foo" => &$b);
		$b = array(1, 2, $a);

		test('array', $b, false, true, '2514030600060106010602060214011103666f6f250100');
		//	2514030600060106010602060214011103666f6f250100
		//	14011103666f6f251403060006010601060206020100
	}

	public function run() {
		$this->run1();
		$this->run2();
	}
}

class Test_030 extends TestCase {
	public function getName() { return "truncate"; }

	function doTest() {
		$datas = array(
		87817,
		-1,
		array(1,2,3,"testing" => 10, "foo"),
		true,
		false,
		0.187182,
	"dakjdh98389\000",
		null,
		(object)array(1,2,3),
		);

		error_reporting(0);
		foreach ($datas as $data) {
			$str = igbinary_serialize($data);
			$len = strlen($str);

			// truncated
			for ($i = 0; $i < $len - 1; $i++) {
				$v = igbinary_unserialize(substr($str, 0, $i));
				if (is_object($data) && $v !== null && $v == $data) {
					continue;
				} elseif ($v !== null && $v != FALSE && $v !== $data) {
					echo "output at $i:\n";
					var_dump($v);
					echo "vs.\n";
					var_dump($data);
				}
			}
			/*
			 // padded
			 $str .= "98398afa\000y21_ ";
			 $v = igbinary_unserialize($str);
			 if ($v !== $data && !(is_object($data) && $v == $data)) {
			 echo "padded should get original\n";
			 var_dump($v);
			 echo "vs.\n";
			 var_dump($data);
			 }*/

		}
	}

	public function run() {
		ob_start();
		$this->doTest();
		$str = ob_get_clean();
		 
		tassert1($str, "", "truncate loop");
	}
}

require_once 'igb_test_031.php';
require_once 'igb_test_032.php';
require_once 'igb_test_033.php';
require_once 'igb_test_040.php';
require_once 'igb_test_041.php';
require_once 'igb_test_043.php';
require_once 'igb_test_044.php';

printf("igbinary_enabled=%s\n", function_exists('igbinary_serialize'));

$tests = array('Test_001', 'Test_002', 'Test_003', 'Test_004', 'Test_005', 'Test_006', 'Test_007', 'Test_008', 'Test_009', 'Test_010',
	'Test_012', 'Test_013', 'Test_014', 'Test_016', 'Test_017', 'Test_018', 'Test_019', 'Test_020', 'Test_021', 'Test_022', 'Test_023',
	'Test_024', 'Test_025', 'Test_026', 'Test_030', 'Test_031', 'Test_032', 'Test_033', 'Test_040', 'Test_041', 'Test_043', 'Test_044');
$totalCases = count($tests);

foreach($tests as $t) {
	runTest($t, new $t());
}

assert_stats();

