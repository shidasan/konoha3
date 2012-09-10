/****************************************************************************
 * Copyright (c) 2012, the Konoha project authors. All rights reserved.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ***************************************************************************/


// ---------------------------------------------------------------------------
// Syntax Management

static void kNameSpace_parseSugarRule2(KonohaContext *kctx, kNameSpace *ns, const char *rule, kfileline_t uline, kArray *ruleList);

static SugarSyntax* kNameSpace_newSyntax(KonohaContext *kctx, kNameSpace *ns, SugarSyntax *parentSyntax, ksymbol_t keyword)
{
	if(ns->syntaxMapNN == NULL) {
		((kNameSpaceVar*)ns)->syntaxMapNN = KLIB Kmap_init(kctx, 0);
	}
	KUtilsHashMapEntry *e = KLIB Kmap_newEntry(kctx, ns->syntaxMapNN, (uintptr_t)keyword);
	SugarSyntaxVar *syn = (SugarSyntaxVar*)KCALLOC(sizeof(SugarSyntax), 1);
	e->unboxValue = (uintptr_t)syn;
	syn->parentSyntaxNULL = parentSyntax;
	syn->keyword          = keyword;
	if(parentSyntax != NULL) {
//		kreportf(DebugTag, 0, "redefining syntax %s%s on NameSpace=%p, syntax=%p, parent=%p", PSYM_t(keyword), ns, syn, parentSyntax);
		syn->precedence_op1 = parentSyntax->precedence_op1;
		syn->precedence_op2 = parentSyntax->precedence_op2;
	}
	else {
//		kreportf(DebugTag, 0, "new syntax %s%s on NameSpace=%p, syntax=%p, parent=%p", PSYM_t(keyword), ns, syn, parentSyntax);
		syn->precedence_op1 = 0;
		syn->precedence_op2 = 0;
	}
	return syn;
}

static SugarSyntax* kNameSpace_getSyntax(KonohaContext *kctx, kNameSpace *ns, ksymbol_t keyword, int isNew)
{
	kNameSpace *currentNameSpace = ns;
	uintptr_t hcode = keyword;
	while(currentNameSpace != NULL) {
		if(currentNameSpace->syntaxMapNN != NULL) {
			KUtilsHashMapEntry *e = KLIB Kmap_get(kctx, currentNameSpace->syntaxMapNN, hcode);
			while(e != NULL) {
				if(e->hcode == hcode) {
					if(isNew && ns != currentNameSpace) {
						return kNameSpace_newSyntax(kctx, ns, (SugarSyntax*)e->unboxValue, keyword);
					}
					return (SugarSyntax*)e->unboxValue;
				}
				e = e->next;
			}
		}
		currentNameSpace = currentNameSpace->parentNULL;
	}
	return (isNew) ? kNameSpace_newSyntax(kctx, ns, NULL, keyword) : NULL;
}

static void kNameSpace_setSugarFunc(KonohaContext *kctx, kNameSpace *ns, ksymbol_t keyword, size_t idx, kFunc *fo)
{
	assert(idx < SUGARFUNC_SIZE);
	SugarSyntaxVar *syn = (SugarSyntaxVar *)kNameSpace_getSyntax(kctx, ns, keyword, 1/*new*/);
	KINITSETv(ns, syn->sugarFuncTable[idx], fo);
}

static void kNameSpace_addSugarFunc(KonohaContext *kctx, kNameSpace *ns, ksymbol_t keyword, size_t idx, kFunc *funcObject)
{
	SugarSyntaxVar *syn = (SugarSyntaxVar *)kNameSpace_getSyntax(kctx, ns, keyword, 1/*new*/);
	DBG_ASSERT(idx < SUGARFUNC_SIZE);
	if(syn->sugarFuncTable[idx] == NULL) {
		KINITv(syn->sugarFuncTable[idx], funcObject);
		return;
	}
	if(IS_Func(syn->sugarFuncTable[idx])) {
		PUSH_GCSTACK(funcObject);
		kArray *a = GCSAFE_new(Array, 0);
		KLIB kArray_add(kctx, a, syn->sugarFuncTable[idx]);
		KSETv(ns, syn->sugarFuncListTable[idx], a);
	}
	DBG_ASSERT(IS_Array(syn->sugarFuncListTable[idx]));
	KLIB kArray_add(kctx, syn->sugarFuncListTable[idx], funcObject);
}

static void SugarSyntax_setSugarFunc(KonohaContext *kctx, SugarSyntaxVar *syn, MethodFunc definedMethodFunc, size_t index, MethodFunc *previousDefinedFuncRef, kFunc **cachedFuncRef)
{
	if(definedMethodFunc != NULL) {
		if(definedMethodFunc != previousDefinedFuncRef[0]) {
			previousDefinedFuncRef[0] = definedMethodFunc;
			cachedFuncRef[0] = new_SugarFunc(definedMethodFunc);
		}
		KINITv(syn->sugarFuncTable[index], cachedFuncRef[0]);
	}
}

