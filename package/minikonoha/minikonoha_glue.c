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

#include <minikonoha/minikonoha.h>
#include <minikonoha/sugar.h>

#ifdef __cplusplus
extern "C"{
#endif


/* ------------------------------------------------------------------------ */

typedef struct kKonohaFactoryVar kKonohaFactory;

struct kKonohaFactoryVar {
	KonohaObjectHeader h;
	KonohaFactory *factory;
};

typedef struct kKonohaVar kKonoha;
struct kKonohaVar {
	KonohaObjectHeader h;
	KonohaContext *konoha;
};

static void kKonohaFactory_Init(KonohaContext *kctx, kObject *o, void *conf)
{
	struct kKonohaFactoryVar *f = (struct kKonohaFactoryVar *)o;
	f->factory = (KonohaFactory *)KMalloc(sizeof(KonohaFactory), NULL);
	memcpy(f->factory, kctx->platApi, sizeof(KonohaFactory));
}

static void kKonohaFactory_Free(KonohaContext *kctx, kObject *o)
{
	struct kKonohaFactoryVar *f = (struct kKonohaFactoryVar *)o;
	if(f->factory != NULL) {
		KFree(f->factory, sizeof(KonohaFactory));
	}
}

//static void kKonohaFactory_p(KonohaContext *kctx, KonohaValue *v, int pos, KGrowingBuffer *wb)
//{
//	kKonohaFactory *file = (kKonohaFactory *)v[pos].asObject;
//	if(file->PathInfoNULL != NULL) {
//		KLIB Kwb_write(kctx, wb, S_text(file->PathInfoNULL), S_size(file->PathInfoNULL));
//	}
//	else {
//		KLIB Kwb_printf(kctx, wb, "FILE:%p", file->fp);
//	}
//}

static void kKonoha_Init(KonohaContext *kctx, kObject *o, void *conf)
{
	struct kKonohaVar *ko = (struct kKonohaVar *)o;
	ko->konoha = KLIB KonohaFactory_CreateKonoha((KonohaFactory *)conf);
}

static void kKonoha_Free(KonohaContext *kctx, kObject *o)
{
	struct kKonohaVar *ko = (struct kKonohaVar *)o;
	if(ko->konoha != NULL) {
		KLIB Konoha_Destroy(ko->konoha);
		ko->konoha = NULL;
	}
}

//static void kKonoha_p(KonohaContext *kctx, KonohaValue *v, int pos, KGrowingBuffer *wb)
//{
//	kKonoha *file = (kKonoha *)v[pos].asObject;
//	if(file->PathInfoNULL != NULL) {
//		KLIB Kwb_write(kctx, wb, S_text(file->PathInfoNULL), S_size(file->PathInfoNULL));
//	}
//	else {
//		KLIB Kwb_printf(kctx, wb, "FILE:%p", file->fp);
//	}
//}


// --------------------------------------------------------------------------
//## KonohaFactory KonohaFactory.new();

static KMETHOD KonohaFactory_new(KonohaContext *kctx, KonohaStack *sfp)
{
	KReturn(KLIB new_kObject(kctx, OnStack, KGetReturnType(sfp), 0));
}

//## boolean KonohaFactory.loadModule(String string);
static KMETHOD KonohaFactory_loadModule(KonohaContext *kctx, KonohaStack *sfp)
{
	kKonohaFactory *f = (kKonohaFactory *)sfp[0].asObject;
	KReturnUnboxValue(f->factory->LoadPlatformModule(f->factory, S_text(sfp[1].asString), ReleaseModule));
}

//## Konoha KonohaFactory.create();
static KMETHOD KonohaFactory_create(KonohaContext *kctx, KonohaStack *sfp)
{
	kKonohaFactory *f = (kKonohaFactory *)sfp[0].asObject;
	KReturn(KLIB new_kObject(kctx, OnStack, KGetReturnType(sfp), (uintptr_t)f->factory));
}

//## void Konoha.loadScript(String filename);
static KMETHOD Konoha_loadScript(KonohaContext *kctx, KonohaStack *sfp)
{
	kKonoha *ko = (kKonoha *)sfp[0].asObject;
	KLIB Konoha_LoadScript(ko->konoha, S_text(sfp[1].asString));
}

//## void Konoha.eval(String script);
static KMETHOD Konoha_eval(KonohaContext *kctx, KonohaStack *sfp)
{
	kKonoha *ko = (kKonoha *)sfp[0].asObject;
	KLIB Konoha_Eval(ko->konoha, S_text(sfp[1].asString), 0);
}

#define _F(F) (intptr_t)(F)

static kbool_t minikonoha_defineMethod(KonohaContext *kctx, kNameSpace *ns, KTraceInfo *trace)
{
	KDEFINE_CLASS defKonohaFactory = {0};
	SETSTRUCTNAME(defKonohaFactory, KonohaFactory);
	defKonohaFactory.init = kKonohaFactory_Init;
	defKonohaFactory.free = kKonohaFactory_Free;
	KDEFINE_CLASS defKonoha = {0};
	SETSTRUCTNAME(defKonoha, Konoha);
	defKonoha.init = kKonoha_Init;
	defKonoha.free = kKonoha_Free;

	KonohaClass *cKonohaFactory = KLIB KonohaClass_define(kctx, ns->packageId, NULL, &defKonohaFactory, trace);
	KonohaClass *cKonoha =  KLIB KonohaClass_define(kctx, ns->packageId, NULL, &defKonoha, trace);
	int TY_KonohaFactory = cKonohaFactory->typeId, TY_Konoha = cKonoha->typeId;

	KDEFINE_METHOD MethodData[] = {
		kMethod_Public, _F(KonohaFactory_new), TY_KonohaFactory, TY_KonohaFactory, MN_("new"), 0,
		kMethod_Public, _F(KonohaFactory_loadModule), TY_boolean, TY_KonohaFactory, MN_("loadModule"), 1, TY_String, FN_("name"),
		kMethod_Public, _F(KonohaFactory_create), TY_Konoha, TY_KonohaFactory, MN_("create"), 0,
		kMethod_Public, _F(Konoha_loadScript), TY_boolean, TY_Konoha, MN_("loadScript"), 1, TY_String, FN_("filename"),
		kMethod_Public, _F(Konoha_eval), TY_Konoha, TY_Konoha, MN_("eval"), 1, TY_String, FN_("script"),
		DEND,
	};
	KLIB kNameSpace_LoadMethodData(kctx, ns, MethodData, trace);
	return true;
}

// ----

static kbool_t minikonoha_PackupNameSpace(KonohaContext *kctx, kNameSpace *ns, int option, KTraceInfo *trace)
{
	minikonoha_defineMethod(kctx, ns, trace);
	return true;
}

static kbool_t minikonoha_ExportNameSpace(KonohaContext *kctx, kNameSpace *ns, kNameSpace *exportNS, int option, KTraceInfo *trace)
{
	return true;
}

KDEFINE_PACKAGE* minikonoha_Init(void)
{
	static KDEFINE_PACKAGE d = {0};
	KSetPackageName(d, "minikonoha", K_VERSION);
	d.PackupNameSpace    = minikonoha_PackupNameSpace;
	d.ExportNameSpace   = minikonoha_ExportNameSpace;
	return &d;
}

#ifdef __cplusplus
}
#endif
