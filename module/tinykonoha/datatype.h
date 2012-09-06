#define KVPROTO_INIT  8
#define KVPROTO_DELTA 7

//#include<../../include/minikonoha/float.h>
#include<../../package/konoha.nxt/nxt_glue.h>
//#include<../../package/konoha.float/float_glue.c>

//static inline karray_t* kvproto_null(void)  // for proto_get safe null
//{
//	static kvs_t dnull[KVPROTO_DELTA] = {};
//	static karray_t pnull = {
//		.bytesize = sizeof(kvs_t), .bytemax = 0,
//	};
//	pnull.kvs = dnull;
//	return &pnull;
//}

static kObject *DEFAULT_fnull(KonohaContext *kctx, KonohaClass *ct)
{
	DBG_ASSERT(ct->defaultValueAsNull != NULL);
	return ct->defaultValueAsNull;
}

static void DEFAULT_init(KonohaContext *kctx, kObject *o, void *conf)
{
	(void)kctx;(void)o;(void)conf;
}

static void DEFAULT_reftrace(KonohaContext *kctx, kObject *o)
{
	(void)kctx;(void)o;
}

static void DEFAULT_free(KonohaContext *kctx, kObject *o)
{
	(void)kctx;(void)o;
}

static void DEFAULT_p(KonohaContext *kctx, KonohaStack *sfp, int pos, KUtilsWriteBuffer *wb, int level)
{
	(void)kctx;(void)sfp;(void)pos;(void)wb;(void)level;
}

static uintptr_t DEFAULT_unbox(KonohaContext *kctx, kObject *o)
{
	return 0;
}

static kObject *new_Object(KonohaContext *kctx, KonohaClass *ct, uintptr_t conf)
{
	DBG_ASSERT(ct->cstruct_size > 0);
	kObjectVar *o = (kObjectVar*) MODGC_omalloc(kctx, ct->cstruct_size);
	o->h.magicflag = ct->magicflag;
	o->h.cid = ct->typeId;
	//o->h.kvproto = kvproto_null();
	ct->init(kctx, (kObject*)o, conf);
	return (kObject*)o;
}

static void Object_init(KonohaContext *kctx, kObject *o, void *conf)
{
	kObjectVar *of = (kObjectVar*)o;
	of->fieldUnboxItems[0] = 0;
	of->fieldUnboxItems[1] = 0;
}

kObjectVar** KONOHA_reftail(KonohaContext *kctx, size_t size);
static void Object_reftrace(KonohaContext *kctx, kObject *o)
{
	kObject *of = (kObject*)o;
	KonohaClass *ct = O_ct(of);
	BEGIN_REFTRACE(ct->fieldsize);
	size_t i;
	for(i = 0; i < ct->fieldsize; i++) {
		if(ct->fieldItems[i].isobj) {
			KREFTRACEv(of->fieldObjectItems[i]);
		}
	}
	END_REFTRACE();
}

//static void ObjectX_init(KonohaContext *kctx, kObject *o, void *conf)
//{
//	kObjectVar *of = (kObjectVar*)o;
//	KonohaClass *ct = O_ct(of);
//	assert(CT_isDefined(ct));
//	assert(ct->defaultValueAsNullVar != NULL);
//	memcpy(of->fieldObjectItems, ct->defaultValueAsNullVar->fieldObjectItems, ct->cstruct_size - sizeof(KonohaObjectHeader));
//}

static void Object_initdef(KonohaContext *kctx, KonohaClassVar *ct, kfileline_t pline)
{
	//if(ct->typeId == TY_Object) return;
	//DBG_P("new object initialization ct->cstruct_size=%d", ct->cstruct_size);
	//KSETv(ct, ct->defaultValueAsNullVar, new_kObject(ct, NULL));
	//if(ct->fieldsize > 0) {  // this is size of super class
	//	KonohaClass *supct = CT_(ct->superTypeId);
	//	assert(ct->fieldsize == supct->fieldsize);
	//	memcpy(ct->defaultValueAsNullVar->fieldObjectItems, supct->defaultValueAsNullVar->fieldObjectItems, sizeof(kObject*) * ct->fieldsize);
	//}
	//if(ct->fieldAllocSize > 0) {
	//	ct->init = ObjectX_init;
	//}
	//ct->fnull = DEFAULT_fnull;
}