static void kNameSpace_defineSyntax(KonohaContext *kctx, kNameSpace *ns, KDEFINE_SYNTAX *syndef, kNameSpace *packageNameSpace)
{
	MethodFunc pPatternMatch = NULL, pParseExpr = NULL, pStmtTyCheck = NULL, pExprTyCheck = NULL;
	kFunc *mPatternMatch = NULL, *mParseExpr = NULL, *mStmtTyCheck = NULL, *mExprTyCheck = NULL;
	while(syndef->keyword != KW_END) {
		SugarSyntaxVar* syn = (SugarSyntaxVar*)kNameSpace_getSyntax(kctx, ns, syndef->keyword, 1/*isnew*/);
		DBG_ASSERT(syn != NULL);
		{
			syn->lastLoadedPackageId = packageNameSpace->packageId;
			syn->flag  |= ((kshortflag_t)syndef->flag);
			if(syndef->precedence_op1 > 0) {
				syn->precedence_op1 = syndef->precedence_op1;
			}
			if(syndef->precedence_op2 > 0) {
				syn->precedence_op2 = syndef->precedence_op2;
			}
			if(syndef->rule != NULL) {
				KINITv(syn->syntaxRuleNULL, new_(TokenArray, 0));
				kNameSpace_parseSugarRule2(kctx, ns, syndef->rule, 0, syn->syntaxRuleNULL);
			}
			SugarSyntax_setSugarFunc(kctx, syn, syndef->PatternMatch,   SUGARFUNC_PatternMatch,   &pPatternMatch, &mPatternMatch);
			SugarSyntax_setSugarFunc(kctx, syn, syndef->ParseExpr,      SUGARFUNC_ParseExpr,      &pParseExpr, &mParseExpr);
			SugarSyntax_setSugarFunc(kctx, syn, syndef->TopStmtTyCheck, SUGARFUNC_TopStmtTyCheck, &pStmtTyCheck, &mStmtTyCheck);
			SugarSyntax_setSugarFunc(kctx, syn, syndef->StmtTyCheck,    SUGARFUNC_StmtTyCheck,    &pStmtTyCheck, &mStmtTyCheck);
			SugarSyntax_setSugarFunc(kctx, syn, syndef->ExprTyCheck,    SUGARFUNC_ExprTyCheck,    &pExprTyCheck, &mExprTyCheck);
			// set default function
			if(syn->parentSyntaxNULL == NULL && syn->sugarFuncTable[SUGARFUNC_ParseExpr] == NULL) {
				if(syn->precedence_op2 > 0 || syn->precedence_op1 > 0) {
					kFunc *fo = SYN_(ns, KW_ExprOperator)->sugarFuncTable[SUGARFUNC_ParseExpr];
					DBG_ASSERT(fo != NULL);
					KINITv(syn->sugarFuncTable[SUGARFUNC_ParseExpr], fo);
				}
				else if(syn->sugarFuncTable[SUGARFUNC_ExprTyCheck] != NULL) {
					kFunc *fo = SYN_(ns, KW_ExprTerm)->sugarFuncTable[SUGARFUNC_ParseExpr];
					DBG_ASSERT(fo != NULL);
					KINITv(syn->sugarFuncTable[SUGARFUNC_ParseExpr], fo);
				}
			}
			DBG_ASSERT(syn == SYN_(ns, syndef->keyword));
			KLIB Kreportf(kctx, DebugTag, 0, "@%s new syntax %s%s", PackageId_t(packageNameSpace->packageId), PSYM_t(syn->keyword));
		}
		syndef++;
	}
}

// --------------------------------------------------------------------------
// ConstTable

static int comprKeyVal(const void *a, const void *b)
{
	int akey = SYMKEY_unbox(((KUtilsKeyValue*)a)->key);
	int bkey = SYMKEY_unbox(((KUtilsKeyValue*)b)->key);
	return akey - bkey;
}

static KUtilsKeyValue* kNameSpace_getLocalConstNULL(KonohaContext *kctx, kNameSpace *ns, ksymbol_t unboxKey)
{
	size_t min = 0, max = kNameSpace_sizeConstTable(ns);
	while(min < max) {
		size_t p = (max + min) / 2;
		ksymbol_t key = SYMKEY_unbox(ns->constTable.keyvalueItems[p].key);
		if(key == unboxKey) return ns->constTable.keyvalueItems + p;
		if((int)key < (int)unboxKey) {
			min = p + 1;
		}
		else {
			max = p;
		}
	}
	return NULL;
}

static KUtilsKeyValue* kNameSpace_getConstNULL(KonohaContext *kctx, kNameSpace *ns, ksymbol_t unboxKey)
{
	while(ns != NULL) {
		KUtilsKeyValue* foundKeyValue = kNameSpace_getLocalConstNULL(kctx, ns, unboxKey);
		if(foundKeyValue != NULL) return foundKeyValue;
		ns = ns->parentNULL;
	}
	return NULL;
}

