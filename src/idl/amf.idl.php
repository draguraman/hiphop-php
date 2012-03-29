<?php
/**
 * Automatically generated by running "php schema.php apc".
 *
 * You may modify the file, but re-running schema.php against this file will
 * standardize the format without losing your schema changes. It does lose
 * any changes that are not part of schema. Use "note" field to comment on
 * schema itself, and "note" fields are not used in any code generation but
 * only staying within this file.
 */
///////////////////////////////////////////////////////////////////////////////
// Preamble: C++ code inserted at beginning of ext_{name}.h

DefinePreamble(<<<CPP

CPP
);

///////////////////////////////////////////////////////////////////////////////
// Constants
//
// array (
//   'name' => name of the constant
//   'type' => type of the constant
//   'note' => additional note about this constant's schema
// )


///////////////////////////////////////////////////////////////////////////////
// Functions
//
// array (
//   'name'   => name of the function
//   'desc'   => description of the function's purpose
//   'flags'  => attributes of the function, see base.php for possible values
//   'opt'    => optimization callback function's name for compiler
//   'note'   => additional note about this function's schema
//   'return' =>
//      array (
//        'type'  => return type, use Reference for ref return
//        'desc'  => description of the return value
//      )
//   'args'   => arguments
//      array (
//        'name'  => name of the argument
//        'type'  => type of the argument, use Reference for output parameter
//        'value' => default value of the argument
//        'desc'  => description of the argument
//      )
// )

DefineFunction(
  array(
    'name'   => "amf_encode",
    'desc'   => "encode object into amf string",
    'flags'  =>  HasDocComment | AllowIntercept,
    'return' => array(
      'type'   => String,
      'desc'   => "Returns the string of encoded object.",
    ),
    'args'   => array(
      array(
        'name'   => "var",
        'type'   => Variant | Reference,
        'desc'   => "The variable to encode",
      ),
      array(
        'name'   => "flag",
        'type'   => Variant | Reference,
        'desc'   => "The flag",
	'value'  => "null",
      ),
      array(
        'name'   => "callback",
        'type'   => Variant | Reference,
        'desc'   => "call back",
	'value'  => "null",
      ),
      array(
        'name'   => "output",
        'type'   => Variant| Reference,
        'desc'   => "output",
	'value'  => "null",
      ),
    ),
    'taint_observer' => array(
      'set_mask'   => "TAINT_BIT_NONE",
      'clear_mask' => "TAINT_BIT_NONE",
    ),
  ));

DefineFunction(
  array(
    'name'   => "amf_decode",
    'desc'   => "decode string to hiphop object.",
    'flags'  =>  HasDocComment | AllowIntercept,
    'return' => array(
      'type'   => Variant,
      'desc'   => "The stored variable or array of variables on success; FALSE on failure",
    ),
    'args'   => array(
      array(
        'name'   => "var",
        'type'   => String,
        'desc'   => "String for encoded obj",
      ),
      array(
        'name'   => "flag",
        'type'   => Variant | Reference,
        'desc'   => "The flag",
        'value'  => "null",
      ),
      array(
        'name'   => "offset",
        'type'   => Variant| Reference,
        'desc'   => "offset",
        'value'  => "null",
      array(
        'name'   => "callback",
        'type'   => Variant | Reference,
        'desc'   => "call back",
        'value'  => "null",
      ),
      ),

    ),
    'taint_observer' => array(
      'set_mask'   => "TAINT_BIT_NONE",
      'clear_mask' => "TAINT_BIT_NONE",
    ),
  ));

///////////////////////////////////////////////////////////////////////////////
// Classes
//
// BeginClass
// array (
//   'name'   => name of the class
//   'desc'   => description of the class's purpose
//   'flags'  => attributes of the class, see base.php for possible values
//   'note'   => additional note about this class's schema
//   'parent' => parent class name, if any
//   'ifaces' => array of interfaces tihs class implements
//   'bases'  => extra internal and special base classes this class requires
//   'footer' => extra C++ inserted at end of class declaration
// )
//
// DefineConstant(..)
// DefineConstant(..)
// ...
// DefineFunction(..)
// DefineFunction(..)
// ...
// DefineProperty
// DefineProperty
//
// array (
//   'name'  => name of the property
//   'type'  => type of the property
//   'flags' => attributes of the property
//   'desc'  => description of the property
//   'note'  => additional note about this property's schema
// )
//
// EndClass()

