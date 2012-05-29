<?php

class Obj_032 {
	private static $count = 0;
	var $a;
	var $b;

	function __construct($a, $b) {
		$this->a = $a;
		$this->b = $b;
	}

	function __sleep() {
		$c = self::$count++;
		if ($this->a) {
			throw new Exception("exception in __sleep $c");
		}
		return array('a', 'b');
	}

	function __wakeup() {
		$c = self::$count++;
		if ($this->b) {
			throw new Exception("exception in __wakeup $c");
		}
		$this->b = $this->a * 3;
	}
}

class Test_032 extends TestCase {
	public function getName() { return "serialize __sleep exception"; }

	public static function doTest() {
		$a = new Obj_032(1, 0);
		$b = new Obj_032(0, 1);
		$c = new Obj_032(0, 0);

		try {
			doSerializeUnserialize($a);
		} catch (Exception $e) {
			echo $e->getMessage(), "\n";
		}

		try {
			doSerializeUnserialize($b);
		} catch (Exception $e) {
			echo $e->getMessage(), "\n";
		}

		try {
			doSerializeUnserialize($c);
		} catch (Exception $e) {
			echo $e->getMessage(), "\n";
		}

	}
	public function run() {
		$expected_032=
			"exception in __sleep 0\n" .
			"exception in __wakeup 2\n"
			;
			testForResult('exception in __sleep', array('Test_032', 'doTest'), $expected_032);

	}
}