static kbool_t kNameSpace_mergeConstData(KonohaContext *kctx, kNameSpaceVar *ns, KUtilsKeyValue *kvs, size_t nitems, kfileline_t pline)
{
	size_t i, s = ns->constTable.bytesize / sizeof(KUtilsKeyValue);
//	DBG_P("mergeConstTable previous_size=%d, size=%d", s, s + nitems);
	if(s == 0) {
		KLIB Karray_init(kctx, &ns->constTable, (nitems + 8) * sizeof(KUtilsKeyValue));
		memcpy(ns->constTable.keyvalueItems, kvs, nitems * sizeof(KUtilsKeyValue));
		for(i = 0; i < nitems; i++) {
			ksymbol_t unboxKey = kvs[i].key;
			KLIB Kreportf(kctx, DebugTag, 0, "@%s loading const %s%s as %s", PackageId_t(ns->packageId), PSYM_t(SYMKEY_unbox(unboxKey)), TY_t(kvs[i].ty));
		}
	}
	else {
		KUtilsWriteBuffer wb;
		KLIB Kwb_init(&(KonohaContext_getSugarContext(kctx)->errorMessageBuffer), &wb);
		for(i = 0; i < nitems; i++) {
			ksymbol_t unboxKey = kvs[i].key;
			KLIB Kreportf(kctx, DebugTag, pline, "loading const %s%s as %s", PSYM_t(SYMKEY_unbox(unboxKey)), TY_t(kvs[i].ty));
			KUtilsKeyValue* stored = kNameSpace_getLocalConstNULL(kctx, ns, unboxKey);
			if(stored != NULL) {
				if(kvs[i].ty == stored->ty && kvs[i].unboxValue == stored->unboxValue) {
					continue;  // same value
				}
				SugarContext_printMessage(kctx, ErrTag, pline, "already defined symbol: %s%s", PSYM_t(SYMKEY_unbox(unboxKey)));
				KLIB Kwb_free(&wb);
				return false;
			}
			KLIB Kwb_write(kctx, &wb, (const char*)(kvs+i), sizeof(KUtilsKeyValue));
		}
		kvs = (KUtilsKeyValue*)KLIB Kwb_top(kctx, &wb, 0);
		nitems = Kwb_bytesize(&wb)/sizeof(KUtilsKeyValue);
		if(nitems > 0) {
			KLIB Karray_resize(kctx, &ns->constTable, (s + nitems + 8) * sizeof(KUtilsKeyValue));
			memcpy(ns->constTable.keyvalueItems + s, kvs, nitems * sizeof(KUtilsKeyValue));
		}
		KLIB Kwb_free(&wb);
	}
	nitems = s + nitems;
	ns->constTable.bytesize = nitems * sizeof(KUtilsKeyValue);
	if(nitems > 0) {
		PLATAPI qsort_i(ns->constTable.keyvalueItems, nitems, sizeof(KUtilsKeyValue), comprKeyVal);
	}
	return true;
}

static kbool_t kNameSpace_setConstData(KonohaContext *kctx, kNameSpace *ns, ksymbol_t key, ktype_t ty, uintptr_t unboxValue, kfileline_t pline)
{
	KUtilsKeyValue kv;
	kv.ty = ty;
	kv.unboxValue = unboxValue;
	if(ty == TY_TEXT) {
		const char *textData = (const char*)unboxValue;
		kv.ty = TY_String;
		kv.stringValue = KLIB new_kString(kctx, textData, strlen(textData), SPOL_TEXT);
		PUSH_GCSTACK(kv.objectValue);
	}
	if(TY_isUnbox(kv.ty) || kv.ty == TY_TYPE) {
		kv.key = key;
	}
	else {
		kv.key = key | SYMKEY_BOXED;
	}
	return kNameSpace_mergeConstData(kctx, (kNameSpaceVar*)ns, &kv, 1, pline);
}

static kbool_t kNameSpace_loadConstData(KonohaContext *kctx, kNameSpace *ns, const char **d, kfileline_t pline)
{
	INIT_GCSTACK();
	KUtilsKeyValue kv;
	KUtilsWriteBuffer wb;
	kbool_t result = true;
	KLIB Kwb_init(&(kctx->stack->cwb), &wb);
	while(d[0] != NULL) {
		kv.key = ksymbolSPOL(d[0], strlen(d[0]), SPOL_TEXT|SPOL_ASCII, _NEWID) | SYMKEY_BOXED;
		kv.ty  = (ktype_t)(uintptr_t)d[1];
		if(kv.ty == TY_TEXT) {
			kv.ty = TY_String;
			kv.stringValue = KLIB new_kString(kctx, d[2], strlen(d[2]), SPOL_TEXT);
			PUSH_GCSTACK(kv.objectValue);
		}
		else if(TY_isUnbox(kv.ty) || kv.ty == TY_TYPE) {
			kv.key = SYMKEY_unbox(kv.key);
			kv.unboxValue = (uintptr_t)d[2];
		}
		else {
			kv.objectValue = (kObject*)d[2];
		}
		KLIB Kwb_write(kctx, &wb, (const char*)(&kv), sizeof(KUtilsKeyValue));
		d += 3;
	}
	size_t nitems = Kwb_bytesize(&wb) / sizeof(KUtilsKeyValue);
	if(nitems > 0) {
		result = kNameSpace_mergeConstData(kctx, (kNameSpaceVar*)ns, (KUtilsKeyValue*)KLIB Kwb_top(kctx, &wb, 0), nitems, pline);
	}
	KLIB Kwb_free(&wb);
	RESET_GCSTACK();
	return result;
}

