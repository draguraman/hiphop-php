<?php

/**
 * Test cases for HipHop ext_igbinary
 * 
 * @author Weijun Li
 * @copyright 2012, Zynga Game Network, Inc.
 *
 */

class Test_041 extends TestCase {
	public function getName() { return "serialize exception"; }

	static function test($type, $variable) {
		$serialized = igbinary_serialize($variable);
		$unserialized = igbinary_unserialize($serialized);

		echo $type, ":\n";
		var_dump($variable);
		var_dump($unserialized);

		echo "   6         5         4         3         2         1          \n";
		echo "3210987654321098765432109876543210987654321098765432109876543210\n";
		echo str2bin(substr($serialized, 5, 8)), "\n";
	}

	public static function doTest1() {
		// exponent all-1, non zero mantissa
		Test_041::test('double NaN', NAN);
	}

	public static function doTest2() {
		// sign 0, exp all-1, zero mantissa
		Test_041::test('double Inf', INF);
	}

	public static function doTest3() {
		// sign 1, exp all-1, zero mantissa
		Test_041::test('double -Inf', -INF);
	}

	public static function doTest4() {
		// sign 0, all-0
		Test_041::test('double 0.0', 0.0);
	}

	public static function doTest5() {
		/* TODO: causes HipHop compilation error.
		error: 's_svd780de548' was not declared in this scope\n/opt/hiphop/build/include/boost/system/error_code.hpp
		 */
		// sign 1, all-0
		//Test_041::test('double -0.0', -1 * 0.0);
	}

	public function run() {
		testForResult('double NaN', array('Test_041', 'doTest1'),
		"double NaN:\n".
		"float(NAN)\n".
		"float(NAN)\n".
		"   6         5         4         3         2         1          \n".
		"3210987654321098765432109876543210987654321098765432109876543210\n".
		"0111111111111000000000000000000000000000000000000000000000000000\n"
		);

		testForResult('double Inf', array('Test_041', 'doTest2'),
		"double Inf:\n".
		"float(INF)\n".
		"float(INF)\n".
		"   6         5         4         3         2         1          \n".
		"3210987654321098765432109876543210987654321098765432109876543210\n".
		"0111111111110000000000000000000000000000000000000000000000000000\n"
		);

		testForResult('double -Inf', array('Test_041', 'doTest3'),
		"double -Inf:\n".
		"float(-INF)\n".
		"float(-INF)\n".
		"   6         5         4         3         2         1          \n".
		"3210987654321098765432109876543210987654321098765432109876543210\n".
		"1111111111110000000000000000000000000000000000000000000000000000\n"
		);

		testForResult('double 0.0', array('Test_041', 'doTest4'),
		"double 0.0:\n".
		"float(0)\n".
		"float(0)\n".
		"   6         5         4         3         2         1          \n".
		"3210987654321098765432109876543210987654321098765432109876543210\n".
		"0000000000000000000000000000000000000000000000000000000000000000\n"
		);
	}
}