static uintptr_t Number_unbox(KonohaContext *kctx, kObject *o)
{
	kNumber *n = (kNumber*)o;
	return (uintptr_t) n->unboxValue;
}

// Boolean
static void Number_init(KonohaContext *kctx, kObject *o, void *conf)
{
	kNumberVar *n = (kNumberVar*)o;
	n->unboxValue = (uintptr_t)conf;
}

static void Boolean_p(KonohaContext *kctx, KonohaStack *sfp, int pos, KUtilsWriteBuffer *wb, int level)
{
	//kwb_printf(wb, sfp[pos].bvalue ? "true" : "false");
}

static kObject* Boolean_fnull(KonohaContext *kctx, KonohaClass *ct)
{
	return (kObject*)K_FALSE;
}

static void Int_p(KonohaContext *kctx, KonohaStack *sfp, int pos, KUtilsWriteBuffer *wb, int level)
{
	//kwb_printf(wb, KINT_FMT, sfp[pos].ivalue);
}

// String
static void String_init(KonohaContext *kctx, kObject *o, void *conf)
{
	kStringVar *s = (kStringVar*)o;
	s->text = (char*)conf;
	s->bytesize = 0;
	S_setTextSgm(s, 1);
}

static void String_free(KonohaContext *kctx, kObject *o)
{
	kString *s = (kString*)o;
	if(S_isMallocText(s)) {
		KFREE(s->buf, S_size(s) + 1);
	}
}

static void String_p(KonohaContext *kctx, KonohaStack *sfp, int pos, KUtilsWriteBuffer *wb, int level)
{
	//if(level == 0) {
	//	kwb_printf(wb, "%s", S_text(sfp[pos].o));
	//}
	//else {
	//	kwb_printf(wb, "\"%s\"", S_text(sfp[pos].o));
	//}
}

static uintptr_t String_unbox(KonohaContext *kctx, kObject *o)
{
	kString *s = (kString*)o;
	DBG_ASSERT(IS_String(s));
	return (uintptr_t) s->text;
}

static void String_checkASCII(KonohaContext *kctx, kString *s)
{
	unsigned char ch = 0;
	long len = S_size(s), n = (len + 3) / 4;
	const unsigned char*p = (const unsigned char *)S_text(s);
	switch(len % 4) { /* Duff's device written by ide */
		case 0: do{ ch |= *p++;
		case 3:     ch |= *p++;
		case 2:     ch |= *p++;
		case 1:     ch |= *p++;
		} while(--n>0);
	}
	S_setASCII(s, (ch < 128));
}

static kString* new_String(KonohaContext *kctx, const char *text, size_t len, int spol)
{
	KonohaClass *ct = CT_(CLASS_String);
	kStringVar *s = NULL; //knh_PtrMap_getS(kctx, ct->constPoolMapNULL, text, len);
	if(s != NULL) return s;
	if(TFLAG_is(int, spol, SPOL_TEXT)) {
		s = (kStringVar*)new_Object(kctx, ct, 0);
		s->text = text;
		s->bytesize = len;
		S_setTextSgm(s, 1);
	}
	/* not allowed to use inline_text area */
	//else if(len + 1 < sizeof(void*) * 2) {
	//	s = (kStringVar*)new_Object(kctx, ct, 0);
	//	s->text = s->inline_text;
	//	s->bytesize = len;
	//	S_setTextSgm(s, 1);
	//	if(text != NULL) {
	//		DBG_ASSERT(!TFLAG_is(int, spol, SPOL_NOCOPY));
	//		memcpy(s->ubuf, text, len);
	//	}
	//	s->buf[len] = '\0';
	//}
	else {
		s = (kStringVar*)new_Object(kctx, ct, 0);
		s->bytesize = len;
		s->buf = (char*)KMALLOC(len+1);
		S_setTextSgm(s, 0);
		S_setMallocText(s, 1);
		if(text != NULL) {
			DBG_ASSERT(!TFLAG_is(int, spol, SPOL_NOCOPY));
			memcpy(s->ubuf, text, len);
		}
		s->buf[len] = '\0';
	}
	if(TFLAG_is(int, spol, SPOL_ASCII)) {
		S_setASCII(s, 1);
	}
	else if(TFLAG_is(int, spol, SPOL_UTF8)) {
		S_setASCII(s, 0);
	}
	else {
		String_checkASCII(kctx, s);
	}
//	if(TFLAG_is(int, policy, SPOL_POOL)) {
//		kmapSN_add(kctx, ct->constPoolMapNO, s);
//		S_setPooled(s, 1);
//	}
	return s;
}