static kbool_t kNameSpace_importClassName(KonohaContext *kctx, kNameSpace *ns, kNameSpace *targetNameSpace, kfileline_t pline)
{
	KUtilsWriteBuffer wb;
	KLIB Kwb_init(&(kctx->stack->cwb), &wb);
	size_t i, size = kNameSpace_sizeConstTable(targetNameSpace);
	kbool_t result = true;
	for(i = 0; i < size; i++) {
		KUtilsKeyValue *kvs = targetNameSpace->constTable.keyvalueItems + i;
		if(kvs->ty == TY_TYPE) {
			KonohaClass *ct = (KonohaClass*)kvs->unboxValue;
			if(CT_isPrivate(ct)) continue;
			if(targetNameSpace->packageId == ct->packageId) {
				DBG_P("importing packageId=%s.%s to %s..", PackageId_t(ct->packageId), SYM_t(ct->classNameSymbol), PackageId_t(ns->packageId));
				KLIB Kwb_write(kctx, &wb, (const char*)(kvs), sizeof(KUtilsKeyValue));
			}
//			kv.key = ct->classNameSymbol;
//			kv.ty  = TY_TYPE;
//			kv.unboxValue = (uintptr_t)ct;
//			KLIB Kwb_write(kctx, &wb, (const char*)(&kv), sizeof(KUtilsKeyValue));
		}
	}
	size_t nitems = Kwb_bytesize(&wb) / sizeof(KUtilsKeyValue);
	if(nitems > 0) {
		result = kNameSpace_mergeConstData(kctx, (kNameSpaceVar*)ns, (KUtilsKeyValue*)KLIB Kwb_top(kctx, &wb, 0), nitems, pline);
	}
	KLIB Kwb_free(&wb);
	return result;
}

static KonohaClass *kNameSpace_getClass(KonohaContext *kctx, kNameSpace *ns, const char *name, size_t len, KonohaClass *defaultClass)
{
	KonohaClass *ct = NULL;
	kpackage_t packageId= PN_konoha;
	ksymbol_t  un = SYM_NONAME;
	char *p = strrchr(name, '.');
	if(p == NULL) {
		un = ksymbolA(name, len, SYM_NONAME);
	}
	else {
		size_t plen = p - name;
		un = ksymbolA(name + (plen+1), len - (plen+1), SYM_NONAME);
		packageId = KLIB KpackageId(kctx, name, plen, 0, SYM_NONAME);
	}
	if(packageId != SYM_NONAME) {
		KUtilsKeyValue *kvs = kNameSpace_getConstNULL(kctx, ns, un);
		if(kvs != NULL && kvs->ty == TY_TYPE) {
			return (KonohaClass*)kvs->unboxValue;
		}
	}
	return (ct != NULL) ? ct : defaultClass;
}

static KonohaClass *kNameSpace_defineClass(KonohaContext *kctx, kNameSpace *ns, kString *name, KDEFINE_CLASS *cdef, kfileline_t pline)
{
	KonohaClass *ct = KLIB KonohaClass_define(kctx, ns->packageId, name, cdef, pline);
	if(!KLIB kNameSpace_setConstData(kctx, ns, ct->classNameSymbol, TY_TYPE, (uintptr_t)ct, pline)) {
		return NULL;
	}
	return ct;
}

// --------------------------------------------------------------------------
// Method Management

static int formatLowerCanonicalName(char *buf, size_t bufsiz, const char *name)
{
	size_t i = 0;
	const char* p = name;
	while(p[0] != 0) {
		if(p[0] != '_') {
			buf[i] = tolower(p[0]);
		}
		i++;
		p++;
		if(!(i + 1 < bufsiz)) break;
	}
	buf[i] = 0;
	return i;
}

static kbool_t checkMethodPolicyOption(KonohaContext *kctx, kMethod *mtd, int option, int policy)
{
	if(TFLAG_is(int, policy, MPOL_PARAMSIZE)) {
		kParam *param = Method_param(mtd);
		if(param->psize != option) return false;
	}
	if(TFLAG_is(int, policy, MPOL_SIGNATURE)) {
		if(mtd->paramdom != option) return false;
	}
//	if(TFLAG_is(int, policy, MPOL_SETTER)) {
//		kParam *param = Method_param(mtd);
//		if(param->psize > 0 && param->paramtypeItems[param->psize - 1].ty != (ktype_t)option) return false;
//	}
	return true;
}

