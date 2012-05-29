<?php

class Obj_031 implements Serializable {
	private static $count = 1;

	var $a;
	var $b;

	function __construct($a, $b) {
		$this->a = $a;
		$this->b = $b;
	}

	public function serialize() {
		$c = self::$count++;
		echo "call serialize, ", ($this->a ? "throw" : "no throw"),"\n";
		if ($this->a) {
			throw new Exception("exception in serialize $c");
		}
		return pack('NN', $this->a, $this->b);
	}

	public function unserialize($serialized) {
		$tmp = unpack('N*', $serialized);
		$this->__construct($tmp[1], $tmp[2]);
		$c = self::$count++;
		echo "call unserialize, ", ($this->b ? "throw" : "no throw"),"\n";
		if ($this->b) {
			throw new Exception("exception in unserialize $c");
		}
	}
}

class Test_031 extends TestCase {
	public function getName() { return "serialize exception"; }

	public static function doTest() {

		$a = new Obj_031(1, 0);
		$a = new Obj_031(0, 0);
		$b = new Obj_031(0, 0);
		$c = new Obj_031(1, 0);
		$d = new Obj_031(0, 1);

		echo "a, a, c\n";
		try {
			doSerializeUnserialize(array($a, $a, $c));
		} catch (Exception $e) {
			if (version_compare(phpversion(), "5.3.0", ">=")) {
				if ($e->getPrevious()) {
					$e = $e->getPrevious();
				}
			}

			echo $e->getMessage(), "\n";
		}

		echo "b, b, d\n";

		try {
			doSerializeUnserialize(array($b, $b, $d));
		} catch (Exception $e) {
			if (version_compare(phpversion(), "5.3.0", ">=")) {
				if ($e->getPrevious()) {
					$e = $e->getPrevious();
				}
			}

			echo $e->getMessage(), "\n";
		}

	}
	public function run() {
		$expected_031=
			"a, a, c\n" .
			"call serialize, no throw\n" .
			"call serialize, throw\n" .
			"exception in serialize 2\n" .
			"b, b, d\n" .
			"call serialize, no throw\n" .
			"call serialize, no throw\n" .
			"call unserialize, no throw\n" .
			"call unserialize, throw\n" .
			"exception in unserialize 6\n"
			;
		testForResult('exception in serialize interface', array('Test_031', 'doTest'), $expected_031);

	}
}