static void Param_init(KonohaContext *kctx, kObject *o, void *conf)
{
	kParamVar *pa = (kParamVar*)o;
	pa->psize = 0;
	pa->rtype = TY_void;
}

static KonohaClassVar *new_KonohaClass(KonohaContext *kctx, KonohaClass *bct, KDEFINE_CLASS *s, kfileline_t pline)
{
	KonohaRuntimeVar *share = kctx->share;
	ktype_t newid = share->classTable.bytesize / sizeof(KonohaClassVar*);
	if (share->classTable.bytesize == share->classTable.bytemax) {
		KLIB Karray_expand(kctx, &share->classTable, share->classTable.bytemax * 2);
	}
	share->classTable.bytesize += sizeof(KonohaClassVar*);
	KonohaClassVar *ct = (KonohaClassVar*)KCALLOC(sizeof(KonohaClass), 1);
	share->classTable.classItems[newid] = (KonohaClass*)ct;
	//ktype_t newcid = share->casize;
	//share->casize++;
	//KonohaClassVar *ct = share->classTable[newcid];
	if (bct != NULL) {
		DBG_ASSERT(s == NULL);
		memcpy(ct, bct, offsetof(KonohaClass, methodList));
		ct->typeId = newid;
		//if (ct->fnull == DEFAULT_fnull) ct->fnull = DEFAULT_fnullinit;
	} else {
		DBG_ASSERT(s != NULL);
		ct->cflag = s->cflag;
		ct->typeId = newid;
		ct->baseTypeId = newid;
		ct->superTypeId = (s->superTypeId == 0) ? CLASS_Object : s->superTypeId;
		ct->fieldItems = s->fieldItems;
		ct->fieldsize = s->fieldsize;
		ct->fieldAllocSize = s->fieldAllocSize;
		ct->cstruct_size = size64(s->cstruct_size);
		if (s->cparamsize > 0 && s->cparamItems != NULL) {
			DBG_P("params");
			ct->p0 = s->cparamItems[0].ty;
			//KINITv(ct->cparam, new_kParam2(s->rtype, s->psize, s->cparamItems));
		}
		ct->init = (s->init != NULL) ? s->init : DEFAULT_init;
		ct->reftrace = (s->reftrace != NULL) ? s->reftrace : DEFAULT_reftrace;
		ct->p = (s->p != NULL) ? s->p : DEFAULT_p;
		ct->unbox = (s->unbox != NULL) ? s->unbox : DEFAULT_unbox;
		ct->free = (s->free != NULL) ? s->free : DEFAULT_free;
		//ct->fnull = (s->fnull != NULL) ? s->fnull : DEFAULT_fnullinit;
		//ct->realtype = (s->realtype != NULL) ? s->realtype : DEFAULT_realtype;
		//ct->isSubType = (s->isSubType != NULL) ? s->isSubType : DEFAULT_isSubType;
		ct->initdef = s->initdef;
	}
	if (ct->initdef != NULL) {
		ct->initdef(kctx, ct, pline);
	}
	return ct;
}