static kMethod* kMethodList_getCanonicalMethodNULL(KonohaContext *kctx, kArray *methodList, size_t beginIdx, ktype_t typeId, ksymbol_t mn, int option, int policy)
{
	size_t i;
	const char *name = SYM_t(SYM_UNMASK(mn));
	char canonicalName[80], methodCanonicalName[80];
	int firstChar = tolower(name[0]), namesize = formatLowerCanonicalName(canonicalName, sizeof(canonicalName), name);
	//DBG_P("canonicalName=%s.'%s'", TY_t(typeId), canonicalName);
	kMethod *foundMethod = NULL;
	for(i = beginIdx; i < kArray_size(methodList); i++) {
		kMethod *mtd = methodList->methodItems[i];
		if(SYM_HEAD(mtd->mn) != SYM_HEAD(mn)) continue;
		if(typeId != TY_var && mtd->typeId != typeId) continue;
		const char *n = SYM_t(SYM_UNMASK(mtd->mn));
		if(firstChar == tolower(n[0]) && namesize == formatLowerCanonicalName(methodCanonicalName, sizeof(methodCanonicalName), n)) {
			if(strcmp(canonicalName, methodCanonicalName) != 0) continue;
			if(policy > 1 && !checkMethodPolicyOption(kctx, mtd, option, policy)) {
				continue;
			}
			if(TFLAG_is(int, policy, MPOL_LATEST)) {
				foundMethod = mtd;
				continue;
			}
			return mtd;  // first one;
		}
	}
	return foundMethod;
}

static kMethod* kMethodList_getMethodNULL(KonohaContext *kctx, kArray *methodList, size_t beginIdx, ktype_t typeId, ksymbol_t mn, int option, int policy)
{
	kMethod *foundMethod = NULL;
	int i, filteredPolicy = policy & (~(MPOL_CANONICAL));
	for(i = beginIdx; i < kArray_size(methodList); i++) {
		kMethod *mtd = methodList->methodItems[i];
		if(mtd->mn != mn) continue;
		if(typeId != TY_var && mtd->typeId != typeId) continue;
		if(filteredPolicy > 1 && !checkMethodPolicyOption(kctx, mtd, option, filteredPolicy)) {
			continue;
		}
		foundMethod = mtd;
		if(!TFLAG_is(int, policy, MPOL_LATEST)) {
			break;
		}
	}
	if(foundMethod == NULL && TFLAG_is(int, policy, MPOL_CANONICAL)) {
		foundMethod = kMethodList_getCanonicalMethodNULL(kctx, methodList, beginIdx, typeId, mn, option, filteredPolicy);
//		DBG_P("canonicalName=%s.%s'%s', mtd=%p", TY_t(typeId), PSYM_t(mn), foundMethod);
//		if(foundMethod != NULL) {
//			DBG_P("method=%s.%s%s, mtd=%p", Method_t(foundMethod));
//		}
//		DBG_ASSERT(foundMethod == NULL);
	}
	return foundMethod;
}

static void kMethodList_findMethodList(KonohaContext *kctx, kArray *methodList, ktype_t typeId, ksymbol_t mn, kArray *resultList, int beginIdx)
{
	size_t i;
	for(i = 0; i < kArray_size(methodList); i++) {
		kMethod *mtd = methodList->methodItems[i];
		if(mtd->mn != mn) continue;
		if(typeId != TY_var && mtd->typeId != typeId) continue;
		kMethod *foundMethod = kMethodList_getMethodNULL(kctx, resultList, beginIdx, typeId, mn, 0, MPOL_FIRST);
		if(foundMethod == NULL) {
			KLIB kArray_add(kctx, resultList, mtd);
		}
	}
}

static void kNameSpace_findMethodList(KonohaContext *kctx, kNameSpace *ns, ktype_t typeId, ksymbol_t mn, kArray *resultList, int beginIdx)
{
	KonohaClass *ct = CT_(typeId);
	while(ns != NULL) {
		kMethodList_findMethodList(kctx, ns->methodList, typeId, mn, resultList, beginIdx);
		ns = ns->parentNULL;
	}
	while(ct != NULL) {
		kMethodList_findMethodList(kctx, ct->methodList, TY_var, mn, resultList, beginIdx);
		ct = ct->searchSuperMethodClassNULL;
	}
}

static kMethod* KonohaClass_getMethodNULL(KonohaContext *kctx, KonohaClass *ct, kmethodn_t mn, int option, int policy)
{
	while(ct != NULL) {
		kMethod *mtd = kMethodList_getMethodNULL(kctx, ct->methodList, 0, TY_var, mn, option, policy);
		if(mtd != NULL) return mtd;
		ct = ct->searchSuperMethodClassNULL;
	}
	return NULL;
}

static kMethod* kNameSpace_getFirstMethodNULL(KonohaContext *kctx, kNameSpace *ns, ktype_t typeId, kmethodn_t mn, int option, int policy)
{
	if(ns != NULL) {
		kMethod *mtd = kNameSpace_getFirstMethodNULL(kctx, ns->parentNULL, typeId, mn, option, policy);
		if(mtd != NULL) return mtd;
		mtd = kMethodList_getMethodNULL(kctx, ns->methodList, 0, typeId, mn, option, policy);
		return mtd;
	}
	return NULL;
}

