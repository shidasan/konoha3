//#define CLASS_Tvoid 0
//#define CLASS_Tvar 1
//#define CLASS_Object 2
//#define CLASS_Boolean 3
//#define CLASS_Int 4
//#define CLASS_String 5
//#define CLASS_Array 6
//#define CLASS_Param 7
//#define CLASS_Method 8
//#define CLASS_Func 9
//#define CLASS_System 10
//#define CLASS_T0 11
//#define CLASS_BasicBlock 12
//#define CLASS_KonohaCode 13
//#define CLASS_KonohaSpace 14
//#define CLASS_Token 15
//#define CLASS_Expr 16
//#define CLASS_Stmt 17
//#define CLASS_Block 18
//#define CLASS_Gamma 19
//
//#define MN_Object_toString 49157
//#define MN_Boolean_opNOT 15
//#define MN_Boolean_opNEQ 14
//#define MN_Boolean_opEQ 13
//#define MN_Int_opMINUS 7
//#define MN_Int_opADD 6
//#define MN_Int_opSUB 8
//#define MN_Int_opMUL 4
//#define MN_Int_opDIV 2
//#define MN_Int_opMOD 3
//#define MN_Int_opEQ 13
//#define MN_Int_opNEQ 14
//#define MN_Int_opLT 9
//#define MN_Int_opLTE 10
//#define MN_Int_opGT 11
//#define MN_Int_opGTE 12
//#define MN_Int_toString 49157
//#define MN_String_opEQ 13
//#define MN_String_opNEQ 14
//#define MN_String_toInt 49156
//#define MN_String_opADD 6
//#define MN_System_assert 18
//#define MN_System_p 19
//#define MN_System_gc 21
//#define MN_KonohaSpace_importPackage 23
//#define MN_KonohaSpace_import 24
//#define MN_KonohaSpace_load 25
//
////static kopl_u opl0[] = {
////  /* L_00 */{.opOSET = {OPCODE_OSET, 8/*r*/, 0/*n*/}},
////  /* L_01 */{.opOSET = {OPCODE_OSET, 10/*r*/, 1/*n*/}},
////  /* L_02 */{.opSCALL = {OPCODE_SCALL, 8/*r*/, 12/*r*/, 14/*cid*/, 24/*mn of import*/, }},
////  /* L_03 */{.opNMOV = {OPCODE_NMOV, -7/*r*/, 1/*r*/, 2/*cid*/, }},
////  /* L_04 */{.opRET = {OPCODE_RET}},
////};
////
////static kconstdata_t data0[] = {
////  //{14, NULL /* default constant */},
////  //{5, (void*)"konoha.nxt"},
////  {CLASS_Tvoid, (void*)NULL},/* sentinel */
////};
////
////static kmethoddecl_t decl0 = {
////0/*cid*/, 0/*method */,
////data0, opl0
////};
//
//#define CLASS_Float 21
//
//#define MN_Int_toFloat 49173
//#define MN_String_toFloat 49173
//#define MN_Float_opADD 6
//#define MN_Float_opSUB 8
//#define MN_Float_opMUL 4
//#define MN_Float_opDIV 2
//#define MN_Float_opEQ 13
//#define MN_Float_opNEQ 14
//#define MN_Float_opLT 9
//#define MN_Float_opLTE 10
//#define MN_Float_opGT 11
//#define MN_Float_opGTE 12
//#define MN_Float_toInt 49156
//#define MN_Float_toString 49157
//#define MN_Float_opMINUS 7
//#define MN_Float_random 27
//
//#define CLASS_Float 21
//
//#define MN_System_balanceInit 29
//#define MN_System_dly 30
//#define MN_System_actMainTask 31
//#define MN_System_ecrobotIsRunning 32
//#define MN_System_tailControl 33
//#define MN_System_manipulateTail 34
//#define MN_System_ecrobotInitNxtstate 35
//#define MN_System_ecrobotInitSensors 36
//#define MN_System_ecrobotSetLightSensorActive 37
//#define MN_System_ecrobotGetGyroSensor 38
//#define MN_System_ecrobotGetLightSensor 39
//#define MN_System_nxtMotorSetSpeed 40
//#define MN_System_nxtMotorSetCount 41
//#define MN_System_nxtMotorGetCount 42
//#define MN_System_staCyc 43
//#define MN_System_waiSem 44
//#define MN_System_balanceControl 45
//
//
//
////static kopl_u opl1[] = {
////  /* L_00 */{.opNMOV = {OPCODE_NMOV, 10/*r*/, 0/*r*/, 2/*cid*/, }},
////  /* L_01 */{.opOSET = {OPCODE_OSET, 12/*r*/, 2/*n*/}},
////  /* L_02 */{.opSCALL = {OPCODE_SCALL, 10/*r*/, 14/*r*/, 10/*cid*/, 19/*mn of p*/, }},
////  /* L_03 */{.opRET = {OPCODE_RET}},
////};
////
////static kconstdata_t data1[] = {
////  {5, (void*)"hello"},
////  {CLASS_Tvoid, (void*)NULL},/* sentinel */
////};
////
////static kmethoddecl_t decl1 = {
////0/*cid*/, 0/*method */,
////data1, opl1
////};
////
////static kmethoddecl_t *decls[] = {
////  &decl0,
////  &decl1,
////};