static KonohaClass *CT_body(KonohaContext *kctx, KonohaClass *ct, size_t head, size_t body)
{
	KonohaClass *bct = ct;
	while(ct->cstruct_size < sizeof(KonohaObjectHeader) + head + body) {
		//DBG_P("ct->cstruct_size =%d, request_size = %d", ct->cstruct_size, head+body);
		if(ct->searchSimilarClassNULL == NULL) {
			KonohaClassVar *newct = new_KonohaClass(kctx, bct, NULL, NOPLINE);
			newct->cflag |= kClass_Private;
			newct->cstruct_size = ct->cstruct_size * 2;
			KINITv(newct->methodList, ct->methodList);
			((KonohaClassVar*)ct)->searchSimilarClassNULL = (KonohaClass*)newct;
		}
		ct = ct->searchSimilarClassNULL;
	}
	return ct;
}

static kParam *new_Param(KonohaContext *kctx, ktype_t rtype, int psize, kparamtype_t *p)
{
	KonohaClass *ct = CT_(CLASS_Param);
	ct = CT_body(kctx, ct, sizeof(void*), psize * sizeof(kparamtype_t));
	kParamVar *pa = (kParamVar*)new_Object(kctx, ct, (void*)0);
	pa->rtype = rtype;
	pa->psize = psize;
	if(psize > 0) {
		memcpy(pa->paramtypeItems, p, sizeof(kparamtype_t) * psize);
	}
	return pa;
}

static void Method_init(KonohaContext *kctx, kObject *o, void *conf)
{
	kMethodVar *mtd = (kMethodVar*)o;
	bzero(&mtd->invokeMethodFunc, sizeof(kMethod) - sizeof(KonohaObjectHeader));
	//KINITv(mtd->tcode, (struct kToken*)K_NULL);
	//KINITv(mtd->kcode, K_NULL);
}

static void Method_reftrace(KonohaContext *kctx, kObject *o)
{
	BEGIN_REFTRACE(3);
	kMethod *mtd = (kMethod*)o;
	//KREFTRACEn(mtd->tcode);
	//KREFTRACEn(mtd->kcode);
	//KREFTRACEn(mtd->proceedNUL);
	END_REFTRACE();
}

static kMethod* new_Method(KonohaContext *kctx, uintptr_t flag, ktype_t cid, kmethodn_t mn, MethodFunc func)
{
#define CT_MethodVar CT_Method
	kMethodVar* mtd = new_(MethodVar, NULL);
	mtd->flag  = flag;
	mtd->typeId     = cid;
	mtd->mn      = mn;
	KLIB kMethod_setFunc(kctx, mtd, func);
	return mtd;
}

struct _kAbstractArray {
	KonohaObjectHeader h;
	KUtilsGrowingArray a;
} ;

static void Array_init(KonohaContext *kctx, kObject *o, void* conf)
{
	struct _kAbstractArray *a = (struct _kAbstractArray*)o;
	a->a.bytebuf     = NULL;
	a->a.bytesize    = 0;
	a->a.bytemax = ((size_t)conf * sizeof(void*));
	if(a->a.bytemax > 0) {
		KLIB Karray_init(kctx, &a->a, a->a.bytemax);
	}
	if(TY_isUnbox(O_p0(a))) {
		kArray_setUnboxData(a, 1);
	} else {
		kArray_setUnboxData(a, 0);
	}
}

static void Array_reftrace(KonohaContext *kctx, kObject *o)
{
	kArray *a = (kArray*)o;
	if(!kArray_isUnboxData(a)) {
		size_t i;
		BEGIN_REFTRACE(kArray_size(a));
		for(i = 0; i < kArray_size(a); i++) {
			printf("size size%zd\n", kArray_size(a));
			KREFTRACEv(a->objectItems[i]);
		}
		END_REFTRACE();
	}
}

static void Array_free(KonohaContext *kctx, kObject *o)
{
	struct _kAbstractArray *a = (struct _kAbstractArray*)o;
	KLIB Karray_free(kctx, &a->a);
}

static void Func_init(KonohaContext *kctx, kObject *o, void *conf)
{
	kFuncVar *fo = (kFuncVar*)o;
	KINITv(fo->self, K_NULL);
	KINITv(fo->mtd, conf != NULL ? KNULL(Method) : (kMethod*)conf);
}