static kMethod* kNameSpace_getMethodNULL(KonohaContext *kctx, kNameSpace *ns, ktype_t typeId, kmethodn_t mn, int option, int policy)
{
	if(TFLAG_is(int, policy, MPOL_LATEST)) {
		while(ns != NULL) {
			kMethod *mtd = kMethodList_getMethodNULL(kctx, ns->methodList, 0, typeId, mn, option, policy);
			if(mtd != NULL) return mtd;
			ns = ns->parentNULL;
		}
		return KonohaClass_getMethodNULL(kctx, CT_(typeId), mn, option, policy);
	}
	else {
		kMethod *mtd = KonohaClass_getMethodNULL(kctx, CT_(typeId), mn, option, policy);
		if(mtd != NULL) return mtd;
		return kNameSpace_getFirstMethodNULL(kctx, ns, typeId, mn, option, policy);
	}
}

static kMethod* kMethod_replaceWith(KonohaContext *kctx, kMethodVar *oldMethod, kMethodVar *newMethod)
{
	if(Method_isOverride(newMethod)) {
		kMethodVar tempMethod;
		tempMethod = *oldMethod;
		*oldMethod = *newMethod;
		*newMethod = tempMethod;
		return NULL;  // when it succeed
	}
	return oldMethod;
}

static kMethod* kNameSpace_addMethod(KonohaContext *kctx, kNameSpace *ns, kMethod *mtd)
{
	KonohaClass *ct = CT_(mtd->typeId);
	if(mtd->packageId == 0 && ns != NULL) {
		((kMethodVar*)mtd)->packageId = ns->packageId;
		KLIB Kreportf(kctx, DebugTag, 0, "@%s loading method %s.%s%s", PackageId_t(ns->packageId), Method_t(mtd));
	}
	if(Method_isPublic(mtd) /* && ct->packageDomain == ns->packageDomain*/) {
		kMethod *foundMethod = KonohaClass_getMethodNULL(kctx, ct, mtd->mn, mtd->paramdom, MPOL_FIRST|MPOL_SIGNATURE);
		if(foundMethod != NULL) {  // same signature
			if(foundMethod->typeId == mtd->typeId) {
				DBG_P("duplicated method %s.%s%s", Method_t(foundMethod));
				PUSH_GCSTACK(mtd);  // avoid memory leaking
				return kMethod_replaceWith(kctx, (kMethodVar*)foundMethod, (kMethodVar*)mtd);
			}
			else {
				if(!Method_isFinal(foundMethod)) {
					DBG_P("Changing Virtual method %s.%s%s by %s.%s%s....", Method_t(foundMethod), Method_t(mtd));
					Method_setVirtual(foundMethod, true);  // FIXME
				}
				if(!Method_isVirtual(foundMethod) || Method_isFinal(foundMethod)) {
					DBG_P("Can't override method %s.%s%s <: %s.%s%s ....", Method_t(mtd), Method_t(foundMethod));
					return NULL;
				}
			}
		}
		else {
			foundMethod = KonohaClass_getMethodNULL(kctx, ct, mtd->mn, Method_paramsize(mtd), MPOL_FIRST|MPOL_PARAMSIZE);
			if(foundMethod != NULL) {
				DBG_P("set overloading method %s.%s%s", Method_t(foundMethod));
				Method_setOverloaded(foundMethod, true);
				Method_setOverloaded(mtd, true);
			}
		}
		if(unlikely(ct->methodList == K_EMPTYARRAY)) {
			KINITv(((KonohaClassVar*)ct)->methodList, new_(MethodArray, 8));
		}
		KLIB kArray_add(kctx, ct->methodList, mtd);
	}
	else {
		size_t i;
		for(i = 0; i < kArray_size(ns->methodList); i++) {
			kMethod *foundMethod = ns->methodList->methodItems[i];
			if(foundMethod->typeId == mtd->typeId && foundMethod->mn == mtd->mn && foundMethod->paramdom == mtd->paramdom) {
				DBG_P("duplicated method %s.%s%s", Method_t(foundMethod));
				PUSH_GCSTACK(mtd);  // avoid memory leaking
				return kMethod_replaceWith(kctx, (kMethodVar*)foundMethod, (kMethodVar*)mtd);
			}
		}
		kArray *matchedMethodList = kctx->stack->gcstack;
		size_t popMatchedMethodListSize = kArray_size(matchedMethodList);
		kNameSpace_findMethodList(kctx, ns, mtd->typeId, mtd->mn, matchedMethodList, popMatchedMethodListSize);
		if(popMatchedMethodListSize < kArray_size(matchedMethodList)) {
			int count = 0;
			for(i = popMatchedMethodListSize; i < kArray_size(matchedMethodList); i++) {
				kMethod *foundMethod = matchedMethodList->methodItems[i];
				if(Method_paramsize(foundMethod) == Method_paramsize(mtd)) {
					Method_setOverloaded(foundMethod, true);
					count++;
				}
			}
			if(count > 0) {
				DBG_P("set overloading method %s.%s%s", Method_t(mtd));
				Method_setOverloaded(mtd, true);
			}
			KLIB kArray_clear(kctx, matchedMethodList, popMatchedMethodListSize);
		}
		if(ns->methodList == K_EMPTYARRAY) {
			KSETv(ns, ((kNameSpaceVar*)ns)->methodList, new_(MethodArray, 8));
		}
		KLIB kArray_add(kctx, ns->methodList, mtd);
	}
	return NULL;
}

