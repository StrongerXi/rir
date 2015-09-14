#ifndef RBC_H
#define RBC_H

#define RBC \
    INSTRUCTION0(BCMISMATCH_OP, 0) \
    SPECIAL0(RETURN_OP, 1) \
    SPECIAL1(GOTO_OP, 2) \
    SPECIAL2(BRIFNOT_OP, 3) \
    INSTRUCTION0(POP_OP, 4) \
    INSTRUCTION0(DUP_OP, 5) \
    INSTRUCTION0(PRINTVALUE_OP, 6) \
    INSTRUCTION1(STARTLOOPCNTXT_OP, 7) \
    INSTRUCTION0(ENDLOOPCNTXT_OP, 8) \
    INSTRUCTION0(DOLOOPNEXT_OP, 9) \
    INSTRUCTION0(DOLOOPBREAK_OP, 10) \
    SPECIAL3(STARTFOR_OP, 11) \
    SPECIAL2(STEPFOR_OP, 12) \
    INSTRUCTION0(ENDFOR_OP, 13) \
    INSTRUCTION0(SETLOOPVAL_OP, 14) \
    INSTRUCTION0(INVISIBLE_OP, 15) \
    INSTRUCTION1(LDCONST_OP, 16) \
    INSTRUCTION0(LDNULL_OP, 17) \
    INSTRUCTION0(LDTRUE_OP, 18) \
    INSTRUCTION0(LDFALSE_OP, 19) \
    INSTRUCTION1(GETVAR_OP, 20) \
    INSTRUCTION1(DDVAL_OP, 21) \
    INSTRUCTION1(SETVAR_OP, 22) \
    INSTRUCTION1(GETFUN_OP, 23) \
    INSTRUCTION1(GETGLOBFUN_OP, 24) \
    INSTRUCTION1(GETSYMFUN_OP, 25) \
    INSTRUCTION1(GETBUILTIN_OP, 26) \
    INSTRUCTION1(GETINTLBUILTIN_OP, 27) \
    INSTRUCTION0(CHECKFUN_OP, 28) \
    INSTRUCTION1(MAKEPROM_OP, 29) \
    INSTRUCTION0(DOMISSING_OP, 30) \
    INSTRUCTION1(SETTAG_OP, 31) \
    INSTRUCTION0(DODOTS_OP, 32) \
    INSTRUCTION0(PUSHARG_OP, 33) \
    INSTRUCTION1(PUSHCONSTARG_OP, 34) \
    INSTRUCTION0(PUSHNULLARG_OP, 35) \
    INSTRUCTION0(PUSHTRUEARG_OP, 36) \
    INSTRUCTION0(PUSHFALSEARG_OP, 37) \
    INSTRUCTION1(CALL_OP, 38) \
    INSTRUCTION1(CALLBUILTIN_OP, 39) \
    INSTRUCTION1(CALLSPECIAL_OP, 40) \
    INSTRUCTION1(MAKECLOSURE_OP, 41) \
    INSTRUCTION1(UMINUS_OP, 42) \
    INSTRUCTION1(UPLUS_OP, 43) \
    INSTRUCTION1(ADD_OP, 44) \
    INSTRUCTION1(SUB_OP, 45) \
    INSTRUCTION1(MUL_OP, 46) \
    INSTRUCTION1(DIV_OP, 47) \
    INSTRUCTION1(EXPT_OP, 48) \
    INSTRUCTION1(SQRT_OP, 49) \
    INSTRUCTION1(EXP_OP, 50) \
    INSTRUCTION1(EQ_OP, 51) \
    INSTRUCTION1(NE_OP, 52) \
    INSTRUCTION1(LT_OP, 53) \
    INSTRUCTION1(LE_OP, 54) \
    INSTRUCTION1(GE_OP, 55) \
    INSTRUCTION1(GT_OP, 56) \
    INSTRUCTION1(AND_OP, 57) \
    INSTRUCTION1(OR_OP, 58) \
    INSTRUCTION1(NOT_OP, 59) \
    INSTRUCTION0(DOTSERR_OP, 60) \
    INSTRUCTION1(STARTASSIGN_OP, 61) \
    INSTRUCTION1(ENDASSIGN_OP, 62) \
    SPECIAL2(STARTSUBSET_OP, 63) \
    INSTRUCTION0(DFLTSUBSET_OP, 64) \
    SPECIAL2(STARTSUBASSIGN_OP, 65) \
    INSTRUCTION0(DFLTSUBASSIGN_OP, 66) \
    SPECIAL2(STARTC_OP, 67) \
    INSTRUCTION0(DFLTC_OP, 68) \
    SPECIAL2(STARTSUBSET2_OP, 69) \
    INSTRUCTION0(DFLTSUBSET2_OP, 70) \
    SPECIAL2(STARTSUBASSIGN2_OP, 71) \
    INSTRUCTION0(DFLTSUBASSIGN2_OP, 72) \
    INSTRUCTION2(DOLLAR_OP, 73) \
    INSTRUCTION2(DOLLARGETS_OP, 74) \
    INSTRUCTION0(ISNULL_OP, 75) \
    INSTRUCTION0(ISLOGICAL_OP, 76) \
    INSTRUCTION0(ISINTEGER_OP, 77) \
    INSTRUCTION0(ISDOUBLE_OP, 78) \
    INSTRUCTION0(ISCOMPLEX_OP, 79) \
    INSTRUCTION0(ISCHARACTER_OP, 80) \
    INSTRUCTION0(ISSYMBOL_OP, 81) \
    INSTRUCTION0(ISOBJECT_OP, 82) \
    INSTRUCTION0(ISNUMERIC_OP, 83) \
    INSTRUCTION1(VECSUBSET_OP, 84) \
    INSTRUCTION1(MATSUBSET_OP, 85) \
    INSTRUCTION1(VECSUBASSIGN_OP, 86) \
    INSTRUCTION1(MATSUBASSIGN_OP, 87) \
    SPECIAL2(AND1ST_OP, 88) \
    INSTRUCTION1(AND2ND_OP, 89) \
    SPECIAL2(OR1ST_OP, 90) \
    INSTRUCTION1(OR2ND_OP, 91) \
    INSTRUCTION1(GETVAR_MISSOK_OP, 92) \
    INSTRUCTION1(DDVAL_MISSOK_OP, 93) \
    INSTRUCTION0(VISIBLE_OP, 94) \
    INSTRUCTION1(SETVAR2_OP, 95) \
    INSTRUCTION1(STARTASSIGN2_OP, 96) \
    INSTRUCTION1(ENDASSIGN2_OP, 97) \
    INSTRUCTION2(SETTER_CALL_OP, 98) \
    INSTRUCTION1(GETTER_CALL_OP, 99) \
    INSTRUCTION0(SWAP_OP, 100) \
    INSTRUCTION0(DUP2ND_OP, 101) \
    SPECIAL4(SWITCH_OP_start, 102) \
    SPECIAL4(SWITCH_OP_character, -1) \
    SPECIAL4(SWITCH_OP_integral, -2) \
    SPECIAL0(RETURNJMP_OP, 103) \
    SPECIAL2(STARTSUBSET_N_OP, 104) \
    SPECIAL2(STARTSUBASSIGN_N_OP, 105) \
    INSTRUCTION1(VECSUBSET2_OP, 106) \
    INSTRUCTION1(MATSUBSET2_OP, 107) \
    INSTRUCTION1(VECSUBASSIGN2_OP, 108) \
    INSTRUCTION1(MATSUBASSIGN2_OP, 109) \
    SPECIAL2(STARTSUBSET2_N_OP, 110) \
    SPECIAL2(STARTSUBASSIGN2_N_OP, 111) \
    INSTRUCTION2(SUBSET_N_OP, 112) \
    INSTRUCTION2(SUBSET2_N_OP, 113) \
    INSTRUCTION2(SUBASSIGN_N_OP, 114) \
    INSTRUCTION2(SUBASSIGN2_N_OP, 115) \
    INSTRUCTION1(LOG_OP, 116) \
    INSTRUCTION1(LOGBASE_OP, 117) \
    INSTRUCTION2(MATH1_OP, 118) \
    INSTRUCTION2(DOTCALL_OP, 119) \
    INSTRUCTION1(COLON_OP, 120) \
    INSTRUCTION1(SEQALONG_OP, 121) \
    INSTRUCTION1(SEQLEN_OP, 122)

namespace rjit {

enum class Opcode : int {
#define INSTRUCTION0(name, opcode) name = opcode,
#define INSTRUCTION1(name, opcode) name = opcode,
#define INSTRUCTION2(name, opcode) name = opcode,
#define INSTRUCTION3(name, opcode) name = opcode,
#define INSTRUCTION4(name, opcode) name = opcode,
#define SPECIAL0(name, opcode) name = opcode,
#define SPECIAL1(name, opcode) name = opcode,
#define SPECIAL2(name, opcode) name = opcode,
#define SPECIAL3(name, opcode) name = opcode,
#define SPECIAL4(name, opcode) name = opcode,
RBC
#undef INSTRUCTION0
#undef INSTRUCTION1
#undef INSTRUCTION2
#undef INSTRUCTION3
#undef INSTRUCTION4
#undef SPECIAL0
#undef SPECIAL1
#undef SPECIAL2
#undef SPECIAL3
#undef SPECIAL4
};

} // namespace rjit

#endif // RBC_H