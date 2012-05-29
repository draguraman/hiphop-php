<?php

/**
 * Test cases for HipHop ext_igbinary
 * 
 * @author Weijun Li
 * @copyright 2012, Zynga Game Network, Inc.
 *
 */

class Test_044 extends TestCase {
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
		echo "\n";
	}

	public static function doTest() {

		// subnormal number
		Test_044::test('double subnormal', -4.944584125e-314);

		// max subnormal: sign 0, exponent 0, all 1 double
		// http://www.exploringbinary.com/php-hangs-on-numeric-value-2-2250738585072011e-308/
		Test_044::test('double 1 max subnormal', 2.2250738585072010e-308);
		Test_044::test('double 2 max subnormal', 2.2250738585072011e-308);
		Test_044::test('double 3 max subnormal', 2.2250738585072012e-308);
		Test_044::test('double 4 max subnormal', 2.2250738585072013e-308);
		Test_044::test('double 5 max subnormal', 2.2250738585072014e-308);

		// min subnormal number
		Test_044::test('double min subnormal', -4.9406564584124654e-324);

		// big double
		Test_044::test('double big', -1.79769e308);

		// max double, sign 0, exponent all-1 - 1, mantissa all-1
		Test_044::test('double max',  1.7976931348623157e308);

		// small double
		Test_044::test('double small', -2.225e-308);
		// min double, sign 1, exponent all-1 - 1, mantissa all-1
		Test_044::test('double min',  -1.7976931348623157e308);
	}
	public function run() {
		testForResultFile('exception in serialize interface', array('Test_044', 'doTest'), './igb_test_044.res');

	}
}