static void kNameSpace_loadMethodData(KonohaContext *kctx, kNameSpace *ns, intptr_t *data)
{
	intptr_t *d = data;
	while(d[0] != -1) {
		uintptr_t flag = (uintptr_t)d[0];
		MethodFunc f = (MethodFunc)d[1];
		ktype_t rtype = (ktype_t)d[2];
		ktype_t cid  = (ktype_t)d[3];
		kmethodn_t mn = (kmethodn_t)d[4];
		size_t i, psize = (size_t)d[5];
		kparamtype_t p[psize+1];
		d = d + 6;
		for(i = 0; i < psize; i++) {
			p[i].ty = (ktype_t)d[0];
			p[i].fn = (ksymbol_t)d[1];
			d += 2;
		}
		kMethod *mtd = KLIB new_kMethod(kctx, flag, cid, mn, f);
		KLIB kMethod_setParam(kctx, mtd, rtype, psize, p);
		kNameSpace_addMethod(kctx, ns, mtd);
	}
}

static kMethod* kNameSpace_getCastMethodNULL(KonohaContext *kctx, kNameSpace *ns, ktype_t cid, ktype_t tcid)
{
	kMethod *mtd = kNameSpace_getMethodNULL(kctx, ns, cid, MN_to(tcid), 0, MPOL_PARAMSIZE|MPOL_FIRST);
	if(mtd == NULL) {
		mtd = kNameSpace_getMethodNULL(kctx, ns, cid, MN_as(tcid), 0, MPOL_PARAMSIZE|MPOL_FIRST);
	}
	return mtd;
}

// ---------------------------------------------------------------------------

static kstatus_t kNameSpace_eval(KonohaContext *kctx, kNameSpace *ns, const char *script, kfileline_t uline);

typedef struct {
	KonohaContext *kctx;
	kNameSpace *ns;
} SugarThunk;

static int evalHookFunc(const char* script, long uline, int *isBreak, void *thunk)
{
	SugarThunk *t = (SugarThunk*)thunk;
//	if(verbose_sugar) {
//		DUMP_P("\n>>>----\n'%s'\n------\n", script);
//	}
	kstatus_t result = kNameSpace_eval(t->kctx, t->ns, script, uline);
	*isBreak = (result == K_BREAK);
	return (result != K_FAILED);
}

#ifndef PATH_MAX
#define PATH_MAX 1024
#endif

static kfileline_t uline_init(KonohaContext *kctx, const char *path, int line, int isreal)
{
	kfileline_t uline = line;
	uline |= KLIB KfileId(kctx, path, strlen(path), 0, _NEWID);
	return uline;
}

static kbool_t kNameSpace_loadScript(KonohaContext *kctx, kNameSpace *ns, const char *path, kfileline_t pline)
{
	SugarThunk thunk = {kctx, ns};
	kfileline_t uline = uline_init(kctx, path, 1, true/*isRealPath*/);
	if(!(PLATAPI loadScript(path, uline, (void*)&thunk, evalHookFunc))) {
		kreportf(ErrTag, pline, "failed to load script: %s", PLATAPI shortText(path));
		return false;
	}
	return true;
}

// ---------------------------------------------------------------------------
// package

static kNameSpace* new_PackageNameSpace(KonohaContext *kctx, kpackage_t packageDomain, kpackage_t packageId)
{
	kNameSpaceVar *ns = GCSAFE_new(NameSpaceVar, KNULL(NameSpace));
	ns->packageId = packageId;
	ns->packageDomain = packageId;
	return (kNameSpace*)ns;
}

static KonohaPackage *loadPackageNULL(KonohaContext *kctx, kpackage_t packageId, kfileline_t pline)
{
	const char *packageName = S_text(PackageId_s(packageId));
	char pathbuf[256];
	const char *path = PLATAPI formatPackagePath(pathbuf, sizeof(pathbuf), packageName, "_glue.k");
	KonohaPackageHandler *packageHandler = PLATAPI loadPackageHandler(packageName);
	if(path == NULL && packageHandler == NULL) {
		KLIB Kreportf(kctx, ErrTag, pline, "package not found: %s path=%s", packageName, PLATAPI shortText(pathbuf));
		KLIB KonohaRuntime_raise(kctx, EXPT_("PackageLoader"), NULL, pline, NULL);
		return NULL;
	}
	kNameSpace *ns = new_PackageNameSpace(kctx, packageId, packageId);
	if(packageHandler != NULL && packageHandler->initPackage != NULL) {
		packageHandler->initPackage(kctx, ns, 0, NULL, pline);
	}
	if(path != NULL) {
		if(!kNameSpace_loadScript(kctx, ns, pathbuf, pline)) {
			return NULL;
		}
	}
	KonohaPackage *pack = (KonohaPackage*)KCALLOC(sizeof(KonohaPackage), 1);
	pack->packageId = packageId;
	KINITv(pack->packageNameSpace, ns);
	pack->packageHandler = packageHandler;
	path = PLATAPI formatPackagePath(pathbuf, sizeof(pathbuf), packageName, "_exports.k");
	if(path != NULL) {
		pack->exportScriptUri = KLIB KfileId(kctx, pathbuf, strlen(pathbuf), 0, _NEWID) | 1;
	}
	return pack;
}

