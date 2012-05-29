<?php

class Foo_033 {
	public $parent;
	public $children;

	public function __construct() {
		$this->parent = null;
		$this->children = array();
	}

	public function addChild(Foo_033 $obj) {
		$this->children[] = $obj;
		$obj->setParent($this);
	}

	public function setParent(Foo_033 $obj) {
		$this->parent = $obj;
	}
}

class Test_033 extends TestCase {
	public function getName() { return "loop child"; }

	public static function doTest() {
		$obj1 = new Foo_033();

		for ($i = 0; $i < 10; $i++) {
			$obj = new Foo_033();
			$obj1->addChild($obj);
		}

		$o = igbinary_unserialize(igbinary_serialize($obj1->children));

		foreach ($obj1->children as $k => $v) {
			$obj_v = $v;
			$o_v = $o[$k];

			echo gettype($obj_v), "\t", gettype($o_v), "\n";
		}

	}
	public function run() {
		$expected_033=
			"object	object\n" .
			"object	object\n" .
			"object	object\n" .
			"object	object\n" .
			"object	object\n" .
			"object	object\n" .
			"object	object\n" .
			"object	object\n" .
			"object	object\n" .
			"object	object\n"
			;
			testForResult('exception in serialize interface', array('Test_033', 'doTest'), $expected_033);
	}
}

