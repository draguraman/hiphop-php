/* A Bison parser, made by GNU Bison 2.4.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006,
   2009, 2010 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 1

/* Substitute the variable and function names.  */
#define yyparse         Compilerparse
#define yylex           Compilerlex
#define yyerror         Compilererror
#define yylval          Compilerlval
#define yychar          Compilerchar
#define yydebug         Compilerdebug
#define yynerrs         Compilernerrs
#define yylloc          Compilerlloc

/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "../../../src/util/parser/hphp.y"

#include "parser.h"
#include <util/util.h>
#include <util/logger.h>

// macros for bison
#define YYSTYPE HPHP::HPHP_PARSER_NS::Token
#define YYSTYPE_IS_TRIVIAL 1
#define YYLTYPE HPHP::Location
#define YYLTYPE_IS_TRIVIAL 1
#define YYERROR_VERBOSE
#define YYINITDEPTH 500
#define YYLEX_PARAM _p

#ifdef yyerror
#undef yyerror
#endif
#define yyerror(loc,p,msg) p->fatal(loc,msg)

#ifdef YYLLOC_DEFAULT
# undef YYLLOC_DEFAULT
#endif
#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#define YYLLOC_DEFAULT(Current, Rhs, N)                                 \
  do                                                                    \
    if (YYID (N)) {                                                     \
      (Current).first(YYRHSLOC (Rhs, 1));                               \
      (Current).last (YYRHSLOC (Rhs, N));                               \
    } else {                                                            \
      (Current).line0 = (Current).line1 = YYRHSLOC (Rhs, 0).line1;      \
      (Current).char0 = (Current).char1 = YYRHSLOC (Rhs, 0).char1;      \
    }                                                                   \
  while (YYID (0));                                                     \
  _p->setRuleLocation(&Current);

#define YYCOPY(To, From, Count)                  \
  do {                                           \
    YYSIZE_T yyi;                                \
    for (yyi = 0; yyi < (Count); yyi++) {        \
      (To)[yyi] = (From)[yyi];                   \
    }                                            \
    if (From != From ## a) {                     \
      YYSTACK_FREE (From);                       \
    }                                            \
  }                                              \
  while (YYID (0))

#define YYCOPY_RESET(To, From, Count)           \
  do                                            \
    {                                           \
      YYSIZE_T yyi;                             \
      for (yyi = 0; yyi < (Count); yyi++) {     \
        (To)[yyi] = (From)[yyi];                \
        (From)[yyi].reset();                    \
      }                                         \
      if (From != From ## a) {                  \
        YYSTACK_FREE (From);                    \
      }                                         \
    }                                           \
  while (YYID (0))

#define YYTOKEN_RESET(From, Count)              \
  do                                            \
    {                                           \
      YYSIZE_T yyi;                             \
      for (yyi = 0; yyi < (Count); yyi++) {     \
        (From)[yyi].reset();                    \
      }                                         \
      if (From != From ## a) {                  \
        YYSTACK_FREE (From);                    \
      }                                         \
    }                                           \
  while (YYID (0))

# define YYSTACK_RELOCATE_RESET(Stack_alloc, Stack)                     \
  do                                                                    \
    {                                                                   \
      YYSIZE_T yynewbytes;                                              \
      YYCOPY_RESET (&yyptr->Stack_alloc, Stack, yysize);                \
      Stack = &yyptr->Stack_alloc;                                      \
      yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
      yyptr += yynewbytes / sizeof (*yyptr);                            \
    }                                                                   \
  while (YYID (0))

#define YYSTACK_CLEANUP                         \
  YYTOKEN_RESET (yyvs, yystacksize);            \
  if (yyvs != yyvsa) {                          \
    YYSTACK_FREE (yyvs);                        \
  }                                             \
  if (yyls != yylsa) {                          \
    YYSTACK_FREE (yyls);                        \
  }                                             \


// macros for rules
#define BEXP(e...) _p->onBinaryOpExp(e);
#define UEXP(e...) _p->onUnaryOpExp(e);

using namespace HPHP::HPHP_PARSER_NS;

///////////////////////////////////////////////////////////////////////////////
// helpers

static void no_gap(Parser *_p) {
  if (_p->scanner().hasGap()) {
    HPHP_PARSER_ERROR("XHP: bad spacing: %s", _p->getMessage(true).c_str());
  }
}

static void scalar_num(Parser *_p, Token &out, const char *num) {
  Token t;
  t.setText(num);
  _p->onScalar(out, T_LNUMBER, t);
}

static void scalar_num(Parser *_p, Token &out, int num) {
  Token t;
  t.setText(boost::lexical_cast<std::string>(num));
  _p->onScalar(out, T_LNUMBER, t);
}

static void scalar_null(Parser *_p, Token &out) {
  Token tnull; tnull.setText("null");
  _p->onConstantValue(out, tnull);
}

///////////////////////////////////////////////////////////////////////////////
// converting constant declartion to "define(name, value);"

static void on_constant(Parser *_p, Token &out, Token *stmts,
                        Token &name, Token &value) {
  Token sname;   _p->onScalar(sname, T_CONSTANT_ENCAPSED_STRING, name);

  Token fname;   fname.setText("define");
  Token params1; _p->onCallParam(params1, NULL, sname, 0);
  Token params2; _p->onCallParam(params2, &params1, value, 0);
  Token call;    _p->onCall(call, 0, fname, params2, 0);
  Token scall;   _p->onExpStatement(scall, call);

  Token stmts0;
  if (!stmts) {
    _p->onStatementListStart(stmts0);
    stmts = &stmts0;
  }
  _p->addStatement(out, *stmts, scall);
}

///////////////////////////////////////////////////////////////////////////////
// continuation transformations

static void on_yield_assign(Parser *_p, Token &out, Token &var, Token *expr) {
  Token yield;    _p->onYield(yield, expr, true);
  Token rhs;
  {
    Token name;   name.setText(CONTINUATION_OBJECT_NAME);
    Token var;    _p->onSynthesizedVariable(var, name);
    Token pn;     pn.setText("receive");
    Token pname;  _p->onName(pname, pn, Parser::VarName);
                  _p->pushObject(var); _p->appendProperty(pname);
    Token empty;  empty = 1; _p->appendMethodParams(empty);
                  _p->popObject(rhs);
  }
  Token assign;   _p->onAssign(assign, var, rhs, 0);
  Token stmt;     _p->onExpStatement(stmt, assign);

  Token stmts0;   _p->onStatementListStart(stmts0);
  Token stmts1;   _p->addStatement(stmts1, stmts0, yield);
  Token stmts2;   _p->addStatement(stmts2, stmts1, stmt);

  _p->finishStatement(out, stmts2); out = 1;
}

static void on_yield_list_assign(Parser *_p, Token &out, Token &var,
                                 Token *expr) {
  Token yield;    _p->onYield(yield, expr, true);
  Token rhs;
  {
    Token name;   name.setText(CONTINUATION_OBJECT_NAME);
    Token var;    _p->onSynthesizedVariable(var, name);
    Token pn;     pn.setText("receive");
    Token pname;  _p->onName(pname, pn, Parser::VarName);
                  _p->pushObject(var); _p->appendProperty(pname);
    Token empty;  empty = 1; _p->appendMethodParams(empty);
                  _p->popObject(rhs);
  }
  Token assign;   _p->onListAssignment(assign, var, &rhs);
  Token stmt;     _p->onExpStatement(stmt, assign);

  Token stmts0;   _p->onStatementListStart(stmts0);
  Token stmts1;   _p->addStatement(stmts1, stmts0, yield);
  Token stmts2;   _p->addStatement(stmts2, stmts1, stmt);

  _p->finishStatement(out, stmts2); out = 1;
}

void prepare_generator(Parser *_p, Token &stmt, Token &params, int count) {
  // 1. add prologue and epilogue to original body and store it back to "stmt"
  {
    Token scall;
    {
      // hphp_unpack_continuation(v___cont__)
      Token name;    name.setText(CONTINUATION_OBJECT_NAME);
      Token var;     _p->onSynthesizedVariable(var, name);
      Token param1;  _p->onCallParam(param1, NULL, var, false);

      Token cname;   cname.setText("hphp_unpack_continuation");
      Token call;    _p->onCall(call, false, cname, param1, NULL);
      _p->onExpStatement(scall, call);
    }
    Token sswitch;
    {
      Token name;    name.setText(CONTINUATION_OBJECT_NAME);
      Token var;     _p->onSynthesizedVariable(var, name);
      Token pn;      pn.setText("getLabel");
      Token pname;   _p->onName(pname, pn, Parser::VarName);
      Token mcall;   _p->pushObject(var); _p->appendProperty(pname);
      Token empty;   empty = 1; _p->appendMethodParams(empty);
                     _p->popObject(mcall);

      _p->pushLabelScope();
      {
        Token cases;
        for (int i = count; i > 0; i--) {
          std::string si = boost::lexical_cast<std::string>(i);

          Token label;   label.setText(YIELD_LABEL_PREFIX + si);
          Token sgoto;   _p->onGoto(sgoto, label, false);
                         _p->addGoto(label.text(), _p->getLocation(), &sgoto);

          Token stmts0;  _p->onStatementListStart(stmts0);
          Token stmts1;  _p->addStatement(stmts1, stmts0, sgoto);
          Token stmts;   _p->finishStatement(stmts, stmts1); stmts = 1;

          Token snum;    snum.setText(si);
          Token num;     _p->onScalar(num, T_LNUMBER, snum);
          Token scase;   _p->onCase(scase, cases, &num, stmts);
          cases = scase;
        }
        _p->onSwitch(sswitch, mcall, cases);
      }
      _p->popLabelScope();
    }
    Token sdone;
    {
      Token name;    name.setText(CONTINUATION_OBJECT_NAME);
      Token var;     _p->onSynthesizedVariable(var, name);
      Token pn;      pn.setText("done");
      Token pname;   _p->onName(pname, pn, Parser::VarName);
      Token mcall;   _p->pushObject(var); _p->appendProperty(pname);
      Token empty;   empty = 1; _p->appendMethodParams(empty);
                     _p->popObject(mcall);
      _p->onExpStatement(sdone, mcall);
    }
    {
      Token stmts0;  _p->onStatementListStart(stmts0);
      Token stmts1;  _p->addStatement(stmts1, stmts0, scall);
      Token stmts2;  _p->addStatement(stmts2, stmts1, sswitch);
      Token stmts3;  _p->addStatement(stmts3, stmts2, stmt);
      Token stmts4;  _p->addStatement(stmts4, stmts3, sdone);

      stmt.reset();
      _p->finishStatement(stmt, stmts4); stmt = 1;
    }
  }

  // 2. prepare a single continuation parameter list and store it in "params"
  {
    Token type;    type.setText("Continuation");
    Token var;     var.setText(CONTINUATION_OBJECT_NAME);
    params.reset();
    _p->onParam(params, NULL, type, var, false, NULL);
  }
}

// create a generator function with original name and parameters
void create_generator(Parser *_p, Token &out, Token &params,
                      Token &name, const std::string &closureName,
                      const char *clsname, Token *modifiers, bool getArgs,
                      Token &origGenFunc) {
  _p->pushFuncLocation();
  if (clsname) {
    _p->onMethodStart(name, *modifiers);
  } else {
    _p->onFunctionStart(name);
  }

  Token scont;
  {
    Token cn;      cn.setText(clsname ? clsname : "");
    Token cname;   _p->onScalar(cname, T_CONSTANT_ENCAPSED_STRING, cn);

    Token fn;      fn.setText(closureName);
    Token fname;   _p->onScalar(fname, T_CONSTANT_ENCAPSED_STRING, fn);

    Token ofn;     ofn.setText(clsname ? "__METHOD__" : "__FUNCTION__");
    Token oname;   _p->onScalar(oname, clsname ? T_METHOD_C : T_FUNC_C, ofn);

    Token param1;  _p->onCallParam(param1, NULL, cname, false);
                   _p->onCallParam(param1, &param1, fname, false);
                   _p->onCallParam(param1, &param1, oname, false);

    if (getArgs) {
      Token cname;   cname.setText("func_get_args");
      Token empty;
      Token call;    _p->onCall(call, false, cname, empty, NULL);
                     _p->onCallParam(param1, &param1, call, false);
    }

    Token cname0;  cname0.setText("hphp_create_continuation");
    Token call;    _p->onCall(call, false, cname0, param1, NULL);
    Token ret;     _p->onReturn(ret, &call);

    Token stmts0;  _p->onStatementListStart(stmts0);
    Token stmts1;  _p->addStatement(stmts1, stmts0, ret);
    _p->finishStatement(scont, stmts1); scont = 1;
  }

  Token ret, ref;
  ret.setText("Continuation");
  ret.setCheck();
  if (clsname) {
    Token closure;
    _p->onMethod(closure, *modifiers, ret, ref, name, params, scont);
    origGenFunc = closure;

    Token stmts0;  _p->onStatementListStart(stmts0);
    Token stmts1;  _p->addStatement(stmts1, stmts0, closure);
    Token stmts2;  _p->addStatement(stmts2, stmts1, out);
    _p->finishStatement(out, stmts2); out = 1;
  } else {
    out.reset();
    _p->onFunction(out, ret, ref, name, params, scont);
    origGenFunc = out;
  }
}

void transform_yield(Parser *_p, Token &stmts, int index,
                     Token *expr, bool assign) {
  Token update;
  {
    // hphp_pack_contination(v___cont__, label, value)

    Token name;    name.setText(CONTINUATION_OBJECT_NAME);
    Token var;     _p->onSynthesizedVariable(var, name);
    Token param1;  _p->onCallParam(param1, NULL, var, false);

    Token snum;    snum.setText(boost::lexical_cast<std::string>(index));
    Token num;     _p->onScalar(num, T_LNUMBER, snum);
                   _p->onCallParam(param1, &param1, num, false);

    if (expr) {
      _p->onCallParam(param1, &param1, *expr, false);
    } else {
      Token tnull; scalar_null(_p, tnull);
      _p->onCallParam(param1, &param1, tnull, false);
    }

    Token cname;   cname.setText("hphp_pack_continuation");
    Token call;    _p->onCall(call, false, cname, param1, NULL);
    _p->onExpStatement(update, call);
  }

  Token lname;   lname.setText(YIELD_LABEL_PREFIX +
                               boost::lexical_cast<std::string>(index));
  Token label;   _p->onLabel(label, lname);
                 _p->addLabel(lname.text(), _p->getLocation(), &label);

  Token stmts0;  _p->onStatementListStart(stmts0);

  if (!expr) {
    Token name;    name.setText(CONTINUATION_OBJECT_NAME);
    Token var;     _p->onSynthesizedVariable(var, name);
    Token pn;      pn.setText("done");
    Token pname;   _p->onName(pname, pn, Parser::VarName);
    Token mcall;   _p->pushObject(var); _p->appendProperty(pname);
    Token empty;   empty = 1; _p->appendMethodParams(empty);
                   _p->popObject(mcall);
    Token sdone;   _p->onExpStatement(sdone, mcall);

    Token tmp;     _p->addStatement(tmp, stmts0, sdone);
    stmts0 = tmp;
  }

  Token ret;     _p->onReturn(ret, NULL, false);
  Token stmts1;  _p->addStatement(stmts1, stmts0, update);
  Token stmts2;  _p->addStatement(stmts2, stmts1, ret);
  Token stmts3;  _p->addStatement(stmts3, stmts2, label);

  if (assign) {
    _p->finishStatement(stmts, stmts3); stmts = 1;
  } else {
    Token raised;
    {
      Token name;   name.setText(CONTINUATION_OBJECT_NAME);
      Token var;    _p->onSynthesizedVariable(var, name);
      Token pn;     pn.setText("raised");
      Token pname;  _p->onName(pname, pn, Parser::VarName);
      _p->pushObject(var); _p->appendProperty(pname);
      Token empty;  empty = 1; _p->appendMethodParams(empty);
      _p->popObject(raised);
    }
    Token stmt;     _p->onExpStatement(stmt, raised);

    Token stmts4;   _p->addStatement(stmts4, stmts3, stmt);
    _p->finishStatement(stmts, stmts4); stmts = 1;
  }

}

// convert a foreach (by ref or not) to a normal for statement with
// an iterator object.
void transform_foreach(Parser *_p, Token &out, Token &arr, Token &name,
                       Token &value, Token &stmt, int count,
                       bool hasValue, bool byRef) {
  out.reset();

  std::string loopvar = FOREACH_VAR_PREFIX;
  loopvar += boost::lexical_cast<std::string>(count);

  Token init;
  {
    Token cname;    cname.setText(byRef ?
                                  "hphp_get_mutable_iterator" :
                                  "hphp_get_iterator");
    Token param1;   _p->onCallParam(param1, NULL, arr, 0);
    Token call;     _p->onCall(call, 0, cname, param1, NULL);
    Token lname;    lname.setText(loopvar);
    Token var;      _p->onSynthesizedVariable(var, lname);
    Token assign;   _p->onAssign(assign, var, call, false);
    _p->onExprListElem(init, NULL, assign);
  }

  Token cond;
  {
    Token lname;    lname.setText(loopvar);
    Token var;      _p->onSynthesizedVariable(var, lname);
    Token pn;       pn.setText("valid");
    Token pname;    _p->onName(pname, pn, Parser::VarName);
    Token empty;    empty = 1;
    Token valid;    _p->pushObject(var); _p->appendProperty(pname);
                    _p->appendMethodParams(empty); _p->popObject(valid);
    _p->onExprListElem(cond, NULL, valid);
  }

  Token step;
  {
    Token lname;    lname.setText(loopvar);
    Token var;      _p->onSynthesizedVariable(var, lname);
    Token pn;       pn.setText("next");
    Token pname;    _p->onName(pname, pn, Parser::VarName);
    Token empty;    empty = 1;
    Token next;     _p->pushObject(var); _p->appendProperty(pname);
                    _p->appendMethodParams(empty); _p->popObject(next);
    _p->onExprListElem(step, NULL, next);
  }

  {
    Token stmts0;   _p->onStatementListStart(stmts0);

    if (hasValue) {
      Token skset;
      {
        Token lname;  lname.setText(loopvar);
        Token var;    _p->onSynthesizedVariable(var, lname);
        Token pn;     pn->setText("key");
        Token pname;  _p->onName(pname, pn, Parser::VarName);
        Token empty;  empty = 1;
        Token call;   _p->pushObject(var); _p->appendProperty(pname);
                      _p->appendMethodParams(empty); _p->popObject(call);
        Token kset;   _p->onAssign(kset, name, call, false);
        _p->onExpStatement(skset, kset);
      }
      Token stmts1; _p->addStatement(stmts1, stmts0, skset);

      Token svset;
      {
        Token lname;  lname.setText(loopvar);
        Token var;    _p->onSynthesizedVariable(var, lname);
        Token pn;     pn.setText(byRef ? "currentRef" : "current");
        Token pname;  _p->onName(pname, pn, Parser::VarName);
        Token empty;  empty = 1;
        Token call;   _p->pushObject(var); _p->appendProperty(pname);
                      _p->appendMethodParams(empty); _p->popObject(call);
        Token vset;   _p->onAssign(vset, value, call, byRef);
        _p->onExpStatement(svset, vset);
      }
      Token stmts2; _p->addStatement(stmts2, stmts1, svset);

      Token stmts3; _p->addStatement(stmts3, stmts2, stmt);
      stmt.reset();
      _p->finishStatement(stmt, stmts3); stmt = 1;
    } else {
      Token svset;
      {
        Token lname;  lname.setText(loopvar);
        Token var;    _p->onSynthesizedVariable(var, lname);
        Token pn;     pn.setText(byRef ? "currentRef" : "current");
        Token pname;  _p->onName(pname, pn, Parser::VarName);
        Token empty;  empty = 1;
        Token call;   _p->pushObject(var); _p->appendProperty(pname);
                      _p->appendMethodParams(empty); _p->popObject(call);
        Token vset;   _p->onAssign(vset, name, call, byRef);
        _p->onExpStatement(svset, vset);
      }
      Token stmts1; _p->addStatement(stmts1, stmts0, svset);

      Token stmts2; _p->addStatement(stmts2, stmts1, stmt);
      stmt.reset();
      _p->finishStatement(stmt, stmts2); stmt = 1;
    }
  }

  _p->onFor(out, init, cond, step, stmt);
}

///////////////////////////////////////////////////////////////////////////////

/**
 * XHP functions: They are defined here, so different parsers don't have to
 * handle XHP rules at all.
 */

static void xhp_tag(Parser *_p, Token &out, Token &label, Token &body) {
  if (!_p->enableXHP()) {
    HPHP_PARSER_ERROR("XHP: not enabled: %s", _p->getMessage(true).c_str());
  }

  if (!body.text().empty() && body.text() != label.text()) {
    HPHP_PARSER_ERROR("XHP: mismatched tag: '%s' not the same as '%s': %s",
                      body.text().c_str(), label.text().c_str(),
                      _p->getMessage(true).c_str());
  }

  label.xhpLabel();
  Token name; _p->onName(name, label, Parser::StringName);
  _p->onNewObject(out, name, body);
}

static void xhp_attribute(Parser *_p, Token &out, Token &type, Token &label,
                          Token &def, Token &req) {
  Token num;  scalar_num(_p, num, type.num());
  Token arr1; _p->onArrayPair(arr1, 0, 0, num, 0);

  Token arr2;
  switch (type.num()) {
    case 5: /* class */ {
      Token cls; _p->onScalar(cls, T_CONSTANT_ENCAPSED_STRING, type);
      _p->onArrayPair(arr2, &arr1, 0, cls, 0);
      break;
    }
    case 7: /* enum */ {
      Token arr;   _p->onArray(arr, type);
      _p->onArrayPair(arr2, &arr1, 0, arr, 0);
      break;
    }
    default: {
      Token tnull; scalar_null(_p, tnull);
      _p->onArrayPair(arr2, &arr1, 0, tnull, 0);
      break;
    }
  }

  Token arr3; _p->onArrayPair(arr3, &arr2, 0, def, 0);
  Token arr4; _p->onArrayPair(arr4, &arr3, 0, req, 0);
  _p->onArray(out, arr4);
  out.setText(label);
}

static void xhp_attribute_list(Parser *_p, Token &out, Token *list,
                               Token &decl) {
  if (decl.num() == 0) {
    decl.xhpLabel();
    if (list) {
      out = *list;
      out.setText(list->text() + ":" + decl.text()); // avoiding vector<string>
    } else {
      out.setText(decl);
    }
  } else {
    Token name; _p->onScalar(name, T_CONSTANT_ENCAPSED_STRING, decl);
    _p->onArrayPair(out, list, &name, decl, 0);
    if (list) {
      out.setText(list->text());
    } else {
      out.setText("");
    }
  }
}

static void xhp_attribute_stmt(Parser *_p, Token &out, Token &attributes) {
  if (!_p->enableXHP()) {
    HPHP_PARSER_ERROR("XHP: not enabled: %s", _p->getMessage(true).c_str());
  }

  Token modifiers;
  Token fname; fname.setText("__xhpAttributeDeclaration");
  {
    Token m;
    Token m1; m1.setNum(T_PROTECTED); _p->onMemberModifier(m, NULL, m1);
    Token m2; m2.setNum(T_STATIC);    _p->onMemberModifier(modifiers, &m, m2);
  }
  _p->pushFuncLocation();
  _p->onMethodStart(fname, modifiers);

  std::vector<std::string> classes;
  HPHP::Util::split(':', attributes.text().c_str(), classes, true);
  Token arrAttributes; _p->onArray(arrAttributes, attributes);

  Token dummy;

  Token stmts0;
  {
    _p->onStatementListStart(stmts0);
  }
  Token stmts1;
  {
    // static $_ = -1;
    Token one;     scalar_num(_p, one, "1");
    Token mone;    UEXP(mone, one, '-', 1);
    Token var;     var.set(T_VARIABLE, "_");
    Token decl;    _p->onStaticVariable(decl, 0, var, &mone);
    Token sdecl;   _p->onStatic(sdecl, decl);
    _p->addStatement(stmts1, stmts0, sdecl);
  }
  Token stmts2;
  {
    // if ($_ === -1) {
    //   $_ = array_merge(parent::__xhpAttributeDeclaration(),
    //                    attributes);
    // }
    Token parent;  parent.set(T_STRING, "parent");
    Token cls;     _p->onName(cls, parent, Parser::StringName);
    Token fname;   fname.setText("__xhpAttributeDeclaration");
    Token param1;  _p->onCall(param1, 0, fname, dummy, &cls);
    Token params1; _p->onCallParam(params1, NULL, param1, 0);

    for (unsigned int i = 0; i < classes.size(); i++) {
      Token parent;  parent.set(T_STRING, classes[i]);
      Token cls;     _p->onName(cls, parent, Parser::StringName);
      Token fname;   fname.setText("__xhpAttributeDeclaration");
      Token param;   _p->onCall(param, 0, fname, dummy, &cls);

      Token params; _p->onCallParam(params, &params1, param, 0);
      params1 = params;
    }

    Token params2; _p->onCallParam(params2, &params1, arrAttributes, 0);

    Token name;    name.set(T_STRING, "array_merge");
    Token call;    _p->onCall(call, 0, name, params2, NULL);
    Token tvar;    tvar.set(T_VARIABLE, "_");
    Token var;     _p->onSimpleVariable(var, tvar);
    Token assign;  _p->onAssign(assign, var, call, 0);
    Token exp;     _p->onExpStatement(exp, assign);
    Token block;   _p->onBlock(block, exp);

    Token tvar2;   tvar2.set(T_VARIABLE, "_");
    Token var2;    _p->onSimpleVariable(var2, tvar2);
    Token one;     scalar_num(_p, one, "1");
    Token mone;    UEXP(mone, one, '-', 1);
    Token cond;    BEXP(cond, var2, mone, T_IS_IDENTICAL);
    Token dummy1, dummy2;
    Token sif;     _p->onIf(sif, cond, block, dummy1, dummy2);
    _p->addStatement(stmts2, stmts1, sif);
  }
  Token stmts3;
  {
    // return $_;
    Token tvar;    tvar.set(T_VARIABLE, "_");
    Token var;     _p->onSimpleVariable(var, tvar);
    Token ret;     _p->onReturn(ret, &var);
    _p->addStatement(stmts3, stmts2, ret);
  }
  Token stmt;
  {
    _p->finishStatement(stmt, stmts3);
    stmt = 1;
  }
  {
    Token params, ret, ref; ref = 1;
    _p->onMethod(out, modifiers, ret, ref, fname, params, stmt, false);
  }
}

static void xhp_collect_attributes(Parser *_p, Token &out, Token &stmts) {
  Token *attr = _p->xhpGetAttributes();
  if (attr) {
    Token stmt;
    xhp_attribute_stmt(_p, stmt, *attr);
    _p->onClassStatement(out, stmts, stmt);
  } else {
    out = stmts;
  }
}

static void xhp_category_stmt(Parser *_p, Token &out, Token &categories) {
  if (!_p->enableXHP()) {
    HPHP_PARSER_ERROR("XHP: not enabled: %s", _p->getMessage(true).c_str());
  }

  Token fname;     fname.setText("__xhpCategoryDeclaration");
  Token m1;        m1.setNum(T_PROTECTED);
  Token modifiers; _p->onMemberModifier(modifiers, 0, m1);
  _p->pushFuncLocation();
  _p->onMethodStart(fname, modifiers);

  Token stmts0;
  {
    _p->onStatementListStart(stmts0);
  }
  Token stmts1;
  {
    // static $_ = categories;
    Token arr;     _p->onArray(arr, categories);
    Token var;     var.set(T_VARIABLE, "_");
    Token decl;    _p->onStaticVariable(decl, 0, var, &arr);
    Token sdecl;   _p->onStatic(sdecl, decl);
    _p->addStatement(stmts1, stmts0, sdecl);
  }
  Token stmts2;
  {
    // return $_;
    Token tvar;    tvar.set(T_VARIABLE, "_");
    Token var;     _p->onSimpleVariable(var, tvar);
    Token ret;     _p->onReturn(ret, &var);
    _p->addStatement(stmts2, stmts1, ret);
  }
  Token stmt;
  {
    _p->finishStatement(stmt, stmts2);
    stmt = 1;
  }
  {
    Token params, ret, ref; ref = 1;
    _p->onMethod(out, modifiers, ret, ref, fname, params, stmt, false);
  }
}

static void xhp_children_decl_tag(Parser *_p, Token &arr, Token &tag) {
  Token num;  scalar_num(_p, num, tag.num());
  Token arr1; _p->onArrayPair(arr1, &arr, 0, num, 0);

  Token name;
  if (tag.num() == 3 || tag.num() == 4) {
    _p->onScalar(name, T_CONSTANT_ENCAPSED_STRING, tag);
  } else if (tag.num() >= 0) {
    scalar_null(_p, name);
  } else {
    HPHP_PARSER_ERROR("XHP: unknown children declaration: %s",
                      _p->getMessage(true).c_str());
  }
  Token arr2; _p->onArrayPair(arr2, &arr1, 0, name, 0);
  arr = arr2;
}

static void xhp_children_decl(Parser *_p, Token &out, Token &op1, int op,
                              Token *op2) {
  Token num; scalar_num(_p, num, op);
  Token arr; _p->onArrayPair(arr, 0, 0, num, 0);

  if (op2) {
    Token arr1; _p->onArrayPair(arr1, &arr,  0, op1,  0);
    Token arr2; _p->onArrayPair(arr2, &arr1, 0, *op2, 0);
    _p->onArray(out, arr2);
  } else {
    xhp_children_decl_tag(_p, arr, op1);
    _p->onArray(out, arr);
  }
}

static void xhp_children_paren(Parser *_p, Token &out, Token exp, int op) {
  Token num;  scalar_num(_p, num, op);
  Token arr1; _p->onArrayPair(arr1, 0, 0, num, 0);

  Token num5; scalar_num(_p, num5, 5);
  Token arr2; _p->onArrayPair(arr2, &arr1, 0, num5, 0);

  Token arr3; _p->onArrayPair(arr3, &arr2, 0, exp, 0);
  _p->onArray(out, arr3);
}

static void xhp_children_stmt(Parser *_p, Token &out, Token &children) {
  if (!_p->enableXHP()) {
    HPHP_PARSER_ERROR("XHP: not enabled: %s", _p->getMessage(true).c_str());
  }

  Token fname;     fname.setText("__xhpChildrenDeclaration");
  Token m1;        m1.setNum(T_PROTECTED);
  Token modifiers; _p->onMemberModifier(modifiers, 0, m1);
  _p->pushFuncLocation();
  _p->onMethodStart(fname, modifiers);

  Token stmts0;
  {
    _p->onStatementListStart(stmts0);
  }
  Token stmts1;
  {
    // static $_ = children;
    Token arr;
    if (children.num() == 2) {
      arr = children;
    } else if (children.num() >= 0) {
      scalar_num(_p, arr, children.num());
    } else {
      HPHP_PARSER_ERROR("XHP: XHP unknown children declaration: %s",
                        _p->getMessage(true).c_str());
    }
    Token var;     var.set(T_VARIABLE, "_");
    Token decl;    _p->onStaticVariable(decl, 0, var, &arr);
    Token sdecl;   _p->onStatic(sdecl, decl);
    _p->addStatement(stmts1, stmts0, sdecl);
  }
  Token stmts2;
  {
    // return $_;
    Token tvar;    tvar.set(T_VARIABLE, "_");
    Token var;     _p->onSimpleVariable(var, tvar);
    Token ret;     _p->onReturn(ret, &var);
    _p->addStatement(stmts2, stmts1, ret);
  }
  Token stmt;
  {
    _p->finishStatement(stmt, stmts2);
    stmt = 1;
  }
  {
    Token params, ret, ref; ref = 1;
    _p->onMethod(out, modifiers, ret, ref, fname, params, stmt, false);
  }
}

///////////////////////////////////////////////////////////////////////////////

static int yylex(YYSTYPE *token, HPHP::Location *loc, Parser *_p) {
  return _p->scan(token, loc);
}


/* Line 189 of yacc.c  */
#line 921 "hphp.tab.cpp"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     T_REQUIRE_ONCE = 258,
     T_REQUIRE = 259,
     T_EVAL = 260,
     T_INCLUDE_ONCE = 261,
     T_INCLUDE = 262,
     T_LOGICAL_OR = 263,
     T_LOGICAL_XOR = 264,
     T_LOGICAL_AND = 265,
     T_PRINT = 266,
     T_SR_EQUAL = 267,
     T_SL_EQUAL = 268,
     T_XOR_EQUAL = 269,
     T_OR_EQUAL = 270,
     T_AND_EQUAL = 271,
     T_MOD_EQUAL = 272,
     T_CONCAT_EQUAL = 273,
     T_DIV_EQUAL = 274,
     T_MUL_EQUAL = 275,
     T_MINUS_EQUAL = 276,
     T_PLUS_EQUAL = 277,
     T_BOOLEAN_OR = 278,
     T_BOOLEAN_AND = 279,
     T_IS_NOT_IDENTICAL = 280,
     T_IS_IDENTICAL = 281,
     T_IS_NOT_EQUAL = 282,
     T_IS_EQUAL = 283,
     T_IS_GREATER_OR_EQUAL = 284,
     T_IS_SMALLER_OR_EQUAL = 285,
     T_SR = 286,
     T_SL = 287,
     T_INSTANCEOF = 288,
     T_UNSET_CAST = 289,
     T_BOOL_CAST = 290,
     T_OBJECT_CAST = 291,
     T_ARRAY_CAST = 292,
     T_STRING_CAST = 293,
     T_DOUBLE_CAST = 294,
     T_INT_CAST = 295,
     T_DEC = 296,
     T_INC = 297,
     T_CLONE = 298,
     T_NEW = 299,
     T_EXIT = 300,
     T_IF = 301,
     T_ELSEIF = 302,
     T_ELSE = 303,
     T_ENDIF = 304,
     T_LNUMBER = 305,
     T_DNUMBER = 306,
     T_STRING = 307,
     T_STRING_VARNAME = 308,
     T_VARIABLE = 309,
     T_NUM_STRING = 310,
     T_INLINE_HTML = 311,
     T_CHARACTER = 312,
     T_BAD_CHARACTER = 313,
     T_ENCAPSED_AND_WHITESPACE = 314,
     T_CONSTANT_ENCAPSED_STRING = 315,
     T_ECHO = 316,
     T_DO = 317,
     T_WHILE = 318,
     T_ENDWHILE = 319,
     T_FOR = 320,
     T_ENDFOR = 321,
     T_FOREACH = 322,
     T_ENDFOREACH = 323,
     T_DECLARE = 324,
     T_ENDDECLARE = 325,
     T_AS = 326,
     T_SWITCH = 327,
     T_ENDSWITCH = 328,
     T_CASE = 329,
     T_DEFAULT = 330,
     T_BREAK = 331,
     T_GOTO = 332,
     T_CONTINUE = 333,
     T_FUNCTION = 334,
     T_CONST = 335,
     T_RETURN = 336,
     T_TRY = 337,
     T_CATCH = 338,
     T_THROW = 339,
     T_USE = 340,
     T_GLOBAL = 341,
     T_PUBLIC = 342,
     T_PROTECTED = 343,
     T_PRIVATE = 344,
     T_FINAL = 345,
     T_ABSTRACT = 346,
     T_STATIC = 347,
     T_VAR = 348,
     T_UNSET = 349,
     T_ISSET = 350,
     T_EMPTY = 351,
     T_HALT_COMPILER = 352,
     T_CLASS = 353,
     T_INTERFACE = 354,
     T_EXTENDS = 355,
     T_IMPLEMENTS = 356,
     T_OBJECT_OPERATOR = 357,
     T_DOUBLE_ARROW = 358,
     T_LIST = 359,
     T_ARRAY = 360,
     T_CLASS_C = 361,
     T_METHOD_C = 362,
     T_FUNC_C = 363,
     T_LINE = 364,
     T_FILE = 365,
     T_COMMENT = 366,
     T_DOC_COMMENT = 367,
     T_OPEN_TAG = 368,
     T_OPEN_TAG_WITH_ECHO = 369,
     T_CLOSE_TAG = 370,
     T_WHITESPACE = 371,
     T_START_HEREDOC = 372,
     T_END_HEREDOC = 373,
     T_DOLLAR_OPEN_CURLY_BRACES = 374,
     T_CURLY_OPEN = 375,
     T_PAAMAYIM_NEKUDOTAYIM = 376,
     T_NAMESPACE = 377,
     T_NS_C = 378,
     T_DIR = 379,
     T_NS_SEPARATOR = 380,
     T_YIELD = 381,
     T_XHP_LABEL = 382,
     T_XHP_TEXT = 383,
     T_XHP_ATTRIBUTE = 384,
     T_XHP_CATEGORY = 385,
     T_XHP_CATEGORY_LABEL = 386,
     T_XHP_CHILDREN = 387,
     T_XHP_ENUM = 388,
     T_XHP_REQUIRED = 389,
     T_TRAIT = 390,
     T_INSTEADOF = 391,
     T_TRAIT_C = 392
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int line0;
  int char0;
  int line1;
  int char1;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 1113 "hphp.tab.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
struct yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (struct yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   8255

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  167
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  172
/* YYNRULES -- Number of rules.  */
#define YYNRULES  589
/* YYNRULES -- Number of states.  */
#define YYNSTATES  1083

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   392

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    48,   165,     2,   162,    47,    31,   166,
     157,   158,    45,    42,     8,    43,    44,    46,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    26,   159,
      36,    13,    37,    25,    51,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    61,     2,   164,    30,     2,   163,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   160,    29,   161,    50,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     9,    10,    11,    12,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    27,    28,
      32,    33,    34,    35,    38,    39,    40,    41,    49,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,     9,    11,    13,    15,    17,
      22,    26,    27,    34,    35,    41,    45,    48,    52,    54,
      56,    59,    63,    68,    70,    74,    76,    79,    83,    85,
      88,    92,    98,   103,   106,   107,   109,   111,   113,   116,
     118,   121,   125,   133,   144,   145,   152,   153,   162,   163,
     174,   175,   182,   185,   189,   192,   196,   199,   203,   207,
     211,   215,   219,   225,   231,   240,   249,   253,   257,   261,
     265,   271,   273,   275,   276,   286,   287,   297,   303,   317,
     321,   325,   335,   336,   338,   342,   344,   346,   347,   349,
     350,   362,   363,   372,   373,   374,   384,   385,   393,   394,
     401,   403,   406,   409,   412,   413,   416,   417,   420,   421,
     423,   427,   429,   433,   436,   437,   439,   442,   444,   449,
     451,   456,   458,   463,   465,   470,   474,   480,   484,   489,
     494,   500,   506,   511,   512,   514,   516,   523,   524,   532,
     533,   536,   537,   541,   542,   544,   545,   548,   552,   558,
     563,   568,   574,   582,   589,   591,   593,   595,   597,   598,
     600,   601,   603,   605,   608,   612,   616,   621,   625,   627,
     629,   632,   637,   641,   647,   649,   653,   657,   663,   665,
     669,   672,   673,   676,   677,   678,   683,   684,   690,   693,
     694,   705,   706,   711,   715,   719,   723,   729,   732,   735,
     736,   743,   749,   754,   758,   760,   762,   763,   768,   773,
     775,   777,   779,   781,   783,   785,   787,   792,   794,   796,
     800,   803,   804,   805,   809,   810,   812,   816,   818,   820,
     822,   824,   828,   833,   838,   843,   845,   847,   850,   853,
     856,   860,   864,   866,   868,   870,   872,   876,   878,   880,
     882,   883,   885,   888,   890,   892,   894,   896,   898,   900,
     904,   910,   912,   916,   922,   927,   931,   933,   935,   936,
     940,   942,   949,   953,   958,   965,   969,   972,   976,   980,
     984,   988,   992,   996,  1000,  1004,  1008,  1012,  1016,  1019,
    1022,  1025,  1028,  1032,  1036,  1040,  1044,  1048,  1052,  1056,
    1060,  1064,  1068,  1072,  1076,  1080,  1084,  1088,  1092,  1095,
    1098,  1101,  1104,  1108,  1112,  1116,  1120,  1124,  1128,  1132,
    1136,  1140,  1144,  1150,  1155,  1157,  1160,  1163,  1166,  1169,
    1172,  1175,  1178,  1181,  1184,  1186,  1191,  1195,  1198,  1199,
    1211,  1216,  1218,  1223,  1224,  1228,  1233,  1235,  1238,  1243,
    1245,  1246,  1251,  1252,  1253,  1262,  1264,  1265,  1266,  1272,
    1273,  1276,  1277,  1279,  1281,  1285,  1287,  1291,  1293,  1295,
    1296,  1301,  1302,  1307,  1309,  1310,  1315,  1316,  1321,  1323,
    1325,  1327,  1329,  1331,  1333,  1335,  1337,  1339,  1341,  1343,
    1345,  1347,  1349,  1351,  1353,  1355,  1357,  1359,  1361,  1363,
    1365,  1367,  1369,  1371,  1373,  1375,  1377,  1379,  1381,  1383,
    1385,  1387,  1389,  1391,  1393,  1395,  1397,  1399,  1401,  1403,
    1405,  1407,  1409,  1411,  1413,  1415,  1417,  1419,  1421,  1423,
    1425,  1427,  1429,  1431,  1433,  1435,  1437,  1439,  1441,  1443,
    1445,  1447,  1449,  1451,  1453,  1455,  1457,  1459,  1461,  1463,
    1465,  1470,  1475,  1482,  1489,  1491,  1493,  1495,  1497,  1499,
    1501,  1503,  1505,  1507,  1508,  1514,  1516,  1519,  1520,  1523,
    1526,  1530,  1531,  1532,  1534,  1536,  1540,  1541,  1543,  1545,
    1547,  1549,  1551,  1553,  1555,  1557,  1559,  1561,  1563,  1567,
    1570,  1572,  1574,  1577,  1580,  1585,  1587,  1591,  1595,  1597,
    1599,  1601,  1603,  1607,  1611,  1615,  1618,  1619,  1621,  1622,
    1628,  1632,  1636,  1638,  1640,  1642,  1644,  1646,  1648,  1649,
    1650,  1658,  1660,  1663,  1664,  1668,  1672,  1673,  1675,  1678,
    1682,  1684,  1686,  1688,  1691,  1693,  1698,  1703,  1705,  1707,
    1712,  1714,  1715,  1717,  1719,  1724,  1729,  1731,  1733,  1737,
    1739,  1742,  1745,  1749,  1756,  1757,  1759,  1764,  1767,  1768,
    1774,  1778,  1782,  1784,  1791,  1796,  1801,  1804,  1807,  1810,
    1812,  1815,  1817,  1822,  1826,  1830,  1837,  1841,  1843,  1845,
    1847,  1852,  1857,  1860,  1863,  1868,  1871,  1874,  1876,  1880
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     168,     0,    -1,   169,    -1,   169,   170,    -1,    -1,   181,
      -1,   194,    -1,   196,    -1,   201,    -1,   116,   157,   158,
     159,    -1,   141,   175,   159,    -1,    -1,   141,   175,   160,
     171,   169,   161,    -1,    -1,   141,   160,   172,   169,   161,
      -1,   104,   173,   159,    -1,   178,   159,    -1,   173,     8,
     174,    -1,   174,    -1,   175,    -1,   144,   175,    -1,   175,
      90,    71,    -1,   144,   175,    90,    71,    -1,    71,    -1,
     175,   144,    71,    -1,   175,    -1,   144,   175,    -1,   141,
     144,   175,    -1,   175,    -1,   144,   175,    -1,   141,   144,
     175,    -1,   178,     8,    71,    13,   303,    -1,    99,    71,
      13,   303,    -1,   179,   180,    -1,    -1,   181,    -1,   194,
      -1,   196,    -1,   309,   159,    -1,   182,    -1,    71,    26,
      -1,   160,   179,   161,    -1,    65,   157,   309,   158,   181,
     219,   221,    -1,    65,   157,   309,   158,    26,   179,   220,
     222,    68,   159,    -1,    -1,    82,   157,   309,   158,   183,
     213,    -1,    -1,    81,   184,   181,    82,   157,   309,   158,
     159,    -1,    -1,    84,   157,   266,   159,   266,   159,   266,
     158,   185,   211,    -1,    -1,    91,   157,   309,   158,   186,
     216,    -1,    95,   159,    -1,    95,   309,   159,    -1,    97,
     159,    -1,    97,   309,   159,    -1,   100,   159,    -1,   100,
     268,   159,    -1,   100,   313,   159,    -1,   145,    95,   159,
      -1,   145,   268,   159,    -1,   145,   313,   159,    -1,   313,
      13,   145,   268,   159,    -1,   313,    13,   145,   313,   159,
      -1,   123,   157,   330,   158,    13,   145,   268,   159,    -1,
     123,   157,   330,   158,    13,   145,   313,   159,    -1,   105,
     229,   159,    -1,   111,   231,   159,    -1,   225,   232,   159,
      -1,    80,   265,   159,    -1,   113,   157,   190,   158,   159,
      -1,   159,    -1,    75,    -1,    -1,    86,   157,   313,    90,
     210,   209,   158,   187,   212,    -1,    -1,    86,   157,   268,
      90,   313,   209,   158,   188,   212,    -1,    88,   157,   215,
     158,   214,    -1,   101,   160,   179,   161,   102,   157,   293,
      73,   158,   160,   179,   161,   189,    -1,   103,   309,   159,
      -1,    96,    71,   159,    -1,   189,   102,   157,   293,    73,
     158,   160,   179,   161,    -1,    -1,   191,    -1,   190,     8,
     191,    -1,   313,    -1,    31,    -1,    -1,    98,    -1,    -1,
     226,   193,   192,    71,   195,   157,   223,   158,   160,   179,
     161,    -1,    -1,   203,    71,   204,   197,   205,   160,   233,
     161,    -1,    -1,    -1,   203,   146,   204,   198,   205,   160,
     199,   234,   161,    -1,    -1,   118,    71,   200,   206,   160,
     233,   161,    -1,    -1,   154,    71,   202,   160,   233,   161,
      -1,   117,    -1,   110,   117,    -1,   109,   117,    -1,   119,
     293,    -1,    -1,   120,   207,    -1,    -1,   119,   207,    -1,
      -1,   293,    -1,   207,     8,   293,    -1,   293,    -1,   208,
       8,   293,    -1,   122,   210,    -1,    -1,   313,    -1,    31,
     313,    -1,   181,    -1,    26,   179,    85,   159,    -1,   181,
      -1,    26,   179,    87,   159,    -1,   181,    -1,    26,   179,
      83,   159,    -1,   181,    -1,    26,   179,    89,   159,    -1,
      71,    13,   303,    -1,   215,     8,    71,    13,   303,    -1,
     160,   217,   161,    -1,   160,   159,   217,   161,    -1,    26,
     217,    92,   159,    -1,    26,   159,   217,    92,   159,    -1,
     217,    93,   309,   218,   179,    -1,   217,    94,   218,   179,
      -1,    -1,    26,    -1,   159,    -1,   219,    66,   157,   309,
     158,   181,    -1,    -1,   220,    66,   157,   309,   158,    26,
     179,    -1,    -1,    67,   181,    -1,    -1,    67,    26,   179,
      -1,    -1,   224,    -1,    -1,   226,    73,    -1,   226,    31,
      73,    -1,   226,    31,    73,    13,   303,    -1,   226,    73,
      13,   303,    -1,   224,     8,   226,    73,    -1,   224,     8,
     226,    31,    73,    -1,   224,     8,   226,    31,    73,    13,
     303,    -1,   224,     8,   226,    73,    13,   303,    -1,    71,
      -1,   124,    -1,   146,    -1,   225,    -1,    -1,   228,    -1,
      -1,   268,    -1,   313,    -1,    31,   311,    -1,   228,     8,
     268,    -1,   228,     8,   313,    -1,   228,     8,    31,   311,
      -1,   229,     8,   230,    -1,   230,    -1,    73,    -1,   162,
     310,    -1,   162,   160,   309,   161,    -1,   231,     8,    73,
      -1,   231,     8,    73,    13,   303,    -1,    73,    -1,    73,
      13,   303,    -1,   232,     8,    73,    -1,   232,     8,    73,
      13,   309,    -1,    73,    -1,    73,    13,   309,    -1,   233,
     235,    -1,    -1,   234,   235,    -1,    -1,    -1,   259,   236,
     263,   159,    -1,    -1,   261,   225,   237,   263,   159,    -1,
     264,   159,    -1,    -1,   260,   226,   193,   192,    71,   157,
     238,   223,   158,   258,    -1,    -1,   148,   239,   244,   159,
      -1,   149,   252,   159,    -1,   151,   254,   159,    -1,   104,
     208,   159,    -1,   104,   208,   160,   240,   161,    -1,   240,
     241,    -1,   240,   242,    -1,    -1,   177,   140,    71,   155,
     208,   159,    -1,   243,    90,   260,    71,   159,    -1,   243,
      90,   261,   159,    -1,   177,   140,    71,    -1,    71,    -1,
     246,    -1,    -1,   244,     8,   245,   246,    -1,   247,   287,
     249,   250,    -1,   146,    -1,    56,    -1,    53,    -1,    58,
      -1,    55,    -1,   293,    -1,   112,    -1,   152,   160,   248,
     161,    -1,    57,    -1,   302,    -1,   248,     8,   302,    -1,
      13,   303,    -1,    -1,    -1,    51,   251,   153,    -1,    -1,
     253,    -1,   252,     8,   253,    -1,   150,    -1,   255,    -1,
      71,    -1,   115,    -1,   157,   256,   158,    -1,   157,   256,
     158,    45,    -1,   157,   256,   158,    25,    -1,   157,   256,
     158,    42,    -1,   255,    -1,   257,    -1,   257,    45,    -1,
     257,    25,    -1,   257,    42,    -1,   256,     8,   256,    -1,
     256,    29,   256,    -1,    71,    -1,   146,    -1,   150,    -1,
     159,    -1,   160,   179,   161,    -1,   261,    -1,   112,    -1,
     261,    -1,    -1,   262,    -1,   261,   262,    -1,   106,    -1,
     107,    -1,   108,    -1,   111,    -1,   110,    -1,   109,    -1,
     263,     8,    73,    -1,   263,     8,    73,    13,   303,    -1,
      73,    -1,    73,    13,   303,    -1,   264,     8,    71,    13,
     303,    -1,    99,    71,    13,   303,    -1,   265,     8,   309,
      -1,   309,    -1,   267,    -1,    -1,   267,     8,   309,    -1,
     309,    -1,   123,   157,   330,   158,    13,   309,    -1,   313,
      13,   309,    -1,   313,    13,    31,   313,    -1,   313,    13,
      31,    63,   294,   301,    -1,    63,   294,   301,    -1,    62,
     309,    -1,   313,    24,   309,    -1,   313,    23,   309,    -1,
     313,    22,   309,    -1,   313,    21,   309,    -1,   313,    20,
     309,    -1,   313,    19,   309,    -1,   313,    18,   309,    -1,
     313,    17,   309,    -1,   313,    16,   309,    -1,   313,    15,
     309,    -1,   313,    14,   309,    -1,   312,    60,    -1,    60,
     312,    -1,   312,    59,    -1,    59,   312,    -1,   309,    27,
     309,    -1,   309,    28,   309,    -1,   309,     9,   309,    -1,
     309,    11,   309,    -1,   309,    10,   309,    -1,   309,    29,
     309,    -1,   309,    31,   309,    -1,   309,    30,   309,    -1,
     309,    44,   309,    -1,   309,    42,   309,    -1,   309,    43,
     309,    -1,   309,    45,   309,    -1,   309,    46,   309,    -1,
     309,    47,   309,    -1,   309,    41,   309,    -1,   309,    40,
     309,    -1,    42,   309,    -1,    43,   309,    -1,    48,   309,
      -1,    50,   309,    -1,   309,    33,   309,    -1,   309,    32,
     309,    -1,   309,    35,   309,    -1,   309,    34,   309,    -1,
     309,    36,   309,    -1,   309,    39,   309,    -1,   309,    37,
     309,    -1,   309,    38,   309,    -1,   309,    49,   294,    -1,
     157,   309,   158,    -1,   309,    25,   309,    26,   309,    -1,
     309,    25,    26,   309,    -1,   336,    -1,    58,   309,    -1,
      57,   309,    -1,    56,   309,    -1,    55,   309,    -1,    54,
     309,    -1,    53,   309,    -1,    52,   309,    -1,    64,   299,
      -1,    51,   309,    -1,   305,    -1,   124,   157,   331,   158,
      -1,   163,   300,   163,    -1,    12,   309,    -1,    -1,   226,
     193,   192,   157,   269,   223,   158,   270,   160,   179,   161,
      -1,   309,    61,   325,   164,    -1,   272,    -1,   104,   157,
     271,   158,    -1,    -1,   271,     8,    73,    -1,   271,     8,
      31,    73,    -1,    73,    -1,    31,    73,    -1,    36,   284,
     273,    37,    -1,    46,    -1,    -1,   278,    46,   274,   277,
      -1,    -1,    -1,   278,    37,   275,   280,    36,    46,   276,
     277,    -1,   146,    -1,    -1,    -1,   278,   281,    13,   279,
     282,    -1,    -1,   280,   283,    -1,    -1,   287,    -1,   147,
      -1,   160,   309,   161,    -1,   147,    -1,   160,   309,   161,
      -1,   272,    -1,   290,    -1,    -1,   284,    26,   285,   290,
      -1,    -1,   284,    43,   286,   290,    -1,   290,    -1,    -1,
     287,    26,   288,   290,    -1,    -1,   287,    43,   289,   290,
      -1,    71,    -1,    64,    -1,    98,    -1,    99,    -1,   100,
      -1,   145,    -1,   101,    -1,   102,    -1,   103,    -1,    65,
      -1,    66,    -1,    68,    -1,    67,    -1,    82,    -1,    83,
      -1,    81,    -1,    84,    -1,    85,    -1,    86,    -1,    87,
      -1,    88,    -1,    89,    -1,    49,    -1,    90,    -1,    91,
      -1,    92,    -1,    93,    -1,    94,    -1,    95,    -1,    97,
      -1,    96,    -1,    80,    -1,    12,    -1,   117,    -1,   118,
      -1,   119,    -1,   120,    -1,    63,    -1,    62,    -1,   112,
      -1,     5,    -1,     7,    -1,     6,    -1,     4,    -1,     3,
      -1,   141,    -1,   104,    -1,   105,    -1,   114,    -1,   115,
      -1,   116,    -1,   111,    -1,   110,    -1,   109,    -1,   108,
      -1,   107,    -1,   106,    -1,   113,    -1,   123,    -1,   124,
      -1,     9,    -1,    11,    -1,    10,    -1,   125,    -1,   127,
      -1,   126,    -1,   128,    -1,   129,    -1,   143,    -1,   142,
      -1,   154,    -1,   156,    -1,   176,   157,   227,   158,    -1,
     319,   157,   227,   158,    -1,   292,   140,    71,   157,   227,
     158,    -1,   292,   140,   319,   157,   227,   158,    -1,   293,
      -1,   111,    -1,   323,    -1,   177,    -1,   146,    -1,   177,
      -1,   146,    -1,   295,    -1,   111,    -1,    -1,   322,   296,
     121,   326,   297,    -1,   322,    -1,   297,   298,    -1,    -1,
     121,   326,    -1,   157,   158,    -1,   157,   309,   158,    -1,
      -1,    -1,    78,    -1,   333,    -1,   157,   227,   158,    -1,
      -1,    69,    -1,    70,    -1,    79,    -1,   128,    -1,   129,
      -1,   143,    -1,   125,    -1,   156,    -1,   126,    -1,   127,
      -1,   142,    -1,   136,    78,   137,    -1,   136,   137,    -1,
     302,    -1,   176,    -1,    42,   303,    -1,    43,   303,    -1,
     124,   157,   306,   158,    -1,   304,    -1,   177,   140,    71,
      -1,   146,   140,    71,    -1,   176,    -1,    72,    -1,   338,
      -1,   302,    -1,   165,   333,   165,    -1,   166,   333,   166,
      -1,   136,   333,   137,    -1,   308,   307,    -1,    -1,     8,
      -1,    -1,   308,     8,   303,   122,   303,    -1,   308,     8,
     303,    -1,   303,   122,   303,    -1,   303,    -1,   310,    -1,
     268,    -1,   313,    -1,   313,    -1,   313,    -1,    -1,    -1,
     321,   314,   121,   326,   318,   315,   316,    -1,   321,    -1,
     316,   317,    -1,    -1,   121,   326,   318,    -1,   157,   227,
     158,    -1,    -1,   323,    -1,   329,   323,    -1,   292,   140,
     319,    -1,   322,    -1,   291,    -1,   323,    -1,   329,   323,
      -1,   320,    -1,   323,    61,   325,   164,    -1,   323,   160,
     309,   161,    -1,   324,    -1,    73,    -1,   162,   160,   309,
     161,    -1,   309,    -1,    -1,   327,    -1,   319,    -1,   327,
      61,   325,   164,    -1,   327,   160,   309,   161,    -1,   328,
      -1,    71,    -1,   160,   309,   161,    -1,   162,    -1,   329,
     162,    -1,   330,     8,    -1,   330,     8,   313,    -1,   330,
       8,   123,   157,   330,   158,    -1,    -1,   313,    -1,   123,
     157,   330,   158,    -1,   332,   307,    -1,    -1,   332,     8,
     309,   122,   309,    -1,   332,     8,   309,    -1,   309,   122,
     309,    -1,   309,    -1,   332,     8,   309,   122,    31,   311,
      -1,   332,     8,    31,   311,    -1,   309,   122,    31,   311,
      -1,    31,   311,    -1,   333,   334,    -1,   333,    78,    -1,
     334,    -1,    78,   334,    -1,    73,    -1,    73,    61,   335,
     164,    -1,    73,   121,    71,    -1,   138,   309,   161,    -1,
     138,    72,    61,   309,   164,   161,    -1,   139,   313,   161,
      -1,    71,    -1,    74,    -1,    73,    -1,   114,   157,   337,
     158,    -1,   115,   157,   313,   158,    -1,     7,   309,    -1,
       6,   309,    -1,     5,   157,   309,   158,    -1,     4,   309,
      -1,     3,   309,    -1,   313,    -1,   337,     8,   313,    -1,
     292,   140,    71,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   964,   964,   969,   971,   974,   976,   977,   978,   979,
     980,   982,   982,   984,   984,   986,   987,   992,   994,   997,
     998,   999,  1000,  1004,  1005,  1009,  1011,  1012,  1016,  1018,
    1019,  1023,  1026,  1031,  1033,  1036,  1037,  1038,  1041,  1042,
    1043,  1049,  1051,  1056,  1062,  1062,  1066,  1066,  1071,  1070,
    1075,  1075,  1079,  1080,  1082,  1083,  1085,  1086,  1087,  1089,
    1090,  1091,  1092,  1094,  1095,  1097,  1100,  1101,  1102,  1103,
    1104,  1106,  1108,  1112,  1110,  1118,  1116,  1122,  1125,  1133,
    1134,  1140,  1146,  1150,  1151,  1154,  1158,  1159,  1163,  1167,
    1166,  1177,  1176,  1183,  1186,  1182,  1192,  1192,  1198,  1198,
    1206,  1207,  1208,  1211,  1213,  1216,  1217,  1220,  1221,  1224,
    1225,  1229,  1230,  1235,  1236,  1239,  1240,  1244,  1245,  1249,
    1250,  1254,  1255,  1259,  1260,  1265,  1266,  1271,  1272,  1273,
    1274,  1277,  1280,  1282,  1285,  1286,  1290,  1292,  1295,  1298,
    1301,  1302,  1305,  1306,  1310,  1311,  1314,  1315,  1316,  1318,
    1320,  1322,  1324,  1327,  1332,  1333,  1334,  1337,  1338,  1342,
    1343,  1346,  1347,  1348,  1349,  1351,  1353,  1358,  1359,  1362,
    1363,  1364,  1368,  1369,  1371,  1372,  1376,  1377,  1378,  1379,
    1383,  1385,  1388,  1391,  1394,  1394,  1398,  1397,  1401,  1405,
    1403,  1409,  1409,  1411,  1413,  1415,  1417,  1421,  1422,  1423,
    1426,  1432,  1435,  1441,  1444,  1448,  1450,  1450,  1455,  1460,
    1464,  1465,  1466,  1467,  1468,  1469,  1470,  1472,  1476,  1477,
    1482,  1483,  1487,  1487,  1489,  1493,  1495,  1501,  1506,  1507,
    1509,  1513,  1514,  1515,  1516,  1520,  1521,  1522,  1523,  1524,
    1525,  1527,  1532,  1535,  1536,  1540,  1541,  1544,  1545,  1548,
    1549,  1552,  1553,  1557,  1558,  1559,  1560,  1561,  1562,  1565,
    1567,  1569,  1570,  1573,  1575,  1579,  1580,  1584,  1585,  1588,
    1589,  1593,  1595,  1596,  1597,  1600,  1602,  1603,  1604,  1605,
    1606,  1607,  1608,  1609,  1610,  1611,  1612,  1613,  1614,  1615,
    1616,  1617,  1618,  1619,  1620,  1621,  1622,  1623,  1624,  1625,
    1626,  1627,  1628,  1629,  1630,  1631,  1632,  1633,  1634,  1635,
    1636,  1637,  1638,  1639,  1640,  1641,  1642,  1643,  1645,  1646,
    1648,  1650,  1651,  1652,  1653,  1654,  1655,  1656,  1657,  1658,
    1659,  1660,  1661,  1662,  1663,  1664,  1665,  1666,  1668,  1667,
    1673,  1674,  1678,  1679,  1683,  1684,  1685,  1686,  1690,  1693,
    1699,  1699,  1705,  1706,  1705,  1714,  1715,  1719,  1718,  1721,
    1724,  1725,  1728,  1732,  1735,  1738,  1745,  1746,  1749,  1750,
    1750,  1752,  1752,  1756,  1757,  1757,  1759,  1759,  1763,  1764,
    1765,  1766,  1767,  1768,  1769,  1770,  1771,  1772,  1773,  1774,
    1775,  1776,  1777,  1778,  1779,  1780,  1781,  1782,  1783,  1784,
    1785,  1786,  1787,  1788,  1789,  1790,  1791,  1792,  1793,  1794,
    1795,  1796,  1797,  1798,  1799,  1800,  1801,  1802,  1803,  1804,
    1805,  1806,  1807,  1808,  1809,  1810,  1811,  1812,  1813,  1814,
    1815,  1816,  1817,  1818,  1819,  1820,  1821,  1822,  1823,  1824,
    1825,  1826,  1827,  1828,  1829,  1830,  1831,  1832,  1833,  1834,
    1838,  1840,  1842,  1846,  1852,  1853,  1854,  1858,  1859,  1862,
    1863,  1865,  1866,  1869,  1869,  1872,  1875,  1877,  1880,  1884,
    1885,  1886,  1890,  1891,  1892,  1895,  1897,  1901,  1902,  1903,
    1905,  1906,  1907,  1908,  1909,  1910,  1911,  1912,  1913,  1916,
    1921,  1922,  1923,  1924,  1925,  1927,  1930,  1933,  1938,  1939,
    1940,  1941,  1942,  1943,  1944,  1949,  1951,  1954,  1955,  1958,
    1961,  1963,  1965,  1969,  1970,  1973,  1976,  1979,  1982,  1984,
    1982,  1986,  1990,  1992,  1995,  1999,  2001,  2005,  2006,  2010,
    2016,  2017,  2020,  2021,  2023,  2026,  2028,  2029,  2032,  2033,
    2036,  2037,  2041,  2042,  2045,  2046,  2047,  2050,  2051,  2055,
    2056,  2060,  2061,  2062,  2064,  2065,  2066,  2070,  2072,  2075,
    2077,  2078,  2079,  2080,  2083,  2085,  2086,  2090,  2091,  2093,
    2094,  2100,  2101,  2103,  2105,  2107,  2109,  2112,  2113,  2114,
    2118,  2119,  2120,  2121,  2122,  2123,  2124,  2128,  2129,  2133
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_REQUIRE_ONCE", "T_REQUIRE", "T_EVAL",
  "T_INCLUDE_ONCE", "T_INCLUDE", "','", "T_LOGICAL_OR", "T_LOGICAL_XOR",
  "T_LOGICAL_AND", "T_PRINT", "'='", "T_SR_EQUAL", "T_SL_EQUAL",
  "T_XOR_EQUAL", "T_OR_EQUAL", "T_AND_EQUAL", "T_MOD_EQUAL",
  "T_CONCAT_EQUAL", "T_DIV_EQUAL", "T_MUL_EQUAL", "T_MINUS_EQUAL",
  "T_PLUS_EQUAL", "'?'", "':'", "T_BOOLEAN_OR", "T_BOOLEAN_AND", "'|'",
  "'^'", "'&'", "T_IS_NOT_IDENTICAL", "T_IS_IDENTICAL", "T_IS_NOT_EQUAL",
  "T_IS_EQUAL", "'<'", "'>'", "T_IS_GREATER_OR_EQUAL",
  "T_IS_SMALLER_OR_EQUAL", "T_SR", "T_SL", "'+'", "'-'", "'.'", "'*'",
  "'/'", "'%'", "'!'", "T_INSTANCEOF", "'~'", "'@'", "T_UNSET_CAST",
  "T_BOOL_CAST", "T_OBJECT_CAST", "T_ARRAY_CAST", "T_STRING_CAST",
  "T_DOUBLE_CAST", "T_INT_CAST", "T_DEC", "T_INC", "'['", "T_CLONE",
  "T_NEW", "T_EXIT", "T_IF", "T_ELSEIF", "T_ELSE", "T_ENDIF", "T_LNUMBER",
  "T_DNUMBER", "T_STRING", "T_STRING_VARNAME", "T_VARIABLE",
  "T_NUM_STRING", "T_INLINE_HTML", "T_CHARACTER", "T_BAD_CHARACTER",
  "T_ENCAPSED_AND_WHITESPACE", "T_CONSTANT_ENCAPSED_STRING", "T_ECHO",
  "T_DO", "T_WHILE", "T_ENDWHILE", "T_FOR", "T_ENDFOR", "T_FOREACH",
  "T_ENDFOREACH", "T_DECLARE", "T_ENDDECLARE", "T_AS", "T_SWITCH",
  "T_ENDSWITCH", "T_CASE", "T_DEFAULT", "T_BREAK", "T_GOTO", "T_CONTINUE",
  "T_FUNCTION", "T_CONST", "T_RETURN", "T_TRY", "T_CATCH", "T_THROW",
  "T_USE", "T_GLOBAL", "T_PUBLIC", "T_PROTECTED", "T_PRIVATE", "T_FINAL",
  "T_ABSTRACT", "T_STATIC", "T_VAR", "T_UNSET", "T_ISSET", "T_EMPTY",
  "T_HALT_COMPILER", "T_CLASS", "T_INTERFACE", "T_EXTENDS", "T_IMPLEMENTS",
  "T_OBJECT_OPERATOR", "T_DOUBLE_ARROW", "T_LIST", "T_ARRAY", "T_CLASS_C",
  "T_METHOD_C", "T_FUNC_C", "T_LINE", "T_FILE", "T_COMMENT",
  "T_DOC_COMMENT", "T_OPEN_TAG", "T_OPEN_TAG_WITH_ECHO", "T_CLOSE_TAG",
  "T_WHITESPACE", "T_START_HEREDOC", "T_END_HEREDOC",
  "T_DOLLAR_OPEN_CURLY_BRACES", "T_CURLY_OPEN", "T_PAAMAYIM_NEKUDOTAYIM",
  "T_NAMESPACE", "T_NS_C", "T_DIR", "T_NS_SEPARATOR", "T_YIELD",
  "T_XHP_LABEL", "T_XHP_TEXT", "T_XHP_ATTRIBUTE", "T_XHP_CATEGORY",
  "T_XHP_CATEGORY_LABEL", "T_XHP_CHILDREN", "T_XHP_ENUM", "T_XHP_REQUIRED",
  "T_TRAIT", "T_INSTEADOF", "T_TRAIT_C", "'('", "')'", "';'", "'{'", "'}'",
  "'$'", "'`'", "']'", "'\"'", "'\\''", "$accept", "start",
  "top_statement_list", "top_statement", "$@1", "$@2", "use_declarations",
  "use_declaration", "namespace_name", "namespace_string",
  "class_namespace_string", "constant_declaration", "inner_statement_list",
  "inner_statement", "statement", "statement_without_expr", "$@3", "$@4",
  "$@5", "$@6", "$@7", "$@8", "additional_catches", "unset_variables",
  "unset_variable", "is_reference", "function_loc",
  "function_declaration_statement", "$@9", "class_declaration_statement",
  "$@10", "$@11", "$@12", "$@13", "trait_declaration_statement", "$@14",
  "class_entry_type", "extends_from", "implements_list",
  "interface_extends_list", "interface_list", "trait_list",
  "foreach_optional_arg", "foreach_variable", "for_statement",
  "foreach_statement", "while_statement", "declare_statement",
  "declare_list", "switch_case_list", "case_list", "case_separator",
  "elseif_list", "new_elseif_list", "else_single", "new_else_single",
  "parameter_list", "non_empty_parameter_list", "non_empty_type_decl",
  "type_decl", "function_call_parameter_list",
  "non_empty_fcall_parameter_list", "global_var_list", "global_var",
  "static_var_list", "var_list", "class_statement_list",
  "xhp_class_statement_list", "class_statement", "$@15", "$@16", "$@17",
  "$@18", "trait_rules", "trait_precedence_rule", "trait_alias_rule",
  "trait_alias_rule_method", "xhp_attribute_stmt", "$@19",
  "xhp_attribute_decl", "xhp_attribute_decl_type", "xhp_attribute_enum",
  "xhp_attribute_default", "xhp_attribute_is_required", "$@20",
  "xhp_category_stmt", "xhp_category_decl", "xhp_children_stmt",
  "xhp_children_paren_expr", "xhp_children_decl_expr",
  "xhp_children_decl_tag", "method_body", "variable_modifiers",
  "method_modifiers", "non_empty_member_modifiers", "member_modifier",
  "class_variable_declaration", "class_constant_declaration",
  "echo_expr_list", "for_expr", "non_empty_for_expr",
  "expr_without_variable", "$@21", "lexical_vars", "lexical_var_list",
  "xhp_tag", "xhp_tag_body", "$@22", "$@23", "$@24", "xhp_end_tag",
  "xhp_attributes", "$@25", "xhp_children", "xhp_attribute_name",
  "xhp_attribute_value", "xhp_child", "xhp_label", "$@26", "$@27",
  "xhp_label_ws", "$@28", "$@29", "xhp_bareword", "function_call",
  "static_class_name", "fully_qualified_class_name",
  "class_name_reference", "dynamic_class_name_reference", "$@30",
  "object_properties", "dynamic_class_name_variable_prop", "exit_expr",
  "backticks_expr", "ctor_arguments", "common_scalar", "static_scalar",
  "static_class_constant", "scalar", "static_array_pair_list",
  "possible_comma", "non_empty_static_array_pair_list", "expr",
  "r_variable", "w_variable", "rw_variable", "variable", "$@31", "$@32",
  "variable_properties", "variable_property", "method_or_not",
  "variable_without_objects", "static_member",
  "base_variable_with_function_calls", "base_variable",
  "reference_variable", "compound_variable", "dim_offset",
  "object_property", "object_dim_list", "variable_name",
  "simple_indirect_reference", "assignment_list", "array_pair_list",
  "non_empty_array_pair_list", "encaps_list", "encaps_var",
  "encaps_var_offset", "internal_functions", "isset_variables",
  "class_constant", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,    44,   263,
     264,   265,   266,    61,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,    63,    58,   278,   279,   124,
      94,    38,   280,   281,   282,   283,    60,    62,   284,   285,
     286,   287,    43,    45,    46,    42,    47,    37,    33,   288,
     126,    64,   289,   290,   291,   292,   293,   294,   295,   296,
     297,    91,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   324,   325,
     326,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,   339,   340,   341,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,   352,   353,   354,   355,
     356,   357,   358,   359,   360,   361,   362,   363,   364,   365,
     366,   367,   368,   369,   370,   371,   372,   373,   374,   375,
     376,   377,   378,   379,   380,   381,   382,   383,   384,   385,
     386,   387,   388,   389,   390,   391,   392,    40,    41,    59,
     123,   125,    36,    96,    93,    34,    39
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   167,   168,   169,   169,   170,   170,   170,   170,   170,
     170,   171,   170,   172,   170,   170,   170,   173,   173,   174,
     174,   174,   174,   175,   175,   176,   176,   176,   177,   177,
     177,   178,   178,   179,   179,   180,   180,   180,   181,   181,
     181,   182,   182,   182,   183,   182,   184,   182,   185,   182,
     186,   182,   182,   182,   182,   182,   182,   182,   182,   182,
     182,   182,   182,   182,   182,   182,   182,   182,   182,   182,
     182,   182,   182,   187,   182,   188,   182,   182,   182,   182,
     182,   189,   189,   190,   190,   191,   192,   192,   193,   195,
     194,   197,   196,   198,   199,   196,   200,   196,   202,   201,
     203,   203,   203,   204,   204,   205,   205,   206,   206,   207,
     207,   208,   208,   209,   209,   210,   210,   211,   211,   212,
     212,   213,   213,   214,   214,   215,   215,   216,   216,   216,
     216,   217,   217,   217,   218,   218,   219,   219,   220,   220,
     221,   221,   222,   222,   223,   223,   224,   224,   224,   224,
     224,   224,   224,   224,   225,   225,   225,   226,   226,   227,
     227,   228,   228,   228,   228,   228,   228,   229,   229,   230,
     230,   230,   231,   231,   231,   231,   232,   232,   232,   232,
     233,   233,   234,   234,   236,   235,   237,   235,   235,   238,
     235,   239,   235,   235,   235,   235,   235,   240,   240,   240,
     241,   242,   242,   243,   243,   244,   245,   244,   246,   246,
     247,   247,   247,   247,   247,   247,   247,   247,   248,   248,
     249,   249,   251,   250,   250,   252,   252,   253,   254,   254,
     254,   255,   255,   255,   255,   256,   256,   256,   256,   256,
     256,   256,   257,   257,   257,   258,   258,   259,   259,   260,
     260,   261,   261,   262,   262,   262,   262,   262,   262,   263,
     263,   263,   263,   264,   264,   265,   265,   266,   266,   267,
     267,   268,   268,   268,   268,   268,   268,   268,   268,   268,
     268,   268,   268,   268,   268,   268,   268,   268,   268,   268,
     268,   268,   268,   268,   268,   268,   268,   268,   268,   268,
     268,   268,   268,   268,   268,   268,   268,   268,   268,   268,
     268,   268,   268,   268,   268,   268,   268,   268,   268,   268,
     268,   268,   268,   268,   268,   268,   268,   268,   268,   268,
     268,   268,   268,   268,   268,   268,   268,   268,   269,   268,
     268,   268,   270,   270,   271,   271,   271,   271,   272,   273,
     274,   273,   275,   276,   273,   277,   277,   279,   278,   278,
     280,   280,   281,   282,   282,   283,   283,   283,   284,   285,
     284,   286,   284,   287,   288,   287,   289,   287,   290,   290,
     290,   290,   290,   290,   290,   290,   290,   290,   290,   290,
     290,   290,   290,   290,   290,   290,   290,   290,   290,   290,
     290,   290,   290,   290,   290,   290,   290,   290,   290,   290,
     290,   290,   290,   290,   290,   290,   290,   290,   290,   290,
     290,   290,   290,   290,   290,   290,   290,   290,   290,   290,
     290,   290,   290,   290,   290,   290,   290,   290,   290,   290,
     290,   290,   290,   290,   290,   290,   290,   290,   290,   290,
     291,   291,   291,   291,   292,   292,   292,   293,   293,   294,
     294,   294,   294,   296,   295,   295,   297,   297,   298,   299,
     299,   299,   300,   300,   300,   301,   301,   302,   302,   302,
     302,   302,   302,   302,   302,   302,   302,   302,   302,   302,
     303,   303,   303,   303,   303,   303,   304,   304,   305,   305,
     305,   305,   305,   305,   305,   306,   306,   307,   307,   308,
     308,   308,   308,   309,   309,   310,   311,   312,   314,   315,
     313,   313,   316,   316,   317,   318,   318,   319,   319,   320,
     321,   321,   322,   322,   322,   323,   323,   323,   324,   324,
     325,   325,   326,   326,   327,   327,   327,   328,   328,   329,
     329,   330,   330,   330,   330,   330,   330,   331,   331,   332,
     332,   332,   332,   332,   332,   332,   332,   333,   333,   333,
     333,   334,   334,   334,   334,   334,   334,   335,   335,   335,
     336,   336,   336,   336,   336,   336,   336,   337,   337,   338
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     1,     1,     1,     1,     4,
       3,     0,     6,     0,     5,     3,     2,     3,     1,     1,
       2,     3,     4,     1,     3,     1,     2,     3,     1,     2,
       3,     5,     4,     2,     0,     1,     1,     1,     2,     1,
       2,     3,     7,    10,     0,     6,     0,     8,     0,    10,
       0,     6,     2,     3,     2,     3,     2,     3,     3,     3,
       3,     3,     5,     5,     8,     8,     3,     3,     3,     3,
       5,     1,     1,     0,     9,     0,     9,     5,    13,     3,
       3,     9,     0,     1,     3,     1,     1,     0,     1,     0,
      11,     0,     8,     0,     0,     9,     0,     7,     0,     6,
       1,     2,     2,     2,     0,     2,     0,     2,     0,     1,
       3,     1,     3,     2,     0,     1,     2,     1,     4,     1,
       4,     1,     4,     1,     4,     3,     5,     3,     4,     4,
       5,     5,     4,     0,     1,     1,     6,     0,     7,     0,
       2,     0,     3,     0,     1,     0,     2,     3,     5,     4,
       4,     5,     7,     6,     1,     1,     1,     1,     0,     1,
       0,     1,     1,     2,     3,     3,     4,     3,     1,     1,
       2,     4,     3,     5,     1,     3,     3,     5,     1,     3,
       2,     0,     2,     0,     0,     4,     0,     5,     2,     0,
      10,     0,     4,     3,     3,     3,     5,     2,     2,     0,
       6,     5,     4,     3,     1,     1,     0,     4,     4,     1,
       1,     1,     1,     1,     1,     1,     4,     1,     1,     3,
       2,     0,     0,     3,     0,     1,     3,     1,     1,     1,
       1,     3,     4,     4,     4,     1,     1,     2,     2,     2,
       3,     3,     1,     1,     1,     1,     3,     1,     1,     1,
       0,     1,     2,     1,     1,     1,     1,     1,     1,     3,
       5,     1,     3,     5,     4,     3,     1,     1,     0,     3,
       1,     6,     3,     4,     6,     3,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       2,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       2,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     5,     4,     1,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     1,     4,     3,     2,     0,    11,
       4,     1,     4,     0,     3,     4,     1,     2,     4,     1,
       0,     4,     0,     0,     8,     1,     0,     0,     5,     0,
       2,     0,     1,     1,     3,     1,     3,     1,     1,     0,
       4,     0,     4,     1,     0,     4,     0,     4,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       4,     4,     6,     6,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     5,     1,     2,     0,     2,     2,
       3,     0,     0,     1,     1,     3,     0,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     2,
       1,     1,     2,     2,     4,     1,     3,     3,     1,     1,
       1,     1,     3,     3,     3,     2,     0,     1,     0,     5,
       3,     3,     1,     1,     1,     1,     1,     1,     0,     0,
       7,     1,     2,     0,     3,     3,     0,     1,     2,     3,
       1,     1,     1,     2,     1,     4,     4,     1,     1,     4,
       1,     0,     1,     1,     4,     4,     1,     1,     3,     1,
       2,     2,     3,     6,     0,     1,     4,     2,     0,     5,
       3,     3,     1,     6,     4,     4,     2,     2,     2,     1,
       2,     1,     4,     3,     3,     6,     3,     1,     1,     1,
       4,     4,     2,     2,     4,     2,     2,     1,     3,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       4,     0,     2,     1,   158,   158,     0,   158,   158,   158,
       0,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     158,   158,   158,     0,     0,   158,     0,   471,     0,   477,
     478,    23,   499,   538,    72,   479,   158,    46,     0,     0,
       0,     0,     0,   158,     0,   158,     0,   158,     0,   158,
       0,     0,     0,     0,   455,     0,     0,     0,     0,   100,
       0,     0,   155,   483,   485,   486,   480,   481,     0,     0,
     487,   482,     0,   158,   156,     0,   484,   158,    71,    34,
     549,   472,     0,     0,     3,    25,   498,   457,     0,     5,
      39,     6,     7,     8,     0,   157,     0,   514,   341,   531,
       0,   454,   501,   334,     0,   513,     0,   515,     0,   534,
     521,   530,   532,   537,     0,   324,   500,    23,   455,     0,
       0,   157,     0,   586,   515,   585,   158,   583,   582,   337,
     422,   421,   418,   420,   419,   438,   440,   439,   410,   400,
     416,   415,   379,   387,   388,   390,   389,   378,   409,   393,
     391,   392,   394,   395,   396,   397,   398,   399,   401,   402,
     403,   404,   405,   406,   408,   407,   380,   381,   382,   384,
     385,   386,   424,   425,   434,   433,   432,   431,   430,   429,
     417,   435,   426,   427,   428,   411,   412,   413,   414,   436,
     437,   441,   443,   442,   444,   445,   423,   447,   446,   383,
     448,   449,   359,   368,   308,   309,   310,   311,   333,   331,
     330,   329,   328,   327,   326,   325,    23,   458,     0,     0,
     291,   517,   289,   276,   462,     0,     0,   460,    28,   459,
       0,   476,   461,   465,   532,     0,   158,   332,   158,    40,
       0,   266,   158,   158,   158,   158,     0,   158,    52,     0,
       0,    54,     0,     0,    56,   514,     0,   515,    34,     0,
       0,     0,    18,    19,   169,     0,     0,   168,   102,   101,
     174,     0,     0,     0,     0,     0,    96,   554,   158,   571,
       0,   489,   158,     0,     0,   569,     0,    13,     0,    26,
       0,   514,   515,    98,     0,   158,   158,   473,     0,   474,
       0,     0,     0,     0,   158,     0,    16,   104,   104,   178,
       0,    88,    87,     0,   158,   158,   158,   158,   158,   158,
     158,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     158,   158,   158,   158,   158,   158,   158,   158,   158,     0,
     158,    38,   290,   288,   158,   158,   158,   158,   158,   158,
     158,   158,   158,   158,   158,   158,   158,     0,   158,   158,
     550,   533,   554,    87,   158,     0,   369,   371,   349,     0,
       0,     0,     0,    29,     0,   158,   275,     0,   533,   469,
       0,     0,   158,    69,     0,     0,     0,   267,   270,   514,
     515,     0,     0,     0,    53,    80,    55,     0,    57,    58,
     158,    79,    20,     0,    15,     0,   158,   170,   515,     0,
      66,     0,     0,    67,     0,    83,    85,   587,     0,     0,
       0,   108,     0,   555,     0,     0,   562,     0,   508,     0,
       0,   488,   570,   499,     0,     0,   568,   504,   567,    27,
       4,    10,    11,    59,    60,    61,     0,   321,    41,    33,
      35,    36,    37,     0,   336,   502,   503,    24,     0,     0,
     159,   514,   515,     0,     0,    91,    93,   158,     0,    68,
      86,     0,   589,   529,   527,     0,   294,   296,   295,   158,
       0,   292,   293,   297,   299,   298,   313,   312,   315,   314,
     316,   318,   319,   317,   307,   306,   301,   302,   300,   303,
     304,   305,   320,   540,     0,     0,   158,   272,   287,   286,
     285,   284,   283,   282,   281,   280,   279,   278,   277,     0,
       0,     0,     0,     0,     0,   584,     0,     0,   348,   352,
     350,     0,   362,   373,     0,    30,   529,     0,     0,   470,
     158,   265,     0,    44,   158,   158,     0,     0,     0,     0,
     158,    50,     0,     0,     0,     0,     0,   491,     0,   490,
      32,   495,     0,     0,    17,    21,     0,   167,   175,   172,
       0,     0,     0,   580,   581,     9,     0,     0,   554,   551,
       0,   566,   516,   158,   335,   158,   557,   577,   579,   578,
       0,   573,   158,   574,   576,   158,     4,   181,   539,   163,
     450,   158,     0,   103,   106,   106,   179,   176,    89,   338,
     158,   158,   528,   323,   158,   340,     0,   273,   514,   515,
     451,   547,   158,   543,   526,   542,   546,   535,   536,     0,
     370,   372,   361,   356,   357,   374,   376,   475,   467,    34,
     137,   158,   158,     0,   269,   114,     0,   114,   115,   125,
       0,    34,   123,    77,     0,   492,   493,   506,     0,     0,
       0,     0,    22,   171,     0,    84,    70,   588,   107,   109,
     181,     0,     0,   552,   158,     0,   561,     0,   560,   572,
       0,    14,   158,   250,     0,   514,   515,    31,     0,     0,
       0,   158,     0,   158,     0,     0,   322,   476,    62,    63,
       0,   158,   519,   158,   158,   158,     0,   355,   351,     0,
       0,     0,   464,   139,   141,     0,    34,   121,    45,   158,
       0,     0,   116,     0,     0,   158,   133,   133,    51,   512,
       0,   508,   497,   496,     0,   173,     0,   250,   556,   554,
     158,   271,   565,   564,   158,     0,    12,     0,     0,   253,
     254,   255,   258,   257,   256,   248,   191,     0,     0,    99,
     180,   184,   158,   247,   251,     0,   166,   105,   181,    94,
     177,   158,   154,   155,   156,     0,   144,     0,   452,   453,
     274,   548,     0,   523,     0,     0,     0,   365,   158,   367,
     360,   363,   158,   358,   375,   377,     0,   466,   143,     0,
     158,    42,     0,   158,     0,   113,    75,    73,   126,     0,
     133,     0,   133,     0,     0,   494,   507,   505,     0,   110,
      97,     0,   514,   515,     0,   559,   575,     0,     0,   111,
       0,   227,     0,   225,   229,   230,     0,     0,   228,     0,
       0,   186,   252,     0,   188,   250,   183,     0,   343,   158,
       0,   146,   525,   520,   544,   545,   353,     0,     0,   468,
       0,     0,     0,   158,   140,    47,     0,    48,   158,   158,
     124,     0,     0,   158,     0,     0,   127,   511,   510,     0,
     553,    64,    65,   563,     0,     0,   195,   199,   211,   213,
     210,   217,   212,   215,   458,     0,     0,   205,     0,   214,
       0,   193,   242,   243,   244,   235,     0,   236,   194,   261,
       0,    87,     0,     0,    92,   250,     0,     0,     0,     0,
     147,     0,     0,   522,   356,   366,   364,   158,    34,     0,
       0,   122,   158,    34,   119,    76,    74,     0,   129,     0,
     134,   135,    34,   128,     0,     0,   264,   112,     0,     0,
     206,   192,   221,   226,     0,     0,   231,   238,   239,   237,
       0,     0,   185,     0,     0,     0,    95,   182,    34,     0,
      34,     0,   150,     0,   149,   526,   354,     0,   142,    43,
     158,    34,   117,    49,   158,   130,    34,   132,   509,    34,
      23,   196,     0,   197,   198,     0,     0,   218,     0,     0,
     224,   240,   241,   233,   234,   232,   262,   259,     0,   187,
     263,   158,     0,   346,     0,   158,   151,     0,   148,   524,
       0,   136,   158,     0,   131,   158,     0,   250,     0,   216,
     207,   220,   222,   208,     0,   189,    90,   347,     0,   342,
     339,     0,   153,    34,     0,   120,    82,   203,     0,   249,
     219,     0,   260,   158,     0,   344,   152,   138,   118,    78,
       0,     0,   202,   223,     0,   345,     0,     0,   201,     0,
       0,   200,   245,    34,   190,     0,   158,     0,   246,     0,
      34,   158,    81
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    84,   596,   440,   261,   262,    85,    86,
      87,    88,   295,   449,   450,    90,   642,   242,   932,   654,
     869,   868,  1059,   414,   415,   471,   312,   451,   692,   452,
     604,   605,   846,   421,    93,   446,    94,   465,   689,   577,
     668,   828,   721,   647,   983,   935,   718,   653,   392,   728,
     811,   942,   714,   798,   801,   862,   775,   776,   121,   122,
     459,   460,   266,   267,   271,   310,   683,   915,   760,   839,
     912,  1053,   830,   948,   993,   994,   995,   896,   998,   897,
     898,   996,  1000,  1033,  1051,   832,   833,   837,   905,   906,
     907,  1074,   761,   762,   763,   764,   910,   765,   240,   386,
     387,    97,   693,   918,  1014,    98,   369,   633,   632,   924,
     708,   370,   709,   706,   531,   793,   790,   202,   526,   527,
     532,   710,   711,   203,    99,   100,   101,   231,   232,   377,
     712,   797,   237,   298,   376,   102,   560,   561,   103,   730,
     586,   731,   104,   105,   581,   106,   124,   357,   783,   853,
     923,   702,   108,   109,   110,   111,   112,   113,   504,   624,
     625,   626,   114,   424,   427,   428,   284,   285,   590,   115,
     418,   116
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -747
static const yytype_int16 yypact[] =
{
    -747,   112,  1939,  -747,  6967,  6967,   -71,  6967,  6967,  6967,
    7513,  6967,  6967,  6967,  6967,  6967,  6967,  6967,  6967,  6967,
    6967,  6967,  6967,   353,   353,  6967,   508,   -40,   100,  -747,
    -747,   288,  -747,  -747,  -747,  -747,  6967,  -747,   102,   131,
     141,   151,   167,  5157,   139,  5285,   266,  5413,   179,  6967,
     121,   -39,   242,   275,   338,   262,   265,   268,   270,  -747,
     386,   302,   304,  -747,  -747,  -747,  -747,  -747,   446,   153,
    -747,  -747,   395,  5541,   327,   399,  -747,  6967,  -747,  -747,
     314,   334,   343,   343,  -747,   -63,   328,  -747,    21,  -747,
    -747,  -747,  -747,  -747,    14,   422,   402,  -747,  -747,  -747,
     361,  -747,  -747,  -747,  6255,  -747,    24,  1946,   348,  -747,
     387,  -747,    92,  -747,    -1,  -747,  -747,   428,  -747,   375,
     384,  -747,   402,  1860,  4851,  1860,  6967,  1860,  1860,  6114,
    -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,
    -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,
    -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,
    -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,
    -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,
    -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,
    -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,
    -747,  -747,   371,  -747,   486,   486,   354,   486,   486,   486,
     486,   486,   486,   486,   486,   486,  -747,  -747,   328,   412,
    -747,  -747,  -747,  -747,   418,   417,   395,   327,   419,   426,
     429,   423,  -747,   454,    19,    -1,  5669,  -747,  6967,  -747,
      23,  1860,  4499,  6967,  5797,  6967,   524,  6967,  -747,  6511,
     447,  -747,  6767,   597,  -747,   453,  1860,   944,  -747,  7023,
     395,    27,  -747,   152,  -747,   347,    29,  -747,  -747,  -747,
     600,    30,   353,   353,   353,   462,  -747,   379,  4645,   189,
     271,  -747,  7095,   353,   477,  -747,   395,  -747,   236,   -62,
     465,   466,  1166,  -747,  7650,  2323,  6967,   291,   473,   433,
     291,   217,   182,   566,  4773,   568,  -747,   522,   522,   634,
      31,  -747,   619,    -7,  6967,  6967,  6967,  5925,  6967,  6967,
    6967,  6967,  6967,  6967,  6967,  6967,  6967,  6967,  6967,  6967,
    6967,  6967,  6967,  6967,  6967,  6967,  6967,  6967,  6967,   508,
    6053,  -747,  -747,  -747,  4901,  6967,  6967,  6967,  6967,  6967,
    6967,  6967,  6967,  6967,  6967,  6967,  4773,   530,  6053,  6967,
     314,   -29,   379,   619,  6199,  7691,  -747,  -747,  -747,   616,
    7259,   191,   395,   419,    91,  4773,  -747,   535,    63,  -747,
    7732,  7785,  6967,  -747,   580,  7826,   504,   660,  1860,   596,
    1390,   676,    44,  7867,  -747,  -747,  -747,  1564,  -747,  -747,
    2451,  -747,   196,   121,  -747,   621,  6967,  -747,  -747,   -39,
    -747,  1564,   618,  -747,    45,  -747,  -747,  -747,    46,   536,
     534,   577,   540,  -747,    48,   353,  8055,   542,   690,   439,
     630,  -747,  -747,   641,   105,   544,  -747,  -747,  -747,   245,
    -747,  -747,  -747,  -747,  -747,  -747,   546,  -747,  -747,  -747,
    -747,  -747,  -747,  1725,  -747,  -747,  -747,  -747,   353,   549,
     701,    49,   154,   707,   258,  -747,  -747,  6967,   649,  -747,
    -747,     8,   569,   571,    63,    -1,  8194,  7248,  6114,  6967,
    8153,  6643,  5090,  5345,  1163,  5855,  6895,  6895,  6895,  6895,
    5601,  5601,  5601,  5601,   801,   801,   620,   620,   620,   354,
     354,   354,  -747,  1860,   565,   221,  6967,  6114,  6114,  6114,
    6114,  6114,  6114,  6114,  6114,  6114,  6114,  6114,  6114,   575,
     183,   570,  1766,    51,   578,  -747,  7513,  7513,  -747,  -747,
    -747,   723,   215,  -747,   569,   419,  -747,   582,   183,  -747,
    3859,  1860,   587,  -747,  5797,  6967,   353,   165,  1564,   674,
    3987,  -747,  1564,  1564,   598,   143,   612,  -747,   614,  -747,
    -747,  -747,   654,   686,  -747,  -747,  4701,  -747,  -747,   745,
     353,   602,   353,  -747,  -747,  -747,   258,   603,   379,   416,
     747,  -747,  -747,  6327,  -747,  5029,  -747,  -747,  -747,  -747,
     615,  -747,  6967,  -747,  -747,  2067,  -747,  -747,  -747,  -747,
    -747,  6455,  1564,  -747,   642,   642,  1860,   751,  -747,  -747,
    4773,  4773,    63,  6388,  6967,  -747,   508,  -747,   611,  1276,
    -747,  -747,  6967,  -747,   623,    65,  -747,  -747,  -747,   763,
    -747,  -747,  -747,   632,  -747,  -747,  -747,  -747,  -747,  -747,
    -747,  6967,  4115,   624,  1860,   662,   353,   662,  -747,  -747,
     772,  -747,  -747,  -747,    62,  -747,  -747,  1564,   650,   715,
     718,   635,  -747,  -747,  1564,  -747,  -747,  -747,   783,  -747,
    -747,    54,   636,  -747,  6583,   353,  1860,   353,  8096,  -747,
      64,  -747,  2195,   523,   353,    57,   424,  -747,   258,   637,
     644,  6967,   638,   247,   653,   655,  6388,   423,  -747,  -747,
    4957,  4773,  -747,  6053,  6967,  6967,    86,  -747,  -747,   156,
    7513,  7513,   673,  2579,    53,  7920,  -747,  -747,  -747,  6711,
     165,   658,  -747,   659,  1564,  2707,   643,   648,  -747,   696,
     671,   800,  -747,  -747,   258,  -747,   258,  1354,  -747,   379,
    6967,  6114,  -747,  -747,  6839,   651,  -747,   749,   258,  -747,
    -747,  -747,  -747,  -747,  -747,  -747,  -747,   680,   116,  -747,
    -747,  -747,   211,   717,  -747,    32,  -747,   783,  -747,  -747,
    1860,   247,  -747,  -747,  -747,   675,   824,    56,  -747,  -747,
    -747,  -747,   678,  -747,   670,  5213,  7386,  -747,  6967,  -747,
    -747,  -747,  6967,  -747,  -747,  -747,   183,  -747,   312,   681,
    4499,  -747,   693,  2835,   679,  -747,  -747,  -747,  -747,   694,
    -747,   341,  -747,   -43,  1564,  -747,  1564,  -747,   766,  -747,
    -747,    60,   695,  1366,   353,  1860,  -747,   827,    25,  -747,
     319,  -747,    34,  -747,  -747,  -747,   176,   698,  -747,   782,
     402,  -747,  -747,   788,  -747,  1511,  -747,   702,   757,   211,
     791,   852,  -747,   748,  -747,  -747,  -747,  5469,  5725,  -747,
     711,   844,   805,  6967,  -747,  -747,   720,  -747,  4243,  4243,
    -747,   443,   729,  6967,    35,   175,  -747,  -747,   767,   732,
    -747,  -747,  -747,  -747,  1564,   258,  -747,  -747,  -747,  -747,
    -747,  -747,  -747,  -747,    36,   733,    38,  -747,  7513,  -747,
     680,  -747,  -747,  -747,  -747,  -747,    47,   509,  -747,   879,
      39,   619,   782,   881,  -747,  1570,   735,   739,   737,    90,
     886,  1564,   183,  -747,   632,  -747,  -747,  6967,  -747,   742,
    7961,  -747,  4371,  -747,  -747,  -747,  -747,   743,  -747,  5981,
    -747,  -747,  -747,  -747,  1564,   744,  -747,  -747,   190,   461,
    -747,  -747,   436,  -747,   176,   176,   601,  -747,  -747,  -747,
    1564,   830,  -747,   835,    40,  1564,  -747,  -747,  -747,   273,
    -747,   834,   895,  1564,  -747,   623,  -747,  8002,  2579,  -747,
    4499,  -747,  -747,  -747,  2963,  -747,  -747,  2579,  -747,  -747,
     819,  -747,   770,  -747,  -747,   821,    20,  -747,   319,  1564,
     861,   884,  -747,  -747,  -747,  -747,  -747,   901,   758,  -747,
    -747,  3091,   843,  -747,    61,  3219,   904,  1564,  -747,  -747,
     894,  -747,  3347,   762,  2579,  3475,   851,   775,   461,  -747,
    -747,  -747,  -747,  -747,  1564,  -747,  -747,  -747,   297,  -747,
    -747,  1564,  -747,  -747,   765,  -747,  -747,   771,   854,   606,
    -747,   774,  -747,   247,   855,  -747,  -747,  2579,  -747,   829,
     258,   773,  -747,  -747,   776,  -747,   779,    41,  -747,   228,
     258,  -747,  -747,  -747,  -747,   856,  3603,   785,  -747,   777,
    -747,  3731,  -747
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -747,  -747,  -413,  -747,  -747,  -747,  -747,   537,    -9,   494,
     194,  -747,  -238,  -747,     3,  -747,  -747,  -747,  -747,  -747,
    -747,  -747,  -747,  -747,   363,  -352,  -116,     1,  -747,     5,
    -747,  -747,  -747,  -747,  -747,  -747,  -747,   633,   339,  -747,
     257,  -114,   300,   229,  -747,    79,  -747,  -747,  -747,  -747,
    -444,    11,  -747,  -747,  -747,  -747,  -746,  -747,     6,    28,
    -332,  -747,  -747,   545,  -747,  -747,  -612,  -747,    55,  -747,
    -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,   -45,
    -747,  -747,  -747,  -747,  -747,  -747,    69,  -747,   213,  -501,
    -747,  -747,  -747,   -55,   -54,  -744,    67,  -747,  -747,  -518,
    -747,   -37,  -747,  -747,  -747,   269,  -747,  -747,  -747,  -747,
      50,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,
      82,  -747,  -747,  -369,  -747,   203,  -449,  -316,  -747,  -747,
    -747,  -747,  -747,  -747,   280,   403,   710,  -747,  -747,  -747,
     250,  -747,  1234,   722,  -440,   498,    -2,  -747,  -747,  -747,
    -747,    13,  -304,  -747,  -747,   -14,   -24,  -747,  -345,  -522,
    -747,  -747,   -22,  -348,  -747,  -747,   595,   358,  -747,  -747,
    -747,  -747
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -559
static const yytype_int16 yytable[] =
{
     107,   533,   234,    91,   235,    89,   363,    92,    95,   473,
     255,   524,   233,   521,   523,   603,   638,   228,   599,   842,
     400,   221,   221,   502,   519,   847,   643,   595,  1028,   305,
      96,   382,   358,   885,   264,   403,   291,   409,   412,   468,
     843,   263,   900,   537,  -209,   257,   950,   961,   961,   885,
     873,   874,   549,   570,   572,   954,   579,  -161,   737,   579,
     288,   940,   579,   289,   472,  -164,    33,   473,   579,  1038,
     536,   292,    33,   314,   315,   316,   955,   -28,   -29,   608,
     358,   303,   303,   342,   343,   307,   126,   850,   726,   317,
     361,   318,   319,   320,   321,   322,   323,   324,   325,   326,
     327,   328,   329,   330,   331,   332,   333,   334,   335,   336,
     337,   338,     3,   339,   314,   315,   316,   236,   876,   799,
     800,   971,   786,   265,   358,   340,   703,   669,  -528,   851,
     317,   359,   318,   319,   320,   321,   322,   323,   324,   325,
     326,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,   358,   339,    80,   845,   630,   631,  -456,
     308,   360,  -162,   972,    33,   609,   340,   364,   345,   346,
     347,   348,   349,   350,   351,   352,   353,   354,   355,   359,
     306,  1029,   383,   682,   886,   887,   404,   834,   410,   413,
     469,   844,   216,   901,   941,  -209,   646,   951,   962,  1009,
    1071,   804,   550,   571,   573,   956,   580,  -161,   389,   629,
     250,   378,   738,  -517,  -517,  -164,   623,   373,   880,  1039,
     229,   658,   727,   359,   216,   704,   219,   219,   745,   230,
     671,   835,  -456,   787,   623,   742,   216,   743,    33,   669,
     107,   635,   405,   390,   766,   384,   788,   902,    95,  -527,
     429,   402,   359,    80,   621,   279,    33,   238,   636,   243,
     436,   990,   534,   408,    33,   260,   593,   461,   873,   874,
     416,   417,   419,   836,   859,   423,   118,   439,   694,   695,
     281,   435,   772,   813,   616,   818,   563,   819,   244,   474,
     279,   475,   216,   107,    33,   436,   303,   286,   245,   829,
     697,    95,   462,   791,  1012,   842,   120,  1064,   246,    72,
     430,   217,  -162,   287,   239,   234,   792,   235,   772,   461,
     282,   283,   903,    96,   247,   233,   904,    80,  1054,   216,
     228,   225,   118,   836,   226,   773,   943,   253,   461,   258,
     303,   794,   795,   622,   279,    80,  1013,   474,   456,   475,
     474,   991,   475,    80,   462,   282,   283,   774,   784,   268,
     423,  -154,   120,   535,   279,    72,   871,   217,   875,   782,
    1055,   773,   888,   462,   889,   890,   891,   892,   860,   861,
     303,   899,   455,    80,   883,   -30,  -154,  1072,  1073,   303,
     216,   821,   269,   774,   263,   441,   442,   366,   107,   225,
     975,   713,   226,   339,   217,  -145,    95,   279,   431,   282,
     283,   270,   297,   725,   367,   340,   279,   368,   216,   272,
      33,   300,   273,   582,   216,   274,    33,   275,    96,   282,
     283,   893,  -165,   872,   873,   874,   947,   364,   345,   346,
     347,   348,   349,   350,   351,   352,   353,   354,   355,   999,
     216,   612,    33,  1001,  1002,   228,   582,   276,   118,   277,
     225,   278,   635,   226,   118,   894,   216,  -458,   219,   618,
     293,   895,   282,   283,   296,   219,   219,   219,   803,   636,
     219,   282,   283,  -517,  -517,   304,   219,   216,   120,    33,
     118,    72,   623,   217,   120,   309,   474,    72,   475,   217,
     311,   313,   422,   617,   619,   356,   279,   406,  -518,    80,
     587,   436,   588,   589,   474,    80,   475,   218,   218,   279,
     120,   220,   222,    72,   280,   217,  -154,   118,   286,   533,
      29,    30,   362,   229,   957,   937,   873,   874,   107,   672,
      35,    80,   230,   640,   645,   648,    95,   340,   107,   899,
     279,   958,   371,   652,   959,   436,    95,   120,  -455,   963,
      72,   372,   217,   303,   685,   219,  -457,   228,   416,   374,
     667,   282,   283,   461,   461,  -463,   423,   673,    80,   216,
     375,    33,  -165,   281,   282,   283,    63,    64,    65,    66,
      67,   558,   234,   107,   235,   391,    91,   555,    89,   686,
      92,    95,   233,    70,    71,   558,   395,   228,   462,   462,
     397,   829,   398,   411,   437,   282,   283,    76,   623,   224,
     420,  1075,   747,    96,   443,   444,  1003,   748,   219,   749,
     750,   751,   752,   753,   754,   755,   454,   457,   432,   463,
     107,   464,   438,  1004,   722,   717,  1005,   467,    95,   225,
     470,   520,   226,   528,   227,   432,   538,   438,   432,   438,
     438,   219,   542,   544,   461,   336,   337,   338,   545,   339,
      80,   756,   757,   582,   758,   582,   299,   301,   302,   228,
     107,   340,   582,    91,   759,    89,   546,    92,    95,   548,
     978,   569,   565,   575,   574,   984,   576,   578,   585,   462,
     584,   591,   592,   822,   987,   594,   597,   600,   219,   601,
      96,   107,   749,   750,   751,   752,   753,   754,   648,    95,
     602,   777,   607,   107,   911,   228,   610,   228,   611,   615,
    1011,    95,  1015,   620,   627,   609,   634,   423,   823,   228,
     637,    96,   558,  1022,   641,   650,   558,   558,  1024,   219,
     219,  1025,   659,    96,   660,   657,   661,   662,   664,   218,
     674,   666,   688,   670,   691,  1062,   218,   218,   218,   841,
     698,   218,   474,   219,   475,   219,   705,   218,   707,   679,
     701,   219,   219,   719,   720,   724,   732,   431,   772,   733,
     840,   736,   734,   739,   796,   771,   558,   768,   107,   777,
     559,   107,   810,   864,   769,  1057,    95,   812,   816,    95,
     229,   778,   826,   779,   559,  -249,   806,   807,   814,   230,
     827,   228,   582,   749,   750,   751,   752,   753,   754,   815,
     831,    96,   849,   848,   854,  1076,   852,   867,   863,   879,
     884,   773,  1081,   333,   334,   335,   336,   337,   338,   219,
     339,   558,   865,   870,   881,   909,   218,   908,   558,   913,
     916,   917,   340,   774,   920,   921,   107,   107,   927,   922,
     928,   934,   934,   929,    95,    95,   228,   919,   219,   931,
     219,   749,   750,   751,   752,   753,   754,   219,   938,   944,
     945,   557,   960,   949,   965,   968,   969,   970,   474,   973,
     475,   979,   985,  1007,   989,   557,  1008,  1016,  1017,  -204,
    1026,  1027,  1032,   955,  1034,  1035,  1037,  1041,   558,   218,
    1043,  1045,  1047,   219,  1058,  1061,  1060,  1063,  1065,  1077,
     107,  1066,  1068,   665,  1069,   982,  1070,  1080,    95,   228,
     564,   466,   219,  1079,   690,   767,  1067,   723,   936,   805,
     986,   559,   218,  1030,   567,   559,   559,   364,   345,   346,
     347,   348,   349,   350,   351,   352,   353,   354,   355,   953,
     967,   838,  1048,  1049,   976,   789,   107,   780,   107,   964,
     952,   817,   107,  1021,    95,   107,    95,   407,  1019,   228,
      95,     0,     0,    95,     0,     0,     0,     0,     0,   218,
       0,     0,     0,  -517,  -517,   559,    96,     0,   558,   107,
     558,     0,    96,   107,     0,    96,     0,    95,     0,     0,
     107,    95,   107,   107,     0,     0,     0,   219,    95,     0,
      95,    95,     0,     0,     0,     0,     0,     0,     0,    96,
     218,   218,   557,    96,     0,     0,   557,   557,     0,     0,
      96,   228,    96,    96,     0,   107,     0,     0,     0,     0,
     559,   228,     0,    95,   218,     0,   218,   559,     0,     0,
       0,     0,   218,   218,   107,     0,     0,     0,   558,   107,
       0,   777,    95,     0,     0,    96,     0,    95,     0,     0,
       0,     0,     0,     0,     0,     0,   557,     0,     0,     0,
       0,     0,     0,   399,    96,     0,     0,     0,     0,    96,
       0,     0,     0,     0,     0,   558,     0,     0,     0,     0,
       0,   568,     0,     0,     0,     0,     0,   559,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   558,     0,
     218,     0,   992,     0,     0,     0,     0,     0,     0,     0,
       0,   557,     0,     0,   558,     0,     0,     0,   557,   558,
       0,     0,     0,     0,     0,     0,     0,   558,     0,   218,
       0,   218,     0,     0,     0,     0,     0,     0,   218,   364,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,     0,     0,   558,   322,   323,   324,   325,   326,   327,
     328,   329,   330,   331,   332,   333,   334,   335,   336,   337,
     338,   558,   339,     0,   218,     0,     0,   559,   557,   559,
       0,     0,     0,     0,   340,  -517,  -517,     0,   558,     0,
       0,     0,     0,   218,     0,   558,     0,     0,   123,   125,
       0,   127,   128,   129,     0,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   215,     0,   649,   223,
       0,     0,   655,   656,     0,     0,     0,     0,     0,     0,
     241,     0,     0,     0,     0,     0,     0,   249,     0,   252,
       0,   256,     0,   259,     0,     0,     0,   559,     0,   364,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,     0,     0,     0,     0,     0,     0,   256,   557,     0,
     557,   294,   687,     0,     0,     0,     0,     0,   218,     0,
       0,     0,     0,     0,   559,   445,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -517,  -517,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   559,     0,     0,
       0,     0,   997,     0,     0,     0,     0,     0,     0,     0,
     365,     0,     0,   559,     0,     0,     0,   729,   559,     0,
       0,     0,     0,     0,   735,     0,   559,     0,   557,   364,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   559,   364,   345,   346,   347,   348,   349,   350,
     351,   352,   353,   354,   355,   557,     0,     0,     0,     0,
     559,     0,     0,     0,     0,  -517,  -517,     0,     0,     0,
       0,  1050,     0,     0,   808,   699,     0,   559,   557,     0,
       0,     0,     0,     0,   559,     0,     0,     0,     0,  -517,
    -517,     0,     0,   747,   557,     0,     0,     0,   748,   557,
     749,   750,   751,   752,   753,   754,   755,   557,     0,     0,
     380,     0,   381,     0,     0,     0,     0,   385,   388,   256,
     547,   393,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   557,     0,     0,     0,     0,     0,     0,
       0,     0,   756,   757,     0,   758,     0,     0,     0,     0,
       0,   557,   426,     0,     0,   820,   434,     0,     0,     0,
       0,     0,     0,     0,   877,   882,   878,     0,   557,     0,
     453,     0,     0,     0,     0,   557,     0,     0,   256,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   476,   477,
     478,   480,   481,   482,   483,   484,   485,   486,   487,   488,
     489,   490,   491,   492,   493,   494,   495,   496,   497,   498,
     499,   500,   501,     0,   503,     0,     0,     0,   507,   508,
     509,   510,   511,   512,   513,   514,   515,   516,   517,   518,
     256,     0,   503,   522,   946,     0,     0,     0,   507,     0,
       0,     0,     0,     0,     0,     0,   552,   553,     0,   256,
     747,     0,     0,     0,     0,   748,   541,   749,   750,   751,
     752,   753,   754,   755,     0,     0,     0,     0,     0,     0,
       0,   974,     0,    29,    30,   216,     0,     0,     0,     0,
     566,     0,     0,    35,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   988,     0,     0,     0,     0,   756,
     757,     0,   758,     0,     0,     0,     0,     0,     0,   747,
    1006,     0,   914,     0,   748,  1010,   749,   750,   751,   752,
     753,   754,   755,  1018,     0,     0,     0,     0,   554,    63,
      64,    65,    66,    67,     0,     0,     0,     0,     0,     0,
     555,   606,     0,     0,     0,   120,    70,    71,    72,  1031,
     556,     0,     0,   613,     0,     0,     0,     0,   756,   757,
      76,   758,     0,     0,     0,     0,     0,  1042,     0,     0,
       0,   966,     0,     0,   314,   315,   316,     0,     0,     0,
     256,     0,     0,     0,  1052,     0,     0,     0,     0,     0,
     317,  1056,   318,   319,   320,   321,   322,   323,   324,   325,
     326,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,     0,   339,   314,   315,   316,   388,   644,
       0,     0,     0,     0,     0,     0,   340,     0,     0,     0,
       0,   317,     0,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,     0,   339,     0,   676,     0,   678,
       0,     0,     0,     0,     0,     0,   680,   340,     0,     0,
       0,     0,     0,     0,     0,   256,     0,     0,     0,     0,
       0,     0,     0,     0,   256,   256,     0,     0,   696,     0,
       0,     0,     0,     0,     0,     0,   700,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   314,
     315,   316,     0,     0,     0,   715,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   317,   598,   318,   319,   320,
     321,   322,   323,   324,   325,   326,   327,   328,   329,   330,
     331,   332,   333,   334,   335,   336,   337,   338,   741,   339,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   340,     0,     0,     0,   770,     0,   628,     0,     0,
       0,     0,     0,     0,     0,   256,     0,   503,   785,   741,
       0,     0,     4,     5,     6,     7,     8,     0,     0,     0,
       0,     9,     0,   388,     0,     0,     0,     0,     0,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,     0,     0,     0,   256,    10,     0,     0,   825,     0,
       0,    11,    12,     0,     0,     0,     0,    13,     0,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
       0,    25,    26,    27,    28,  -517,  -517,     0,    29,    30,
      31,    32,    33,     0,    34,     0,     0,     0,    35,    36,
      37,    38,   857,    39,     0,    40,   858,    41,     0,     0,
      42,     0,     0,     0,    43,    44,    45,  -158,    46,    47,
      48,     0,    49,    50,    51,     0,     0,     0,    52,    53,
      54,     0,    55,    56,    57,    58,    59,    60,     0,     0,
       0,     0,    61,    62,    63,    64,    65,    66,    67,     0,
       4,     5,     6,     7,     8,    68,     0,     0,     0,     9,
      69,    70,    71,    72,    73,    74,     0,     0,     0,     0,
       0,     0,     0,    75,     0,    76,    77,   930,    78,    79,
       0,    80,    81,    10,    82,    83,     0,   939,     0,    11,
      12,     0,     0,     0,     0,    13,     0,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,     0,    25,
      26,    27,    28,     0,     0,     0,    29,    30,    31,    32,
      33,     0,    34,     0,     0,     0,    35,    36,    37,    38,
       0,    39,     0,    40,     0,    41,     0,     0,    42,     0,
       0,   977,    43,    44,    45,     0,    46,    47,    48,     0,
      49,    50,    51,     0,     0,     0,    52,    53,    54,     0,
      55,    56,    57,    58,    59,    60,     0,     0,     0,     0,
      61,    62,    63,    64,    65,    66,    67,     0,     4,     5,
       6,     7,     8,    68,     0,     0,     0,     9,    69,    70,
      71,    72,    73,    74,     0,     0,     0,     0,     0,     0,
       0,    75,     0,    76,    77,     0,    78,    79,   681,    80,
      81,    10,    82,    83,     0,     0,     0,    11,    12,     0,
       0,     0,     0,    13,     0,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,     0,    25,    26,    27,
      28,     0,     0,     0,    29,    30,    31,    32,    33,     0,
      34,     0,     0,     0,    35,    36,    37,    38,     0,    39,
       0,    40,     0,    41,     0,     0,    42,     0,     0,     0,
      43,    44,    45,     0,    46,    47,    48,     0,    49,    50,
      51,     0,     0,     0,    52,    53,    54,     0,    55,    56,
      57,    58,    59,    60,     0,     0,     0,     0,    61,    62,
      63,    64,    65,    66,    67,     0,     4,     5,     6,     7,
       8,    68,     0,     0,     0,     9,    69,    70,    71,    72,
      73,    74,     0,     0,     0,     0,     0,     0,     0,    75,
       0,    76,    77,     0,    78,    79,   746,    80,    81,    10,
      82,    83,     0,     0,     0,    11,    12,     0,     0,     0,
       0,    13,     0,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,     0,    25,    26,    27,    28,     0,
       0,     0,    29,    30,    31,    32,    33,     0,    34,     0,
       0,     0,    35,    36,    37,    38,     0,    39,     0,    40,
       0,    41,     0,     0,    42,     0,     0,     0,    43,    44,
      45,     0,     0,    47,    48,     0,    49,     0,    51,     0,
       0,     0,    52,    53,    54,     0,    55,    56,    57,     0,
      59,    60,     0,     0,     0,     0,    61,    62,    63,    64,
      65,    66,    67,     0,     4,     5,     6,     7,     8,    68,
       0,     0,     0,     9,   120,    70,    71,    72,    73,    74,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    76,
      77,     0,    78,    79,   448,    80,    81,    10,    82,    83,
       0,     0,     0,    11,    12,     0,     0,     0,     0,    13,
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,     0,    25,    26,    27,    28,     0,     0,     0,
      29,    30,    31,    32,    33,     0,    34,     0,     0,     0,
      35,    36,    37,    38,     0,    39,     0,    40,     0,    41,
       0,     0,    42,     0,     0,     0,    43,    44,    45,     0,
       0,    47,    48,     0,    49,     0,    51,     0,     0,     0,
      52,    53,    54,     0,    55,    56,    57,     0,    59,    60,
       0,     0,     0,     0,    61,    62,    63,    64,    65,    66,
      67,     0,     4,     5,     6,     7,     8,    68,     0,     0,
       0,     9,   120,    70,    71,    72,    73,    74,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    76,    77,     0,
      78,    79,   562,    80,    81,    10,    82,    83,     0,     0,
       0,    11,    12,     0,     0,     0,     0,    13,     0,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
       0,    25,    26,    27,    28,     0,     0,     0,    29,    30,
      31,    32,    33,     0,    34,     0,     0,     0,    35,    36,
      37,    38,     0,    39,     0,    40,     0,    41,     0,     0,
      42,     0,     0,     0,    43,    44,    45,  -158,     0,    47,
      48,     0,    49,     0,    51,     0,     0,     0,    52,    53,
      54,     0,    55,    56,    57,     0,    59,    60,     0,     0,
       0,     0,    61,    62,    63,    64,    65,    66,    67,     0,
       4,     5,     6,     7,     8,    68,     0,     0,     0,     9,
     120,    70,    71,    72,    73,    74,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    76,    77,     0,    78,    79,
       0,    80,    81,    10,    82,    83,     0,     0,     0,    11,
      12,     0,     0,     0,     0,    13,     0,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,     0,    25,
      26,    27,    28,     0,     0,     0,    29,    30,    31,    32,
      33,     0,    34,     0,     0,     0,    35,    36,    37,    38,
       0,    39,     0,    40,     0,    41,   809,     0,    42,     0,
       0,     0,    43,    44,    45,     0,     0,    47,    48,     0,
      49,     0,    51,     0,     0,     0,    52,    53,    54,     0,
      55,    56,    57,     0,    59,    60,     0,     0,     0,     0,
      61,    62,    63,    64,    65,    66,    67,     0,     4,     5,
       6,     7,     8,    68,     0,     0,     0,     9,   120,    70,
      71,    72,    73,    74,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    76,    77,     0,    78,    79,     0,    80,
      81,    10,    82,    83,     0,     0,     0,    11,    12,     0,
       0,     0,     0,    13,     0,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,     0,    25,    26,    27,
      28,     0,     0,     0,    29,    30,    31,    32,    33,     0,
      34,     0,     0,     0,    35,    36,    37,    38,   866,    39,
       0,    40,     0,    41,     0,     0,    42,     0,     0,     0,
      43,    44,    45,     0,     0,    47,    48,     0,    49,     0,
      51,     0,     0,     0,    52,    53,    54,     0,    55,    56,
      57,     0,    59,    60,     0,     0,     0,     0,    61,    62,
      63,    64,    65,    66,    67,     0,     4,     5,     6,     7,
       8,    68,     0,     0,     0,     9,   120,    70,    71,    72,
      73,    74,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    76,    77,     0,    78,    79,     0,    80,    81,    10,
      82,    83,     0,     0,     0,    11,    12,     0,     0,     0,
       0,    13,     0,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,     0,    25,    26,    27,    28,     0,
       0,     0,    29,    30,    31,    32,    33,     0,    34,     0,
       0,     0,    35,    36,    37,    38,     0,    39,     0,    40,
    1023,    41,     0,     0,    42,     0,     0,     0,    43,    44,
      45,     0,     0,    47,    48,     0,    49,     0,    51,     0,
       0,     0,    52,    53,    54,     0,    55,    56,    57,     0,
      59,    60,     0,     0,     0,     0,    61,    62,    63,    64,
      65,    66,    67,     0,     4,     5,     6,     7,     8,    68,
       0,     0,     0,     9,   120,    70,    71,    72,    73,    74,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    76,
      77,     0,    78,    79,     0,    80,    81,    10,    82,    83,
       0,     0,     0,    11,    12,     0,     0,     0,     0,    13,
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,     0,    25,    26,    27,    28,     0,     0,     0,
      29,    30,    31,    32,    33,     0,    34,     0,     0,     0,
      35,    36,    37,    38,     0,    39,     0,    40,     0,    41,
       0,     0,    42,     0,     0,     0,    43,    44,    45,     0,
       0,    47,    48,     0,    49,     0,    51,     0,     0,     0,
      52,    53,    54,     0,    55,    56,    57,     0,    59,    60,
       0,     0,     0,     0,    61,    62,    63,    64,    65,    66,
      67,     0,     4,     5,     6,     7,     8,    68,     0,     0,
       0,     9,   120,    70,    71,    72,    73,    74,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    76,    77,     0,
      78,    79,  1036,    80,    81,    10,    82,    83,     0,     0,
       0,    11,    12,     0,     0,     0,     0,    13,     0,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
       0,    25,    26,    27,    28,     0,     0,     0,    29,    30,
      31,    32,    33,     0,    34,     0,     0,     0,    35,    36,
      37,    38,     0,    39,     0,    40,     0,    41,     0,     0,
      42,     0,     0,     0,    43,    44,    45,     0,     0,    47,
      48,     0,    49,     0,    51,     0,     0,     0,    52,    53,
      54,     0,    55,    56,    57,     0,    59,    60,     0,     0,
       0,     0,    61,    62,    63,    64,    65,    66,    67,     0,
       4,     5,     6,     7,     8,    68,     0,     0,     0,     9,
     120,    70,    71,    72,    73,    74,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    76,    77,     0,    78,    79,
    1040,    80,    81,    10,    82,    83,     0,     0,     0,    11,
      12,     0,     0,     0,     0,    13,     0,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,     0,    25,
      26,    27,    28,     0,     0,     0,    29,    30,    31,    32,
      33,     0,    34,     0,     0,     0,    35,    36,    37,    38,
       0,    39,  1044,    40,     0,    41,     0,     0,    42,     0,
       0,     0,    43,    44,    45,     0,     0,    47,    48,     0,
      49,     0,    51,     0,     0,     0,    52,    53,    54,     0,
      55,    56,    57,     0,    59,    60,     0,     0,     0,     0,
      61,    62,    63,    64,    65,    66,    67,     0,     4,     5,
       6,     7,     8,    68,     0,     0,     0,     9,   120,    70,
      71,    72,    73,    74,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    76,    77,     0,    78,    79,     0,    80,
      81,    10,    82,    83,     0,     0,     0,    11,    12,     0,
       0,     0,     0,    13,     0,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,     0,    25,    26,    27,
      28,     0,     0,     0,    29,    30,    31,    32,    33,     0,
      34,     0,     0,     0,    35,    36,    37,    38,     0,    39,
       0,    40,     0,    41,     0,     0,    42,     0,     0,     0,
      43,    44,    45,     0,     0,    47,    48,     0,    49,     0,
      51,     0,     0,     0,    52,    53,    54,     0,    55,    56,
      57,     0,    59,    60,     0,     0,     0,     0,    61,    62,
      63,    64,    65,    66,    67,     0,     4,     5,     6,     7,
       8,    68,     0,     0,     0,     9,   120,    70,    71,    72,
      73,    74,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    76,    77,     0,    78,    79,  1046,    80,    81,    10,
      82,    83,     0,     0,     0,    11,    12,     0,     0,     0,
       0,    13,     0,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,     0,    25,    26,    27,    28,     0,
       0,     0,    29,    30,    31,    32,    33,     0,    34,     0,
       0,     0,    35,    36,    37,    38,     0,    39,     0,    40,
       0,    41,     0,     0,    42,     0,     0,     0,    43,    44,
      45,     0,     0,    47,    48,     0,    49,     0,    51,     0,
       0,     0,    52,    53,    54,     0,    55,    56,    57,     0,
      59,    60,     0,     0,     0,     0,    61,    62,    63,    64,
      65,    66,    67,     0,     4,     5,     6,     7,     8,    68,
       0,     0,     0,     9,   120,    70,    71,    72,    73,    74,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    76,
      77,     0,    78,    79,  1078,    80,    81,    10,    82,    83,
       0,     0,     0,    11,    12,     0,     0,     0,     0,    13,
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,     0,    25,    26,    27,    28,     0,     0,     0,
      29,    30,    31,    32,    33,     0,    34,     0,     0,     0,
      35,    36,    37,    38,     0,    39,     0,    40,     0,    41,
       0,     0,    42,     0,     0,     0,    43,    44,    45,     0,
       0,    47,    48,     0,    49,     0,    51,     0,     0,     0,
      52,    53,    54,     0,    55,    56,    57,     0,    59,    60,
       0,     0,     0,     0,    61,    62,    63,    64,    65,    66,
      67,     0,     4,     5,     6,     7,     8,    68,     0,     0,
       0,     9,   120,    70,    71,    72,    73,    74,     0,     0,
       0,     0,     0,     0,     0,   639,     0,    76,    77,     0,
      78,    79,  1082,    80,    81,    10,    82,    83,     0,     0,
       0,    11,    12,     0,     0,     0,     0,    13,     0,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
       0,    25,    26,    27,    28,     0,     0,     0,    29,    30,
      31,    32,    33,     0,    34,     0,     0,     0,    35,    36,
      37,    38,     0,    39,     0,    40,     0,    41,     0,     0,
      42,     0,     0,     0,    43,    44,    45,     0,     0,    47,
      48,     0,    49,     0,    51,     0,     0,     0,     0,     0,
      54,     0,    55,    56,    57,     0,     0,     0,     0,     0,
       0,     0,    61,    62,    63,    64,    65,    66,    67,     0,
       4,     5,     6,     7,     8,    68,     0,     0,     0,     9,
     120,    70,    71,    72,    73,    74,     0,     0,     0,     0,
       0,     0,     0,   651,     0,    76,    77,     0,    78,    79,
       0,    80,    81,    10,    82,    83,     0,     0,     0,    11,
      12,     0,     0,     0,     0,    13,     0,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,     0,    25,
      26,    27,    28,     0,     0,     0,    29,    30,    31,    32,
      33,     0,    34,     0,     0,     0,    35,    36,    37,    38,
       0,    39,     0,    40,     0,    41,     0,     0,    42,     0,
       0,     0,    43,    44,    45,     0,     0,    47,    48,     0,
      49,     0,    51,     0,     0,     0,     0,     0,    54,     0,
      55,    56,    57,     0,     0,     0,     0,     0,     0,     0,
      61,    62,    63,    64,    65,    66,    67,     0,     4,     5,
       6,     7,     8,    68,     0,     0,     0,     9,   120,    70,
      71,    72,    73,    74,     0,     0,     0,     0,     0,     0,
       0,   716,     0,    76,    77,     0,    78,    79,     0,    80,
      81,    10,    82,    83,     0,     0,     0,    11,    12,     0,
       0,     0,     0,    13,     0,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,     0,    25,    26,    27,
      28,     0,     0,     0,    29,    30,    31,    32,    33,     0,
      34,     0,     0,     0,    35,    36,    37,    38,     0,    39,
       0,    40,     0,    41,     0,     0,    42,     0,     0,     0,
      43,    44,    45,     0,     0,    47,    48,     0,    49,     0,
      51,     0,     0,     0,     0,     0,    54,     0,    55,    56,
      57,     0,     0,     0,     0,     0,     0,     0,    61,    62,
      63,    64,    65,    66,    67,     0,     4,     5,     6,     7,
       8,    68,     0,     0,     0,     9,   120,    70,    71,    72,
      73,    74,     0,     0,     0,     0,     0,     0,     0,   933,
       0,    76,    77,     0,    78,    79,     0,    80,    81,    10,
      82,    83,     0,     0,     0,    11,    12,     0,     0,     0,
       0,    13,     0,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,     0,    25,    26,    27,    28,     0,
       0,     0,    29,    30,    31,    32,    33,     0,    34,     0,
       0,     0,    35,    36,    37,    38,     0,    39,     0,    40,
       0,    41,     0,     0,    42,     0,     0,     0,    43,    44,
      45,     0,     0,    47,    48,     0,    49,     0,    51,     0,
       0,     0,     0,     0,    54,     0,    55,    56,    57,     0,
       0,     0,     0,     0,     0,     0,    61,    62,    63,    64,
      65,    66,    67,     0,     4,     5,     6,     7,     8,    68,
       0,     0,     0,     9,   120,    70,    71,    72,    73,    74,
       0,     0,     0,     0,     0,     0,     0,   981,     0,    76,
      77,     0,    78,    79,     0,    80,    81,    10,    82,    83,
       0,     0,     0,    11,    12,     0,     0,     0,     0,    13,
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,     0,    25,    26,    27,    28,     0,     0,     0,
      29,    30,    31,    32,    33,     0,    34,     0,     0,     0,
      35,    36,    37,    38,     0,    39,     0,    40,     0,    41,
       0,     0,    42,     0,     0,     0,    43,    44,    45,     0,
       0,    47,    48,     0,    49,     0,    51,     0,     0,     0,
       0,     0,    54,     0,    55,    56,    57,     0,     0,     0,
       0,     0,     0,     0,    61,    62,    63,    64,    65,    66,
      67,     0,     4,     5,     6,     7,     8,    68,     0,     0,
       0,     9,   120,    70,    71,    72,    73,    74,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    76,    77,     0,
      78,    79,     0,    80,    81,    10,    82,    83,     0,     0,
       0,    11,    12,     0,     0,     0,     0,    13,     0,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
       0,    25,    26,    27,    28,     0,     0,     0,    29,    30,
      31,    32,    33,     0,    34,     0,     0,     0,    35,    36,
      37,    38,     0,    39,     0,    40,     0,    41,     0,     0,
      42,     0,     0,     0,    43,    44,    45,     0,     0,    47,
      48,     0,    49,     0,    51,     0,     0,     0,     0,     0,
      54,     0,    55,    56,    57,     0,     0,     0,     0,     0,
       0,     0,    61,    62,    63,    64,    65,    66,    67,     0,
       0,     0,     0,     0,     0,    68,     0,     0,     0,     0,
     120,    70,    71,    72,    73,    74,     0,     0,     4,     5,
       6,     7,     8,     0,     0,    76,    77,     9,    78,    79,
       0,    80,    81,     0,    82,    83,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   425,     0,     0,     0,
       0,    10,     0,     0,     0,     0,     0,    11,    12,     0,
       0,     0,     0,    13,     0,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,     0,    25,    26,    27,
     314,   315,   316,     0,    29,    30,   117,    32,    33,     0,
       0,     0,     0,     0,    35,     0,   317,     0,   318,   319,
     320,   321,   322,   323,   324,   325,   326,   327,   328,   329,
     330,   331,   332,   333,   334,   335,   336,   337,   338,     0,
     339,     0,     0,     0,     0,     0,   118,     0,     0,    56,
      57,     0,   340,     0,     0,     0,     0,     0,   119,    62,
      63,    64,    65,    66,    67,     0,     4,     5,     6,     7,
       8,    68,     0,     0,     0,     9,   120,    70,    71,    72,
       0,    74,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    76,    77,  -558,   458,     0,     0,    80,    81,    10,
      82,    83,     0,     0,     0,    11,    12,     0,     0,     0,
       0,    13,     0,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,     0,    25,    26,    27,     0,     0,
       0,     0,    29,    30,   117,    32,    33,     0,     0,     0,
       0,     0,    35,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   663,     0,   364,   345,   346,   347,   348,   349,
     350,   351,   352,   353,   354,   355,     0,     0,     0,     0,
       0,     0,     0,     0,   118,     0,     0,    56,    57,     0,
       0,     0,     0,     0,     0,     0,   119,    62,    63,    64,
      65,    66,    67,     0,     4,     5,     6,     7,     8,    68,
    -517,  -517,     0,     9,   120,    70,    71,    72,     0,    74,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    76,
      77,  -160,   505,     0,     0,    80,    81,    10,    82,    83,
       0,     0,     0,    11,    12,     0,     0,     0,     0,    13,
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,     0,    25,    26,    27,   314,   315,   316,     0,
      29,    30,   117,    32,    33,     0,     0,     0,     0,     0,
      35,     0,   317,     0,   318,   319,   320,   321,   322,   323,
     324,   325,   326,   327,   328,   329,   330,   331,   332,   333,
     334,   335,   336,   337,   338,     0,   339,     0,     0,     0,
       0,     0,   118,     0,     0,    56,    57,     0,   340,     0,
       0,     0,     0,     0,   119,    62,    63,    64,    65,    66,
      67,     0,     4,     5,     6,     7,     8,    68,     0,     0,
       0,     9,   120,    70,    71,    72,   506,    74,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    76,    77,     0,
     677,     0,     0,    80,    81,    10,    82,    83,     0,     0,
       0,    11,    12,     0,     0,     0,     0,    13,     0,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
       0,    25,    26,    27,     0,     0,     0,     0,    29,    30,
     117,    32,    33,     0,     0,     0,     0,     0,    35,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   781,   320,
     321,   322,   323,   324,   325,   326,   327,   328,   329,   330,
     331,   332,   333,   334,   335,   336,   337,   338,     0,   339,
     118,     0,     0,    56,    57,     0,     0,     0,     0,     0,
       0,   340,   119,    62,    63,    64,    65,    66,    67,     0,
       4,     5,     6,     7,     8,    68,     0,     0,     0,     9,
     120,    70,    71,    72,     0,    74,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    76,    77,  -507,     0,     0,
       0,    80,    81,    10,    82,    83,     0,     0,     0,    11,
      12,     0,     0,     0,     0,    13,     0,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,     0,    25,
      26,    27,   314,   315,   316,     0,    29,    30,   117,    32,
      33,     0,     0,     0,     0,     0,    35,     0,   317,     0,
     318,   319,   320,   321,   322,   323,   324,   325,   326,   327,
     328,   329,   330,   331,   332,   333,   334,   335,   336,   337,
     338,     0,   339,     0,     0,     0,     0,     0,   118,     0,
       0,    56,    57,     0,   340,     0,     0,     0,     0,     0,
     119,    62,    63,    64,    65,    66,    67,     0,     4,     5,
       6,     7,     8,    68,     0,     0,     0,     9,   120,    70,
      71,    72,     0,    74,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    76,    77,     0,   248,     0,     0,    80,
      81,    10,    82,    83,     0,     0,     0,    11,    12,     0,
       0,     0,     0,    13,     0,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,     0,    25,    26,    27,
       0,     0,     0,     0,    29,    30,   117,    32,    33,     0,
       0,     0,     0,     0,    35,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   855,   321,   322,   323,   324,   325,
     326,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,     0,   339,     0,   118,     0,     0,    56,
      57,     0,     0,     0,     0,     0,   340,     0,   119,    62,
      63,    64,    65,    66,    67,     0,     4,     5,     6,     7,
       8,    68,     0,     0,     0,     9,   120,    70,    71,    72,
       0,    74,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    76,    77,     0,   251,     0,     0,    80,    81,    10,
      82,    83,     0,     0,     0,    11,    12,     0,     0,     0,
       0,    13,     0,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,     0,    25,    26,    27,   314,   315,
     316,     0,    29,    30,   117,    32,    33,     0,     0,     0,
       0,     0,    35,     0,   317,     0,   318,   319,   320,   321,
     322,   323,   324,   325,   326,   327,   328,   329,   330,   331,
     332,   333,   334,   335,   336,   337,   338,     0,   339,     0,
       0,     0,     0,     0,   118,     0,     0,    56,    57,     0,
     340,     0,     0,     0,     0,     0,   119,    62,    63,    64,
      65,    66,    67,     0,     4,     5,     6,     7,     8,    68,
       0,     0,     0,     9,   120,    70,    71,    72,     0,    74,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    76,
      77,     0,   254,     0,     0,    80,    81,    10,    82,    83,
       0,     0,     0,    11,    12,     0,     0,     0,     0,    13,
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,     0,    25,    26,    27,     0,     0,     0,     0,
      29,    30,   117,    32,    33,     0,     0,     0,     0,     0,
      35,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     925,     0,     0,     0,     0,     0,   290,  -559,  -559,  -559,
    -559,   331,   332,   333,   334,   335,   336,   337,   338,     0,
     339,     0,   118,     0,     0,    56,    57,     0,     0,     0,
       0,     0,   340,     0,   119,    62,    63,    64,    65,    66,
      67,     0,     4,     5,     6,     7,     8,    68,     0,     0,
       0,     9,   120,    70,    71,    72,     0,    74,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    76,    77,     0,
       0,     0,     0,    80,    81,    10,    82,    83,     0,     0,
       0,    11,    12,     0,     0,     0,     0,    13,     0,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
       0,    25,    26,    27,   314,   315,   316,     0,    29,    30,
     117,    32,    33,     0,     0,     0,     0,     0,    35,     0,
     317,     0,   318,   319,   320,   321,   322,   323,   324,   325,
     326,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,     0,   339,     0,     0,     0,     0,     0,
     118,     0,     0,    56,    57,     0,   340,     0,     0,     0,
       0,     0,   119,    62,    63,    64,    65,    66,    67,     0,
       4,     5,     6,     7,     8,    68,     0,     0,     0,     9,
     120,    70,    71,    72,     0,    74,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    76,    77,   379,     0,     0,
       0,    80,    81,    10,    82,    83,     0,     0,     0,    11,
      12,     0,     0,     0,     0,    13,     0,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,     0,    25,
      26,    27,     0,     0,     0,     0,    29,    30,   117,    32,
      33,     0,     0,     0,     0,     0,    35,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   926,   323,   324,   325,
     326,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,     0,   339,     0,     0,     0,   118,     0,
       0,    56,    57,     0,     0,     0,   340,     0,     0,     0,
     119,    62,    63,    64,    65,    66,    67,     0,     4,     5,
       6,     7,     8,    68,     0,     0,     0,     9,   120,    70,
      71,    72,     0,    74,     0,     0,     0,     0,     0,     0,
       0,   479,     0,    76,    77,     0,  -268,     0,     0,    80,
      81,    10,    82,    83,     0,     0,     0,    11,    12,     0,
       0,     0,     0,    13,     0,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,     0,    25,    26,    27,
     314,   315,   316,     0,    29,    30,   117,    32,    33,     0,
       0,     0,     0,     0,    35,     0,   317,   940,   318,   319,
     320,   321,   322,   323,   324,   325,   326,   327,   328,   329,
     330,   331,   332,   333,   334,   335,   336,   337,   338,     0,
     339,     0,     0,     0,     0,     0,   118,     0,     0,    56,
      57,     0,   340,     0,     0,     0,     0,     0,   119,    62,
      63,    64,    65,    66,    67,     0,     4,     5,     6,     7,
       8,    68,     0,     0,     0,     9,   120,    70,    71,    72,
       0,    74,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    76,    77,     0,     0,     0,     0,    80,    81,    10,
      82,    83,     0,     0,     0,    11,    12,     0,     0,     0,
       0,    13,     0,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,     0,    25,    26,    27,     0,     0,
       0,     0,    29,    30,   117,    32,    33,     0,     0,     0,
       0,     0,    35,     0,     0,     0,     0,     0,     0,   317,
     941,   318,   319,   320,   321,   322,   323,   324,   325,   326,
     327,   328,   329,   330,   331,   332,   333,   334,   335,   336,
     337,   338,     0,   339,   118,     0,     0,    56,    57,     0,
       0,     0,     0,     0,     0,   340,   119,    62,    63,    64,
      65,    66,    67,     0,     0,     0,     0,     0,     0,    68,
       0,     0,     0,     0,   120,    70,    71,    72,     0,    74,
       0,     0,     4,     5,     6,     7,     8,     0,     0,    76,
      77,     9,     0,     0,     0,    80,    81,  -541,    82,    83,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     505,     0,     0,     0,     0,    10,     0,     0,     0,     0,
       0,    11,    12,     0,     0,     0,     0,    13,     0,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
       0,    25,    26,    27,   314,   315,   316,     0,    29,    30,
     117,    32,    33,     0,     0,     0,     0,     0,    35,     0,
     317,     0,   318,   319,   320,   321,   322,   323,   324,   325,
     326,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,     0,   339,     0,     0,     0,     0,     0,
     118,     0,     0,    56,    57,     0,   340,     0,     0,     0,
       0,     0,   119,    62,    63,    64,    65,    66,    67,     0,
       4,     5,     6,     7,     8,    68,     0,     0,     0,     9,
     120,    70,    71,    72,     0,    74,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    76,    77,     0,   675,     0,
       0,    80,    81,    10,    82,    83,     0,     0,     0,    11,
      12,     0,     0,     0,     0,    13,     0,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,     0,    25,
      26,    27,     0,     0,     0,     0,    29,    30,   117,    32,
      33,     0,     0,     0,     0,     0,    35,     0,     0,     0,
       0,     0,     0,     0,   341,   318,   319,   320,   321,   322,
     323,   324,   325,   326,   327,   328,   329,   330,   331,   332,
     333,   334,   335,   336,   337,   338,     0,   339,   118,     0,
       0,    56,    57,     0,     0,     0,     0,     0,     0,   340,
     119,    62,    63,    64,    65,    66,    67,     0,     4,     5,
       6,     7,     8,    68,     0,     0,     0,     9,   120,    70,
      71,    72,     0,    74,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    76,    77,     0,   684,     0,     0,    80,
      81,    10,    82,    83,     0,     0,     0,    11,    12,     0,
       0,     0,     0,    13,     0,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,     0,    25,    26,    27,
     314,   315,   316,     0,    29,    30,   117,    32,    33,     0,
       0,     0,     0,     0,    35,     0,   317,     0,   318,   319,
     320,   321,   322,   323,   324,   325,   326,   327,   328,   329,
     330,   331,   332,   333,   334,   335,   336,   337,   338,     0,
     339,     0,     0,     0,     0,     0,   118,     0,     0,    56,
      57,     0,   340,     0,     0,     0,     0,     0,   119,    62,
      63,    64,    65,    66,    67,     0,     4,     5,     6,     7,
       8,    68,     0,     0,     0,     9,   120,    70,    71,    72,
       0,    74,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    76,    77,     0,     0,     0,     0,    80,    81,    10,
      82,    83,     0,     0,     0,    11,    12,     0,     0,     0,
       0,    13,     0,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,     0,    25,    26,    27,     0,     0,
       0,     0,    29,    30,   117,    32,    33,     0,     0,     0,
       0,     0,    35,     0,     0,     0,     0,     0,     0,     0,
     394,   319,   320,   321,   322,   323,   324,   325,   326,   327,
     328,   329,   330,   331,   332,   333,   334,   335,   336,   337,
     338,     0,   339,     0,   118,     0,     0,    56,    57,     0,
       0,     0,     0,     0,   340,     0,   119,    62,    63,    64,
      65,    66,    67,     0,     4,     5,     6,     7,     8,    68,
       0,     0,     0,     9,   120,    70,    71,    72,   740,    74,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    76,
      77,     0,     0,     0,     0,    80,    81,    10,    82,    83,
       0,     0,     0,    11,    12,     0,     0,     0,     0,    13,
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,     0,    25,    26,    27,   314,   315,   316,     0,
      29,    30,   117,    32,    33,     0,     0,     0,     0,     0,
      35,     0,   317,     0,   318,   319,   320,   321,   322,   323,
     324,   325,   326,   327,   328,   329,   330,   331,   332,   333,
     334,   335,   336,   337,   338,     0,   339,     0,     0,     0,
       0,     0,   118,     0,     0,    56,    57,     0,   340,     0,
       0,     0,     0,     0,   119,    62,    63,    64,    65,    66,
      67,     0,     4,     5,     6,     7,     8,    68,     0,     0,
       0,     9,   120,    70,    71,    72,     0,    74,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    76,    77,  -268,
     824,     0,     0,    80,    81,    10,    82,    83,     0,     0,
       0,    11,    12,     0,     0,     0,     0,    13,     0,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
       0,    25,    26,    27,     0,     0,     0,     0,    29,    30,
     117,    32,    33,     0,     0,     0,     0,     0,    35,     0,
       0,     0,     0,     0,     0,     0,   396,  -559,  -559,  -559,
    -559,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,     0,   339,     0,     0,     0,     0,     0,
     118,     0,     0,    56,    57,     0,   340,     0,     0,     0,
       0,     0,   119,    62,    63,    64,    65,    66,    67,     0,
       4,     5,     6,     7,     8,    68,     0,     0,     0,     9,
     120,    70,    71,    72,     0,    74,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    76,    77,     0,     0,     0,
       0,    80,    81,    10,    82,    83,     0,     0,     0,    11,
      12,     0,     0,     0,     0,    13,     0,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,     0,    25,
      26,    27,   314,   315,   316,     0,    29,    30,   117,    32,
      33,     0,     0,     0,     0,     0,    35,     0,   317,     0,
     318,   319,   320,   321,   322,   323,   324,   325,   326,   327,
     328,   329,   330,   331,   332,   333,   334,   335,   336,   337,
     338,     0,   339,     0,     0,     0,     0,     0,   118,     0,
       0,    56,    57,     0,   340,     0,     0,     0,     0,     0,
     119,    62,    63,    64,    65,    66,    67,     0,     4,     5,
       6,     7,     8,    68,     0,     0,     0,     9,   120,    70,
      71,    72,     0,    74,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    76,    77,     0,     0,     0,     0,    80,
      81,    10,    82,    83,     0,     0,     0,    11,    12,     0,
       0,     0,     0,    13,     0,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,     0,    25,    26,    27,
       0,     0,     0,     0,    29,    30,   117,   433,    33,     0,
       0,     0,     0,     0,    35,     0,     0,     0,     0,     0,
       0,     0,   401,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   118,     0,     0,    56,
      57,     0,     0,     0,     0,     0,     0,     0,   119,    62,
      63,    64,    65,    66,    67,     0,     0,     0,     0,     0,
       0,    68,     0,     0,     0,     0,   120,    70,    71,    72,
       0,    74,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    76,    77,     0,     0,     0,     0,    80,    81,   316,
      82,    83,   130,   131,   132,   133,   134,     0,   135,   136,
     137,   138,     0,   317,     0,   318,   319,   320,   321,   322,
     323,   324,   325,   326,   327,   328,   329,   330,   331,   332,
     333,   334,   335,   336,   337,   338,   529,   339,     0,     0,
       0,     0,     0,     0,     0,   530,     0,     0,   139,   340,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   140,   141,   142,   143,   144,   145,   146,     0,     0,
     147,     0,     0,     0,     0,     0,     0,     0,     0,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
       0,     0,   189,   190,   191,   192,   193,   194,   195,   130,
     131,   132,   133,   134,     0,   135,   136,   137,   138,     0,
     196,   197,   198,     0,   199,     0,     0,     0,     0,     0,
       0,     0,     0,   200,     0,   201,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   856,     0,     0,   139,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   140,   141,
     142,   143,   144,   145,   146,     0,     0,   147,     0,     0,
       0,     0,     0,     0,     0,     0,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,     0,     0,   189,
     190,   191,   192,   193,   194,   195,   130,   131,   132,   133,
     134,     0,   135,   136,   137,   138,     0,   196,   197,   198,
       0,   199,     0,     0,     0,     0,     0,     0,     0,     0,
     200,     0,   201,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   139,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   140,   141,   142,   143,   144,
     145,   146,     0,     0,   147,     0,     0,     0,     0,     0,
       0,     0,     0,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,     0,     0,   189,   190,   191,   192,
     193,   194,   195,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   196,   197,   198,     0,   199,   314,
     315,   316,     0,     0,     0,     0,     0,   200,     0,   201,
       0,     0,     0,     0,     0,   317,     0,   318,   319,   320,
     321,   322,   323,   324,   325,   326,   327,   328,   329,   330,
     331,   332,   333,   334,   335,   336,   337,   338,     0,   339,
     314,   315,   316,     0,     0,     0,     0,     0,     0,     0,
       0,   340,     0,     0,     0,     0,   317,     0,   318,   319,
     320,   321,   322,   323,   324,   325,   326,   327,   328,   329,
     330,   331,   332,   333,   334,   335,   336,   337,   338,     0,
     339,   314,   315,   316,     0,     0,     0,     0,     0,     0,
       0,     0,   340,     0,     0,     0,     0,   317,     0,   318,
     319,   320,   321,   322,   323,   324,   325,   326,   327,   328,
     329,   330,   331,   332,   333,   334,   335,   336,   337,   338,
       0,   339,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   340,   314,   315,   316,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   447,     0,
     317,     0,   318,   319,   320,   321,   322,   323,   324,   325,
     326,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,     0,   339,   314,   315,   316,     0,     0,
       0,     0,     0,     0,     0,     0,   340,     0,     0,   525,
       0,   317,     0,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,     0,   339,   314,   315,   316,     0,
       0,     0,     0,     0,     0,     0,     0,   340,     0,     0,
     539,     0,   317,     0,   318,   319,   320,   321,   322,   323,
     324,   325,   326,   327,   328,   329,   330,   331,   332,   333,
     334,   335,   336,   337,   338,     0,   339,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   340,   314,
     315,   316,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   540,     0,   317,     0,   318,   319,   320,
     321,   322,   323,   324,   325,   326,   327,   328,   329,   330,
     331,   332,   333,   334,   335,   336,   337,   338,     0,   339,
     314,   315,   316,     0,     0,     0,     0,     0,     0,     0,
       0,   340,     0,     0,   543,     0,   317,     0,   318,   319,
     320,   321,   322,   323,   324,   325,   326,   327,   328,   329,
     330,   331,   332,   333,   334,   335,   336,   337,   338,     0,
     339,   314,   315,   316,     0,     0,     0,     0,     0,     0,
       0,     0,   340,     0,     0,   551,     0,   317,     0,   318,
     319,   320,   321,   322,   323,   324,   325,   326,   327,   328,
     329,   330,   331,   332,   333,   334,   335,   336,   337,   338,
       0,   339,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   340,   314,   315,   316,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   802,     0,
     317,     0,   318,   319,   320,   321,   322,   323,   324,   325,
     326,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,     0,   339,   314,   315,   316,     0,     0,
       0,     0,     0,     0,     0,     0,   340,     0,     0,   980,
       0,   317,     0,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,     0,   339,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   340,     0,     0,
    1020,     0,   314,   315,   316,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   583,   317,   614,
     318,   319,   320,   321,   322,   323,   324,   325,   326,   327,
     328,   329,   330,   331,   332,   333,   334,   335,   336,   337,
     338,     0,   339,     0,   315,   316,     0,     0,     0,     0,
       0,     0,     0,     0,   340,     0,     0,     0,   744,   317,
       0,   318,   319,   320,   321,   322,   323,   324,   325,   326,
     327,   328,   329,   330,   331,   332,   333,   334,   335,   336,
     337,   338,     0,   339,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   340
};

static const yytype_int16 yycheck[] =
{
       2,   370,    26,     2,    26,     2,   122,     2,     2,   313,
      47,   363,    26,   358,   362,   464,   538,    26,   458,   763,
     258,    23,    24,   339,   356,   771,   544,   440,     8,     8,
       2,     8,    61,     8,    73,     8,    73,     8,     8,     8,
       8,    50,     8,   375,     8,    47,     8,     8,     8,     8,
      93,    94,     8,     8,     8,     8,     8,     8,   670,     8,
      69,    26,     8,    72,    71,     8,    73,   371,     8,     8,
     374,    73,    73,     9,    10,    11,    29,   140,   140,    71,
      61,   144,   144,    59,    60,    71,   157,    31,    26,    25,
     114,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,     0,    49,     9,    10,    11,   157,   161,    66,
      67,    31,    36,   162,    61,    61,    61,   576,   157,    73,
      25,   160,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    61,    49,   162,   768,   526,   527,   140,
     146,   162,     8,    73,    73,   157,    61,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,   160,
     159,   161,   159,   596,   159,   160,   159,    71,   159,   159,
     159,   159,    71,   159,   159,   159,    31,   159,   159,   159,
     159,   719,   158,   158,   158,   158,   158,   158,   245,   158,
      71,   235,   158,    59,    60,   158,   520,   226,   158,   158,
      26,    78,   160,   160,    71,   160,    23,    24,   164,    26,
     578,   115,   140,   147,   538,   675,    71,   677,    73,   688,
     242,    26,    90,   245,   684,   242,   160,    71,   242,   157,
      61,   260,   160,   162,    71,    73,    73,   157,    43,   157,
      78,    71,    71,   265,    73,   144,   161,   304,    93,    94,
     272,   273,   274,   157,   796,   277,   111,   286,   610,   611,
     137,   283,    71,   727,    63,   734,    90,   736,   157,   313,
      73,   313,    71,   295,    73,    78,   144,   144,   157,   748,
     616,   295,   304,   147,    31,  1049,   141,  1053,   157,   144,
     121,   146,   158,   160,    26,   339,   160,   339,    71,   356,
     138,   139,   146,   295,   157,   339,   150,   162,    31,    71,
     339,   141,   111,   157,   144,   124,   161,    71,   375,   160,
     144,   710,   711,   160,    73,   162,    73,   371,   166,   371,
     374,   161,   374,   162,   356,   138,   139,   146,   703,   117,
     362,    73,   141,   372,    73,   144,   810,   146,   812,   701,
      73,   124,    53,   375,    55,    56,    57,    58,    66,    67,
     144,   830,   165,   162,   824,   140,    98,   159,   160,   144,
      71,   739,   117,   146,   403,   159,   160,    26,   400,   141,
     922,   639,   144,    49,   146,   158,   400,    73,   137,   138,
     139,    73,    78,   651,    43,    61,    73,    46,    71,   157,
      73,    78,   157,   425,    71,   157,    73,   157,   400,   138,
     139,   112,     8,    92,    93,    94,   885,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    13,
      71,   475,    73,   954,   955,   464,   458,    71,   111,   157,
     141,   157,    26,   144,   111,   146,    71,   140,   265,   506,
      71,   152,   138,   139,   160,   272,   273,   274,   716,    43,
     277,   138,   139,    59,    60,   157,   283,    71,   141,    73,
     111,   144,   796,   146,   141,    73,   520,   144,   520,   146,
      98,   140,   123,   505,   506,   157,    73,   160,   121,   162,
      71,    78,    73,    74,   538,   162,   538,    23,    24,    73,
     141,    23,    24,   144,    78,   146,    98,   111,   144,   898,
      69,    70,   157,   339,    25,    92,    93,    94,   540,   123,
      79,   162,   339,   540,   546,   547,   540,    61,   550,   998,
      73,    42,   140,   550,    45,    78,   550,   141,   140,   911,
     144,   144,   146,   144,   601,   362,   140,   576,   570,   140,
     572,   138,   139,   610,   611,   121,   578,   579,   162,    71,
     157,    73,   158,   137,   138,   139,   125,   126,   127,   128,
     129,   397,   616,   595,   616,    71,   595,   136,   595,   601,
     595,   595,   616,   142,   143,   411,   159,   616,   610,   611,
      13,  1060,   159,    13,   137,   138,   139,   156,   922,   111,
     158,  1070,    99,   595,   159,   159,    25,   104,   425,   106,
     107,   108,   109,   110,   111,   112,   163,    71,   280,    71,
     642,   119,   284,    42,   646,   642,    45,    13,   642,   141,
      31,   121,   144,    37,   146,   297,   121,   299,   300,   301,
     302,   458,    82,   159,   701,    45,    46,    47,     8,    49,
     162,   148,   149,   675,   151,   677,    81,    82,    83,   688,
     682,    61,   684,   682,   161,   682,    90,   682,   682,    13,
     928,    73,    71,   159,   158,   933,   119,   157,     8,   701,
     158,    71,    61,   740,   942,   161,   160,   158,   505,     8,
     682,   713,   106,   107,   108,   109,   110,   111,   720,   713,
      13,   693,    73,   725,   840,   734,   157,   736,   157,   164,
     968,   725,   970,   158,   164,   157,    13,   739,   740,   748,
     158,   713,   548,   981,   157,    71,   552,   553,   986,   546,
     547,   989,   140,   725,   140,   157,   102,    71,    13,   265,
      13,   159,   120,   160,    13,   159,   272,   273,   274,   763,
     159,   277,   796,   570,   796,   572,    13,   283,   146,   164,
     157,   578,   579,   159,   122,    13,    71,   137,    71,    71,
     762,     8,   157,   157,   121,   157,   602,   160,   800,   771,
     397,   803,   159,   800,   160,  1043,   800,   159,     8,   803,
     616,   158,   161,   158,   411,    98,   158,   158,   122,   616,
      71,   830,   824,   106,   107,   108,   109,   110,   111,   158,
     150,   803,     8,   158,   164,  1073,   158,   158,   157,    73,
      13,   124,  1080,    42,    43,    44,    45,    46,    47,   646,
      49,   657,   159,   159,   159,    73,   362,   159,   664,    71,
     158,   104,    61,   146,    73,    13,   868,   869,   157,   121,
      26,   868,   869,    68,   868,   869,   885,   849,   675,   159,
     677,   106,   107,   108,   109,   110,   111,   684,   159,   122,
     158,   397,    13,   160,    13,   160,   157,   160,   922,    13,
     922,   159,   159,    73,   160,   411,    71,    73,    13,    90,
     140,    90,    51,    29,    13,   157,    73,    13,   724,   425,
      26,   159,    71,   720,   159,    71,   155,   153,    73,    73,
     932,   102,   159,   570,   158,   932,   157,   160,   932,   948,
     403,   308,   739,   158,   605,   688,  1060,   647,   869,   720,
     939,   548,   458,   998,   409,   552,   553,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,   900,
     915,   758,  1027,  1027,   924,   706,   978,   697,   980,   912,
     898,   731,   984,   980,   978,   987,   980,   265,   975,   998,
     984,    -1,    -1,   987,    -1,    -1,    -1,    -1,    -1,   505,
      -1,    -1,    -1,    59,    60,   602,   978,    -1,   814,  1011,
     816,    -1,   984,  1015,    -1,   987,    -1,  1011,    -1,    -1,
    1022,  1015,  1024,  1025,    -1,    -1,    -1,   824,  1022,    -1,
    1024,  1025,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1011,
     546,   547,   548,  1015,    -1,    -1,   552,   553,    -1,    -1,
    1022,  1060,  1024,  1025,    -1,  1057,    -1,    -1,    -1,    -1,
     657,  1070,    -1,  1057,   570,    -1,   572,   664,    -1,    -1,
      -1,    -1,   578,   579,  1076,    -1,    -1,    -1,   884,  1081,
      -1,  1053,  1076,    -1,    -1,  1057,    -1,  1081,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   602,    -1,    -1,    -1,
      -1,    -1,    -1,   159,  1076,    -1,    -1,    -1,    -1,  1081,
      -1,    -1,    -1,    -1,    -1,   921,    -1,    -1,    -1,    -1,
      -1,   411,    -1,    -1,    -1,    -1,    -1,   724,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   944,    -1,
     646,    -1,   948,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   657,    -1,    -1,   960,    -1,    -1,    -1,   664,   965,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   973,    -1,   675,
      -1,   677,    -1,    -1,    -1,    -1,    -1,    -1,   684,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    -1,    -1,   999,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,  1017,    49,    -1,   720,    -1,    -1,   814,   724,   816,
      -1,    -1,    -1,    -1,    61,    59,    60,    -1,  1034,    -1,
      -1,    -1,    -1,   739,    -1,  1041,    -1,    -1,     4,     5,
      -1,     7,     8,     9,    -1,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    -1,   548,    25,
      -1,    -1,   552,   553,    -1,    -1,    -1,    -1,    -1,    -1,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    43,    -1,    45,
      -1,    47,    -1,    49,    -1,    -1,    -1,   884,    -1,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    73,   814,    -1,
     816,    77,   602,    -1,    -1,    -1,    -1,    -1,   824,    -1,
      -1,    -1,    -1,    -1,   921,   159,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    59,    60,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   944,    -1,    -1,
      -1,    -1,   949,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     126,    -1,    -1,   960,    -1,    -1,    -1,   657,   965,    -1,
      -1,    -1,    -1,    -1,   664,    -1,   973,    -1,   884,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   999,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,   921,    -1,    -1,    -1,    -1,
    1017,    -1,    -1,    -1,    -1,    59,    60,    -1,    -1,    -1,
      -1,  1028,    -1,    -1,   724,   159,    -1,  1034,   944,    -1,
      -1,    -1,    -1,    -1,  1041,    -1,    -1,    -1,    -1,    59,
      60,    -1,    -1,    99,   960,    -1,    -1,    -1,   104,   965,
     106,   107,   108,   109,   110,   111,   112,   973,    -1,    -1,
     236,    -1,   238,    -1,    -1,    -1,    -1,   243,   244,   245,
      90,   247,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   999,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   148,   149,    -1,   151,    -1,    -1,    -1,    -1,
      -1,  1017,   278,    -1,    -1,   161,   282,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   814,   159,   816,    -1,  1034,    -1,
     296,    -1,    -1,    -1,    -1,  1041,    -1,    -1,   304,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   314,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   324,   325,
     326,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,    -1,   340,    -1,    -1,    -1,   344,   345,
     346,   347,   348,   349,   350,   351,   352,   353,   354,   355,
     356,    -1,   358,   359,   884,    -1,    -1,    -1,   364,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    42,    43,    -1,   375,
      99,    -1,    -1,    -1,    -1,   104,   382,   106,   107,   108,
     109,   110,   111,   112,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   921,    -1,    69,    70,    71,    -1,    -1,    -1,    -1,
     406,    -1,    -1,    79,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   944,    -1,    -1,    -1,    -1,   148,
     149,    -1,   151,    -1,    -1,    -1,    -1,    -1,    -1,    99,
     960,    -1,   161,    -1,   104,   965,   106,   107,   108,   109,
     110,   111,   112,   973,    -1,    -1,    -1,    -1,   124,   125,
     126,   127,   128,   129,    -1,    -1,    -1,    -1,    -1,    -1,
     136,   467,    -1,    -1,    -1,   141,   142,   143,   144,   999,
     146,    -1,    -1,   479,    -1,    -1,    -1,    -1,   148,   149,
     156,   151,    -1,    -1,    -1,    -1,    -1,  1017,    -1,    -1,
      -1,   161,    -1,    -1,     9,    10,    11,    -1,    -1,    -1,
     506,    -1,    -1,    -1,  1034,    -1,    -1,    -1,    -1,    -1,
      25,  1041,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    -1,    49,     9,    10,    11,   544,   545,
      -1,    -1,    -1,    -1,    -1,    -1,    61,    -1,    -1,    -1,
      -1,    25,    -1,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    -1,    49,    -1,   583,    -1,   585,
      -1,    -1,    -1,    -1,    -1,    -1,   592,    61,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   601,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   610,   611,    -1,    -1,   614,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   622,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,
      10,    11,    -1,    -1,    -1,   641,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    25,   161,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,   674,    49,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    61,    -1,    -1,    -1,   691,    -1,   161,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   701,    -1,   703,   704,   705,
      -1,    -1,     3,     4,     5,     6,     7,    -1,    -1,    -1,
      -1,    12,    -1,   719,    -1,    -1,    -1,    -1,    -1,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    -1,    -1,    -1,   740,    36,    -1,    -1,   744,    -1,
      -1,    42,    43,    -1,    -1,    -1,    -1,    48,    -1,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      -1,    62,    63,    64,    65,    59,    60,    -1,    69,    70,
      71,    72,    73,    -1,    75,    -1,    -1,    -1,    79,    80,
      81,    82,   788,    84,    -1,    86,   792,    88,    -1,    -1,
      91,    -1,    -1,    -1,    95,    96,    97,    98,    99,   100,
     101,    -1,   103,   104,   105,    -1,    -1,    -1,   109,   110,
     111,    -1,   113,   114,   115,   116,   117,   118,    -1,    -1,
      -1,    -1,   123,   124,   125,   126,   127,   128,   129,    -1,
       3,     4,     5,     6,     7,   136,    -1,    -1,    -1,    12,
     141,   142,   143,   144,   145,   146,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   154,    -1,   156,   157,   863,   159,   160,
      -1,   162,   163,    36,   165,   166,    -1,   873,    -1,    42,
      43,    -1,    -1,    -1,    -1,    48,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    -1,    62,
      63,    64,    65,    -1,    -1,    -1,    69,    70,    71,    72,
      73,    -1,    75,    -1,    -1,    -1,    79,    80,    81,    82,
      -1,    84,    -1,    86,    -1,    88,    -1,    -1,    91,    -1,
      -1,   927,    95,    96,    97,    -1,    99,   100,   101,    -1,
     103,   104,   105,    -1,    -1,    -1,   109,   110,   111,    -1,
     113,   114,   115,   116,   117,   118,    -1,    -1,    -1,    -1,
     123,   124,   125,   126,   127,   128,   129,    -1,     3,     4,
       5,     6,     7,   136,    -1,    -1,    -1,    12,   141,   142,
     143,   144,   145,   146,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   154,    -1,   156,   157,    -1,   159,   160,   161,   162,
     163,    36,   165,   166,    -1,    -1,    -1,    42,    43,    -1,
      -1,    -1,    -1,    48,    -1,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    -1,    62,    63,    64,
      65,    -1,    -1,    -1,    69,    70,    71,    72,    73,    -1,
      75,    -1,    -1,    -1,    79,    80,    81,    82,    -1,    84,
      -1,    86,    -1,    88,    -1,    -1,    91,    -1,    -1,    -1,
      95,    96,    97,    -1,    99,   100,   101,    -1,   103,   104,
     105,    -1,    -1,    -1,   109,   110,   111,    -1,   113,   114,
     115,   116,   117,   118,    -1,    -1,    -1,    -1,   123,   124,
     125,   126,   127,   128,   129,    -1,     3,     4,     5,     6,
       7,   136,    -1,    -1,    -1,    12,   141,   142,   143,   144,
     145,   146,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   154,
      -1,   156,   157,    -1,   159,   160,   161,   162,   163,    36,
     165,   166,    -1,    -1,    -1,    42,    43,    -1,    -1,    -1,
      -1,    48,    -1,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    -1,    62,    63,    64,    65,    -1,
      -1,    -1,    69,    70,    71,    72,    73,    -1,    75,    -1,
      -1,    -1,    79,    80,    81,    82,    -1,    84,    -1,    86,
      -1,    88,    -1,    -1,    91,    -1,    -1,    -1,    95,    96,
      97,    -1,    -1,   100,   101,    -1,   103,    -1,   105,    -1,
      -1,    -1,   109,   110,   111,    -1,   113,   114,   115,    -1,
     117,   118,    -1,    -1,    -1,    -1,   123,   124,   125,   126,
     127,   128,   129,    -1,     3,     4,     5,     6,     7,   136,
      -1,    -1,    -1,    12,   141,   142,   143,   144,   145,   146,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   156,
     157,    -1,   159,   160,   161,   162,   163,    36,   165,   166,
      -1,    -1,    -1,    42,    43,    -1,    -1,    -1,    -1,    48,
      -1,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    -1,    62,    63,    64,    65,    -1,    -1,    -1,
      69,    70,    71,    72,    73,    -1,    75,    -1,    -1,    -1,
      79,    80,    81,    82,    -1,    84,    -1,    86,    -1,    88,
      -1,    -1,    91,    -1,    -1,    -1,    95,    96,    97,    -1,
      -1,   100,   101,    -1,   103,    -1,   105,    -1,    -1,    -1,
     109,   110,   111,    -1,   113,   114,   115,    -1,   117,   118,
      -1,    -1,    -1,    -1,   123,   124,   125,   126,   127,   128,
     129,    -1,     3,     4,     5,     6,     7,   136,    -1,    -1,
      -1,    12,   141,   142,   143,   144,   145,   146,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   156,   157,    -1,
     159,   160,   161,   162,   163,    36,   165,   166,    -1,    -1,
      -1,    42,    43,    -1,    -1,    -1,    -1,    48,    -1,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      -1,    62,    63,    64,    65,    -1,    -1,    -1,    69,    70,
      71,    72,    73,    -1,    75,    -1,    -1,    -1,    79,    80,
      81,    82,    -1,    84,    -1,    86,    -1,    88,    -1,    -1,
      91,    -1,    -1,    -1,    95,    96,    97,    98,    -1,   100,
     101,    -1,   103,    -1,   105,    -1,    -1,    -1,   109,   110,
     111,    -1,   113,   114,   115,    -1,   117,   118,    -1,    -1,
      -1,    -1,   123,   124,   125,   126,   127,   128,   129,    -1,
       3,     4,     5,     6,     7,   136,    -1,    -1,    -1,    12,
     141,   142,   143,   144,   145,   146,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   156,   157,    -1,   159,   160,
      -1,   162,   163,    36,   165,   166,    -1,    -1,    -1,    42,
      43,    -1,    -1,    -1,    -1,    48,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    -1,    62,
      63,    64,    65,    -1,    -1,    -1,    69,    70,    71,    72,
      73,    -1,    75,    -1,    -1,    -1,    79,    80,    81,    82,
      -1,    84,    -1,    86,    -1,    88,    89,    -1,    91,    -1,
      -1,    -1,    95,    96,    97,    -1,    -1,   100,   101,    -1,
     103,    -1,   105,    -1,    -1,    -1,   109,   110,   111,    -1,
     113,   114,   115,    -1,   117,   118,    -1,    -1,    -1,    -1,
     123,   124,   125,   126,   127,   128,   129,    -1,     3,     4,
       5,     6,     7,   136,    -1,    -1,    -1,    12,   141,   142,
     143,   144,   145,   146,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   156,   157,    -1,   159,   160,    -1,   162,
     163,    36,   165,   166,    -1,    -1,    -1,    42,    43,    -1,
      -1,    -1,    -1,    48,    -1,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    -1,    62,    63,    64,
      65,    -1,    -1,    -1,    69,    70,    71,    72,    73,    -1,
      75,    -1,    -1,    -1,    79,    80,    81,    82,    83,    84,
      -1,    86,    -1,    88,    -1,    -1,    91,    -1,    -1,    -1,
      95,    96,    97,    -1,    -1,   100,   101,    -1,   103,    -1,
     105,    -1,    -1,    -1,   109,   110,   111,    -1,   113,   114,
     115,    -1,   117,   118,    -1,    -1,    -1,    -1,   123,   124,
     125,   126,   127,   128,   129,    -1,     3,     4,     5,     6,
       7,   136,    -1,    -1,    -1,    12,   141,   142,   143,   144,
     145,   146,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   156,   157,    -1,   159,   160,    -1,   162,   163,    36,
     165,   166,    -1,    -1,    -1,    42,    43,    -1,    -1,    -1,
      -1,    48,    -1,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    -1,    62,    63,    64,    65,    -1,
      -1,    -1,    69,    70,    71,    72,    73,    -1,    75,    -1,
      -1,    -1,    79,    80,    81,    82,    -1,    84,    -1,    86,
      87,    88,    -1,    -1,    91,    -1,    -1,    -1,    95,    96,
      97,    -1,    -1,   100,   101,    -1,   103,    -1,   105,    -1,
      -1,    -1,   109,   110,   111,    -1,   113,   114,   115,    -1,
     117,   118,    -1,    -1,    -1,    -1,   123,   124,   125,   126,
     127,   128,   129,    -1,     3,     4,     5,     6,     7,   136,
      -1,    -1,    -1,    12,   141,   142,   143,   144,   145,   146,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   156,
     157,    -1,   159,   160,    -1,   162,   163,    36,   165,   166,
      -1,    -1,    -1,    42,    43,    -1,    -1,    -1,    -1,    48,
      -1,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    -1,    62,    63,    64,    65,    -1,    -1,    -1,
      69,    70,    71,    72,    73,    -1,    75,    -1,    -1,    -1,
      79,    80,    81,    82,    -1,    84,    -1,    86,    -1,    88,
      -1,    -1,    91,    -1,    -1,    -1,    95,    96,    97,    -1,
      -1,   100,   101,    -1,   103,    -1,   105,    -1,    -1,    -1,
     109,   110,   111,    -1,   113,   114,   115,    -1,   117,   118,
      -1,    -1,    -1,    -1,   123,   124,   125,   126,   127,   128,
     129,    -1,     3,     4,     5,     6,     7,   136,    -1,    -1,
      -1,    12,   141,   142,   143,   144,   145,   146,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   156,   157,    -1,
     159,   160,   161,   162,   163,    36,   165,   166,    -1,    -1,
      -1,    42,    43,    -1,    -1,    -1,    -1,    48,    -1,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      -1,    62,    63,    64,    65,    -1,    -1,    -1,    69,    70,
      71,    72,    73,    -1,    75,    -1,    -1,    -1,    79,    80,
      81,    82,    -1,    84,    -1,    86,    -1,    88,    -1,    -1,
      91,    -1,    -1,    -1,    95,    96,    97,    -1,    -1,   100,
     101,    -1,   103,    -1,   105,    -1,    -1,    -1,   109,   110,
     111,    -1,   113,   114,   115,    -1,   117,   118,    -1,    -1,
      -1,    -1,   123,   124,   125,   126,   127,   128,   129,    -1,
       3,     4,     5,     6,     7,   136,    -1,    -1,    -1,    12,
     141,   142,   143,   144,   145,   146,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   156,   157,    -1,   159,   160,
     161,   162,   163,    36,   165,   166,    -1,    -1,    -1,    42,
      43,    -1,    -1,    -1,    -1,    48,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    -1,    62,
      63,    64,    65,    -1,    -1,    -1,    69,    70,    71,    72,
      73,    -1,    75,    -1,    -1,    -1,    79,    80,    81,    82,
      -1,    84,    85,    86,    -1,    88,    -1,    -1,    91,    -1,
      -1,    -1,    95,    96,    97,    -1,    -1,   100,   101,    -1,
     103,    -1,   105,    -1,    -1,    -1,   109,   110,   111,    -1,
     113,   114,   115,    -1,   117,   118,    -1,    -1,    -1,    -1,
     123,   124,   125,   126,   127,   128,   129,    -1,     3,     4,
       5,     6,     7,   136,    -1,    -1,    -1,    12,   141,   142,
     143,   144,   145,   146,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   156,   157,    -1,   159,   160,    -1,   162,
     163,    36,   165,   166,    -1,    -1,    -1,    42,    43,    -1,
      -1,    -1,    -1,    48,    -1,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    -1,    62,    63,    64,
      65,    -1,    -1,    -1,    69,    70,    71,    72,    73,    -1,
      75,    -1,    -1,    -1,    79,    80,    81,    82,    -1,    84,
      -1,    86,    -1,    88,    -1,    -1,    91,    -1,    -1,    -1,
      95,    96,    97,    -1,    -1,   100,   101,    -1,   103,    -1,
     105,    -1,    -1,    -1,   109,   110,   111,    -1,   113,   114,
     115,    -1,   117,   118,    -1,    -1,    -1,    -1,   123,   124,
     125,   126,   127,   128,   129,    -1,     3,     4,     5,     6,
       7,   136,    -1,    -1,    -1,    12,   141,   142,   143,   144,
     145,   146,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   156,   157,    -1,   159,   160,   161,   162,   163,    36,
     165,   166,    -1,    -1,    -1,    42,    43,    -1,    -1,    -1,
      -1,    48,    -1,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    -1,    62,    63,    64,    65,    -1,
      -1,    -1,    69,    70,    71,    72,    73,    -1,    75,    -1,
      -1,    -1,    79,    80,    81,    82,    -1,    84,    -1,    86,
      -1,    88,    -1,    -1,    91,    -1,    -1,    -1,    95,    96,
      97,    -1,    -1,   100,   101,    -1,   103,    -1,   105,    -1,
      -1,    -1,   109,   110,   111,    -1,   113,   114,   115,    -1,
     117,   118,    -1,    -1,    -1,    -1,   123,   124,   125,   126,
     127,   128,   129,    -1,     3,     4,     5,     6,     7,   136,
      -1,    -1,    -1,    12,   141,   142,   143,   144,   145,   146,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   156,
     157,    -1,   159,   160,   161,   162,   163,    36,   165,   166,
      -1,    -1,    -1,    42,    43,    -1,    -1,    -1,    -1,    48,
      -1,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    -1,    62,    63,    64,    65,    -1,    -1,    -1,
      69,    70,    71,    72,    73,    -1,    75,    -1,    -1,    -1,
      79,    80,    81,    82,    -1,    84,    -1,    86,    -1,    88,
      -1,    -1,    91,    -1,    -1,    -1,    95,    96,    97,    -1,
      -1,   100,   101,    -1,   103,    -1,   105,    -1,    -1,    -1,
     109,   110,   111,    -1,   113,   114,   115,    -1,   117,   118,
      -1,    -1,    -1,    -1,   123,   124,   125,   126,   127,   128,
     129,    -1,     3,     4,     5,     6,     7,   136,    -1,    -1,
      -1,    12,   141,   142,   143,   144,   145,   146,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    26,    -1,   156,   157,    -1,
     159,   160,   161,   162,   163,    36,   165,   166,    -1,    -1,
      -1,    42,    43,    -1,    -1,    -1,    -1,    48,    -1,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      -1,    62,    63,    64,    65,    -1,    -1,    -1,    69,    70,
      71,    72,    73,    -1,    75,    -1,    -1,    -1,    79,    80,
      81,    82,    -1,    84,    -1,    86,    -1,    88,    -1,    -1,
      91,    -1,    -1,    -1,    95,    96,    97,    -1,    -1,   100,
     101,    -1,   103,    -1,   105,    -1,    -1,    -1,    -1,    -1,
     111,    -1,   113,   114,   115,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   123,   124,   125,   126,   127,   128,   129,    -1,
       3,     4,     5,     6,     7,   136,    -1,    -1,    -1,    12,
     141,   142,   143,   144,   145,   146,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    26,    -1,   156,   157,    -1,   159,   160,
      -1,   162,   163,    36,   165,   166,    -1,    -1,    -1,    42,
      43,    -1,    -1,    -1,    -1,    48,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    -1,    62,
      63,    64,    65,    -1,    -1,    -1,    69,    70,    71,    72,
      73,    -1,    75,    -1,    -1,    -1,    79,    80,    81,    82,
      -1,    84,    -1,    86,    -1,    88,    -1,    -1,    91,    -1,
      -1,    -1,    95,    96,    97,    -1,    -1,   100,   101,    -1,
     103,    -1,   105,    -1,    -1,    -1,    -1,    -1,   111,    -1,
     113,   114,   115,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     123,   124,   125,   126,   127,   128,   129,    -1,     3,     4,
       5,     6,     7,   136,    -1,    -1,    -1,    12,   141,   142,
     143,   144,   145,   146,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    26,    -1,   156,   157,    -1,   159,   160,    -1,   162,
     163,    36,   165,   166,    -1,    -1,    -1,    42,    43,    -1,
      -1,    -1,    -1,    48,    -1,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    -1,    62,    63,    64,
      65,    -1,    -1,    -1,    69,    70,    71,    72,    73,    -1,
      75,    -1,    -1,    -1,    79,    80,    81,    82,    -1,    84,
      -1,    86,    -1,    88,    -1,    -1,    91,    -1,    -1,    -1,
      95,    96,    97,    -1,    -1,   100,   101,    -1,   103,    -1,
     105,    -1,    -1,    -1,    -1,    -1,   111,    -1,   113,   114,
     115,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   123,   124,
     125,   126,   127,   128,   129,    -1,     3,     4,     5,     6,
       7,   136,    -1,    -1,    -1,    12,   141,   142,   143,   144,
     145,   146,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,
      -1,   156,   157,    -1,   159,   160,    -1,   162,   163,    36,
     165,   166,    -1,    -1,    -1,    42,    43,    -1,    -1,    -1,
      -1,    48,    -1,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    -1,    62,    63,    64,    65,    -1,
      -1,    -1,    69,    70,    71,    72,    73,    -1,    75,    -1,
      -1,    -1,    79,    80,    81,    82,    -1,    84,    -1,    86,
      -1,    88,    -1,    -1,    91,    -1,    -1,    -1,    95,    96,
      97,    -1,    -1,   100,   101,    -1,   103,    -1,   105,    -1,
      -1,    -1,    -1,    -1,   111,    -1,   113,   114,   115,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   123,   124,   125,   126,
     127,   128,   129,    -1,     3,     4,     5,     6,     7,   136,
      -1,    -1,    -1,    12,   141,   142,   143,   144,   145,   146,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,    -1,   156,
     157,    -1,   159,   160,    -1,   162,   163,    36,   165,   166,
      -1,    -1,    -1,    42,    43,    -1,    -1,    -1,    -1,    48,
      -1,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    -1,    62,    63,    64,    65,    -1,    -1,    -1,
      69,    70,    71,    72,    73,    -1,    75,    -1,    -1,    -1,
      79,    80,    81,    82,    -1,    84,    -1,    86,    -1,    88,
      -1,    -1,    91,    -1,    -1,    -1,    95,    96,    97,    -1,
      -1,   100,   101,    -1,   103,    -1,   105,    -1,    -1,    -1,
      -1,    -1,   111,    -1,   113,   114,   115,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   123,   124,   125,   126,   127,   128,
     129,    -1,     3,     4,     5,     6,     7,   136,    -1,    -1,
      -1,    12,   141,   142,   143,   144,   145,   146,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   156,   157,    -1,
     159,   160,    -1,   162,   163,    36,   165,   166,    -1,    -1,
      -1,    42,    43,    -1,    -1,    -1,    -1,    48,    -1,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      -1,    62,    63,    64,    65,    -1,    -1,    -1,    69,    70,
      71,    72,    73,    -1,    75,    -1,    -1,    -1,    79,    80,
      81,    82,    -1,    84,    -1,    86,    -1,    88,    -1,    -1,
      91,    -1,    -1,    -1,    95,    96,    97,    -1,    -1,   100,
     101,    -1,   103,    -1,   105,    -1,    -1,    -1,    -1,    -1,
     111,    -1,   113,   114,   115,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   123,   124,   125,   126,   127,   128,   129,    -1,
      -1,    -1,    -1,    -1,    -1,   136,    -1,    -1,    -1,    -1,
     141,   142,   143,   144,   145,   146,    -1,    -1,     3,     4,
       5,     6,     7,    -1,    -1,   156,   157,    12,   159,   160,
      -1,   162,   163,    -1,   165,   166,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,    -1,
      -1,    36,    -1,    -1,    -1,    -1,    -1,    42,    43,    -1,
      -1,    -1,    -1,    48,    -1,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    -1,    62,    63,    64,
       9,    10,    11,    -1,    69,    70,    71,    72,    73,    -1,
      -1,    -1,    -1,    -1,    79,    -1,    25,    -1,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    -1,
      49,    -1,    -1,    -1,    -1,    -1,   111,    -1,    -1,   114,
     115,    -1,    61,    -1,    -1,    -1,    -1,    -1,   123,   124,
     125,   126,   127,   128,   129,    -1,     3,     4,     5,     6,
       7,   136,    -1,    -1,    -1,    12,   141,   142,   143,   144,
      -1,   146,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   156,   157,   158,    31,    -1,    -1,   162,   163,    36,
     165,   166,    -1,    -1,    -1,    42,    43,    -1,    -1,    -1,
      -1,    48,    -1,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    -1,    62,    63,    64,    -1,    -1,
      -1,    -1,    69,    70,    71,    72,    73,    -1,    -1,    -1,
      -1,    -1,    79,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   161,    -1,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   111,    -1,    -1,   114,   115,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   123,   124,   125,   126,
     127,   128,   129,    -1,     3,     4,     5,     6,     7,   136,
      59,    60,    -1,    12,   141,   142,   143,   144,    -1,   146,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   156,
     157,   158,    31,    -1,    -1,   162,   163,    36,   165,   166,
      -1,    -1,    -1,    42,    43,    -1,    -1,    -1,    -1,    48,
      -1,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    -1,    62,    63,    64,     9,    10,    11,    -1,
      69,    70,    71,    72,    73,    -1,    -1,    -1,    -1,    -1,
      79,    -1,    25,    -1,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    -1,    49,    -1,    -1,    -1,
      -1,    -1,   111,    -1,    -1,   114,   115,    -1,    61,    -1,
      -1,    -1,    -1,    -1,   123,   124,   125,   126,   127,   128,
     129,    -1,     3,     4,     5,     6,     7,   136,    -1,    -1,
      -1,    12,   141,   142,   143,   144,   145,   146,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   156,   157,    -1,
      31,    -1,    -1,   162,   163,    36,   165,   166,    -1,    -1,
      -1,    42,    43,    -1,    -1,    -1,    -1,    48,    -1,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      -1,    62,    63,    64,    -1,    -1,    -1,    -1,    69,    70,
      71,    72,    73,    -1,    -1,    -1,    -1,    -1,    79,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   161,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    -1,    49,
     111,    -1,    -1,   114,   115,    -1,    -1,    -1,    -1,    -1,
      -1,    61,   123,   124,   125,   126,   127,   128,   129,    -1,
       3,     4,     5,     6,     7,   136,    -1,    -1,    -1,    12,
     141,   142,   143,   144,    -1,   146,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   156,   157,   158,    -1,    -1,
      -1,   162,   163,    36,   165,   166,    -1,    -1,    -1,    42,
      43,    -1,    -1,    -1,    -1,    48,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    -1,    62,
      63,    64,     9,    10,    11,    -1,    69,    70,    71,    72,
      73,    -1,    -1,    -1,    -1,    -1,    79,    -1,    25,    -1,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    -1,    49,    -1,    -1,    -1,    -1,    -1,   111,    -1,
      -1,   114,   115,    -1,    61,    -1,    -1,    -1,    -1,    -1,
     123,   124,   125,   126,   127,   128,   129,    -1,     3,     4,
       5,     6,     7,   136,    -1,    -1,    -1,    12,   141,   142,
     143,   144,    -1,   146,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   156,   157,    -1,   159,    -1,    -1,   162,
     163,    36,   165,   166,    -1,    -1,    -1,    42,    43,    -1,
      -1,    -1,    -1,    48,    -1,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    -1,    62,    63,    64,
      -1,    -1,    -1,    -1,    69,    70,    71,    72,    73,    -1,
      -1,    -1,    -1,    -1,    79,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   161,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    -1,    49,    -1,   111,    -1,    -1,   114,
     115,    -1,    -1,    -1,    -1,    -1,    61,    -1,   123,   124,
     125,   126,   127,   128,   129,    -1,     3,     4,     5,     6,
       7,   136,    -1,    -1,    -1,    12,   141,   142,   143,   144,
      -1,   146,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   156,   157,    -1,   159,    -1,    -1,   162,   163,    36,
     165,   166,    -1,    -1,    -1,    42,    43,    -1,    -1,    -1,
      -1,    48,    -1,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    -1,    62,    63,    64,     9,    10,
      11,    -1,    69,    70,    71,    72,    73,    -1,    -1,    -1,
      -1,    -1,    79,    -1,    25,    -1,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    -1,    49,    -1,
      -1,    -1,    -1,    -1,   111,    -1,    -1,   114,   115,    -1,
      61,    -1,    -1,    -1,    -1,    -1,   123,   124,   125,   126,
     127,   128,   129,    -1,     3,     4,     5,     6,     7,   136,
      -1,    -1,    -1,    12,   141,   142,   143,   144,    -1,   146,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   156,
     157,    -1,   159,    -1,    -1,   162,   163,    36,   165,   166,
      -1,    -1,    -1,    42,    43,    -1,    -1,    -1,    -1,    48,
      -1,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    -1,    62,    63,    64,    -1,    -1,    -1,    -1,
      69,    70,    71,    72,    73,    -1,    -1,    -1,    -1,    -1,
      79,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     161,    -1,    -1,    -1,    -1,    -1,    95,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    -1,
      49,    -1,   111,    -1,    -1,   114,   115,    -1,    -1,    -1,
      -1,    -1,    61,    -1,   123,   124,   125,   126,   127,   128,
     129,    -1,     3,     4,     5,     6,     7,   136,    -1,    -1,
      -1,    12,   141,   142,   143,   144,    -1,   146,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   156,   157,    -1,
      -1,    -1,    -1,   162,   163,    36,   165,   166,    -1,    -1,
      -1,    42,    43,    -1,    -1,    -1,    -1,    48,    -1,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      -1,    62,    63,    64,     9,    10,    11,    -1,    69,    70,
      71,    72,    73,    -1,    -1,    -1,    -1,    -1,    79,    -1,
      25,    -1,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    -1,    49,    -1,    -1,    -1,    -1,    -1,
     111,    -1,    -1,   114,   115,    -1,    61,    -1,    -1,    -1,
      -1,    -1,   123,   124,   125,   126,   127,   128,   129,    -1,
       3,     4,     5,     6,     7,   136,    -1,    -1,    -1,    12,
     141,   142,   143,   144,    -1,   146,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   156,   157,   158,    -1,    -1,
      -1,   162,   163,    36,   165,   166,    -1,    -1,    -1,    42,
      43,    -1,    -1,    -1,    -1,    48,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    -1,    62,
      63,    64,    -1,    -1,    -1,    -1,    69,    70,    71,    72,
      73,    -1,    -1,    -1,    -1,    -1,    79,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   161,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    -1,    49,    -1,    -1,    -1,   111,    -1,
      -1,   114,   115,    -1,    -1,    -1,    61,    -1,    -1,    -1,
     123,   124,   125,   126,   127,   128,   129,    -1,     3,     4,
       5,     6,     7,   136,    -1,    -1,    -1,    12,   141,   142,
     143,   144,    -1,   146,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    26,    -1,   156,   157,    -1,   159,    -1,    -1,   162,
     163,    36,   165,   166,    -1,    -1,    -1,    42,    43,    -1,
      -1,    -1,    -1,    48,    -1,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    -1,    62,    63,    64,
       9,    10,    11,    -1,    69,    70,    71,    72,    73,    -1,
      -1,    -1,    -1,    -1,    79,    -1,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    -1,
      49,    -1,    -1,    -1,    -1,    -1,   111,    -1,    -1,   114,
     115,    -1,    61,    -1,    -1,    -1,    -1,    -1,   123,   124,
     125,   126,   127,   128,   129,    -1,     3,     4,     5,     6,
       7,   136,    -1,    -1,    -1,    12,   141,   142,   143,   144,
      -1,   146,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   156,   157,    -1,    -1,    -1,    -1,   162,   163,    36,
     165,   166,    -1,    -1,    -1,    42,    43,    -1,    -1,    -1,
      -1,    48,    -1,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    -1,    62,    63,    64,    -1,    -1,
      -1,    -1,    69,    70,    71,    72,    73,    -1,    -1,    -1,
      -1,    -1,    79,    -1,    -1,    -1,    -1,    -1,    -1,    25,
     159,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    -1,    49,   111,    -1,    -1,   114,   115,    -1,
      -1,    -1,    -1,    -1,    -1,    61,   123,   124,   125,   126,
     127,   128,   129,    -1,    -1,    -1,    -1,    -1,    -1,   136,
      -1,    -1,    -1,    -1,   141,   142,   143,   144,    -1,   146,
      -1,    -1,     3,     4,     5,     6,     7,    -1,    -1,   156,
     157,    12,    -1,    -1,    -1,   162,   163,   164,   165,   166,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      31,    -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,    -1,
      -1,    42,    43,    -1,    -1,    -1,    -1,    48,    -1,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      -1,    62,    63,    64,     9,    10,    11,    -1,    69,    70,
      71,    72,    73,    -1,    -1,    -1,    -1,    -1,    79,    -1,
      25,    -1,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    -1,    49,    -1,    -1,    -1,    -1,    -1,
     111,    -1,    -1,   114,   115,    -1,    61,    -1,    -1,    -1,
      -1,    -1,   123,   124,   125,   126,   127,   128,   129,    -1,
       3,     4,     5,     6,     7,   136,    -1,    -1,    -1,    12,
     141,   142,   143,   144,    -1,   146,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   156,   157,    -1,    31,    -1,
      -1,   162,   163,    36,   165,   166,    -1,    -1,    -1,    42,
      43,    -1,    -1,    -1,    -1,    48,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    -1,    62,
      63,    64,    -1,    -1,    -1,    -1,    69,    70,    71,    72,
      73,    -1,    -1,    -1,    -1,    -1,    79,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   159,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    -1,    49,   111,    -1,
      -1,   114,   115,    -1,    -1,    -1,    -1,    -1,    -1,    61,
     123,   124,   125,   126,   127,   128,   129,    -1,     3,     4,
       5,     6,     7,   136,    -1,    -1,    -1,    12,   141,   142,
     143,   144,    -1,   146,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   156,   157,    -1,    31,    -1,    -1,   162,
     163,    36,   165,   166,    -1,    -1,    -1,    42,    43,    -1,
      -1,    -1,    -1,    48,    -1,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    -1,    62,    63,    64,
       9,    10,    11,    -1,    69,    70,    71,    72,    73,    -1,
      -1,    -1,    -1,    -1,    79,    -1,    25,    -1,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    -1,
      49,    -1,    -1,    -1,    -1,    -1,   111,    -1,    -1,   114,
     115,    -1,    61,    -1,    -1,    -1,    -1,    -1,   123,   124,
     125,   126,   127,   128,   129,    -1,     3,     4,     5,     6,
       7,   136,    -1,    -1,    -1,    12,   141,   142,   143,   144,
      -1,   146,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   156,   157,    -1,    -1,    -1,    -1,   162,   163,    36,
     165,   166,    -1,    -1,    -1,    42,    43,    -1,    -1,    -1,
      -1,    48,    -1,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    -1,    62,    63,    64,    -1,    -1,
      -1,    -1,    69,    70,    71,    72,    73,    -1,    -1,    -1,
      -1,    -1,    79,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     159,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    -1,    49,    -1,   111,    -1,    -1,   114,   115,    -1,
      -1,    -1,    -1,    -1,    61,    -1,   123,   124,   125,   126,
     127,   128,   129,    -1,     3,     4,     5,     6,     7,   136,
      -1,    -1,    -1,    12,   141,   142,   143,   144,   145,   146,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   156,
     157,    -1,    -1,    -1,    -1,   162,   163,    36,   165,   166,
      -1,    -1,    -1,    42,    43,    -1,    -1,    -1,    -1,    48,
      -1,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    -1,    62,    63,    64,     9,    10,    11,    -1,
      69,    70,    71,    72,    73,    -1,    -1,    -1,    -1,    -1,
      79,    -1,    25,    -1,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    -1,    49,    -1,    -1,    -1,
      -1,    -1,   111,    -1,    -1,   114,   115,    -1,    61,    -1,
      -1,    -1,    -1,    -1,   123,   124,   125,   126,   127,   128,
     129,    -1,     3,     4,     5,     6,     7,   136,    -1,    -1,
      -1,    12,   141,   142,   143,   144,    -1,   146,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   156,   157,   158,
      31,    -1,    -1,   162,   163,    36,   165,   166,    -1,    -1,
      -1,    42,    43,    -1,    -1,    -1,    -1,    48,    -1,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      -1,    62,    63,    64,    -1,    -1,    -1,    -1,    69,    70,
      71,    72,    73,    -1,    -1,    -1,    -1,    -1,    79,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   159,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    -1,    49,    -1,    -1,    -1,    -1,    -1,
     111,    -1,    -1,   114,   115,    -1,    61,    -1,    -1,    -1,
      -1,    -1,   123,   124,   125,   126,   127,   128,   129,    -1,
       3,     4,     5,     6,     7,   136,    -1,    -1,    -1,    12,
     141,   142,   143,   144,    -1,   146,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   156,   157,    -1,    -1,    -1,
      -1,   162,   163,    36,   165,   166,    -1,    -1,    -1,    42,
      43,    -1,    -1,    -1,    -1,    48,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    -1,    62,
      63,    64,     9,    10,    11,    -1,    69,    70,    71,    72,
      73,    -1,    -1,    -1,    -1,    -1,    79,    -1,    25,    -1,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    -1,    49,    -1,    -1,    -1,    -1,    -1,   111,    -1,
      -1,   114,   115,    -1,    61,    -1,    -1,    -1,    -1,    -1,
     123,   124,   125,   126,   127,   128,   129,    -1,     3,     4,
       5,     6,     7,   136,    -1,    -1,    -1,    12,   141,   142,
     143,   144,    -1,   146,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   156,   157,    -1,    -1,    -1,    -1,   162,
     163,    36,   165,   166,    -1,    -1,    -1,    42,    43,    -1,
      -1,    -1,    -1,    48,    -1,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    -1,    62,    63,    64,
      -1,    -1,    -1,    -1,    69,    70,    71,    72,    73,    -1,
      -1,    -1,    -1,    -1,    79,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   159,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   111,    -1,    -1,   114,
     115,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   123,   124,
     125,   126,   127,   128,   129,    -1,    -1,    -1,    -1,    -1,
      -1,   136,    -1,    -1,    -1,    -1,   141,   142,   143,   144,
      -1,   146,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   156,   157,    -1,    -1,    -1,    -1,   162,   163,    11,
     165,   166,     3,     4,     5,     6,     7,    -1,     9,    10,
      11,    12,    -1,    25,    -1,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    37,    49,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,    49,    61,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    62,    63,    64,    65,    66,    67,    68,    -1,    -1,
      71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
      -1,    -1,   123,   124,   125,   126,   127,   128,   129,     3,
       4,     5,     6,     7,    -1,     9,    10,    11,    12,    -1,
     141,   142,   143,    -1,   145,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   154,    -1,   156,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    46,    -1,    -1,    49,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,    63,
      64,    65,    66,    67,    68,    -1,    -1,    71,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,    -1,    -1,   123,
     124,   125,   126,   127,   128,   129,     3,     4,     5,     6,
       7,    -1,     9,    10,    11,    12,    -1,   141,   142,   143,
      -1,   145,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     154,    -1,   156,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    62,    63,    64,    65,    66,
      67,    68,    -1,    -1,    71,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,    -1,    -1,   123,   124,   125,   126,
     127,   128,   129,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   141,   142,   143,    -1,   145,     9,
      10,    11,    -1,    -1,    -1,    -1,    -1,   154,    -1,   156,
      -1,    -1,    -1,    -1,    -1,    25,    -1,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    -1,    49,
       9,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    61,    -1,    -1,    -1,    -1,    25,    -1,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    -1,
      49,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    61,    -1,    -1,    -1,    -1,    25,    -1,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    61,     9,    10,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   158,    -1,
      25,    -1,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    -1,    49,     9,    10,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    61,    -1,    -1,   158,
      -1,    25,    -1,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    -1,    49,     9,    10,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,    -1,    -1,
     158,    -1,    25,    -1,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    -1,    49,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,     9,
      10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   158,    -1,    25,    -1,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    -1,    49,
       9,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    61,    -1,    -1,   158,    -1,    25,    -1,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    -1,
      49,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    61,    -1,    -1,   158,    -1,    25,    -1,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    61,     9,    10,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   158,    -1,
      25,    -1,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    -1,    49,     9,    10,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    61,    -1,    -1,   158,
      -1,    25,    -1,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    -1,    49,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,    -1,    -1,
     158,    -1,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   122,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    -1,    49,    -1,    10,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    61,    -1,    -1,    -1,   122,    25,
      -1,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    61
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   168,   169,     0,     3,     4,     5,     6,     7,    12,
      36,    42,    43,    48,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    62,    63,    64,    65,    69,
      70,    71,    72,    73,    75,    79,    80,    81,    82,    84,
      86,    88,    91,    95,    96,    97,    99,   100,   101,   103,
     104,   105,   109,   110,   111,   113,   114,   115,   116,   117,
     118,   123,   124,   125,   126,   127,   128,   129,   136,   141,
     142,   143,   144,   145,   146,   154,   156,   157,   159,   160,
     162,   163,   165,   166,   170,   175,   176,   177,   178,   181,
     182,   194,   196,   201,   203,   225,   226,   268,   272,   291,
     292,   293,   302,   305,   309,   310,   312,   313,   319,   320,
     321,   322,   323,   324,   329,   336,   338,    71,   111,   123,
     141,   225,   226,   309,   313,   309,   157,   309,   309,   309,
       3,     4,     5,     6,     7,     9,    10,    11,    12,    49,
      62,    63,    64,    65,    66,    67,    68,    71,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   123,
     124,   125,   126,   127,   128,   129,   141,   142,   143,   145,
     154,   156,   284,   290,   309,   309,   309,   309,   309,   309,
     309,   309,   309,   309,   309,   309,    71,   146,   176,   292,
     312,   313,   312,   309,   111,   141,   144,   146,   175,   177,
     292,   294,   295,   322,   323,   329,   157,   299,   157,    26,
     265,   309,   184,   157,   157,   157,   157,   157,   159,   309,
      71,   159,   309,    71,   159,   268,   309,   313,   160,   309,
     144,   173,   174,   175,    73,   162,   229,   230,   117,   117,
      73,   231,   157,   157,   157,   157,    71,   157,   157,    73,
      78,   137,   138,   139,   333,   334,   144,   160,   175,   175,
      95,   268,   313,    71,   309,   179,   160,    78,   300,   333,
      78,   333,   333,   144,   157,     8,   159,    71,   146,    73,
     232,    98,   193,   140,     9,    10,    11,    25,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    49,
      61,   159,    59,    60,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,   157,   314,    61,   160,
     162,   323,   157,   193,    13,   309,    26,    43,    46,   273,
     278,   140,   144,   175,   140,   157,   301,   296,   323,   158,
     309,   309,     8,   159,   181,   309,   266,   267,   309,   268,
     313,    71,   215,   309,   159,   159,   159,    13,   159,   159,
     179,   159,   175,     8,   159,    90,   160,   310,   313,     8,
     159,    13,     8,   159,   190,   191,   313,   313,   337,   313,
     158,   200,   123,   313,   330,    31,   309,   331,   332,    61,
     121,   137,   334,    72,   309,   313,    78,   137,   334,   175,
     172,   159,   160,   159,   159,   159,   202,   158,   161,   180,
     181,   194,   196,   309,   163,   165,   166,    71,    31,   227,
     228,   268,   313,    71,   119,   204,   204,    13,     8,   159,
      31,   192,    71,   319,   323,   329,   309,   309,   309,    26,
     309,   309,   309,   309,   309,   309,   309,   309,   309,   309,
     309,   309,   309,   309,   309,   309,   309,   309,   309,   309,
     309,   309,   294,   309,   325,    31,   145,   309,   309,   309,
     309,   309,   309,   309,   309,   309,   309,   309,   309,   227,
     121,   325,   309,   330,   192,   158,   285,   286,    37,    37,
      46,   281,   287,   290,    71,   175,   319,   227,   121,   158,
     158,   309,    82,   158,   159,     8,    90,    90,    13,     8,
     158,   158,    42,    43,   124,   136,   146,   176,   177,   302,
     303,   304,   161,    90,   174,    71,   309,   230,   303,    73,
       8,   158,     8,   158,   158,   159,   119,   206,   157,     8,
     158,   311,   313,   122,   158,     8,   307,    71,    73,    74,
     335,    71,    61,   161,   161,   169,   171,   160,   161,   311,
     158,     8,    13,   293,   197,   198,   309,    73,    71,   157,
     157,   157,   323,   309,    26,   164,    63,   313,   268,   313,
     158,    71,   160,   319,   326,   327,   328,   164,   161,   158,
     290,   290,   275,   274,    13,    26,    43,   158,   326,    26,
     181,   157,   183,   266,   309,   313,    31,   210,   313,   303,
      71,    26,   181,   214,   186,   303,   303,   157,    78,   140,
     140,   102,    71,   161,    13,   191,   159,   313,   207,   293,
     160,   330,   123,   313,    13,    31,   309,    31,   309,   164,
     309,   161,   169,   233,    31,   268,   313,   303,   120,   205,
     205,    13,   195,   269,   227,   227,   309,   294,   159,   159,
     309,   157,   318,    61,   160,    13,   280,   146,   277,   279,
     288,   289,   297,   179,   219,   309,    26,   181,   213,   159,
     122,   209,   313,   209,    13,   179,    26,   160,   216,   303,
     306,   308,    71,    71,   157,   303,     8,   233,   158,   157,
     145,   309,   311,   311,   122,   164,   161,    99,   104,   106,
     107,   108,   109,   110,   111,   112,   148,   149,   151,   161,
     235,   259,   260,   261,   262,   264,   311,   207,   160,   160,
     309,   157,    71,   124,   146,   223,   224,   226,   158,   158,
     301,   161,   227,   315,   325,   309,    36,   147,   160,   272,
     283,   147,   160,   282,   290,   290,   121,   298,   220,    66,
      67,   221,   158,   179,   266,   210,   158,   158,   303,    89,
     159,   217,   159,   217,   122,   158,     8,   307,   293,   293,
     161,   330,   268,   313,    31,   309,   161,    71,   208,   293,
     239,   150,   252,   253,    71,   115,   157,   254,   255,   236,
     226,   225,   262,     8,   159,   233,   199,   223,   158,     8,
      31,    73,   158,   316,   164,   161,    46,   309,   309,   326,
      66,    67,   222,   157,   181,   159,    83,   158,   188,   187,
     159,   217,    92,    93,    94,   217,   161,   303,   303,    73,
     158,   159,   159,   311,    13,     8,   159,   160,    53,    55,
      56,    57,    58,   112,   146,   152,   244,   246,   247,   293,
       8,   159,    71,   146,   150,   255,   256,   257,   159,    73,
     263,   193,   237,    71,   161,   234,   158,   104,   270,   226,
      73,    13,   121,   317,   276,   161,   161,   157,    26,    68,
     309,   159,   185,    26,   181,   212,   212,    92,   159,   309,
      26,   159,   218,   161,   122,   158,   303,   293,   240,   160,
       8,   159,   287,   253,     8,    29,   158,    25,    42,    45,
      13,     8,   159,   192,   263,    13,   161,   235,   160,   157,
     160,    31,    73,    13,   303,   326,   277,   309,   179,   159,
     158,    26,   181,   211,   179,   159,   218,   179,   303,   160,
      71,   161,   177,   241,   242,   243,   248,   302,   245,    13,
     249,   256,   256,    25,    42,    45,   303,    73,    71,   159,
     303,   179,    31,    73,   271,   179,    73,    13,   303,   318,
     158,   181,   179,    87,   179,   179,   140,    90,     8,   161,
     246,   303,    51,   250,    13,   157,   161,    73,     8,   158,
     161,    13,   303,    26,    85,   159,   161,    71,   260,   261,
     302,   251,   303,   238,    31,    73,   303,   179,   159,   189,
     155,    71,   159,   153,   223,    73,   102,   208,   159,   158,
     157,   159,   159,   160,   258,   293,   179,    73,   161,   158,
     160,   179,   161
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (&yylloc, _p, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).line0   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).char0 = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).line1    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).char1  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).line0   = (Current).line1   =		\
	    YYRHSLOC (Rhs, 0).line1;				\
	  (Current).char0 = (Current).char1 =		\
	    YYRHSLOC (Rhs, 0).char1;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).line0, (Loc).char0,	\
	      (Loc).line1,  (Loc).char1)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, &yylloc, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval, &yylloc)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location, _p); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, HPHP::HPHP_PARSER_NS::Parser *_p)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, _p)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    HPHP::HPHP_PARSER_NS::Parser *_p;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
  YYUSE (_p);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, HPHP::HPHP_PARSER_NS::Parser *_p)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp, _p)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    HPHP::HPHP_PARSER_NS::Parser *_p;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, _p);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, HPHP::HPHP_PARSER_NS::Parser *_p)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule, _p)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
    HPHP::HPHP_PARSER_NS::Parser *_p;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       , _p);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule, _p); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, HPHP::HPHP_PARSER_NS::Parser *_p)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp, _p)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
    HPHP::HPHP_PARSER_NS::Parser *_p;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (_p);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (HPHP::HPHP_PARSER_NS::Parser *_p);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */





/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (HPHP::HPHP_PARSER_NS::Parser *_p)
#else
int
yyparse (_p)
    HPHP::HPHP_PARSER_NS::Parser *_p;
#endif
#endif
{
/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;

#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.line0   = yylloc.line1   = 1;
  yylloc.char0 = yylloc.char1 = 1;
#endif

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);

	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	struct yyalloc *yyptr =
	  (struct yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        memset(yyptr, 0, YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE_RESET (yyvs_alloc, yyvs);
	YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1464 of yacc.c  */
#line 964 "../../../src/util/parser/hphp.y"
    { _p->popLabelInfo();
                                         _p->saveParseTree((yyval));;}
    break;

  case 3:

/* Line 1464 of yacc.c  */
#line 970 "../../../src/util/parser/hphp.y"
    { _p->addStatement((yyval),(yyvsp[(1) - (2)]),(yyvsp[(2) - (2)]));;}
    break;

  case 4:

/* Line 1464 of yacc.c  */
#line 971 "../../../src/util/parser/hphp.y"
    { _p->onStatementListStart((yyval));;}
    break;

  case 5:

/* Line 1464 of yacc.c  */
#line 974 "../../../src/util/parser/hphp.y"
    { _p->nns((yyvsp[(1) - (1)]).num() == T_DECLARE);
                                         (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 6:

/* Line 1464 of yacc.c  */
#line 976 "../../../src/util/parser/hphp.y"
    { _p->nns(); (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 7:

/* Line 1464 of yacc.c  */
#line 977 "../../../src/util/parser/hphp.y"
    { _p->nns(); (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 8:

/* Line 1464 of yacc.c  */
#line 978 "../../../src/util/parser/hphp.y"
    { _p->nns(); (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 9:

/* Line 1464 of yacc.c  */
#line 979 "../../../src/util/parser/hphp.y"
    { (yyval).reset();;}
    break;

  case 10:

/* Line 1464 of yacc.c  */
#line 980 "../../../src/util/parser/hphp.y"
    { _p->onNamespaceStart((yyvsp[(2) - (3)]).text());
                                         (yyval).reset();;}
    break;

  case 11:

/* Line 1464 of yacc.c  */
#line 982 "../../../src/util/parser/hphp.y"
    { _p->onNamespaceStart((yyvsp[(2) - (3)]).text());;}
    break;

  case 12:

/* Line 1464 of yacc.c  */
#line 983 "../../../src/util/parser/hphp.y"
    { _p->onNamespaceEnd(); (yyval) = (yyvsp[(5) - (6)]);;}
    break;

  case 13:

/* Line 1464 of yacc.c  */
#line 984 "../../../src/util/parser/hphp.y"
    { _p->onNamespaceStart("");;}
    break;

  case 14:

/* Line 1464 of yacc.c  */
#line 985 "../../../src/util/parser/hphp.y"
    { _p->onNamespaceEnd(); (yyval) = (yyvsp[(4) - (5)]);;}
    break;

  case 15:

/* Line 1464 of yacc.c  */
#line 986 "../../../src/util/parser/hphp.y"
    { _p->nns(); (yyval).reset();;}
    break;

  case 16:

/* Line 1464 of yacc.c  */
#line 987 "../../../src/util/parser/hphp.y"
    { _p->nns();
                                         _p->finishStatement((yyval), (yyvsp[(1) - (2)])); (yyval) = 1;;}
    break;

  case 17:

/* Line 1464 of yacc.c  */
#line 993 "../../../src/util/parser/hphp.y"
    { ;}
    break;

  case 18:

/* Line 1464 of yacc.c  */
#line 994 "../../../src/util/parser/hphp.y"
    { ;}
    break;

  case 19:

/* Line 1464 of yacc.c  */
#line 997 "../../../src/util/parser/hphp.y"
    { _p->onUse((yyvsp[(1) - (1)]).text(),"");;}
    break;

  case 20:

/* Line 1464 of yacc.c  */
#line 998 "../../../src/util/parser/hphp.y"
    { _p->onUse((yyvsp[(2) - (2)]).text(),"");;}
    break;

  case 21:

/* Line 1464 of yacc.c  */
#line 999 "../../../src/util/parser/hphp.y"
    { _p->onUse((yyvsp[(1) - (3)]).text(),(yyvsp[(3) - (3)]).text());;}
    break;

  case 22:

/* Line 1464 of yacc.c  */
#line 1001 "../../../src/util/parser/hphp.y"
    { _p->onUse((yyvsp[(2) - (4)]).text(),(yyvsp[(4) - (4)]).text());;}
    break;

  case 23:

/* Line 1464 of yacc.c  */
#line 1004 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 24:

/* Line 1464 of yacc.c  */
#line 1006 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);;}
    break;

  case 25:

/* Line 1464 of yacc.c  */
#line 1009 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);
                                         (yyval).setText(_p->resolve((yyval).text(),0));;}
    break;

  case 26:

/* Line 1464 of yacc.c  */
#line 1011 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(2) - (2)]);;}
    break;

  case 27:

/* Line 1464 of yacc.c  */
#line 1013 "../../../src/util/parser/hphp.y"
    { (yyval).setText(_p->nsDecl((yyvsp[(3) - (3)]).text()));;}
    break;

  case 28:

/* Line 1464 of yacc.c  */
#line 1016 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);
                                         (yyval).setText(_p->resolve((yyval).text(),1));;}
    break;

  case 29:

/* Line 1464 of yacc.c  */
#line 1018 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(2) - (2)]);;}
    break;

  case 30:

/* Line 1464 of yacc.c  */
#line 1020 "../../../src/util/parser/hphp.y"
    { (yyval).setText(_p->nsDecl((yyvsp[(3) - (3)]).text()));;}
    break;

  case 31:

/* Line 1464 of yacc.c  */
#line 1024 "../../../src/util/parser/hphp.y"
    { (yyvsp[(3) - (5)]).setText(_p->nsDecl((yyvsp[(3) - (5)]).text()));
                                         on_constant(_p,(yyval),&(yyvsp[(1) - (5)]),(yyvsp[(3) - (5)]),(yyvsp[(5) - (5)]));;}
    break;

  case 32:

/* Line 1464 of yacc.c  */
#line 1026 "../../../src/util/parser/hphp.y"
    { (yyvsp[(2) - (4)]).setText(_p->nsDecl((yyvsp[(2) - (4)]).text()));
                                         on_constant(_p,(yyval),  0,(yyvsp[(2) - (4)]),(yyvsp[(4) - (4)]));;}
    break;

  case 33:

/* Line 1464 of yacc.c  */
#line 1032 "../../../src/util/parser/hphp.y"
    { _p->addStatement((yyval),(yyvsp[(1) - (2)]),(yyvsp[(2) - (2)]));;}
    break;

  case 34:

/* Line 1464 of yacc.c  */
#line 1033 "../../../src/util/parser/hphp.y"
    { _p->onStatementListStart((yyval));;}
    break;

  case 35:

/* Line 1464 of yacc.c  */
#line 1036 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 36:

/* Line 1464 of yacc.c  */
#line 1037 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 37:

/* Line 1464 of yacc.c  */
#line 1038 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 38:

/* Line 1464 of yacc.c  */
#line 1041 "../../../src/util/parser/hphp.y"
    { _p->onExpStatement((yyval), (yyvsp[(1) - (2)]));;}
    break;

  case 39:

/* Line 1464 of yacc.c  */
#line 1042 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 40:

/* Line 1464 of yacc.c  */
#line 1043 "../../../src/util/parser/hphp.y"
    { _p->onLabel((yyval), (yyvsp[(1) - (2)]));
                                         _p->addLabel((yyvsp[(1) - (2)]).text(),
                                                      _p->getLocation(),
                                                      &(yyval)); ;}
    break;

  case 41:

/* Line 1464 of yacc.c  */
#line 1049 "../../../src/util/parser/hphp.y"
    { _p->onBlock((yyval), (yyvsp[(2) - (3)]));;}
    break;

  case 42:

/* Line 1464 of yacc.c  */
#line 1054 "../../../src/util/parser/hphp.y"
    { _p->onIf((yyval),(yyvsp[(3) - (7)]),(yyvsp[(5) - (7)]),(yyvsp[(6) - (7)]),(yyvsp[(7) - (7)]));;}
    break;

  case 43:

/* Line 1464 of yacc.c  */
#line 1060 "../../../src/util/parser/hphp.y"
    { _p->onIf((yyval),(yyvsp[(3) - (10)]),(yyvsp[(6) - (10)]),(yyvsp[(7) - (10)]),(yyvsp[(8) - (10)]));;}
    break;

  case 44:

/* Line 1464 of yacc.c  */
#line 1062 "../../../src/util/parser/hphp.y"
    { _p->pushLabelScope();;}
    break;

  case 45:

/* Line 1464 of yacc.c  */
#line 1063 "../../../src/util/parser/hphp.y"
    { _p->popLabelScope();
                                         _p->onWhile((yyval),(yyvsp[(3) - (6)]),(yyvsp[(6) - (6)]));;}
    break;

  case 46:

/* Line 1464 of yacc.c  */
#line 1066 "../../../src/util/parser/hphp.y"
    { _p->pushLabelScope();;}
    break;

  case 47:

/* Line 1464 of yacc.c  */
#line 1067 "../../../src/util/parser/hphp.y"
    { _p->popLabelScope();
                                         _p->onDo((yyval),(yyvsp[(3) - (8)]),(yyvsp[(6) - (8)]));;}
    break;

  case 48:

/* Line 1464 of yacc.c  */
#line 1071 "../../../src/util/parser/hphp.y"
    { _p->pushLabelScope();;}
    break;

  case 49:

/* Line 1464 of yacc.c  */
#line 1072 "../../../src/util/parser/hphp.y"
    { _p->popLabelScope();
                                         _p->onFor((yyval),(yyvsp[(3) - (10)]),(yyvsp[(5) - (10)]),(yyvsp[(7) - (10)]),(yyvsp[(10) - (10)]));;}
    break;

  case 50:

/* Line 1464 of yacc.c  */
#line 1075 "../../../src/util/parser/hphp.y"
    { _p->pushLabelScope();;}
    break;

  case 51:

/* Line 1464 of yacc.c  */
#line 1076 "../../../src/util/parser/hphp.y"
    { _p->popLabelScope();
                                         _p->onSwitch((yyval),(yyvsp[(3) - (6)]),(yyvsp[(6) - (6)]));;}
    break;

  case 52:

/* Line 1464 of yacc.c  */
#line 1079 "../../../src/util/parser/hphp.y"
    { _p->onBreak((yyval), NULL);;}
    break;

  case 53:

/* Line 1464 of yacc.c  */
#line 1080 "../../../src/util/parser/hphp.y"
    { _p->onBreak((yyval), &(yyvsp[(2) - (3)]));;}
    break;

  case 54:

/* Line 1464 of yacc.c  */
#line 1082 "../../../src/util/parser/hphp.y"
    { _p->onContinue((yyval), NULL);;}
    break;

  case 55:

/* Line 1464 of yacc.c  */
#line 1083 "../../../src/util/parser/hphp.y"
    { _p->onContinue((yyval), &(yyvsp[(2) - (3)]));;}
    break;

  case 56:

/* Line 1464 of yacc.c  */
#line 1085 "../../../src/util/parser/hphp.y"
    { _p->onReturn((yyval), NULL);;}
    break;

  case 57:

/* Line 1464 of yacc.c  */
#line 1086 "../../../src/util/parser/hphp.y"
    { _p->onReturn((yyval), &(yyvsp[(2) - (3)]));;}
    break;

  case 58:

/* Line 1464 of yacc.c  */
#line 1087 "../../../src/util/parser/hphp.y"
    { _p->onReturn((yyval), &(yyvsp[(2) - (3)]));;}
    break;

  case 59:

/* Line 1464 of yacc.c  */
#line 1089 "../../../src/util/parser/hphp.y"
    { _p->onYield((yyval), NULL, false);;}
    break;

  case 60:

/* Line 1464 of yacc.c  */
#line 1090 "../../../src/util/parser/hphp.y"
    { _p->onYield((yyval), &(yyvsp[(2) - (3)]), false);;}
    break;

  case 61:

/* Line 1464 of yacc.c  */
#line 1091 "../../../src/util/parser/hphp.y"
    { _p->onYield((yyval), &(yyvsp[(2) - (3)]), false);;}
    break;

  case 62:

/* Line 1464 of yacc.c  */
#line 1093 "../../../src/util/parser/hphp.y"
    { on_yield_assign(_p, (yyval), (yyvsp[(1) - (5)]), &(yyvsp[(4) - (5)]));;}
    break;

  case 63:

/* Line 1464 of yacc.c  */
#line 1094 "../../../src/util/parser/hphp.y"
    { on_yield_assign(_p, (yyval), (yyvsp[(1) - (5)]), &(yyvsp[(4) - (5)]));;}
    break;

  case 64:

/* Line 1464 of yacc.c  */
#line 1096 "../../../src/util/parser/hphp.y"
    { on_yield_list_assign(_p, (yyval), (yyvsp[(3) - (8)]), &(yyvsp[(7) - (8)]));;}
    break;

  case 65:

/* Line 1464 of yacc.c  */
#line 1098 "../../../src/util/parser/hphp.y"
    { on_yield_list_assign(_p, (yyval), (yyvsp[(3) - (8)]), &(yyvsp[(7) - (8)]));;}
    break;

  case 66:

/* Line 1464 of yacc.c  */
#line 1100 "../../../src/util/parser/hphp.y"
    { _p->onGlobal((yyval), (yyvsp[(2) - (3)]));;}
    break;

  case 67:

/* Line 1464 of yacc.c  */
#line 1101 "../../../src/util/parser/hphp.y"
    { _p->onStatic((yyval), (yyvsp[(2) - (3)]));;}
    break;

  case 68:

/* Line 1464 of yacc.c  */
#line 1102 "../../../src/util/parser/hphp.y"
    { _p->onTypeDecl((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]));;}
    break;

  case 69:

/* Line 1464 of yacc.c  */
#line 1103 "../../../src/util/parser/hphp.y"
    { _p->onEcho((yyval), (yyvsp[(2) - (3)]), 0);;}
    break;

  case 70:

/* Line 1464 of yacc.c  */
#line 1105 "../../../src/util/parser/hphp.y"
    { _p->onUnset((yyval), (yyvsp[(3) - (5)]));;}
    break;

  case 71:

/* Line 1464 of yacc.c  */
#line 1106 "../../../src/util/parser/hphp.y"
    { (yyval).reset();;}
    break;

  case 72:

/* Line 1464 of yacc.c  */
#line 1108 "../../../src/util/parser/hphp.y"
    { _p->onEcho((yyval), (yyvsp[(1) - (1)]), 1);;}
    break;

  case 73:

/* Line 1464 of yacc.c  */
#line 1112 "../../../src/util/parser/hphp.y"
    { _p->pushLabelScope();;}
    break;

  case 74:

/* Line 1464 of yacc.c  */
#line 1113 "../../../src/util/parser/hphp.y"
    { _p->popLabelScope();
                                         _p->onForEach((yyval),(yyvsp[(3) - (9)]),(yyvsp[(5) - (9)]),(yyvsp[(6) - (9)]),(yyvsp[(9) - (9)]));;}
    break;

  case 75:

/* Line 1464 of yacc.c  */
#line 1118 "../../../src/util/parser/hphp.y"
    { _p->pushLabelScope();;}
    break;

  case 76:

/* Line 1464 of yacc.c  */
#line 1119 "../../../src/util/parser/hphp.y"
    { _p->popLabelScope();
                                         _p->onForEach((yyval),(yyvsp[(3) - (9)]),(yyvsp[(5) - (9)]),(yyvsp[(6) - (9)]),(yyvsp[(9) - (9)]));;}
    break;

  case 77:

/* Line 1464 of yacc.c  */
#line 1123 "../../../src/util/parser/hphp.y"
    { _p->onBlock((yyval), (yyvsp[(5) - (5)])); (yyval) = T_DECLARE;;}
    break;

  case 78:

/* Line 1464 of yacc.c  */
#line 1131 "../../../src/util/parser/hphp.y"
    { _p->onTry((yyval),(yyvsp[(3) - (13)]),(yyvsp[(7) - (13)]),(yyvsp[(8) - (13)]),(yyvsp[(11) - (13)]),(yyvsp[(13) - (13)]));;}
    break;

  case 79:

/* Line 1464 of yacc.c  */
#line 1133 "../../../src/util/parser/hphp.y"
    { _p->onThrow((yyval), (yyvsp[(2) - (3)]));;}
    break;

  case 80:

/* Line 1464 of yacc.c  */
#line 1134 "../../../src/util/parser/hphp.y"
    { _p->onGoto((yyval), (yyvsp[(2) - (3)]), true);
                                         _p->addGoto((yyvsp[(2) - (3)]).text(),
                                                     _p->getLocation(),
                                                     &(yyval)); ;}
    break;

  case 81:

/* Line 1464 of yacc.c  */
#line 1145 "../../../src/util/parser/hphp.y"
    { _p->onCatch((yyval), (yyvsp[(1) - (9)]), (yyvsp[(4) - (9)]), (yyvsp[(5) - (9)]), (yyvsp[(8) - (9)]));;}
    break;

  case 82:

/* Line 1464 of yacc.c  */
#line 1146 "../../../src/util/parser/hphp.y"
    { (yyval).reset();;}
    break;

  case 83:

/* Line 1464 of yacc.c  */
#line 1150 "../../../src/util/parser/hphp.y"
    { _p->onExprListElem((yyval), NULL, (yyvsp[(1) - (1)]));;}
    break;

  case 84:

/* Line 1464 of yacc.c  */
#line 1151 "../../../src/util/parser/hphp.y"
    { _p->onExprListElem((yyval), &(yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));;}
    break;

  case 85:

/* Line 1464 of yacc.c  */
#line 1154 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 86:

/* Line 1464 of yacc.c  */
#line 1158 "../../../src/util/parser/hphp.y"
    { (yyval) = 1;;}
    break;

  case 87:

/* Line 1464 of yacc.c  */
#line 1159 "../../../src/util/parser/hphp.y"
    { (yyval).reset();;}
    break;

  case 88:

/* Line 1464 of yacc.c  */
#line 1163 "../../../src/util/parser/hphp.y"
    { _p->pushFuncLocation();;}
    break;

  case 89:

/* Line 1464 of yacc.c  */
#line 1167 "../../../src/util/parser/hphp.y"
    { (yyvsp[(4) - (4)]).setText(_p->nsDecl((yyvsp[(4) - (4)]).text()));
                                         _p->onFunctionStart((yyvsp[(4) - (4)]));
                                         _p->pushLabelInfo();;}
    break;

  case 90:

/* Line 1464 of yacc.c  */
#line 1171 "../../../src/util/parser/hphp.y"
    { _p->onFunction((yyval),(yyvsp[(1) - (11)]),(yyvsp[(3) - (11)]),(yyvsp[(4) - (11)]),(yyvsp[(7) - (11)]),(yyvsp[(10) - (11)]));
                                         _p->popLabelInfo();;}
    break;

  case 91:

/* Line 1464 of yacc.c  */
#line 1177 "../../../src/util/parser/hphp.y"
    { (yyvsp[(2) - (3)]).setText(_p->nsDecl((yyvsp[(2) - (3)]).text()));
                                         _p->onClassStart((yyvsp[(1) - (3)]).num(), (yyvsp[(2) - (3)]), &(yyvsp[(3) - (3)]));;}
    break;

  case 92:

/* Line 1464 of yacc.c  */
#line 1180 "../../../src/util/parser/hphp.y"
    { _p->onClass((yyval),(yyvsp[(1) - (8)]).num(),(yyvsp[(2) - (8)]),(yyvsp[(3) - (8)]),(yyvsp[(5) - (8)]),(yyvsp[(7) - (8)]));;}
    break;

  case 93:

/* Line 1464 of yacc.c  */
#line 1183 "../../../src/util/parser/hphp.y"
    { (yyvsp[(2) - (3)]).xhpLabel();
                                         (yyvsp[(2) - (3)]).setText(_p->nsDecl((yyvsp[(2) - (3)]).text()));
                                         _p->onClassStart((yyvsp[(1) - (3)]).num(), (yyvsp[(2) - (3)]), &(yyvsp[(3) - (3)]));;}
    break;

  case 94:

/* Line 1464 of yacc.c  */
#line 1186 "../../../src/util/parser/hphp.y"
    { _p->scanner().xhpStatement();;}
    break;

  case 95:

/* Line 1464 of yacc.c  */
#line 1187 "../../../src/util/parser/hphp.y"
    { xhp_collect_attributes(_p, (yyvsp[(9) - (9)]), (yyvsp[(8) - (9)]));
                                         _p->onClass((yyval),(yyvsp[(1) - (9)]).num(),(yyvsp[(2) - (9)]),(yyvsp[(3) - (9)]),(yyvsp[(5) - (9)]),(yyvsp[(9) - (9)]));
                                         _p->xhpResetAttributes();
                                         _p->scanner().xhpReset();;}
    break;

  case 96:

/* Line 1464 of yacc.c  */
#line 1192 "../../../src/util/parser/hphp.y"
    { (yyvsp[(2) - (2)]).setText(_p->nsDecl((yyvsp[(2) - (2)]).text()));
                                         _p->onClassStart(T_INTERFACE, (yyvsp[(2) - (2)]), 0);;}
    break;

  case 97:

/* Line 1464 of yacc.c  */
#line 1195 "../../../src/util/parser/hphp.y"
    { _p->onInterface((yyval),(yyvsp[(2) - (7)]),(yyvsp[(4) - (7)]),(yyvsp[(6) - (7)]));;}
    break;

  case 98:

/* Line 1464 of yacc.c  */
#line 1198 "../../../src/util/parser/hphp.y"
    { (yyvsp[(2) - (2)]).setText(_p->nsDecl((yyvsp[(2) - (2)]).text()));
                                         _p->onClassStart(T_TRAIT, (yyvsp[(2) - (2)]), 0);;}
    break;

  case 99:

/* Line 1464 of yacc.c  */
#line 1200 "../../../src/util/parser/hphp.y"
    { Token t_ext, t_imp;
                                         t_ext.reset(); t_imp.reset();
                                         _p->onClass((yyval),T_TRAIT,(yyvsp[(2) - (6)]),t_ext,t_imp,
                                                     (yyvsp[(5) - (6)]));;}
    break;

  case 100:

/* Line 1464 of yacc.c  */
#line 1206 "../../../src/util/parser/hphp.y"
    { (yyval) = T_CLASS;;}
    break;

  case 101:

/* Line 1464 of yacc.c  */
#line 1207 "../../../src/util/parser/hphp.y"
    { (yyval) = T_ABSTRACT;;}
    break;

  case 102:

/* Line 1464 of yacc.c  */
#line 1208 "../../../src/util/parser/hphp.y"
    { (yyval) = T_FINAL;;}
    break;

  case 103:

/* Line 1464 of yacc.c  */
#line 1212 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(2) - (2)]);;}
    break;

  case 104:

/* Line 1464 of yacc.c  */
#line 1213 "../../../src/util/parser/hphp.y"
    { (yyval).reset();;}
    break;

  case 105:

/* Line 1464 of yacc.c  */
#line 1216 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(2) - (2)]);;}
    break;

  case 106:

/* Line 1464 of yacc.c  */
#line 1217 "../../../src/util/parser/hphp.y"
    { (yyval).reset();;}
    break;

  case 107:

/* Line 1464 of yacc.c  */
#line 1220 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(2) - (2)]);;}
    break;

  case 108:

/* Line 1464 of yacc.c  */
#line 1221 "../../../src/util/parser/hphp.y"
    { (yyval).reset();;}
    break;

  case 109:

/* Line 1464 of yacc.c  */
#line 1224 "../../../src/util/parser/hphp.y"
    { _p->onInterfaceName((yyval), NULL, (yyvsp[(1) - (1)]));;}
    break;

  case 110:

/* Line 1464 of yacc.c  */
#line 1226 "../../../src/util/parser/hphp.y"
    { _p->onInterfaceName((yyval), &(yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));;}
    break;

  case 111:

/* Line 1464 of yacc.c  */
#line 1229 "../../../src/util/parser/hphp.y"
    { _p->onTraitName((yyval), NULL, (yyvsp[(1) - (1)]));;}
    break;

  case 112:

/* Line 1464 of yacc.c  */
#line 1231 "../../../src/util/parser/hphp.y"
    { _p->onTraitName((yyval), &(yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));;}
    break;

  case 113:

/* Line 1464 of yacc.c  */
#line 1235 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(2) - (2)]);;}
    break;

  case 114:

/* Line 1464 of yacc.c  */
#line 1236 "../../../src/util/parser/hphp.y"
    { (yyval).reset();;}
    break;

  case 115:

/* Line 1464 of yacc.c  */
#line 1239 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 116:

/* Line 1464 of yacc.c  */
#line 1240 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(2) - (2)]); (yyval) = 1;;}
    break;

  case 117:

/* Line 1464 of yacc.c  */
#line 1244 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 118:

/* Line 1464 of yacc.c  */
#line 1246 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(2) - (4)]);;}
    break;

  case 119:

/* Line 1464 of yacc.c  */
#line 1249 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 120:

/* Line 1464 of yacc.c  */
#line 1251 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(2) - (4)]);;}
    break;

  case 121:

/* Line 1464 of yacc.c  */
#line 1254 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 122:

/* Line 1464 of yacc.c  */
#line 1256 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(2) - (4)]);;}
    break;

  case 123:

/* Line 1464 of yacc.c  */
#line 1259 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 124:

/* Line 1464 of yacc.c  */
#line 1261 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(2) - (4)]);;}
    break;

  case 127:

/* Line 1464 of yacc.c  */
#line 1271 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(2) - (3)]);;}
    break;

  case 128:

/* Line 1464 of yacc.c  */
#line 1272 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(3) - (4)]);;}
    break;

  case 129:

/* Line 1464 of yacc.c  */
#line 1273 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(2) - (4)]);;}
    break;

  case 130:

/* Line 1464 of yacc.c  */
#line 1274 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(3) - (5)]);;}
    break;

  case 131:

/* Line 1464 of yacc.c  */
#line 1279 "../../../src/util/parser/hphp.y"
    { _p->onCase((yyval),(yyvsp[(1) - (5)]),&(yyvsp[(3) - (5)]),(yyvsp[(5) - (5)]));;}
    break;

  case 132:

/* Line 1464 of yacc.c  */
#line 1281 "../../../src/util/parser/hphp.y"
    { _p->onCase((yyval),(yyvsp[(1) - (4)]),NULL,(yyvsp[(4) - (4)]));;}
    break;

  case 133:

/* Line 1464 of yacc.c  */
#line 1282 "../../../src/util/parser/hphp.y"
    { (yyval).reset();;}
    break;

  case 134:

/* Line 1464 of yacc.c  */
#line 1285 "../../../src/util/parser/hphp.y"
    { (yyval).reset();;}
    break;

  case 135:

/* Line 1464 of yacc.c  */
#line 1286 "../../../src/util/parser/hphp.y"
    { (yyval).reset();;}
    break;

  case 136:

/* Line 1464 of yacc.c  */
#line 1291 "../../../src/util/parser/hphp.y"
    { _p->onElseIf((yyval),(yyvsp[(1) - (6)]),(yyvsp[(4) - (6)]),(yyvsp[(6) - (6)]));;}
    break;

  case 137:

/* Line 1464 of yacc.c  */
#line 1292 "../../../src/util/parser/hphp.y"
    { (yyval).reset();;}
    break;

  case 138:

/* Line 1464 of yacc.c  */
#line 1297 "../../../src/util/parser/hphp.y"
    { _p->onElseIf((yyval),(yyvsp[(1) - (7)]),(yyvsp[(4) - (7)]),(yyvsp[(7) - (7)]));;}
    break;

  case 139:

/* Line 1464 of yacc.c  */
#line 1298 "../../../src/util/parser/hphp.y"
    { (yyval).reset();;}
    break;

  case 140:

/* Line 1464 of yacc.c  */
#line 1301 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(2) - (2)]);;}
    break;

  case 141:

/* Line 1464 of yacc.c  */
#line 1302 "../../../src/util/parser/hphp.y"
    { (yyval).reset();;}
    break;

  case 142:

/* Line 1464 of yacc.c  */
#line 1305 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(3) - (3)]);;}
    break;

  case 143:

/* Line 1464 of yacc.c  */
#line 1306 "../../../src/util/parser/hphp.y"
    { (yyval).reset();;}
    break;

  case 144:

/* Line 1464 of yacc.c  */
#line 1310 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 145:

/* Line 1464 of yacc.c  */
#line 1311 "../../../src/util/parser/hphp.y"
    { (yyval).reset();;}
    break;

  case 146:

/* Line 1464 of yacc.c  */
#line 1314 "../../../src/util/parser/hphp.y"
    { _p->onParam((yyval),NULL,(yyvsp[(1) - (2)]),(yyvsp[(2) - (2)]),0,NULL);;}
    break;

  case 147:

/* Line 1464 of yacc.c  */
#line 1315 "../../../src/util/parser/hphp.y"
    { _p->onParam((yyval),NULL,(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),1,NULL);;}
    break;

  case 148:

/* Line 1464 of yacc.c  */
#line 1317 "../../../src/util/parser/hphp.y"
    { _p->onParam((yyval),NULL,(yyvsp[(1) - (5)]),(yyvsp[(3) - (5)]),1,&(yyvsp[(5) - (5)]));;}
    break;

  case 149:

/* Line 1464 of yacc.c  */
#line 1319 "../../../src/util/parser/hphp.y"
    { _p->onParam((yyval),NULL,(yyvsp[(1) - (4)]),(yyvsp[(2) - (4)]),0,&(yyvsp[(4) - (4)]));;}
    break;

  case 150:

/* Line 1464 of yacc.c  */
#line 1321 "../../../src/util/parser/hphp.y"
    { _p->onParam((yyval),&(yyvsp[(1) - (4)]),(yyvsp[(3) - (4)]),(yyvsp[(4) - (4)]),0,NULL);;}
    break;

  case 151:

/* Line 1464 of yacc.c  */
#line 1323 "../../../src/util/parser/hphp.y"
    { _p->onParam((yyval),&(yyvsp[(1) - (5)]),(yyvsp[(3) - (5)]),(yyvsp[(5) - (5)]),1,NULL);;}
    break;

  case 152:

/* Line 1464 of yacc.c  */
#line 1326 "../../../src/util/parser/hphp.y"
    { _p->onParam((yyval),&(yyvsp[(1) - (7)]),(yyvsp[(3) - (7)]),(yyvsp[(5) - (7)]),1,&(yyvsp[(7) - (7)]));;}
    break;

  case 153:

/* Line 1464 of yacc.c  */
#line 1329 "../../../src/util/parser/hphp.y"
    { _p->onParam((yyval),&(yyvsp[(1) - (6)]),(yyvsp[(3) - (6)]),(yyvsp[(4) - (6)]),0,&(yyvsp[(6) - (6)]));;}
    break;

  case 154:

/* Line 1464 of yacc.c  */
#line 1332 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 155:

/* Line 1464 of yacc.c  */
#line 1333 "../../../src/util/parser/hphp.y"
    { (yyval).setText("array");;}
    break;

  case 156:

/* Line 1464 of yacc.c  */
#line 1334 "../../../src/util/parser/hphp.y"
    { (yyvsp[(1) - (1)]).xhpLabel(); (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 157:

/* Line 1464 of yacc.c  */
#line 1337 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 158:

/* Line 1464 of yacc.c  */
#line 1338 "../../../src/util/parser/hphp.y"
    { (yyval).reset();;}
    break;

  case 159:

/* Line 1464 of yacc.c  */
#line 1342 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 160:

/* Line 1464 of yacc.c  */
#line 1343 "../../../src/util/parser/hphp.y"
    { (yyval).reset();;}
    break;

  case 161:

/* Line 1464 of yacc.c  */
#line 1346 "../../../src/util/parser/hphp.y"
    { _p->onCallParam((yyval),NULL,(yyvsp[(1) - (1)]),0);;}
    break;

  case 162:

/* Line 1464 of yacc.c  */
#line 1347 "../../../src/util/parser/hphp.y"
    { _p->onCallParam((yyval),NULL,(yyvsp[(1) - (1)]),0);;}
    break;

  case 163:

/* Line 1464 of yacc.c  */
#line 1348 "../../../src/util/parser/hphp.y"
    { _p->onCallParam((yyval),NULL,(yyvsp[(2) - (2)]),1);;}
    break;

  case 164:

/* Line 1464 of yacc.c  */
#line 1350 "../../../src/util/parser/hphp.y"
    { _p->onCallParam((yyval),&(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),0);;}
    break;

  case 165:

/* Line 1464 of yacc.c  */
#line 1352 "../../../src/util/parser/hphp.y"
    { _p->onCallParam((yyval),&(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),0);;}
    break;

  case 166:

/* Line 1464 of yacc.c  */
#line 1354 "../../../src/util/parser/hphp.y"
    { _p->onCallParam((yyval),&(yyvsp[(1) - (4)]),(yyvsp[(4) - (4)]),1);;}
    break;

  case 167:

/* Line 1464 of yacc.c  */
#line 1358 "../../../src/util/parser/hphp.y"
    { _p->onGlobalVar((yyval), &(yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));;}
    break;

  case 168:

/* Line 1464 of yacc.c  */
#line 1359 "../../../src/util/parser/hphp.y"
    { _p->onGlobalVar((yyval), NULL, (yyvsp[(1) - (1)]));;}
    break;

  case 169:

/* Line 1464 of yacc.c  */
#line 1362 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 170:

/* Line 1464 of yacc.c  */
#line 1363 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(2) - (2)]); (yyval) = 1;;}
    break;

  case 171:

/* Line 1464 of yacc.c  */
#line 1364 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(3) - (4)]); (yyval) = 1;;}
    break;

  case 172:

/* Line 1464 of yacc.c  */
#line 1368 "../../../src/util/parser/hphp.y"
    { _p->onStaticVariable((yyval),&(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),0);;}
    break;

  case 173:

/* Line 1464 of yacc.c  */
#line 1370 "../../../src/util/parser/hphp.y"
    { _p->onStaticVariable((yyval),&(yyvsp[(1) - (5)]),(yyvsp[(3) - (5)]),&(yyvsp[(5) - (5)]));;}
    break;

  case 174:

/* Line 1464 of yacc.c  */
#line 1371 "../../../src/util/parser/hphp.y"
    { _p->onStaticVariable((yyval),0,(yyvsp[(1) - (1)]),0);;}
    break;

  case 175:

/* Line 1464 of yacc.c  */
#line 1372 "../../../src/util/parser/hphp.y"
    { _p->onStaticVariable((yyval),0,(yyvsp[(1) - (3)]),&(yyvsp[(3) - (3)]));;}
    break;

  case 176:

/* Line 1464 of yacc.c  */
#line 1376 "../../../src/util/parser/hphp.y"
    { _p->onTypedVariable((yyval),&(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),0);;}
    break;

  case 177:

/* Line 1464 of yacc.c  */
#line 1377 "../../../src/util/parser/hphp.y"
    { _p->onTypedVariable((yyval),&(yyvsp[(1) - (5)]),(yyvsp[(3) - (5)]),&(yyvsp[(5) - (5)]));;}
    break;

  case 178:

/* Line 1464 of yacc.c  */
#line 1378 "../../../src/util/parser/hphp.y"
    { _p->onTypedVariable((yyval),0,(yyvsp[(1) - (1)]),0);;}
    break;

  case 179:

/* Line 1464 of yacc.c  */
#line 1379 "../../../src/util/parser/hphp.y"
    { _p->onTypedVariable((yyval),0,(yyvsp[(1) - (3)]),&(yyvsp[(3) - (3)]));;}
    break;

  case 180:

/* Line 1464 of yacc.c  */
#line 1384 "../../../src/util/parser/hphp.y"
    { _p->onClassStatement((yyval), (yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));;}
    break;

  case 181:

/* Line 1464 of yacc.c  */
#line 1385 "../../../src/util/parser/hphp.y"
    { (yyval).reset();;}
    break;

  case 182:

/* Line 1464 of yacc.c  */
#line 1389 "../../../src/util/parser/hphp.y"
    { _p->onClassStatement((yyval), (yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
                                         _p->scanner().xhpStatement();;}
    break;

  case 183:

/* Line 1464 of yacc.c  */
#line 1391 "../../../src/util/parser/hphp.y"
    { (yyval).reset();;}
    break;

  case 184:

/* Line 1464 of yacc.c  */
#line 1394 "../../../src/util/parser/hphp.y"
    { _p->onClassVariableModifer((yyvsp[(1) - (1)]));;}
    break;

  case 185:

/* Line 1464 of yacc.c  */
#line 1395 "../../../src/util/parser/hphp.y"
    { _p->onClassVariableStart
                                         ((yyval),&(yyvsp[(1) - (4)]),(yyvsp[(3) - (4)]),NULL);;}
    break;

  case 186:

/* Line 1464 of yacc.c  */
#line 1398 "../../../src/util/parser/hphp.y"
    { _p->onClassVariableModifer((yyvsp[(1) - (2)]));;}
    break;

  case 187:

/* Line 1464 of yacc.c  */
#line 1399 "../../../src/util/parser/hphp.y"
    { _p->onClassVariableStart
                                         ((yyval),&(yyvsp[(1) - (5)]),(yyvsp[(4) - (5)]),&(yyvsp[(2) - (5)]));;}
    break;

  case 188:

/* Line 1464 of yacc.c  */
#line 1401 "../../../src/util/parser/hphp.y"
    { _p->onClassVariableStart
                                         ((yyval),NULL,(yyvsp[(1) - (2)]),NULL);;}
    break;

  case 189:

/* Line 1464 of yacc.c  */
#line 1405 "../../../src/util/parser/hphp.y"
    { _p->onMethodStart((yyvsp[(5) - (6)]), (yyvsp[(1) - (6)]));
                                         _p->pushLabelInfo();;}
    break;

  case 190:

/* Line 1464 of yacc.c  */
#line 1407 "../../../src/util/parser/hphp.y"
    { _p->onMethod((yyval),(yyvsp[(1) - (10)]),(yyvsp[(2) - (10)]),(yyvsp[(4) - (10)]),(yyvsp[(5) - (10)]),(yyvsp[(8) - (10)]),(yyvsp[(10) - (10)]));
                                         _p->popLabelInfo();;}
    break;

  case 191:

/* Line 1464 of yacc.c  */
#line 1409 "../../../src/util/parser/hphp.y"
    { _p->scanner().xhpAttributeDecl();;}
    break;

  case 192:

/* Line 1464 of yacc.c  */
#line 1410 "../../../src/util/parser/hphp.y"
    { _p->xhpSetAttributes((yyvsp[(3) - (4)]));;}
    break;

  case 193:

/* Line 1464 of yacc.c  */
#line 1412 "../../../src/util/parser/hphp.y"
    { xhp_category_stmt(_p,(yyval),(yyvsp[(2) - (3)]));;}
    break;

  case 194:

/* Line 1464 of yacc.c  */
#line 1414 "../../../src/util/parser/hphp.y"
    { xhp_children_stmt(_p,(yyval),(yyvsp[(2) - (3)]));;}
    break;

  case 195:

/* Line 1464 of yacc.c  */
#line 1415 "../../../src/util/parser/hphp.y"
    { Token t; t.reset();
                                         _p->onTraitUse((yyval),(yyvsp[(2) - (3)]),t); ;}
    break;

  case 196:

/* Line 1464 of yacc.c  */
#line 1418 "../../../src/util/parser/hphp.y"
    { _p->onTraitUse((yyval),(yyvsp[(2) - (5)]),(yyvsp[(4) - (5)])); ;}
    break;

  case 197:

/* Line 1464 of yacc.c  */
#line 1421 "../../../src/util/parser/hphp.y"
    { _p->onTraitRule((yyval),(yyvsp[(1) - (2)]),(yyvsp[(2) - (2)])); ;}
    break;

  case 198:

/* Line 1464 of yacc.c  */
#line 1422 "../../../src/util/parser/hphp.y"
    { _p->onTraitRule((yyval),(yyvsp[(1) - (2)]),(yyvsp[(2) - (2)])); ;}
    break;

  case 199:

/* Line 1464 of yacc.c  */
#line 1423 "../../../src/util/parser/hphp.y"
    { (yyval).reset(); ;}
    break;

  case 200:

/* Line 1464 of yacc.c  */
#line 1429 "../../../src/util/parser/hphp.y"
    { _p->onTraitPrecRule((yyval),(yyvsp[(1) - (6)]),(yyvsp[(3) - (6)]),(yyvsp[(5) - (6)])); ;}
    break;

  case 201:

/* Line 1464 of yacc.c  */
#line 1433 "../../../src/util/parser/hphp.y"
    { _p->onTraitAliasRuleModify((yyval),(yyvsp[(1) - (5)]),(yyvsp[(3) - (5)]),
                                                                    (yyvsp[(4) - (5)]));;}
    break;

  case 202:

/* Line 1464 of yacc.c  */
#line 1436 "../../../src/util/parser/hphp.y"
    { Token t; t.reset();
                                         _p->onTraitAliasRuleModify((yyval),(yyvsp[(1) - (4)]),(yyvsp[(3) - (4)]),
                                                                    t);;}
    break;

  case 203:

/* Line 1464 of yacc.c  */
#line 1443 "../../../src/util/parser/hphp.y"
    { _p->onTraitAliasRuleStart((yyval),(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]));;}
    break;

  case 204:

/* Line 1464 of yacc.c  */
#line 1444 "../../../src/util/parser/hphp.y"
    { Token t; t.reset();
                                         _p->onTraitAliasRuleStart((yyval),t,(yyvsp[(1) - (1)]));;}
    break;

  case 205:

/* Line 1464 of yacc.c  */
#line 1448 "../../../src/util/parser/hphp.y"
    { xhp_attribute_list(_p,(yyval),
                                         _p->xhpGetAttributes(),(yyvsp[(1) - (1)]));;}
    break;

  case 206:

/* Line 1464 of yacc.c  */
#line 1450 "../../../src/util/parser/hphp.y"
    { _p->scanner().xhpAttributeDecl();;}
    break;

  case 207:

/* Line 1464 of yacc.c  */
#line 1451 "../../../src/util/parser/hphp.y"
    { xhp_attribute_list(_p,(yyval), &(yyvsp[(1) - (4)]),(yyvsp[(4) - (4)]));;}
    break;

  case 208:

/* Line 1464 of yacc.c  */
#line 1458 "../../../src/util/parser/hphp.y"
    { xhp_attribute(_p,(yyval),(yyvsp[(1) - (4)]),(yyvsp[(2) - (4)]),(yyvsp[(3) - (4)]),(yyvsp[(4) - (4)]));
                                         (yyval) = 1;;}
    break;

  case 209:

/* Line 1464 of yacc.c  */
#line 1460 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]); (yyval) = 0;;}
    break;

  case 210:

/* Line 1464 of yacc.c  */
#line 1464 "../../../src/util/parser/hphp.y"
    { (yyval) = 1;;}
    break;

  case 211:

/* Line 1464 of yacc.c  */
#line 1465 "../../../src/util/parser/hphp.y"
    { (yyval) = 2;;}
    break;

  case 212:

/* Line 1464 of yacc.c  */
#line 1466 "../../../src/util/parser/hphp.y"
    { (yyval) = 3;;}
    break;

  case 213:

/* Line 1464 of yacc.c  */
#line 1467 "../../../src/util/parser/hphp.y"
    { (yyval) = 4;;}
    break;

  case 214:

/* Line 1464 of yacc.c  */
#line 1468 "../../../src/util/parser/hphp.y"
    { (yyval) = 5; (yyval).setText((yyvsp[(1) - (1)]));;}
    break;

  case 215:

/* Line 1464 of yacc.c  */
#line 1469 "../../../src/util/parser/hphp.y"
    { (yyval) = 6;;}
    break;

  case 216:

/* Line 1464 of yacc.c  */
#line 1471 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(3) - (4)]); (yyval) = 7;;}
    break;

  case 217:

/* Line 1464 of yacc.c  */
#line 1472 "../../../src/util/parser/hphp.y"
    { (yyval) = 8;;}
    break;

  case 218:

/* Line 1464 of yacc.c  */
#line 1476 "../../../src/util/parser/hphp.y"
    { _p->onArrayPair((yyval),  0,0,(yyvsp[(1) - (1)]),0);;}
    break;

  case 219:

/* Line 1464 of yacc.c  */
#line 1478 "../../../src/util/parser/hphp.y"
    { _p->onArrayPair((yyval),&(yyvsp[(1) - (3)]),0,(yyvsp[(3) - (3)]),0);;}
    break;

  case 220:

/* Line 1464 of yacc.c  */
#line 1482 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(2) - (2)]);;}
    break;

  case 221:

/* Line 1464 of yacc.c  */
#line 1483 "../../../src/util/parser/hphp.y"
    { scalar_null(_p, (yyval));;}
    break;

  case 222:

/* Line 1464 of yacc.c  */
#line 1487 "../../../src/util/parser/hphp.y"
    { _p->scanner().xhpAttributeDecl();;}
    break;

  case 223:

/* Line 1464 of yacc.c  */
#line 1488 "../../../src/util/parser/hphp.y"
    { scalar_num(_p, (yyval), "1");;}
    break;

  case 224:

/* Line 1464 of yacc.c  */
#line 1489 "../../../src/util/parser/hphp.y"
    { scalar_num(_p, (yyval), "0");;}
    break;

  case 225:

/* Line 1464 of yacc.c  */
#line 1493 "../../../src/util/parser/hphp.y"
    { Token t; scalar_num(_p, t, "1");
                                         _p->onArrayPair((yyval),0,&(yyvsp[(1) - (1)]),t,0);;}
    break;

  case 226:

/* Line 1464 of yacc.c  */
#line 1496 "../../../src/util/parser/hphp.y"
    { Token t; scalar_num(_p, t, "1");
                                         _p->onArrayPair((yyval),&(yyvsp[(1) - (3)]),&(yyvsp[(3) - (3)]),t,0);;}
    break;

  case 227:

/* Line 1464 of yacc.c  */
#line 1501 "../../../src/util/parser/hphp.y"
    { _p->onScalar((yyval),
                                         T_CONSTANT_ENCAPSED_STRING, (yyvsp[(1) - (1)]));;}
    break;

  case 228:

/* Line 1464 of yacc.c  */
#line 1506 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]); (yyval) = 2;;}
    break;

  case 229:

/* Line 1464 of yacc.c  */
#line 1507 "../../../src/util/parser/hphp.y"
    { (yyval) = -1;
                                         if ((yyvsp[(1) - (1)]).same("any")) (yyval) = 1;;}
    break;

  case 230:

/* Line 1464 of yacc.c  */
#line 1509 "../../../src/util/parser/hphp.y"
    { (yyval) = 0;;}
    break;

  case 231:

/* Line 1464 of yacc.c  */
#line 1513 "../../../src/util/parser/hphp.y"
    { xhp_children_paren(_p, (yyval), (yyvsp[(2) - (3)]), 0);;}
    break;

  case 232:

/* Line 1464 of yacc.c  */
#line 1514 "../../../src/util/parser/hphp.y"
    { xhp_children_paren(_p, (yyval), (yyvsp[(2) - (4)]), 1);;}
    break;

  case 233:

/* Line 1464 of yacc.c  */
#line 1515 "../../../src/util/parser/hphp.y"
    { xhp_children_paren(_p, (yyval), (yyvsp[(2) - (4)]), 2);;}
    break;

  case 234:

/* Line 1464 of yacc.c  */
#line 1516 "../../../src/util/parser/hphp.y"
    { xhp_children_paren(_p, (yyval), (yyvsp[(2) - (4)]), 3);;}
    break;

  case 235:

/* Line 1464 of yacc.c  */
#line 1520 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 236:

/* Line 1464 of yacc.c  */
#line 1521 "../../../src/util/parser/hphp.y"
    { xhp_children_decl(_p,(yyval),(yyvsp[(1) - (1)]),0,  0);;}
    break;

  case 237:

/* Line 1464 of yacc.c  */
#line 1522 "../../../src/util/parser/hphp.y"
    { xhp_children_decl(_p,(yyval),(yyvsp[(1) - (2)]),1,  0);;}
    break;

  case 238:

/* Line 1464 of yacc.c  */
#line 1523 "../../../src/util/parser/hphp.y"
    { xhp_children_decl(_p,(yyval),(yyvsp[(1) - (2)]),2,  0);;}
    break;

  case 239:

/* Line 1464 of yacc.c  */
#line 1524 "../../../src/util/parser/hphp.y"
    { xhp_children_decl(_p,(yyval),(yyvsp[(1) - (2)]),3,  0);;}
    break;

  case 240:

/* Line 1464 of yacc.c  */
#line 1526 "../../../src/util/parser/hphp.y"
    { xhp_children_decl(_p,(yyval),(yyvsp[(1) - (3)]),4,&(yyvsp[(3) - (3)]));;}
    break;

  case 241:

/* Line 1464 of yacc.c  */
#line 1528 "../../../src/util/parser/hphp.y"
    { xhp_children_decl(_p,(yyval),(yyvsp[(1) - (3)]),5,&(yyvsp[(3) - (3)]));;}
    break;

  case 242:

/* Line 1464 of yacc.c  */
#line 1532 "../../../src/util/parser/hphp.y"
    { (yyval) = -1;
                                         if ((yyvsp[(1) - (1)]).same("any")) (yyval) = 1; else
                                         if ((yyvsp[(1) - (1)]).same("pcdata")) (yyval) = 2;;}
    break;

  case 243:

/* Line 1464 of yacc.c  */
#line 1535 "../../../src/util/parser/hphp.y"
    { (yyvsp[(1) - (1)]).xhpLabel();  (yyval) = (yyvsp[(1) - (1)]); (yyval) = 3;;}
    break;

  case 244:

/* Line 1464 of yacc.c  */
#line 1536 "../../../src/util/parser/hphp.y"
    { (yyvsp[(1) - (1)]).xhpLabel(0); (yyval) = (yyvsp[(1) - (1)]); (yyval) = 4;;}
    break;

  case 245:

/* Line 1464 of yacc.c  */
#line 1540 "../../../src/util/parser/hphp.y"
    { (yyval).reset();;}
    break;

  case 246:

/* Line 1464 of yacc.c  */
#line 1541 "../../../src/util/parser/hphp.y"
    { _p->finishStatement((yyval), (yyvsp[(2) - (3)])); (yyval) = 1;;}
    break;

  case 247:

/* Line 1464 of yacc.c  */
#line 1544 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 248:

/* Line 1464 of yacc.c  */
#line 1545 "../../../src/util/parser/hphp.y"
    { (yyval).reset();;}
    break;

  case 249:

/* Line 1464 of yacc.c  */
#line 1548 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 250:

/* Line 1464 of yacc.c  */
#line 1549 "../../../src/util/parser/hphp.y"
    { (yyval).reset();;}
    break;

  case 251:

/* Line 1464 of yacc.c  */
#line 1552 "../../../src/util/parser/hphp.y"
    { _p->onMemberModifier((yyval),NULL,(yyvsp[(1) - (1)]));;}
    break;

  case 252:

/* Line 1464 of yacc.c  */
#line 1554 "../../../src/util/parser/hphp.y"
    { _p->onMemberModifier((yyval),&(yyvsp[(1) - (2)]),(yyvsp[(2) - (2)]));;}
    break;

  case 253:

/* Line 1464 of yacc.c  */
#line 1557 "../../../src/util/parser/hphp.y"
    { (yyval) = T_PUBLIC;;}
    break;

  case 254:

/* Line 1464 of yacc.c  */
#line 1558 "../../../src/util/parser/hphp.y"
    { (yyval) = T_PROTECTED;;}
    break;

  case 255:

/* Line 1464 of yacc.c  */
#line 1559 "../../../src/util/parser/hphp.y"
    { (yyval) = T_PRIVATE;;}
    break;

  case 256:

/* Line 1464 of yacc.c  */
#line 1560 "../../../src/util/parser/hphp.y"
    { (yyval) = T_STATIC;;}
    break;

  case 257:

/* Line 1464 of yacc.c  */
#line 1561 "../../../src/util/parser/hphp.y"
    { (yyval) = T_ABSTRACT;;}
    break;

  case 258:

/* Line 1464 of yacc.c  */
#line 1562 "../../../src/util/parser/hphp.y"
    { (yyval) = T_FINAL;;}
    break;

  case 259:

/* Line 1464 of yacc.c  */
#line 1566 "../../../src/util/parser/hphp.y"
    { _p->onClassVariable((yyval),&(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),0);;}
    break;

  case 260:

/* Line 1464 of yacc.c  */
#line 1568 "../../../src/util/parser/hphp.y"
    { _p->onClassVariable((yyval),&(yyvsp[(1) - (5)]),(yyvsp[(3) - (5)]),&(yyvsp[(5) - (5)]));;}
    break;

  case 261:

/* Line 1464 of yacc.c  */
#line 1569 "../../../src/util/parser/hphp.y"
    { _p->onClassVariable((yyval),0,(yyvsp[(1) - (1)]),0);;}
    break;

  case 262:

/* Line 1464 of yacc.c  */
#line 1570 "../../../src/util/parser/hphp.y"
    { _p->onClassVariable((yyval),0,(yyvsp[(1) - (3)]),&(yyvsp[(3) - (3)]));;}
    break;

  case 263:

/* Line 1464 of yacc.c  */
#line 1574 "../../../src/util/parser/hphp.y"
    { _p->onClassConstant((yyval),&(yyvsp[(1) - (5)]),(yyvsp[(3) - (5)]),(yyvsp[(5) - (5)]));;}
    break;

  case 264:

/* Line 1464 of yacc.c  */
#line 1575 "../../../src/util/parser/hphp.y"
    { _p->onClassConstant((yyval),0,(yyvsp[(2) - (4)]),(yyvsp[(4) - (4)]));;}
    break;

  case 265:

/* Line 1464 of yacc.c  */
#line 1579 "../../../src/util/parser/hphp.y"
    { _p->onExprListElem((yyval), &(yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));;}
    break;

  case 266:

/* Line 1464 of yacc.c  */
#line 1580 "../../../src/util/parser/hphp.y"
    { _p->onExprListElem((yyval), NULL, (yyvsp[(1) - (1)]));;}
    break;

  case 267:

/* Line 1464 of yacc.c  */
#line 1584 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 268:

/* Line 1464 of yacc.c  */
#line 1585 "../../../src/util/parser/hphp.y"
    { (yyval).reset();;}
    break;

  case 269:

/* Line 1464 of yacc.c  */
#line 1588 "../../../src/util/parser/hphp.y"
    { _p->onExprListElem((yyval), &(yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));;}
    break;

  case 270:

/* Line 1464 of yacc.c  */
#line 1589 "../../../src/util/parser/hphp.y"
    { _p->onExprListElem((yyval), NULL, (yyvsp[(1) - (1)]));;}
    break;

  case 271:

/* Line 1464 of yacc.c  */
#line 1594 "../../../src/util/parser/hphp.y"
    { _p->onListAssignment((yyval), (yyvsp[(3) - (6)]), &(yyvsp[(6) - (6)]));;}
    break;

  case 272:

/* Line 1464 of yacc.c  */
#line 1595 "../../../src/util/parser/hphp.y"
    { _p->onAssign((yyval), (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), 0);;}
    break;

  case 273:

/* Line 1464 of yacc.c  */
#line 1596 "../../../src/util/parser/hphp.y"
    { _p->onAssign((yyval), (yyvsp[(1) - (4)]), (yyvsp[(4) - (4)]), 1);;}
    break;

  case 274:

/* Line 1464 of yacc.c  */
#line 1599 "../../../src/util/parser/hphp.y"
    { _p->onAssignNew((yyval),(yyvsp[(1) - (6)]),(yyvsp[(5) - (6)]),(yyvsp[(6) - (6)]));;}
    break;

  case 275:

/* Line 1464 of yacc.c  */
#line 1601 "../../../src/util/parser/hphp.y"
    { _p->onNewObject((yyval), (yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]));;}
    break;

  case 276:

/* Line 1464 of yacc.c  */
#line 1602 "../../../src/util/parser/hphp.y"
    { UEXP((yyval),(yyvsp[(2) - (2)]),T_CLONE,1);;}
    break;

  case 277:

/* Line 1464 of yacc.c  */
#line 1603 "../../../src/util/parser/hphp.y"
    { BEXP((yyval),(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),T_PLUS_EQUAL);;}
    break;

  case 278:

/* Line 1464 of yacc.c  */
#line 1604 "../../../src/util/parser/hphp.y"
    { BEXP((yyval),(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),T_MINUS_EQUAL);;}
    break;

  case 279:

/* Line 1464 of yacc.c  */
#line 1605 "../../../src/util/parser/hphp.y"
    { BEXP((yyval),(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),T_MUL_EQUAL);;}
    break;

  case 280:

/* Line 1464 of yacc.c  */
#line 1606 "../../../src/util/parser/hphp.y"
    { BEXP((yyval),(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),T_DIV_EQUAL);;}
    break;

  case 281:

/* Line 1464 of yacc.c  */
#line 1607 "../../../src/util/parser/hphp.y"
    { BEXP((yyval),(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),T_CONCAT_EQUAL);;}
    break;

  case 282:

/* Line 1464 of yacc.c  */
#line 1608 "../../../src/util/parser/hphp.y"
    { BEXP((yyval),(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),T_MOD_EQUAL);;}
    break;

  case 283:

/* Line 1464 of yacc.c  */
#line 1609 "../../../src/util/parser/hphp.y"
    { BEXP((yyval),(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),T_AND_EQUAL);;}
    break;

  case 284:

/* Line 1464 of yacc.c  */
#line 1610 "../../../src/util/parser/hphp.y"
    { BEXP((yyval),(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),T_OR_EQUAL);;}
    break;

  case 285:

/* Line 1464 of yacc.c  */
#line 1611 "../../../src/util/parser/hphp.y"
    { BEXP((yyval),(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),T_XOR_EQUAL);;}
    break;

  case 286:

/* Line 1464 of yacc.c  */
#line 1612 "../../../src/util/parser/hphp.y"
    { BEXP((yyval),(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),T_SL_EQUAL);;}
    break;

  case 287:

/* Line 1464 of yacc.c  */
#line 1613 "../../../src/util/parser/hphp.y"
    { BEXP((yyval),(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),T_SR_EQUAL);;}
    break;

  case 288:

/* Line 1464 of yacc.c  */
#line 1614 "../../../src/util/parser/hphp.y"
    { UEXP((yyval),(yyvsp[(1) - (2)]),T_INC,0);;}
    break;

  case 289:

/* Line 1464 of yacc.c  */
#line 1615 "../../../src/util/parser/hphp.y"
    { UEXP((yyval),(yyvsp[(2) - (2)]),T_INC,1);;}
    break;

  case 290:

/* Line 1464 of yacc.c  */
#line 1616 "../../../src/util/parser/hphp.y"
    { UEXP((yyval),(yyvsp[(1) - (2)]),T_DEC,0);;}
    break;

  case 291:

/* Line 1464 of yacc.c  */
#line 1617 "../../../src/util/parser/hphp.y"
    { UEXP((yyval),(yyvsp[(2) - (2)]),T_DEC,1);;}
    break;

  case 292:

/* Line 1464 of yacc.c  */
#line 1618 "../../../src/util/parser/hphp.y"
    { BEXP((yyval),(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),T_BOOLEAN_OR);;}
    break;

  case 293:

/* Line 1464 of yacc.c  */
#line 1619 "../../../src/util/parser/hphp.y"
    { BEXP((yyval),(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),T_BOOLEAN_AND);;}
    break;

  case 294:

/* Line 1464 of yacc.c  */
#line 1620 "../../../src/util/parser/hphp.y"
    { BEXP((yyval),(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),T_LOGICAL_OR);;}
    break;

  case 295:

/* Line 1464 of yacc.c  */
#line 1621 "../../../src/util/parser/hphp.y"
    { BEXP((yyval),(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),T_LOGICAL_AND);;}
    break;

  case 296:

/* Line 1464 of yacc.c  */
#line 1622 "../../../src/util/parser/hphp.y"
    { BEXP((yyval),(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),T_LOGICAL_XOR);;}
    break;

  case 297:

/* Line 1464 of yacc.c  */
#line 1623 "../../../src/util/parser/hphp.y"
    { BEXP((yyval),(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),'|');;}
    break;

  case 298:

/* Line 1464 of yacc.c  */
#line 1624 "../../../src/util/parser/hphp.y"
    { BEXP((yyval),(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),'&');;}
    break;

  case 299:

/* Line 1464 of yacc.c  */
#line 1625 "../../../src/util/parser/hphp.y"
    { BEXP((yyval),(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),'^');;}
    break;

  case 300:

/* Line 1464 of yacc.c  */
#line 1626 "../../../src/util/parser/hphp.y"
    { BEXP((yyval),(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),'.');;}
    break;

  case 301:

/* Line 1464 of yacc.c  */
#line 1627 "../../../src/util/parser/hphp.y"
    { BEXP((yyval),(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),'+');;}
    break;

  case 302:

/* Line 1464 of yacc.c  */
#line 1628 "../../../src/util/parser/hphp.y"
    { BEXP((yyval),(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),'-');;}
    break;

  case 303:

/* Line 1464 of yacc.c  */
#line 1629 "../../../src/util/parser/hphp.y"
    { BEXP((yyval),(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),'*');;}
    break;

  case 304:

/* Line 1464 of yacc.c  */
#line 1630 "../../../src/util/parser/hphp.y"
    { BEXP((yyval),(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),'/');;}
    break;

  case 305:

/* Line 1464 of yacc.c  */
#line 1631 "../../../src/util/parser/hphp.y"
    { BEXP((yyval),(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),'%');;}
    break;

  case 306:

/* Line 1464 of yacc.c  */
#line 1632 "../../../src/util/parser/hphp.y"
    { BEXP((yyval),(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),T_SL);;}
    break;

  case 307:

/* Line 1464 of yacc.c  */
#line 1633 "../../../src/util/parser/hphp.y"
    { BEXP((yyval),(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),T_SR);;}
    break;

  case 308:

/* Line 1464 of yacc.c  */
#line 1634 "../../../src/util/parser/hphp.y"
    { UEXP((yyval),(yyvsp[(2) - (2)]),'+',1);;}
    break;

  case 309:

/* Line 1464 of yacc.c  */
#line 1635 "../../../src/util/parser/hphp.y"
    { UEXP((yyval),(yyvsp[(2) - (2)]),'-',1);;}
    break;

  case 310:

/* Line 1464 of yacc.c  */
#line 1636 "../../../src/util/parser/hphp.y"
    { UEXP((yyval),(yyvsp[(2) - (2)]),'!',1);;}
    break;

  case 311:

/* Line 1464 of yacc.c  */
#line 1637 "../../../src/util/parser/hphp.y"
    { UEXP((yyval),(yyvsp[(2) - (2)]),'~',1);;}
    break;

  case 312:

/* Line 1464 of yacc.c  */
#line 1638 "../../../src/util/parser/hphp.y"
    { BEXP((yyval),(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),T_IS_IDENTICAL);;}
    break;

  case 313:

/* Line 1464 of yacc.c  */
#line 1639 "../../../src/util/parser/hphp.y"
    { BEXP((yyval),(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),T_IS_NOT_IDENTICAL);;}
    break;

  case 314:

/* Line 1464 of yacc.c  */
#line 1640 "../../../src/util/parser/hphp.y"
    { BEXP((yyval),(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),T_IS_EQUAL);;}
    break;

  case 315:

/* Line 1464 of yacc.c  */
#line 1641 "../../../src/util/parser/hphp.y"
    { BEXP((yyval),(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),T_IS_NOT_EQUAL);;}
    break;

  case 316:

/* Line 1464 of yacc.c  */
#line 1642 "../../../src/util/parser/hphp.y"
    { BEXP((yyval),(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),'<');;}
    break;

  case 317:

/* Line 1464 of yacc.c  */
#line 1643 "../../../src/util/parser/hphp.y"
    { BEXP((yyval),(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),
                                              T_IS_SMALLER_OR_EQUAL);;}
    break;

  case 318:

/* Line 1464 of yacc.c  */
#line 1645 "../../../src/util/parser/hphp.y"
    { BEXP((yyval),(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),'>');;}
    break;

  case 319:

/* Line 1464 of yacc.c  */
#line 1646 "../../../src/util/parser/hphp.y"
    { BEXP((yyval),(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),
                                              T_IS_GREATER_OR_EQUAL);;}
    break;

  case 320:

/* Line 1464 of yacc.c  */
#line 1649 "../../../src/util/parser/hphp.y"
    { BEXP((yyval),(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),T_INSTANCEOF);;}
    break;

  case 321:

/* Line 1464 of yacc.c  */
#line 1650 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(2) - (3)]);;}
    break;

  case 322:

/* Line 1464 of yacc.c  */
#line 1651 "../../../src/util/parser/hphp.y"
    { _p->onQOp((yyval), (yyvsp[(1) - (5)]), &(yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));;}
    break;

  case 323:

/* Line 1464 of yacc.c  */
#line 1652 "../../../src/util/parser/hphp.y"
    { _p->onQOp((yyval), (yyvsp[(1) - (4)]),   0, (yyvsp[(4) - (4)]));;}
    break;

  case 324:

/* Line 1464 of yacc.c  */
#line 1653 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 325:

/* Line 1464 of yacc.c  */
#line 1654 "../../../src/util/parser/hphp.y"
    { UEXP((yyval),(yyvsp[(2) - (2)]),T_INT_CAST,1);;}
    break;

  case 326:

/* Line 1464 of yacc.c  */
#line 1655 "../../../src/util/parser/hphp.y"
    { UEXP((yyval),(yyvsp[(2) - (2)]),T_DOUBLE_CAST,1);;}
    break;

  case 327:

/* Line 1464 of yacc.c  */
#line 1656 "../../../src/util/parser/hphp.y"
    { UEXP((yyval),(yyvsp[(2) - (2)]),T_STRING_CAST,1);;}
    break;

  case 328:

/* Line 1464 of yacc.c  */
#line 1657 "../../../src/util/parser/hphp.y"
    { UEXP((yyval),(yyvsp[(2) - (2)]),T_ARRAY_CAST,1);;}
    break;

  case 329:

/* Line 1464 of yacc.c  */
#line 1658 "../../../src/util/parser/hphp.y"
    { UEXP((yyval),(yyvsp[(2) - (2)]),T_OBJECT_CAST,1);;}
    break;

  case 330:

/* Line 1464 of yacc.c  */
#line 1659 "../../../src/util/parser/hphp.y"
    { UEXP((yyval),(yyvsp[(2) - (2)]),T_BOOL_CAST,1);;}
    break;

  case 331:

/* Line 1464 of yacc.c  */
#line 1660 "../../../src/util/parser/hphp.y"
    { UEXP((yyval),(yyvsp[(2) - (2)]),T_UNSET_CAST,1);;}
    break;

  case 332:

/* Line 1464 of yacc.c  */
#line 1661 "../../../src/util/parser/hphp.y"
    { UEXP((yyval),(yyvsp[(2) - (2)]),T_EXIT,1);;}
    break;

  case 333:

/* Line 1464 of yacc.c  */
#line 1662 "../../../src/util/parser/hphp.y"
    { UEXP((yyval),(yyvsp[(2) - (2)]),'@',1);;}
    break;

  case 334:

/* Line 1464 of yacc.c  */
#line 1663 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 335:

/* Line 1464 of yacc.c  */
#line 1664 "../../../src/util/parser/hphp.y"
    { _p->onArray((yyval),(yyvsp[(3) - (4)]),T_ARRAY);;}
    break;

  case 336:

/* Line 1464 of yacc.c  */
#line 1665 "../../../src/util/parser/hphp.y"
    { _p->onEncapsList((yyval),'`',(yyvsp[(2) - (3)]));;}
    break;

  case 337:

/* Line 1464 of yacc.c  */
#line 1666 "../../../src/util/parser/hphp.y"
    { UEXP((yyval),(yyvsp[(2) - (2)]),T_PRINT,1);;}
    break;

  case 338:

/* Line 1464 of yacc.c  */
#line 1668 "../../../src/util/parser/hphp.y"
    { Token t; _p->onFunctionStart(t);
                                         _p->pushLabelInfo();;}
    break;

  case 339:

/* Line 1464 of yacc.c  */
#line 1671 "../../../src/util/parser/hphp.y"
    { _p->onClosure((yyval),(yyvsp[(1) - (11)]),(yyvsp[(3) - (11)]),(yyvsp[(6) - (11)]),(yyvsp[(8) - (11)]),(yyvsp[(10) - (11)]));
                                         _p->popLabelInfo();;}
    break;

  case 340:

/* Line 1464 of yacc.c  */
#line 1673 "../../../src/util/parser/hphp.y"
    { _p->onRefDim((yyval), (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));;}
    break;

  case 341:

/* Line 1464 of yacc.c  */
#line 1674 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 342:

/* Line 1464 of yacc.c  */
#line 1678 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(3) - (4)]);;}
    break;

  case 343:

/* Line 1464 of yacc.c  */
#line 1679 "../../../src/util/parser/hphp.y"
    { (yyval).reset();;}
    break;

  case 344:

/* Line 1464 of yacc.c  */
#line 1683 "../../../src/util/parser/hphp.y"
    { _p->onClosureParam((yyval),&(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),0);;}
    break;

  case 345:

/* Line 1464 of yacc.c  */
#line 1684 "../../../src/util/parser/hphp.y"
    { _p->onClosureParam((yyval),&(yyvsp[(1) - (4)]),(yyvsp[(4) - (4)]),1);;}
    break;

  case 346:

/* Line 1464 of yacc.c  */
#line 1685 "../../../src/util/parser/hphp.y"
    { _p->onClosureParam((yyval),  0,(yyvsp[(1) - (1)]),0);;}
    break;

  case 347:

/* Line 1464 of yacc.c  */
#line 1686 "../../../src/util/parser/hphp.y"
    { _p->onClosureParam((yyval),  0,(yyvsp[(2) - (2)]),1);;}
    break;

  case 348:

/* Line 1464 of yacc.c  */
#line 1690 "../../../src/util/parser/hphp.y"
    { no_gap(_p); xhp_tag(_p,(yyval),(yyvsp[(2) - (4)]),(yyvsp[(3) - (4)]));;}
    break;

  case 349:

/* Line 1464 of yacc.c  */
#line 1693 "../../../src/util/parser/hphp.y"
    { Token t1; _p->onArray(t1,(yyvsp[(1) - (1)]));
                                         Token t2; _p->onArray(t2,(yyvsp[(1) - (1)]));
                                         _p->onCallParam((yyvsp[(1) - (1)]),NULL,t1,0);
                                         _p->onCallParam((yyval), &(yyvsp[(1) - (1)]),t2,0);
                                         (yyval).setText("");
                                         _p->scanner().xhpCloseTag();;}
    break;

  case 350:

/* Line 1464 of yacc.c  */
#line 1699 "../../../src/util/parser/hphp.y"
    { _p->scanner().xhpCloseTag();;}
    break;

  case 351:

/* Line 1464 of yacc.c  */
#line 1700 "../../../src/util/parser/hphp.y"
    { Token t1; _p->onArray(t1,(yyvsp[(1) - (4)]));
                                         Token t2; _p->onArray(t2,(yyvsp[(2) - (4)]));
                                         _p->onCallParam((yyvsp[(1) - (4)]),NULL,t1,0);
                                         _p->onCallParam((yyval), &(yyvsp[(1) - (4)]),t2,0);
                                         (yyval).setText((yyvsp[(4) - (4)]));;}
    break;

  case 352:

/* Line 1464 of yacc.c  */
#line 1705 "../../../src/util/parser/hphp.y"
    { _p->scanner().xhpChild();;}
    break;

  case 353:

/* Line 1464 of yacc.c  */
#line 1706 "../../../src/util/parser/hphp.y"
    { _p->scanner().xhpCloseTag();;}
    break;

  case 354:

/* Line 1464 of yacc.c  */
#line 1707 "../../../src/util/parser/hphp.y"
    { _p->onArray((yyvsp[(5) - (8)]),(yyvsp[(1) - (8)]));
                                         _p->onArray((yyvsp[(6) - (8)]),(yyvsp[(4) - (8)]));
                                         _p->onCallParam((yyvsp[(2) - (8)]),NULL,(yyvsp[(5) - (8)]),0);
                                         _p->onCallParam((yyval), &(yyvsp[(2) - (8)]),(yyvsp[(6) - (8)]),0);
                                         (yyval).setText((yyvsp[(8) - (8)]));;}
    break;

  case 355:

/* Line 1464 of yacc.c  */
#line 1714 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 356:

/* Line 1464 of yacc.c  */
#line 1715 "../../../src/util/parser/hphp.y"
    { (yyval).reset();;}
    break;

  case 357:

/* Line 1464 of yacc.c  */
#line 1719 "../../../src/util/parser/hphp.y"
    { _p->scanner().xhpAttribute();;}
    break;

  case 358:

/* Line 1464 of yacc.c  */
#line 1720 "../../../src/util/parser/hphp.y"
    { _p->onArrayPair((yyval),&(yyvsp[(1) - (5)]),&(yyvsp[(2) - (5)]),(yyvsp[(5) - (5)]),0);;}
    break;

  case 359:

/* Line 1464 of yacc.c  */
#line 1721 "../../../src/util/parser/hphp.y"
    { (yyval).reset();;}
    break;

  case 360:

/* Line 1464 of yacc.c  */
#line 1724 "../../../src/util/parser/hphp.y"
    { _p->onArrayPair((yyval),&(yyvsp[(1) - (2)]),0,(yyvsp[(2) - (2)]),0);;}
    break;

  case 361:

/* Line 1464 of yacc.c  */
#line 1725 "../../../src/util/parser/hphp.y"
    { (yyval).reset();;}
    break;

  case 362:

/* Line 1464 of yacc.c  */
#line 1728 "../../../src/util/parser/hphp.y"
    { _p->onScalar((yyval),
                                         T_CONSTANT_ENCAPSED_STRING, (yyvsp[(1) - (1)]));;}
    break;

  case 363:

/* Line 1464 of yacc.c  */
#line 1732 "../../../src/util/parser/hphp.y"
    { (yyvsp[(1) - (1)]).xhpDecode();
                                         _p->onScalar((yyval),
                                         T_CONSTANT_ENCAPSED_STRING, (yyvsp[(1) - (1)]));;}
    break;

  case 364:

/* Line 1464 of yacc.c  */
#line 1735 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(2) - (3)]);;}
    break;

  case 365:

/* Line 1464 of yacc.c  */
#line 1738 "../../../src/util/parser/hphp.y"
    { (yyval).reset();
                                         if ((yyvsp[(1) - (1)]).htmlTrim()) {
                                           (yyvsp[(1) - (1)]).xhpDecode();
                                           _p->onScalar((yyval),
                                           T_CONSTANT_ENCAPSED_STRING, (yyvsp[(1) - (1)]));
                                         }
                                       ;}
    break;

  case 366:

/* Line 1464 of yacc.c  */
#line 1745 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(2) - (3)]); _p->scanner().xhpChild();;}
    break;

  case 367:

/* Line 1464 of yacc.c  */
#line 1746 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]); _p->scanner().xhpChild();;}
    break;

  case 368:

/* Line 1464 of yacc.c  */
#line 1749 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]); no_gap(_p);;}
    break;

  case 369:

/* Line 1464 of yacc.c  */
#line 1750 "../../../src/util/parser/hphp.y"
    { no_gap(_p);;}
    break;

  case 370:

/* Line 1464 of yacc.c  */
#line 1751 "../../../src/util/parser/hphp.y"
    { no_gap(_p); (yyval) = (yyvsp[(1) - (4)]) + ":" + (yyvsp[(4) - (4)]);;}
    break;

  case 371:

/* Line 1464 of yacc.c  */
#line 1752 "../../../src/util/parser/hphp.y"
    { no_gap(_p);;}
    break;

  case 372:

/* Line 1464 of yacc.c  */
#line 1753 "../../../src/util/parser/hphp.y"
    { no_gap(_p); (yyval) = (yyvsp[(1) - (4)]) + "-" + (yyvsp[(4) - (4)]);;}
    break;

  case 373:

/* Line 1464 of yacc.c  */
#line 1756 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 374:

/* Line 1464 of yacc.c  */
#line 1757 "../../../src/util/parser/hphp.y"
    { no_gap(_p);;}
    break;

  case 375:

/* Line 1464 of yacc.c  */
#line 1758 "../../../src/util/parser/hphp.y"
    { no_gap(_p); (yyval) = (yyvsp[(1) - (4)]) + ":" + (yyvsp[(4) - (4)]);;}
    break;

  case 376:

/* Line 1464 of yacc.c  */
#line 1759 "../../../src/util/parser/hphp.y"
    { no_gap(_p);;}
    break;

  case 377:

/* Line 1464 of yacc.c  */
#line 1760 "../../../src/util/parser/hphp.y"
    { no_gap(_p); (yyval) = (yyvsp[(1) - (4)]) + "-" + (yyvsp[(4) - (4)]);;}
    break;

  case 378:

/* Line 1464 of yacc.c  */
#line 1763 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 379:

/* Line 1464 of yacc.c  */
#line 1764 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 380:

/* Line 1464 of yacc.c  */
#line 1765 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 381:

/* Line 1464 of yacc.c  */
#line 1766 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 382:

/* Line 1464 of yacc.c  */
#line 1767 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 383:

/* Line 1464 of yacc.c  */
#line 1768 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 384:

/* Line 1464 of yacc.c  */
#line 1769 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 385:

/* Line 1464 of yacc.c  */
#line 1770 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 386:

/* Line 1464 of yacc.c  */
#line 1771 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 387:

/* Line 1464 of yacc.c  */
#line 1772 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 388:

/* Line 1464 of yacc.c  */
#line 1773 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 389:

/* Line 1464 of yacc.c  */
#line 1774 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 390:

/* Line 1464 of yacc.c  */
#line 1775 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 391:

/* Line 1464 of yacc.c  */
#line 1776 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 392:

/* Line 1464 of yacc.c  */
#line 1777 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 393:

/* Line 1464 of yacc.c  */
#line 1778 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 394:

/* Line 1464 of yacc.c  */
#line 1779 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 395:

/* Line 1464 of yacc.c  */
#line 1780 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 396:

/* Line 1464 of yacc.c  */
#line 1781 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 397:

/* Line 1464 of yacc.c  */
#line 1782 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 398:

/* Line 1464 of yacc.c  */
#line 1783 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 399:

/* Line 1464 of yacc.c  */
#line 1784 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 400:

/* Line 1464 of yacc.c  */
#line 1785 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 401:

/* Line 1464 of yacc.c  */
#line 1786 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 402:

/* Line 1464 of yacc.c  */
#line 1787 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 403:

/* Line 1464 of yacc.c  */
#line 1788 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 404:

/* Line 1464 of yacc.c  */
#line 1789 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 405:

/* Line 1464 of yacc.c  */
#line 1790 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 406:

/* Line 1464 of yacc.c  */
#line 1791 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 407:

/* Line 1464 of yacc.c  */
#line 1792 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 408:

/* Line 1464 of yacc.c  */
#line 1793 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 409:

/* Line 1464 of yacc.c  */
#line 1794 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 410:

/* Line 1464 of yacc.c  */
#line 1795 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 411:

/* Line 1464 of yacc.c  */
#line 1796 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 412:

/* Line 1464 of yacc.c  */
#line 1797 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 413:

/* Line 1464 of yacc.c  */
#line 1798 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 414:

/* Line 1464 of yacc.c  */
#line 1799 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 415:

/* Line 1464 of yacc.c  */
#line 1800 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 416:

/* Line 1464 of yacc.c  */
#line 1801 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 417:

/* Line 1464 of yacc.c  */
#line 1802 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 418:

/* Line 1464 of yacc.c  */
#line 1803 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 419:

/* Line 1464 of yacc.c  */
#line 1804 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 420:

/* Line 1464 of yacc.c  */
#line 1805 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 421:

/* Line 1464 of yacc.c  */
#line 1806 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 422:

/* Line 1464 of yacc.c  */
#line 1807 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 423:

/* Line 1464 of yacc.c  */
#line 1808 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 424:

/* Line 1464 of yacc.c  */
#line 1809 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 425:

/* Line 1464 of yacc.c  */
#line 1810 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 426:

/* Line 1464 of yacc.c  */
#line 1811 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 427:

/* Line 1464 of yacc.c  */
#line 1812 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 428:

/* Line 1464 of yacc.c  */
#line 1813 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 429:

/* Line 1464 of yacc.c  */
#line 1814 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 430:

/* Line 1464 of yacc.c  */
#line 1815 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 431:

/* Line 1464 of yacc.c  */
#line 1816 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 432:

/* Line 1464 of yacc.c  */
#line 1817 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 433:

/* Line 1464 of yacc.c  */
#line 1818 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 434:

/* Line 1464 of yacc.c  */
#line 1819 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 435:

/* Line 1464 of yacc.c  */
#line 1820 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 436:

/* Line 1464 of yacc.c  */
#line 1821 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 437:

/* Line 1464 of yacc.c  */
#line 1822 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 438:

/* Line 1464 of yacc.c  */
#line 1823 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 439:

/* Line 1464 of yacc.c  */
#line 1824 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 440:

/* Line 1464 of yacc.c  */
#line 1825 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 441:

/* Line 1464 of yacc.c  */
#line 1826 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 442:

/* Line 1464 of yacc.c  */
#line 1827 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 443:

/* Line 1464 of yacc.c  */
#line 1828 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 444:

/* Line 1464 of yacc.c  */
#line 1829 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 445:

/* Line 1464 of yacc.c  */
#line 1830 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 446:

/* Line 1464 of yacc.c  */
#line 1831 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 447:

/* Line 1464 of yacc.c  */
#line 1832 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 448:

/* Line 1464 of yacc.c  */
#line 1833 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 449:

/* Line 1464 of yacc.c  */
#line 1834 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 450:

/* Line 1464 of yacc.c  */
#line 1839 "../../../src/util/parser/hphp.y"
    { _p->onCall((yyval),0,(yyvsp[(1) - (4)]),(yyvsp[(3) - (4)]),NULL);;}
    break;

  case 451:

/* Line 1464 of yacc.c  */
#line 1841 "../../../src/util/parser/hphp.y"
    { _p->onCall((yyval),1,(yyvsp[(1) - (4)]),(yyvsp[(3) - (4)]),NULL);;}
    break;

  case 452:

/* Line 1464 of yacc.c  */
#line 1845 "../../../src/util/parser/hphp.y"
    { _p->onCall((yyval),0,(yyvsp[(3) - (6)]),(yyvsp[(5) - (6)]),&(yyvsp[(1) - (6)]));;}
    break;

  case 453:

/* Line 1464 of yacc.c  */
#line 1849 "../../../src/util/parser/hphp.y"
    { _p->onCall((yyval),1,(yyvsp[(3) - (6)]),(yyvsp[(5) - (6)]),&(yyvsp[(1) - (6)]));;}
    break;

  case 454:

/* Line 1464 of yacc.c  */
#line 1852 "../../../src/util/parser/hphp.y"
    { _p->onName((yyval),(yyvsp[(1) - (1)]),Parser::StringName);;}
    break;

  case 455:

/* Line 1464 of yacc.c  */
#line 1853 "../../../src/util/parser/hphp.y"
    { _p->onName((yyval),(yyvsp[(1) - (1)]),Parser::StaticName);;}
    break;

  case 456:

/* Line 1464 of yacc.c  */
#line 1854 "../../../src/util/parser/hphp.y"
    { _p->onName((yyval),(yyvsp[(1) - (1)]),
                                         Parser::StaticClassExprName);;}
    break;

  case 457:

/* Line 1464 of yacc.c  */
#line 1858 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 458:

/* Line 1464 of yacc.c  */
#line 1859 "../../../src/util/parser/hphp.y"
    { (yyvsp[(1) - (1)]).xhpLabel(); (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 459:

/* Line 1464 of yacc.c  */
#line 1862 "../../../src/util/parser/hphp.y"
    { _p->onName((yyval),(yyvsp[(1) - (1)]),Parser::StringName);;}
    break;

  case 460:

/* Line 1464 of yacc.c  */
#line 1863 "../../../src/util/parser/hphp.y"
    { (yyvsp[(1) - (1)]).xhpLabel();
                                         _p->onName((yyval),(yyvsp[(1) - (1)]),Parser::StringName);;}
    break;

  case 461:

/* Line 1464 of yacc.c  */
#line 1865 "../../../src/util/parser/hphp.y"
    { _p->onName((yyval),(yyvsp[(1) - (1)]),Parser::ExprName);;}
    break;

  case 462:

/* Line 1464 of yacc.c  */
#line 1866 "../../../src/util/parser/hphp.y"
    { _p->onName((yyval),(yyvsp[(1) - (1)]),Parser::StaticName);;}
    break;

  case 463:

/* Line 1464 of yacc.c  */
#line 1869 "../../../src/util/parser/hphp.y"
    { _p->pushObject((yyvsp[(1) - (1)]));;}
    break;

  case 464:

/* Line 1464 of yacc.c  */
#line 1871 "../../../src/util/parser/hphp.y"
    { _p->popObject((yyval));;}
    break;

  case 465:

/* Line 1464 of yacc.c  */
#line 1872 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 466:

/* Line 1464 of yacc.c  */
#line 1876 "../../../src/util/parser/hphp.y"
    { ;}
    break;

  case 467:

/* Line 1464 of yacc.c  */
#line 1877 "../../../src/util/parser/hphp.y"
    { ;}
    break;

  case 468:

/* Line 1464 of yacc.c  */
#line 1880 "../../../src/util/parser/hphp.y"
    { ;}
    break;

  case 469:

/* Line 1464 of yacc.c  */
#line 1884 "../../../src/util/parser/hphp.y"
    { (yyval).reset();;}
    break;

  case 470:

/* Line 1464 of yacc.c  */
#line 1885 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(2) - (3)]);;}
    break;

  case 471:

/* Line 1464 of yacc.c  */
#line 1886 "../../../src/util/parser/hphp.y"
    { (yyval).reset();;}
    break;

  case 472:

/* Line 1464 of yacc.c  */
#line 1890 "../../../src/util/parser/hphp.y"
    { (yyval).reset();;}
    break;

  case 473:

/* Line 1464 of yacc.c  */
#line 1891 "../../../src/util/parser/hphp.y"
    { _p->addEncap((yyval), NULL, (yyvsp[(1) - (1)]), 0);;}
    break;

  case 474:

/* Line 1464 of yacc.c  */
#line 1892 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 475:

/* Line 1464 of yacc.c  */
#line 1896 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(2) - (3)]);;}
    break;

  case 476:

/* Line 1464 of yacc.c  */
#line 1897 "../../../src/util/parser/hphp.y"
    { (yyval).reset();;}
    break;

  case 477:

/* Line 1464 of yacc.c  */
#line 1901 "../../../src/util/parser/hphp.y"
    { _p->onScalar((yyval), T_LNUMBER,  (yyvsp[(1) - (1)]));;}
    break;

  case 478:

/* Line 1464 of yacc.c  */
#line 1902 "../../../src/util/parser/hphp.y"
    { _p->onScalar((yyval), T_DNUMBER,  (yyvsp[(1) - (1)]));;}
    break;

  case 479:

/* Line 1464 of yacc.c  */
#line 1903 "../../../src/util/parser/hphp.y"
    { _p->onScalar((yyval),
                                         T_CONSTANT_ENCAPSED_STRING,  (yyvsp[(1) - (1)]));;}
    break;

  case 480:

/* Line 1464 of yacc.c  */
#line 1905 "../../../src/util/parser/hphp.y"
    { _p->onScalar((yyval), T_LINE,     (yyvsp[(1) - (1)]));;}
    break;

  case 481:

/* Line 1464 of yacc.c  */
#line 1906 "../../../src/util/parser/hphp.y"
    { _p->onScalar((yyval), T_FILE,     (yyvsp[(1) - (1)]));;}
    break;

  case 482:

/* Line 1464 of yacc.c  */
#line 1907 "../../../src/util/parser/hphp.y"
    { _p->onScalar((yyval), T_DIR,      (yyvsp[(1) - (1)]));;}
    break;

  case 483:

/* Line 1464 of yacc.c  */
#line 1908 "../../../src/util/parser/hphp.y"
    { _p->onScalar((yyval), T_CLASS_C,  (yyvsp[(1) - (1)]));;}
    break;

  case 484:

/* Line 1464 of yacc.c  */
#line 1909 "../../../src/util/parser/hphp.y"
    { _p->onScalar((yyval), T_TRAIT_C,  (yyvsp[(1) - (1)]));;}
    break;

  case 485:

/* Line 1464 of yacc.c  */
#line 1910 "../../../src/util/parser/hphp.y"
    { _p->onScalar((yyval), T_METHOD_C, (yyvsp[(1) - (1)]));;}
    break;

  case 486:

/* Line 1464 of yacc.c  */
#line 1911 "../../../src/util/parser/hphp.y"
    { _p->onScalar((yyval), T_FUNC_C,   (yyvsp[(1) - (1)]));;}
    break;

  case 487:

/* Line 1464 of yacc.c  */
#line 1912 "../../../src/util/parser/hphp.y"
    { _p->onScalar((yyval), T_NS_C,  (yyvsp[(1) - (1)]));;}
    break;

  case 488:

/* Line 1464 of yacc.c  */
#line 1915 "../../../src/util/parser/hphp.y"
    { _p->onScalar((yyval), T_CONSTANT_ENCAPSED_STRING, (yyvsp[(2) - (3)]));;}
    break;

  case 489:

/* Line 1464 of yacc.c  */
#line 1917 "../../../src/util/parser/hphp.y"
    { (yyval).setText(""); _p->onScalar((yyval), T_CONSTANT_ENCAPSED_STRING, (yyval));;}
    break;

  case 490:

/* Line 1464 of yacc.c  */
#line 1921 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 491:

/* Line 1464 of yacc.c  */
#line 1922 "../../../src/util/parser/hphp.y"
    { _p->onConstantValue((yyval), (yyvsp[(1) - (1)]));;}
    break;

  case 492:

/* Line 1464 of yacc.c  */
#line 1923 "../../../src/util/parser/hphp.y"
    { UEXP((yyval),(yyvsp[(2) - (2)]),'+',1);;}
    break;

  case 493:

/* Line 1464 of yacc.c  */
#line 1924 "../../../src/util/parser/hphp.y"
    { UEXP((yyval),(yyvsp[(2) - (2)]),'-',1);;}
    break;

  case 494:

/* Line 1464 of yacc.c  */
#line 1926 "../../../src/util/parser/hphp.y"
    { _p->onArray((yyval),(yyvsp[(3) - (4)]),T_ARRAY);;}
    break;

  case 495:

/* Line 1464 of yacc.c  */
#line 1927 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 496:

/* Line 1464 of yacc.c  */
#line 1932 "../../../src/util/parser/hphp.y"
    { _p->onClassConst((yyval), (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), 1);;}
    break;

  case 497:

/* Line 1464 of yacc.c  */
#line 1934 "../../../src/util/parser/hphp.y"
    { (yyvsp[(1) - (3)]).xhpLabel();
                                         _p->onClassConst((yyval), (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), 1);;}
    break;

  case 498:

/* Line 1464 of yacc.c  */
#line 1938 "../../../src/util/parser/hphp.y"
    { _p->onConstantValue((yyval), (yyvsp[(1) - (1)]));;}
    break;

  case 499:

/* Line 1464 of yacc.c  */
#line 1939 "../../../src/util/parser/hphp.y"
    { _p->onConstantValue((yyval), (yyvsp[(1) - (1)]));;}
    break;

  case 500:

/* Line 1464 of yacc.c  */
#line 1940 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 501:

/* Line 1464 of yacc.c  */
#line 1941 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 502:

/* Line 1464 of yacc.c  */
#line 1942 "../../../src/util/parser/hphp.y"
    { _p->onEncapsList((yyval),'"',(yyvsp[(2) - (3)]));;}
    break;

  case 503:

/* Line 1464 of yacc.c  */
#line 1943 "../../../src/util/parser/hphp.y"
    { _p->onEncapsList((yyval),'\'',(yyvsp[(2) - (3)]));;}
    break;

  case 504:

/* Line 1464 of yacc.c  */
#line 1945 "../../../src/util/parser/hphp.y"
    { _p->onEncapsList((yyval),T_START_HEREDOC,
                                                          (yyvsp[(2) - (3)]));;}
    break;

  case 505:

/* Line 1464 of yacc.c  */
#line 1950 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (2)]);;}
    break;

  case 506:

/* Line 1464 of yacc.c  */
#line 1951 "../../../src/util/parser/hphp.y"
    { (yyval).reset();;}
    break;

  case 507:

/* Line 1464 of yacc.c  */
#line 1954 "../../../src/util/parser/hphp.y"
    { (yyval).reset();;}
    break;

  case 508:

/* Line 1464 of yacc.c  */
#line 1955 "../../../src/util/parser/hphp.y"
    { (yyval).reset();;}
    break;

  case 509:

/* Line 1464 of yacc.c  */
#line 1960 "../../../src/util/parser/hphp.y"
    { _p->onArrayPair((yyval),&(yyvsp[(1) - (5)]),&(yyvsp[(3) - (5)]),(yyvsp[(5) - (5)]),0);;}
    break;

  case 510:

/* Line 1464 of yacc.c  */
#line 1962 "../../../src/util/parser/hphp.y"
    { _p->onArrayPair((yyval),&(yyvsp[(1) - (3)]),  0,(yyvsp[(3) - (3)]),0);;}
    break;

  case 511:

/* Line 1464 of yacc.c  */
#line 1964 "../../../src/util/parser/hphp.y"
    { _p->onArrayPair((yyval),  0,&(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),0);;}
    break;

  case 512:

/* Line 1464 of yacc.c  */
#line 1965 "../../../src/util/parser/hphp.y"
    { _p->onArrayPair((yyval),  0,  0,(yyvsp[(1) - (1)]),0);;}
    break;

  case 513:

/* Line 1464 of yacc.c  */
#line 1969 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 514:

/* Line 1464 of yacc.c  */
#line 1970 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 515:

/* Line 1464 of yacc.c  */
#line 1973 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 516:

/* Line 1464 of yacc.c  */
#line 1976 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 517:

/* Line 1464 of yacc.c  */
#line 1979 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 518:

/* Line 1464 of yacc.c  */
#line 1982 "../../../src/util/parser/hphp.y"
    { _p->pushObject((yyvsp[(1) - (1)]));;}
    break;

  case 519:

/* Line 1464 of yacc.c  */
#line 1984 "../../../src/util/parser/hphp.y"
    { _p->appendMethodParams((yyvsp[(5) - (5)]));;}
    break;

  case 520:

/* Line 1464 of yacc.c  */
#line 1985 "../../../src/util/parser/hphp.y"
    { _p->popObject((yyval));;}
    break;

  case 521:

/* Line 1464 of yacc.c  */
#line 1986 "../../../src/util/parser/hphp.y"
    { _p->pushObject((yyvsp[(1) - (1)]));
                                         _p->popObject((yyval));;}
    break;

  case 522:

/* Line 1464 of yacc.c  */
#line 1991 "../../../src/util/parser/hphp.y"
    { ;}
    break;

  case 523:

/* Line 1464 of yacc.c  */
#line 1992 "../../../src/util/parser/hphp.y"
    { ;}
    break;

  case 524:

/* Line 1464 of yacc.c  */
#line 1996 "../../../src/util/parser/hphp.y"
    { _p->appendMethodParams((yyvsp[(3) - (3)]));;}
    break;

  case 525:

/* Line 1464 of yacc.c  */
#line 2000 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(2) - (3)]); (yyval) = 1;;}
    break;

  case 526:

/* Line 1464 of yacc.c  */
#line 2001 "../../../src/util/parser/hphp.y"
    { (yyval).reset();;}
    break;

  case 527:

/* Line 1464 of yacc.c  */
#line 2005 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 528:

/* Line 1464 of yacc.c  */
#line 2007 "../../../src/util/parser/hphp.y"
    { _p->onIndirectRef((yyval),(yyvsp[(1) - (2)]),(yyvsp[(2) - (2)]));;}
    break;

  case 529:

/* Line 1464 of yacc.c  */
#line 2012 "../../../src/util/parser/hphp.y"
    { _p->onStaticMember((yyval),(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]));;}
    break;

  case 530:

/* Line 1464 of yacc.c  */
#line 2016 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 531:

/* Line 1464 of yacc.c  */
#line 2017 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 532:

/* Line 1464 of yacc.c  */
#line 2020 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 533:

/* Line 1464 of yacc.c  */
#line 2022 "../../../src/util/parser/hphp.y"
    { _p->onIndirectRef((yyval),(yyvsp[(1) - (2)]),(yyvsp[(2) - (2)]));;}
    break;

  case 534:

/* Line 1464 of yacc.c  */
#line 2023 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]); (yyval) = 2;;}
    break;

  case 535:

/* Line 1464 of yacc.c  */
#line 2027 "../../../src/util/parser/hphp.y"
    { _p->onRefDim((yyval), (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));;}
    break;

  case 536:

/* Line 1464 of yacc.c  */
#line 2028 "../../../src/util/parser/hphp.y"
    { _p->onRefDim((yyval), (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));;}
    break;

  case 537:

/* Line 1464 of yacc.c  */
#line 2029 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 538:

/* Line 1464 of yacc.c  */
#line 2032 "../../../src/util/parser/hphp.y"
    { _p->onSimpleVariable((yyval), (yyvsp[(1) - (1)]));;}
    break;

  case 539:

/* Line 1464 of yacc.c  */
#line 2033 "../../../src/util/parser/hphp.y"
    { _p->onDynamicVariable((yyval), (yyvsp[(3) - (4)]), 0);;}
    break;

  case 540:

/* Line 1464 of yacc.c  */
#line 2036 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 541:

/* Line 1464 of yacc.c  */
#line 2037 "../../../src/util/parser/hphp.y"
    { (yyval).reset();;}
    break;

  case 542:

/* Line 1464 of yacc.c  */
#line 2041 "../../../src/util/parser/hphp.y"
    { ;}
    break;

  case 543:

/* Line 1464 of yacc.c  */
#line 2042 "../../../src/util/parser/hphp.y"
    { _p->appendProperty((yyvsp[(1) - (1)]));;}
    break;

  case 544:

/* Line 1464 of yacc.c  */
#line 2045 "../../../src/util/parser/hphp.y"
    { _p->appendRefDim((yyvsp[(3) - (4)]));;}
    break;

  case 545:

/* Line 1464 of yacc.c  */
#line 2046 "../../../src/util/parser/hphp.y"
    { _p->appendRefDim((yyvsp[(3) - (4)]));;}
    break;

  case 546:

/* Line 1464 of yacc.c  */
#line 2047 "../../../src/util/parser/hphp.y"
    { _p->appendProperty((yyvsp[(1) - (1)]));;}
    break;

  case 547:

/* Line 1464 of yacc.c  */
#line 2050 "../../../src/util/parser/hphp.y"
    {_p->onName((yyval),(yyvsp[(1) - (1)]),Parser::VarName);;}
    break;

  case 548:

/* Line 1464 of yacc.c  */
#line 2051 "../../../src/util/parser/hphp.y"
    {_p->onName((yyval),(yyvsp[(2) - (3)]),Parser::ExprName);;}
    break;

  case 549:

/* Line 1464 of yacc.c  */
#line 2055 "../../../src/util/parser/hphp.y"
    { (yyval) = 1;;}
    break;

  case 550:

/* Line 1464 of yacc.c  */
#line 2056 "../../../src/util/parser/hphp.y"
    { (yyval)++;;}
    break;

  case 551:

/* Line 1464 of yacc.c  */
#line 2060 "../../../src/util/parser/hphp.y"
    { _p->onAListVar((yyval),&(yyvsp[(1) - (2)]),NULL);;}
    break;

  case 552:

/* Line 1464 of yacc.c  */
#line 2061 "../../../src/util/parser/hphp.y"
    { _p->onAListVar((yyval),&(yyvsp[(1) - (3)]),&(yyvsp[(3) - (3)]));;}
    break;

  case 553:

/* Line 1464 of yacc.c  */
#line 2063 "../../../src/util/parser/hphp.y"
    { _p->onAListSub((yyval),&(yyvsp[(1) - (6)]),(yyvsp[(5) - (6)]));;}
    break;

  case 554:

/* Line 1464 of yacc.c  */
#line 2064 "../../../src/util/parser/hphp.y"
    { _p->onAListVar((yyval),NULL,NULL);;}
    break;

  case 555:

/* Line 1464 of yacc.c  */
#line 2065 "../../../src/util/parser/hphp.y"
    { _p->onAListVar((yyval),NULL,&(yyvsp[(1) - (1)]));;}
    break;

  case 556:

/* Line 1464 of yacc.c  */
#line 2066 "../../../src/util/parser/hphp.y"
    { _p->onAListSub((yyval),NULL,(yyvsp[(3) - (4)]));;}
    break;

  case 557:

/* Line 1464 of yacc.c  */
#line 2071 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (2)]);;}
    break;

  case 558:

/* Line 1464 of yacc.c  */
#line 2072 "../../../src/util/parser/hphp.y"
    { (yyval).reset();;}
    break;

  case 559:

/* Line 1464 of yacc.c  */
#line 2076 "../../../src/util/parser/hphp.y"
    { _p->onArrayPair((yyval),&(yyvsp[(1) - (5)]),&(yyvsp[(3) - (5)]),(yyvsp[(5) - (5)]),0);;}
    break;

  case 560:

/* Line 1464 of yacc.c  */
#line 2077 "../../../src/util/parser/hphp.y"
    { _p->onArrayPair((yyval),&(yyvsp[(1) - (3)]),  0,(yyvsp[(3) - (3)]),0);;}
    break;

  case 561:

/* Line 1464 of yacc.c  */
#line 2078 "../../../src/util/parser/hphp.y"
    { _p->onArrayPair((yyval),  0,&(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),0);;}
    break;

  case 562:

/* Line 1464 of yacc.c  */
#line 2079 "../../../src/util/parser/hphp.y"
    { _p->onArrayPair((yyval),  0,  0,(yyvsp[(1) - (1)]),0);;}
    break;

  case 563:

/* Line 1464 of yacc.c  */
#line 2082 "../../../src/util/parser/hphp.y"
    { _p->onArrayPair((yyval),&(yyvsp[(1) - (6)]),&(yyvsp[(3) - (6)]),(yyvsp[(6) - (6)]),1);;}
    break;

  case 564:

/* Line 1464 of yacc.c  */
#line 2084 "../../../src/util/parser/hphp.y"
    { _p->onArrayPair((yyval),&(yyvsp[(1) - (4)]),  0,(yyvsp[(4) - (4)]),1);;}
    break;

  case 565:

/* Line 1464 of yacc.c  */
#line 2085 "../../../src/util/parser/hphp.y"
    { _p->onArrayPair((yyval),  0,&(yyvsp[(1) - (4)]),(yyvsp[(4) - (4)]),1);;}
    break;

  case 566:

/* Line 1464 of yacc.c  */
#line 2086 "../../../src/util/parser/hphp.y"
    { _p->onArrayPair((yyval),  0,  0,(yyvsp[(2) - (2)]),1);;}
    break;

  case 567:

/* Line 1464 of yacc.c  */
#line 2090 "../../../src/util/parser/hphp.y"
    { _p->addEncap((yyval), &(yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]), -1);;}
    break;

  case 568:

/* Line 1464 of yacc.c  */
#line 2092 "../../../src/util/parser/hphp.y"
    { _p->addEncap((yyval), &(yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]), 0);;}
    break;

  case 569:

/* Line 1464 of yacc.c  */
#line 2093 "../../../src/util/parser/hphp.y"
    { _p->addEncap((yyval), NULL, (yyvsp[(1) - (1)]), -1);;}
    break;

  case 570:

/* Line 1464 of yacc.c  */
#line 2095 "../../../src/util/parser/hphp.y"
    { _p->addEncap((yyval), NULL, (yyvsp[(1) - (2)]), 0);
                                         _p->addEncap((yyval), &(yyval), (yyvsp[(2) - (2)]), -1); ;}
    break;

  case 571:

/* Line 1464 of yacc.c  */
#line 2100 "../../../src/util/parser/hphp.y"
    { _p->onSimpleVariable((yyval), (yyvsp[(1) - (1)]));;}
    break;

  case 572:

/* Line 1464 of yacc.c  */
#line 2102 "../../../src/util/parser/hphp.y"
    { _p->encapRefDim((yyval), (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));;}
    break;

  case 573:

/* Line 1464 of yacc.c  */
#line 2104 "../../../src/util/parser/hphp.y"
    { _p->encapObjProp((yyval), (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));;}
    break;

  case 574:

/* Line 1464 of yacc.c  */
#line 2106 "../../../src/util/parser/hphp.y"
    { _p->onDynamicVariable((yyval), (yyvsp[(2) - (3)]), 1);;}
    break;

  case 575:

/* Line 1464 of yacc.c  */
#line 2108 "../../../src/util/parser/hphp.y"
    { _p->encapArray((yyval), (yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]));;}
    break;

  case 576:

/* Line 1464 of yacc.c  */
#line 2109 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(2) - (3)]);;}
    break;

  case 577:

/* Line 1464 of yacc.c  */
#line 2112 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]); (yyval) = T_STRING;;}
    break;

  case 578:

/* Line 1464 of yacc.c  */
#line 2113 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]); (yyval) = T_NUM_STRING;;}
    break;

  case 579:

/* Line 1464 of yacc.c  */
#line 2114 "../../../src/util/parser/hphp.y"
    { (yyval) = (yyvsp[(1) - (1)]); (yyval) = T_VARIABLE;;}
    break;

  case 580:

/* Line 1464 of yacc.c  */
#line 2118 "../../../src/util/parser/hphp.y"
    { UEXP((yyval),(yyvsp[(3) - (4)]),T_ISSET,1);;}
    break;

  case 581:

/* Line 1464 of yacc.c  */
#line 2119 "../../../src/util/parser/hphp.y"
    { UEXP((yyval),(yyvsp[(3) - (4)]),T_EMPTY,1);;}
    break;

  case 582:

/* Line 1464 of yacc.c  */
#line 2120 "../../../src/util/parser/hphp.y"
    { UEXP((yyval),(yyvsp[(2) - (2)]),T_INCLUDE,1);;}
    break;

  case 583:

/* Line 1464 of yacc.c  */
#line 2121 "../../../src/util/parser/hphp.y"
    { UEXP((yyval),(yyvsp[(2) - (2)]),T_INCLUDE_ONCE,1);;}
    break;

  case 584:

/* Line 1464 of yacc.c  */
#line 2122 "../../../src/util/parser/hphp.y"
    { UEXP((yyval),(yyvsp[(3) - (4)]),T_EVAL,1);;}
    break;

  case 585:

/* Line 1464 of yacc.c  */
#line 2123 "../../../src/util/parser/hphp.y"
    { UEXP((yyval),(yyvsp[(2) - (2)]),T_REQUIRE,1);;}
    break;

  case 586:

/* Line 1464 of yacc.c  */
#line 2124 "../../../src/util/parser/hphp.y"
    { UEXP((yyval),(yyvsp[(2) - (2)]),T_REQUIRE_ONCE,1);;}
    break;

  case 587:

/* Line 1464 of yacc.c  */
#line 2128 "../../../src/util/parser/hphp.y"
    { _p->onExprListElem((yyval), NULL, (yyvsp[(1) - (1)]));;}
    break;

  case 588:

/* Line 1464 of yacc.c  */
#line 2129 "../../../src/util/parser/hphp.y"
    { _p->onExprListElem((yyval), &(yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));;}
    break;

  case 589:

/* Line 1464 of yacc.c  */
#line 2134 "../../../src/util/parser/hphp.y"
    { _p->onClassConst((yyval), (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), 0);;}
    break;



/* Line 1464 of yacc.c  */
#line 9068 "hphp.tab.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (&yylloc, _p, YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (&yylloc, _p, yymsg);
	  }
	else
	  {
	    yyerror (&yylloc, _p, YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, &yylloc, _p);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp, _p);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, _p, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc, _p);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp, _p);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
  YYSTACK_CLEANUP;
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1684 of yacc.c  */
#line 2136 "../../../src/util/parser/hphp.y"

bool Parser::parse() {
  return yyparse(this) == 0;
}