static KonohaPackage *getPackageNULL(KonohaContext *kctx, kpackage_t packageId, kfileline_t pline)
{
	KonohaPackage *pack = (KonohaPackage*)map_getu(kctx, kmodsugar->packageMapNO, packageId, uNULL);
	isFirstTime_t flag = isFirstTime;
	if(pack == NULL) {
		pack = loadPackageNULL(kctx, packageId, pline);
		if(pack == NULL) return NULL;
		map_addu(kctx, kmodsugar->packageMapNO, packageId, (uintptr_t)pack);
		flag = Nope;
	}
	if(pack->packageHandler != NULL && pack->packageHandler->setupPackage != NULL) {
		pack->packageHandler->setupPackage(kctx, pack->packageNameSpace, flag, pline);
	}
	return pack;
}

static kbool_t kNameSpace_isImported(KonohaContext *kctx, kNameSpace *ns, kNameSpace *target, kfileline_t pline)
{
	KUtilsKeyValue* value = kNameSpace_getLocalConstNULL(kctx, ns, target->packageId | KW_PATTERN);
	if(value != NULL) {
		kreportf(DebugTag, pline, "package %s has already imported in %s", PackageId_t(ns->packageId), PackageId_t(target->packageId));
		return true;
	}
	return false;
}

static kbool_t kNameSpace_merge(KonohaContext *kctx, kNameSpace *ns, kNameSpace *target, kfileline_t pline)
{
	if(!kNameSpace_isImported(kctx, ns, target, pline)) {
		DBG_P("target->packageId=%s", PackageId_t(target->packageId));
		if(!kNameSpace_importClassName(kctx, ns, target, pline)) {
			return false;
		}
		if(target->constTable.bytesize > 0) {
			if(!kNameSpace_mergeConstData(kctx, (kNameSpaceVar*)ns, target->constTable.keyvalueItems, target->constTable.bytesize/sizeof(KUtilsKeyValue), pline)) {
				return false;
			}
		}
		size_t i;
		for(i = 0; i < kArray_size(target->methodList); i++) {
			kMethod *mtd = target->methodList->methodItems[i];
			if(Method_isPublic(mtd) && mtd->packageId == target->packageId) {
				KLIB kArray_add(kctx, ns->methodList, mtd);
			}
		}
		// record imported
		return kNameSpace_setConstData(kctx, ns, target->packageId | KW_PATTERN, TY_int, target->packageId, pline);
	}
	return false;
}

static KonohaPackage* kNameSpace_requirePackage(KonohaContext *kctx, const char *name, kfileline_t pline)
{
	kpackage_t packageId = KLIB KpackageId(kctx, name, strlen(name), 0, _NEWID);
	KonohaPackage *pack = getPackageNULL(kctx, packageId, pline);
	return pack;
}

static kbool_t kNameSpace_importPackage(KonohaContext *kctx, kNameSpace *ns, const char *name, kfileline_t pline)
{
	kpackage_t packageId = KLIB KpackageId(kctx, name, strlen(name), 0, _NEWID);
	KonohaPackage *pack = getPackageNULL(kctx, packageId, pline);
	DBG_ASSERT(ns != NULL);
	if(pack != NULL) {
		kbool_t isContinousLoading = kNameSpace_merge(kctx, ns, pack->packageNameSpace, pline);
		if(isContinousLoading && pack->packageHandler != NULL && pack->packageHandler->initNameSpace != NULL) {
			isContinousLoading = pack->packageHandler->initNameSpace(kctx, pack->packageNameSpace, ns, pline);
		}
		if(isContinousLoading && pack->exportScriptUri != 0) {
			const char *scriptPath = FileId_t(pack->exportScriptUri);
			kfileline_t uline = pack->exportScriptUri | (kfileline_t)1;
			SugarThunk thunk = {kctx, ns};
			isContinousLoading = PLATAPI loadScript(scriptPath, uline, (void*)&thunk, evalHookFunc);
		}
		if(isContinousLoading && pack->packageHandler != NULL && pack->packageHandler->setupNameSpace != NULL) {
			isContinousLoading = pack->packageHandler->setupNameSpace(kctx, pack->packageNameSpace, ns, pline);
		}
		return true;
	}
	return false;
}

kstatus_t MODSUGAR_loadScript(KonohaContext *kctx, const char *path, size_t len, kfileline_t pline)
{
	if (KonohaContext_getSugarContext(kctx) == NULL) {
		kmodsugar->h.setup(kctx, (KonohaModule*)kmodsugar, 0/*lazy*/);
	}
	INIT_GCSTACK();
	kpackage_t packageId = KLIB KpackageId(kctx, "main", sizeof("main")-1, 0, _NEWID);
	kNameSpace *ns = new_PackageNameSpace(kctx, packageId, packageId);
	PUSH_GCSTACK(ns);
	kstatus_t result = kNameSpace_loadScript(kctx, ns, path, pline);
	RESET_GCSTACK();
	return result;
}