static void Func_reftrace(KonohaContext *kctx, kObject *o)
{
	BEGIN_REFTRACE(4);
	kFunc *fo = (kFunc*)o;
	KREFTRACEv(fo->self);
	KREFTRACEv(fo->mtd);
	END_REFTRACE();
}
static KonohaClass *T_realtype(KonohaContext *kctx, KonohaClass *ct, KonohaClass *self)
{
	kParam *cparam = CT_cparam(self);
	DBG_ASSERT(ct->optvalue < cparam->psize);
	KonohaClass *pct = CT_(cparam->paramtypeItems[ct->optvalue].ty);
	return pct->realtype(kctx, pct, self);
}

#define TYPENAME(C) \
	.structname = #C,\
	.typeId = TY_##C,\
	.cflag = CFLAG_##C\

#define CLASSNAME(C) \
	.structname = #C,\
	.typeId = TY_##C,\
	.cflag = CFLAG_##C,\
	.cstruct_size = sizeof(k##C)\

static void loadInitStructData(KonohaContext *kctx)
{
	KDEFINE_CLASS defTvoid = {
		TYPENAME(void),
	};
	KDEFINE_CLASS defTvar = {
		TYPENAME(var),
	};
	KDEFINE_CLASS defObject = {
		CLASSNAME(Object),
		.init = Object_init,
		.reftrace = Object_reftrace,
		.initdef = Object_initdef,
	};
	KDEFINE_CLASS defBoolean = {
		CLASSNAME(Boolean),
		.init = Number_init,
		.unbox = Number_unbox,
		.p    = Boolean_p,
		.fnull = Boolean_fnull,
	};
	KDEFINE_CLASS defInt = {
		CLASSNAME(Int),
		.init  = Number_init,
		.unbox = Number_unbox,
		.p     = Int_p,
	};
	KDEFINE_CLASS defString = {
		CLASSNAME(String),
		.init = String_init,
		.free = String_free,
		.p    = String_p,
		.unbox = String_unbox
	};
	kparamtype_t ArrayCparam = {TY_Object, 1};
	KDEFINE_CLASS defArray = {
		CLASSNAME(Array),
		.init = Array_init,
		.reftrace = Array_reftrace,
		.free = Array_free,
//		.psize = 1, .cparams = &ArrayCparam,
	};
	KDEFINE_CLASS defParam = {
		CLASSNAME(Param),
		.init = Param_init,
	};
	KDEFINE_CLASS defMethod = {
		CLASSNAME(Method),
		.init = Method_init,
		.reftrace = Method_reftrace,
	};
	KDEFINE_CLASS defFunc = {
		CLASSNAME(Func),
		.init = Func_init,
		.reftrace = Func_reftrace,
	};
	KDEFINE_CLASS defSystem = {
		CLASSNAME(System),
		.init = DEFAULT_init,
	};
	KDEFINE_CLASS defT0 = {
		TYPENAME(0),
		.init = DEFAULT_init,
		.realtype = T_realtype,
	};
	KDEFINE_CLASS *DATATYPES[] = {
		&defTvoid,
		&defTvar,
		&defObject,
		&defBoolean,
		&defInt,
		&defString,
		&defArray,
		&defParam,
		&defMethod,
		&defFunc,
		&defSystem,
		&defT0,
		NULL,
	};
	KDEFINE_CLASS **dd = DATATYPES;
	while(dd[0] != NULL) {
		new_KonohaClass(kctx, NULL, dd[0], 0);
		dd++;
	}
	KonohaClassVar *ct = (KonohaClassVar *)CT_Array;
	ct->p0 = TY_Object;
}

//static KonohaClass *addClassDef(KonohaContext *kctx, kpack_t packid, kpack_t packdom, kString *name, KDEFINE_CLASS *cdef, kfileline_t pline)
//{
//	KonohaClassVar *ct = new_KonohaClass(kctx, NULL, cdef, pline);
//	ct->packid = packid;
//	ct->packdom = packdom;
//	if (name == NULL) {
//		const char *n = cdef->structname;
//		//ct->nameid = kuname(n, strlen(n), SPOL_ASCII|SPOL_POOL|SPOL_TEXT, _NEWID);
//	} else {
//		//ct->nameid = kuname(S_text(name), S_size(name), 0, _NEWID);
//	}
//	//CT_setName(kctx, ct, pline);
//	return (KonohaClass*)ct;
//}

static KMETHOD Fmethod_abstract(KonohaContext *kctx, KonohaStack *sfp)
{
	//kMethod *mtd = sfp[K_MTDIDX].mtdNC;
	//char mbuf[128];
	//kreportf(WARN_, sfp[K_RTNIDX].uline, "calling abstract method: %s.%s", T_cid(mtd->cid), T_mn(mbuf, mtd->mn));
	RETURNi_(0); //necessary
}

static void Method_setFunc(KonohaContext *kctx, kMethod *mtd, MethodFunc func)
{
	func = (func == NULL) ? Fmethod_abstract : func;
	((kMethodVar*)mtd)->invokeMethodFunc = func;
	//((kMethodVar*)mtd)->pc_start = CODE_NCALL;

}

static void Array_ensureMinimumSize(KonohaContext *kctx, struct _kAbstractArray *a, size_t min)
{
	size_t minbyte = min * sizeof(void*);
	if(!(minbyte < a->a.bytemax)) {
		if(minbyte < sizeof(kObject)) minbyte = sizeof(kObject);
		KLIB Karray_expand(kctx, &a->a, minbyte);
	}
}
//static void Array_ensureMinimumSize(KonohaContext *kctx, struct _kAbstractArray *a, size_t min)
//{
//	if(!((min * sizeof(void*)) < a->a.bytemax)) {
//		if(min < sizeof(kObject)) min = sizeof(kObject);
//		KLIB Karray_expand(kctx, &a->a, min);
//	}
//}

static void Array_add(KonohaContext *kctx, kArray *o, kObject *value)
{
	size_t asize = kArray_size(o);
	struct _kAbstractArray *a = (struct _kAbstractArray*)o;
	Array_ensureMinimumSize(kctx, a, asize+1);
	DBG_ASSERT(a->a.objectItems[asize] == NULL);
	KINITv(a->a.objectItems[asize], value);
	a->a.bytesize = (asize+1) * sizeof(void*);
}

/* KonohaSpace/Class/Method */
static kMethod* CT_findMethodNULL(KonohaContext *kctx, KonohaClass *ct, kmethodn_t mn)
{
	while(ct != NULL) {
		size_t i;
		kArray *a = ct->methodList;
		for(i = 0; i < kArray_size(a); i++) {
			kMethod *mtd = a->methodItems[i];
			if((mtd)->mn == mn) {
				return mtd;
			}
		}
		ct = ct->searchSuperMethodClassNULL;
	}
	return NULL;
}

#define kNameSpace_getStaticMethodNULL(ns, mn)   KonohaSpace_getStaticMethodNULL(kctx, ns, mn)

static kMethod* KonohaSpace_getMethodNULL(KonohaContext *kctx, kNameSpace *ks, ktype_t cid, kmethodn_t mn, int option, int policy)
{
	while(ks != NULL) {
		size_t i;
		kArray *a = ks->methodList;
		for(i = 0; i < kArray_size(a); i++) {
			kMethod *mtd = a->methodItems[i];
			if(mtd->typeId == cid && mtd->mn == mn) {
				return mtd;
			}
		}
		ks = ks->parentNULL;
	}
	return CT_findMethodNULL(kctx, CT_(cid), mn);
}

static void KCLASSTABLE_initKonohaLib(KonohaLibVar *l)
{
	l->new_kObject = new_Object;
	l->new_kMethod   = new_Method;
	l->kMethod_setFunc = Method_setFunc;
	l->kArray_add = Array_add;
	//l->kNameSpace_getMethodNULL = kNameSpace_getMethodNULL;
	//l->KaddClassDef = addClassDef;
}

static void CT_setName(KonohaContext *kctx, KonohaClassVar *ct, kfileline_t pline)
{
	//uintptr_t lname = longid(ct->packdom, ct->nameid);
	//kreportf(DEBUG_, pline, "new class domain=%s, name='%s.%s'", T_PN(ct->packdom), T_PN(ct->packid), T_UN(ct->nameid));
	//KonohaClass *ct2 = (KonohaClass*)map_getu(kctx, kctx->share->lcnameMapNN, lname, (uintptr_t)NULL);
	//if(ct2 == NULL) {
	//	map_addu(kctx, kctx->share->lcnameMapNN, lname, (uintptr_t)ct);
	//}
	if(ct->methodList == NULL) {
		KINITv(ct->methodList, K_EMPTYARRAY);
		if(ct->typeId > CLASS_Object) {
			ct->searchSuperMethodClassNULL = CT_(ct->superTypeId);
		}
	}
	//if(ct->cparam == NULL) {
	//	KINITv(ct->cparam, K_NULLPARAM);
	//}
}

static void initStructData(KonohaContext *kctx)
{
	KonohaClass **ctt = (KonohaClass**)kctx->share->classTable.classItems;
	size_t i;
	for (i = 0; i <= CLASS_T0; i++) {
		KonohaClassVar *ct = (KonohaClassVar *)ctt[i];
		//const char *name = ct->DBG_NAME;
		//ct->nameid = kuname(name, strlen(name), SPOL_ASCII|SPOL_POOL|SPOL_TEXT, _NEWID);
		CT_setName(kctx, ct, 0);
	}
}

static	kbool_t FLOAT_init(KonohaContext *kctx, kNameSpace *ks);
static kbool_t nxt_init(KonohaContext *kctx, kNameSpace *ks);

static void KCLASSTABLE_init(KonohaContextVar *kctx)
{
	static KonohaRuntimeVar share;
	kctx->share = &share;
	KCLASSTABLE_initKonohaLib((KonohaLibVar*)kctx->klib);
	KLIB Karray_init(kctx, &(share.classTable), MAX_CT * sizeof(KonohaClass));
	loadInitStructData(kctx);
	KINITv(share.constNull, new_(Object, NULL));
	kObject_setNullObject(share.constNull, 1);
	//
	KINITv(share.constData, new_(Array, 0));
	KINITv(share.emptyArray, new_(Array, 0));
	initStructData(kctx);
	//FLOAT_init(kctx, NULL);
	nxt_init(kctx, NULL);
}

#define _Public    kMethod_Public
#define _Const     kMethod_Const
#define _Immutable kMethod_Immutable
#define _F(F)      (intptr_t)(F)

static void KCLASSTABLE_loadMethod(KonohaContext *kctx)
{
	//int FN_x = FN_("x");
	intptr_t MethodData[] = {
		_F(Object_toString), TY_Object, MN_to(Int, String),
		_F(Boolean_opNOT), TY_Boolean, MN_(Boolean_opNOT),
		_F(Int_opMINUS), TY_Int, MN_(Int_opMINUS),
		_F(Int_opADD), TY_Int, MN_(Int_opADD),
		_F(Int_opSUB), TY_Int, MN_(Int_opSUB),
		_F(Int_opMUL), TY_Int, MN_(Int_opMUL),
		/* opDIV and opMOD raise zero divided exception. Don't set _Const */
		_F(Int_opDIV), TY_Int, MN_(Int_opDIV),
		_F(Int_opMOD), TY_Int, MN_(Int_opMOD),
		_F(Int_opEQ),  TY_Int, MN_(Int_opEQ),
		_F(Int_opNEQ), TY_Int, MN_(Int_opNEQ),
		_F(Int_opLT),  TY_Int, MN_(Int_opLT),
		_F(Int_opLTE), TY_Int, MN_(Int_opLTE),
		_F(Int_opGT),  TY_Int, MN_(Int_opGT),
		_F(Int_opGTE), TY_Int, MN_(Int_opGTE),
		_F(Int_toString), TY_Int, MN_to(Int, String),
		_F(String_toInt), TY_String, MN_to(String, Int),
		_F(String_opADD), TY_String, MN_(String_opADD),
		_F(System_assert), TY_System, MN_(System_assert),
		_F(System_p), TY_System, MN_(System_p),
		_F(System_gc), TY_System, MN_(System_gc),
		DEND,
	};

	KLIB kNameSpace_loadMethodData(kctx, NULL, MethodData);
}


static kbool_t nxt_init(KonohaContext *kctx, kNameSpace *ks)
{
	intptr_t MethodData[] = {
		_F(System_balanceInit), TY_System, MN_(System_balanceInit),
		_F(System_dly), TY_System, MN_(System_dly),
		_F(System_actMainTask), TY_System, MN_(System_actMainTask),
		_F(System_ecrobotIsRunning), TY_System, MN_(System_ecrobotIsRunning),
		_F(System_tailControl), TY_System, MN_(System_tailControl),
		_F(System_manipulateTail), TY_System, MN_(System_manipulateTail),
		_F(System_ecrobotInitNxtstate), TY_System, MN_(System_ecrobotInitNxtstate),
		_F(System_ecrobotInitSensors), TY_System, MN_(System_ecrobotInitSensors),
		_F(System_ecrobotSetLightSensorActive), TY_System, MN_(System_ecrobotSetLightSensorActive),
		_F(System_ecrobotGetGyroSensor), TY_System, MN_(System_ecrobotGetGyroSensor),
		_F(System_ecrobotGetLightSensor), TY_System, MN_(System_ecrobotGetLightSensor),
		_F(System_nxtMotorSetSpeed), TY_System, MN_(System_nxtMotorSetSpeed),
		_F(System_nxtMotorSetCount), TY_System, MN_(System_nxtMotorSetCount),
		_F(System_nxtMotorGetCount), TY_System, MN_(System_nxtMotorGetCount),
		_F(System_staCyc), TY_System, MN_(System_staCyc),
		_F(System_waiSem), TY_System, MN_(System_waiSem),
		_F(System_balanceControl), TY_System, MN_(System_balanceControl),
		DEND,
	};
	KLIB kNameSpace_loadMethodData(kctx, ks, MethodData);
	return true;
}

//static	kbool_t FLOAT_init(KonohaContext *kctx, kNameSpace *ks)
//{
//	kmodfloat_t *base = (kmodfloat_t*)KCALLOC(sizeof(kmodfloat_t), 1);
//	base->h.name     = "float";
//	base->h.setup    = kmodfloat_setup;
//	base->h.reftrace = kmodfloat_reftrace;
//	base->h.free     = kmodfloat_free;
//	Konoha_setModule(MOD_float, &base->h, 0);
//
//	KDEFINE_CLASS defFloat = {
//		STRUCTNAME(Float),
//		.cflag = CFLAG_Int,
//		.init = Float_init,
//	};
//
//	//base->cFloat = Konoha_addClassDef(0/*ks->packid*/, PN_konoha, NULL, &defFloat, 0);
//	base->cFloat = new_KonohaClass(kctx, NULL, &defFloat, 0);
//	CT_setName(kctx, (KonohaClassVar*)base->cFloat, 0);
//
//	int FN_x = FN_("x");
//	intptr_t MethodData[] = {
//		//_F(Float_opADD), TY_Float, MN_(Float_opADD),
//		//_F(Float_opSUB), TY_Float, MN_(Float_opSUB),
//		//_F(Float_opMUL), TY_Float, MN_(Float_opMUL),
//		//_F(Float_opDIV), TY_Float, MN_(Float_opDIV),
//		//_F(Float_opEQ),  TY_Float, MN_(Float_opEQ),
//		//_F(Float_opNEQ), TY_Float, MN_(Float_opNEQ),
//		//_F(Float_opLT),  TY_Float, MN_(Float_opLT),
//		//_F(Float_opLTE), TY_Float, MN_(Float_opLTE),
//		//_F(Float_opGT),  TY_Float, MN_(Float_opGT),
//		//_F(Float_opGTE), TY_Float, MN_(Float_opGTE),
//		//_F(Float_toInt), TY_Float, MN_to(Float, Int),
//		//_F(Int_toFloat), TY_Int, MN_to(Int, Float),
//		//_F(Float_toString), TY_Float, MN_to(Float, String),
//		//_F(String_toFloat), TY_String, MN_to(String, Float),
//		DEND,
//	};
//	kNameSpace_loadMethodData(ks, MethodData);
//	return true;
//}
