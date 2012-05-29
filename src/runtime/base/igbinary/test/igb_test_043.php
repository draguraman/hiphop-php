<?php

/**
 * Test cases for HipHop ext_igbinary
 * 
 * @author Weijun Li
 * @copyright 2012, Zynga Game Network, Inc.
 * 
 */

class Foo_043 {
}

class Bar_043 {
}

class Test_043 extends TestCase {
	public function getName() { return "class array"; }

	public static function doTest() {
		$expected_array = array();
		for ($i = 0; $i < 10; $i++) {
			$expected_array['foo_' . $i] = new Foo_043;
			$expected_array['bar_' . $i] = new Bar_043;
		}

		$actual_array = igbinary_unserialize(igbinary_serialize($expected_array));

		$error = 'OK';

		foreach ($expected_array as $key => $object) {
			if (!isset($actual_array[$key])) {
				$error = 'ERROR';
				echo "Key $key is missing from result.\n";
				echo "Expected key/value:\n";
				var_dump($key, $object);
				var_dump($object);

				break;
			}

			if (!is_object($actual_array[$key]) ||
			get_class($object) !== get_class($actual_array[$key])) {
				$error = 'ERROR';
				echo "Array mismatch on $key\n";
				echo "Expected key/value:\n";
				var_dump($key, $object);
				echo "Actual key/value:\n";
				var_dump($key, $actual_array[$key]);

				break;
			}

		}

		echo $error, "\n";

	}
	public function run() {
		$expected = "OK\n";
		testForResult('array', array('Test_043', 'doTest'), $expected);

	}
}

